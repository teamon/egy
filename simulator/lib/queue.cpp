#include "sumo.h"
#include "queue.h"
#include <cstdlib>

struct Item{
	Move move;
	Item* next;
} *head, *tail;

Queue::Queue(){
	head = tail = NULL;
}

Queue::~Queue(){
	clear();
}

void Queue::clear(){
	while(head) pop();
}

bool Queue::empty(){
	return (head==NULL);
}

void Queue::push(Move move){
	Item* curr = (Item*) malloc(sizeof(Item));
	if(head == NULL) head = curr;
	else tail->next = curr;
	curr->move = move;
	curr->next = NULL;
	tail = curr;
}

void Queue::push(char left, char right, int time){
	Move m;
	m.left = left;
	m.right = right;
	m.time = time;
	m.pri = 0;
	push(m);
}

void Queue::push(char left, char right, int time, int priority){
	Move m;
	m.left = left;
	m.right = right;
	m.time = time;
	m.pri = priority;
	push(m);
}

Move* Queue::front(){
	if (head){
		return &(head->move);
	}else
		return NULL;
}

void Queue::dec(int time){
	if(head){
		head->move.time -= time;
		if(head->move.time <= 0){
			pop();
		}
	}
}

void Queue::pop(){
	if(head){
		Item *tmp = head->next;
		free(head);
		head = tmp;
	}
}