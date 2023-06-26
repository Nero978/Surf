#pragma once
#include <QPixmap>
#include "config.h"


class Water
{
private:
	int x = 0, y = 0;
	QPixmap waterImage;

public:
	Water();
	~Water();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	QPixmap getWaterImg();
};

