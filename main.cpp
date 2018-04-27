#include <iostream>
#include <pthread.h>
#include <errno.h>
#include <ringqueue.cpp>
#include <unistd.h>
#include <semaphore.h>
#define PRODUCER 4
#define CONSUMER 4
sem_t sem_in,sem_out;
pthread_mutex_t mutex_in,mutex_out;
pthread_t threads[PRODUCER + CONSUMER];
void* HandleProducer(void* arg){
    while(true){

    }
}
void* HandleConsumer(void* arg){
    while(true){

    }
}
int main(void){
    RingQueue<int>* q = new RingQueue<int>();
    pthread_mutex_t in_mutex,out_mutex;
    uint32_t compacity = q->GetCompacity();
    sem_init(&sem_in, 0, compacity);
    sem_init(&sem_out, 0, 0);
    for(int i = 0; i < PRODUCER; i++){
        pthread_create(&threads[i], NULL, HandleProducer, &i);
    }
    for(int i = PRODUCER; i < CONSUMER + PRODUCER; i++){
        pthread_create(&threads[i], NULL, HandleConsumer, &i);
    }
    for(int i = 0; i < CONSUMER+PRODUCER; i++){
        pthread_join(threads[i],NULL);
    }
    pthread_mutex_destroy(&mutex_in);
    pthread_mutex_destroy(&mutex_out);
    sem_destroy(&sem_in);
    sem_destroy(&sem_out);
}
