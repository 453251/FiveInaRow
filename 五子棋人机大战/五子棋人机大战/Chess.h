#pragma once
#include<graphics.h>//easyXͼ�ο�
#include<vector>
using namespace std;
//����ö�ٱ�����ʾ���ӺͰ���
typedef enum 
{
	CHESS_WHITE = -1,  // ����
	CHESS_BLACK = 1    // ����
} chess_kind_t;

struct ChessPos 
{
	//��ʾ��������
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

class Chess
{
public:
	//���캯��
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	// ���̵ĳ�ʼ��:�������̵�ͼƬ��Դ����ʼ�����̵��������
	void init();

	// �ж���ָ������(x,y)λ�ã��Ƿ�����Ч���
	// �������Ч���������Ч�����λ��(�У��У������ڲ���pos��
	bool clickBoard(int x, int y, ChessPos* pos);

	// �����̵�ָ��λ�ã�pos��, ���ӣ�kind��
	void chessDown(ChessPos* pos, chess_kind_t kind);

	// ��ȡ���̵Ĵ�С
	int getGradeSize();

	// ��ȡָ��λ���Ǻ��壬���ǰ��壬���ǿհ�
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	// �ж�����Ƿ����
	bool checkOver();

	bool checkWin();

private:
	int gradeSize;//���̴�С
	int margin_x;//���̵����߽�
	int margin_y;//���̵Ķ����߽�
	float chessSize;//���Ӵ�С(������Ĵ�С)
	ChessPos lastPos;
	void updateGameMap(ChessPos* pos);
	
	IMAGE chessBlackImg;//����
	IMAGE chessWhiteImg;//����
	
	//���������洢��ǰ�������������Ϊ1������Ϊ0������Ϊ-1
	vector<vector<int>>ChessMap;

	//��ʾִ�ӷ�������Ϊtrue������Ϊfalse
	bool playerFlag;
};

