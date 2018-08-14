//datain.h文件
//实现功能：录入前期构造的所有数据

#ifndef _DATAIN_H_
#define _DATAIN_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//用户
struct Person {
	string person_id;      //用户ID
	int vip_grade;         //VIP等级
};

//航班
struct Plane {
	bool site_num[50];     //座位号及预订记录
	string plane_num;      //航班号
	float start_time;      //出发时间
	int time_len;          //飞行时长
	string start_place;    //起点
	string end_place;      //终点
	int path_len;          //路程长度
	int price;             //票价
};

//历史记录
struct History {
	string person_id;      //用户ID
	int vip_grade;         //VIP等级
	int site_num;          //座位号
	string plane_num;      //航班号
	float start_time;      //出发时间
	int time_len;          //飞行时长
	string start_place;    //起点
	string end_place;      //终点
	int path_len;          //路程长度
	int price;             //票价
};

Plane plane[300];          //航班数组——存储所有航班信息
Person person[100];        //用户数组——存储所有用户信息
History history[100];      //历史记录数组——存储所有历史记录
Plane tmp_p[300];		   //临时航班数组

void Datain() {
	ifstream inyonghu("yonghu.txt");
	ifstream inhangban("hangban.txt");

	//录入用户数据
	for (int i = 0; i < 80; i++) {
		inyonghu >> person[i].person_id >> person[i].vip_grade;
	}

	//录入航班数据
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