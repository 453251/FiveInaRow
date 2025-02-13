#pragma once
#include<graphics.h>//easyX图形库
#include<vector>
using namespace std;
//定义枚举变量表示黑子和白子
typedef enum 
{
	CHESS_WHITE = -1,  // 白子
	CHESS_BLACK = 1    // 黑子
} chess_kind_t;

struct ChessPos 
{
	//表示落子坐标
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

class Chess
{
public:
	//构造函数
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	// 棋盘的初始化:加载棋盘的图片资源，初始化棋盘的相关数据
	void init();

	// 判断在指定坐标(x,y)位置，是否是有效点击
	// 如果是有效点击，把有效点击的位置(行，列）保存在参数pos中
	bool clickBoard(int x, int y, ChessPos* pos);

	// 在棋盘的指定位置（pos）, 落子（kind）
	void chessDown(ChessPos* pos, chess_kind_t kind);

	// 获取棋盘的大小
	int getGradeSize();

	// 获取指定位置是黑棋，还是白棋，还是空白
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	// 判断棋局是否结束
	bool checkOver();

	bool checkWin();

private:
	int gradeSize;//棋盘大小
	int margin_x;//棋盘的左侧边界
	int margin_y;//棋盘的顶部边界
	float chessSize;//棋子大小(即方格的大小)
	ChessPos lastPos;
	void updateGameMap(ChessPos* pos);
	
	IMAGE chessBlackImg;//黑子
	IMAGE chessWhiteImg;//白子
	
	//利用向量存储当前落子情况，黑子为1，无子为0，白子为-1
	vector<vector<int>>ChessMap;

	//表示执子方，黑子为true，白子为false
	bool playerFlag;
};

