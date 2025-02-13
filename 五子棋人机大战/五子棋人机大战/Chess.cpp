#include "Chess.h"
#include<mmsystem.h>
#include<conio.h>
#pragma comment(lib, "winmm.lib")
Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	//�ó�ʼ���б�̫�鷳��������thisָ��
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	//��������
	playerFlag = CHESS_BLACK;

	//��ChessMap��ʼ��
	//��memset������ʣ���������ѭ��
	for (int i = 0; i < gradeSize; i++) 
	{
		vector<int>row;
		for (int j = 0; j < gradeSize; j++)
		{
			row.push_back(0);
		}
		ChessMap.push_back(row);
	}
}
void Chess::init()
{
	initgraph(800, 800);
	loadimage(0, "..\\image\\����.jpg");

	//mciSendString("play res/start.wav", 0, 0, 0); //��Ҫ�޸��ַ���Ϊ���ֽ��ַ���

	loadimage(&chessBlackImg, "..\\image\\black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "..\\image\\white.png", chessSize, chessSize, true);

	for (int i = 0; i < ChessMap.size(); i++) 
	{
		for (int j = 0; j < ChessMap[i].size(); j++) 
		{
			ChessMap[i][j] = 0;
		}
	}

	playerFlag = true;
}
void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}
void Chess::updateGameMap(ChessPos* pos)
{
	lastPos = *pos;
	ChessMap[pos->row][pos->col] = playerFlag ? 1 : -1;
	playerFlag = !playerFlag; // ����
}
bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;

	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_y + chessSize * row;
	int offset = chessSize * 0.4; // 20 �������ģ����������

	int len;
	int selectPos = false;

	do {
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) 
		{
			pos->row = row;
			pos->col = col;
			if (ChessMap[pos->row][pos->col] == 0) 
			{
				selectPos = true;
			}
			break;
		}

		// �������Ͻǵľ���
		len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) 
		{
			pos->row = row;
			pos->col = col + 1;
			if (ChessMap[pos->row][pos->col] == 0) 
			{
				selectPos = true;
			}
			break;
		}

		// �������½ǵľ���
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
		if (len < offset) 
		{
			pos->row = row + 1;
			pos->col = col;
			if (ChessMap[pos->row][pos->col] == 0) 
			{
				selectPos = true;
			}
			break;
		}

		// �������½ǵľ���
		len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
		if (len < offset) 
		{
			pos->row = row + 1;
			pos->col = col + 1;

			if (ChessMap[pos->row][pos->col] == 0) 
			{
				selectPos = true;
			}
			break;
		}
	} while (0);

	return selectPos;

}
void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	mciSendString("play ..\\image\\down7.WAV", 0, 0, 0);

	int x = margin_x + pos->col * chessSize - 0.5 * chessSize;
	int y = margin_y + pos->row * chessSize - 0.5 * chessSize;

	if (kind == CHESS_WHITE) 
	{
		putimagePNG(x, y, &chessWhiteImg);
	}
	else 
	{
		putimagePNG(x, y, &chessBlackImg);
	}
	updateGameMap(pos);
}
int Chess::getGradeSize()
{
	return gradeSize;
}
int Chess::getChessData(ChessPos* pos)
{
	return ChessMap[pos->row][pos->col];
}
int Chess::getChessData(int row, int col)
{
	return ChessMap[row][col];
}

bool Chess::checkWin()
{
	// ����б���ִ������ÿ����������ݵ�ǰ�����������5�����ӣ���һ�ַ��Ͼ���Ӯ
	// ˮƽ����
	int row = lastPos.row;
	int col = lastPos.col;

	for (int i = 0; i < 5; i++)
	{
		// ����5��������ƥ��4���ӣ�20�����
		if (col - i >= 0 &&
			col - i + 4 < gradeSize &&
			ChessMap[row][col - i] == ChessMap[row][col - i + 1] &&
			ChessMap[row][col - i] == ChessMap[row][col - i + 2] &&
			ChessMap[row][col - i] == ChessMap[row][col - i + 3] &&
			ChessMap[row][col - i] == ChessMap[row][col - i + 4])
			return true;
	}

	// ��ֱ����(��������4��)
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			ChessMap[row - i][col] == ChessMap[row - i + 1][col] &&
			ChessMap[row - i][col] == ChessMap[row - i + 2][col] &&
			ChessMap[row - i][col] == ChessMap[row - i + 3][col] &&
			ChessMap[row - i][col] == ChessMap[row - i + 4][col])
			return true;
	}

	// ��/"����
	for (int i = 0; i < 5; i++)
	{
		if (row + i < gradeSize &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			// ��[row+i]�У���[col-i]�����ӣ������Ϸ�����4�����Ӷ���ͬ
			ChessMap[row + i][col - i] == ChessMap[row + i - 1][col - i + 1] &&
			ChessMap[row + i][col - i] == ChessMap[row + i - 2][col - i + 2] &&
			ChessMap[row + i][col - i] == ChessMap[row + i - 3][col - i + 3] &&
			ChessMap[row + i][col - i] == ChessMap[row + i - 4][col - i + 4])
			return true;
	}

	// ��\�� ����
	for (int i = 0; i < 5; i++)
	{
		// ��[row+i]�У���[col-i]�����ӣ������·�����4�����Ӷ���ͬ
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			ChessMap[row - i][col - i] == ChessMap[row - i + 1][col - i + 1] &&
			ChessMap[row - i][col - i] == ChessMap[row - i + 2][col - i + 2] &&
			ChessMap[row - i][col - i] == ChessMap[row - i + 3][col - i + 3] &&
			ChessMap[row - i][col - i] == ChessMap[row - i + 4][col - i + 4])
			return true;
	}

	return false;
}
bool Chess::checkOver()
{
	if (checkWin())
	{
		Sleep(1500);
		if (playerFlag == false) 
		{  //����Ӯ�����Ӯ��,��ʱ����Ѿ���ת���ֵ���������
			mciSendString("play ..\\image\\ʤ��.mp3", 0, 0, 0);
			loadimage(0, "..\\image\\ʤ��.jpg");
		}
		else 
		{
			mciSendString("play ..\\image\\ʧ��.mp3", 0, 0, 0);
			loadimage(0, "..\\image\\ʧ��.jpg");
		}

		_getch(); // ����ͷ�ļ� #include <conio.h>
		return true;
	}

	return false;
}


