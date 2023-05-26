#include "map.h"

void Map::loadMap(string mapName) {
	ifstream mapFile;
	mapFile.open(mapName);
	if (mapFile.is_open()) {
		cout << "\n" << mapName << " ���� ������ �ҷ��ɴϴ�.\n\n";
		this->initialize(); // ���� �ʱ�ȭ
		char line[10];

		while (mapFile.getline(line, sizeof(line)))
		{
			map[cnt][0] = line[0];
			if (cnt == 0) { // start
				map[cnt][1] = line[2];
				board[coord.x][coord.y] = map[cnt][0];
				coord.n = cnt;
				mapCoord.push_back(coord);
				coord = direction(coord, map[cnt][1]);
			}
			if (map[cnt][0] == 'E') {
				board[coord.x][coord.y] = map[cnt][0];
				coord.n = cnt;
				mapCoord.push_back(coord);
				break;
			}
			else if (map[cnt][0] == 'B')
			{
				map[cnt][1] = line[2];
				map[cnt][2] = line[4];
				map[cnt][3] = (char)(bi + 48); // ���° bridge���� ����
				bi++;
				bridgeB.push_back(cnt);
				board[coord.x][coord.y] = map[cnt][0];
				coord.n = cnt;
				mapCoord.push_back(coord);
				coord = direction(coord, map[cnt][2]);
			}
			else if (map[cnt][0] == 'b')
			{
				map[cnt][1] = line[2];
				map[cnt][2] = line[4];
				board[coord.x][coord.y] = map[cnt][0];
				coord.n = cnt;
				mapCoord.push_back(coord);
				coord = direction(coord, map[cnt][2]);
			}
			else
			{
				if (cnt != 0) {
					map[cnt][1] = line[2];
					map[cnt][2] = line[4];
					board[coord.x][coord.y] = map[cnt][0];
					coord.n = cnt;
					mapCoord.push_back(coord);
					coord = direction(coord, map[cnt][2]);
				}
			}
			cnt++;
		}
		mapFile.close();
		this->setBridge();
	}
	else {
		cout << "\n" << mapName << " ������ �����ϴ�." << endl;
	}
}

void Map::loadMap() {
	ifstream mapFile;
	mapFile.open("default.map.txt");
	if (!mapFile.is_open()) {
		cout << "\n" << "�⺻ ���� ������ �����ϴ�.\n\n������ �����մϴ�.\n";
		exit(1);
	}
	char line[10];

	while (mapFile.getline(line, sizeof(line)))
	{
		map[cnt][0] = line[0];
		if (cnt == 0) { // start
			map[cnt][1] = line[2];
			board[coord.x][coord.y] = map[cnt][0];
			coord.n = cnt;
			mapCoord.push_back(coord);
			coord = direction(coord, map[cnt][1]);
		}
		if (map[cnt][0] == 'E') {
			board[coord.x][coord.y] = map[cnt][0];
			mapCoord.push_back(coord);
			break;
		}
		else if (map[cnt][0] == 'B')
		{
			map[cnt][1] = line[2];
			map[cnt][2] = line[4];
			map[cnt][3] = (char)(bi + 48); // ���° bridge���� ����
			bi++;
			bridgeB.push_back(cnt); // B ��ǥ ����
			board[coord.x][coord.y] = map[cnt][0];
			coord.n = cnt;
			mapCoord.push_back(coord);
			coord = direction(coord, map[cnt][2]);
		}
		else if (map[cnt][0] == 'b')
		{
			map[cnt][1] = line[2];
			map[cnt][2] = line[4];
			board[coord.x][coord.y] = map[cnt][0];
			coord.n = cnt;
			mapCoord.push_back(coord);
			coord = direction(coord, map[cnt][2]);
		}
		else
		{
			if (cnt != 0) {
				map[cnt][1] = line[2];
				map[cnt][2] = line[4];
				board[coord.x][coord.y] = map[cnt][0];
				coord.n = cnt;
				mapCoord.push_back(coord);
				coord = direction(coord, map[cnt][2]);
			}
		}
		cnt++;
	}
	mapFile.close();
	this->setBridge();
}

void Map::setBridge() {
	for (int i = 0; i < bi; i++) {
		int a = mapCoord[bridgeB.at(i)].x;
		int b = mapCoord[bridgeB.at(i)].y;
		int n = mapCoord.size();
		if (board[a][b + 2] == 'b') { // B -> b
			for (int j = 0; j < n; j++) {
				if (mapCoord[j].x == a && mapCoord[j].y == b + 2) {
					bridgeb.push_back(mapCoord[j].n); // b�� ��ǥ bridgeb�� ������� ����
					break;
				}
			}
			board[a][b + 1] = '-';
		}
		else if (board[a][b - 2] == 'b') {
			for (int j = 0; j < n; j++) {
				if (mapCoord[j].x == a && mapCoord[j].y == b - 2) {
					bridgeb.push_back(mapCoord[j].n); // b�� ��ǥ bridgeb�� ������� ����
					break;
				}
			}
			board[a][b - 1] = '-';
		}
	}
}

void Map::showMap(int location) {
	int a = 0, b = 0;
	if (location != -1) {
		a = mapCoord.at(location).x;
		b = mapCoord.at(location).y;
	}
	for (int i = this->u; i < this->d + 1; i++) {
		cout << " ";
		for (int j = 0; j < this->r + 1; j++) {
			if (i == a && j == b) {
				cout << "* ";
			}
			else if (board[i][j] == '\0')
				cout << "  ";
			else
				cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}

Coord Map::direction(Coord c, char d) { 
	if (d == 'U') {
		c.x--;
		if (this->u > c.x)
			this->u = c.x;
	}
	else if (d == 'D') {
		c.x++;
		if (this->d < c.x)
			this->d = c.x;
	}
	else if (d == 'R') {
		c.y++;
		if (this->r < c.y)
			this->r = c.y;
	}
	else
		c.y--;
	return c;
}

int Map::isAvail(char c, int location) { // �̵� �������� ���
	if (location == 0 && c == this->map[location][1])
		return 2;
	else if (c == this->map[location][1])
		return 1;
	else if (c == this->map[location][2])
		return 2;
	else if (this->map[location][0] == 'B') {
		int a = int(this->map[location][3] - 48);
		if ((this->bridgeB.at(a) < this->bridgeb.at(a) && c == 'R') || (this->bridgeB.at(a) > this->bridgeb.at(a) && c == 'L')) // B->b �̰� R �̰ų� b->B �̰� L�̸� �̵� ����
			return 3;
		else
			return 4;
	}
	else
		return 4;
}

int Map::getbLocation(int i) { // �ٸ� �ǳ� �� ��ġ ��ȯ
	int a = int(this->map[i][3] - 48);
	return this->bridgeb.at(a);
}

char Map::getOpposite(int a) { // end�� ���� ������ �ݴ���� ���
	if (map[a][2] == 'U')
		return 'D';
	else if (map[a][2] == 'D')
		return 'U';
	else if (map[a][2] == 'R')
		return 'L';
	else
		return 'R';
}

void Map::initialize() { // map�� ���� �Է¹��� �� �ʱ�ȭ
	for (int i = 0; i < 101; i++) {
		this->map[i][0] = '\0';
		this->map[i][1] = '\0';
		this->map[i][2] = '\0';
		this->map[i][3] = '\0';
	}
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 21; j++) {
			this->board[i][j] = '\0';
		}
	}
	this->coord = { 25,0,0 };
	this->u = 25;
	this->d = 25;
	this->r = 0;
	this->mapCoord.clear();
	this->bridgeB.clear();
	this->bridgeb.clear();
	this->cnt = 0;
	this->bi = 0;
}