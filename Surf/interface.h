#pragma once

#include <QWidget>
#include <QPixmap>
#include "config.h"

class Interface
{
private:
	int width = 24;
	int height = 24;
	QPixmap uiImage;
	QPixmap Blood0;
	QPixmap Blood1;
	QPixmap Speed0;
	QPixmap Speed1;
	QPixmap Blood[3];
	QPixmap Speed[3];

public:
	Interface();
	~Interface();

	int getWidth();
	int getHeight();
	QPixmap getBlood(int blood, int id);
	QPixmap getSpeed(int speed, int id);

};
