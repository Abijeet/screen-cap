#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDir>
#include <QTimer>
#include <QDesktopWidget>


class SCUtility;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    this->settings = new ScreenCapSettings();
    ui->txtCaptureTime->setText(QString::number(this->settings->GetCapTime()));
    ui->txtDestinationPath->setText(this->settings->GetFilePath());

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
    if(ui->btnStartCapture->isEnabled()) {
        // Is on
        this->settings->SetCapIsOn(DEF_CAP_IS_ON);
    } else {
        // Is not on
        this->settings->SetCapIsOn(DEF_CAP_IS_OFF);
    }
    this->settings->SaveMainSettings();
}

void MainWindow::on_btnStartCapture_clicked() {
    this->changeStatusCtrls(true);
    this->qSize = new QSize(this->settings->GetCapWidth(),
                            this->settings->GetCapHeight());
    timer->start(this->settings->GetCapTime());
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
    QString foldername = Utility::GetDateTimeInString(FOLDER_DATE_FORMAT);
    QString filepath = this->settings->GetFilePath();
    if(filepath.trimmed().isEmpty() ||
            !Utility::CheckAndCreateFolder(foldername, this->settings->GetFilePath())) {
        // TODO : Show error message box
         emit on_btnStopCapture_clicked();
    }
    QString filename = Utility::GetDateTimeInString(FILE_DATE_FORMAT);
    bool isSuccess =
            this->takeScreenshotAndSave(this->getFullFilePath(filename),
                                             QApplication::desktop()->winId());
    if(isSuccess) {

    } else {

    }
}

QString MainWindow::getFullFilePath(QString filename) {
    QString filePath = this->settings->GetFilePath();
    return QDir::cleanPath(filePath + QDir::separator() + filename);
}

bool MainWindow::takeScreenshotAndSave(QString savePath, int windowId) {
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap originalPixmap = screen->grabWindow(windowId);
    //QPixmap scaledPixmap = originalPixmap.scaled(*(this->qSize), Qt::KeepAspectRatio,Qt::FastTransformation);
    return originalPixmap.save(savePath + ".png", "PNG", 0);
}

