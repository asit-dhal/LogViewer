#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class SettingsDialog;
}

class Configuration;

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();
    void onLoadConfigClicked();
    void onBrowseConfigClicked();
    void populateFields();
    void updateStatus(const QString& statusMessage);

    static SettingsDialog *getSettingsDialog();

private:
    Ui::SettingsDialog *ui;
    Configuration *m_configuration;
    QSettings m_appSettings;
    static SettingsDialog *m_settingsDialog;
};

#endif // SETTINGSDIALOG_H
