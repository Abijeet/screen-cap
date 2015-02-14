#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include "constants.h"
#include "utility.h"
#include "screencapsettings.h"
#include "appsettings.h"

namespace Ui {
    class QApplication;
    class QDesktopWidget;
    class MainWindow;
    class Utility;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnSettings_clicked();
    void on_btnStartCapture_clicked();
    void on_btnStopCapture_clicked();
    void timeToTakeScreenshot();
    void resetRandomTimer();
    void on_btnDestinationBrowser_clicked();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_btnAbout_clicked();

protected:
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

private:
    void changeStatusCtrls(bool isStartCapturing);
    QString getFullFilePath(QString filename);
    bool takeScreenshotAndSave(QString savePath, int windowId, QString imageFormat,
                               int imgQuality, int imgHeight, int imgWidth);
    void updateSettings();
    bool settingsHasError();
    void folderCreationError();
    void createTrayIcons();
    void createTrayActions();
    void setCurrentImgHeightAndWidth();    

    Ui::MainWindow *ui;
    AppSettings *appSettings;
    ScreenCapSettings *settings;
    QTimer *timer;
    QTimer *randomTimer;
    QSize *qSize;

    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    int imgHeight;
    int imgWidth;
};

#endif // MAINWINDOW_H
