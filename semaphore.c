#include <stdio.h>

#define N 5

int buffer[N];
int in = 0;
int out = 0;

int empty = N;
int full = 0;
int mutex = 1;

void wait(int *s){
    while(*s <= 0);   // busy waiting
    (*s)--;
}

void signal(int *s){
    (*s)++;
}

void producer(int item){
    wait(&empty);      // wait for empty slot
    wait(&mutex);      // enter critical section

    buffer[in] = item;
    printf("Produced: %d\n", item);
    in = (in + 1) % N;

    signal(&mutex);    // leave critical section
    signal(&full);     // increase full slots
}

void consumer(){
    int item;

    wait(&full);       // wait for available item
    wait(&mutex);      // enter critical section

    item = buffer[out];
    printf("Consumed: %d\n", item);
    out = (out + 1) % N;

    signal(&mutex);    // leave critical section
    signal(&empty);    // increase empty slots
}

int main(){
    producer(10);
    producer(20);
    consumer();
    consumer();

    return 0;
}
