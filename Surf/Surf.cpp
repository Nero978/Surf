#include "Surf.h"
#include "config.h"
#include "About.h"
#include "RWScore.h"
#include "player.h"
#include <QPainter>
#include <QIcon>
#include <QKeyEvent>
#include <QProcess>
#include <QString>
#include <QDebug>

extern int chooseId;

Surf::Surf(QWidget *parent)
    : QWidget(parent), player0(0)
{
    ui.setupUi(this);
    initScene();
}

Surf::~Surf()
{}

void Surf::welcome()
{
    QString username = QString::fromLocal8Bit(qgetenv("USERNAME"));
    QString welcomeText = "Hello, " + username + 
        "!\nYour highest record: " + QString::number(readScore());
    ui.hello->setText(welcomeText);
    ui.hello->setAcceptDrops(false);
    ui.hello->setAlignment(Qt::AlignCenter);
    QFont font; // �����������
    font.setPointSize(12); // �����ֺŴ�СΪ12
    ui.hello->setFont(font);// Ӧ�����嵽QLabel
}

//��ʼ������
void Surf::initScene()
{
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowIcon(QIcon(GAME_ICON));
    setWindowTitle(GAME_NAME);
    loadVersion();
    welcome();//welcome



    m_timer.setInterval(GAME_RATE);//����ˢ��
    m_timer.start();
    connect(&m_timer, &QTimer::timeout, [=]() {
        if (switchStatus)
        {
            player0.setStatus((player0.status + 1) % 13);
            timerCount++;
            if (timerCount == 13)   
            {
                switchStatus = false;
                timerCount = 0;
            }
        }
        player0.updateAnimo();
        update();
	});
    
    QObject::connect(ui.version, &QPushButton::clicked, [&]() {//չʾAboutҳ��
        aboutWindow.setWindowIcon(QIcon(GAME_ICON));
        aboutWindow.show();
    });
    QObject::connect(ui.GuideBtn, &QPushButton::clicked, [&]() {//չʾAboutҳ��
        guideWindow.setWindowIcon(QIcon(GAME_ICON));
        guideWindow.setWindowTitle("Game Guide");
        guideWindow.show();
        });
}

void Surf::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	//��ӡ���
	painter.drawPixmap(player0.x, player0.y, player0.getBoard());
	painter.drawPixmap(player0.x, player0.y, player0.getPlayer());
}

void Surf::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_A:
        if (player0.playerId == 0)
        {
            player0.setPid(8);
		}
		else
		{
			player0.setPid((player0.playerId - 1) % 9);
        }
        chooseAnimo();
		break;
	case Qt::Key_D:
        player0.setPid((player0.playerId + 1) % 9);
        chooseAnimo();
        //qDebug() << "DDD";
        break;
    case Qt::Key_Return:
	case Qt::Key_Enter:
        qDebug() << "KKK";
        startGame();
        break;
	default:
        //qDebug() << event->key();
        QWidget::keyPressEvent(event);
		break;
	}
}

void Surf::chooseAnimo()//�л���ɫ����
{
    switchStatus = true;
}

void Surf::loadVersion()
{
    QString versionText = QString("Version: ") + GAME_VERSION;
    ui.version->setText(versionText);
}

void Surf::startGame()
{
    qDebug() << "Sart!";
    extern int chooseId;
    chooseId= player0.playerId;
    g.start();
    this->hide();
    g.start();
    g.show();
}

Surf* Surf::pIntence = nullptr; // ��ʼ����̬��Ա����Ϊ nullptr
Surf* Surf::getpIntence()
{
	if (Surf::pIntence == nullptr)//�������δ����
	{
		Surf::pIntence = new Surf; //��������
		return Surf::pIntence;//���ض���
	}
    return Surf::pIntence;//���ض���
}

