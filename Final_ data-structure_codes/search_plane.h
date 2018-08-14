//search_plane.h文件
//实现功能：航班查询功能
//使用的相关算法：哈希查找(冲突解决方案：链接法)、索引查找、冒泡排序

#ifndef _SEARCH_PLANE_H_
#define _SEARCH_PLANE_H_

#include "datain.h"
#include <cmath>
#include <vector>

const int HashMaxsize = 200;     //哈希表最大长度
const int IndexMaxsize = 100;    //设置索引表最大长度
const int NULLnum = -1;          //设置数字初值-1
const string NULLstr = "\0";     //设置字符串初值\0
const int M = 103;               //哈希函数除留余数法模M

//定义索引表
struct IndexItem {
	string index;				 //关键字
	int start;					 //开始位置
	int length;					 //长度
};

//定义哈希表
struct HashItem {
	Plane plane;				 //元素类型
	HashItem* next;				 //链接法指向关键字相同的元素
};

typedef HashItem* Hashlist[HashMaxsize];               //命名哈希表
typedef IndexItem Indexlist[IndexMaxsize];             //命名索引表

//哈希函数：参数float类型
int Hash(float time) {
	return int(time * 8) % M;
}

//排序：将航班数据以出发地点有序的方式排序
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

//索引表：初始化
void InitIndex(Indexlist BT) {
	for (int i = 0; i < IndexMaxsize; i++) {
		BT[i].index = NULLstr;
		BT[i].start = NULLnum;
		BT[i].length = NULLnum;
	}
}

//索引表：创建
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

//索引表：查找
void SearchIndex(string start_p, string end_p, Indexlist BT, int *loc_return) {
	int cnt = 0;
	for (int i = 0; i < 10; i++) {
		if (BT[i].index == start_p)
			for (int j = BT[i].start; j < (BT[i].start + BT[i].length); j++)
				if (plane[j].end_place == end_p)
					loc_return[cnt++] = j;
	}
}

//哈希表：初始化
void InitHashlist(Hashlist HT) {
	for (int i = 0; i < HashMaxsize; i++) {
		HT[i] = NULL;
	}
}

//哈希表：创建
void CreatHashlist(Hashlist HT) {
	int location = 0;
	for (int i = 0; i <= 200; i++) {
		location = Hash(plane[i].start_time);
		HashItem *p = new HashItem;				//冲突解决方案：链接法
		p->plane = plane[i];
		p->next = HT[location];
		HT[location] = p;
	}
}

//哈希表：查找
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

//以“起点、终点”作为关键字查找索引表
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
			cout << "			航班号：" << plane[loc[i]].plane_num << endl;
			cout << "			当前可选座位：" << endl;
			int cnt = 0;
			for (int j = 0; j < 50; j++) {
				if (cnt == 0)
					cout << "		";
				if (plane[loc[i]].site_num[j] == false) {
					if (j + 1 < 10)
						cout << " " << j + 1 << "号      ";
					else
						cout << j + 1 << "号      ";
					cnt++;
				}
				if (cnt % 6 == 0)
					cout << endl << "		";
			}
			if (cnt == 0)
				cout << "			您查询的航班座位已经订满，请换乘其他航班......" << endl << "返回上一级......" << endl;
			cout << endl;
			if (plane[loc[i]].start_time - floor(plane[loc[i]].start_time) == 0) {
				cout << "			出发时间：" << floor(plane[loc[i]].start_time) << ':' << (plane[loc[i]].start_time - floor(plane[loc[i]].start_time)) * 60 << '0' << endl
					<< "			起点：" << plane[loc[i]].start_place << endl
					<< "			终点：" << plane[loc[i]].end_place << endl;
			}
			else
				cout << "			出发时间：" << floor(plane[loc[i]].start_time) << ':' << (plane[loc[i]].start_time - floor(plane[loc[i]].start_time)) * 60 << endl
				<< "			起点：" << plane[loc[i]].start_place << endl
				<< "			终点：" << plane[loc[i]].end_place << endl;
			i++;
		}
	}
	else
		cout << "			未找到查询航班，返回上一级菜单......" << endl;
}

//以“起始时间、起点、终点”作为关键字查找哈希表
void Search_all(string time, string start_p, string end_p) {
	Hashlist HT;
	InitHashlist(HT);
	CreatHashlist(HT);
	//因传入时间为string类型要将其转化为float类型
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
			cout << "			航班号：" << p->plane_num << endl;
			cout << "			当前可选座位：" << endl;
			int cnt = 0;
			for (int j = 0; j < 50; j++) {
				if (cnt == 0)
					cout << "		";
				if (p->site_num[j] == false) {
					if (j + 1 < 10)
						cout << " " << j + 1 << "号      ";
					else
						cout << j + 1 << "号      ";
					cnt++;
				}
				if (cnt % 6 == 0)
					cout << endl << "		";
			}
			if (cnt == 0)
				cout << "			您查询的航班座位已经订满，请换乘其他航班......" << endl << "返回上一级......" << endl;
			cout << endl;
			if (p->start_time - floor(p->start_time) == 0) {
				cout << "			出发时间：" << floor(p->start_time) << ':' << (p->start_time - floor(p->start_time)) * 60 << '0' << endl
					<< "			起点：" << p->start_place << endl
					<< "			终点：" << p->end_place << endl;
			}
			else
				cout << "			出发时间：" << floor(p->start_time) << ':' << (p->start_time - floor(p->start_time)) * 60 << endl
				<< "			起点：" << p->start_place << endl
				<< "			终点：" << p->end_place << endl;

		}
		else
			cout << "			未找到查询航班，返回上一级菜单......" << endl;
	else
		cout << "			未找到查询航班，返回上一级菜单......" << endl;
}

#endif