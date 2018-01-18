/* this time I am trying to use inline asm
 * instead of simple timestamp++.
 * Usage: still -lpthread
 */

#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>
#include <sched.h>

#include <pthread.h>

volatile uint32_t counter4n = 0;
volatile uint32_t counter4u = 0;
volatile uint32_t counter4s = 0;

#define NINCR(n) non_atomic_incr((n))
#define UINCR(n) ump_atomic_incr((n))
#define SINCR(n) smp_atomic_incr((n))

void non_atomic_incr(volatile uint32_t *n)
{
	asm volatile (	"mov %0, %%eax\n\t"
			"add $1, %%eax\n\t"
			"mov %%eax, %0"
			: "+m"(*n)
			:
			: "eax", "memory", "cc");
}

void ump_atomic_incr(volatile uint32_t *n)
{
	asm volatile (	"incl %0\n\t"
			: "+m"(*n)
			:
			: "memory");
}

void smp_atomic_incr(volatile uint32_t *n)
{
	asm volatile (	"lock; incl %0\n\t"
			: "+m"(*n)
			:
			: "memory");
}

void *thread()
{
#ifdef BINDING
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	/* binding the thread on CPU 0 */
	CPU_SET(0, &cpuset);
	sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
#endif
	int i = 0;
	while(i++ < 1000000) {
		/* using clock. I also could use other functions */
		NINCR(&counter4n);
		UINCR(&counter4u);
		SINCR(&counter4s);
	}
}

int main()
{
	pthread_t t1, t2;
	pthread_create(&t1, NULL, thread, NULL);
	pthread_create(&t2, NULL, thread, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	fprintf(stderr, "%u\n", counter4n);
	fprintf(stderr, "%u\n", counter4u);
	fprintf(stderr, "%u\n", counter4s);

	//test the new counter thread


	return 0;
}
