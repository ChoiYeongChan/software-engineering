#include "player.h"

bool Player::rollDice() {
	int a;
	cout << "\n================================================================" << endl;
	while (1) {
		cout << "\n" << this->name << " �����Դϴ�.\n\n";
		cout << "�ֻ����� ������ ���� �����ϼ���.\n\n1. ������\n2. ����\n\n�Է� : ";
		cin >> a;
		if (a == 1)
		{
			srand((unsigned int)time(NULL));
			int d = (int)(1 + rand() % 6);
			cout << "\n" << "�ֻ������� ���� ���� : " << d << endl;
			cout << "������ �ִ� �ٸ�ī�� ���� : " << this->bCard << endl;
			if (d - this->bCard < 0)
				this->dice = 0;
			else
				this->dice = d - this->bCard;
			cout << "�ֻ��� ��� : " << dice << endl;
			return true;
		}
		else if (a == 2) {
			cout << "\n" << "�̹� ���ʴ� ���ϴ�." << endl;
			if (this->bCard > 0) {
				this->bCard--;
				cout << "�ٸ�ī�� �Ѱ��� �����մϴ�." << endl;
			}
			return false;
		}
		else {
			cout << "\n�ٽ� �Է��ϼ���." << endl;
		}
	}
}

bool Player::isEnd() { // �������� �Ǵ�
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
	int bonus[4] = { 0,7,3,1 }; // ���� ������ ���� ���� ���� ���ϸ� 0��
	this->score = this->pCard + this->hCard * 2 + this->sCard * 3 + bonus[this->arrival];
	return this->score;
}

void Player::showScore() {
	cout << this->name << " �� ���� : " << this->score << endl;
}