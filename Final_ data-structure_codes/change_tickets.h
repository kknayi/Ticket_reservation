//change_tickets.h�ļ�
//ʵ�ֹ��ܣ���ǩ���ܣ����ö�Ʊ����Ʊ�����Ľӿں���

#ifndef CHANGE_TICKETS_H_
#define CHANGE_TICKETS_H_

#include "datain.h"
#include "search_plane.h"
#include "recommend_plane.h"
#include "book_tickets.h"
#include "search_all_history.h"

bool CheckHistory(int loc) {
	if (history[loc].person_id == NULLstr) {
		cout << "			��ǰ�˺��޶�Ʊ��¼��������һ��Ŀ¼......" << endl;
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
		cout << "			�����Ǳ��˺ŵĵ�ǰԤ��������Ϣ��" << endl << endl;
		search_all_history(id);
		string select;
		cout << endl << endl;
		cout << "			ȷ����ǩ��(Y/N)��";
		cin >> select;
		if (select == "Y" || select == "y") {
			Unbook(id);
			cout << endl << endl;
			cout << "			��ѡ�񻻳˺��ࣺ" << endl << endl;
			EnterUser(id);
		}
		else if(select == "N" || select == "n") {
			cout << "			ȡ��������������һ��Ŀ¼......" << endl;
			Sleep(3000);
			return;
		}
		else {
			cout << "			�������󣬷�����һ��Ŀ¼......" << endl;
			return;
		}
	}
	else
		return;
}

#endif