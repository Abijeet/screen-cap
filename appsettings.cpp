#include "appsettings.h"
#include "ui_appsettings.h"
#include <QMessageBox>

AppSettings::AppSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppSettings)
{
    ui->setupUi(this);

}

void AppSettings::setupUI(ScreenCapSettings *settings) {
    ui->txtImageDimension->setText(QString::number(settings->GetCapDimensions()));
    ui->chkMinimizeToTray->setChecked(settings->GetMinimizeToTray());
    ui->chkStartCapturing->setChecked(settings->GetCaptureOnStartup());
    ui->chkStartMinimized->setChecked(settings->GetStartMinimized());
    this->addItemsToFormatDdl(ui->ddlImgFormat, settings);
    this->addItemsToQualityDdl(ui->ddlQuality, settings);
}

/**
 * @brief AppSettings::GetUpdatedSettings
 * Fetches the updated settings when the user presses the OK button
 * @param settings Current application settings.
 * @return Updated application settings.
 */
ScreenCapSettings* AppSettings::GetUpdatedSettings(ScreenCapSettings *settings) {
    settings->SetCapDimensions(ui->txtImageDimension->text().toInt());
    settings->SetCaptureOnStartup(ui->chkStartCapturing->isChecked());
    settings->SetMinimizeToTray(ui->chkMinimizeToTray->isChecked());
    settings->SetStartMinimized(ui->chkStartMinimized->isChecked());

    int imgQuality = ui->ddlQuality->itemData(ui->ddlQuality->currentIndex()).toInt();
    int imgFormat = ui->ddlImgFormat->itemData(ui->ddlImgFormat->currentIndex()).toInt();
    settings->SetImgFormat(imgFormat);
    settings->SetImgQuality(imgQuality);

    return settings;
}

/**
 * @brief AppSettings::addItemsToQualityDdl
 * Adds items to the quality dropdown and also selects the
 * currently preferred image quality.
 * @param cmbBox Image quality combobox
 * @param settings Application settings
 */
void AppSettings::addItemsToQualityDdl(QComboBox *cmbBox, ScreenCapSettings *settings)
{
    QMap<int, QString> qQualities = settings->GetListOfImgQualities();
    QMap<int, QString>::iterator i;
    int currQuality = settings->GetImgQuality();
    int intIndex = 0;
    int currIndex = -1;
    for(i = qQualities.begin(); i != qQualities.end(); ++i) {
        cmbBox->addItem(i.value(), QVariant(i.key()));
        if(i.key() == currQuality) {
            currIndex = intIndex;
        }
        ++intIndex;
    }
    cmbBox->setCurrentIndex(currIndex);
}

/**
 * @brief AppSettings::addItemsToFormatDdl
 * Adds items to the image format dropdown and also selects the
 * default image
 * @param cmbBox Image format combobox
 * @param settings Application settings.
 */
void AppSettings::addItemsToFormatDdl(QComboBox *cmbBox, ScreenCapSettings *settings)
{
    QMap<int, QString> qFormats = settings->GetListOfImgFormats();
    QMap<int, QString>::iterator i;
    int intIndex = 0;
    int currIndex = -1;
    int currFormat = settings->GetImgFormatInt();
    for(i = qFormats.begin(); i != qFormats.end(); ++i) {
        cmbBox->addItem(i.value(), QVariant(i.key()));
        if(currFormat == i.key()) {
            currIndex = intIndex;
        }
        ++intIndex;
    }
    cmbBox->setCurrentIndex(currIndex);
}

/**
 * @brief AppSettings::done
 * Overriding the base done method to perform validations.
 * If everything is okay, calls the base QDialog::done()
 * to close the dialog.
 * @param result QDialog::result()
 */
void AppSettings::done(int result) {
    if(QDialog::Accepted == result) {
        if(this->checkSettings()) {
            QDialog::done(result);
        } else {

            return;
        }
    } else {
        QDialog::done(result);
        return;
    }
}

/**
 * @brief AppSettings::checkSettings
 * Performs validation on the values entered by the user.
 * @return true if everything is okay, else false.
 */
bool AppSettings::checkSettings() {
    // Validating the dimensions...
    bool isDimensionInt = false;
    QString strDimensions = ui->txtImageDimension->text().trimmed();
    int intDimensions = strDimensions.toInt(&isDimensionInt);
    if(strDimensions.length() != 0 || isDimensionInt) {
        if(intDimensions > MIN_DIMENSION_HEIGHT && intDimensions <= 100) {
            return true;
        }
        this->dimensionError();
        return false;
    }
    this->dimensionError();
    return false;
}

/**
 * @brief AppSettings::dimensionError
 * Clears the textbox and displays a message box
 * when the user enters an incorrect dimension.
 */
void AppSettings::dimensionError() {
    ui->txtImageDimension->setFocus();
    ui->txtImageDimension->setText("");
    QMessageBox msgBox;
    QFont font(DLG_FONT_FAMILY);
    font.setStyleHint(QFont::TypeWriter);
    msgBox.setWindowTitle("Settings Error");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("The dimensions should be between " + QString::number(MIN_DIMENSION_HEIGHT) + " and 100.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setFont(font);
    msgBox.exec();
}

AppSettings::~AppSettings()
{
    delete ui;
}
