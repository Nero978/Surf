#pragma once
#include "Objects.h"
#include "config.h"

class Island : public Objects
{
public:
	QPixmap island[4];

	Island(int id);
	~Island();

	QPixmap getImg() override;
};

