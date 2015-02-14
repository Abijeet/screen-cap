#include "screencapsettings.h"
#include "utility.h"

ScreenCapSettings::ScreenCapSettings()
{
    this->loadMainSettings();
}

/**
 * @brief ScreenCapSettings::loadMainSettings
 * Loads the application's setting.
 */
void ScreenCapSettings::loadMainSettings() {
    QSettings settings(QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
    this->capFilePath = settings.value(FILE_PATH, DEF_FILE_PATH).toString();
    this->capTime = settings.value(CAP_TIME, DEF_CAP_TIME).toInt();
    this->capDimensions = settings.value(CAP_DIMENSIONS, DEF_CAP_DIMENSIONS).toInt();
    this->capIsOn = settings.value(CAP_IS_ON, DEF_CAP_IS_OFF).toInt();
    this->isCapRandom = settings.value(CAP_IS_RANDOM, DEF_CAP_IS_RANDOM).toBool();
    this->minimizeToTray = settings.value(MINIMIZE_TO_TRAY, DEF_MINIMIZE_TO_TRAY).toBool();
    this->startMinimized = settings.value(START_MINIMIZED, DEF_START_MINIMIZED).toBool();
    this->captureOnStartup = settings.value(CAP_STARTUP, DEF_CAP_STARTUP).toBool();
    this->imgFormat = settings.value(CAP_IMG_FORMAT, DEF_IMG_FORMAT).toInt();
    this->imgQuality = settings.value(CAP_IMG_QUALITY, DEF_IMG_QUALITY).toInt();
}

/**
 * @brief ScreenCapSettings::SaveMainSettings
 * Saves the main settings in the registry or a file.
 */
void ScreenCapSettings::SaveMainSettings() {
    QSettings settings(QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(FILE_PATH, this->capFilePath);
    settings.setValue(CAP_TIME, this->capTime);
    settings.setValue(CAP_DIMENSIONS, this->capDimensions);
    settings.setValue(CAP_IS_ON, this->capIsOn);
    settings.setValue(CAP_IS_RANDOM, this->isCapRandom);
    settings.setValue(MINIMIZE_TO_TRAY, this->minimizeToTray);
    settings.setValue(START_MINIMIZED, this->startMinimized);
    settings.setValue(CAP_STARTUP, this->captureOnStartup);
    settings.setValue(CAP_IMG_FORMAT, this->imgFormat);
    settings.setValue(CAP_IMG_QUALITY, this->imgQuality);
}

/**
 * @brief ScreenCapSettings::LoadDefaultValues
 * Load the default values, this is called incase the application settings
 * cannot be loaded.
 */
void ScreenCapSettings::LoadDefaultValues() {
    this->capFilePath = DEF_FILE_PATH;
    this->capTime = DEF_CAP_TIME;    
    this->capDimensions = DEF_CAP_DIMENSIONS;
    this->capIsOn = DEF_CAP_IS_ON;
    this->isCapRandom = DEF_CAP_IS_RANDOM;
    this->minimizeToTray = DEF_MINIMIZE_TO_TRAY;
    this->startMinimized = DEF_START_MINIMIZED;
    this->captureOnStartup = DEF_CAP_STARTUP;
    this->imgFormat = DEF_IMG_FORMAT;
    this->imgQuality = DEF_IMG_QUALITY;
}


void ScreenCapSettings::SaveDefaultSettings() {
    this->loadMainSettings();
    this->SaveMainSettings();
}

bool ScreenCapSettings::ValidateSettings() {
    if(this->capTime == 0) {
        return false;
    }
    return true;
}

// Getters
QString ScreenCapSettings::GetFilePath() {
    return this->capFilePath;
}

int ScreenCapSettings::GetCapDimensions() {
    return this->capDimensions;
}

int ScreenCapSettings::GetCapTime() {
    return this->capTime;
}

int ScreenCapSettings::GetCapIsOn() {
    return this->capIsOn;
}

bool ScreenCapSettings::GetCapIsRandom() {
    return this->isCapRandom;
}

bool ScreenCapSettings::GetMinimizeToTray()
{
    return this->minimizeToTray;
}

bool ScreenCapSettings::GetStartMinimized()
{
    return this->startMinimized;
}

bool ScreenCapSettings::GetCaptureOnStartup()
{
    return this->captureOnStartup;
}

QMap<int, QString> ScreenCapSettings::GetListOfImgFormats()
{
    QMap<int, QString> imgFormats;
    for(int i = 0; i < IMG_FORMATS.length(); ++i) {
        imgFormats[IMG_FORMAT_KEYS[i]] = IMG_FORMATS[i];
    }
    return imgFormats;
}

QMap<int, QString> ScreenCapSettings::GetListOfImgQualities() {
    QMap<int, QString> imgQualities;
    for(int i = 0; i < IMG_QUALITY.length(); ++i) {
        imgQualities[IMG_QUALITY[i]] = IMG_QUALITY_NAME[i];
    }
    return imgQualities;
}

int ScreenCapSettings::GetImgQuality()
{
    return this->imgQuality;
}

QString ScreenCapSettings::GetImgFormat()
{
    if(this->imgFormat == JPG_FORMAT) {
        return "JPG";
    } else if(this->imgFormat == PNG_FORMAT) {
        return "PNG";
    } else {
        return "JPG";
    }
}

// Setters
void ScreenCapSettings::SetFilePath(QString path) {
    this->capFilePath = path;
}

void ScreenCapSettings::SetCapDimensions(int dimensions) {
    this->capDimensions = dimensions;
}

void ScreenCapSettings::SetCapTime(int time) {
    this->capTime = time;
}

void ScreenCapSettings::SetCapIsOn(int isOn) {
    this->capIsOn = isOn;
}

void ScreenCapSettings::SetCapIsRandom(bool isRandom) {
    this->isCapRandom = isRandom;
}

void ScreenCapSettings::SetMinimizeToTray(bool isSet)
{
    this->minimizeToTray = isSet;
}

void ScreenCapSettings::SetStartMinimized(bool isSet)
{
    this->startMinimized = isSet;
}

void ScreenCapSettings::SetCaptureOnStartup(bool isSet)
{
    this->captureOnStartup = isSet;
}

void ScreenCapSettings::SetImgQuality(int quality)
{
    if(quality > 100) {
        quality  = 100;
    } else if(quality <= 0) {
        quality = 1;
    }
    this->imgQuality = quality;
}

void ScreenCapSettings::SetImgFormat(int imgFormat)
{
    this->imgFormat = imgFormat;
}
