#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDir>
#include <QTimer>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

class SCUtility;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    this->settings = new ScreenCapSettings();
    if(!this->settings->ValidateSettings()) {
        if(!this->settingsHasError()) {
            this->close();
            qApp->exit();
        }
    }
    ui->txtCaptureTime->setText(QString::number(this->settings->GetCapTime()));
    ui->txtDestinationPath->setText(this->settings->GetFilePath());
    ui->chkRandomCapture->setChecked(this->settings->GetCapIsRandom());

    this->timer =  new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeToTakeScreenshot()));

    if(this->settings->GetCapIsOn() == DEF_CAP_IS_OFF) {
        // Is not on
        emit on_btnStopCapture_clicked();
    } else {
        // Is on
        emit on_btnStartCapture_clicked();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnSettings_clicked() {
    AppSettings *appSettings = new AppSettings(this);
    appSettings->setupUI(this->settings);
    appSettings->exec();
    if(appSettings->result() == QDialog::Accepted) {
        this->settings = appSettings->GetUpdatedSettings(this->settings);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    this->updateSettings();
    this->settings->SaveMainSettings();
}

void MainWindow::on_btnStartCapture_clicked() {
    this->changeStatusCtrls(true);
    this->updateSettings();
    this->qSize = new QSize(this->settings->GetCapWidth(),
                            this->settings->GetCapHeight());
    timer->start(this->settings->GetCapTime() * 1000);
}

void MainWindow::on_btnStopCapture_clicked()
{
    this->changeStatusCtrls(false);
}

void MainWindow::changeStatusCtrls(bool isStartCapturing = true) {
    if(isStartCapturing) {
        ui->btnStartCapture->setEnabled(false);
        ui->btnStopCapture->setEnabled(true);
        ui->btnSettings->setEnabled(false);
        ui->txtCaptureTime->setEnabled(false);
        ui->txtDestinationPath->setEnabled(false);
    } else {
        ui->btnStartCapture->setEnabled(true);
        ui->btnStopCapture->setEnabled(false);
        ui->btnSettings->setEnabled(true);
        ui->txtCaptureTime->setEnabled(true);
        ui->txtDestinationPath->setEnabled(true);
        this->timer->stop();
        delete this->qSize;
    }
}

void MainWindow::timeToTakeScreenshot() {
    QString fullPath = this->getFullFilePath(Utility::GetDateTimeInString(FILE_DATE_FORMAT));
    if(fullPath.isEmpty()) {
        // TODO : Show error message box regarding
        this->folderCreationError();
        return;
    }
    bool isSuccess =
            this->takeScreenshotAndSave(fullPath,
                    QApplication::desktop()->winId());
    if(isSuccess) {

    } else {

    }
}

QString MainWindow::getFullFilePath(QString filename) {
    QString dateFoldername = Utility::GetDateTimeInString(FOLDER_DATE_FORMAT);
    QString filepath = this->settings->GetFilePath();
    if(filepath.trimmed().isEmpty() ||
            !Utility::CheckAndCreateFolder(dateFoldername, this->settings->GetFilePath())) {
        emit on_btnStopCapture_clicked();
        return "";
    }
    QString filePath = this->settings->GetFilePath();
    return QDir::cleanPath(filePath + QDir::separator() + dateFoldername + QDir::separator() + filename);
}

bool MainWindow::takeScreenshotAndSave(QString savePath, int windowId, QString imageFormat) {
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap originalPixmap = screen->grabWindow(windowId);
    //QPixmap scaledPixmap = originalPixmap.scaled(*(this->qSize), Qt::KeepAspectRatio,Qt::FastTransformation);
    return originalPixmap.save(savePath + "." + imageFormat.toLower(), imageFormat.toUtf8().constData(), 50);
}

void MainWindow::updateSettings() {
    this->settings->SetCapTime(this->ui->txtCaptureTime->text().toInt());
    this->settings->SetFilePath(this->ui->txtDestinationPath->text());
    this->settings->SetCapIsRandom(this->ui->chkRandomCapture->isChecked());
    if(ui->btnStartCapture->isEnabled()) {
        // Is on
        this->settings->SetCapIsOn(DEF_CAP_IS_ON);
    } else {
        // Is not on
        this->settings->SetCapIsOn(DEF_CAP_IS_OFF);
    }
}

void MainWindow::on_btnDestinationBrowser_clicked() {
    ui->txtDestinationPath->setText(QFileDialog::getExistingDirectory(this, tr("Select a directory to save in..."),
        QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks));

}

bool MainWindow::settingsHasError() {
    QMessageBox msgBox;
    msgBox.setText("The settings for the application seem to be invalid.");
    msgBox.setInformativeText("Do you want to restore default settings or close the app?");
    msgBox.setStandardButtons(QMessageBox::RestoreDefaults | QMessageBox::Close );
    msgBox.setDefaultButton(QMessageBox::RestoreDefaults);
    int ret = msgBox.exec();
    if(ret == QMessageBox::RestoreDefaults) {
        this->settings->LoadDefaultValues();
        return true;
    } else if (ret == QMessageBox::Close) {
        return false;
    }
    return false;
}

void MainWindow::folderCreationError() {
    QMessageBox msgBox;
    msgBox.setText("We were unable to create a folder in the destination path.");
    msgBox.setInformativeText("Please ensure that we have read/write permissions to that folder. If the folder is over a network,"
    "ensure that you are connected to it.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
