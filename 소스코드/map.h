#pragma once
#ifndef __MAP_H__
#define __MAP_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
struct Coord { // ���� ��ǥ
	int x = 0;
	int y = 0;
	int n = 0; // ���° ĭ���� ����
};
class Map {
private:
	char map[101][4]; // ���� �ִ� ĭ�� 100ĭ���� ����
	char board[50][21]; // ������ �ִ� ũ��� 20X20���� ����, start�� end�� �¿� �� ���̶�� ����
	Coord coord = { 25,0,0 }; // ������������ �� �Ʒ��� 20ĭ ���� �� �ֱ� ������ ���� ��ǥ [25][0]���� ����
	int u = 25;//������ ���� �� �ʱⰪ
	int d = 25;//������ �Ʒ��� �� �ʱⰪ
	int r = 0;//������ ������ �� �ʱⰪ
	vector<Coord> mapCoord; // �� ĭ�� ��ǥ ����
	vector<int> bridgeB; // B��ǥ
	vector<int> bridgeb; // b��ǥ
	int cnt = 0;
	int bi = 0; // bridge index ���° bridge����
public:
	Map() {}
	~Map() {}
	void loadMap(string);
	void loadMap();
	void setBridge();
	void showMap(int);
	Coord direction(Coord, char);
	int isAvail(char, int);
	int getbLocation(int);
	char getCard(int l) { return this->map[l][0]; }
	char getOpposite(int);
	int getCnt() { return this->cnt; }
	void initialize();
};
#endif