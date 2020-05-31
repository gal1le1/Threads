#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long counter;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// First version with the problem
void * calculate(void *args){
    
    for (int i = 0; i < 1000000; i++)
    {
        counter++;
    }

    pthread_exit(NULL);
}

// Second version with solution

void * calculate2(void *args){
    
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&lock); //takes the lock so no any other threads access it
        counter++;
        pthread_mutex_unlock(&lock); // releases the lock so other threads can access it
    }

    pthread_exit(NULL);
}


int main(int argc, char const *argv[])
{
    pthread_t threads[4];

    for (int i = 0; i < 4; i++)
    {
        // pthread_create(&threads[i], NULL, &calculate, NULL);    /*Run with this line to see the problem*/
         pthread_create(&threads[i], NULL, &calculate2, NULL);    /*Run with this line to see the solution*/

    }

    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);    
    }

    printf("Global counter is %ld\n", counter);
    
    return 0;
}
