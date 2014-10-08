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
    bool ValidateSettings();
    void LoadDefaultValues();

    // Getters
    QString GetFilePath();
    int GetCapHeight();
    int GetCapWidth();
    int GetCapTime();
    int GetCapIsOn();
    bool GetCapIsRandom();

    // Setters
    void SetFilePath(QString path);
    void SetCapHeight(int height);
    void SetCapWidth(int width);
    void SetCapTime(int time);
    void SetCapIsOn(int isOn);
    void SetCapIsRandom(bool isRandom);

private:
    void loadMainSettings();    

    int capHeight;
    int capWidth;
    int capIsOn;
    QString capFilePath;
    int capTime;
    QString strGroupName;
    bool isCapRandom;
};

#endif // SCREENCAPSETTINGS_H
