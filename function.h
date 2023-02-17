#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <graphics.h>


void initChessboard();
void drawChessboard();
void startGame();
int judgeBlank(int x, int y);
int placePieces(int x, int y);
int coordinate(int x);
void Mouse();
int judgeWin(int x, int y);
int boardJudge(int row, int col);
int judgeScore(int x, int y, int p);
void AIplace();
void judgeRestart(int par);
void restart();
void changeplayer();
void exitgame();

