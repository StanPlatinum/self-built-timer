/* Usage: gcc -lthread
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#include <asm/delay.h>

#include <sys/types.h>
#include <sys/sysinfo.h>

#define __USE_GNU
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <sched.h>

#include "rdtsc.h"

#define CLOCK_MAX 1ULL<<63

uint64_t ticks;	/* global, not sure if it is vital */

pthread_t thread[2];

int cpu_nums;
/* set cpu core */
int set_cpu(int i)
{
	cpu_set_t mask;
	CPU_ZERO(&mask);
	if(cpu_nums < 2) {
		printf("not enough CPU cores!\n");
		return -1;
	}
	CPU_SET(i, &mask);
	if(sched_setaffinity(0, sizeof(mask), &mask) == -1) {
		printf("could not set CPU affinity!\n");
		return -1;
	}
	return 0;
}

void count_loop_asm(uint64_t *counter)
{
	asm volatile (	"movq %0, %%rcx \n\t"
			"1: inc %%rax \n\t"
			"movq %%rax, (%%rcx) \n\t"
			"jmp 1b"
			:
			: "m"(counter)
		);	
}

void count_loop_asm_slow(uint64_t *counter)
{
	asm volatile (	"movq %0, %%rcx \n\t"
			"1: incq (%%rcx) \n\t"
			"jmp 1b"
			:
			: "m"(counter)
		);	
}

void *thread_clock()
{
	int i;
	printf("this is thread clock...\n");
	uint64_t *s = &ticks;
	set_cpu(0);
	
	/* clock self */
#if 0	
	for (i = 0; i < CLOCK_MAX; i++)
		ticks++;
	printf("ticks ran out\n");
	count_loop_asm_slow(s);
#endif
	count_loop_asm(s);

	pthread_exit(NULL);
}

void *thread_attack()
{
	uint64_t start, end;
	unsigned long long tsc_start, tsc_end, self_start, self_end;
	float result, diff;
	printf("this is thread timing attack...\n");
	set_cpu(1);

	int i;
	//warmup
	for(i = 0; i < 10; i++){
		rdtsc_start();
		rdtsc_end();
	}
	/* read clock */
	start = ticks;
	tsc_start = rdtsc_start();

	usleep(1);
	//udelay(1);
	
	/* read clock */
	tsc_end = rdtsc_end();
	end = ticks;
	/* measure rdtsc ifself */
	self_start = rdtsc_start();
	rdtsc_start();
	rdtsc_end();
	self_end =rdtsc_end(); 

	printf("cost:%llu\n", (unsigned long long)(end - start));
	printf("cost:%llu - FORTSC\n", tsc_end - tsc_start);
	diff = end - start*1.0;
	result = (tsc_end - tsc_start + self_start - self_end)/diff;
	printf("%f, cycles per ticks\n", result);
	pthread_exit(NULL);
}

int startup_clock()
{
	int ret = 1;
	/* create the clock thread */
	if((pthread_create(&thread[0], NULL, thread_clock, NULL)) != 0) {
		ret = -1;
	} else {
		ret = 0;
	}
	return ret;
}

int main()
{
	int create_assert;
	memset(&thread, 0, sizeof(thread));
	cpu_nums = sysconf(_SC_NPROCESSORS_CONF);

	/* start up the clock thread */ 
	create_assert = startup_clock();
	if(create_assert == 0)	printf("clock thread created\n");
	else printf("clock failed!\n");

	sleep(1);

	/* create the attack thread */
	if((create_assert = pthread_create(&thread[1], NULL, thread_attack, NULL)) != 0)	printf("create attack failed!\n");
	else	printf("attack thread created\n");

	sleep(1);

	/* finish the attack thread */
	pthread_join(thread[1], NULL);
	pthread_join(thread[0], NULL);

	return 0;
}
