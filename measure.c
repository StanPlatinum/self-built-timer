#include <stdio.h>
#include <stdlib.h>

#include "timing.h"
#include "rdtsc.h"
#include "clock.h"

int main()
{
	volatile uint32_t counter = 0;
	unsigned long long start, end;
	float result = 0;

	//warmup UMP_INCR
	twtimes(UINCR(&counter));
/* begin to time */
	start = rdtsc_start();
	twtimes(UINCR(&counter));
	end = rdtsc_end();
	printf("20 times cost:%lld\n", end - start);
	printf("counter:%d\n", counter);
	result = end - start;
	printf("percost:%f\n", result/20);
//rdtsc measuring
	start = rdtsc_start();
	rdtsc_start();
	rdtsc_end();
	end = rdtsc_end();
	printf("rdtsc couple cost:%lld\n", end - start);

	return 0;
}
