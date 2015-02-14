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
    int GetCapDimensions();
    int GetCapTime();
    int GetCapIsOn();
    bool GetCapIsRandom();
    bool GetMinimizeToTray();
    bool GetStartMinimized();
    bool GetCaptureOnStartup();
    QMap<int, QString> GetListOfImgFormats();
    QMap<int, QString> GetListOfImgQualities();
    int GetImgQuality();
    QString GetImgFormat();

    // Setters
    void SetFilePath(QString path);
    void SetCapTime(int time);
    void SetCapIsOn(int isOn);
    void SetCapIsRandom(bool isRandom);
    void SetMinimizeToTray(bool isSet);
    void SetStartMinimized(bool isSet);
    void SetCaptureOnStartup(bool isSet);
    void SetImgQuality(int quality);
    void SetImgFormat(int imgFormat);
    void SetCapDimensions(int dimensions);

private:
    void loadMainSettings();

    int capDimensions;
    int capIsOn;
    QString capFilePath;
    int capTime;
    int imgQuality;
    int imgFormat;
    QString strGroupName;
    bool isCapRandom;
    bool minimizeToTray;
    bool startMinimized;
    bool captureOnStartup;
};

#endif // SCREENCAPSETTINGS_H
