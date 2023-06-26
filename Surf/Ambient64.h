#pragma once
#include "Objects.h"
#include "config.h"

class Ambient64 : public Objects
{
	public:
	QPixmap ambient64[6];
	QPixmap Out;
	int AnimotionId = 0;

	Ambient64(int id);
	~Ambient64();

	void updateAnimo();
	QPixmap getImg() override;
};
