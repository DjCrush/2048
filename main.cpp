#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
using namespace std;
HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursor;

enum Keys { ESCAPE = 27, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80 };
int score;

bool set_number(int a[][4])
{
	bool flag = false;
	int c = 0;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (a[j][i] == 0) c++;
		}
	}
	if (c != 0)
	{
		int x, y;
		do {
			x = rand() % 4;
			y = rand() % 4;
		} while (a[y][x] != 0);
		if (rand() % 100 > 90)
		{
			a[y][x] = 4;
		}
		else
		{
			a[y][x] = 2;
		}
	}
	else
	{
		flag = true;
	}
	return flag;
}

void print(int a[][4])
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			cursor.X = i * 4;
			cursor.Y = j * 2;
			SetConsoleCursorPosition(output, cursor);
			cout << (a[j][i] & 0x7fff) << "   ";
		}
	}
	cursor.X = 40;
	cursor.Y = 5;
	SetConsoleCursorPosition(output, cursor);
	cout << "SCORE = " << score << "   ";
}

void reset(int a[][4])
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			a[j][i] = a[j][i] & 0x7fff;
		}
	}
}

void up(int a[][4])
{
	bool flag;
	do {
		flag = false;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (a[j][i] == a[j + 1][i] && a[j][i] > 0 && a[j][i] < 0x8000)
				{
					a[j][i] = a[j][i] + a[j + 1][i];
					score += a[j][i];
					a[j][i] = a[j][i] | 0x8000;
					a[j + 1][i] = 0;
					flag = true;
				}
				if (a[j][i] == 0 && a[j + 1][i] != 0)
				{
					a[j][i] = a[j + 1][i];
					a[j + 1][i] = 0;
					flag = true;
				}
			}
		}
		print(a);
		Sleep(100);
	} while (flag == true);
	reset(a);
}

void down(int a[][4])
{
	bool flag;
	do {
		flag = false;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 3; j >= 1; j--)
			{
				if (a[j][i] == a[j - 1][i] && a[j][i] > 0 && a[j][i] < 0x8000)
				{
					a[j][i] = a[j][i] + a[j - 1][i];
					score += a[j][i];
					a[j][i] = a[j][i] | 0x8000;
					a[j - 1][i] = 0;
					flag = true;
				}
				if (a[j][i] == 0 && a[j - 1][i] != 0)
				{
					a[j][i] = a[j - 1][i];
					a[j - 1][i] = 0;
					flag = true;
				}
			}
		}
		print(a);
		Sleep(100);
	} while (flag == true);
	reset(a);
}

void left(int a[][4])
{
	bool flag;
	do {
		flag = false;
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (a[j][i] == a[j][i + 1] && a[j][i] > 0 && a[j][i] < 0x8000)
				{
					a[j][i] = a[j][i] + a[j][i + 1];
					score += a[j][i];
					a[j][i] = a[j][i] | 0x8000;
					a[j][i + 1] = 0;
					flag = true;
				}
				if (a[j][i] == 0 && a[j][i + 1] != 0)
				{
					a[j][i] = a[j][i + 1];
					a[j][i + 1] = 0;
					flag = true;
				}
			}
		}
		print(a);
		Sleep(100);
	} while (flag == true);
	reset(a);
}

void right(int a[][4])
{
	bool flag;
	do {
		flag = false;
		for (int j = 0; j < 4; j++)
		{
			for (int i = 3; i >= 1; i--)
			{
				if (a[j][i] == a[j][i - 1] && a[j][i] > 0 && a[j][i] < 0x8000)
				{
					a[j][i] = a[j][i] + a[j][i - 1];
					score += a[j][i];
					a[j][i] = a[j][i] | 0x8000;
					a[j][i - 1] = 0;
					flag = true;
				}
				if (a[j][i] == 0 && a[j][i - 1] != 0)
				{
					a[j][i] = a[j][i - 1];
					a[j][i - 1] = 0;
					flag = true;
				}
			}
		}
		Sleep(100);
		print(a);
	} while (flag == true);
	reset(a);
}

int main()
{
	Keys key_pressed;
	int a[4][4] = { 2 };
	bool game_over = false;
	score = 0;
	game_over = set_number(a);
	print(a);
	while ((key_pressed = static_cast<Keys>(getch())) != ESCAPE || game_over != true)
	{
		switch (key_pressed)
		{
		case LEFT:
		{
			left(a);
			break;
		}
		case DOWN:
		{
			down(a);
			break;
		}
		case RIGHT:
		{
			right(a);
			break;
		}
		case UP:
		{
			up(a);
			break;
		}
		}
		if (key_pressed == UP || key_pressed == DOWN || key_pressed == LEFT || key_pressed == RIGHT)
		{
			game_over == set_number(a);
		}
		print(a);
	}
	return 0;
}
