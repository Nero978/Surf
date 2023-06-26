#include "player.h"
#include <QPainter>
#include <QPixmap>
#include "config.h"

player::player(int pid = 0)
{
	
	playerImage.load(GAME_PLAYER);
	boardImage.load(":/assets/images/surfboard64.png");
	m_Rect.setWidth(mWidth);
	m_Rect.setHeight(mHeight);
	
	playerId = pid;
	status = 1;
	animotionId = 0;
	isFly = false;
	isCheat = false;
	x = (WINDOW_WIDTH - mWidth) * 0.5;
	y = PLAYER_Y;
	m_Rect.moveTo(x, y);
	for (int i = 0; i < 13; i++)
	{
		m_Player[i] = playerImage.copy(i * mWidth, playerId * mHeight, mWidth, mHeight);
	}
	Player = m_Player[status];
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_board[i][j] = boardImage.copy(i * mWidth, j * mHeight, mWidth, mHeight);
		}
	}
	Board = m_board[status][animotionId];
}

void player::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
	m_Rect.moveTo(x, y);
}

void player::setPid(int pid)
{
	playerId = pid;
	for (int i = 0; i < 13; i++)
	{
		m_Player[i] = playerImage.copy(i * mWidth, playerId * mHeight, mWidth, mHeight);
	}
	Player = m_Player[status];
}

void player::setStatus(int status_in)
{
	status = status_in;
	Player = m_Player[status];
	Board = m_board[status][animotionId];
}

void player::setSpeed(int speed)
{
	this->speed = speed;
}

void player::setBlood(int blood)
{
	this->blood = blood;
}

void player::updateAnimo()
{
	animotionId = (animotionId + 1) % 3;
	Board = m_board[status][animotionId];
}

QPixmap player::getPlayer()
{
	if (isCheat == true && isFly == false)
	{
		QPixmap newPlayer(Player.size()); // 创建一个透明的Pixmap
		newPlayer.fill(Qt::transparent); // 创建一个透明的Pixmap
		QPainter painter(&newPlayer);
		painter.setOpacity(0.5); // 设置透明度为0.5
		painter.drawPixmap(0, 0, Player); // 在透明的Pixmap上绘制原始图片
		painter.end();
		return newPlayer;
	}
	else
	{
		return Player;
	}
}

QPixmap player::getBoard()
{
	if (isCheat == true && isFly == false)
	{
		QPixmap newBoard(Board.size()); // 创建一个透明的Pixmap
		newBoard.fill(Qt::transparent); // 创建一个透明的Pixmap
		QPainter painter(&newBoard);
		painter.setOpacity(0.5); // 设置透明度为0.5
		painter.drawPixmap(0, 0, Board); // 在透明的Pixmap上绘制原始图片
		painter.end();
		return newBoard;
	}
	else
	{
		return Board;
	}
}

player::~player()
{}
