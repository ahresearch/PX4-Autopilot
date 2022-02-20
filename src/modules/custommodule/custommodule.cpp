/****************************************************************************
 *
 *   Copyright (c) 2018 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include "custommodule.h"

#include <px4_platform_common/getopt.h>
#include <px4_platform_common/log.h>
#include <px4_platform_common/posix.h>

#include <uORB/topics/parameter_update.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/vehicle_global_position.h>
#include <uORB/topics/vehicle_gps_position.h>
#include <cmath>

/* Sample data structure to pass to thread */
typedef struct _thread_data_t {
  int tid;
  double stuff;
} thread_data_t;

pthread_t CustomModule::diag_thr;

int CustomModule::print_status()
{
	PX4_INFO("Running");
	// TODO: print additional runtime information about the state of the module

	return 0;
}

int CustomModule::custom_command(int argc, char *argv[])
{

	if (!is_running()) {
		print_usage("not running");
		return 1;
	}

	// additional custom commands can be handled like this:
	if (!strcmp(argv[0], "test")) {
		get_instance()->test();
		return 0;
	}


	return print_usage("unknown command");
}


int CustomModule::test()
{
	PX4_INFO("test command");

	return 0;
}

bool CustomModule::check_gps_data(double alt)
{
        bool result = true;
	static double prev_value = 0;
	static double delta = 2000;
	if(abs(alt - prev_value) > delta){
		PX4_INFO("");
	        PX4_INFO("check_gps_data()::altitude jumped bigger than delta");
		PX4_INFO("");
		result = false;
	 }
	prev_value = alt;
	return result;
}





void CustomModule::RunDiag(){
  while(true){
      printf("CustomModule::Hello from RunDiag() function\n");
      sleep(1);
  }
}

void * CustomModule::run_diag(void *arg){
	CustomModule *instance = get_instance();

	/*  Call the main class methods from this thread */
	instance->RunDiag();
 	pthread_exit(NULL);
}




int CustomModule::task_spawn(int argc, char *argv[])
{
	thread_data_t thr_data;
	int rc;

	_task_id = px4_task_spawn_cmd("custommodule",
				      SCHED_DEFAULT,
				      SCHED_PRIORITY_DEFAULT,
				      1024,
				      (px4_main_t)&run_trampoline,
				      (char *const *)argv);

	if (_task_id < 0) {
		_task_id = -1;
		return -errno;
	}

    thr_data.tid  = 1;
    thr_data.stuff = 3.14;

    if ((rc = pthread_create(&diag_thr, NULL, CustomModule::run_diag, &thr_data))) {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      return EXIT_FAILURE;
    }


	return 0;
}

CustomModule *CustomModule::instantiate(int argc, char *argv[])
{
	int example_param = 0;
	bool example_flag = false;
	bool error_flag = false;

	int myoptind = 1;
	int ch;
	const char *myoptarg = nullptr;

	// parse CLI arguments
	while ((ch = px4_getopt(argc, argv, "p:f", &myoptind, &myoptarg)) != EOF) {
		switch (ch) {
		case 'p':
			example_param = (int)strtol(myoptarg, nullptr, 10);
	                PX4_INFO("parameter: %d",example_param);
			break;

		case 'f':
			example_flag = true;
	                PX4_INFO("flag is true");
			break;

		case '?':
			error_flag = true;
			break;

		default:
			PX4_WARN("unrecognized flag");
			error_flag = true;
			break;
		}
	}

	if (error_flag) {
		return nullptr;
	}
	CustomModule *instance = new CustomModule(example_param, example_flag);

	if (instance == nullptr) {
		PX4_ERR("alloc failed");
	}

	return instance;
}

CustomModule::CustomModule(int example_param, bool example_flag)
	: ModuleParams(nullptr)
{
}

void CustomModule::run()
{
	// Example: run the loop synchronized to the sensor_combined topic publication
	int pos_sub_fd = orb_subscribe(ORB_ID(vehicle_global_position));
	int sensor_sub_fd = orb_subscribe(ORB_ID(sensor_combined));
	int gps_sub_fd = orb_subscribe(ORB_ID(vehicle_gps_position));
    struct vehicle_gps_position_s final_gps_pos;
    static int count = 0;
    px4_pollfd_struct_t fds[] = {
                { .fd = pos_sub_fd,      .events = POLLIN },
                { .fd = sensor_sub_fd,   .events = POLLIN },
                { .fd = gps_sub_fd,      .events = POLLIN },
                /* there could be more file descriptors here, in the form like:
                 * { .fd = other_sub_fd,   .events = POLLIN },
                 */
        };

	// initialize parameters
	parameters_update(true);
	memset(&final_gps_pos, 0, sizeof(final_gps_pos));
	orb_advert_t gps_pub = orb_advertise(ORB_ID(vehicle_gps_position), &final_gps_pos);

	while (!should_exit()) {


		// wait for up to 1000ms for data
		int pret = px4_poll(fds, (sizeof(fds) / sizeof(fds[0])), 1000);

		if (pret == 0) {
			// Timeout: let the loop run anyway, don't do `continue` here

		} else if (pret < 0) {
			// this is undesirable but not much we can do
			PX4_ERR("poll error %d, %d", pret, errno);
			px4_usleep(50000);
			continue;

		} else{
                        if (fds[0].revents & POLLIN) {
                                /* obtained data for the first file descriptor */
                                struct vehicle_global_position_s global_pos;
                                /* copy sensors data into local buffer */
                                orb_copy(ORB_ID(vehicle_global_position), pos_sub_fd, &global_pos);
                                /* PX4_INFO("Position (lat,lon,alt):\t%8.4f\t%8.4f\t%8.4f",
                                         (double)global_pos.lat,
                                         (double)global_pos.lon,
                                         (double)global_pos.alt); */
                        }
			if (fds[1].revents & POLLIN) {


                           /* obtained data for the second file descriptor */
			   struct sensor_combined_s sensor_combined;
			   orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &sensor_combined);
			   // TODO: do something with the data...
                            if(count >= 100){
                            PX4_INFO("Accelerometer:\t%8.4f\t%8.4f\t%8.4f",
                                         (double)sensor_combined.accelerometer_m_s2[0],
                                         (double)sensor_combined.accelerometer_m_s2[1],
                                         (double)sensor_combined.accelerometer_m_s2[2]);
                           PX4_INFO("Gyro:\t%8.4f\t%8.4f\t%8.4f",
                                         (double)sensor_combined.gyro_rad[0],
                                         (double)sensor_combined.gyro_rad[1],
                                         (double)sensor_combined.gyro_rad[2]);
                               count = 0;
                            }
                            count++;
                        }
			if (fds[2].revents & POLLIN) {

                           /* obtained data for the second file descriptor */
                           struct vehicle_gps_position_s gps_pos;
			   orb_copy(ORB_ID(vehicle_gps_position), gps_sub_fd, &gps_pos);
			   // TODO: do something with the data...
                          /*

                           PX4_INFO("GPS:\t%8.4f\t%8.4f\t%8.4f",
                                         (double)gps_pos.lat,
                                         (double)gps_pos.lon,
                                         (double)gps_pos.alt); */

                           // Do some checking here
			   check_gps_data(gps_pos.alt);
			   final_gps_pos.timestamp = gps_pos.timestamp ;
                           final_gps_pos.time_utc_usec = gps_pos.time_utc_usec ;
                           final_gps_pos.fix_type = gps_pos.fix_type ;
                           final_gps_pos.lat = gps_pos.lat ;
                           final_gps_pos.lon = gps_pos.lon ;
                           final_gps_pos.alt = gps_pos.alt ;
                           final_gps_pos.eph = gps_pos.eph ;
                           final_gps_pos.epv = gps_pos.epv ;
                           final_gps_pos.vel_m_s = gps_pos.vel_m_s ;
                           final_gps_pos.vel_n_m_s = gps_pos.vel_n_m_s ;
                           final_gps_pos.vel_e_m_s = gps_pos.vel_e_m_s ;
                           final_gps_pos.vel_d_m_s = gps_pos.vel_d_m_s ;
                           final_gps_pos.cog_rad = gps_pos.cog_rad ;
                           final_gps_pos.satellites_used = gps_pos.satellites_used ;
                           final_gps_pos.s_variance_m_s = gps_pos.s_variance_m_s ;

			   orb_publish(ORB_ID(vehicle_gps_position),gps_pub, &final_gps_pos);

                        }

			// Add your processing here
			// Create a function in the class and call it
			// Publish topics by calling orb_publish() for other modules in px4 to be updated
		}

		parameters_update();
	}

	orb_unsubscribe(sensor_sub_fd);
	orb_unsubscribe(pos_sub_fd);
	orb_unsubscribe(gps_sub_fd);
	PX4_INFO("run() method exiting.");
}

void CustomModule::parameters_update(bool force)
{
	// check for parameter updates
	if (_parameter_update_sub.updated() || force) {
		// clear update
		parameter_update_s update;
		_parameter_update_sub.copy(&update);

		// update parameters from storage
		updateParams();
	}
}

int CustomModule::print_usage(const char *reason)
{
	if (reason) {
		PX4_WARN("%s\n", reason);
	}

	PRINT_MODULE_DESCRIPTION(
		R"DESCR_STR(
### Description
Section that describes the provided module functionality.

This is a template for a module running as a task in the background with start/stop/status functionality.

### Implementation
Section describing the high-level implementation of this module.

### Examples
CLI usage example:
$ custommodule start -f -p 42

)DESCR_STR");

	PRINT_MODULE_USAGE_NAME("custommodule", "template");
	PRINT_MODULE_USAGE_COMMAND("start");
	PRINT_MODULE_USAGE_PARAM_FLAG('f', "Optional example flag", true);
	PRINT_MODULE_USAGE_PARAM_INT('p', 0, 0, 1000, "Optional example parameter", true);
	PRINT_MODULE_USAGE_DEFAULT_COMMANDS();

	return 0;
}

int custommodule_main(int argc, char *argv[])
{
	int res = CustomModule::main(argc, argv);
	if ((argc > 1) && (res == 0)  && (strcmp(argv[1], "stop") == 0)) {
		/* Cancel the diagnostics thread */
		res = pthread_cancel(CustomModule::diag_thr);
		if(res == 0){
			PX4_INFO("Auxiliary thread stopped");
		}
	}
	return res;
}
