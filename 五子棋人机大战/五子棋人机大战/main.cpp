#include<iostream>
#include"ChessGame.h"

int main(void)
{
	//�������֣�AI������
	Man man;
	AI ai;
	Chess chess(15,50,52,50);
	//������Ϸ����
	ChessGame game(&man, &ai, &chess);

	game.play();



	return 0;
}