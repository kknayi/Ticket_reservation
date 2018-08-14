//recommend_plane.h�ļ�
//ʵ�ֹ��ܣ������Ƽ����ܣ�����һ���Ƽ��Ͷ����Ƽ�
//ʹ�õ�����㷨���������򡢸��������㷨(�����������·������С�۸�)

#ifndef _RECOMMEND_PLANE_H_
#define _RECOMMEND_PLANE_H_

#include "datain.h"
#include "search_plane.h"
#include <string>

const int MaxVertexNum = 15;						//ͼ�����������
const int MaxEdgeNum = 500;							//ͼ�����ߵ�����
typedef int WeightPrice;							//���塰�۸�����
typedef int Weightroad;								//���塰·�̡�����
const WeightPrice MaxValue = INT_MAX;				//���塰�۸��������ֵ
typedef int Matrix[MaxVertexNum][MaxVertexNum];		//����ͼ���ڽӾ���
int dis_road[MaxVertexNum][MaxVertexNum];			//����·��Ȩֵ����
int path_road[MaxVertexNum][MaxVertexNum];			//����·����¼����
int dis_price[MaxVertexNum][MaxVertexNum];			//����۸�Ȩֵ����
int path_price[MaxVertexNum][MaxVertexNum];			//����۸��¼����
int cnt_road = 0;									//����·���Ƽ����ô���
int cnt_price = 0;									//����۸��Ƽ����ô���

//һ���Ƽ�������۸���ź���
void PriceQuicksort(int left, int right) {
	int i = 0, j = 0, temp = 0;
	Plane t, temp_plane;
	if (left > right)
		return;

	temp = tmp_p[left].price;
	temp_plane = tmp_p[left];
	i = left;
	j = right;
	while (i != j)
	{
		while (tmp_p[j].price >= temp && i < j)
			j--;
		while (tmp_p[i].price <= temp && i < j)
			i++;
		if (i < j)
		{
			t = tmp_p[i];
			tmp_p[i] = tmp_p[j];
			tmp_p[j] = t;
		}
	}
	tmp_p[left] = tmp_p[i];
	tmp_p[i] = temp_plane;

	PriceQuicksort(left, i - 1);
	PriceQuicksort(i + 1, right);
}

//һ���Ƽ�������ʱ����ź���
void TimeQuicksort(int left, int right) {
	int i = 0, j = 0, temp = 0;
	Plane t, temp_plane;
	if (left > right)
		return;

	temp = tmp_p[left].time_len;
	temp_plane = tmp_p[left];
	i = left;
	j = right;
	while (i != j)
	{
		while (tmp_p[j].time_len >= temp && i < j)
			j--;
		while (tmp_p[i].time_len <= temp && i < j)
			i++;
		if (i < j)
		{
			t = tmp_p[i];
			tmp_p[i] = tmp_p[j];
			tmp_p[j] = t;
		}
	}
	tmp_p[left] = tmp_p[i];
	tmp_p[i] = temp_plane;

	TimeQuicksort(left, i - 1);
	TimeQuicksort(i + 1, right);
}

//һ���Ƽ������ͺ�����̺���ʱ���������ɵ͵��ߣ�
void TimeSort() {
	TimeQuicksort(0, 200);
	cout << "			Ϊ���Ƽ���ǰ����ʱ����̵�10�ܺ��ࣺ" << endl << endl;
	for (int i = 1; i < 10; i++)                  //��ʾǰ10��������Ϣ
		cout << "				" << tmp_p[i].start_place << "--->" << tmp_p[i].end_place << "  " << tmp_p[i].time_len << endl;
}

//һ���Ƽ������ͺ���۸��������ɵ͵��ߣ�
void PriceSort() {
	PriceQuicksort(0, 200);
	cout << "			Ϊ���Ƽ���ǰ�۸���͵�10�ܺ��ࣺ" << endl << endl;
	for (int i = 1; i < 10; i++)                  //��ʾǰ10��������Ϣ
		cout << "				" << tmp_p[i].start_place << "--->" << tmp_p[i].end_place << "  " << tmp_p[i].price << endl;
}

//ģ�庯������ʼ��ͼ���ڽӾ���
template<typename T>
void InitMatrix(T GA) {
	for (int i = 0; i < MaxVertexNum; i++) {
		for (int j = 0; j < MaxVertexNum; j++) {
			if (i == j) GA[i][j] = 0;
			else GA[i][j] = MaxValue;
		}
	}
}

//stringתint����
int place2int(string place) {
	if (place == "Shanghai")
		return 0;
	else if (place == "Guizhou")
		return 1;
	else if (place == "Gansu")
		return 2;
	else if (place == "Hongkong")
		return 3;
	else if (place == "NewYork")
		return 4;
	else if (place == "Tokyo")
		return 5;
	else if (place == "India")
		return 6;
	else if (place == "USA")
		return 7;
	else if (place == "Hangzhou")
		return 8;
	else if (place == "Chongqing")
		return 9;
}

//intתstring����
string int2place(int n) {
	if (n == 0)
		return "Shanghai";
	else if (n == 1)
		return "Guizhou";
	else if (n == 2)
		return "Gansu";
	else if (n == 3)
		return "Hongkong";
	else if (n == 4)
		return "NewYork";
	else if (n == 5)
		return "Tokyo";
	else if (n == 6)
		return "India";
	else if (n == 7)
		return "USA";
	else if (n == 8)
		return "Hangzhou";
	else if (n == 9)
		return "Chongqing";
}

//����·��ͼ���ڽӾ���
void CreatMatrix_road(Matrix GA) {
	Weightroad wr;
	int x = 0, y = 0;
	for (int i = 0; i < 200; i++) {
		x = place2int(plane[i].start_place);
		y = place2int(plane[i].end_place);
		wr = plane[i].path_len;
		GA[x][y] = wr;
	}
}

//�����۸�ͼ���ڽӾ���
void CreatMatrix_price(Matrix GA) {
	Weightroad wr;
	for (int i = 0; i < 200; i++) {
		int x = 0, y = 0;
		x = place2int(plane[i].start_place);
		y = place2int(plane[i].end_place);
		wr = plane[i].price;
		GA[x][y] = wr;
	}
}

//�����·
void Floyd_road(Matrix GA, int n) {
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			dis_road[row][col] = GA[row][col];
			path_road[row][col] = col;
		}
	}

	int select = 0;
	for (int tmp = 0; tmp < n; tmp++) {
		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {
				select = (dis_road[row][tmp] == INT_MAX || dis_road[tmp][col] == INT_MAX) ? INT_MAX : (dis_road[row][tmp] + dis_road[tmp][col]);
				if (dis_road[row][col] > select) {
					dis_road[row][col] = select;
					path_road[row][col] = path_road[row][tmp];
				}
			}
		}
	}
}

//������·
void Print_road(Matrix GA, int n, string start_p, string end_p) {
	int temp = 0;
	cout << "			Ϊ���Ƽ����·����ѡ��" << endl;
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (int2place(row) == start_p && int2place(col) == end_p) {
				cout << "			";
				cout << int2place(row) << "--->" << int2place(col) << "    " << "·��: " << dis_road[row][col] << "    " << "���·��: " << int2place(row);
				temp = path_road[row][col];
				//ѭ�����;����ÿ��·��
				while (temp != col) {
					cout << "-->" << int2place(temp);
					temp = path_road[temp][col];
				}
				cout << "-->" << int2place(col) << endl;
			}
		}
	}
}

//�����Ƽ���·��
void RoadSort_2(string start_p, string end_p) {
	if (cnt_road == 0) {
		Matrix GA;
		InitMatrix(GA);
		CreatMatrix_road(GA);
		Floyd_road(GA, 10);
		Print_road(GA, 10, start_p, end_p);
		cnt_road++;
	}
	else return;
}

//����С�۸�
void Floyd_price(Matrix GA, int n) {
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			dis_price[row][col] = GA[row][col];
			path_price[row][col] = col;
		}
	}

	int select = 0;
	for (int tmp = 0; tmp < n; tmp++) {
		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {
				select = (dis_price[row][tmp] == INT_MAX || dis_price[tmp][col] == INT_MAX) ? INT_MAX : (dis_price[row][tmp] + dis_price[tmp][col]);
				if (dis_price[row][col] > select) {
					dis_price[row][col] = select;
					path_price[row][col] = path_price[row][tmp];
				}
			}
		}
	}
}

//�����С�۸�
void Print_price(Matrix GA, int n, string start_p, string end_p) {
	int temp = 0;
	cout << "			Ϊ���Ƽ���С�۸��ѡ��" << endl;
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (int2place(row) == start_p && int2place(col) == end_p) {
				cout << "			";
				cout << int2place(row) << "--->" << int2place(col) << "    " << "�۸�: " << dis_price[row][col] << "    " << "��Ӧ·��: " << int2place(row);
				temp = path_price[row][col];
				//ѭ�����;����ÿ��·��
				while (temp != col) {
					cout << "-->" << int2place(temp);
					temp = path_price[temp][col];
				}
				cout << "-->" << int2place(col) << endl;
			}
		}
	}
}

//�����Ƽ����۸�
void PriceSort_2(string start_p, string end_p) {
	if (cnt_price == 0) {
		Matrix GA;
		InitMatrix(GA);
		CreatMatrix_price(GA);
		Floyd_price(GA, 10);
		Print_price(GA, 10, start_p, end_p);
		cnt_price++;
	}
	else return;
}

#endif