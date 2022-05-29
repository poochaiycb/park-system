#include <stdio.h>
#include "park.h"
#include "var.h"

int park_num[ROW][COL] = {0};//设置停车场大小
int total; //停放车的总数
Queue q; // 初始化全局指针 要赋值NULL 否则防止野指针
linklist* head;

int main()
{
   int choice;
   welcome();//欢迎界面
   init_park();//初始化停车场
   init_Queue();//初始化等待队列 
   init_linklist();
   while(1)
   {
   show();
   scanf("%d",&choice);
   printf("Your choice is %d",choice);
   printf("\n\n");
   switch(choice){
		case 1:
			show_park();
			break;
		case 2:
			go_park();
			break;
		case 3:
			leave_park();
			break;
		case 4:exit_p();
			break;
		default:
			printf("ERROR!Please try again!\n\n");
		
		}
	}
    return 0;
}