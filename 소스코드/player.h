#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <ctime>
#include <string>
#include "map.h"
using namespace std;

class Player {
private:
	int location = 0; // player가 몇번째 칸인지
	string name;
	bool end = false;  //if end, F->T
	int dice = 0; // 주사위 결과, 움직일 수 있는 칸 수
	int arrival = 0; // 도착순서
	int score = 0;
	int pCard = 0; // Philips Driver
	int hCard = 0; // Hammer
	int sCard = 0; // Saw
	int bCard = 0; // Bridge
public:
	Player() {}
	~Player() {}
	bool rollDice();
	void setEnd() { this->end = true; }
	bool isEnd();
	void setName(int);
	string getName() { return this->name; }
	void setArrival(int i) { this->arrival = i; }
	void showCard();
	void getpCard() { this->pCard += 1; cout << "P 카드를 얻습니다.\n"; }
	void gethCard() { this->hCard += 1; cout << "H 카드를 얻습니다.\n"; }
	void getsCard() { this->sCard += 1; cout << "S 카드를 얻습니다.\n"; }
	void getbCard() { this->bCard += 1; cout << "B 카드를 얻습니다.\n"; }
	int getArrival() { return this->arrival; }
	void setDice(int d) { this->dice = d; }
	int getDice() { return this->dice; }
	void setLocation(int l) { this->location = l; }
	int getLocation() { return this->location; }
	int getScore();
	void showScore();
};
#endif