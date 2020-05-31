# Threads

## thread.c
This program made of n new threads. Each of these threads increments a thread-specific
counter and stops at value 10 while printing a message. At each increment, the thread waits an arbitrary duration and prints the counter value prefixes by the thread number. The program terminates when the n
threads are over, and prints the number of the thread that finished last.

## mutex.c
This program made of 4 new threads. Each thread increments a million times a global
variable counter of type long int. Once the threads have completed their job, prints the value of
the counter.
