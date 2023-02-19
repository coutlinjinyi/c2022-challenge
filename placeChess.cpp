#include"function.h"
#include"init.h"

int player = p1;//��������
int chess[N][N];//����
static int chessNum;//��������
int param1 = 0;
int param2 = 0;


#include"function.h"
#include"init.h"
void initChessboard()
{
	setfillcolor(BLACK);
	player = p1;	//Ĭ�Ϻ�������
	for (int i = 0; i < N; i++)//��������
	{
		for (int j = 0; j < N; j++)
		{
			chess[i][j] = blank;
		}
	}
	chessNum = 0;			//������������
}

void drawChessboard()
{
	setlinecolor(BLACK);
	int i;
	for (i = 0; i < N; i++)//����
	{
		line(1 + i * g_wid, 1, 1 + i * g_wid, g_wid * (N - 1));
		line(1, 1 + i * g_wid, g_wid * (N - 1), 1 + i * g_wid);
	}
}


void startGame()
{
	initgraph(width, heigth);//��ʼ������
	setbkcolor(RGB(250, 215, 90));//���ñ���ɫ
	cleardevice();
	drawChessboard();
	initChessboard();
	int c1 = MessageBoxA(0, "�˻�ģʽ", "ģʽ", MB_YESNO | MB_SYSTEMMODAL);
	if (c1 == IDYES)
	{
		param1 = player_AI;
	}
	else
	{
		param1 = player_player;
	}
	int c2 = MessageBoxA(0, "ѡ������", "�Ⱥ���", MB_YESNO | MB_SYSTEMMODAL);
	if (c2 == IDYES)
	{
		param2 = 1;
	}
	else
	{
		param2 = 2;
	}
}

void judgeRestart(int par)
{
	int res;
	if (par == 1)
	{
		if (player == p1)
		{
			res = MessageBoxA(0, "����ʤ,�Ƿ��ؿ���", "�ؿ�", MB_YESNO | MB_SYSTEMMODAL);
			if (res == IDYES)
				restart();
			else
				exitgame();
		}
		else
		{
			res = MessageBoxA(0, "����ʤ,�Ƿ��ؿ���", "�ؿ�", MB_YESNO | MB_SYSTEMMODAL);
			if (res == IDYES)
				restart();
			else
				exitgame();
		}
	}
	else
	{
		res = MessageBoxA(0, "ƽ��,�Ƿ��ؿ���", "�ؿ�", MB_YESNO | MB_SYSTEMMODAL);
		if (res == IDYES)
			restart();
		else
			exitgame();
	}
}

void restart()
{
	initChessboard();
	cleardevice();
	drawChessboard();
	while (1)
	{
		Mouse();
	}
}

void exitgame()
{
	closegraph();
	exit(0);
}
int judgeBlank(int x, int y)
{
	return chess[x][y] ? 0 : 1;
}
void Mouse()//����ƶ�
{
	if (param1 == player_player)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN://�������
				int x1 = coordinate(msg.x);
				int y1 = coordinate(msg.y);
				placePieces(x1, y1);
				break;
			}
		}
	}
	else
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN://�������
				int x1 = coordinate(msg.x);
				int y1 = coordinate(msg.y);
				if (placePieces(x1, y1))
				{
					AIplace();
				}
				break;
			}
		}
	}
}
int boardJudge(int row, int col)//��������
{
	if ((row >= 0 && row < N) && (col >= 0 && col < N))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void AIplace()//AI����
{
	int tra1, ver1, tra2, ver2;
	tra1 = ver1 = tra2 = ver2 = -1;
	int  scorenew1, score1 = 0;
	int  scorenew2, score2 = 0;
	srand((unsigned)time(NULL));
	if (chessNum <= 1)
	{
		srand((unsigned)time(NULL));
		do
		{
			tra1 = rand() % 2 + 6;
			ver1 = rand() % 2 + 6;
		} while (!judgeBlank(tra1, ver1));
		placePieces(tra1, ver1);
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (judgeBlank(i, j))
				{
					scorenew1 = judgeScore(i, j, p1);
					if (score1 < scorenew1)
					{
						score1 = scorenew1;
						tra1 = i;
						ver1 = j;
					}
					scorenew2 = judgeScore(i, j, p2);
					if (score2 < scorenew2)
					{
						score2 = scorenew2;
						tra2 = i;
						ver2 = j;
					}
				}
			}
		}
		if (tra1 == -1 && ver1 == -1 && tra2 == -1 && ver2 == -1)//û�ҵ����Ž� ƽ��
		{
			judgeRestart(2);
		}
		else
		{
			if (chessNum == 3)
			{
				placePieces(tra2, ver2);
			}
			else
			{
				if (score1 > score2)
				{
					placePieces(tra1, ver1);
				}
				else
				{
					placePieces(tra2, ver2);
				}
			}
		}
	}
}
int judgeScore(int x, int y, int p)//���꣬���
{
	int sumscore = 0;
	char w, s, a, d, q, z, e, c;//��������б AI
	int tra, ver;//�Ʒֵ�
	int count1, count2, count3, count4;//�Ʒ� 1�� 2�� 3б�� 4б��
	count1 = count2 = count3 = count4 = 1;
	a = d = w = s = q = z = e = c = 0;
	chess[x][y] = p;      //ģ������

	tra = x, ver = y + 1;//��
	while (chess[tra][ver] == p && boardJudge(tra, ver))
	{
		count1++;
		ver++;
	}
	while (chess[tra][ver] == blank && boardJudge(tra, ver))
	{
		d++;
		ver++;
	}

	tra = x, ver = y - 1;//��
	while (chess[tra][ver] == p && boardJudge(tra, ver))
	{
		count1++;
		ver--;
	}
	while (chess[tra][ver] == blank && boardJudge(tra, ver))
	{
		a++;
		ver--;
	}

	tra = x + 1, ver = y;//��
	while (chess[tra][ver] == p && boardJudge(tra, ver))
	{
		count2++;
		tra++;
	}
	while (chess[tra][ver] == blank && boardJudge(tra, ver))
	{
		s++;
		tra++;
	}

	tra = x - 1, ver = y;//��
	while (chess[tra][ver] == p && boardJudge(tra, ver))
	{
		count2++;
		tra--;
	}
	while (chess[tra][ver] == blank && boardJudge(tra, ver))
	{
		w++;
		tra--;
	}

	tra = x - 1, ver = y + 1;//����
	while (chess[tra][ver] == p && boardJudge(tra, ver))
	{
		count3++;
		ver++;
		tra--;
	}
	while (chess[tra][ver] == blank && boardJudge(tra, ver))
	{
		e++;
		ver++;
		tra--;
	}

	tra = x + 1, ver = y - 1;//����
	while (chess[tra][ver] == p && boardJudge(tra, ver))
	{
		count3++;
		ver--;
		tra++;
	}
	while (chess[tra][ver] == blank && boardJudge(tra, ver))
	{
		z++;
		ver--;
		tra++;
	}

	tra = x + 1, ver = y + 1;//����
	while (chess[tra][ver] == p && boardJudge(tra, ver))
	{
		count4++;
		ver++;
		tra++;
	}
	while (chess[tra][ver] == blank && boardJudge(tra, ver))
	{
		c++;
		ver++;
		tra++;
	}
	tra = x - 1, ver = y - 1;//����
	while (chess[tra][ver] == p && boardJudge(tra, ver))
	{
		count4++;
		ver--;
		tra--;
	}
	while (chess[tra][ver] == blank && boardJudge(tra, ver))
	{
		q++;
		ver--;
		tra--;
	}

	chess[x][y] = blank;


	if (count1 >= 5 || count2 >= 5 || count3 >= 5 || count4 >= 5)//����
	{
		return sumscore = 5000000;
	}

	//˫����
	if ((count1 == 4 && count2 == 4 && a >= 1 && d >= 1 && w >= 1 && s >= 1) ||
		(count1 == 4 && count3 == 4 && a >= 1 && d >= 1 && e >= 1 && z >= 1) ||
		(count1 == 4 && count4 == 4 && a >= 1 && d >= 1 && c >= 1 && q >= 1) ||
		(count2 == 4 && count3 == 4 && w >= 1 && s >= 1 && e >= 1 && z >= 1) ||
		(count2 == 4 && count4 == 4 && w >= 1 && s >= 1 && q >= 1 && c >= 1) ||
		(count3 == 4 && count4 == 4 && e >= 1 && z >= 1 && q >= 1 && c >= 1))
	{
		return sumscore = 5000000;
	}

	//����
	if ((count1 == 4 && a >= 1 && d >= 1) || (count2 == 4 && w >= 1 && s >= 1) ||
		(count3 == 4 && e >= 1 && z >= 1) || (count4 == 4 && q >= 1 && c >= 1))
	{
		return sumscore = 1000000;
	}

	//����
	if ((count1 == 4 && ((a == 0 && d >= 1) || (a >= 1 && d == 0)))
		|| (count2 == 4 && ((w == 0 && s >= 1) || (w >= 1 && s == 0)))
		|| (count3 == 4 && ((z == 0 && e >= 1) || (z >= 1 && e == 0)))
		|| (count4 == 4 && ((q == 0 && c >= 1) || (q >= 1 && c == 0))))
	{
		sumscore += 50000;
	}

	//˫����
	if ((count1 == 3 && count2 == 3 && a >= 1 && d >= 1 && w >= 1 && s >= 1) ||
		(count1 == 3 && count3 == 3 && a >= 1 && d >= 1 && e >= 1 && z >= 1) ||
		(count1 == 3 && count4 == 3 && a >= 1 && d >= 1 && c >= 1 && q >= 1) ||
		(count2 == 3 && count3 == 3 && w >= 1 && s >= 1 && e >= 1 && z >= 1) ||
		(count2 == 3 && count4 == 3 && w >= 1 && s >= 1 && q >= 1 && c >= 1) ||
		(count3 == 3 && count4 == 3 && e >= 1 && z >= 1 && q >= 1 && c >= 1))

	{
		return sumscore + 500000;
	}

	//����
	if ((count1 == 3 && a >= 1 && d >= 1) || (count2 == 3 && w >= 1 && s >= 1) ||
		(count3 == 3 && e >= 1 && z >= 1) || (count4 == 3 && q >= 1 && c >= 1))
	{
		sumscore = sumscore + 50000;
		return sumscore;
	}

	//˫���
	if ((count1 == 2 && count2 == 2 && a >= 1 && d >= 1 && w >= 1 && s >= 1) ||
		(count1 == 2 && count3 == 2 && a >= 1 && d >= 1 && e >= 1 && z >= 1) ||
		(count1 == 2 && count4 == 2 && a >= 1 && d >= 1 && c >= 1 && q >= 1) ||
		(count2 == 2 && count3 == 2 && w >= 1 && s >= 1 && e >= 1 && z >= 1) ||
		(count2 == 2 && count4 == 2 && w >= 1 && s >= 1 && q >= 1 && c >= 1) ||
		(count3 == 2 && count4 == 2 && e >= 1 && z >= 1 && q >= 1 && c >= 1))
	{
		sumscore = sumscore + 25000;
	}

	//�����
	if ((count1 == 2 && a >= 1 && d >= 1) || (count2 == 2 && w >= 1 && s >= 1) ||
		(count3 == 2 && e >= 1 && z >= 1) || (count4 == 2 && q >= 1 && c >= 1))
	{
		sumscore = sumscore + 10000;
	}

	//����
	if ((count1 == 3 && ((a == 0 && d >= 1) || (a >= 1 && d == 0)))
		|| (count2 == 3 && ((w == 0 && s >= 1) || (w >= 1 && s == 0)))
		|| (count3 == 3 && ((z == 0 && e >= 1) || (z >= 1 && e == 0)))
		|| (count4 == 3 && ((q == 0 && c >= 1) || (q >= 1 && c == 0))))
	{
		sumscore = sumscore + 5000;
	}
	return sumscore;
}

int coordinate(int x)
{
	int coo = int((double)x / g_wid + 0.5);
	if (coo > 0 && coo < N)
	{
		return coo;
	}
	else
	{
		return -1;
	}
}

int placePieces(int x, int y)//����
{
	if (player == p1)
	{
		setfillcolor(BLACK);
	}
	else
	{
		setfillcolor(WHITE);
	}
	if (judgeBlank(x, y))
	{
		chess[x][y] = player;
		chessNum++;
		solidcircle(x * g_wid, y * g_wid, Chess_R);
		if (judgeWin(x, y))
		{
			judgeRestart(1);
		}
		else
		{
			changeplayer();
		}
		return 1;
	}
	return 0;
}
void changeplayer()//����
{
	player = p1 + p2 - player;
	if (player == p1)
		setfillcolor(BLACK);
	else
		setfillcolor(WHITE);
}
int judgeWin(int x, int y)
{
	int i, j, k;
	const int step[4][2] = { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 1, -1 } };
	for (i = 0; i < 4; ++i)
	{
		const int d[2] = { -1, 1 };
		int count = 1;
		for (j = 0; j < 2; ++j)
			for (k = 1; k <= 4; ++k) {
				int row = x + k * d[j] * step[i][0];
				int col = y + k * d[j] * step[i][1];
				if (row >= 1 && row <= N &&
					col >= 1 && col <= N &&
					chess[x][y] == chess[row][col])
					count += 1;
				else
					break;
			}
		if (count >= 5)
			return 1;
	}
	if (chessNum == N * N)
		judgeRestart(2);

	return 0;
}


