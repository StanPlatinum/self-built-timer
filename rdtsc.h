#ifndef RDTSC_H

#include <stdint.h>

typedef uint64_t clk_t;

struct tscclock {
	clk_t ticks, r0, r1;
};

#define START_TSC(cl) __asm__ __volatile__ ( \
	"cpuid \n" \
	"rdtsc \n" \
	"shlq $32, %%rdx \n" \
	"orq %%rdx, %%rax \n" \
	: "=a"(cl.r0) \
	: \
	: "%rbx", "%rcx", "%rdx")

#define END_TSC(cl) __asm__ __volatile__ ( \
	"rdtscp \n" \
	"shlq $32, %%rdx \n" \
	"orq %%rdx, %%rax \n" \
	"movq %%rax, %0 \n" \
	"cpuid" \
	: "=g"(cl.r1) \
	: \
	: "%rax", "%rbx", "%rcx", "%rdx"); \
	cl.ticks = cl.r1 - cl.r0;

clk_t tsc_overhead(void);

unsigned long long rdtsc_start(void);

unsigned long long rdtsc_end(void);

#endif
