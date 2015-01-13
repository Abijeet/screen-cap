#include "appsettings.h"
#include "ui_appsettings.h"

AppSettings::AppSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppSettings)
{
    ui->setupUi(this);

}

void AppSettings::setupUI(ScreenCapSettings *settings) {
    ui->txtImgHeight->setText(QString::number(settings->GetCapHeight()));
    ui->txtImgWidth->setText(QString::number(settings->GetCapWidth()));
    ui->chkMinimizeToTray->setChecked(settings->GetMinimizeToTray());
    ui->chkStartCapturing->setChecked(settings->GetCaptureOnStartup());
    ui->chkStartMinimized->setChecked(settings->GetStartMinimized());
    ui->ddlImgFormat->addItems(settings->GetListOfImgFormats());
}

ScreenCapSettings* AppSettings::GetUpdatedSettings(ScreenCapSettings *settings) {
    settings->SetCapHeight(ui->txtImgHeight->text().toInt());
    settings->SetCapWidth(ui->txtImgWidth->text().toInt());
    settings->SetCaptureOnStartup(ui->chkStartCapturing->isChecked());
    settings->SetMinimizeToTray(ui->chkMinimizeToTray->isChecked());
    settings->SetStartMinimized(ui->chkStartMinimized->isChecked());
    return settings;
}

AppSettings::~AppSettings()
{
    delete ui;
}
