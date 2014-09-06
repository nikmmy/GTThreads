#include "gtthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
const char *smartGuys[] = { "Buddha", "Kabir", "Krishna", "Birbal", "Shivaji" };
 
typedef struct infoPhil {
    gtthread_mutex_t *lft_chopstick, *rgt_chopstick;
    const char *name;
    gtthread_t thread;
} Philosopher;
 
int keep_running = 1;
 

void *PhilospherFunc(void *p) {
    Philosopher *phil = (Philosopher*)p;
    int failed;
    int chances_left;
    gtthread_mutex_t *lft_chopstick, *rgt_chopstick, *tmp_chopstick;
    static int i;
    
    while(keep_running) {
        printf("\n%s is now thinking.\n", phil->name);
        sleep(3); 
		for(i=0;i<=10000000;i++);
			
        lft_chopstick = phil->lft_chopstick;
        rgt_chopstick = phil->rgt_chopstick;
        printf("\n%s is now hungry.\n", phil->name);
        for(i=0;i<=10000000;i++);
        chances_left = 2;   /*we will try twice before being forceful */
        printf("\n%s is now picking up left chopstick.\n", phil->name);
        do {
            failed = gtthread_mutex_lock( lft_chopstick);
            failed = (chances_left>0)? gtthread_mutex_trylock( rgt_chopstick )
                                   : gtthread_mutex_lock(rgt_chopstick);
            if (failed) {
                gtthread_mutex_unlock( lft_chopstick);
                tmp_chopstick = lft_chopstick;
                lft_chopstick = rgt_chopstick;
                rgt_chopstick = tmp_chopstick;
                chances_left -= 1;
            }
            else
				printf("\n%s is now picking up right chopstick.\n", phil->name);
         
        } while(failed && keep_running);
		
        if (!failed) {
		
            printf("\n%s is now eating sphagetti. Yum Yum.\n", phil->name);
            sleep(3);
            gtthread_mutex_unlock( rgt_chopstick);
            gtthread_mutex_unlock( lft_chopstick);
			gtthread_yield();
        }
    }
    return NULL;
}
 
void think()
{
    gtthread_mutex_t forks[5];
    Philosopher philosophers[5];
    Philosopher *phil;
    int i;
    int failed;
   
    gtthread_init(1000);
 
    for (i=0;i<5; i++) 
        gtthread_mutex_init(&forks[i]);
 
    for (i=0;i<5; i++) {
        phil = &philosophers[i];
        phil->name = smartGuys[i];
        phil->lft_chopstick = &forks[i];
        phil->rgt_chopstick = &forks[(i+1)%5];
        gtthread_create( &phil->thread, PhilospherFunc, phil);
    }
 
    sleep(2);
    printf("\n***DINING PHILOSOPHERS***\n");
 
    for(i=0; i<5; i++) {
        phil = &philosophers[i];
        while(1);
    }
}
 
int main()
{
    think();
    return 0;
}
