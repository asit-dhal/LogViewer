#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LogModel;
class SearchLogModel;
class QUdpSocket;
class QAction;

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
    void processPendingDatagrams();

    void connectToRemote();
    void disconnectFromRemote();

    Ui::MainWindow *ui;
    LogModel *m_logModel = nullptr;
    SearchLogModel *m_searchLogModel = nullptr;
    QUdpSocket *m_udpSocket = nullptr;

    QAction *m_startStopRecording;
    QAction *m_clearAction;
};

#endif // MAINWINDOW_H
