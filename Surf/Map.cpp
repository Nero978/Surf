#include "Map.h"


Map::Map()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_water[i][j].setX(OriginX(i, j));
			m_water[i][j].setY(OriginY(i, j));
		}
	}
}

Map::~Map()
{}

int Map::OriginX(int i, int j)
{
	return -(WINDOW_WIDTH)+j * WINDOW_WIDTH;
}

int Map::OriginY(int i, int j)
{
	return i * WINDOW_HEIGHT;
}

void Map::mapMove(int x, int y)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_water[i][j].setX(m_water[i][j].getX() + x);
			m_water[i][j].setY(m_water[i][j].getY() + y);
		}
	}
	bool NeedSet = qAbs(m_water[0][1].getX()) >= WINDOW_WIDTH
		|| qAbs(m_water[0][1].getY()) >= WINDOW_HEIGHT;
	if (NeedSet)	
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m_water[i][j].setX(OriginX(i, j));
				m_water[i][j].setY(OriginY(i, j));
			}
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int newX = qAbs(m_water[i][j].getX() - OriginX(i, j)) % WINDOW_WIDTH;
				if (x < 0)
				{
					newX = -newX;
				}
				int newY = qAbs(m_water[i][j].getY() - OriginY(i, j)) % WINDOW_HEIGHT;
				if (y < 0)
				{
					newY = -newY;
				}
				m_water[i][j].setX(m_water[i][j].getX() + newX);
				m_water[i][j].setY(m_water[i][j].getY() + newY);
			}
		}
	}
}

Water Map::getWater(int i, int j)
{
	if (i < 2 && i >= 0 && j < 3 && j >= 0)
	{
		return m_water[i][j];
	}
	else
	{
		return m_water[0][0];
	}
}