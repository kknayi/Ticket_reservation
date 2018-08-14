//menu.h�ļ�
//ʵ�ֹ��ܣ�ϵͳ�����ļ����������еײ㺯���ӿ�

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

//��ʼ���ؽ���
void start_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************��ӭ������ƱԤ��ϵͳ*******************************" << endl << endl;
	cout << "                             ��������������......." << endl;
	for (int i = 1; i <= 100; i++) {
		cout << "\r" << "[" << i << "\%" << "]";    //����һ�е���λ�ô�ӡ���������ٷֱ�
		for (int j = 1; j <= i; j += 2) {
			cout << "��";
			if (i <= 35)
				Sleep(1);                           //�ó�������һ������Է��������������
		}
	}
}

//����û��Ƿ����
bool TestUser(string ID) {
	int tmp = 0;
	for (int i = 0; i < 80; i++) {
		if (person[i].person_id == ID) {
			cout << "			��¼�ɹ������ѽ����ƱԤ��ϵͳ��" << endl;
			tmp++;
			return true;
		}
	}
	if (!tmp) {
		cout << "			�û������ڣ�������һ������......" << endl;
		Sleep(3000);
		return false;
	}
}

//�û���¼����
bool User_Enter_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************��ƱԤ��ϵͳ*******************************" << endl << endl;
	cout << "			����������ID: ";
	cin >> id;
	bool flag = TestUser(id);
	return flag;
}

//�����û����Ƿ����
bool CheckUser_inUser2in_menu(string id) {
	for (int i = 0; i < 80; i++) {
		if (person[i].person_id == id)
			return true;
	}
	return false;
}

//���û��������
int User_2in_menu() {
	int i = 0;
	ID[i] = id;
	i++;
	system("cls");
	cout << endl << endl;
	cout << "*****************************��ƱԤ��ϵͳ*******************************" << endl << endl;
	cout << "			�����������û�(����00�˳����û�����)��" << endl;
	while (true) {
		cout << "			�����������е� " << i + 1 << " ���û�" << "��";
		string tmp_id;
		cin >> tmp_id;
		if (tmp_id == "00")
			break;
		if (!CheckUser_inUser2in_menu(tmp_id)) {
			cout << "			��������û������ڣ�����������......" << endl << endl;
			continue;
		}
		ID[i] = tmp_id;
		i++;
	}
	return i;
}

//���û���¼����
void User_2_enter_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************��ƱԤ��ϵͳ*******************************" << endl << endl;
	int user_num = User_2in_menu();
	system("cls");
	cout << "			�����û��б�" << endl << endl;
	for (int i = 0; i < user_num; i++)
		cout << "			" << ID[i] << endl;
	cout << "			������ת���붩Ʊ����......" << endl;
	Sleep(3000);
	EnterUser(ID, user_num);
}

//1.���û������û���֧����
void User_1or_2() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************��ƱԤ��ϵͳ*******************************" << endl << endl;
	cout << "			1. ���û�����" << endl;
	cout << "			2. ���û�����" << endl;
	cout << endl << endl;
	cout << "			����������ѡ��";
	string chance;
	cin >> chance;
	if (chance == "1") {
		EnterUser(id);
	}
	else if (chance == "2") {
		User_2_enter_menu();
	}
	else {
		cout << "			����ѡ�����󣬷����ϼ�ѡ��......" << endl;
		Sleep(3000);
		return;
	}
}

//2.��ѯ�û�����
void Search_history_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************��ƱԤ��ϵͳ*******************************" << endl << endl;
	cout << "			�����Ǳ��˺ŵĵ�ǰԤ��������Ϣ��" << endl << endl;
	search_all_history(id);
}

//3.������Ʊ����
void Unbook_tickets_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************��ƱԤ��ϵͳ*******************************" << endl << endl;
	int loc = 0;
	for (int i = 0; i < 80; i++) {
		if (person[i].person_id == id) {
			loc = i;
			break;
		}
	}
	if (history[loc].person_id == NULLstr) {
		cout << "			��ǰ�˺��޶�Ʊ��¼��������һ��Ŀ¼......" << endl;
		Sleep(3000);
		return;
	}
	else {
		cout << "			�����Ǳ��˺ŵĵ�ǰԤ��������Ϣ��" << endl << endl;
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

		cout << endl << endl;
		cout << "			ȷ����Ʊ��(Y/N)��";
		string select;
		cin >> select;
		if (select == "Y" || select == "y") {
			Unbook(id);
		}
		else if (select == "N" || select == "n") {
			cout << "			ȡ��������������һ������......" << endl;
			Sleep(3000);
			return;
		}
		else {
			cout << "			�������󣬷�����һ������......" << endl;
			Sleep(3000);
			return;
		}
	}
}

//4.��ǩ����
void Change_tickets_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************��ƱԤ��ϵͳ*******************************" << endl << endl;
	Change_tickets(id);
}

//ѡ�����
int Select_menu() {
	system("cls");
	cout << endl << endl;
	cout << "*****************************��ƱԤ��ϵͳ*******************************" << endl << endl;
	cout << "			1. Ԥ����Ʊ" << endl;
	cout << "			2. ��ѯԤ��" << endl;
	cout << "			3. ������Ʊ" << endl;
	cout << "			4. ��ǩ��Ʊ" << endl;
	cout << "			5. �˳��˺�" << endl;
	cout << "			6. �˳�ϵͳ" << endl;
	cout << endl << endl;
	cout << "			����������ѡ��";
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
		cout << "����ѡ���������ý���......" << endl;
		Sleep(3000);
	}
}

//���溯��
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