#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <vector>

#include "ui_Game.h"
#include "config.h"
#include "Map.h"
#include "player.h"
#include "Interface.h"
#include "Objects32.h"
#include "Objects64.h"
#include "Island.h"
#include "Ambient64.h"
#include "Interact.h"
#include "RWScore.h"

class Game : public QWidget
{
	Q_OBJECT

public:
	Game(QWidget *parent = nullptr);
	~Game();

	bool isFreshMap = false;
	int MapDrection_X = 0;
	int Score = 0;

	std::vector<Objects32> objects32Lib;
	std::vector<Objects64> objects64Lib;
	std::vector<Island> islandsLib;
	std::vector<Ambient64> ambient64Lib;
	std::vector<Interact> interactLib;

	QTimer m_timer;
	QTimer Animotiom_timer;
	QTimer Cheat_timer;
	QTimer Fly_timer;
	Map m;
	player player0;
	Interface interface;

	void paintEvent(QPaintEvent* event);
	void keyPressEvent(QKeyEvent* event);
	
	int getScore();
	void loadScore();
	void initGame();
	void start();

	template<typename T>
	void addObject(std::vector<T>& objects, int maxObjects, int idRange);
	void addObjects();
	template<typename T>
	void moveObjectsLib(std::vector<T>& objects);
	void AllObjectsMove();
	bool isCollisionObj(QRect in);
	bool isCollisionInteract(QRect in);
	bool isCollisionAll(QRect in);
	void updateObjectsAnimo();
	void deleteUnuseObjects();
	void deleteAll();
	
	template<typename T>
	void deleteObjectsTemplate(std::vector<T>& objects, int mode);
	
	void isHurt();
	void isInteract();

	void gameOver();

private:
	Ui::GameClass ui;
	
};
