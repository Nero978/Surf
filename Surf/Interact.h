#pragma once
#include "Objects.h"
class Interact : public Objects 
{
public:
	QPixmap interact64[4];
	QPixmap enemy[6];
	QPixmap Out;

	bool isEnemy = false;
	int typeId = 0;

	int AnimotionId = 0;

	Interact(int id);
	~Interact();

	int getId();
	void updateAnimo();
	void switchToEnemy();
	QPixmap getImg() override;
};

