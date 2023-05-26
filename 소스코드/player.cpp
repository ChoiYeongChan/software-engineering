#include "player.h"

bool Player::rollDice() {
	int a;
	cout << "\n================================================================" << endl;
	while (1) {
		cout << "\n" << this->name << " 차례입니다.\n\n";
		cout << "주사위를 굴릴지 쉴지 선택하세요.\n\n1. 굴린다\n2. 쉰다\n\n입력 : ";
		cin >> a;
		if (a == 1)
		{
			srand((unsigned int)time(NULL));
			int d = (int)(1 + rand() % 6);
			cout << "\n" << "주사위에서 나온 숫자 : " << d << endl;
			cout << "가지고 있는 다리카드 개수 : " << this->bCard << endl;
			if (d - this->bCard < 0)
				this->dice = 0;
			else
				this->dice = d - this->bCard;
			cout << "주사위 결과 : " << dice << endl;
			return true;
		}
		else if (a == 2) {
			cout << "\n" << "이번 차례는 쉽니다." << endl;
			if (this->bCard > 0) {
				this->bCard--;
				cout << "다리카드 한개를 제거합니다." << endl;
			}
			return false;
		}
		else {
			cout << "\n다시 입력하세요." << endl;
		}
	}
}

bool Player::isEnd() { // 끝났는지 판단
	if (this->end == true)
		return true;
	else
		return false;
}

void Player::setName(int n) {
	string temp1 = "Player ";
	string temp2 = to_string(n);
	this->name = temp1 + temp2;
}

void Player::showCard() {
	cout << this->name << " " << " P : " << this->pCard << "  H : " << this->hCard << "  S : " << this->sCard << "  B : " << this->bCard << endl;
}

int Player::getScore() {
	int bonus[4] = { 0,7,3,1 }; // 도착 순서에 따른 점수 도착 못하면 0점
	this->score = this->pCard + this->hCard * 2 + this->sCard * 3 + bonus[this->arrival];
	return this->score;
}

void Player::showScore() {
	cout << this->name << " 의 점수 : " << this->score << endl;
}