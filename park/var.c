#include "var.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern Queue q;
extern linklist* head;

void init_Queue()
{
	q.front = q.rear = (Queuenode*)malloc(sizeof(Queuenode));
	if(q.front == NULL){
		printf("init queue failure!\n");
		return;
		}
}


position get_car_p(char* id)
{
	int i = 0;
	linklist* tmp = head->next;
	position pos;
	pos.row = -1;
	pos.col = -1;
	while(tmp){
		if(strcmp(tmp->data,id) == 0){
			return tmp->p;
			}
		tmp = tmp->next;
	}
	return pos;
}


time_t get_time(char* id)
{
	linklist* tmp = head->next;
	while(tmp){
		if(strcmp(tmp->data,id) == 0){
			return tmp->begin;
		}
		tmp = tmp->next;
	}
	return 0;
}



void init_linklist()
{
	head = (linklist*)malloc(sizeof(linklist));	//头节点
	if(head == NULL){
		printf("init linklist failure!\n");
		return;
		}
	head->next = NULL;
}

/*
把等待的车放入队列
*/
void push_Queue(char *id)
{
	Queuenode* n = (Queuenode*)malloc(sizeof(Queuenode));
	if(n == NULL){
		printf("push queue failure!\n");
		return;
		}
	int i =0;
	for(i = 0;i < 6;i++){
		n->data[i] = id[i];
		}
	n->next = NULL;
	q.rear->next = n;
	q.rear = n;
	
}

/*
把停车的车辆信息录入链表
*/
void insert_link(char* id,position loca)
{
	linklist* temp = (linklist*)malloc(sizeof(linklist)*1);
	if(temp == NULL){
		printf("insert failuer!\n");
		return;
		}
	linklist* p = head;
	int i =0;
	for(i = 0;i < 6;i++){
		temp->data[i] = id[i];
		}
	temp->next = NULL;
	temp->p = loca;
	temp->begin = time(NULL);
	while(p->next){
		p = p->next;
	}
	p->next = temp;
}

void delete_car(char* id)
{
	linklist* now = head->next;
	linklist* tmp = head;
	while(now){
		if(strcmp(now->data,id) == 0){
			tmp->next = now->next;
			free(now);
			return;
		}
		now = now->next;
		tmp = tmp->next;
	}	
}

void display()
{
	linklist* tmp = head->next;
	while(tmp){
	printf("car_number:%s position:[%d,%d] time: %s\n\n",tmp->data,tmp->p.row,tmp->p.col,ctime(&(tmp->begin)));
	tmp = tmp->next;
	}
}

int empty_queue()
{
	return (q.front == q.rear) ? 1 : 0;   //为空返回1
}

void pop_queue(char* id)
{
	strcpy(id,q.front->next->data);
	
	Queuenode* n = q.front->next;
	q.front->next = n->next;
	free(n);
}


int check_id(char* id)
{
	linklist* p = head->next;
	while(p){
		if(strcmp(p->data,id) == 0){
			return REPETITION;
		}
		p = p->next;
		}
	return ONLY;
}








