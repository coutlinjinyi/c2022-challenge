#include"function.h"
extern int param2;
int main()
{
	startGame();
	if (param2 == 1)
	{
		while (1)
		{
			Mouse();
		}
	}
	else
	{
		AIplace();
		while (1)
		{
			Mouse();
		}
	}
	return 0;
}
