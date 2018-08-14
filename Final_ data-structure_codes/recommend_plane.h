//recommend_plane.h文件
//实现功能：航班推荐功能，包含一级推荐和二级推荐
//使用的相关算法：快速排序、弗洛依德算法(求两点间的最短路径、最小价格)

#ifndef _RECOMMEND_PLANE_H_
#define _RECOMMEND_PLANE_H_

#include "datain.h"
#include "search_plane.h"
#include <string>

const int MaxVertexNum = 15;						//图的最大点的数量
const int MaxEdgeNum = 500;							//图的最大边的数量
typedef int WeightPrice;							//定义“价格”类型
typedef int Weightroad;								//定义“路程”类型
const WeightPrice MaxValue = INT_MAX;				//定义“价格”类型最大值
typedef int Matrix[MaxVertexNum][MaxVertexNum];		//定义图的邻接矩阵
int dis_road[MaxVertexNum][MaxVertexNum];			//定义路径权值矩阵
int path_road[MaxVertexNum][MaxVertexNum];			//定义路径记录矩阵
int dis_price[MaxVertexNum][MaxVertexNum];			//定义价格权值矩阵
int path_price[MaxVertexNum][MaxVertexNum];			//定义价格记录矩阵
int cnt_road = 0;									//定义路径推荐调用次数
int cnt_price = 0;									//定义价格推荐调用次数

//一级推荐：航班价格快排函数
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

//一级推荐：飞行时间快排函数
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

//一级推荐：推送航班最短航行时间排名（由低到高）
void TimeSort() {
	TimeQuicksort(0, 200);
	cout << "			为您推荐当前航行时间最短的10架航班：" << endl << endl;
	for (int i = 1; i < 10; i++)                  //显示前10条航班信息
		cout << "				" << tmp_p[i].start_place << "--->" << tmp_p[i].end_place << "  " << tmp_p[i].time_len << endl;
}

//一级推荐：推送航班价格排名（由低到高）
void PriceSort() {
	PriceQuicksort(0, 200);
	cout << "			为您推荐当前价格最低的10架航班：" << endl << endl;
	for (int i = 1; i < 10; i++)                  //显示前10条航班信息
		cout << "				" << tmp_p[i].start_place << "--->" << tmp_p[i].end_place << "  " << tmp_p[i].price << endl;
}

//模板函数：初始化图的邻接矩阵
template<typename T>
void InitMatrix(T GA) {
	for (int i = 0; i < MaxVertexNum; i++) {
		for (int j = 0; j < MaxVertexNum; j++) {
			if (i == j) GA[i][j] = 0;
			else GA[i][j] = MaxValue;
		}
	}
}

//string转int函数
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

//int转string函数
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

//建立路径图的邻接矩阵
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

//建立价格图的邻接矩阵
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

//求最短路
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

//输出最短路
void Print_road(Matrix GA, int n, string start_p, string end_p) {
	int temp = 0;
	cout << "			为您推荐最短路径的选择：" << endl;
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (int2place(row) == start_p && int2place(col) == end_p) {
				cout << "			";
				cout << int2place(row) << "--->" << int2place(col) << "    " << "路程: " << dis_road[row][col] << "    " << "最短路径: " << int2place(row);
				temp = path_road[row][col];
				//循环输出途径的每条路径
				while (temp != col) {
					cout << "-->" << int2place(temp);
					temp = path_road[temp][col];
				}
				cout << "-->" << int2place(col) << endl;
			}
		}
	}
}

//二级推荐：路径
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

//求最小价格
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

//输出最小价格
void Print_price(Matrix GA, int n, string start_p, string end_p) {
	int temp = 0;
	cout << "			为您推荐最小价格的选择：" << endl;
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (int2place(row) == start_p && int2place(col) == end_p) {
				cout << "			";
				cout << int2place(row) << "--->" << int2place(col) << "    " << "价格: " << dis_price[row][col] << "    " << "对应路径: " << int2place(row);
				temp = path_price[row][col];
				//循环输出途径的每条路径
				while (temp != col) {
					cout << "-->" << int2place(temp);
					temp = path_price[temp][col];
				}
				cout << "-->" << int2place(col) << endl;
			}
		}
	}
}

//二级推荐：价格
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