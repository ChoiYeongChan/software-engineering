#pragma once
#ifndef __MAP_H__
#define __MAP_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
struct Coord { // 지도 좌표
	int x = 0;
	int y = 0;
	int n = 0; // 몇번째 칸인지 저장
};
class Map {
private:
	char map[101][4]; // 지도 최대 칸은 100칸으로 제한
	char board[50][21]; // 지도의 최대 크기는 20X20으로 제한, start와 end는 좌우 양 끝이라고 가정
	Coord coord = { 25,0,0 }; // 시작지점부터 위 아래로 20칸 있을 수 있기 때문에 지도 좌표 [25][0]에서 시작
	int u = 25;//지도의 위쪽 끝 초기값
	int d = 25;//지도의 아래쪽 끝 초기값
	int r = 0;//지도의 오른쪽 끝 초기값
	vector<Coord> mapCoord; // 각 칸의 좌표 저장
	vector<int> bridgeB; // B좌표
	vector<int> bridgeb; // b좌표
	int cnt = 0;
	int bi = 0; // bridge index 몇번째 bridge인지
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