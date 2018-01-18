/* short test program to test the CPU sched_setaffinity 
 * and how I use it into a thread programming
 * Compile: gcc -lm
 */

#include <stdio.h>
#include <math.h>
#include <sched.h>

double waste_time(long n)
{
	double res = 0;
	long i = 0;
	while(i < n*1000000) {
		i++;
		res += sqrt(i);
	}
	return res;
}

int main(int argc, char **argv)
{
	unsigned long mask = 1;	/* processor 0 */
	if(sched_setaffinity(0, sizeof(mask), &mask) < 0) {
		perror("sched_setaffinity");
	}

	printf("result: %f\n", waste_time(2000));

	mask = 2;	/* switch to processor 1 */
	if(sched_setaffinity(0, sizeof(mask), &mask) < 0) {
		perror("sched_setaffinity");
	}

	printf("result: %f\n", waste_time(2000));
}
