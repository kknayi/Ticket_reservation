//menu.h文件
//实现功能：系统界面文件，调用所有底层函数接口

#ifndef MENU_H_
#define MENU_H_

#include "datain.h"
#include "search_plane.h"
#include "recommend_plane.h"
#include "book_tickets.h"
#include "search_all_history.h"
#include "change_tickets.h"
#include <Windows.h>

string id;
string ID[100];

//初始加载界面
void start_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************欢迎来到机票预订系统*******************************" << endl << endl;
	cout << "                             程序正在启动中......." << endl;
	for (int i = 1; i <= 100; i++) {
		cout << "\r" << "[" << i << "\%" << "]";    //在这一行的首位置打印出进度条百分比
		for (int j = 1; j <= i; j += 2) {
			cout << "█";
			if (i <= 35)
				Sleep(1);                           //让程序休眠一会儿，以防进度条过快完成
		}
	}
}

//检测用户是否存在
bool TestUser(string ID) {
	int tmp = 0;
	for (int i = 0; i < 80; i++) {
		if (person[i].person_id == ID) {
			cout << "			登录成功，您已进入机票预订系统！" << endl;
			tmp++;
			return true;
		}
	}
	if (!tmp) {
		cout << "			用户不存在，返回上一级界面......" << endl;
		Sleep(3000);
		return false;
	}
}

//用户登录界面
bool User_Enter_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************机票预订系统*******************************" << endl << endl;
	cout << "			请输入您的ID: ";
	cin >> id;
	bool flag = TestUser(id);
	return flag;
}

//测试用户名是否存在
bool CheckUser_inUser2in_menu(string id) {
	for (int i = 0; i < 80; i++) {
		if (person[i].person_id == id)
			return true;
	}
	return false;
}

//多用户输入界面
int User_2in_menu() {
	int i = 0;
	ID[i] = id;
	i++;
	system("cls");
	cout << endl << endl;
	cout << "*****************************机票预订系统*******************************" << endl << endl;
	cout << "			请输入其余用户(输入00退出多用户输入)：" << endl;
	while (true) {
		cout << "			请输入团体中第 " << i + 1 << " 个用户" << "：";
		string tmp_id;
		cin >> tmp_id;
		if (tmp_id == "00")
			break;
		if (!CheckUser_inUser2in_menu(tmp_id)) {
			cout << "			您输入的用户不存在，请重新输入......" << endl << endl;
			continue;
		}
		ID[i] = tmp_id;
		i++;
	}
	return i;
}

//多用户登录界面
void User_2_enter_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************机票预订系统*******************************" << endl << endl;
	int user_num = User_2in_menu();
	system("cls");
	cout << "			团体用户列表：" << endl << endl;
	for (int i = 0; i < user_num; i++)
		cout << "			" << ID[i] << endl;
	cout << "			正在跳转进入订票流程......" << endl;
	Sleep(3000);
	EnterUser(ID, user_num);
}

//1.单用户、多用户分支界面
void User_1or_2() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************机票预订系统*******************************" << endl << endl;
	cout << "			1. 单用户操作" << endl;
	cout << "			2. 多用户操作" << endl;
	cout << endl << endl;
	cout << "			请输入您的选择：";
	string chance;
	cin >> chance;
	if (chance == "1") {
		EnterUser(id);
	}
	else if (chance == "2") {
		User_2_enter_menu();
	}
	else {
		cout << "			输入选项有误，返回上级选项......" << endl;
		Sleep(3000);
		return;
	}
}

//2.查询用户界面
void Search_history_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************机票预订系统*******************************" << endl << endl;
	cout << "			以下是本账号的当前预订航班信息：" << endl << endl;
	search_all_history(id);
}

//3.申请退票界面
void Unbook_tickets_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************机票预订系统*******************************" << endl << endl;
	int loc = 0;
	for (int i = 0; i < 80; i++) {
		if (person[i].person_id == id) {
			loc = i;
			break;
		}
	}
	if (history[loc].person_id == NULLstr) {
		cout << "			当前账号无订票记录，返回上一级目录......" << endl;
		Sleep(3000);
		return;
	}
	else {
		cout << "			以下是本账号的当前预订航班信息：" << endl << endl;
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

		cout << endl << endl;
		cout << "			确认退票？(Y/N)：";
		string select;
		cin >> select;
		if (select == "Y" || select == "y") {
			Unbook(id);
		}
		else if (select == "N" || select == "n") {
			cout << "			取消操作，返回上一级界面......" << endl;
			Sleep(3000);
			return;
		}
		else {
			cout << "			输入有误，返回上一级界面......" << endl;
			Sleep(3000);
			return;
		}
	}
}

//4.改签界面
void Change_tickets_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************机票预订系统*******************************" << endl << endl;
	Change_tickets(id);
}

//选项界面
int Select_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************机票预订系统*******************************" << endl << endl;
	cout << "			1. 预订机票" << endl;
	cout << "			2. 查询预订" << endl;
	cout << "			3. 申请退票" << endl;
	cout << "			4. 改签机票" << endl;
	cout << "			5. 退出账号" << endl;
	cout << "			6. 退出系统" << endl;
	cout << endl << endl;
	cout << "			请输入您的选择：";
	string select;
	cin >> select;
	bool flag = true;
	if (select == "1") {
		User_1or_2();
	}
	else if (select == "2") {
		Search_history_menu();
	}
	else if (select == "3") {
		Unbook_tickets_menu();
	}
	else if (select == "4") {
		Change_tickets_menu();
	}
	else if (select == "5") {
		return 5;
	}
	else if (select == "6") {
		return 6;
	}
	else {
		cout << "输入选项有误，重置界面......" << endl;
		Sleep(3000);
	}
}

//界面函数
void menu() {
	start_menu();
	while (true) {
		bool flag = User_Enter_menu();
		while (flag == false) {
			system("cls");
			flag = User_Enter_menu();
		}
		if (flag == true) {
			while (true) {
				int flag = 0;
				flag = Select_menu();
				if (flag == 5)
					break;
				else if (flag == 6)
					exit(1);
			}
		}
	}
}

#endif