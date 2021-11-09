#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void *philosopher(void *);
void think(int);
void pick_up(int);
void eat(int);
void put_down(int);
void down(int* s);
void up(int* s);

int chopsticks[5];
pthread_t philosophers[5];
pthread_attr_t attributes[5];

int main() {
	int i;
	for (i = 0; i < 5; ++i) {
		chopsticks[i] = 1;
	}

	for (i = 0; i < 5; ++i) {
		pthread_attr_init(&attributes[i]);
	}
	
	for (i = 0; i < 5; ++i) {
		pthread_create(&philosophers[i], &attributes[i], philosopher, (void *)(i));
	}

	for (i = 0; i < 5; ++i) {
		pthread_join(philosophers[i], NULL);
	}
	return 0;
}

void *philosopher(void *philosopherNumber) {
	while (1) {
		think(philosopherNumber);
		pick_up(philosopherNumber);
		eat(philosopherNumber);
		put_down(philosopherNumber);
	}
}

void think(int philosopherNumber) { 
	printf("Philosopher %d is thinking !!\n", philosopherNumber  + 1);
	sleep(1); 
}

void pick_up(int philosopherNumber) {
	int right = (philosopherNumber + 1) % 5;
	int left = (philosopherNumber + 4) % 5;
	if (philosopherNumber % 2 == 1) {
		printf("Philosopher %d is waiting to eat using chopsticks %d , %d\n", philosopherNumber + 1, left,right);
		down(&chopsticks[right]);
		down(&chopsticks[left]);
		printf("Philosopher %d is eating using chopsticks %d , %d\n", philosopherNumber  + 1,left,right);
	}
	else {
		printf("Philosopher %d is waiting to eat using chopsticks %d , %d\n", philosopherNumber + 1, left , right);
		down(&chopsticks[left]);
		down(&chopsticks[right]);
		printf("Philosopher %d start to eat using chopsticks %d , %d\n", philosopherNumber + 1, left , right);
	}
}

void eat(int philosopherNumber) {
	printf("Philosopher %d is eating\n", philosopherNumber + 1);
	sleep(1);
}

void put_down(int philosopherNumber) {
	printf("Philosopher %d finished eating !!\n", philosopherNumber  + 1);
	if (philosopherNumber % 2 == 0) {
		up(&chopsticks[(philosopherNumber + 1) % 5]);
		up(&chopsticks[(philosopherNumber + 4) % 5]);
	}
	else{
		up(&chopsticks[(philosopherNumber + 4) % 5]);
		up(&chopsticks[(philosopherNumber + 1) % 5]);
	}
}
void down(int* s){
	while(*s <= 0);
	*s = *s - 1;
}
void up(int* s){
	*s = *s + 1;
}
