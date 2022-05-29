#ifndef _BFS_H
#define _BFS_H

#include "park.h"

#define SIZE 1024



typedef struct bfs_pos
{
	int x;
	int y;
	int pre;
}bfs_pos;


typedef struct bfs_queue
{
	bfs_pos data[SIZE];
	int front;
	int rear;
}bfs_queue;



void find_car();
void best_way(int start_x,int start_y,int end_x,int end_y);
void pay_leave();
void bfs(bfs_queue* q,int start_x,int start_y,int end_x,int end_y);


#endif