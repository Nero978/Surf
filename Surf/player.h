#pragma once
#include <QPixmap>
#include <QRect>
#include "config.h"

class player
{
private:
	QPixmap Player;
	QPixmap Board;
public:
	int speed = MAP_SPEED;
	int blood = 3;
	int playerId = 0;
	int status = 1;
	int animotionId = 0;
	int x,y;
	const int mWidth = 64;
	const int mHeight = 64;
	bool isCheat = false;
	bool isFly = false;

	QPixmap playerImage;
	QPixmap m_Player[13];
	QRect m_Rect;
	QPixmap boardImage;
	QPixmap m_board[13][3];


	player(int pid);
	~player();
	void setPos(int x, int y);
	void setPid(int pid);
	void setStatus(int status);
	void setSpeed(int speed);
	void setBlood(int blood);
	void updateAnimo();
	QPixmap getPlayer();
	QPixmap getBoard();

	
};

