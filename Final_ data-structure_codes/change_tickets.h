//change_tickets.h文件
//实现功能：改签功能，调用订票、退票操作的接口函数

#ifndef CHANGE_TICKETS_H_
#define CHANGE_TICKETS_H_

#include "datain.h"
#include "search_plane.h"
#include "recommend_plane.h"
#include "book_tickets.h"
#include "search_all_history.h"

bool CheckHistory(int loc) {
	if (history[loc].person_id == NULLstr) {
		cout << "			当前账号无订票记录，返回上一级目录......" << endl;
		Sleep(3000);
		return false;
	}
	else
		return true;
}

void Change_tickets(string id) {
	int loc = 0;
	for (int i = 0; i < 80; i++)
		if (person[i].person_id == id)
			loc = i;
	bool flag = CheckHistory(loc);
	if (flag) {
		cout << "			以下是本账号的当前预订航班信息：" << endl << endl;
		search_all_history(id);
		string select;
		cout << endl << endl;
		cout << "			确定改签？(Y/N)：";
		cin >> select;
		if (select == "Y" || select == "y") {
			Unbook(id);
			cout << endl << endl;
			cout << "			请选择换乘航班：" << endl << endl;
			EnterUser(id);
		}
		else if(select == "N" || select == "n") {
			cout << "			取消操作，返回上一级目录......" << endl;
			Sleep(3000);
			return;
		}
		else {
			cout << "			输入有误，返回上一级目录......" << endl;
			return;
		}
	}
	else
		return;
}

#endif