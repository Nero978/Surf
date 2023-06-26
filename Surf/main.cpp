#include "Surf.h"
#include "config.h"
#include "player.h"
#include <QtWidgets/QApplication>
#include <QResource>

int chooseId = 0;//玩家皮肤选择ID


int main(int argc, char *argv[])
{
    QResource::registerResource(GAME_RES_PATH);//注册qrc/rcc外部资源文件
    QApplication a(argc, argv);
    Surf w;
    QMediaPlayer* m_player = nullptr;
    QAudioOutput* m_audioOutput = nullptr;
	if (m_player == nullptr)
	{
		m_player = new QMediaPlayer(&w);
		m_audioOutput = new QAudioOutput(&w);
		m_audioOutput->setVolume(50);
		m_player->setAudioOutput(m_audioOutput);
		m_player->setSource(QUrl(BG_MUSIC_PATH));
		m_player->setLoops(-1);
		m_player->play();
		qDebug() << "MUSIC!\n" << "ID: " << m_player;
	}
    w.show();
    return a.exec();
}
