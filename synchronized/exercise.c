#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_INPUT 7
#define MIN 99999
#define MAX -99999


struct msg{
	int* arr;
	pthread_t thread_id;
};

void average(struct msg* arg){
	pthread_join(arg->thread_id,NULL);
	double sum;
	int i;
	for(i=0;i<NUM_INPUT;++i){
		sum+=arg->arr[i];	
	}
	printf("average:%.2f\n",sum/NUM_INPUT);
};

void max(struct msg* arg){
	pthread_join(arg->thread_id,NULL);
	int max=MAX, i;
	for(i=0;i<NUM_INPUT;++i){
		if(max<arg->arr[i]) max = arg->arr[i];
	}
	printf("max:%d\n",max);
};
void min(struct msg* arg){
	pthread_join(arg->thread_id,NULL);
	int min=MIN,i;
	for(i=0;i<NUM_INPUT;++i){
		if(min>arg->arr[i]) min = arg->arr[i];
	}
	printf("min:%d\n",min);

};
int main(){
	int i;
	int arr[NUM_INPUT];
	struct msg m;
	for(i=0;i<NUM_INPUT;++i){
		scanf("%d",&arr[i]);
	}
	m.arr=arr;
	pthread_t threads[3];
	m.thread_id=pthread_self();
	pthread_create(&threads[0],NULL,&min,&m);
	m.thread_id=threads[0];
	pthread_create(&threads[1],NULL,&max,&m);
	m.thread_id=threads[1];
	pthread_create(&threads[2],NULL,&average,&m);
	return 0;
}

