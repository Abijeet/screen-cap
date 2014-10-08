#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "constants.h"
#include "utility.h"
#include "screencapsettings.h"
#include "appsettings.h"

namespace Ui {
    // Forward Declaration
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

protected:
    void closeEvent(QCloseEvent *event);

private:
    void changeStatusCtrls(bool isStartCapturing);
    QString getFullFilePath(QString filename);
    bool takeScreenshotAndSave(QString savePath, int windowId, QString imageFormat = IMG_FILE_FORMAT);
    void updateSettings();
    bool settingsHasError();
    void folderCreationError();

    Ui::MainWindow *ui;
    AppSettings *appSettings;
    ScreenCapSettings *settings;
    QTimer *timer;
    QTimer *randomTimer;
    QSize *qSize;    
};

#endif // MAINWINDOW_H
