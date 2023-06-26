#pragma once

#include <QWidget>
#include "ui_Guide.h"

class Guide : public QWidget
{
	Q_OBJECT

public:
	Guide(QWidget *parent = nullptr);
	~Guide();

private:
	Ui::GuideClass ui;
};
