#define _CRT_SECURE_NO_DEPRECATE 1
#define _CRT_NONSTDC_NO_DEPRECATE 1
//### ��Ŀ���Թ�С��Ϸ������console��
//
//### ����Ҫ��
//
//1. �ڿ���̨����ʾһ���Թ���������ǽ����ҡ����ڵȣ�
//1. ͨ���������Ҽ�������������ߣ�
//1. ����ҵ�����ڣ�����ʾ���Ӯ������Ϸ��

#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include<conio.h>

int main()
{
	SetConsoleTitle(L"maze");
    //�Թ�
    char map[50][50] = {
                "********************",
                "*&   *    **********",
                "* *** *** **********",
                "* *** ***      *****",
                "*   * *O*** ** *****",
                "** ** * *** ** *** *",
                "** ** *     *****  *",
                "** ****** ******* **",
                "**        *       **",
                "**************** ***",
    };
    int i, j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 20; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    //����λ��
    int x = 4;
    int y = 7;//��ʼ
    int a = 1;
    int b = 1;//����
    //�ƶ�
    while (x != a || y != b)
    {
        char ch[1];
        scanf_s("%c", ch, 1);
        ch[0] = getch();
        if (ch[0] == 's')
        {
            if (map[x + 1][y] != '*')
            {
                map[x][y] = ' ';
                x++;
                map[x][y] = 'O';
            }
        }
        if (ch[0] == 'w')
        {
            if (map[x - 1][y] != '*')
            {
                map[x][y] = ' ';
                x--;
                map[x][y] = 'O';
            }
        }
        if (ch[0] == 'a')
        {
            if (map[x][y - 1] != '*')
            {
                map[x][y] = ' ';
                y--;
                map[x][y] = 'O';
            }
        }
        if (ch[0] == 'd')
        {
            if (map[x][y + 1] != '*')
            {
                map[x][y] = ' ';
                y++;
                map[x][y] = 'O';
            }
        }
        system("cls");
        int i, j;
        for (i = 0; i < 10; i++)
        {
            for (j = 0; j < 20; j++)
            {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
    } 
    system("cls");
    puts("ͨ����");
    Sleep(3000);
    return 0;   
}