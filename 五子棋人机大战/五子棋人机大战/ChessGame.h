#pragma once
#include"Man.h"
#include"AI.h"
#include"Chess.h"
class ChessGame
{
public:
	//构造函数
	//这里不采用初始化列表
	ChessGame(Man* man, AI* ai, Chess* chess);
	void play();
	//添加成员
private:
	Man* man;
	AI* ai;
	Chess* chess;
};

