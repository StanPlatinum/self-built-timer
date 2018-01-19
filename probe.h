void read_set(char *p);

/* read specific line and time using rdtsc */
unsigned long long probe_line_tsc(char *p);

/* read set and time using rdtsc */
unsigned long long probe_set_tsc(char *p);

uint64_t* build_eviction_array(char *p, uint64_t *arr, int len);

unsigned long long traverse_eviction_array(uint64_t *a, int len);
