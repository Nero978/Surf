#include "Objects64.h"

Objects64::Objects64(int id)
{
	if (id >= 0 && id < 30)
	{
		objId = id;
	}
	else
	{
		objId = 0;
	}
	width = 64;
	height = 64;
	objRect.setWidth(width);
	objRect.setHeight(height);

	objImage.load(OBJECTS64_PATH);
	for (int i = 0; i < 30; i++)
	{
		obj64[i] = objImage.copy(i * width, 0, width, height);
	}
}

Objects64::~Objects64()
{
}

QPixmap Objects64::getImg()
{
	return obj64[objId];
}