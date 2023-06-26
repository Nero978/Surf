#include "Objects32.h"

Objects32::Objects32(int id)
{
	if (id >= 0 && id < 20)
	{
		objId = id;
	}
	else
	{
		objId = 0;
	}

	width = 32;
	height = 32;
	objRect.setWidth(width);
	objRect.setHeight(height);
	
	objImage.load(OBJECTS32_PATH);
	for (int i = 0; i < 20; i++)
	{
		obj32[i] = objImage.copy(i * width, 0, width, height);
	}
}

Objects32::~Objects32()
{
}

QPixmap Objects32::getImg()
{
	return obj32[objId];
}
