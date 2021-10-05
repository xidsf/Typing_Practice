#include "hwpP.h"

char showingword[100][20];
char compareword[20];
int wordorder, wordquantity, worddifficulty, score;
int locate[100][2];
int wordlocate = 17;
int HELLOPEN;
int speed = 1000;
int difficulty = 3000;
int health = 5;

//난이도별 단어 개수  
const int easy = 10;
const int normal = 15;
const int hard = 20;
const int impossible = 25;
const int hell = 30;
const int EX = 21;
int healthD; //health Difficulty


void UserFileRead()//난이도 저장한 것 읽기 & 덮어쓰거나 추가하기 
{
	char arr[100];
	FILE* fp;
	fp = fopen("UserMode.txt", "r");
	if(fp == NULL)
	{
		fp = fopen("UserMode.txt", "w");
		fprintf(fp, "difficulty= 10\n");
		fprintf(fp, "healthD= 1\n");
		fprintf(fp, "HELLOPEN= 0");
		fclose(fp);
		fp = fopen("UserMode.txt", "r");
	}
	
	fscanf(fp ,"%s %d", arr, &worddifficulty);
	fscanf(fp, "%s %d", arr, &healthD);
	fscanf(fp, "%s %d", arr, &HELLOPEN);
	
	fclose(fp);
}

void FilePrint()//난이도 저장한것 불러오기 
{
	FILE* fp;
	fp = fopen("UserMode.txt", "w");
	fprintf(fp, "difficulty= %d\n", worddifficulty);
	fprintf(fp, "healthD= %d\n", healthD);
	fprintf(fp, "HELLOPEN= %d", HELLOPEN);
	fclose(fp);
}

void Icon()//메인화면에 글자 입력  
{
	int i, j, k;
	
	for(i = 0; i < 13; i++)
	{
		for(j = 0; j < 75; j++)
		{
			if(worddifficulty == EX) setcolor(Green, Black);
			if(i == 0 || i == 12) printf("■");
			else if((j == 0 || j == 74) && i != 0 && i != 12) printf("■");
			else printf("  ");
		}
	}
	for(k = 0; k <6; k++)
	{
		for(i = 0; i < 9; i++)
		{
			gotoxy(25*k + 5, i + 2);
			for(j = 0; j < 8; j++)
			{
				if(k == 0)
				{
					if(worddifficulty == EX)setcolor(k + 1, Black);
					if(Ta[i][j] == 1) printf("■");
					else printf("  ");
				}
				else if(k == 1)
				{
					if(worddifficulty == EX)setcolor(k + 3, Black);
					if(Ja[i][j] == 1) printf("■");
					else printf("  ");
				}
				else if(k == 2)
				{
					if(worddifficulty == EX)setcolor(k + 3, Black);
					if(Yeun[i][j] == 1) printf("■");
					else printf("  ");
				}
				else if(k == 3)
				{
					if(worddifficulty == EX)setcolor(k + 8, Black);
					if(Seup[i][j] == 1) printf("■");
					else printf("  ");
				}
				else if(k == 4)
				{
					if(worddifficulty == EX)setcolor(k + 5, Black);
					if(Ge[i][j] == 1) printf("■");
					else printf("  ");
				}
				else if(k == 5)
				{
					if(worddifficulty == EX)setcolor(k+6, Black);
					if(Im[i][j] == 1) printf("■");
					else printf("  ");
					setcolor(Lgray, Black);
				}
			}
		}
	}
	
	for(i = 0; i < 13; i++)
	{
		gotoxy(60, i + 15);
		for(j = 0; j < 10; j++)
		{
			if(i == 0 || i == 12) printf("■");
			else if((i != 0 && i != 12) && j == 0 || j ==9)printf("■");
			else printf("  ");
		}
	}
}

int Start()//메인 화면 화살표 이동
{
	Icon();
	int hit, i;
	int Location = 17;
	
	gotoxy(65, 17);
	printf("Game Start");
	gotoxy(65, 21);
	printf("Game Option");
	gotoxy(65, 25);
	printf("Exit Game"); 
	gotoxy(63, 17);
	printf("▶");
	
	gotoxy(60, 30);
	printf("이동 : →←↑↓방향키");
	gotoxy(60, 31);
	printf("결정키 : ENTER or Z");
	gotoxy(60, 32);
	printf("취소키 : ESC or X");
	gotoxy(56, 33);
	printf("한영키 누르기 금지(버그있음)");
	
	while(1)//커서 이동 
	{
		for(i = 0; i < 3; i++)
		{
			if(i == 0) setcolor(Red, Black);
			else if(i == 1) setcolor(Blue, Black);
			else if(i == 2) setcolor(Lgray, Black);
			gotoxy(65, Location);
			if(Location == 17) printf("Game Start");
			else if(Location == 21) printf("Game Option");
			else if(Location == 25) printf("Exit Game");
			Sleep(20);	
		}
		
		if(kbhit())
		{
			hit = getch();
			if(hit == 224)
			{
				hit = getch();
				gotoxy(63, Location);
				printf("  ");
				switch(hit)
				{
					case DOWN:
						Location = Location + 4;
						if(Location == 29) Location = 17;
						break;
					case UP:
						Location = Location - 4;
						if(Location == 13) Location = 25;
						break;
					default:
						printf("bug");
						break;
				}
				gotoxy(63, Location);
				printf("▶");
			}
			else if(hit == ENTER || hit == Z || hit == LZ)
			{
				system("cls");
				return (Location -1)/4 - 3;
			}
		}
	}
}

void Wordclear()//단어 초기화 
{
	int i, j;
	for(i = 0; i < 100 ; i++)
	{
		for(j = 0; j < 20; j++)//화면의 단어들 초기화 
		{
			showingword[i][j] = '\0';
		}
	}
	for(i = 0; i < 100 ; i++)//화면의 단어들의 위치좌표 초기화 
	{
		for(j = 0; j < 2; j++)
		{
			locate[i][j] = 0;
		}
	}
	for(i = 0; i < 20; i++)//입력되어 있는 단어 초기화 
	{
		compareword[i] = '\0';
	}
}

int Timer()//랜덤 단어 출력 및 시간이 지날 때 마다 내려오기 
{
	int i, j;
	TDownend = clock();//단어 생성 속도 
	TSpeedend = clock();//내려오는 속도 
	if(TSpeedend - TSpeedstart >= speed)//내려오기 
	{
		CursorView(0);
		for(i = 0; i < 100; i++)
		{
			if(locate[i][0] != 0)
			{
				if(healthD == 2) setcolor(Lred, Black);
				else if(healthD == 3) setcolor(Red, Black);
				gotoxy(locate[i][0], locate[i][1]);
				printf("                    ");
				locate[i][1]++;
				gotoxy(locate[i][0], locate[i][1]);
				printf("%s", showingword[i]);
				gotoxy(wordlocate, 33);
			}
		}
		TSpeedstart = clock();
		CursorView(1);
	}
	
	if(TDownend - TDownstart >= difficulty)
	{
		CursorView(0);
		if(healthD == 2) setcolor(Lred, Black);
		else if(healthD == 3) setcolor(Red, Black);
		strcpy(showingword[wordorder], word[rand() % WORD]);//랜덤 단어 설정 
		locate[wordorder][0] = (rand() % 100)+ 10;//랜덤 위치 설정 
		gotoxy(locate[wordorder][0], 0);
		printf("%s", showingword[wordorder]);
		gotoxy(wordlocate, 33);
		wordorder++;
		TDownstart = clock();
		CursorView(1);
	}
	setcolor(Lgray, Black);
}

void WriteRecord()//기록 저장 
{
	int i, j, a;
	FILE* fp;
	fp = fopen("scoreboard.txt", "r");
	if(fp == NULL)
	{
		fclose(fp);
		fp = fopen("scoreboard.txt", "w");
		fprintf(fp, "0\n");
		fclose(fp);
		fp = fopen("scoreboard.txt", "r");
	}
	fscanf(fp, "%d", &a);
	
	int record_healthD[a + 1];
	char record_difficulty[a + 1][15];
	int record_score[a + 1];
	
	for(i = 0; i < a; i++)
	{
		fscanf(fp, "%d %s %d", &record_healthD[i], record_difficulty[i], &record_score[i]);
	}
	
	record_healthD[a] = healthD;
	if(worddifficulty == easy) strcpy(record_difficulty[a], "easy");
	else if(worddifficulty == normal) strcpy(record_difficulty[a], "normal");
	else if(worddifficulty == hard) strcpy(record_difficulty[a], "hard");
	else if(worddifficulty == impossible) strcpy(record_difficulty[a], "impossible");
	else if(worddifficulty == hell) strcpy(record_difficulty[a], "HELL");
	record_score[a] = score;
	
	
	for(j = 0; j < a; j++)//버블정렬: 내림차순으로 정렬 
	{
		for(i = 0; i < a - j; i++)
		{
			if(record_score[i] < record_score[i + 1]) 
			{
				swap(&record_healthD[i], &record_healthD[i+1]);//체력감소 스왑 
				swaps(record_difficulty[i], record_difficulty[i+1]);//난이도 스왑 
				swap(&record_score[i], &record_score[i+1]);//점수 스왑 
			}
		}
	}
	
	fclose(fp);
	fp = fopen("scoreboard.txt", "w");
	if(a == 10)
	{
		fprintf(fp, "10\n");
		for(i = 0; i < 10; i++)
		{
			fprintf(fp, "%d %s %d\n", record_healthD[i], record_difficulty[i], record_score[i]);
		}
	}
	else if(a < 10)
	{
		fprintf(fp, "%d\n", a + 1);
		for(i = 0; i < a + 1; i++)
		{
			fprintf(fp, "%d %s %d\n", record_healthD[i], record_difficulty[i], record_score[i]);
		}
	}
	fclose(fp);
}

int Game()//문자 입력 및 확인 
{
	int i, j, key, initialdifficulty;
	int compare = 0;
	int pause = 68;
	char button;
	
	if(worddifficulty == easy)
	{
		score = 0;
		difficulty = 5000;
		speed = 1000;
	}
	else if(worddifficulty == normal) //초기 난이도 
	{
		score = 100;
		difficulty = 3000;
		speed = 800;
	}
	else if(worddifficulty == hard)
	{
		score = 250;
		difficulty = 2500;
		speed = 600;
	}
	else if(worddifficulty == impossible)
	{
		score = 450;
		difficulty = 1500;
		speed = 500;
	}
	else if(worddifficulty == hell)
	{
		score = 750;
		difficulty = 1000;
		speed = 400;
	}
	else if(worddifficulty == EX)
	{
		speed = 100;
		difficulty = 3000;
	}
	initialdifficulty = worddifficulty;
	
	
	START:
	Wordclear();
	gotoxy(0, 30);
	
	for(i = 0; i < 150; i++)
	{
		setcolor(Blue, Black);
		printf("~");
		setcolor(Lgray, Black);
	}
	
	gotoxy(10, 33);
	printf("입력 : ");
	gotoxy(17, 34);
	printf("********************");
	gotoxy(130, 0);
	printf("HP : ");
	for(j = 0; j < health; j++)
	{
		printf("■");
	}
	for(j = 0; j < 5-health ; j++)
	{
		printf("□");
	}
	
	gotoxy(130, 1);
	printf("점수: %d", score);
	gotoxy(130, 2);
	printf("난이도 : ");
	if(worddifficulty == easy) printf("EASY"); 
	else if(worddifficulty == normal) printf("NORMAL");
	else if(worddifficulty == hard) printf("HARD");
	else if(worddifficulty == impossible) 
	{
		setcolor(Yellow, Black);
		printf("IMPOSSIBLE");
		setcolor(Lgray, Black);
	}
	else if(worddifficulty == hell)
	{
		setcolor(Red, Black);
		printf("HELL");
		setcolor(Lgray, Black);
	}
	else if(worddifficulty == EX)
	{
		setcolor(Blue, Black);
		printf("E");
		setcolor(Green, Black);
		printf("X");
		setcolor(Lgray, Black);
	}
	
	TDownstart = clock();
	TSpeedstart = clock();
	CursorView(1);
	gotoxy(17, 33);
	while(1)
	{
		if(kbhit())
		{
			key = getch();
			button = key;
			if(key == ENTER)//엔터키 
			{
				for(i = 0; i < 100; i++)
				{
					compare = strcmp(showingword[i], compareword);//입력단어와 표시되어있는 문자열을 비교 
					if(compare == 0 && showingword[i][0] != '\0')//만약 맞다면 
					{
						printf("\a");
						CursorView(0);
						if(strcmp(showingword[i], "deal with something") == 0) score = score + (10 * healthD);//추가 점수 
						else if(strcmp(showingword[i], "be involved in") == 0) score = score + (10 * healthD);
						else if(strcmp(showingword[i], "at the same time") == 0) score = score + (10 * healthD);
						else if(strcmp(showingword[i], "take part in") == 0) score = score + (10 * healthD);
						else if(strcmp(showingword[i], "instead of") == 0) score = score + (10 * healthD);
						else if(strcmp(showingword[i], "according to") == 0) score = score + (10 * healthD);
						for(j = 0; j < 20; j++)//없앤 단어의 초기화 
						{
							showingword[i][j] = '\0';
						}
						gotoxy(locate[i][0], locate[i][1]);//단어 제거 
						printf("                    ");
						locate[i][0] = 0;
						locate[i][1] = 0;
						score = score + (10 * healthD);//점수 상승 
						wordquantity++;//입력한 단어 갯수 증가 
						gotoxy(130, 1);
						printf("               ");
						gotoxy(130, 1);
						printf("점수: %d", score);
						CursorView(1);
						break;
					}
				}
				for(j = 0; j < 20; j++)
				{
					compareword[j] = '\0';//입력한 단어 없애기 
				}
				wordlocate = 17;
				gotoxy(wordlocate, 33);
				printf("                       ");
				gotoxy(wordlocate, 33);
			}
			else if(key == BACKSPACE && compareword[0] != '\0' && wordlocate >= 18)//백스페이스
			{
				wordlocate--;
				compareword[wordlocate - 17] = '\0';
				gotoxy(wordlocate, 33);
				printf(" ");
				gotoxy(wordlocate, 33);
				if(wordlocate == 16)
				{
					gotoxy(17, 33);
				}
			}
			else if(key == ESC)//일시 정지 
			{
				CursorView(0);
				gotoxy(80, 31);
				setcolor(White, Black);
				printf("PAUSE");
				gotoxy(70, 32);
				printf("CONTINUE");
				gotoxy(90, 32);
				printf("RETURN MENU");
				gotoxy(68, 32);
				printf("▷");
				while(1)//커서이동 
				{
					button = getch();
					if(button == RIGHT || button == LEFT)
					{
						gotoxy(pause, 32);
						printf("  ");
						if(pause == 68) pause = 88;
						else if(pause == 88) pause = 68;
						gotoxy(pause, 32);
						printf("▷");
					}
					else if(button == Z || button == ENTER || button == LZ)
					{
						setcolor(Lgray, Black);
						if(pause == 68)
						{
							CursorView(1);
							gotoxy(80, 31);
							printf("      ");
							gotoxy(70, 32);
							printf("                                ");
							gotoxy(pause, 32);
							printf("  ");
							gotoxy(wordlocate, 33);
							break;
						}
						else if(pause == 88)//게임 나가기 
						{
							pause = 68;
							goto PAUSEEXIT;
						}
					}
				}
			}
			else if(key != BACKSPACE)//단어 입력(백스페이스 입력 방지->백스페이스에 조건이 추가로 있기 때문에) 
			{
				if(compareword[19] == '\0')
				{
					compareword[wordlocate - 17] = button;
					wordlocate++;
					printf("%c", button);
				}
			}
		}
		
		Timer(); // 내려오기+새로운 단어 추가 
		
		if(wordquantity == worddifficulty)//단어를 일정 개수를 막으면 난이도 상승 
		{
			wordorder = 0;
			if(worddifficulty == easy) worddifficulty = normal;
			else if(worddifficulty == normal) worddifficulty = hard;
			else if(worddifficulty == hard) worddifficulty = impossible;
			else if(worddifficulty == impossible) worddifficulty = hell;
			else if(worddifficulty == hell) goto HELLCLEAR;
			else if(worddifficulty == EX) goto EXCLEAR;
			Wordclear();
			if(worddifficulty == normal)
			{
				speed = 800;
				difficulty = 3000;
			}
			else if(worddifficulty == hard)
			{
				speed = 600;
				difficulty = 2500;
			}
			else if(worddifficulty == impossible)
			{
				speed = 500;
				difficulty = 1500;
			}
			else if(worddifficulty == hell)
			{
				speed = 400;
				difficulty = 1000;
			}
			system("cls");
			wordquantity = 0;
			for(i = 0; i < 3; i++)
			{
				CursorView(0);
				gotoxy(70, 15);
				if(worddifficulty == normal) printf("NEXT LEVEL : NORMAL");
				else if(worddifficulty == hard) printf("NEXT LEVEL : HARD");
				else if(worddifficulty == impossible) printf("NEXT LEVEL : IMPOSSIBLE");
				else if(worddifficulty == hell) printf("NEXT LEVEL : HELL");
				Sleep(500);
				gotoxy(70, 15);
				printf("                       ");
				Sleep(500);
			}
			while(1)//Sleep함수 동안 버퍼에 입력된 값 받기 
			{
				if(kbhit())
				{
					getch();
					continue;
				}
				break;
			}
			CursorView(1);
			goto START;//처음으로 돌아가기 
		}
		
		if(worddifficulty == EX && locate[99][1] == 30)//EX모드 게임오버 
		{
			goto GAMEOVER;
		}
		for(i = 0; i < 100; i++)//단어가 맨 밑에 닿았는지 확인 
		{
			if(locate[i][1] == 30)
			{
				CursorView(0);
				for(j = 0; j < 20; j++)//화면의 단어 삭제 후 체력 감소 
				{
					showingword[i][j] = '\0';
				}
				gotoxy(locate[i][0], locate[i][1]);
				printf("                    ");
				locate[i][0] = 0;
				locate[i][1] = 0;
				gotoxy(0, 30);
				for(i = 0; i < 150; i++)
				{
					setcolor(Blue, Black);
					printf("~");
					setcolor(Lgray, Black);
				}
				
				health = health - healthD;
				gotoxy(130, 0);
				printf("HP : ");
				if(health < 0) health = 0;
				if(worddifficulty == EX) health = 5; //EX모드이면 체력 5 유지 
				for(j = 0; j < health; j++)
				{
					printf("■");
				}
				for(j = 0; j < 5-health ; j++)
				{
					printf("□");
				}
				CursorView(1);
				if(health <= 0) 
				{
					goto GAMEOVER;
				}
				gotoxy(wordlocate, 33);
				break;
			}
		}
	}
	
	GAMEOVER://게임오버 
		setcolor(Magenta, Black);
		gotoxy(60, 14);
		printf("□□□□□□□□□□□□□□□");
		gotoxy(60, 15);
		printf("□        Game  Over        □");
		gotoxy(60, 16);
		printf("□□□□□□□□□□□□□□□");
		CursorView(0);
		gotoxy(60, 17);
		printf("Press 'ESC' to exit");
		setcolor(Lgray, Black);
		WriteRecord();
		while(getch() != ESC){
		}
	PAUSEEXIT://일시정지로 나갈 시 
		CursorView(0);
		system("cls");
		Wordclear();
		score = 0;
		health = 5;
		wordquantity = 0;
		wordlocate = 17;
		worddifficulty = initialdifficulty;
		return 0;
	
	HELLCLEAR://HELL난이도 클리어 
		CursorView(0);
		system("cls");
		gotoxy(60, 30);
		setcolor(Magenta, Black);
		gotoxy(60, 14);
		printf("□□□□□□□□□□□□□□□");
		gotoxy(60, 15);
		printf("□        HEll CLEAR        □");
		gotoxy(60, 16);
		printf("□□□□□□□□□□□□□□□");
		CursorView(0);
		gotoxy(60, 17);
		printf("Press 'ESC' to exit");
		while(getch() != ESC){
		}
		setcolor(Lgray, Black);
		wordlocate = 17;
		health = 5;
		HELLOPEN = 1;
		FilePrint();//HELLOPEN기록 저장 
		WriteRecord();//기록 저장 
		system("cls");
		Wordclear();//단어 초기화 
		score = 0;
		wordquantity = 0;
		worddifficulty = initialdifficulty;
		return 0;
	
	EXCLEAR://EX모드 클리어 
		CursorView(0);
		system("cls");
		gotoxy(60, 30);
		setcolor(Blue, Black);
		printf("EX");
		setcolor(Green, Black);
		printf("Clear");
		setcolor(Yellow, Black);
		printf("!!!!!");
		setcolor(White, Black);
		gotoxy(60, 31);
		printf("※EX스테이지는 숨겨진 추가 스테이지 입니다.※");
		gotoxy(60, 32);
		printf("Press 'ESC' to exit");
		while(getch() != ESC){
		}
		wordlocate = 17;
		setcolor(Lgray, Black);
		system("cls");
		wordquantity = 0;
		Wordclear();
		return 0; 
}

void HowToPlay()//GameOption.HowToPlay
{
	int i; 
	gotoxy(0, 30);
	for(i = 0; i < 150; i++)
	{
		printf("~");
	}
	gotoxy(10, 33);
	printf("입력 : ");
	
	gotoxy(10, 10);
	printf("bamboo");
	gotoxy(50, 20);
	printf("deal with something");
	gotoxy(130, 0);
	printf("HP : ■■■■■");
	gotoxy(130, 1);
	printf("점수 : 40"); 
	gotoxy(12, 11);
	setcolor(White, Black);
	printf("↖하늘에서 산성 비(글자)가 떨어집니다.");
	gotoxy(14, 12);
	printf("글자가 바다에 도달하기 전에 입력칸에 글자를 써서 없에주세요"); 
	gotoxy(10, 31);
	printf("ENTER키를 누르면 입력 단어를 확인하고 맞으면 글자가 없어집니다.");
	gotoxy(10, 32);
	printf("버그제보는 gooderic8160@naver.com"); 
	gotoxy(110, 2); 
	printf("점수와 체력바입니다.   ↗");
	gotoxy(90, 3); 
	printf("난이도 설정에서 체력 감소의 정도를 설정할 수 있습니다.");
	
	
	gotoxy(52, 21);
	printf("↖단어는 영단어만 나오고 숙어도 나옵니다.(몇개의 숙어는 점수가 2배입니다.)");
	gotoxy(54, 22);
	printf("오른쪽 위의 체력바가 다 없어지면 게임오버가 됩니다."); 
	setcolor(Lgray, Black); 
	
	getch();
} 

void Makers()//GameOption.Makers
{
	int i;
	double makerstart, makerend;
	int order = 0;
	char egg;
	makerstart = clock();
	printf("아무키나 누르면 Skip"); 
	
	
	while(1)
	{
		if(kbhit())break;
		makerend = clock();
		if(makerend - makerstart >= 200 && makerend - makerstart < 400 & order == 0)
		{
			gotoxy(65, 34); 
			printf("제작자 : xidsf");
			order++;
		}
		else if(makerend - makerstart >= 400 && makerend - makerstart < 600 && order == 1)
		{
			gotoxy(65, 34);
			printf("               ");
			gotoxy(65, 33);
			printf("제작자 : xidsf");
			gotoxy(53, 34);
			printf("[고등학교 때 연습 겸 재미로 만든 게임]");
			order++;
		}
		else if(makerend - makerstart >= 600 && makerend - makerstart < 800 && order == 2) 
		{
			gotoxy(65, 33);
			printf("               ");
			gotoxy(53, 34);
			printf("                                      ");
			gotoxy(65, 32);
			printf("제작자 : xidsf");
			gotoxy(53, 33);
			printf("[고등학교 때 연습 겸 재미로 만든 게임]");
			gotoxy(64, 34); 
			printf("<도움을 준 사람>");
			order++;
		}
		else if(makerend - makerstart >= 800 && makerend - makerstart < 1000 && order == 3) 
		{
			gotoxy(65, 32);
			printf("               ");
			gotoxy(53, 33);
			printf("                                      ");
			gotoxy(64, 34);
			printf("                 ");
			gotoxy(65, 31);
			printf("제작자 : xidsf");
			gotoxy(53, 32);
			printf("[고등학교 때 연습 겸 재미로 만든 게임]");
			gotoxy(64, 33); 
			printf("<도움을 준 사람>");
			gotoxy(50, 34); 
			printf("-이 게임을 플레이 해준 고등학교 친구들 모두-");
			order++;
		}
		else if(order == 4 && makerend - makerstart >= 1000)
		{
			order = 5;
			for(i = 0; i < 31; i++)
			{
				while(1)
				{
					if(kbhit())	goto Escape;

					makerend = clock();
					if(makerend - makerstart >= 200)
					{
						gotoxy(65, 31 - i);
						printf("               ");
						gotoxy(53, 32 - i);
						printf("                                      ");
						gotoxy(64, 33 - i);
						printf("                 ");
						gotoxy(50, 34 - i); 
						printf("                                            ");
						gotoxy(65, 31 - 1 - i);
						printf("제작자 : xidsf");
						gotoxy(53, 32 - 1 - i);
						printf("[고등학교 때 연습 겸 재미로 만든 게임]");
						gotoxy(64, 33 - 1 - i); 
						printf("<도움을 준 사람>");
						gotoxy(50, 34 - 1 - i); 
						printf("-이 게임을 플레이 해준 고등학교 친구들 모두-");
						makerstart = clock();
						break;
					}
				}
			}
		}
		if(order >= 5)
		{
			if(makerend - makerstart >= 200 && makerend - makerstart < 400 && order == 5)
			{
				gotoxy(65, 0);
				printf("               ");
				gotoxy(53, 1);
				printf("                                      ");
				gotoxy(64, 2);
				printf("                 ");
				gotoxy(50, 3); 
				printf("                                            ");
				gotoxy(53, 0);
				printf("[고등학교 때 연습 겸 재미로 만든 게임]");
				gotoxy(64, 1); 
				printf("<도움을 준 사람>");
				gotoxy(50, 2); 
				printf("-이 게임을 플레이 해준 고등학교 친구들 모두-");
				order++;
			}
			else if(makerend - makerstart >= 400 && makerend - makerstart < 600 & order == 6)
			{
				gotoxy(53, 0);
				printf("                                      ");
				gotoxy(64, 1);
				printf("                 ");
				gotoxy(50, 2); 
				printf("                                            ");
				gotoxy(64, 0); 
				printf("<도움을 준 사람>");
				gotoxy(50, 1); 
				printf("-이 게임을 플레이 해준 고등학교 친구들 모두-");
				order++;
			}
			else if(makerend - makerstart >= 600 && makerend - makerstart < 800 & order == 7)
			{
				gotoxy(64, 0);
				printf("                 ");
				gotoxy(50, 1); 
				printf("                                            ");
				gotoxy(50, 0); 
				printf("-이 게임을 플레이 해준 고등학교 친구들 모두-");
				order++;
			}
			else if(makerend - makerstart >= 800 && makerend - makerstart < 1000 & order == 8)
			{
				gotoxy(50, 0); 
				printf("                                            ");
				order++;
			}
			else if(makerend - makerstart >= 1000 && makerend - makerstart < 1200 & order == 9) goto EscapeOut;
		}
	}
	Escape:
		egg = getch();
		if(egg == 64)//@입력시 이스터에그 페이지로 이동 
		{ 
			system("cls");
			gotoxy(50, 10);
			printf("★★★★★Maker`s Secret Room★★★★★★"); 
			gotoxy(59, 15);
			printf("▶");
			gotoxy(63, 15);
			printf("Turn On EX Mode");
			gotoxy(35, 25);
			printf("[EX Mode] : 글자가 매우 빠르게 떨어지면서 체력 감소가 없습니다. ");
			gotoxy(35, 26);
			printf("단, 단어가 100개 이상이 내려오면 게임 오버!");
			if(worddifficulty == EX)
			{
				gotoxy(61, 15);
				setcolor(Blue, Black);
				printf("★");
				gotoxy(63, 15);
				for(i = 1; i <= 12; i++)
				{
					setcolor(i , Black);
					if(i == 1)printf("T");
					else if(i == 2)printf("u");
					else if(i == 3)printf("r");
					else if(i == 4)printf("n ");
					else if(i == 5)printf("O");
					else if(i == 6)printf("n ");
					else if(i == 7)printf("E");
					else if(i == 8)printf("X ");
					else if(i == 9)printf("M");
					else if(i == 10)printf("o");
					else if(i == 11)printf("d");
					else if(i == 12)printf("e");
				}
				setcolor(Lgray, Black);
			}
			while(1)
			{
				egg = getch();
				if(egg == Z || egg == ENTER || egg == LZ)
				{
					gotoxy(63, 15);
					for(i = 1; i <= 12; i++)
					{
						setcolor(i , Black);
						if(i == 1)printf("T");
						else if(i == 2)printf("u");
						else if(i == 3)printf("r");
						else if(i == 4)printf("n ");
						else if(i == 5)printf("O");
						else if(i == 6)printf("n ");
						else if(i == 7)printf("E");
						else if(i == 8)printf("X ");
						else if(i == 9)printf("M");
						else if(i == 10)printf("o");
						else if(i == 11)printf("d");
						else if(i == 12)printf("e");
					}
					
					gotoxy(61, 15);
					setcolor(Blue, Black);
					printf("★");
					setcolor(Lgray, Black); 
					worddifficulty = EX;
				}
				else if(egg == X || egg == ESC || egg == LX) goto EscapeOut;
				
			}
		}
	EscapeOut:
		Sleep(1);
}

void DifficultyOption()//GameOption.DifficultyOption
{
	int i, j, key;
	int locate[2] = {41, 13};
	
	gotoxy(30, 2);
	printf("Game Difficulty Option ---------------------------------------------------------------------------");
	gotoxy(30, 4);
	printf("※[체력 감소 설정] : 체력이 n배로 없어지는 대신 얻는 점수가 n배가 됩니다.");
	gotoxy(30, 5);
	printf("※[초기 난이도 설정] :  난이도를 지나갈 때 얻을 수 있는 최소 점수만 주어지고 난이도를 스킵합니다.");
	gotoxy(43, 7);
	printf("[체력 감소 설정]");
	gotoxy(80, 7);
	printf("[초기 난이도 설정]");
	gotoxy(30, 25);
	printf("[주의]HELL난이도는 초기 난이도로 설정할 수 없습니다.(하지만 왜 있을까요? ^^7 )");
	
	gotoxy(30, 8);
	for(i = 0; i < 40; i++)
	{
		printf("□");
	}
	for(i = 1; i <= 13; i++)
	{
		gotoxy(30, 8 + i);
		for(j = 0; j < 40; j++)
		{
			if(j == 0|| j == 19|| j == 39) printf("□");
			else printf("  ");
		}
	}
	gotoxy(30, 22);
	for(i = 0; i < 40; i++)
	{
		printf("□");
	}
	gotoxy(41, 13);
	printf("▷");
	gotoxy(46, 13);
	printf("체력 감소 X 1");
	gotoxy(46, 15);
	printf("체력 감소 X 2");
	gotoxy(46, 17);
	printf("체력 감소 X 3");
	gotoxy(82, 11);
	printf("EASY");
	gotoxy(82, 13);
	printf("NORMAL");
	gotoxy(82, 15);
	printf("HARD");
	gotoxy(82, 17);
	printf("IMPOSSIBLE");
	gotoxy(82, 19);
	printf("HELL");
	
	gotoxy(43, 11 + (2 * healthD));
	if(healthD == 1)
	{
		printf("☆");
	}
	else if(healthD == 2)
	{
		printf("★");
	}
	else if(healthD == 3)
	{
		setcolor(Red, Black);
		printf("★");
		setcolor(Lgray, Black); 
	}
	
	for(i = 0; i < 5; i++)
	{
		gotoxy(79, 11 + (i*2));
		printf("  ");
	}
	if(worddifficulty == easy)
	{
		gotoxy(79, 11);
		printf("☆");
	}
	else if(worddifficulty == normal)
	{
		gotoxy(79, 13);
		printf("☆");
	}
	else if(worddifficulty == hard)
	{
		gotoxy(79, 15);
		printf("★");
	}
	else if(worddifficulty == impossible)
	{
		gotoxy(79, 17);
		printf("★");
	}
	else if(worddifficulty == hell)
	{
		gotoxy(79, 19);
		setcolor(Red,Black);
		printf("★");
		setcolor(Lgray, Black);
	}
	while(1)
	{
		if(kbhit())
		{
			key = getch();
			if(key == 224)
			{
				key = getch();
				gotoxy(locate[0], locate[1]);
				printf("  ");
				switch(key)
				{
					case UP:
						locate[1] = locate[1] - 2;
						if(locate[0] == 77)
						{
							if(locate[1] == 9) locate[1] = 19;
						}
						else if(locate[0] == 41)
						{
							if(locate[1] == 11) locate[1] = 17;
						}
						break;
						
					case DOWN:
						locate[1] = locate[1] + 2;
						if(locate[0] == 77)
						{
							if(locate[1] == 21) locate[1] = 11;
						}
						else if(locate[0] == 41)
						{
							if(locate[1] == 19) locate[1] = 13;
						}
						break;
					case RIGHT:
						if(locate[0] == 41) locate[0] = 77;
						else if(locate[0] == 77)
						{
							locate[0] = 41;
							if(locate[1] == 11) locate[1] = 13;
							else if(locate[1] == 19) locate[1] = 17;
						}
						break;
					case LEFT:
						if(locate[0] == 41) locate[0] = 77;
						else if(locate[0] == 77)
						{
							locate[0] = 41;
							if(locate[1] == 11) locate[1] = 13;
							else if(locate[1] == 19) locate[1] = 17;
						}
						break;
				}
				gotoxy(locate[0], locate[1]);
				printf("▷");
			}
			if(key == ENTER || key == Z || key == LZ)
			{
				if(locate[0] == 41 && locate[1] == 13) healthD = 1;
				else if(locate[0] == 41 && locate[1] == 15) healthD = 2;
				else if(locate[0] == 41 && locate[1] == 17) healthD = 3;
				if(locate[0] == 77 && locate[1] == 11) worddifficulty = easy;
				else if(locate[0] == 77 && locate[1] == 13) worddifficulty = normal;
				else if(locate[0] == 77 && locate[1] == 15) worddifficulty = hard;
				else if(locate[0] == 77 && locate[1] == 17) worddifficulty = impossible;
				else if(locate[0] == 77 && locate[1] == 19 && HELLOPEN == 1) worddifficulty = hell;
				else if(locate[0] == 77 && locate[1] == 19 && HELLOPEN == 0)
				{
					gotoxy(50, 30);
					setcolor(Red, Black);
					printf("*************해금되지 않았습니다*************"); 
					Sleep(300);
					if(kbhit()) getch();
					gotoxy(50, 30);
					printf("                                             ");
					setcolor(Lgray, Black);
				}
				for(i = 0; i < 3; i++)
				{
					gotoxy(43, 13 + (i*2));
					printf("  ");
				}
				gotoxy(43, 11 + (2 * healthD));
				if(healthD == 1)
				{
					printf("☆");
				}
				else if(healthD == 2)
				{
					printf("★");
				}
				else if(healthD == 3)
				{
					setcolor(Red, Black);
					printf("★");
					setcolor(Lgray, Black); 
				}
				
				
				for(i = 0; i < 5; i++)
				{
					gotoxy(79, 11 + (i*2));
					printf("  ");
				}
				if(worddifficulty == easy)
				{
					gotoxy(79, 11);
					printf("☆");
				}
				else if(worddifficulty == normal)
				{
					gotoxy(79, 13);
					printf("☆");
				}
				else if(worddifficulty == hard)
				{
					gotoxy(79, 15);
					printf("★");
				}
				else if(worddifficulty == impossible)
				{
					gotoxy(79, 17);
					printf("★");
				}
				else if(worddifficulty == hell)
				{
					gotoxy(79, 19);
					setcolor(Red, Black); 
					printf("★");
					setcolor(Lgray, Black);
				}
				FilePrint();
			}
			else if(key == ESC || key == X || key == LX)
			{
				break;
			} 
		}
	} 
}

void ScoreRecord()//점수 파일이 있는지 확인하고 없으면 생성
{
	int i, j, a;
	int healthD[10];
	char difficulty[10][11];
	int score[10];
	
	FILE* fp;
	fp = fopen("scoreboard.txt", "r");
	if(fp == NULL)
	{
		fp = fopen("scoreboard.txt", "w");
		fprintf(fp ,"0");
		gotoxy(60, 30);
		printf("기록이 없습니다.");
		Sleep(500);
		gotoxy(60, 30);
		printf("                "); 
		goto Escape;
	}
	fscanf(fp, "%d", &a);//몇개의 기록이 있는지 확인 
	
	if(a == 0)//기록이 0개면 나감 
	{
		gotoxy(60, 30);
		printf("기록이 없습니다.");
		Sleep(500);
		gotoxy(60, 30);
		printf("                "); 
		goto Escape;
	}
	system("cls"); 
	
	for(i = 0; i < a; i++)
	{
		fscanf(fp, "%d %s %d", &healthD[i], difficulty[i], &score[i]);
	}
	fclose(fp);
	
	for(i = 0; i < a; i++)//화면에 출력 
	{
		gotoxy(60, 5);
		printf("S C O R E   R E C O R D");
		gotoxy(50, 10 + i*2);
		printf("%d등:  X%d배  %s단계  %d점", i + 1, healthD[i], difficulty[i], score[i]);
	}
	
	for(i = 0; i < 35; i++)
	{
		gotoxy(0, i);
		if(i % 2 == 0)
		{
			setcolor(Red, Black);
			printf("★");
			setcolor(Blue, Black);
			printf("☆");
			setcolor(Red, Black);
			printf("★");
			setcolor(Lgray, Black); 
		}
		else
		{
			setcolor(Blue, Black);
			printf("★");
			setcolor(Red, Black);
			printf("☆");
			setcolor(Blue, Black);
			printf("★");
			setcolor(Lgray, Black); 
		}
		gotoxy(144, i);
		if(i % 2 == 0)
		{
			setcolor(Red, Black);
			printf("★");
			setcolor(Blue, Black);
			printf("☆");
			setcolor(Red, Black);
			printf("★");
			setcolor(Lgray, Black); 
		}
		else
		{
			setcolor(Blue, Black);
			printf("★");
			setcolor(Red, Black);
			printf("☆");
			setcolor(Blue, Black);
			printf("★");
			setcolor(Lgray, Black); 
		}
	}
	gotoxy(45, 32);
	printf("등수는 10등까지 저장되며 체력배수, 최고 난이도, 최대점수가 표시됩니다.");
	
	while(1)
	{
		getch();
		Escape:
		fclose(fp); 
		system("cls");
		break;
	}
}

void GameOption()//게임 정보 
{
	int i ,j, key;
	int CS = 12;
	
	Select:
	system("cls"); 
	gotoxy(60, 5);
	printf("Game Option");
	
	gotoxy(50, 10);
	for(i = 0; i < 20; i++)
	{
		printf("□");
	}
	for(i = 1; i <= 9; i++)
	{
		gotoxy(50, 10 +  i);
		for(j = 0; j < 20; j++)
		{
			if(j == 0|| j == 19) printf("□");
			else printf("  ");
		}
	}
	gotoxy(50, 20);
	for(i = 0; i < 20; i++)
	{
		printf("□");
	}
	
	gotoxy(61, 12);
	printf("How to Play");
	gotoxy(61, 14);
	printf("Makers");
	gotoxy(61, 16);
	printf("Difficulty Option");
	gotoxy(61, 18);
	printf("Score Record");
	gotoxy(59, CS);
	printf("▷");
	
	while(1)
	{
		if(kbhit())
		{
			key = getch();
			if(key == 224)
			{
				key = getch();
				switch(key)
				{
					case UP:
						gotoxy(59, CS);
						printf("  ");
						CS = CS - 2;
						if(CS == 10) CS = 18;
						break;
						
					case DOWN:
						gotoxy(59, CS);
						printf("  ");
						CS = CS + 2;
						if(CS == 20) CS = 12;
						break;
				}
				gotoxy(59, CS);
				printf("▷");
			}
			else if(key == ENTER || key == Z || key == LZ)
			{
				switch(CS)
				{
					case 12:
						system("cls");
						HowToPlay();//플레이 방법
						goto Select;
						break;
					case 14:
						system("cls");
						Makers();//만든이 
						goto Select;
						break;
					case 16:
						system("cls");
						DifficultyOption();//초기 난이도 설정 및 체력 감소 설정 옵션 
						goto Select;
						break;
					case 18:
						ScoreRecord(); // 점수 보기 
						goto Select;
						break;
				}
			}
			else if(key == X || key == ESC || key == LX) break;
		}
	}
	system("cls");
}

/*
[추가목록]	
bgm또는 효과음 추가 
*/

int main()
{
	srand(time(NULL));
	int select;
	system("mode con: cols=150 lines=35");
	CursorView(0);
	WordSet();
	UserFileRead();
	system("title English Typing Game");
	while(1)
	{
		select = Start();
		if(select == 1) Game();
		else if(select == 2) GameOption();
		else if(select == 3) break;
	}
	return 0;
}
