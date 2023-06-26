#pragma once

#include <QPixmap>
#include "config.h"

class Objects
{
public:
	int x = 0;
	int y = 0;
	int objId = 0;
	int width = 32;
	int height = 32;
	QPixmap objImage;
	QRect objRect;
	Objects();
	~Objects();
	void MoveTo(int x, int y);
	void MoveBy(int x, int y);
	void setId(int id);
	int getX();
	int getY();

	virtual QPixmap getImg();

	QRect getRect();
};

