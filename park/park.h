#ifndef _PARK_H
#define _PARK_H

#define ROW 8
#define COL 9
#define WAY 99
#define FREE 100
#define FULL 101
#define BEST 199

#include "var.h"

void welcome();
void show();
void show_park();
void go_park();
void leave_park();
void exit_p();
void init_park();
void park_info();
void parking_car(char *id);
position get_position();
void pay();


#endif