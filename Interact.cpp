#include "Interact.h"

Interact::Interact(int id)
{
	if (id >= 0 && id < 4)
	{
		typeId = id;
	}
	else
	{
		typeId = 0;
	}

	width = 64;
	height = 64;
	objRect.setWidth(width);
	objRect.setHeight(height);

	objImage.load(INTERACT_PATH);
	for (int i = 0; i < 4; i++)
	{
		interact64[i] = objImage.copy(typeId * width, i * height, width, height);
	}
	AnimotionId = 0;
	Out = interact64[AnimotionId];
}

Interact::~Interact()
{
}

int Interact::getId()
{
	return typeId;
}

void Interact::updateAnimo()
{
	if (isEnemy)
	{
		AnimotionId = (AnimotionId + 1) % 6;
		Out = enemy[AnimotionId];
	}
	else
	{
		AnimotionId = (AnimotionId + 1) % 4;
		Out = interact64[AnimotionId];
	}
}

void Interact::switchToEnemy()
{
	if (typeId == 1)
	{
		isEnemy = true;
		width = 128;
		height = 128;
		objRect.setWidth(width);
		objRect.setHeight(height);
		AnimotionId = 0;

		objImage.load(ENEMY_PATH);
		for (int i = 0; i < 6; i++)
		{
			enemy[i] = objImage.copy(width, i * height, width, height);
		}
		Out = enemy[AnimotionId];
	}
}

QPixmap Interact::getImg()
{
	return Out;
}
