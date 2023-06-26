#include "Water.h"

//******** Water **********

Water::Water() { waterImage.load(BG_PATH); }

Water::~Water() {}

int Water::getX() { return x; }

int Water::getY() { return y; }

void Water::setX(int x) { this->x = x; }

void Water::setY(int y) { this->y = y; }

QPixmap Water::getWaterImg() { return waterImage; }