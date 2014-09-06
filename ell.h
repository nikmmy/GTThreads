# include<stdio.h>
#include<stdlib.h>

struct ellnode{
int thread_id;
void * retval;
struct ellnode* next;
};

struct ellnode* ellhead = NULL, *new, *temp;


void display_ell(){
	
		//printf("Displaying exit linked list:\n");
		
		if(ellhead == NULL){
			//printf("Empty exit linked list.");
		  }
		else
			{
					temp = ellhead;
					while(temp->next!= NULL)
						{
						   //printf(" id%d:%d", temp->thread_id, (int*)temp->retval);		
						   temp = temp->next;
						}
					//print last node
					//printf(" id%d:%d", temp->thread_id, (int*)temp->retval);
				
			}
	
}

void insert_ell(int thread_id, void* retval){
	new = (struct ellnode*)malloc(sizeof(struct ellnode));
	new -> retval = retval;
	new ->thread_id = thread_id;
	new->next = NULL;
	
	//empty list
	if(ellhead == NULL){
		ellhead= new;
	}
	
	//move ahead till reach list end
	else{
			temp = ellhead;
			while(temp->next != NULL)
				temp = temp->next;
		
			temp->next = new;
	}
	
	
	
display_ell();
}

struct ellnode* search_ell(int thread_id){
	struct ellnode* temp = ellhead;
	while(temp!=NULL){
		if(temp->thread_id == thread_id)
			break;
		temp = temp->next;
	}
  return temp;
		 
	
}
