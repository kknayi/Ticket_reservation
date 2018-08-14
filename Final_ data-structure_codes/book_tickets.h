//book_tickets.h文件
//实现功能：订票、退票功能，并将订票成功信息写入历史记录数组，集成一部分查询推荐功能
//使用的相关算法：优先队列

#ifndef BOOK_TICKETS_H_
#define BOOK_TICKETS_H_

#include "datain.h"
#include "search_plane.h"
#include "recommend_plane.h"
#include <Windows.h>

//团体订票优先队列
struct Queue {
	Person queue_p[100];
	int len;
};

//初始化历史列表
void InitHistory() {
	for (int i = 0; i < 100; i++) {
		history[i].person_id = NULLstr;
		history[i].vip_grade = NULLnum;
		history[i].site_num = NULLnum;
		history[i].plane_num = NULLstr;
		history[i].start_time = NULLnum;
		history[i].time_len = NULLnum;
		history[i].start_place = NULLstr;
		history[i].end_place = NULLstr;
		history[i].path_len = NULLnum;
		history[i].price = NULLnum;
	}
}

//检测输入地点名称合法性函数
bool ChackPlace(string p) {
	string list[] = { "Shanghai", "Guizhou", "Gansu", "Hongkong", "NewYork", "Tokyo", "India", "USA", "Hangzhou", "Chongqing" };
	for (int i = 0; i < 10; i++) {
		if (p == list[i])
			return true;
	}
	return false;
}

//检测航班号合法性函数
bool ChackPlane_num(string p) {
	for (int i = 0; i < 200; i++) {
		if (p == plane[i].plane_num)
			return true;
	}
	return false;
}

//检测航班座位号合法性函数
bool ChackPlane_site(int site) {
	if (site < 1 || site > 50)
		return false;
	else
		return true;
}

//单人订票功能
//person *p 登录的用户，person_num 用户在表中的位置
bool Book_tickets(Person p, int person_num) {
	string select;
	string start_p;
	string end_p;
	string time;

	cout << endl << endl;
	//登录并给出一级推荐
	TimeSort();
	cout << endl << "			--------------------------------------------" << endl << endl;
	PriceSort();

	cout << endl << endl;

	//查询
	cout << "今日可选路径：Shanghai, Guizhou, Gansu, Hongkong, NewYork, Tokyo, India, USA, Hangzhou, Chongqing" << endl << endl;
	cout << "			1. 以起点、终点作为关键字查询" << endl
		<< "			2. 以时间、起点、终点作为关键字查询" << endl << endl << endl;
	cout << "			请输入查询选项：";
	cin >> select;
	if (select == "1") {         //起点、终点查询
		cout << "			请输入起点：";
		cin >> start_p;
		while (!ChackPlace(start_p)) {
			cout << "			您的输入有误，请重新输入起点：";
			cin >> start_p;
		}
		cout << "			请输入终点：";
		cin >> end_p;
		while (!ChackPlace(end_p)) {
			cout << "			您的输入有误，请重新输入终点：";
			cin >> end_p;
		}

		cout << endl << endl;

		//二级推荐功能
		RoadSort_2(start_p, end_p);
		PriceSort_2(start_p, end_p);
		////////////
		Search_place(start_p, end_p);
	}
	else if (select == "2") {      //起始时间、起点、终点查询
		cout << "			请输入起始时间(输入时间以hh:mm的形式输入)：";
		cin >> time;
		cout << "			请输入起点：";
		cin >> start_p;
		cout << "			请输入终点：";
		cin >> end_p;
		//二级推荐功能
		RoadSort_2(start_p, end_p);
		PriceSort_2(start_p, end_p);
		////////////
		Search_all(time, start_p, end_p);
	}
	else {
		cout << "			输入选项有误，返回上一级......" << endl;
		Sleep(3000);
		return false;
	}

	//选择相应的航班及座位号
	string Plane_num;
	cout << "			请选择您将要乘坐的航班号: ";
	cin >> Plane_num;
	while (!ChackPlane_num(Plane_num)) {
		cout << "			您输入的航班信息有误，请重新输入：";
		cin >> Plane_num;
	}
	int loc = 0;
	for (int i = 0; i < 200; i++) {
		if (plane[i].plane_num == Plane_num) {
			loc = i;
			break;
		}
	}
	int site_loc;
	cout << "			请选择您想要的航班座位号: ";
	cin >> site_loc;
	while (!ChackPlane_site(site_loc)) {
		cout << "			您输入的航班座位号有误，请重新输入：";
		cin >> site_loc;
	}
	plane[loc].site_num[site_loc - 1] = true;
	history[person_num].person_id = p.person_id;
	history[person_num].vip_grade = p.vip_grade;
	history[person_num].site_num = site_loc;
	history[person_num].plane_num = plane[loc].plane_num;
	history[person_num].start_time = plane[loc].start_time;
	history[person_num].time_len = plane[loc].time_len;
	history[person_num].start_place = plane[loc].start_place;
	history[person_num].end_place = plane[loc].end_place;
	history[person_num].path_len = plane[loc].path_len;
	history[person_num].price = plane[loc].price;

	cout << "			订票成功，返回选择界面......" << endl;

	Sleep(3000);
	return true;
}

//多人同时订票功能
//person *p存储同时订票用户的数组，数组大小n
void Book_tickets(Person *p, int n) {
	for (int k = 0; k < n; k++) {
		cout << endl << endl;
		cout << "			当前操作的用户ID：";
		cout << p[k].person_id << endl;
		cout << "			当前操作的用户VIP等级：";
		cout << p[k].vip_grade << endl;
		cout << endl;
		string select;
		string start_p;
		string end_p;
		string time;

		cout << endl << endl;
		//登录并给出一级推荐
		TimeSort();
		cout << endl << "			--------------------------------------------" << endl << endl;
		PriceSort();

		cout << endl << endl;

		//查询
		cout << "今日可选路径：Shanghai, Guizhou, Gansu, Hongkong, NewYork, Tokyo, India, USA, Hangzhou, Chongqing" << endl << endl;
		cout << "			1. 以起点、终点作为关键字查询" << endl
			<< "			2. 以时间、起点、终点作为关键字查询" << endl << endl << endl;
		cout << "			请输入查询选项：";
		cin >> select;
		if (select == "1") {           //起点、终点查询
			cout << "			请输入起点：";
			cin >> start_p;
			while (!ChackPlace(start_p)) {
				cout << "			您的输入有误，请重新输入起点：";
				cin >> start_p;
			}
			cout << "			请输入终点：";
			cin >> end_p;
			while (!ChackPlace(end_p)) {
				cout << "			您的输入有误，请重新输入终点：";
				cin >> end_p;
			}

			cout << endl << endl;

			//二级推荐功能
			RoadSort_2(start_p, end_p);
			PriceSort_2(start_p, end_p);
			////////////
			Search_place(start_p, end_p);
		}
		else if (select == "2") {        //起始时间、起点、终点查询
			cout << "			请输入起始时间(输入时间以hh:mm的形式输入)：";
			cin >> time;
			cout << "			请输入起点：";
			cin >> start_p;
			cout << "			请输入终点：";
			cin >> end_p;
			//二级推荐功能
			RoadSort_2(start_p, end_p);
			PriceSort_2(start_p, end_p);
			////////////
			Search_all(time, start_p, end_p);
		}
		else {
			cout << "			输入选项有误，进入下一成员的订票系统......" << endl;
			Sleep(3000);
			continue;
		}

		//选择相应的航班及座位号
		string Plane_num;
		cout << "			请选择您将要乘坐的航班号: ";
		cin >> Plane_num;
		while (!ChackPlane_num(Plane_num)) {
			cout << "			您输入的航班信息有误，请重新输入：";
			cin >> Plane_num;
		}
		int loc = 0;
		for (int i = 0; i < 200; i++) {
			if (plane[i].plane_num == Plane_num) {
				loc = i;
				break;
			}
		}
		int site_loc;
		cout << "			请选择您想要的航班座位号: ";
		cin >> site_loc;
		while (!ChackPlane_site(site_loc)) {
			cout << "			您输入的航班座位号有误，请重新输入：";
			cin >> site_loc;
		}
		int person_num = 0;
		for (int i = 0; i < 80; i++) {
			if (p[k].person_id == person[i].person_id)
				person_num = i;
		}
		plane[loc].site_num[site_loc - 1] = true;
		history[person_num].person_id = p[k].person_id;
		history[person_num].vip_grade = p[k].vip_grade;
		history[person_num].site_num = site_loc;
		history[person_num].plane_num = plane[loc].plane_num;
		history[person_num].start_time = plane[loc].start_time;
		history[person_num].time_len = plane[loc].time_len;
		history[person_num].start_place = plane[loc].start_place;
		history[person_num].end_place = plane[loc].end_place;
		history[person_num].path_len = plane[loc].path_len;
		history[person_num].price = plane[loc].price;

		cout << "			订票成功，返回选择界面......" << endl;
		Sleep(3000);
		continue;
	}
}

//退票功能
void Unbook_tickets(int person_num) {
	int site_loc = history[person_num].site_num;
	for (int i = 0; i < 200; i++) {
		if (plane[i].plane_num == history[person_num].plane_num) {
			plane[i].site_num[site_loc - 1] = false;
		}
	}
	history[person_num].person_id = NULLstr;
	history[person_num].vip_grade = NULLnum;
	history[person_num].site_num = NULLnum;
	history[person_num].plane_num = NULLstr;
	history[person_num].start_time = NULLnum;
	history[person_num].time_len = NULLnum;
	history[person_num].start_place = NULLstr;
	history[person_num].end_place = NULLstr;
	history[person_num].path_len = NULLnum;
	history[person_num].price = NULLnum;

	cout << "			退票成功，返回上一级界面......" << endl;
	Sleep(3000);
}

//优先队列排序
void Sort_queue(Person *p, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (p[i].vip_grade < p[j].vip_grade) {
				Person tmp;
				tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
		}
	}
}

//初始化优先队列
void InitQueue(Queue Q) {
	for (int i = 0; i < 100; i++) {
		Q.queue_p[i].person_id = NULLstr;
		Q.queue_p[i].vip_grade = NULLnum;
	}
	Q.len = 0;
}

//创建优先队列
Queue CreatQueue(Person *p, int n) {
	Queue Q;
	InitQueue(Q);
	for (int i = 0; i < n; i++) {
		Q.queue_p[i] = p[i];
		Sort_queue(Q.queue_p, i + 1);
	}
	Q.len = n;
	return Q;
}

//单一用户登录
void EnterUser(string ID) {
	bool flag = true;
	for (int i = 0; i < 80; i++) {
		if (person[i].person_id == ID) {
			bool flag = Book_tickets(person[i], i);
			while (!flag)
				flag = Book_tickets(person[i], i);
			if (flag)
				return;
		}
	}
}

//多用户同时登录
void EnterUser(string *ID, int n) {
	Person tmp[100];
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 80; j++) {
			if (person[j].person_id == ID[i]) {
				tmp[cnt].person_id = person[j].person_id;
				tmp[cnt].vip_grade = person[j].vip_grade;
				cnt++;
			}
		}
	}
	Queue Q = CreatQueue(tmp, cnt);
	Book_tickets(Q.queue_p, Q.len);
}

//用户退票接口
void Unbook(string id) {
	int loc = 0;
	for (int i = 0; i < 80; i++) {
		if (person[i].person_id == id)
			loc = i;
	}
	Unbook_tickets(loc);
}

#endif