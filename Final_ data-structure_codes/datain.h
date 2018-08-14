//datain.h�ļ�
//ʵ�ֹ��ܣ�¼��ǰ�ڹ������������

#ifndef _DATAIN_H_
#define _DATAIN_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//�û�
struct Person {
	string person_id;      //�û�ID
	int vip_grade;         //VIP�ȼ�
};

//����
struct Plane {
	bool site_num[50];     //��λ�ż�Ԥ����¼
	string plane_num;      //�����
	float start_time;      //����ʱ��
	int time_len;          //����ʱ��
	string start_place;    //���
	string end_place;      //�յ�
	int path_len;          //·�̳���
	int price;             //Ʊ��
};

//��ʷ��¼
struct History {
	string person_id;      //�û�ID
	int vip_grade;         //VIP�ȼ�
	int site_num;          //��λ��
	string plane_num;      //�����
	float start_time;      //����ʱ��
	int time_len;          //����ʱ��
	string start_place;    //���
	string end_place;      //�յ�
	int path_len;          //·�̳���
	int price;             //Ʊ��
};

Plane plane[300];          //�������顪���洢���к�����Ϣ
Person person[100];        //�û����顪���洢�����û���Ϣ
History history[100];      //��ʷ��¼���顪���洢������ʷ��¼
Plane tmp_p[300];		   //��ʱ��������

void Datain() {
	ifstream inyonghu("yonghu.txt");
	ifstream inhangban("hangban.txt");

	//¼���û�����
	for (int i = 0; i < 80; i++) {
		inyonghu >> person[i].person_id >> person[i].vip_grade;
	}

	//¼�뺽������
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 50; j++)
			plane[i].site_num[j] = false;
		inhangban >> plane[i].plane_num >> plane[i].start_time >> plane[i].time_len
			>> plane[i].start_place >> plane[i].end_place >> plane[i].path_len >> plane[i].price;
	}

	for (int i = 0; i < 200; i++) {
		tmp_p[i] = plane[i];
	}
}

#endif