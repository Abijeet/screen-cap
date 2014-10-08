#include "utility.h"

bool Utility::CheckAndCreateFolder(QString folder, QString path) {
    QString fullFolderPath = QDir::cleanPath(path + QDir::separator() + folder);
    if(!QDir(fullFolderPath).exists()) {
        return QDir().mkdir(fullFolderPath);
    } else {
        return true;
    }
}

int Utility::GetRandomBetween(int min, int max) {
    return rand() % (max - min + 1) + min;
}

QString Utility::GetDateTimeInString(QString strFormat) {
    QDateTime now = QDateTime::currentDateTime();
    return now.toString(strFormat);
}

