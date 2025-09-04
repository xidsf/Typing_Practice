#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13
#define BACKSPACE 8
#define SPACE 32
#define WORD 30
#define Z 122
#define X 120
#define ESC 27
#define SPACEBAR 32
#define LZ 90
#define LX 88

int TDownstart, TDownend, TSpeedstart, TSpeedend;//시간 관련 변수 

enum color4
{
	Black=0,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Brown,
	Lgray,
	Dgray,
	Lblue,
	Lgreen,
	Lcyan,
	Lred,
	Lmagenta,
	Yellow,
	White
};

void setcolor(int txt, int bg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), txt + bg * 16);
}

void gotoxy(int x, int y)
{
    COORD pos={x,y}; //x, y 좌표 설정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //커서 설정
}

void CursorView(char show)//커서숨기기 0이면 숨김, 1이면 보임
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

int Ta[9][8] = 
	{
	{0, 0, 0, 0, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 0, 1, 0},
	{1, 0, 0, 0, 0, 0, 1, 0},
	{1, 0, 0, 0, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 1, 0},
	{1, 0, 0, 0, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 1, 0},
	};
	
int Ja[9][8] = 
	{
	{0, 0, 0, 0, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 0, 1, 0},
	{0, 0, 1, 0, 0, 0, 1, 0},
	{0, 0, 1, 0, 0, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 1, 1},
	{0, 1, 0, 1, 0, 0, 1, 0},
	{1, 0, 0, 0, 1, 0, 1, 0},
	{1, 0, 0, 0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 1, 0}
	};
	
int Yeun[9][8] = 
	{
	{0, 1, 1, 1, 0, 0, 1, 0},
	{1, 0, 0, 0, 1, 1, 1, 0},
	{1, 0, 0, 0, 1, 0, 1, 0},
	{1, 0, 0, 0, 1, 1, 1, 0},
	{0, 1, 1, 1, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 0}
	};
	
int Seup[9][8] = 
	{
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 1, 0, 0, 1, 0, 0},
	{0, 1, 0, 0, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 1, 1},
	{0, 1, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 0}
	};
	
int Ge[9][8] = 
	{
	{0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 1, 0, 1},
	{0, 0, 0, 1, 0, 1, 0, 1},
	{0, 0, 0, 1, 0, 1, 0, 1},
	{0, 0, 0, 1, 1, 1, 0, 1},
	{0, 0, 0, 1, 0, 1, 0, 1},
	{0, 0, 1, 0, 0, 1, 0, 1},
	{0, 0, 1, 0, 0, 1, 0, 1},
	{0, 1, 0, 0, 0, 1, 0, 1}
	};
	
int Im[9][8] = 
	{
	{0, 1, 1, 1, 0, 0, 1, 0},
	{1, 0, 0, 0, 1, 0, 1, 0},
	{1, 0, 0, 0, 1, 0, 1, 0},
	{1, 0, 0, 0, 1, 0, 1, 0},
	{0, 1, 1, 1, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 0}
	};
	
void swap(int* x, int* y)// 숫자 스왑 함수 
{
	int temp;
	
	temp = *x;
	*x = *y;
	*y = temp;
}

void swaps(char name1[15], char name2[15]) //문자열 스왑 함수 
{
	char stemp[15];
	
	strcpy(stemp, name1);
	strcpy(name1, name2);
	strcpy(name2, stemp);
}


char word[WORD][20];

void WordSet()
{
	strcpy(word[0], "according to");
	strcpy(word[1], "bamboo");
	strcpy(word[2], "at least");
	strcpy(word[3], "eventually");
	strcpy(word[4], "deal with something");
	strcpy(word[5], "unfortunately");
	strcpy(word[6], "impressive");
	strcpy(word[7], "chemical");
	strcpy(word[8], "incident");
	strcpy(word[9], "exhale");
	//strcpy(word[9], "Anseonghyun"); //안성현 '삭제'
	strcpy(word[10], "focus on");
	strcpy(word[11], "contribute");
	strcpy(word[12], "be involved in");
	strcpy(word[13], "independence");
	strcpy(word[14], "grocery");
	strcpy(word[15], "at the same time");
	strcpy(word[16], "competitive");
	strcpy(word[17], "available");
	strcpy(word[18], "appreciate");
	strcpy(word[19], "as well as");
	strcpy(word[20], "disappear");
	strcpy(word[21], "harmful");
	strcpy(word[22], "environment");
	strcpy(word[23], "confident");
	strcpy(word[24], "international");
	strcpy(word[25], "advertise");
	strcpy(word[26], "instead of");
	strcpy(word[27], "endangered");
	strcpy(word[28], "take part in");
	strcpy(word[29], "absolutely");
}
