#include <stdio.h>
# include <ucontext.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include "cll.h"
#include "gtthread.h"
#include "ell.h"
#define MEM 64000

ucontext_t  *ucp1;
int thread_count = 0;
int ucp_index=0;



struct itimerval it;
struct sigaction act, oact;

sigset_t a;


int gtthread_join(gtthread_t thread,  void** value_ptr){
struct ellnode* found;
while(1){
		found = search_ell(thread);
		if(found!=NULL)
			break;
}

//Now that child has finished, store return val and exit
printf("\nNow that child has finished executing, store return value and exit.");
if(value_ptr!=NULL)
	*value_ptr = found -> retval;
}

int gtthread_equal(gtthread_t t1, gtthread_t t2){
	if(t1 == t2)
		return 1;
	else
		return 0;
}

void schedule(int sig)
{ 
  int flag;
  struct node* traversal;
 //printf("\n***Signal Occurred***.\n");
 	
 traversal = traverse();
 //printf("\nSwapping with Thread id %d", running->thread_id);
 //printf("\nStarting Thread id %d", traversal->thread_id);
 
 flag =  swapcontext(running->data,traversal->data);
 
}

int gtthread_cancel(gtthread_t id){
insert_ell(id, NULL); 
cancel(id);
schedule(2);
return 0;
}

int gtthread_yield(void){
	schedule(2);
	return 1;
}

void gtthread_exit(void *retval){
	
	if(search_ell(current ->thread_id) == NULL)
		{
		
			insert_ell(current->thread_id, retval); 
			delete();
		
		}
		schedule(2);
}

 
void wrapper_function(void*(*func)(void*), void* arg){
	void *a;
	a = func(arg);
	gtthread_exit(a);
}


gtthread_t gtthread_self(void){
		return current->thread_id;
	
};
int  gtthread_create(gtthread_t *thread,
                     void *(*start_routine)(void *),
                     void *arg){
    struct node *new_node;					 
	//Storing context of thread
	*thread = thread_count;
	
	//declaring memory
	new_node = (struct node*)malloc(sizeof(struct node));
	new_node -> data = (ucontext_t*)malloc(sizeof(ucontext_t));
	new_node ->thread_id = thread_count;
	
	//getcontext
	getcontext(new_node->data);

	//makecontext
	new_node ->data -> uc_link = 0;
	new_node->data->uc_stack.ss_sp=malloc(MEM);
	new_node->data->uc_stack.ss_size=MEM;
	new_node->data->uc_stack.ss_flags=0;
	makecontext( new_node->data,  (void(*)(void))wrapper_function, 2, (void*(*)(void))start_routine, arg);


	//inserting in queue
	insert(new_node, thread_count++);
	return 0;

}
                     
                     
void gtthread_init(long period){
//Initialization
ucontext_t first_data;
ucp1 = (ucontext_t*)malloc(sizeof(ucontext_t));
int flag;

//Fetching context of main
struct node *new_node;					 
//declaring memory
new_node = (struct node*)malloc(sizeof(struct node));
new_node -> data = (ucontext_t*)malloc(sizeof(ucontext_t));
new_node ->thread_id = 0;
	

//getcontext
getcontext(new_node->data);

new_node ->data -> uc_link = 0;
new_node->data->uc_stack.ss_sp=malloc(MEM);
new_node->data->uc_stack.ss_size=MEM;
new_node->data->uc_stack.ss_flags=0;
	
insert(new_node, thread_count++);

//Initializing signal handler
 act.sa_handler = schedule;
 sigemptyset(&act.sa_mask);
 act.sa_flags = 0;
 sigaction(SIGPROF, &act, &oact);
 
 // Start itimer
 it.it_interval.tv_sec =0;
 it.it_interval.tv_usec = period;
 it.it_value.tv_sec = 0;
 it.it_value.tv_usec = period;
 setitimer(ITIMER_PROF, &it, NULL);
 
}

int  gtthread_mutex_init(gtthread_mutex_t *mutex){
	mutex->set = 0;
	mutex->thread_id = -1;
	return 0;

}
void pausee(){
//	printf("\nPausing");
	sigemptyset(&a);
	sigaddset(&a, SIGPROF);   // I want to block SIGPROF...
	sigprocmask(SIG_BLOCK, &a, NULL); //SIGPROF blocked...
	
}

void resume(){
//printf("\nRestarting");
	sigemptyset(&a);
	sigaddset(&a, SIGPROF);   // I want to block SIGPROF...
	sigprocmask(SIG_UNBLOCK, &a, NULL); //SIGPROF blocked...
	
}

int  gtthread_mutex_lock(gtthread_mutex_t *mutex){
	//pause_scheduler
	int i;
	pausee();
	if(mutex->set == 0)
		{
			mutex->set=1;
			mutex->thread_id = current->thread_id;
			resume();	
		}
			
	else
		{
			while(1){
					if(mutex->set==0)
						break;
					else
						{
							resume();
							//printf("\nSuccessfully unmasked");
							gtthread_yield();
						
						}
					}
			pausee();
			mutex->set=1;
			mutex->thread_id = current->thread_id;
			resume();
		}
	//successfully got lock
   return 0;
   
}


int  gtthread_mutex_unlock(gtthread_mutex_t *mutex){
if(mutex->thread_id == current->thread_id)
	{	
		pausee();
		mutex->set =0;	
		mutex->thread_id=-1;
		resume();
	}
else
	printf("Illegal instruction.");
}


int gtthread_mutex_trylock(gtthread_mutex_t *mutex){
	int flag;
	//printf("\nTrying to acquire lock %d" ,mutex -> thread_id);
	pausee();
	if(mutex->set == 0)
		{
			mutex->set=1;
			mutex->thread_id = current->thread_id;
			flag = 1;
		}
	resume();
	if(flag == 1){
		//printf("\nAcquired lock");
		return 0;
	}
	else{
		//printf("\nCould not get lock"); 
		return 1;
	}
}
