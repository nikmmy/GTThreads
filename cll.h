//circular linked list
#include <stdio.h>
#include <stdlib.h>
# include <ucontext.h>

struct node{
struct node*next;
ucontext_t* data;
int thread_id;
};

struct node*head = NULL,*current, *new_node, *running;

void display_all(){
struct node* temp;

//printf("\nDisplaying..");
if(head == NULL)
 {
	//printf("Empty list");
 }
else {
	temp = head->next;	
	while(temp!=head)
	 {
		//printf("\nDisplaying %d ", temp->thread_id);
		temp = temp->next;
	 }
	//printf("\nHead:%d", head->thread_id);
}	
	
}

void insert(struct node *new_node, int thread_id){
	
	//empty list
	if(head == NULL){
		head= new_node;
		head ->next = new_node;
		current = running = new_node;
	}
	
	//non-empty list
    else{
		new_node -> next = head->next;
		head -> next = new_node;
		head = new_node;
	 }
	
	display_all();
}


struct node* traverse(){
//empty list
if(head == NULL)

	return NULL;


running = current;
current = current -> next;
//printf("\nThread id of thread to be run is %d" ,current->thread_id);
return current;
}


int delete(){
	struct node* temp = head;
//empty list
if(head == NULL)
	return 0;

//one element list
if(head->next == head)
	{
		current = running = head = NULL;
		//printf("\nLast thread deleted.");
	}
else
	{
		//if deleting last non-single node
		if(current==head)
			head = running;
			
		//printf("\nDeleting %d", current ->thread_id);
		
		//finding node before current in list
		while(temp->next!=current)
			temp = temp->next;
			
		temp->next = current ->next;
	}

return 1;	
}

void cancel(int thread){
struct node*temp= head;
struct node*temp1 = head;

//currently running thread is cancelled
if(thread == current -> thread_id)
	{
		delete();
		return;
	}
			
//empty list
if(head == NULL)
	return;

//one element list
if(head->next == head)
	{
		current = running = head = NULL;
		//printf("\nLast thread deleted.");
	}
//finding node with thread_id thread
else{	
		//printf("\nCancelling %d", thread);
		
		//if deleting last non-single node
		while(temp->thread_id != thread)
 			temp = temp -> next;
				
		//finding node prior to node with thread_id thread
		while(temp1->next != temp)
			temp1 = temp1 -> next;
		
		
		//if head is the node being deleted			
		if(temp == head)
			head = temp;
		
		//deleting node from linked list
		temp1->next = temp->next;
		
			
	}
	
}
