#include "Ambient64.h"

Ambient64::Ambient64(int id)
{
	if (id >= 0 && id < 4)
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

	objImage.load(AMBIENT_PATH);
	for (int i = 0; i < 6; i++)
	{
		ambient64[i] = objImage.copy(objId * width, i * height, width, height);
	}
	AnimotionId = 0;
	Out = ambient64[AnimotionId];
}

Ambient64::~Ambient64()
{
}



void Ambient64::updateAnimo()
{
	AnimotionId = (AnimotionId + 1) % 6;
	Out = ambient64[AnimotionId];
}

QPixmap Ambient64::getImg()
{
	return Out;
}
