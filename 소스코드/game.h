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
	int finish = 0; // ���� ����� ��
	int n; // �÷��̾� ��
	int rank = 1; // �� ����
	Player player[5]; // 1~4 �迭�� ��� ���ǻ� 5���� ����
	char opposite; // end���� �Ǵ��� ���� ����, end ��ĭ���� ������ ����� �ݴ������ �ƴϸ� ��
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