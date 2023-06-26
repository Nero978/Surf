#pragma once
#include "Objects.h"
#include "config.h"

class Objects64 : public Objects
{
	public:
	QPixmap obj64[30];

	Objects64(int id);
	~Objects64();

	QPixmap getImg() override;
};
