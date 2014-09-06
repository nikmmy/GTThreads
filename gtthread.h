

struct gtthread_mutex_t{
		int thread_id;
		int set;
};

typedef int gtthread_t;

typedef struct gtthread_mutex_t gtthread_mutex_t; 

int gtthread_join(gtthread_t thread,  void** value_ptr);

int gtthread_equal(gtthread_t t1, gtthread_t t2);

int gtthread_cancel(gtthread_t id);

int gtthread_yield(void);

void gtthread_exit(void *retval);

gtthread_t gtthread_self(void);

int  gtthread_create(gtthread_t *thread,
                     void *(*start_routine)(void *),
                     void *arg);
                     
void gtthread_init(long period);

int  gtthread_mutex_init(gtthread_mutex_t *mutex);

int  gtthread_mutex_lock(gtthread_mutex_t *mutex);

int  gtthread_mutex_unlock(gtthread_mutex_t *mutex);

int gtthread_mutex_trylock(gtthread_mutex_t *mutex);
