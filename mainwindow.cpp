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
    this->randomTimer = new QTimer(this);

    if(this->settings->GetCapIsOn() == DEF_CAP_IS_ON) {
        // Is not on
        emit on_btnStartCapture_clicked();
    } else {
        // Is on
        emit on_btnStopCapture_clicked();
    }
    // Initialize the actions
    createTrayActions();

    // Add the actions to the tray icon menu
    createTrayIcons();
    if(this->settings->GetStartMinimized()) {
        this->setWindowState(Qt::WindowMinimized);
    }
    trayIcon->setIcon(QIcon(":/img/img/Desktop.png"));
    trayIcon->show();
}

MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @brief MainWindow::on_btnSettings_clicked
 * Fires on the click on the settings button.
 */
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
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }    
}

/**
 * @brief MainWindow::on_btnStartCapture_clicked
 * Fires when the user clicks on the capture button.
 * 1. Changes the status of the application.
 * 2. Calls update settings
 * 3. Sets the image width and height based on the setting.
 * 4. Starts the timer and connects the SLOT to MainWindow::timeToTakeScreenshot()
 */
void MainWindow::on_btnStartCapture_clicked() {
    this->changeStatusCtrls(true);
    this->updateSettings();
    this->setCurrentImgHeightAndWidth();
    this->timer->start(this->settings->GetCapTime() * 1000);
    if(this->settings->GetCapIsRandom()) {
        /******************************************************************
         * 1. Checking if random is set, if so starting the random timer
         * 2. Attaching the screenshot to the random timer
         * 3. Attaching the restart of random timer to the main timer
         ******************************************************************/
        this->randomTimer->start(Utility::GetRandomBetween(1, this->settings->GetCapTime() - 1) * 1000);
        connect(this->randomTimer, SIGNAL(timeout()), this, SLOT(timeToTakeScreenshot()));
        connect(timer, SIGNAL(timeout()), this, SLOT(resetRandomTimer()));
    } else {
        // No random, setting screenshot to random timer.
        connect(timer, SIGNAL(timeout()), this, SLOT(timeToTakeScreenshot()));
    }

}

void MainWindow::on_btnStopCapture_clicked()
{
    this->changeStatusCtrls(false);
}

void MainWindow::changeStatusCtrls(bool isStartCapturing = true) {
    ui->btnStartCapture->setEnabled(!isStartCapturing);
    ui->btnSettings->setEnabled(!isStartCapturing);
    ui->btnDestinationBrowser->setEnabled(!isStartCapturing);
    ui->btnSettings->setEnabled(!isStartCapturing);
    ui->txtCaptureTime->setEnabled(!isStartCapturing);
    ui->txtDestinationPath->setEnabled(!isStartCapturing);
    ui->chkRandomCapture->setEnabled(!isStartCapturing);

    // Stop button is opposite.
    ui->btnStopCapture->setEnabled(isStartCapturing);
    if(!isStartCapturing) {
        this->timer->stop();
    }
}

void MainWindow::timeToTakeScreenshot() {
    if(this->settings->GetCapIsRandom() && this->randomTimer && this->randomTimer->isActive()) {
        this->randomTimer->stop();
    }
    QString fileName = Utility::GetDateTimeInString(FILE_DATE_FORMAT);
    QString fullPath = this->getFullFilePath(fileName);
    if(fullPath.isEmpty()) {
        // TODO : Show error message box regarding
        this->folderCreationError();
        return;
    }
    bool isSuccess =
            this->takeScreenshotAndSave(fullPath,
                QApplication::desktop()->winId(), this->settings->GetImgFormat(),
                    this->settings->GetImgQuality(), this->imgHeight, this->imgWidth);
    if(!isSuccess) {
        // TODO : Write a log file.
        Utility::WriteLog(fileName, "Error while taking a screenshot.", __LINE__, __FILE__);
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

bool MainWindow::takeScreenshotAndSave(QString savePath, int windowId, QString imageFormat,
                                       int imgQuality, int imgHeight, int imgWidth) {
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap originalPixmap = screen->grabWindow(windowId);
    originalPixmap.scaled(imgWidth, imgHeight, Qt::KeepAspectRatio,
                          Qt::SmoothTransformation);
    return originalPixmap.save(savePath + "." + imageFormat.toLower(), imageFormat.toUtf8(),
                               imgQuality);
}

void MainWindow::updateSettings() {
    this->settings->SetCapTime(this->ui->txtCaptureTime->text().toInt());
    this->settings->SetFilePath(this->ui->txtDestinationPath->text());
    this->settings->SetCapIsRandom(this->ui->chkRandomCapture->isChecked());
    if(ui->btnStartCapture->isEnabled()) {
        // Is off
        this->settings->SetCapIsOn(DEF_CAP_IS_OFF);
    } else {
        // Is on
        this->settings->SetCapIsOn(DEF_CAP_IS_ON);
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
    QFont font(DLG_FONT_FAMILY);
    font.setStyleHint(QFont::TypeWriter);
    msgBox.setWindowTitle("Settings Error");
    msgBox.setText("The settings for the application seem to be invalid.");
    msgBox.setInformativeText("Do you want to restore default settings or close the app?");
    msgBox.setStandardButtons(QMessageBox::RestoreDefaults | QMessageBox::Close );
    msgBox.setDefaultButton(QMessageBox::RestoreDefaults);
    msgBox.setFont(font);
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
    QFont font(DLG_FONT_FAMILY);
    font.setStyleHint(QFont::TypeWriter);
    msgBox.setWindowTitle("Unable to create folder");
    msgBox.setText("We were unable to create a folder in the destination path.");
    msgBox.setInformativeText("Please ensure that we have read/write permissions to that folder. If the folder is over a network,"
    " ensure that you are connected to it.");
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);    
    msgBox.setFont(font);
    msgBox.exec();
}

void MainWindow::resetRandomTimer() {
    if(this->settings->GetCapIsRandom()) {
        this->randomTimer->start(Utility::GetRandomBetween(1, this->settings->GetCapTime()) * 1000);
    }
}

void MainWindow::createTrayIcons() {
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIconMenu->setEnabled(true);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

void MainWindow::createTrayActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::setCurrentImgHeightAndWidth() {
    QRect rec = QApplication::desktop()->screenGeometry();
    this->imgHeight = rec.height();
    this->imgWidth = rec.width();
}

void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if( event->type() == QEvent::WindowStateChange && windowState() == Qt::WindowMinimized
            && this->isVisible()) {
        if(this->settings->GetMinimizeToTray()) {
            hide();
            trayIcon->setVisible(true);
        }
    }
}
