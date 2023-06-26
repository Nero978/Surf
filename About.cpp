#include "About.h"
#include "config.h"

About::About(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	loadAboutVersion();
}

About::~About()
{}

void About::loadAboutVersion()
{
	QString VersionText = QString("Current Version: ") + QString(GAME_VERSION);
	ui.CV->setText(VersionText);
	QFont font;
	font.setPointSize(12);
	font.setBold(true);
	ui.CV->setFont(font);
}

