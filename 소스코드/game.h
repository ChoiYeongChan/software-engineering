#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <string>
#include "map.h"
#include "player.h"
using namespace std;

class Game {
private:
	int finish = 0; // 끝낸 사람의 수
	int n; // 플레이어 수
	int rank = 1; // 들어간 순서
	Player player[5]; // 1~4 배열만 사용 편의상 5까지 설정
	char opposite; // end에서 판단을 위한 방향, end 전칸에서 들어오는 방향과 반대방향이 아니면 끝
	Map m;
	string mapName;
public:
	Game() {}
	~Game() {}
	void start();
	void play();
	void move(int);
};
#endif