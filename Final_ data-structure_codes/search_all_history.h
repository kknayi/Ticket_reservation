//search_all_history.h文件
//实现功能：查询用户订票历史信息，并输出相应的信息

#ifndef SEARCH_ALL_HISTORY_H_
#define SEARCH_ALL_HISTORY_H_

#include "datain.h"
#include "search_plane.h"
#include "recommend_plane.h"
#include "book_tickets.h"
#include "search_all_history.h"

//查询用户历史信息功能
void search_all_history(string id) {
	int loc = 0;
	for (int i = 0; i < 80; i++) {
		if (person[i].person_id == id) {
			loc = i;
			break;
		}
	}

	if (history[loc].person_id == NULLstr) {
		cout << endl;
		cout << "			您还没有预订航班，请返回上一级界面预订航班......" << endl;
	}
	else {
		cout << "			个人信息：" << endl;
		cout << "			用户ID：" << history[loc].person_id << endl;
		cout << "			VIP等级：" << history[loc].vip_grade << endl;
		cout << endl;
		cout << "			航班信息：" << endl;
		cout << "			您乘坐的航班号：" << history[loc].plane_num << endl;
		cout << "			您的座位号：" << history[loc].site_num << endl;
		if (history[loc].start_time - floor(history[loc].start_time) == 0)
			cout << "			出发时间：" << floor(history[loc].start_time) << ':' << (plane[loc].start_time - floor(plane[loc].start_time)) * 60 << '0' << endl;
		else
			cout << "			出发时间：" << floor(history[loc].start_time) << ':' << (plane[loc].start_time - floor(plane[loc].start_time)) * 60 << endl;
		cout << "			起点：" << history[loc].start_place << endl;
		cout << "			终点：" << history[loc].end_place << endl;
		cout << "			票价：" << history[loc].price << endl;
	}
	Sleep(3000);
	return;
}

#endif