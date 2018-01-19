#ifndef CACHE_SPEC

#define CACHE_SPEC

#define L3_ways 16
#define L3_number_of_sets 8192
#define L3_SLICE_number_of_sets 2048
#define L3_TOTAL_NUM L3_number_of_sets*L3_ways*64
#define L3_SLICE_NUM L3_SLICE_number_of_sets*L3_ways*64

#endif
