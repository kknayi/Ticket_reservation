//book_tickets.h�ļ�
//ʵ�ֹ��ܣ���Ʊ����Ʊ���ܣ�������Ʊ�ɹ���Ϣд����ʷ��¼���飬����һ���ֲ�ѯ�Ƽ�����
//ʹ�õ�����㷨�����ȶ���

#ifndef BOOK_TICKETS_H_
#define BOOK_TICKETS_H_

#include "datain.h"
#include "search_plane.h"
#include "recommend_plane.h"
#include <Windows.h>

//���嶩Ʊ���ȶ���
struct Queue {
	Person queue_p[100];
	int len;
};

//��ʼ����ʷ�б�
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

//�������ص����ƺϷ��Ժ���
bool ChackPlace(string p) {
	string list[] = { "Shanghai", "Guizhou", "Gansu", "Hongkong", "NewYork", "Tokyo", "India", "USA", "Hangzhou", "Chongqing" };
	for (int i = 0; i < 10; i++) {
		if (p == list[i])
			return true;
	}
	return false;
}

//��⺽��źϷ��Ժ���
bool ChackPlane_num(string p) {
	for (int i = 0; i < 200; i++) {
		if (p == plane[i].plane_num)
			return true;
	}
	return false;
}

//��⺽����λ�źϷ��Ժ���
bool ChackPlane_site(int site) {
	if (site < 1 || site > 50)
		return false;
	else
		return true;
}

//���˶�Ʊ����
//person *p ��¼���û���person_num �û��ڱ��е�λ��
bool Book_tickets(Person p, int person_num) {
	string select;
	string start_p;
	string end_p;
	string time;

	cout << endl << endl;
	//��¼������һ���Ƽ�
	TimeSort();
	cout << endl << "			--------------------------------------------" << endl << endl;
	PriceSort();

	cout << endl << endl;

	//��ѯ
	cout << "���տ�ѡ·����Shanghai, Guizhou, Gansu, Hongkong, NewYork, Tokyo, India, USA, Hangzhou, Chongqing" << endl << endl;
	cout << "			1. ����㡢�յ���Ϊ�ؼ��ֲ�ѯ" << endl
		<< "			2. ��ʱ�䡢��㡢�յ���Ϊ�ؼ��ֲ�ѯ" << endl << endl << endl;
	cout << "			�������ѯѡ�";
	cin >> select;
	if (select == "1") {         //��㡢�յ��ѯ
		cout << "			��������㣺";
		cin >> start_p;
		while (!ChackPlace(start_p)) {
			cout << "			������������������������㣺";
			cin >> start_p;
		}
		cout << "			�������յ㣺";
		cin >> end_p;
		while (!ChackPlace(end_p)) {
			cout << "			�����������������������յ㣺";
			cin >> end_p;
		}

		cout << endl << endl;

		//�����Ƽ�����
		RoadSort_2(start_p, end_p);
		PriceSort_2(start_p, end_p);
		////////////
		Search_place(start_p, end_p);
	}
	else if (select == "2") {      //��ʼʱ�䡢��㡢�յ��ѯ
		cout << "			��������ʼʱ��(����ʱ����hh:mm����ʽ����)��";
		cin >> time;
		cout << "			��������㣺";
		cin >> start_p;
		cout << "			�������յ㣺";
		cin >> end_p;
		//�����Ƽ�����
		RoadSort_2(start_p, end_p);
		PriceSort_2(start_p, end_p);
		////////////
		Search_all(time, start_p, end_p);
	}
	else {
		cout << "			����ѡ�����󣬷�����һ��......" << endl;
		Sleep(3000);
		return false;
	}

	//ѡ����Ӧ�ĺ��༰��λ��
	string Plane_num;
	cout << "			��ѡ������Ҫ�����ĺ����: ";
	cin >> Plane_num;
	while (!ChackPlane_num(Plane_num)) {
		cout << "			������ĺ�����Ϣ�������������룺";
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
	cout << "			��ѡ������Ҫ�ĺ�����λ��: ";
	cin >> site_loc;
	while (!ChackPlane_site(site_loc)) {
		cout << "			������ĺ�����λ���������������룺";
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

	cout << "			��Ʊ�ɹ�������ѡ�����......" << endl;

	Sleep(3000);
	return true;
}

//����ͬʱ��Ʊ����
//person *p�洢ͬʱ��Ʊ�û������飬�����Сn
void Book_tickets(Person *p, int n) {
	for (int k = 0; k < n; k++) {
		cout << endl << endl;
		cout << "			��ǰ�������û�ID��";
		cout << p[k].person_id << endl;
		cout << "			��ǰ�������û�VIP�ȼ���";
		cout << p[k].vip_grade << endl;
		cout << endl;
		string select;
		string start_p;
		string end_p;
		string time;

		cout << endl << endl;
		//��¼������һ���Ƽ�
		TimeSort();
		cout << endl << "			--------------------------------------------" << endl << endl;
		PriceSort();

		cout << endl << endl;

		//��ѯ
		cout << "���տ�ѡ·����Shanghai, Guizhou, Gansu, Hongkong, NewYork, Tokyo, India, USA, Hangzhou, Chongqing" << endl << endl;
		cout << "			1. ����㡢�յ���Ϊ�ؼ��ֲ�ѯ" << endl
			<< "			2. ��ʱ�䡢��㡢�յ���Ϊ�ؼ��ֲ�ѯ" << endl << endl << endl;
		cout << "			�������ѯѡ�";
		cin >> select;
		if (select == "1") {           //��㡢�յ��ѯ
			cout << "			��������㣺";
			cin >> start_p;
			while (!ChackPlace(start_p)) {
				cout << "			������������������������㣺";
				cin >> start_p;
			}
			cout << "			�������յ㣺";
			cin >> end_p;
			while (!ChackPlace(end_p)) {
				cout << "			�����������������������յ㣺";
				cin >> end_p;
			}

			cout << endl << endl;

			//�����Ƽ�����
			RoadSort_2(start_p, end_p);
			PriceSort_2(start_p, end_p);
			////////////
			Search_place(start_p, end_p);
		}
		else if (select == "2") {        //��ʼʱ�䡢��㡢�յ��ѯ
			cout << "			��������ʼʱ��(����ʱ����hh:mm����ʽ����)��";
			cin >> time;
			cout << "			��������㣺";
			cin >> start_p;
			cout << "			�������յ㣺";
			cin >> end_p;
			//�����Ƽ�����
			RoadSort_2(start_p, end_p);
			PriceSort_2(start_p, end_p);
			////////////
			Search_all(time, start_p, end_p);
		}
		else {
			cout << "			����ѡ�����󣬽�����һ��Ա�Ķ�Ʊϵͳ......" << endl;
			Sleep(3000);
			continue;
		}

		//ѡ����Ӧ�ĺ��༰��λ��
		string Plane_num;
		cout << "			��ѡ������Ҫ�����ĺ����: ";
		cin >> Plane_num;
		while (!ChackPlane_num(Plane_num)) {
			cout << "			������ĺ�����Ϣ�������������룺";
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
		cout << "			��ѡ������Ҫ�ĺ�����λ��: ";
		cin >> site_loc;
		while (!ChackPlane_site(site_loc)) {
			cout << "			������ĺ�����λ���������������룺";
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

		cout << "			��Ʊ�ɹ�������ѡ�����......" << endl;
		Sleep(3000);
		continue;
	}
}

//��Ʊ����
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

	cout << "			��Ʊ�ɹ���������һ������......" << endl;
	Sleep(3000);
}

//���ȶ�������
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

//��ʼ�����ȶ���
void InitQueue(Queue Q) {
	for (int i = 0; i < 100; i++) {
		Q.queue_p[i].person_id = NULLstr;
		Q.queue_p[i].vip_grade = NULLnum;
	}
	Q.len = 0;
}

//�������ȶ���
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

//��һ�û���¼
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

//���û�ͬʱ��¼
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

//�û���Ʊ�ӿ�
void Unbook(string id) {
	int loc = 0;
	for (int i = 0; i < 80; i++) {
		if (person[i].person_id == id)
			loc = i;
	}
	Unbook_tickets(loc);
}

#endif