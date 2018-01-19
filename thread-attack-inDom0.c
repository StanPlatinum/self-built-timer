/* Usage: gcc -lthread
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <emmintrin.h>

#include <sys/types.h>
#include <sys/sysinfo.h>

#define __USE_GNU
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <sched.h>

#include "spec.h"
#include "rdtsc.h"
#include "clock.h"
#include "hugep.h"
#include "probe.h"

uint64_t ticks;	/* global, it is vital */

pthread_t thread[2];

int cpu_nums;	/* total cpu core number, at least 2 */
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

/* read specific line and time */
uint64_t probe_line(char *p)
{
	uint64_t start, end , result = 0;
	char tmp[64];	/* defined here for accessing a memory line */
	start = ticks;
	tmp[0] = p[0];
	tmp[1] = p[1];
	tmp[3] = p[3];
	tmp[3] = p[7];
	tmp[3] = p[15];
	tmp[3] = p[31];
	end = ticks;
	result = end - start;
	return result;
}

/* read set and time */
uint64_t probe_set(char *p)
{
	uint64_t start, end , result, rv = 0;
	int i;
	char tmp[64];	/* defined here for accessing a memory line */
	for (i = 0; i < L3_ways; i++) {
		start = ticks;
		tmp[0] = p[0];
		tmp[1] = p[1];
		tmp[3] = p[3];
		tmp[3] = p[7];
		tmp[3] = p[15];
		tmp[3] = p[31];
		end = ticks;
		p = p + (L3_SLICE_number_of_sets)*64;
		result = end - start;
		rv += result;
	}
	return rv;
}

/* to create a self-built clock */
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
	count_loop_asm(s);	/* actually it's infinite loop */
	pthread_exit(NULL);
}

/* to carry out the timing attack */
void *thread_attack()
{
	uint64_t rpl1, rp1, rp2, rp3, rp4, rp5, rp6, rp7, rp8;
	uint64_t start, end;
	unsigned long long rpl1t, rp1t, rp2t, rp3t, rp4t, rp5t, rp6t, rp7t, rp8t;
	unsigned long long startt, endt, resultt;
	printf("this is thread timing attack...\n");
	set_cpu(1);

	/* init the hugepages(2M)/sets(2M) */
	char *p1 = init_hugetlb_seg_1page(0);
	char *p2 = init_hugetlb_seg_ano_page(1);
	char *p3 = init_hugetlb_seg_3rd_page(2);
	char *p4 = init_hugetlb_seg_4th_page(3);
	char *p5 = init_hugetlb_seg_5th_page(4);
	char *p6 = init_hugetlb_seg_6th_page(5);
	char *p7 = init_hugetlb_seg_7th_page(6);
	char *p8 = init_hugetlb_seg_8th_page(7);

	int i;
	/* warmup */
	for(i = 0; i < 10; i++){
		startt = rdtsc_start();
		endt = rdtsc_end();
		start = ticks;
		end = ticks;
		probe_set(p1);
		probe_set_tsc(p1);
		probe_line(p1);
		probe_line_tsc(p1);
	}
#if 0
	read_set(p1);
	read_set(p2);
	read_set(p3);
	read_set(p4);
	/* read clock */
	start = ticks;
		tsc_start = rdtsc_start();

			read_set(p5);
	
	/* read clock */
		tsc_end = rdtsc_end();
	end = ticks;
#endif

/* attack self */

	/* probe a set using lff's way */
	/* malloc pool */
	uint64_t *pool = (uint64_t *)malloc(L3_ways);
	/* leverage p1 to construct the candidate addresses */
	pool = build_eviction_array(p1, pool, L3_ways);
	/* measure this */
	resultt = traverse_eviction_array(pool, L3_ways);
	printf("probe 1 set using lff's way: %llu\n", resultt);

	/* use old way */
	rpl1 = probe_line(p1);

	rp1 = probe_set(p1);
	rp2 = probe_set(p2);
	rp3 = probe_set(p3);
	rp4 = probe_set(p4);
	rp5 = probe_set(p5);
	rp6 = probe_set(p6);
	rp7 = probe_set(p7);
	rp8 = probe_set(p8);

	rp1t = probe_set_tsc(p1);
	rp2t = probe_set_tsc(p2);
	rp3t = probe_set_tsc(p3);
	rp4t = probe_set_tsc(p4);
	rp5t = probe_set_tsc(p5);
	rp6t = probe_set_tsc(p6);
	rp7t = probe_set_tsc(p7);
	rp8t = probe_set_tsc(p8);
	
	rpl1t = probe_line_tsc(p1);

	/* output the result */
	printf("probe 1 line in TSC:\t%llu\nprobe 1 line in ours:\t%llu\n", rpl1t, (unsigned long long)rpl1);

	printf("probe 8 sets in TSC:\t\n%llu ,%llu, %llu, %llu\n%llu, %llu, %llu, %llu\n", rp1t, rp2t, rp3t, rp4t, rp5t, rp6t, rp7t, rp8t);
	printf("probe 8 sets in ours:\t\n%llu ,%llu, %llu, %llu\n%llu, %llu, %llu, %llu\n", (unsigned long long)rp1, (unsigned long long)rp2, (unsigned long long)rp3, (unsigned long long)rp4, (unsigned long long)rp5, (unsigned long long)rp6, (unsigned long long)rp7, (unsigned long long)rp8);
/* end of attack */

	/* deinit the hugepages */
	shmctl(shmid1, IPC_RMID, NULL);
	shmctl(shmid2, IPC_RMID, NULL);
	shmctl(shmid3, IPC_RMID, NULL);
	shmctl(shmid4, IPC_RMID, NULL);
	shmctl(shmid5, IPC_RMID, NULL);
	shmctl(shmid6, IPC_RMID, NULL);
	shmctl(shmid7, IPC_RMID, NULL);
	shmctl(shmid8, IPC_RMID, NULL);

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
	else printf("attack thread created\n");

	sleep(1);

	/* finish the attack thread */
	pthread_join(thread[1], NULL);

	pthread_join(thread[0], NULL);

	return 0;
}
