#include "rdtsc.h"

clk_t tsc_overhead(void)
{
	struct tscclock cl;
	int i;
	clk_t sum = 0;
	//warmup
	for(i = 0; i < 10; ++i)
	{
		START_TSC(cl);
		END_TSC(cl);
		sum += cl.ticks;
	}
	sum = 0;
	for(i = 0; i <1000; ++i)
	{
		START_TSC(cl);
		END_TSC(cl);
		if(cl.ticks < 100) {
			sum += cl.ticks;
			i--;
		}
	}
	return sum/1000;
}

unsigned long long rdtsc_start(void)
{
	unsigned long long lo, hi;
	asm volatile (	"mfence\n"
			"rdtsc\n"
			: "=a"(lo), "=d"(hi)
			);
	return (unsigned long long) ( (hi<<32) | (lo) );
}

unsigned long long rdtsc_end(void)
{
	unsigned long long lo, hi;
	asm volatile (	"rdtsc\n"
			"mfence\n"
			: "=a"(lo), "=d"(hi)
			);
	return (unsigned long long) ( (hi<<32) | (lo) );
}

