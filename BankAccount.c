#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
void* deposit(void* data);
struct account
{
	char name[20];
	int balance;
};
struct account yac={"Gokhan",100};//Init bank money
pthread_mutex_t lock; //Define lock
int main(int argc, char const *argv[])
{
	int i,n;
	n=6;
	pthread_t tid[n];
	int deposit_amount[n];
	deposit_amount[0]=1000;
	deposit_amount[1]=2500;
	deposit_amount[2]=2000;
	deposit_amount[3]=1500;
	deposit_amount[4]=4000;
	deposit_amount[5]=7500;

	for (int i = 0; i < n; ++i)
		pthread_create(&tid[i],NULL,&deposit,(void*)&deposit_amount[i]);

	for (int i = 0; i < n; ++i)
	pthread_join(tid[i],NULL);

	printf("---------RESULT\n Account Owner:%s,balance%d",yac.name,yac.balance);
	return 0;
}
int ReturnValue(int temp1)
{
	int temp2;
	for(temp2=0;temp2<1000000;temp2++);//Simulate for timing 
	return temp1;
}
void* deposit(void* data)
{
	int amount=*((int*)data);//Type Casting to int
	pthread_mutex_lock(&lock);//Critical Section Start
	
	printf("Account Owner:%s,Current Balance:%d \n",yac.name,yac.balance);
	printf("deposit işlemi gerçekleştiriliyor....%d\n",amount);

	//Read balance and update
	yac.balance +=ReturnValue(amount);
	printf("Account Owner:%s,Updated Balance:%d \n\n",yac.name,yac.balance );

	pthread_mutex_unlock(&lock);//Critical Section End
	return(void*)NULL;
}
