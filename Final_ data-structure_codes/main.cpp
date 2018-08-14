//main.cpp文件
//存在的问题：多次调用最短路径函数会出现程序崩溃的情况

#include "datain.h"
#include "search_plane.h"
#include "recommend_plane.h"
#include "book_tickets.h"
#include "search_all_history.h"
#include "menu.h"

int main() {
	Datain();
	menu();

	return 0;
}