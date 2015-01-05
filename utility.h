#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include <QDir>
#include <QDateTime>
#include <QPixmap>
#include <QSize>
#include <QScreen>
#include <QApplication>
#include <QTextStream>
#include "constants.h"

class Utility
{
public:
    static bool CheckAndCreateFolder(QString folder, QString path);
    static QString GetDateTimeInString(QString strFormat = FILE_LOG_DATE_FORMAT);
    static int GetRandomBetween(int max, int min);
    static bool WriteLog(QString filePath, QString message, int line = 0, QString srcfileName = "Unknown");
};

#endif // UTILITY_H
