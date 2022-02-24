/****************************************************************************
 *
 *   Copyright (c) 2012-2019 PX4 Development Team. All rights reserved.
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

/**
 * @file component_manager.c
 * Component Manager
 *
 * @author Anton Hristozov <mail@example.com>
 */

#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/tasks.h>
#include <px4_platform_common/posix.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <math.h>

#include <uORB/uORB.h>
#include <uORB/topics/vehicle_acceleration.h>
#include <uORB/topics/vehicle_attitude.h>
#include <pxh.h>

extern "C" int component_manager_main(int argc, char *argv[]);
/**
 * Print the correct usage.
 */
static void usage(const char *reason);


/* Variables */
static bool thread_should_exit = false;         /**< Daemon exit flag */
static bool thread_running = false;             /**< Daemon status flag */
static int daemon_task;                         /**< Handle of deamon task / thread */

int component_manager_thread(int argc, char *argv[])
{
	PX4_INFO("Component Manager!");

	px4_daemon::Pxh::process_line("hello start",true);

	px4_daemon::Pxh::process_line("px4_simple_app",true);

	while(!thread_should_exit){
	    sleep(1);

	}

	thread_running = false;

	PX4_INFO("Component manager Exiting");

	return 0;
}



static void
usage(const char *reason)
{
        if (reason) {
                fprintf(stderr, "%s\n", reason);
        }

        fprintf(stderr, "usage: rover_steering_control {start|stop|status}\n\n");
}



int component_manager_main(int argc, char *argv[])
{
        if (argc < 2) {
                usage("missing command");
                return 1;
        }

        if (!strcmp(argv[1], "start")) {

                if (thread_running) {
                        PX4_WARN("running");
                        /* this is not an error */
                        return 0;
                }

                thread_should_exit = false;
                daemon_task = px4_task_spawn_cmd("component_manager_thread",
                                                 SCHED_DEFAULT,
                                                 SCHED_PRIORITY_MAX - 20,
                                                 2048,
                                                 component_manager_thread,
                                                 (argv) ? (char *const *)&argv[2] : (char *const *)NULL);

                 thread_running = true;
                return 0;
        }

        if (!strcmp(argv[1], "stop")) {
                thread_should_exit = true;
                return 0;
        }

        if (!strcmp(argv[1], "status")) {
                if (thread_running) {
                        PX4_WARN("running");

                } else {
                        PX4_WARN("not started");
                }

                return 0;
        }

        usage("unrecognized command");
        return 1;
}

