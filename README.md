GTThreads
=========
This is a preemptive user-level thread package with an API similar to the existing C Pthreads library.

The GTThreads API consists of the following functions:


      void gtthread_init(long period);
      int  gtthread_create(gtthread_t *thread,
                           void *(*start_routine)(void *),
                           void *arg);
      int  gtthread_join(gtthread_t thread, void **status);
      void gtthread_exit(void *retval);
      int  gtthread_yield(void);
      int  gtthread_equal(gtthread_t t1, gtthread_t t2);
      int  gtthread_cancel(gtthread_t thread);
      gtthread_t gtthread_self(void);
      
It also contains implementation of a mutex synchronization primitive to enable safe concurrent manipulation of shared data. The API for the mutex primitive is as follows:
       
      int  gtthread_mutex_init(gtthread_mutex_t *mutex);
      int  gtthread_mutex_lock(gtthread_mutex_t *mutex);
      int  gtthread_mutex_unlock(gtthread_mutex_t *mutex);

The gtthread_init(period) function is required to be called from the main thread before any other GTThreads functions are called. It allows the caller to specify the scheduling period and performs other initializations(In this manner it does not behave like pthread_init). Adiditonally, it implements a pre-emptive Round Robin scheduler instead of Pthread's priority based scheduler using signals.

I have also implemented the Dining Philosopher's problem to demonstrate the use of this library. Note that deadlock is avoided in this implementation od Dining Philosophers problem by never waiting for a fork while holding a fork (locked). The procedure to do this is to do block while waiting to get first fork, and a nonblocking acquire of second fork. If failed to get second fork, release first fork, swap which fork is first and which is second and retry until getting both. The swapping is to avoid live lock, where each philosopher keeps retrying but never makes any progress.


COMPILING AND RUNNING THE CODE:

The code is orgranized into three header files, one for two linked lists needed by the scheduler(cll.h and ell.h) and one the gtthread header file which uses the linked list header files. The dining philosopher's source code is dp_gt.c. 
Compile the program pgm.c which uses the Gtthreads library as follows:
	
	First, compile library itself,
	
		make
	
	Then,compile the program,
	
		gcc -Wall -pedantic -o pgm pgm.c gtthread.a
	
	and then run it as,
	
		./pgm	
		
	To execute dining philosophers’ code,
	
		./diningPhilosopher

