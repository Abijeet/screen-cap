#ifndef SCREENCAPSETTINGS_H
#define SCREENCAPSETTINGS_H
#include <QSettings>
#include "constants.h"

class ScreenCapSettings
{
public:
    ScreenCapSettings();
    void SaveMainSettings();
    void SaveDefaultSettings();

    // Getters
    QString GetFilePath();
    int GetCapHeight();
    int GetCapWidth();
    int GetCapTime();
    int GetCapIsOn();

    // Setters
    void SetFilePath(QString path);
    void SetCapHeight(int height);
    void SetCapWidth(int width);
    void SetCapTime(int time);
    void SetCapIsOn(int isOn);

private:
    void loadMainSettings();
    void loadDefaultValues();

    int capHeight;
    int capWidth;
    int capIsOn;
    QString capFilePath;
    int capTime;
    QString strGroupName;
};

#endif // SCREENCAPSETTINGS_H
