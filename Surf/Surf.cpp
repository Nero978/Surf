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
    QFont font; // 创建字体对象
    font.setPointSize(12); // 设置字号大小为12
    ui.hello->setFont(font);// 应用字体到QLabel
}

//初始化窗口
void Surf::initScene()
{
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowIcon(QIcon(GAME_ICON));
    setWindowTitle(GAME_NAME);
    loadVersion();
    welcome();//welcome



    m_timer.setInterval(GAME_RATE);//动画刷新
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
    
    QObject::connect(ui.version, &QPushButton::clicked, [&]() {//展示About页面
        aboutWindow.setWindowIcon(QIcon(GAME_ICON));
        aboutWindow.show();
    });
    QObject::connect(ui.GuideBtn, &QPushButton::clicked, [&]() {//展示About页面
        guideWindow.setWindowIcon(QIcon(GAME_ICON));
        guideWindow.setWindowTitle("Game Guide");
        guideWindow.show();
        });
}

void Surf::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	//打印玩家
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

void Surf::chooseAnimo()//切换角色动画
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

Surf* Surf::pIntence = nullptr; // 初始化静态成员变量为 nullptr
Surf* Surf::getpIntence()
{
	if (Surf::pIntence == nullptr)//如果对象未创建
	{
		Surf::pIntence = new Surf; //创建对象
		return Surf::pIntence;//返回对象
	}
    return Surf::pIntence;//返回对象
}

