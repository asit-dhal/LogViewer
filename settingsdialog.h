#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class SettingsDialog;
}

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
    QSettings m_appSettings;
    static SettingsDialog *m_settingsDialog;
};

#endif // SETTINGSDIALOG_H
