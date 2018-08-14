//search_all_history.h�ļ�
//ʵ�ֹ��ܣ���ѯ�û���Ʊ��ʷ��Ϣ���������Ӧ����Ϣ

#ifndef SEARCH_ALL_HISTORY_H_
#define SEARCH_ALL_HISTORY_H_

#include "datain.h"
#include "search_plane.h"
#include "recommend_plane.h"
#include "book_tickets.h"
#include "search_all_history.h"

//��ѯ�û���ʷ��Ϣ����
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
		cout << "			����û��Ԥ�����࣬�뷵����һ������Ԥ������......" << endl;
	}
	else {
		cout << "			������Ϣ��" << endl;
		cout << "			�û�ID��" << history[loc].person_id << endl;
		cout << "			VIP�ȼ���" << history[loc].vip_grade << endl;
		cout << endl;
		cout << "			������Ϣ��" << endl;
		cout << "			�������ĺ���ţ�" << history[loc].plane_num << endl;
		cout << "			������λ�ţ�" << history[loc].site_num << endl;
		if (history[loc].start_time - floor(history[loc].start_time) == 0)
			cout << "			����ʱ�䣺" << floor(history[loc].start_time) << ':' << (plane[loc].start_time - floor(plane[loc].start_time)) * 60 << '0' << endl;
		else
			cout << "			����ʱ�䣺" << floor(history[loc].start_time) << ':' << (plane[loc].start_time - floor(plane[loc].start_time)) * 60 << endl;
		cout << "			��㣺" << history[loc].start_place << endl;
		cout << "			�յ㣺" << history[loc].end_place << endl;
		cout << "			Ʊ�ۣ�" << history[loc].price << endl;
	}
	Sleep(3000);
	return;
}

#endif