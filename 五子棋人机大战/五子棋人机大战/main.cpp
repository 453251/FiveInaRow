#include<iostream>
#include"ChessGame.h"

int main(void)
{
	//创建棋手，AI和棋盘
	Man man;
	AI ai;
	Chess chess(15,50,52,50);
	//创建游戏对象
	ChessGame game(&man, &ai, &chess);

	game.play();



	return 0;
}