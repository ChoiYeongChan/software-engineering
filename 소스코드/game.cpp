#include "game.h"
void Game::start() {
	while (1) {
		cout << "����̼� �÷��� �Ұǰ���? (2 ~ 4)\n\n�Է� : ";
		char a;
		cin >> a;
		n = int(a - 48);
		if (n >= 2 && n <= 4)
			break;
		else {
			cout << "\n�ٽ� �Է��ϼ���.\n" << endl;
		}
	}
	char a;
	m.loadMap();
	cout << "\n�⺻ ������ �ҷ��Խ��ϴ�." << endl;
	while (1) {
		cout << "\n1. �ҷ��� ������ ������ �����Ѵ�.\n2. �ٸ� ������ �ҷ��´�.\n\n�Է� : ";
		cin >> a;
		int b = int(a - 48);
		if (b == 1) {
			cout << "\n�ҷ��� ����\n" << endl;
			break;
		}
		else if (b == 2) {
			cout << "\n�ҷ��� ���� �̸��� �Է��ϼ���. (ex. dafault.map.txt)\n\n�Է� : ";
			cin >> mapName;
			m.loadMap(mapName);
		}
		else {
			cout << "\n�ٽ� �Է��ϼ���." << endl;
		}
	}
	m.showMap(-1); // ó������ -1
	this->opposite = m.getOpposite(m.getCnt() - 1);
	for (int i = 1; i < n + 1; i++)
	{
		player[i].setName(i);
	}
	this->play();
}

void Game::play() {
	int i = 1;
	int turn = 1;
	while (1) {
		if (this->player[i].isEnd() == false) {
			bool d = this->player[i].rollDice();
			if (d == true)
				this->move(i);
			if (this->n - 1 == this->finish) // �Ѹ� ���ܳ��� ������ ��
				break;
			cout << "\n";
			this->player[i].showCard();
			i += 1;
			if (i > this->n) {
				cout << "\n\n" << turn << "�� ����" << endl;
				turn++;
				for (int i = 1; i < n + 1; i++)
				{
					this->player[i].showCard();
				}
				i = 1;
			}
		}
		else // �̹� �������� ����������� �Ѿ
			i++;
	}
	// �������
	int m = -1;//max score
	int index = 0;
	for (i = 1; i < this->n + 1; i++) {
		int n = this->player[i].getScore();
		if (n > m) {
			m = n;
			index = i;
		}
		else if (n == m) { // ���� ������ ���� ���� ����� �¸�
			if (this->player[i].getArrival() < this->player[index].getArrival())
				index = i;
		}
		this->player[i].showScore();
	}
	cout << "\n\n�¸��� : " << this->player[index].getName() << endl;
}

void Game::move(int nPlayer) {
	string input;
	int n = 0;
	while (1)
	{
		int i = 0;
		if (this->player[nPlayer].getDice() == 0) {
			cout << "\n�̵� �� �� �����ϴ�." << endl;
			break;
		}
		cout << "\n������ġ\n" << endl;
		m.showMap(this->player[nPlayer].getLocation());
		cout << "\n�ֻ����� ��� ( " << this->player[nPlayer].getDice() << " ) ��ŭ �̵� �� ��θ� �Է��ϼ���(ex.UDRL or ududdu)\n\n�Է� : ";
		cin >> input;
		int tmp = this->player[nPlayer].getLocation();
		n = input.length();
		if (n != this->player[nPlayer].getDice()) {
			cout << "\n�ٽ� �Է��ϼ���.\n";
		}
		else {
			cout << "\n";
			const char* arr = input.c_str();
			int getb = 0;
			bool mflag = true; // �̵� �Ϸ� �ߴ��� �Ǵ��ϴ� moveflag
			for (i = 0; i < n; i++) {
				char c = toupper(arr[i]);
				if (m.getCnt() == tmp) { // END�� ����
					if (c != opposite) { // END�� ���� ����� �ݴ�� ������ ������ ��
						this->player[nPlayer].setEnd();
						this->player[nPlayer].setArrival(rank);
						rank++;
						this->finish++;
						cout << this->player[nPlayer].getName() << " ����\n" << endl;
						break;
					}
					else
						tmp--;
				}
				else {
					int s = m.isAvail(c, tmp);
					if (s == 1) {
						if (finish > 0) {
							cout << "�ڷ� �� �� �����ϴ�.\n";
							mflag = false;
							break;
						}
						tmp--;
					}
					else if (s == 2)
						tmp++;
					else if (s == 3) { // �ٸ� �ǳʱ�
						tmp = m.getbLocation(tmp);
						getb++;
					}
					else {
						mflag = false;
						break;
					}
				}
			}
			if (mflag == true) { // �̵� �Ϸ�
				for (i = 0; i < getb; i++) { // �ٸ� �ǳ� �� ��ŭ bī�带 ��´�
					this->player[nPlayer].getbCard();
				}
				this->player[nPlayer].setLocation(tmp);
				char card = m.getCard(this->player[nPlayer].getLocation()); // ī�� �ݱ�
				if (card == 'P')
					this->player[nPlayer].getpCard();
				else if (card == 'S' && this->player[nPlayer].getLocation() != 0)
					this->player[nPlayer].getsCard();
				else if (card == 'H')
					this->player[nPlayer].gethCard();
				break;
			}
			else {
				cout << "�ٽ� �Է��ϼ���.\n";
			}
		}
	}
	if (this->player[nPlayer].isEnd() == false) { // ������ ���ߴٸ� �̵� �� ��ġ ���
		cout << "\n�̵� �� ��ġ\n" << endl;
		m.showMap(this->player[nPlayer].getLocation());
	}
}