//search_plane.h�ļ�
//ʵ�ֹ��ܣ������ѯ����
//ʹ�õ�����㷨����ϣ����(��ͻ������������ӷ�)���������ҡ�ð������

#ifndef _SEARCH_PLANE_H_
#define _SEARCH_PLANE_H_

#include "datain.h"
#include <cmath>
#include <vector>

const int HashMaxsize = 200;     //��ϣ����󳤶�
const int IndexMaxsize = 100;    //������������󳤶�
const int NULLnum = -1;          //�������ֳ�ֵ-1
const string NULLstr = "\0";     //�����ַ�����ֵ\0
const int M = 103;               //��ϣ��������������ģM

//����������
struct IndexItem {
	string index;				 //�ؼ���
	int start;					 //��ʼλ��
	int length;					 //����
};

//�����ϣ��
struct HashItem {
	Plane plane;				 //Ԫ������
	HashItem* next;				 //���ӷ�ָ��ؼ�����ͬ��Ԫ��
};

typedef HashItem* Hashlist[HashMaxsize];               //������ϣ��
typedef IndexItem Indexlist[IndexMaxsize];             //����������

//��ϣ����������float����
int Hash(float time) {
	return int(time * 8) % M;
}

//���򣺽����������Գ����ص�����ķ�ʽ����
void Sort(Plane *p) {
	for (int i = 0; i <= 200; i++)
		for (int j = i; j <= 200; j++)
			if (p[i].start_place > p[j].start_place) {
				Plane tmp;
				tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
}

//��������ʼ��
void InitIndex(Indexlist BT) {
	for (int i = 0; i < IndexMaxsize; i++) {
		BT[i].index = NULLstr;
		BT[i].start = NULLnum;
		BT[i].length = NULLnum;
	}
}

//����������
void CreatIndex(Indexlist BT) {
	int cnt = 0;
	int j = 0;
	string tmp_str = plane[0].start_place;
	for (int i = 0; i <= 200; i++) {
		if (plane[i].start_place == tmp_str) {
			if (cnt == 0)
				BT[j].start = i;
			cnt++;
			tmp_str = plane[i].start_place;
		}
		else {
			BT[j].index = tmp_str;
			BT[j].length = cnt;
			cnt = 0;
			tmp_str = plane[i].start_place;
			j++;
			i--;
		}
	}
}

//����������
void SearchIndex(string start_p, string end_p, Indexlist BT, int *loc_return) {
	int cnt = 0;
	for (int i = 0; i < 10; i++) {
		if (BT[i].index == start_p)
			for (int j = BT[i].start; j < (BT[i].start + BT[i].length); j++)
				if (plane[j].end_place == end_p)
					loc_return[cnt++] = j;
	}
}

//��ϣ����ʼ��
void InitHashlist(Hashlist HT) {
	for (int i = 0; i < HashMaxsize; i++) {
		HT[i] = NULL;
	}
}

//��ϣ������
void CreatHashlist(Hashlist HT) {
	int location = 0;
	for (int i = 0; i <= 200; i++) {
		location = Hash(plane[i].start_time);
		HashItem *p = new HashItem;				//��ͻ������������ӷ�
		p->plane = plane[i];
		p->next = HT[location];
		HT[location] = p;
	}
}

//��ϣ������
Plane* SearchHashlist(Hashlist HT, float time, string start_p) {
	int location = Hash(time);
	HashItem *p = HT[location];
	while (p != NULL) {
		if (p->plane.start_time == time && p->plane.start_place == start_p)
			return &(p->plane);
		else
			p = p->next;
	}
	return NULL;
}

//�ԡ���㡢�յ㡱��Ϊ�ؼ��ֲ���������
void Search_place(string start_p, string end_p) {
	Indexlist BT;
	InitIndex(BT);
	Sort(plane);
	CreatIndex(BT);
	int loc[10] = { -1 };
	for (int i = 0; i < 10; i++)
		loc[i] = -1;
	SearchIndex(start_p, end_p, BT, loc);
	if (loc[0] != -1) {
		int i = 0;
		while (loc[i] != -1) {
			cout << endl << endl;
			cout << "			����ţ�" << plane[loc[i]].plane_num << endl;
			cout << "			��ǰ��ѡ��λ��" << endl;
			int cnt = 0;
			for (int j = 0; j < 50; j++) {
				if (cnt == 0)
					cout << "		";
				if (plane[loc[i]].site_num[j] == false) {
					if (j + 1 < 10)
						cout << " " << j + 1 << "��      ";
					else
						cout << j + 1 << "��      ";
					cnt++;
				}
				if (cnt % 6 == 0)
					cout << endl << "		";
			}
			if (cnt == 0)
				cout << "			����ѯ�ĺ�����λ�Ѿ��������뻻����������......" << endl << "������һ��......" << endl;
			cout << endl;
			if (plane[loc[i]].start_time - floor(plane[loc[i]].start_time) == 0) {
				cout << "			����ʱ�䣺" << floor(plane[loc[i]].start_time) << ':' << (plane[loc[i]].start_time - floor(plane[loc[i]].start_time)) * 60 << '0' << endl
					<< "			��㣺" << plane[loc[i]].start_place << endl
					<< "			�յ㣺" << plane[loc[i]].end_place << endl;
			}
			else
				cout << "			����ʱ�䣺" << floor(plane[loc[i]].start_time) << ':' << (plane[loc[i]].start_time - floor(plane[loc[i]].start_time)) * 60 << endl
				<< "			��㣺" << plane[loc[i]].start_place << endl
				<< "			�յ㣺" << plane[loc[i]].end_place << endl;
			i++;
		}
	}
	else
		cout << "			δ�ҵ���ѯ���࣬������һ���˵�......" << endl;
}

//�ԡ���ʼʱ�䡢��㡢�յ㡱��Ϊ�ؼ��ֲ��ҹ�ϣ��
void Search_all(string time, string start_p, string end_p) {
	Hashlist HT;
	InitHashlist(HT);
	CreatHashlist(HT);
	//����ʱ��Ϊstring����Ҫ����ת��Ϊfloat����
	int hour = 0;
	float minute = 0;
	hour = (int(time[0]) - 48) * 10 + (int(time[1]) - 48);
	minute = ((int(time[3]) - 48) * 10 + (int(time[4]) - 48)) / 60.0;
	float current = 0;
	current = hour + minute;
	///////////////////////////
	Plane* p = SearchHashlist(HT, current, start_p);
	if (p != NULL)
		if (p->end_place == end_p) {
			cout << endl << endl;
			cout << "			����ţ�" << p->plane_num << endl;
			cout << "			��ǰ��ѡ��λ��" << endl;
			int cnt = 0;
			for (int j = 0; j < 50; j++) {
				if (cnt == 0)
					cout << "		";
				if (p->site_num[j] == false) {
					if (j + 1 < 10)
						cout << " " << j + 1 << "��      ";
					else
						cout << j + 1 << "��      ";
					cnt++;
				}
				if (cnt % 6 == 0)
					cout << endl << "		";
			}
			if (cnt == 0)
				cout << "			����ѯ�ĺ�����λ�Ѿ��������뻻����������......" << endl << "������һ��......" << endl;
			cout << endl;
			if (p->start_time - floor(p->start_time) == 0) {
				cout << "			����ʱ�䣺" << floor(p->start_time) << ':' << (p->start_time - floor(p->start_time)) * 60 << '0' << endl
					<< "			��㣺" << p->start_place << endl
					<< "			�յ㣺" << p->end_place << endl;
			}
			else
				cout << "			����ʱ�䣺" << floor(p->start_time) << ':' << (p->start_time - floor(p->start_time)) * 60 << endl
				<< "			��㣺" << p->start_place << endl
				<< "			�յ㣺" << p->end_place << endl;

		}
		else
			cout << "			δ�ҵ���ѯ���࣬������һ���˵�......" << endl;
	else
		cout << "			δ�ҵ���ѯ���࣬������һ���˵�......" << endl;
}

#endif