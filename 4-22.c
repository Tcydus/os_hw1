#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#define THREAD_LEN 3
int min_value = 0,max_value = 0;
float avg_value = 0.0;

typedef struct{
	int *arr;
	size_t len;
}args;

void *findMin(void *param);
void *findMax(void *param);
void *findAvg(void *param);
void atoiArray(char *src[],int *dst,int size);

int main(int argc, char *argv[])
{
	//Check if didn't input some argument
	if(argc <= 1){
		fprintf(stderr, "[ERROR] : Please input some argument!!\n");
		return -1;
	}

	//create thread argument
	args targ;
	targ.len = argc - 1;
	targ.arr = (int*)malloc(targ.len*sizeof(int));
	
	//assign systems argument to thread argument  
	atoiArray(argv,targ.arr,argc);	
	
	// create thread to run function
	pthread_t *tid[3];
	pthread_create(tid[0],NULL,findAvg,(void *)&targ);
	pthread_create(tid[1],NULL,findMin,(void *)&targ);
	pthread_create(tid[2],NULL,findMax,(void *)&targ);
	pthread_join(*tid[0],NULL);
	pthread_join(*tid[1],NULL);
	pthread_join(*tid[2],NULL);

	// free memory of array	
	free(targ.arr);

	// show value
	printf("The average value is %.3f\n",avg_value);
	printf("The minimum value is %d\n",min_value);
	printf("The maximum value is %d\n",max_value);		
}

void *findAvg(void *param) {
	args *targ = (args*)param;
	int sum = 0;
	for(int i = 0; i < targ->len; ++i){
		sum += targ->arr[i];	
	}
	avg_value = sum/targ->len;
	pthread_exit(0);
}

void *findMin(void *param) {
	args *targ = (args*)param;
	min_value = targ->arr[0];
	for(int i = 1; i < targ->len; ++i){
		if(targ->arr[i] < min_value){
			min_value = targ->arr[i];
		} 	
	}
	pthread_exit(0);
}

void *findMax(void *param) {
	args *targ = (args*)param;
	max_value = targ->arr[0];
	for(int i = 1; i < targ->len; ++i){
		if(targ->arr[i] > max_value){
			max_value = targ->arr[i];
		} 	
	}
	pthread_exit(0);
}

void atoiArray(char *src[], int *dst, int size){
	for(int i = 1; i < size; ++i){
		dst[i-1] = atoi(src[i]);
	}
}

