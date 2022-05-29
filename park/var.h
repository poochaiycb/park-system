#ifndef _VAR_H
#define _VAR_H

#define REPETITION 992
#define ONLY       993

#include <time.h>

//队列的节点
typedef struct Queuenode
{
	char data[6];
	struct Queuenode* next;
}Queuenode;

//队列
typedef struct Queue
{
	Queuenode* front;
	Queuenode* rear;
}Queue;

//停车场的位置
typedef struct position
{
	int row;
	int col;
}position;

//用来储存停放车辆的信息的链表
typedef struct linklist
{
	char data[6];
	time_t begin;
	position p;
	struct linklist* next;
}linklist;

void init_Queue();
void push_Queue(char* id);
void init_linklist();
void insert_link(char* ch,position loca);
int check_id(char* id);
void display();
position get_car_p(char* id);
time_t get_time(char* id);
void delete_car(char* id);
int empty_queue();
void pop_queue(char* id);


#endif



