#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LogModel;
class SearchLogModel;
class QUdpSocket;
class QAction;
class SettingsDialog;
class Configuration;

namespace ProjectManager {
class ProjectWizard;
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createActions();
    void onConnectDisconnectActionTriggered(bool checked);
    void onLogTableHeaderContextMenuRequested(const QPoint &p);
    void onSettingsAction();
    void onNewProject();
    void processPendingDatagrams();

    void scrollToBottomLogTable();
    void connectToRemote();
    void disconnectFromRemote();

    Ui::MainWindow *ui;
    SettingsDialog *m_settingsDialog = nullptr;
    LogModel *m_logModel = nullptr;
    SearchLogModel *m_searchLogModel = nullptr;
    QUdpSocket *m_udpSocket = nullptr;
    int m_receivedDataSize = 0;

    QAction *m_startStopRecording;
    QAction *m_clearAction;
    QAction *m_loadConfigurationAction;
    Configuration *m_configuration;
    ProjectManager::ProjectWizard *m_newProjectWizard;
};

#endif // MAINWINDOW_H
