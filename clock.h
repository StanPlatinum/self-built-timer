#define NINCR(n) non_atomic_incr((n))
#define UINCR(n) ump_atomic_incr((n))
#define SINCR(n) smp_atomic_incr((n))

#define CLOCK_MAX 1ULL<<63

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

void count_loop_asm(uint64_t *counter)
{
	asm volatile (	"movq %0, %%rcx \n\t"
			"1: inc %%rax \n\t"
			"movq %%rax, (%%rcx) \n\t"
			"jmp 1b"
			:
			: "m"(counter)
		);	
}

void count_loop_asm_slow(uint64_t *counter)
{
	asm volatile (	"movq %0, %%rcx \n\t"
			"1: incq (%%rcx) \n\t"
			"jmp 1b"
			:
			: "m"(counter)
		);	
}
