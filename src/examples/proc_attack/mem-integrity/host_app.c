#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int len(char *str);

typedef struct _thread_data_t {
  int tid;
  char stuff[256];
} thread_data_t;

/* Thread run function */
void * run_thread(void *arg){
	_thread_data_t * thr_data =  (_thread_data_t *)arg;
	while(true){
      printf("run_thread() func: %s - addr: %p\n",thr_data->stuff,thr_data->stuff);
      sleep(1);
  }
 	pthread_exit(NULL);
}


int main(int ac, char **av)
{
	char *str;
	char *buff;
	thread_data_t thr_data;
	int rc;
  pthread_t test_thr;


	if (ac == 2)
	{
	   str = (char *) malloc(len(av[1]) + 1);
	   buff = (char *) malloc(len(av[1]) + 1);
	   strcpy(str, av[1]);
	}
	else{
	   printf("Incorrect number of arguments\n");
	   return -1;
	}
  strcpy(thr_data.stuff,str);
  if ((rc = pthread_create(&test_thr, NULL, run_thread, &thr_data))) {
     fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
     return EXIT_FAILURE;
  }

	pthread_setname_np(test_thr, "test_thread");
	strcpy(buff,str);
	printf("\n");
	while (true)
	{
		 printf("main() function  : %s - addr: %p\n", buff, buff);
		 strcpy(buff,str);
		 sleep(1);
	}
	free(str);
	free(buff);
	return (0);
}

int len(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
		;
	return (i);
}
