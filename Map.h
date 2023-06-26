#pragma once
#include <QPixmap>
#include "config.h"
#include "Water.h"

class Map
{
public:
	Water m_water[2][3];
	Map();
	~Map();



	int OriginX(int i, int j);
	int OriginY(int i, int j);
	void mapMove(int x, int y);
	Water getWater(int a, int b);
};