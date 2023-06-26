#include "Interface.h"


Interface::Interface()
{
	uiImage.load(INTERFACE_PATH);
	width = 24;
	height = 24;
	Blood0 = uiImage.copy(0, 0, width, height);
	Blood1 = uiImage.copy(width, 0, width, height);
	Speed0 = uiImage.copy(0, height, width, height);
	Speed1 = uiImage.copy(width, height, width, height);
	for (int i = 0; i < 3; i++)
	{
		Blood[i] = Blood1;
	}
	for (int i = 0; i < 3; i++)
	{
		Speed[i] = Speed1;
	}
}

Interface::~Interface()
{}

int Interface::getWidth()
{
	return width;
}

int Interface::getHeight()
{
	return height;
}

QPixmap Interface::getBlood(int blood, int id)
{
	for (int i = 0; i < 3; i++)
	{
		if (i < blood)
		{
			Blood[i] = Blood1;
		}
		else
		{
			Blood[i] = Blood0;
		}
	}
	return Blood[id];
}

QPixmap Interface::getSpeed(int speed, int id)
{
	for (int i = 0; i < 3; i++)
	{
		if (i < speed)
		{
			Speed[i] = Speed1;
		}
		else
		{
			Speed[i] = Speed0;
		}
	}
	return Speed[id];
}

