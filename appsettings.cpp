#include "appsettings.h"
#include "ui_appsettings.h"

AppSettings::AppSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppSettings)
{
    ui->setupUi(this);

}

void AppSettings::setupUI(ScreenCapSettings *settings) {
    ui->txtImgHeight_2->setText(QString::number(settings->GetCapHeight()));
    ui->txtImgWidth->setText(QString::number(settings->GetCapWidth()));
}

ScreenCapSettings* AppSettings::GetUpdatedSettings(ScreenCapSettings *settings) {
    settings->SetCapHeight(ui->txtImgHeight_2->text().toInt());
    settings->SetCapWidth(ui->txtImgWidth->text().toInt());
    return settings;
}

AppSettings::~AppSettings()
{
    delete ui;
}
