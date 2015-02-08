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
    this->addItemsToFormatDdl(ui->ddlImgFormat, settings);
    this->addItemsToQualityDdl(ui->ddlQuality, settings);
}

ScreenCapSettings* AppSettings::GetUpdatedSettings(ScreenCapSettings *settings) {
    settings->SetCapHeight(ui->txtImgHeight->text().toInt());
    settings->SetCapWidth(ui->txtImgWidth->text().toInt());
    settings->SetCaptureOnStartup(ui->chkStartCapturing->isChecked());
    settings->SetMinimizeToTray(ui->chkMinimizeToTray->isChecked());
    settings->SetStartMinimized(ui->chkStartMinimized->isChecked());
    return settings;
}

void AppSettings::addItemsToQualityDdl(QComboBox *cmbBox, ScreenCapSettings *settings)
{
    QMap<int, QString> qQualities = settings->GetListOfImgQualities();
    QMap<int, QString>::iterator i;
    for(i = qQualities.begin(); i != qQualities.end(); ++i) {
        cmbBox->addItem(i.value(), QVariant(i.key()));
    }
}

void AppSettings::addItemsToFormatDdl(QComboBox *cmbBox, ScreenCapSettings *settings)
{
    QMap<int, QString> qFormats = settings->GetListOfImgFormats();
    QMap<int, QString>::iterator i;
    for(i = qFormats.begin(); i != qFormats.end(); ++i) {
        cmbBox->addItem(i.value(), QVariant(i.key()));
    }
}

AppSettings::~AppSettings()
{
    delete ui;
}
