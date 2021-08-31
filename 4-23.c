#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_THREAD 4

typedef struct{
	uint64_t *arr;
	size_t len;
	struct range{
		uint64_t min;
		uint64_t max;
	}range;
	uint64_t value;
}args;

//create prime number list
uint64_t prime_element[1000] = {2};
args prime_arr = {prime_element,1};

void *isPrime(void *param);
void updateTargList();

int main(int argc, char *argv[])
{
	// Check if input more or less than 1
	if(argc != 2){
		fprintf(stderr, "[ERROR] : Please input 1 argument!!\n");
		return 1;
	}

	// casting argument to integer
	uint64_t max_value = atoi(argv[1]);

	// create array of thread argument
	args targ[MAX_THREAD];
	
	// create array of thread id
	pthread_t *tid;
	tid = (pthread_t *)malloc(MAX_THREAD * sizeof(pthread_t));
	
	//seperate range of division by reference prime array and add to thread argument
	updateTargList(&targ);

	printf("Prime Number is %lu",prime_arr.arr[0]);

	for(int i = 3; i <= max_value ; ++i){
		
		//dynamic create thread when amount of division less than maximum thread
		uint8_t running =  prime_arr.len < MAX_THREAD ? prime_arr.len : MAX_THREAD; 

		// call thread to calculate prime number 
		for(uint8_t j = 0; j < running; ++j){ 
			targ[j].value = i;
			pthread_create(&tid[j],NULL,(void *)&isPrime,(void *)&targ[j]);
		}
		
		// get result from every thread to identify prime number
		bool isPrime = 1;
		for(uint8_t j = 0; j < running; ++j){
			void *result;	
			pthread_join(tid[j],&result);
			isPrime &= (bool)(bool *)result;
		}

		// if this number is prime show result ,add value to array and update thread argument 
		if(isPrime == 1){
			printf(",%d", i);
			prime_arr.len++;
			prime_arr.arr[prime_arr.len-1] = i;
			updateTargList(&targ);
		}
	}
	printf("\nThis is prime number from 2 - %lu\n",max_value);
	
	//free memory of thread id
	free(tid);
}

void *isPrime(void *param) {
	/*
		check that current value is prime by division with prime number
		if curent value can't divisible by every prime number. That is prime number
	*/

	args *targ = (args*)param;
	bool isPrime;
	for(int i = targ->range.min; i < targ->range.max; ++i){
		if(targ->value % targ->arr[i] == 0){
			isPrime = false;
			break;
		}
		else if(i == (targ->range.max - 1)){
			isPrime = true;
		}
	}

	pthread_exit((void*) isPrime);
}

void updateTargList(args *targ){
	/*
		seperate range of division by reference prime array 
		and add to thread argument
	*/

	uint64_t data_range = prime_arr.len / MAX_THREAD ;
	uint64_t remainder_data = prime_arr.len % MAX_THREAD ;

	for(int k = 0; k < MAX_THREAD; ++k){
		uint64_t min = k != 0 ? targ[k-1].range.max : 0;
		
		if( k == 0 &&  remainder_data != 0 ) ++data_range;
		if( k != 0 && k == remainder_data) --data_range;

		targ[k].arr = prime_arr.arr;
		targ[k].len = data_range;
		targ[k].range.min = min;
		targ[k].range.max = targ[k].range.min + targ[k].len;
	}

}
