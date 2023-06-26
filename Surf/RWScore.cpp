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

		// 读取原有内容
		QString existingContent;
		if (file.size() > 0) {
			QTextStream in(&file);
			existingContent = in.readAll();
		}

		// 将新的分数记录追加到原有内容之后
		QString newContent = existingContent + QString::number(score) + "\n";

		// 写入新的内容
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
