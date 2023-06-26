#pragma once
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "config.h"

int readScore();
void writeScore(int score);
bool directoryExists(const QString& directoryPath);
bool createDirectory(const QString& directoryPath);