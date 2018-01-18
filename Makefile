TIMING = rdtsc
PROBE = probe

METRIC = measure
AFFINITY = affinity-test
THREAD = thread-test
CLOCK = clock-test

ATTACK = thread-attack
TEST0 = thread-attack-inDom0

all:
	gcc -c $(TIMING).c
	gcc -S $(CLOCK).c -o $(CLOCK).S
	gcc -c $(METRIC).c
	gcc -S $(METRIC).c
	gcc -o $(METRIC) $(TIMING).o $(METRIC).o 
	gcc -c $(PROBE).c
	gcc $(AFFINITY).c -o $(AFFINITY) -lm
	gcc -c $(THREAD).c
	gcc -o $(THREAD) $(TIMING).o $(THREAD).o -lpthread
	gcc $(CLOCK).c -o $(CLOCK) -lpthread
	gcc -c $(ATTACK).c
	gcc -o $(ATTACK) $(TIMING).o $(ATTACK).o -lpthread
	gcc -c $(TEST0).c 
	gcc -o $(TEST0) $(TIMING).o $(PROBE).o $(TEST0).o -lpthread
clean:
	rm -f *.S *.o $(TIMING) $(AFFINITY) $(THREAD) $(CLOCK) $(METRIC) $(PROBE) $(ATTACK) $(TEST0)
