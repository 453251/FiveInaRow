#pragma once
#include"Man.h"
#include"AI.h"
#include"Chess.h"
class ChessGame
{
public:
	//���캯��
	//���ﲻ���ó�ʼ���б�
	ChessGame(Man* man, AI* ai, Chess* chess);
	void play();
	//��ӳ�Ա
private:
	Man* man;
	AI* ai;
	Chess* chess;
};

