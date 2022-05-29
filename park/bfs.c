#include "bfs.h"
#include "var.h"
#include <stdio.h>
#include <string.h>



extern int park_num[ROW][COL];
int map[ROW][COL];



void init_bfs_queue(bfs_queue* q)
{
	q->front = q->rear = 0;
}

void init_map()
{
	int i,j;
	for( i = 0; i < ROW;i++){
		for(j = 0; j < COL;j++){
			map[i][j] = park_num[i][j];
			}
		}
}	

int isempty(bfs_queue* q) //判断队列是否为空
{
	return (q->front == q->rear) ? 1 : 0;   //为空返回1
}

int push(bfs_queue* q,bfs_pos pos)
{
	if(q->rear >= SIZE-1){
		printf("The queue is full!\n");
		return FULL;
	}
	q->data[q->rear++] = pos;
		return FREE;
}

void pop(bfs_queue* q,bfs_pos* pos)
{
	if(isempty(q) == 1){
		printf("The queue is empty!\n");
		return;
	}
	*pos = q->data[q->front++];	
}




int istarget(bfs_pos pos,int end_x,int end_y)
{
	if((pos.x - 1 == end_x && pos.y == end_y)||
	   (pos.x == end_x && pos.y - 1 == end_y)||
	   (pos.x + 1 == end_x && pos.y == end_y)||
	   (pos.x == end_x && pos.y + 1 == end_y)	
	  )return 1;
	else return 0;
}

int is_free(bfs_pos pos)
{
	if(pos.x >= 0 && pos.x < ROW && pos.y >= 0 && pos.y < COL &&map[pos.x][pos.y] == WAY){
		return 1;
		}
	else{
		return 0;
	}
}

void show_path(bfs_queue* q, int front)
{
	int i;
	int tmp;
	for( i = front - 1;i >= 0;){
		tmp = q->data[i].pre; //记录当前点的上一个点
		q->data[i].pre = -1;
		i = tmp;
	}
	
	int state = park_num[q->data[0].x][q->data[0].y]; 
	
	for(i = 0; i < front; i++){
		if(q->data[i].pre == -1){
			park_num[q->data[i].x][q->data[i].y] = BEST;
		}
	}
	printf("\n");
	printf("The best way to your car is\n\n");
	park_info();
	for(i = 0; i < front; i++){
		if(q->data[i].pre == -1){
			park_num[q->data[i].x][q->data[i].y] = WAY; //复位
		}
	}
	park_num[q->data[0].x][q->data[0].y] = state;
	
}

void bfs(bfs_queue* q,int start_x,int start_y,int end_x,int end_y)
{
	bfs_pos now,next;
	now.x = start_x;
	now.y = start_y;
	
	now.pre = -1; //表示已经走过
	
	
// 入队
	if(push(q,now) == FULL){ 
		printf("ERROR in push!\n");
		return;
		}
	map[now.x][now.y] = -1;
	while(isempty(q) == 0){
	pop(q,&now);  //出队
	if(istarget(now,end_x,end_y)){
		show_path(q,q->front);
		return;
		}
	int dir;
	for(dir = 0;dir < 4;dir++){
		switch(dir){
			case 0:     //上
				next.x = now.x - 1;
				next.y = now.y;
				break;
			case 1:     //右
				next.x = now.x;
				next.y = now.y + 1;
				break;
			case 2:     //下
				next.x = now.x + 1;
				next.y = now.y;
				break;
			case 3:     //左
				next.x = now.x;
				next.y = now.y - 1;
				break;
			}
		if(is_free(next)){
			next.pre = q->front - 1;
			push(q,next);
			map[next.x][next.y] = -1;
		}
	}
	}	
}


void find_car() 
{
	char ch[6] = {0};
	position p;
	position car_p;
	printf("Please input your car_number:");
	scanf("%s",ch);
	while(strlen(ch)!=6 || check_id(ch) == ONLY){
		printf("ERROR!Please try again!\n");
		printf("Please input your car number:");
		scanf("%s",ch);
	}
	
	printf("Please input where are you now:");
	scanf("%d,%d",&(p.row),&(p.col));
	while(p.row >= ROW || p.col >= COL || p.row < 0 || p.col < 0){
		printf("Your position error!Please try again!\n");
		printf("Please input where are you now:");
		scanf("%d,%d",&(p.row),&(p.col));
	}
	
	car_p = get_car_p(ch);
	if( car_p.row == -1 || car_p.col == -1){
		printf("Your car don't exsit!\n");
		return;
	}
	
	best_way(p.row,p.col,car_p.row,car_p.col);
	printf("Please press enter to main menu!\n\n");
	getchar();
	getchar();
}


void best_way(int start_x,int start_y,int end_x,int end_y)
{
	bfs_queue q;
	init_bfs_queue(&q);
	init_map();	
	bfs(&q,start_x,start_y,end_x,end_y);
}



void pay_leave()
{
	int choice;
	printf("1.pay\n");
	printf("2.main menu\n\n");
	printf("Your choice:");
	scanf("%d",&choice);
	printf("\n");
	switch(choice){
		case 1:
			pay();
			break;
		case 2:
			return;
	}
}









