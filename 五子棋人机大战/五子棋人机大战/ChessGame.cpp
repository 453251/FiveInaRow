#include "ChessGame.h"

void ChessGame::play()
{
	//初始化棋盘
	chess->init();
	while (1) 
	{
		man->go();
		//如果结束，则开启下一轮对局
		if (chess->checkOver()) 
		{
			//下一轮对局之前先初始化棋盘
			chess->init();
			continue;
		}

		ai->go();
		if (chess->checkOver()) 
		{
			chess->init();
			continue;
		}
		/*man->go();
		//如果结束，则开启下一轮对局
		if (chess->checkOver())
		{
			//下一轮对局之前先初始化棋盘
			chess->init();
			continue;
		}*/
	}
}
ChessGame::ChessGame(Man* man, AI* ai, Chess* chess) 
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	ai->init(chess);
	man->init(chess);
}
