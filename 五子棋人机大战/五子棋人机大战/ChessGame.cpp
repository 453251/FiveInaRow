#include "ChessGame.h"

void ChessGame::play()
{
	//��ʼ������
	chess->init();
	while (1) 
	{
		man->go();
		//���������������һ�ֶԾ�
		if (chess->checkOver()) 
		{
			//��һ�ֶԾ�֮ǰ�ȳ�ʼ������
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
		//���������������һ�ֶԾ�
		if (chess->checkOver())
		{
			//��һ�ֶԾ�֮ǰ�ȳ�ʼ������
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
