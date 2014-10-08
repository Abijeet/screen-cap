#include "screencapsettings.h"
#include "utility.h"

ScreenCapSettings::ScreenCapSettings()
{
    this->loadMainSettings();
}

void ScreenCapSettings::loadMainSettings() {
    QSettings settings(QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
    this->capFilePath = settings.value(FILE_PATH, DEF_FILE_PATH).toString();
    this->capTime = settings.value(CAP_TIME, DEF_CAP_TIME).toInt();
    this->capWidth = settings.value(CAP_WIDTH, DEF_CAP_WIDTH).toInt();
    this->capHeight = settings.value(CAP_HEIGHT, DEF_CAP_HEIGHT).toInt();
    this->capIsOn = settings.value(CAP_IS_ON, DEF_CAP_IS_OFF).toInt();
    this->isCapRandom = settings.value(CAP_IS_RANDOM, DEF_CAP_IS_RANDOM).toBool();
}

void ScreenCapSettings::SaveMainSettings() {
    QSettings settings(QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(FILE_PATH, this->capFilePath);
    settings.setValue(CAP_TIME, this->capTime);
    settings.setValue(CAP_HEIGHT, this->capHeight);
    settings.setValue(CAP_WIDTH, this->capWidth);
    settings.setValue(CAP_IS_ON, this->capIsOn);
    settings.setValue(CAP_IS_RANDOM, this->isCapRandom);
}

void ScreenCapSettings::LoadDefaultValues() {
    this->capFilePath = DEF_FILE_PATH;
    this->capTime = DEF_CAP_TIME;
    this->capWidth = DEF_CAP_WIDTH;
    this->capHeight = DEF_CAP_HEIGHT;
    this->capIsOn = DEF_CAP_IS_ON;
    this->isCapRandom = DEF_CAP_IS_RANDOM;
}

void ScreenCapSettings::SaveDefaultSettings() {
    this->loadMainSettings();
    this->SaveMainSettings();
}

bool ScreenCapSettings::ValidateSettings() {
    if(this->capTime == 0 || this->capWidth == 0 || this->capHeight == 0) {
        return false;
    }
    return true;
}

// Getters
QString ScreenCapSettings::GetFilePath() {
    return this->capFilePath;
}

int ScreenCapSettings::GetCapWidth() {
    return this->capWidth;
}

int ScreenCapSettings::GetCapHeight() {
    return this->capHeight;
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

// Setters
void ScreenCapSettings::SetFilePath(QString path) {
    this->capFilePath = path;
}

void ScreenCapSettings::SetCapWidth(int width) {
    this->capWidth = width;
}

void ScreenCapSettings::SetCapHeight(int height) {
    this->capHeight = height;
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
