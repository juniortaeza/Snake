#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool game_over;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
	game_over = false;
	dir = STOP;
	x = width / 2;
	y = height / 2; //snake head will be centered on map
	fruitX = rand() % width;
	fruitY = rand() % height; //fruit will be spawned randomly on 2D map
}

void Draw() {
	system("cls");
	for (int i = 0; i <= width + 1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i <= width + 1; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			game_over = true;
			break;
		}
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
	case LEFT:
		x--; //direct x coord of snake to left
		break;
	case RIGHT:
		x++; //durect x coord of snake to right
		break;
	case UP:
		y--; //direct y coord of snake up/decrease down
		break;
	case DOWN:
		y++; //direct y coord of snake down/decrease up
		break;
	default:
		break;
	}
	//if (x > width || x < 0 || y > height || y < 0)
	//		game_over = true;

	if (x > width) x = 0; else if (x < 0) x = width - 1;
	if (y > height) x = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			game_over = true;
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main() {
	Setup();
	while (!game_over) {
		Draw();
		Input();
		Logic();
		Sleep(20);
	}
	return 0;
}d