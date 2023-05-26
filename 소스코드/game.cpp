#include "game.h"
void Game::start() {
	while (1) {
		cout << "몇명이서 플레이 할건가요? (2 ~ 4)\n\n입력 : ";
		char a;
		cin >> a;
		n = int(a - 48);
		if (n >= 2 && n <= 4)
			break;
		else {
			cout << "\n다시 입력하세요.\n" << endl;
		}
	}
	char a;
	m.loadMap();
	cout << "\n기본 지도를 불러왔습니다." << endl;
	while (1) {
		cout << "\n1. 불러온 지도로 게임을 시작한다.\n2. 다른 지도를 불러온다.\n\n입력 : ";
		cin >> a;
		int b = int(a - 48);
		if (b == 1) {
			cout << "\n불러온 지도\n" << endl;
			break;
		}
		else if (b == 2) {
			cout << "\n불러올 지도 이름을 입력하세요. (ex. dafault.map.txt)\n\n입력 : ";
			cin >> mapName;
			m.loadMap(mapName);
		}
		else {
			cout << "\n다시 입력하세요." << endl;
		}
	}
	m.showMap(-1); // 처음에는 -1
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
			if (this->n - 1 == this->finish) // 한명 남겨놓고 끝나면 끝
				break;
			cout << "\n";
			this->player[i].showCard();
			i += 1;
			if (i > this->n) {
				cout << "\n\n" << turn << "턴 종료" << endl;
				turn++;
				for (int i = 1; i < n + 1; i++)
				{
					this->player[i].showCard();
				}
				i = 1;
			}
		}
		else // 이미 끝냈으면 다음사람으로 넘어감
			i++;
	}
	// 점수계산
	int m = -1;//max score
	int index = 0;
	for (i = 1; i < this->n + 1; i++) {
		int n = this->player[i].getScore();
		if (n > m) {
			m = n;
			index = i;
		}
		else if (n == m) { // 같은 점수면 먼저 들어온 사람이 승리
			if (this->player[i].getArrival() < this->player[index].getArrival())
				index = i;
		}
		this->player[i].showScore();
	}
	cout << "\n\n승리자 : " << this->player[index].getName() << endl;
}

void Game::move(int nPlayer) {
	string input;
	int n = 0;
	while (1)
	{
		int i = 0;
		if (this->player[nPlayer].getDice() == 0) {
			cout << "\n이동 할 수 없습니다." << endl;
			break;
		}
		cout << "\n현재위치\n" << endl;
		m.showMap(this->player[nPlayer].getLocation());
		cout << "\n주사위의 결과 ( " << this->player[nPlayer].getDice() << " ) 만큼 이동 할 경로를 입력하세요(ex.UDRL or ududdu)\n\n입력 : ";
		cin >> input;
		int tmp = this->player[nPlayer].getLocation();
		n = input.length();
		if (n != this->player[nPlayer].getDice()) {
			cout << "\n다시 입력하세요.\n";
		}
		else {
			cout << "\n";
			const char* arr = input.c_str();
			int getb = 0;
			bool mflag = true; // 이동 완료 했는지 판단하는 moveflag
			for (i = 0; i < n; i++) {
				char c = toupper(arr[i]);
				if (m.getCnt() == tmp) { // END로 들어옴
					if (c != opposite) { // END로 들어온 방향과 반대로 나가지 않으면 끝
						this->player[nPlayer].setEnd();
						this->player[nPlayer].setArrival(rank);
						rank++;
						this->finish++;
						cout << this->player[nPlayer].getName() << " 골인\n" << endl;
						break;
					}
					else
						tmp--;
				}
				else {
					int s = m.isAvail(c, tmp);
					if (s == 1) {
						if (finish > 0) {
							cout << "뒤로 갈 수 없습니다.\n";
							mflag = false;
							break;
						}
						tmp--;
					}
					else if (s == 2)
						tmp++;
					else if (s == 3) { // 다리 건너기
						tmp = m.getbLocation(tmp);
						getb++;
					}
					else {
						mflag = false;
						break;
					}
				}
			}
			if (mflag == true) { // 이동 완료
				for (i = 0; i < getb; i++) { // 다리 건넌 수 만큼 b카드를 얻는다
					this->player[nPlayer].getbCard();
				}
				this->player[nPlayer].setLocation(tmp);
				char card = m.getCard(this->player[nPlayer].getLocation()); // 카드 줍기
				if (card == 'P')
					this->player[nPlayer].getpCard();
				else if (card == 'S' && this->player[nPlayer].getLocation() != 0)
					this->player[nPlayer].getsCard();
				else if (card == 'H')
					this->player[nPlayer].gethCard();
				break;
			}
			else {
				cout << "다시 입력하세요.\n";
			}
		}
	}
	if (this->player[nPlayer].isEnd() == false) { // 골인을 안했다면 이동 후 위치 출력
		cout << "\n이동 후 위치\n" << endl;
		m.showMap(this->player[nPlayer].getLocation());
	}
}