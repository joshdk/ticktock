#include "ticktock.h"




#if defined(__i386__)
	static __inline__ unsigned long long rdtsc(void){
		unsigned long long int x;
		__asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
		return x;
	}

#elif defined(__x86_64__)
	static __inline__ unsigned long long rdtsc(void){
		unsigned hi, lo;
		__asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
		return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
	}

#elif defined(__powerpc__)
	static __inline__ unsigned long long rdtsc(void){
		unsigned long long int result = 0;
		unsigned long int upper, lower,tmp;
		__asm__ volatile(
				"0:             \n"
				"\tmftbu  %0    \n"
				"\tmftb   %1    \n"
				"\tmftbu  %2    \n"
				"\tcmpw   %2,%0 \n"
				"\tbne    0b    \n"
				: "=r"(upper),"=r"(lower),"=r"(tmp)
		);
		result = upper;
		result = result << 32;
		result = result | lower;
		return result;
	}

#endif


unsigned long long int cycles(void){
	return rdtsc();
}




static unsigned long long int *timers = NULL;
static unsigned int timers_size = 0;
static unsigned int timers_length = 0;


static int resize_timers(void){
	unsigned long long int *tmp = NULL;
	unsigned int timers_size_new = 0;
	if(timers == NULL){
		timers_size_new = 1;
	}else{
		timers_size_new = timers_size * 2;
	}
	if((tmp = realloc(timers, sizeof(*timers) * timers_size_new)) == NULL){
		return 1;
	}
	timers_size = timers_size_new;
	timers = tmp;
	return 0;
}


void tick(void){
	if(timers_length == timers_size){
		resize_timers();
	}
	if(timers_length == timers_size){
		fputs("ticktock: Failed to allocate more timers.", stderr);
		exit(1);
	}
	unsigned long long int ticks = cycles();
	timers[timers_length] = ticks;
	timers_length += 1;
}


unsigned long long int tock(void){
	unsigned long long int ticks = cycles();
	if(timers_length == 0){
		return 0;
	}
	timers_length -= 1;
	return ticks - timers[timers_length];
}
