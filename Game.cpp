#include "Game.h"
#include <QPainter>
#include <QMessageBox>
#include "Surf.h"

extern int chooseId;

Game::Game(QWidget* parent)
	: QWidget(parent), player0(0)
{
	ui.setupUi(this);
	initGame();
}

Game::~Game()
{}

void Game::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	//��ӡ����
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			painter.drawPixmap(m.getWater(i, j).getX(), m.getWater(i, j).getY(), m.getWater(i, j).getWaterImg());
			//qDebug() << "paint!!!\n" << m.getWater(i,j).getX() << m.getWater(i,j).getY();
		}
	}
	//��ӡ�ϰ���
	for (int i = 0; i < objects32Lib.size(); i++)
	{
		painter.drawPixmap(objects32Lib[i].getX(), objects32Lib[i].getY(), objects32Lib[i].getImg());
	}
	for (int i = 0; i < objects64Lib.size(); i++)
	{
		painter.drawPixmap(objects64Lib[i].getX(), objects64Lib[i].getY(), objects64Lib[i].getImg());
	}
	//��ӡ����
	for (int i = 0; i < islandsLib.size(); i++)
	{
		painter.drawPixmap(islandsLib[i].getX(), islandsLib[i].getY(), islandsLib[i].getImg());
	}
	//��ӡ����
	for (int i = 0; i < ambient64Lib.size(); i++)
	{
		painter.drawPixmap(ambient64Lib[i].getX(), ambient64Lib[i].getY(), ambient64Lib[i].getImg());
	}
	//��ӡ������
	for (int i = 0; i < interactLib.size(); i++)
	{
		painter.drawPixmap(interactLib[i].getX(), interactLib[i].getY(), interactLib[i].getImg());
	}
	//��ӡ���
	painter.drawPixmap(player0.x, player0.y, player0.getBoard());
	painter.drawPixmap(player0.x, player0.y, player0.getPlayer());
	//��ӡѪ��
	for (int i = 0; i < 3; i++)
	{
		painter.drawPixmap(BLOOD_X + i * interface.getWidth(),
			BLOOD_Y, interface.getBlood(player0.blood, i));
	}
	//��ӡ�ٶ�
	for (int i = 0; i < 3; i++)
	{
		painter.drawPixmap(SPEED_X + i * interface.getWidth(),
			SPEED_Y, interface.getSpeed(player0.speed, i));
	}
}

void Game::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_W:
		if (!player0.isFly)
		{
			player0.setStatus(0);
			MapDrection_X = 0;
			isFreshMap = false;
		}
		break;
	case Qt::Key_A:
		MapDrection_X = -1;
		isFreshMap = true;
		if (player0.isFly)
		{
			player0.setStatus(10);
		}
		else
		{
			player0.setStatus(1);
		}
		break;
	case Qt::Key_S:
		player0.setStatus(3);
		MapDrection_X = 0;
		isFreshMap = true;
		break;
	case Qt::Key_D:
		MapDrection_X = 1;
		isFreshMap = true;
		if (player0.isFly)
		{
			player0.setStatus(12);
		}
		else
		{
			player0.setStatus(5);
		}
		break;
	default:
		QWidget::keyPressEvent(event);
		break;
	}
}

int Game::getScore()
{
	return Score / 10;
}

void Game::loadScore()
{
	ui.score->setText(QString::number(getScore()) + QString(" m"));
	ui.score->setAlignment(Qt::AlignCenter);
	QFont font;
	font.setBold(true);
	font.setPointSize(14);
	ui.score->setFont(font);
}

void Game::initGame()
{

	setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	setWindowIcon(QIcon(GAME_ICON));
	setWindowTitle(GAME_NAME);
	loadScore();

	extern int chooseId;
	qDebug() << "SKIN_CHOOSE_ID: " << chooseId << "\n";
	player0.setPid(chooseId);
	player0.setStatus(0);
	player0.setSpeed(MAP_SPEED);
	player0.setBlood(BLOOD);
	player0.isCheat = false;
	player0.isFly = false;

	Animotiom_timer.setInterval(200);//����ˢ��
	connect(&Animotiom_timer, &QTimer::timeout, [=]() {
		player0.updateAnimo();
		updateObjectsAnimo();
		update();
		});
	Animotiom_timer.start();

	m_timer.setInterval(GAME_RATE);//�߼�ˢ��
	connect(&m_timer, &QTimer::timeout, [=]() {
		//����ϰ�
		addObjects();
		//�������ö���
		deleteUnuseObjects();
		//ˢ�µ�ͼ
		if (isFreshMap)
		{
			m.mapMove(-MapDrection_X * player0.speed, -player0.speed);
			AllObjectsMove();
			Score++;
		}
		//ˢ�·���
		loadScore();
		//ˢ������״̬
		isHurt();
		//ˢ�½���
		isInteract();

		update();//�ٶȡ�Ѫ����update����paint�Զ�ˢ��
		});

	/******* �޵�״̬��ʱ�� *******/
	Cheat_timer.setSingleShot(true); // ����Ϊ���δ���ģʽ����ֻ����һ��
	Cheat_timer.setInterval(CHEAT_TIME);
	QObject::connect(&Cheat_timer, &QTimer::timeout, [&]() {
		player0.isCheat = false;
		});

	/******* ����״̬��ʱ�� ******/
	Fly_timer.setSingleShot(true); // ����Ϊ���δ���ģʽ����ֻ����һ��
	Fly_timer.setInterval(FLY_TIME);
	QObject::connect(&Fly_timer, &QTimer::timeout, [&]() {
		player0.isFly = false;
		player0.isCheat = false;
		});
}

void Game::start()
{
	initGame();
	m_timer.start();
	isFreshMap = false;
	player0.isCheat = false;
	Score = 0;
	player0.isFly = false;
}

void Game::AllObjectsMove()
{
	moveObjectsLib(objects32Lib);
	moveObjectsLib(objects64Lib);
	moveObjectsLib(islandsLib);
	moveObjectsLib(ambient64Lib);
	moveObjectsLib(interactLib);
}

template<typename T>
void Game::moveObjectsLib(std::vector<T>& objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i].MoveBy(-MapDrection_X * player0.speed, -player0.speed);
	}
}


void Game::addObjects()
{
	addObject(objects32Lib, MAX_OBJECTS, 20);
	addObject(objects64Lib, MAX_OBJECTS, 30);
	addObject(islandsLib, MAX_OBJECTS, 4);
	addObject(ambient64Lib, MAX_OBJECTS, 4);
	addObject(interactLib, MAX_INTERACT, 4);
}

template<typename T>
void Game::addObject(std::vector<T>& objects, int maxObjects, int idRange)
{
	if (objects.size() >= maxObjects)
	{
		return;
	}

	int id = QRandomGenerator::global()->bounded(idRange);
	int x = QRandomGenerator::global()->bounded(-WINDOW_WIDTH, 2 * WINDOW_WIDTH);
	int y = QRandomGenerator::global()->bounded(0, 2 * WINDOW_HEIGHT);

	if (x >= 0 && x <= WINDOW_WIDTH && y >= 0 && y <= WINDOW_HEIGHT)
	{
		return;
	}

	T obj(id);
	obj.MoveTo(x, y);

	if (!isCollisionAll(obj.getRect()))
	{
		objects.push_back(obj);
	}
}


bool Game::isCollisionObj(QRect in)
{
	int result = false;
	for (int i = 0; i < objects32Lib.size(); i++)
	{
		if (in.intersects(objects32Lib[i].getRect()))
		{
			result = true;
			return result;
		}
	}
	for (int i = 0; i < objects64Lib.size(); i++)
	{
		if (in.intersects(objects64Lib[i].getRect()))
		{
			result = true;
			return result;
		}
	}
	for (int i = 0; i < islandsLib.size(); i++)
	{
		if (in.intersects(islandsLib[i].getRect()))
		{
			result = true;
			return result;
		}
	}
	for (int i = 0; i < ambient64Lib.size(); i++)
	{
		if (in.intersects(ambient64Lib[i].getRect()))
		{
			result = true;
			return result;
		}
	}
	return result;
}

bool Game::isCollisionInteract(QRect in)
{
	for (int i = 0; i < interactLib.size(); i++)
	{
		if (in.intersects(interactLib[i].getRect()))
		{
			return true;
		}
	}
	return false;
}

bool Game::isCollisionAll(QRect in)
{
	bool result = false;
	result = isCollisionObj(in) || isCollisionInteract(in);
	return result;
}

void Game::updateObjectsAnimo()
{
	for (int i = 0; i < ambient64Lib.size(); i++)
	{
		ambient64Lib[i].updateAnimo();
	}
	for (int i = 0; i < interactLib.size(); i++)
	{
		interactLib[i].updateAnimo();
	}
}

void Game::deleteUnuseObjects()
{
	deleteObjectsTemplate(objects32Lib, 0);
	deleteObjectsTemplate(objects64Lib, 0);
	deleteObjectsTemplate(islandsLib, 0);
	deleteObjectsTemplate(ambient64Lib, 0);
	deleteObjectsTemplate(interactLib, 0);
}

void Game::isHurt()
{
	if (!player0.isCheat)
	{
		bool result = false;
		result = isCollisionObj(player0.m_Rect);
		if (result)
		{
			player0.setBlood(player0.blood - 1);
			isFreshMap = false;
			if (player0.blood <= 0)
			{
				gameOver();
			}
			else
			{
				player0.setSpeed(1);
				player0.setStatus(6);
				player0.isCheat = true;
				Cheat_timer.start();
			}
		}
	}
}

void Game::deleteAll()
{
	deleteObjectsTemplate(objects32Lib, 1);
	deleteObjectsTemplate(objects64Lib, 1);
	deleteObjectsTemplate(islandsLib, 1);
	deleteObjectsTemplate(ambient64Lib, 1);
	deleteObjectsTemplate(interactLib, 1);
}

void Game::isInteract()
{
	for (int i = 0; i < interactLib.size(); i++)
	{
		if (player0.m_Rect.intersects(interactLib[i].getRect()))
		{
			switch (interactLib[i].getId())
			{
			case 0://Fly
				player0.isCheat = true;
				player0.isFly = true;
				player0.setSpeed(3);
				player0.setStatus(9);
				Fly_timer.start();
				break;
			case 1://Enemy
				interactLib[i].switchToEnemy();
				player0.setBlood(0);
				gameOver();
				break;
			case 2://Speed
				if (player0.speed < 3)
				{
					player0.setSpeed(player0.speed + 1);
					interactLib.erase(interactLib.begin() + i);
				}
				break;
			case 3://Blood
				if (player0.blood < 3)
				{
					player0.setBlood(player0.blood + 1);
					interactLib.erase(interactLib.begin() + i);
				}
				break;
			}
		}
	}
}

template<typename T>
void Game::deleteObjectsTemplate(std::vector<T>& objects, int mode)
//mode=0����ɾ����mode=1ɾ������
{
	auto it = objects.begin();
	while (it != objects.end())
	{
		if (mode == 1)
		{
			it = objects.erase(it);
		}
		else if (mode == 0)
		{
			if ((*it).getY() < -500)
			{
				it = objects.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

void Game::gameOver()
{
	isFreshMap = false;
	player0.setBlood(0);

	player0.setStatus(7);
	update();//ˢ����ˮ�������㻬��û�ˣ�����������

	m_timer.stop();
	Animotiom_timer.stop();
	int newScore = getScore();
	int oldScore = readScore();
	QString recordText = "";
	if (newScore > oldScore)
	{
		recordText = "[New Record!]";
	}
	QMessageBox::information(this, "Game Over", "Your Score is\n"
		+ QString::number(newScore) + " m" + recordText);
	writeScore(getScore());
	Surf::getpIntence()->show();
	Surf::getpIntence()->welcome();
	deleteAll();
	this->close();
}


