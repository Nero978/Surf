#include "Objects.h"

Objects::Objects()
{
	objRect.setWidth(width);
	objRect.setHeight(height);
}

Objects::~Objects()
{
}

void Objects::MoveTo(int x, int y)
{
	this->x = x;
	this->y = y;
	objRect.moveTo(x, y);
}

void Objects::MoveBy(int x, int y)
{
	this->x += x;
	this->y += y;
	objRect.moveTo(this->x, this->y);
}

void Objects::setId(int id)
{
	objId = id;
}

int Objects::getX()
{
	return x;
}

int Objects::getY()
{
	return y;
}

QPixmap Objects::getImg()
{
	return QPixmap();
}

QRect Objects::getRect()
{
	return objRect;
}
