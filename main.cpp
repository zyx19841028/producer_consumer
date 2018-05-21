#include "ringqueue.cpp"
#include <iostream>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#define PRODUCER 4
#define CONSUMER 4
sem_t sem_in,sem_out;
pthread_mutex_t mutex_in,mutex_out;
pthread_t threads[PRODUCER + CONSUMER];
RingQueue<int> rq;
int productID;
void* HandleProducer(void* arg){
    int n = (int)arg;
    while(true){
        sem_wait(&sem_in);
        pthread_mutex_lock(&mutex_in);
        if(rq.IsFull()){
            printf("queue is full\n"); 
        }else{
            int temp = productID++;
            printf("thread[%d] is producing %d\n",n, temp);
            rq.EnQueue(temp);
        }
        pthread_mutex_unlock(&mutex_in);
        sem_post(&sem_out);
        sleep(1);
    }
    return NULL;
}
void* HandleConsumer(void* arg){
    int n = (int)arg;
    int* pq; 
    while(true){
        sem_wait(&sem_out);
        pthread_mutex_lock(&mutex_out);
        if(rq.IsEmpty()){
            printf("queue is empty\n"); 
        }else{
            pq = rq.DeQueue();
            printf("thread[%d] is consuming %d\n",n, *pq);
        }
        pthread_mutex_unlock(&mutex_out);
        sem_post(&sem_in);
        sleep(1);
    }
    return NULL;
}
int main(void){
    RingQueue<int>* q = new RingQueue<int>();
    sem_init(&sem_in, 0, q->GetCompacity());
    sem_init(&sem_out, 0, 0);
    for(int i = 0; i < PRODUCER; i++){
        pthread_create(&threads[i], NULL, HandleProducer, (void*)i);
    }
    for(int i = PRODUCER; i < CONSUMER + PRODUCER; i++){
        pthread_create(&threads[i], NULL, HandleConsumer, (void*)i);
    }
    for(int i = 0; i < CONSUMER+PRODUCER; i++){
        pthread_join(threads[i],NULL);
    }
    pthread_mutex_destroy(&mutex_in);
    pthread_mutex_destroy(&mutex_out);
    sem_destroy(&sem_in);
    sem_destroy(&sem_out);
}
