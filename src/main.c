#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ticktock.h"



int main(int argc, char **argv){

	tick();
	tock();
	tick();
	tock();

	// tick();
	// tick();
	// tick();
	// tick();
	// tick();
	// tick();

	for(int n=0; n<6; n++){
		tick();
		printf("ticks: %llu\n", tock());
	}



	return 0;
}
