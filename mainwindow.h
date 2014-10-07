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

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    AppSettings *appSettings;
    ScreenCapSettings *settings;
    QTimer *timer;
    void changeStatusCtrls(bool isStartCapturing);
    QString getFullFilePath(QString filename);
    bool takeScreenshotAndSave(QString savePath, int windowId);
    QSize *qSize;
};

#endif // MAINWINDOW_H
