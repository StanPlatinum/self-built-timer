#include <stdint.h>
#include "spec.h"
#include "rdtsc.h"

/* to access a cache set in one slice */
void read_set(char *p)
{
	int i;
	char tmp[64];	/* defined here for accessing a memory line */
	for (i = 0; i < L3_ways; i++) {
		tmp[0] = p[0];
		tmp[1] = p[1];
		tmp[3] = p[3];
		tmp[3] = p[7];
		tmp[3] = p[15];
		tmp[3] = p[31];
		p = p + (L3_SLICE_number_of_sets)*64;
	}
}

/* read specific line and time using rdtsc */
unsigned long long probe_line_tsc(char *p)
{
	unsigned long long start, end , result = 0;
	char tmp[64];	/* defined here for accessing a memory line */
	start = rdtsc_start();
	tmp[0] = p[0];
	tmp[1] = p[1];
	tmp[3] = p[3];
	tmp[3] = p[7];
	tmp[3] = p[15];
	tmp[3] = p[31];
	end = rdtsc_end();
	result = end - start;
	return result;
}

/* read set and time using rdtsc */
unsigned long long probe_set_tsc(char *p)
{
	unsigned long long start, end , result, rv = 0;
	int i;
	char tmp[64];	/* defined here for accessing a memory line */
	for (i = 0; i < L3_ways; i++) {
		start = rdtsc_start();
		tmp[0] = p[0];
		tmp[1] = p[1];
		tmp[3] = p[3];
		tmp[3] = p[7];
		tmp[3] = p[15];
		tmp[3] = p[31];
		end = rdtsc_end();
		p = p + (L3_SLICE_number_of_sets)*64;
		result = end - start;
		rv += result;
	}
	return rv;
}

/*
 * p is the first address of the target set, namely pool[0].
 * arr is the first address of array that helps to build a eviction set. User 
 * should allocate arr[] first, then use this function!
 */
uint64_t* build_eviction_array(char *p, uint64_t *arr, int len)
{
	/* build the array[] for function::make_eviction_list */

	/* initialization */
	int i, j;
	for (i = 0; i < len; ++i) {
		arr[i] = (uint64_t)p;
		p += (L3_SLICE_number_of_sets)*64; 
	}
	/* make eviction list */
	for (j = 0; j < len-1; ++j) {
		/* actually put addresses as content into the cells of eviction set */
		*((uint64_t *)arr[j]) = arr[j+1];
	}

	/* something wrong with next line */
	*((uint64_t *)arr[len-1]) = 0;

	/* but how to send out the arr[]? */
	return arr;
}

/* a = arr[0] */
unsigned long long traverse_eviction_array(uint64_t *a, int len)
{
	int i;
	unsigned long long start, end, result = 0;
	start = rdtsc_start();
	//for (i = 0; i < len; i++)	a = *(uint64_t *)a;
	/* this is brilliant, created by lailai */
	while ( ( a = *(uint64_t *)a ) );
	end = rdtsc_start();
	result = end - start;
	return result;
}
