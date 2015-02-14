#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QDialog>
#include <QComboBox>
#include "screencapsettings.h"

namespace Ui {
class AppSettings;
}

class AppSettings : public QDialog
{
    Q_OBJECT

public:
    explicit AppSettings(QWidget *parent);
    void setupUI(ScreenCapSettings *settings);
    ScreenCapSettings* GetUpdatedSettings(ScreenCapSettings *settings);
    void addItemsToQualityDdl(QComboBox *cmbBox, ScreenCapSettings *settings);
    void addItemsToFormatDdl(QComboBox *cmbBox, ScreenCapSettings *settings);
    ~AppSettings();

protected:
    void done(int result);

private:
    Ui::AppSettings *ui;
    bool checkSettings();
    void dimensionError();
};

#endif // APPSETTINGS_H
