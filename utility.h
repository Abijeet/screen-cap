#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include <QDir>
#include <QDateTime>
#include <QPixmap>
#include <QSize>
#include <QScreen>
#include <QApplication>

class Utility
{
public:
    static bool CheckAndCreateFolder(QString folder, QString path);
    static QString GetDateTimeInString(QString strFormat);
    static int GetRandomBetween(int max, int min);
};

#endif // UTILITY_H
