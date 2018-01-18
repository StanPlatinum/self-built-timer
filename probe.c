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

uint64_t* build_eviction_array(char *p, int len)
{
	/* build the array[] for function::make_eviction_list */
	uint64_t arr[len];
	/* initialization */
	int i;
	for (i = 0; i < len-1; ++i) {
		arr[i] = (uint64_t)p;
		p += (L3_SLICE_number_of_sets)*64; 
	}
}

void make_eviction_list(uint64_t *arr, int len)
{
	int i;
	for (i = 0; i < len-1; ++i) {
		/* actually put addresses as content into the cells of eviction set */
		*((uint64_t *)arr[i]) = arr[i+1];
	}
	*((uint64_t *)arr[len-1]) = 0;
}
