#include "Island.h"

Island::Island(int id)
{
	if (id >= 0 && id < 4)
	{
		objId = id;
	}
	else
	{
		objId = 0;
	}

	width = 256;
	height = 128;
	objRect.setWidth(width);
	objRect.setHeight(height);

	objImage.load(ISLANDS_PATH);
	for (int i = 0; i < 4; i++)
	{
		island[i] = objImage.copy(i * width, 0, width, height);
	}
}

Island::~Island()
{
}

QPixmap Island::getImg()
{
	return island[objId];
}
