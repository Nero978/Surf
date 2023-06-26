#pragma once
#include "Objects.h"
#include "config.h"

class Objects32 : public Objects
{
public:
	QPixmap obj32[20];

	Objects32(int id);
	~Objects32();

	QPixmap getImg() override;
};

