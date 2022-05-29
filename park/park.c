#include "park.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "var.h"
#include <string.h>
#include "bfs.h"


#define ROW 8
#define COL 9

extern int park_num[ROW][COL];
extern int total;
int park_number = 0;//停车数量


void welcome()
{
	system("clear");
	printf("########################################################################\n");
	printf("########################################################################\n");
	printf("########################################################################\n\n");
	printf("               Welcome to our car park!\n\n");
	printf("########################################################################\n");
	printf("########################################################################\n");
	printf("########################################################################\n\n");
	sleep(1);
}
/*
显示选择界面
*/
void show()
{
	printf("Loading........\n\n");
	sleep(1);
	//system("clear");
	printf("1.Cheak the information of the park \n");
	printf("2.Enter the park to park car \n");
	printf("3.Pay and leave the park \n");
	printf("4.exit\n\n");
	printf("please input your choice: ");	 
}

void exit_p()
{
	printf("Welcome to use it again!\n");
	sleep(1);
	exit(0);
}
/*
初始化停车场
*/
void init_park()
{
	int i,j;
	for(i = 0;i < ROW;i++){
		for(j = 0; j < COL; j++){
			if(i == 0||i == ROW-1|| j == 0 || j == COL-1){
				park_num[i][j] = WAY;
				}
			else if((j%4) == 3 || (j%4) == 0){
				park_num[i][j] = WAY;
				}
			else{
				park_num[i][j] = FREE;
				total++;
				}
			}
		}
}
/*
展示车位
*/
void park_info() 
{
	int i,j;
	for(i = 0;i < ROW;i++){
		for(j = 0; j < COL; j++){
			if(park_num[i][j] ==WAY)
				printf("- ");
			else if(park_num[i][j] == FREE)
				printf("# ");
			else if(park_num[i][j] == BEST)
				printf("\033[0;31m- \033[0m"); 
			else
				printf("0 ");
			}
		printf("\n");
		}
		
		//printf("Please press enter to main menu!\n\n");
}

void show_park()
{
	printf("Loading......\n");
	sleep(1);
	system("clear");
	park_info(); 
		printf("\n");
		printf("The number of the position in the park is %d\n",total);
		printf("There are %d positions is free.\n\n",total-park_number);
	display();
	printf("Please press enter to main menu!\n\n");
		getchar();
		getchar();
}

//分配一个车位
position get_position()
{
	int r,c;
	position p;
	srand(time(NULL));
	while(1)
	{
		r = rand()%ROW;
		c = rand()%COL;
		if(park_num[r][c] == FREE){
			p.row = r;
			p.col = c;
			return p;
		}
	}
}


void parking_car(char *id)
{
	position p = get_position();
	park_num[p.row][p.col] = FULL;
	insert_link(id,p);
	printf("Success to park car! \n");
	printf("Car_number:%s position:[%d,%d]\n\n",id,p.row,p.col);
	park_number++;
	printf("Please press enter to main menu!\n\n");
}



/*
停车
*/	
void go_park()
{
	char id[10] = {0};
	printf("Please input your car number:");
	scanf("%s",id);
	while(strlen(id)!=6 || check_id(id) != ONLY){
		printf("ERROR!Please try again!\n");
		printf("Please input your car number:");
		scanf("%s",id);
	}
	
	/*while(check_id(id) != ONLY){
		printf("Your car has been parked!\n");
		printf("Please input correct car number:");
		scanf("%s",id);
	}*/
	
	if((total-park_number) == 0){
		printf("Sorry!The park is full,please wait!\n");
		push_Queue(id);//车位满了，把车放入等待队列
	}
	else{
		parking_car(id); 
		//	push_link(id);//把车的信息录入链表
		getchar();
		getchar();
	}
}



void pay()
{
	char id[6] = {0};
	position car_p;
	printf("Please input your car number:");
	scanf("%s",id);
	while(strlen(id)!=6 || check_id(id) == ONLY){
		printf("ERROR!Please try again!\n");
		printf("Please input your car number:");
		scanf("%s",id);
	}
	time_t t = get_time(id);
	car_p = get_car_p(id);
	double park_time = difftime(time(NULL),t);
	
	printf("\nYour park time is %.lf sec,please pay $%f\n\n",park_time,park_time*0.1);
	printf("1.Success paying            2.Give up Paying \n\n");
	int choice;
	printf("Your choice:");
	scanf("%d",&choice);
	printf("\n");
	switch(choice){
		case 1:
			best_way(car_p.row,car_p.col,ROW - 1,COL - 1);
			break;
		case 2:
			return;
		}
		
	delete_car(id);	
	park_num[car_p.row][car_p.col] = FREE;
	park_number--;	
	printf("The car has leave!\n\n");
	
	if(!empty_queue()){       //判断等待队列是否为空
		char id[6] = {0};
		pop_queue(id);
		parking_car(id);
		
	}
	
}

void leave_park()
{
	printf("1.Find your car\n");
	printf("2.Pay and find the best way to leave\n\n");
	int choice;
	printf("Your choice:");
	scanf("%d",&choice);
	printf("\n");
	switch(choice){
		case 1:
			find_car();
			break;
		case 2:
			pay_leave();
			break;
		default:
			printf("ERROR!Please try again!\n\n");
		}
}












