#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// global value to hold the number of last thread
int last_thread;

// function that is passed to each thread
void * increments(void *args){
    time_t t;
    srand((unsigned) time(&t));

    int counter = 0;
    int *thread_numb = args; //recevies the thread number from main thread
    struct timespec tim1, tim2;
    tim1.tv_sec = 0;
    
    for (int i = 0; i < 10; i++)
    {
        tim1.tv_nsec = rand()%1000000000; //gives a number between 1 and 999999999 (in nanoseconds)

        // waits for arbitrary nanoseconds (less than 1 second)
        if(nanosleep(&tim1 , &tim2) < 0 )
        {
            perror("nanosleep");
            exit(1);
        }      
        printf("Thread number : %d,  Counter value : %d\n", *thread_numb, i+1);
    }

    last_thread = *thread_numb; //last_thread is global value so the last thread that is writing to last_thread will be the last one
    pthread_exit(NULL);
}



int main(int argc, char const *argv[])
{
    int n;
    printf("Enter number of threads: ");
    scanf("%d", &n);

    pthread_t threads[n];
    int *thread_number;

    for (int i = 0; i < n; i++)
    {
        thread_number = malloc(sizeof(thread_number));
        *thread_number = i+1;

        // thread is created
        if (pthread_create(&threads[i], NULL, &increments, thread_number) != 0)
        {
            perror("pthread_create");
            exit(1);
        }
    }

    for (int i = 0; i < n; i++)
    {
        // main thread waits for each threads termination
        if (pthread_join(threads[i], NULL) == -1)
        {
            perror("pthread_join");
            exit(1);
        }
    }

    // Prints the number of the thread that finished last 
    printf("Last thread is %d\n", last_thread);

    return 0;
}
