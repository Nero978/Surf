#include "RWScore.h"


int readScore()
{
	int maxScore = 0;
	QString LibPath = QDir::toNativeSeparators(LIB_PATH);
	if (!directoryExists(LibPath))
	{
		createDirectory(LibPath);
	}
	QFile file(SCORE_PATH);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in(&file);
		if (in.atEnd())
		{
			maxScore = 0;
		}
		else
		{
			while (!in.atEnd()) {
				QString line = in.readLine();
				int temp = line.toInt();
				if (temp > maxScore)
				{
					maxScore = temp;
				}
			}
		}
		file.close();
		return maxScore;
	}
	else
	{
		return 0;
	}
}

void writeScore(int score)
{
	QString LibPath = QDir::toNativeSeparators(LIB_PATH);
	if (!directoryExists(LibPath))
	{
		createDirectory(LibPath);
	}
	QFile file(SCORE_PATH);
	if (file.open(QIODevice::Append | QIODevice::Text))
	{
		QTextStream out(&file);

		// ��ȡԭ������
		QString existingContent;
		if (file.size() > 0) {
			QTextStream in(&file);
			existingContent = in.readAll();
		}

		// ���µķ�����¼׷�ӵ�ԭ������֮��
		QString newContent = existingContent + QString::number(score) + "\n";

		// д���µ�����
		out << newContent;
		file.close();
	}
}

bool directoryExists(const QString& directoryPath)
{

	QDir dir(directoryPath);
	return dir.exists();
}

bool createDirectory(const QString& directoryPath)
{
	QDir dir;
	return dir.mkpath(directoryPath);
}
