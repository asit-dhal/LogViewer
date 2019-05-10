#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logmodel.h"
#include "searchlogmodel.h"
#include "settingsdialog.h"
#include <QAbstractItemView>

#include <QAction>
#include <QUdpSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_logModel = new LogModel(this);
    m_searchLogModel = new SearchLogModel(this);
    m_settingsDialog = new SettingsDialog(this);

    ui->logTableView->setModel(m_logModel);
    ui->logTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->logTableView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->logTableView->horizontalHeader()->setStretchLastSection(true);
    connect(ui->logTableView->horizontalHeader(), &QTableView::customContextMenuRequested,
            this, &MainWindow::onLogTableHeaderContextMenuRequested);

    m_searchLogModel->setSourceModel(m_logModel);
    ui->searchTableView->setModel(m_searchLogModel);
    ui->searchTableView->horizontalHeader()->setStretchLastSection(true);
    ui->searchTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    createActions();

    connect(ui->reCheckBox, &QCheckBox::stateChanged, [this](int state) {
       m_searchLogModel->onRegularExpressionEnabled(state == Qt::CheckState::Checked);
    });

    connect(ui->searchLineEdit, &QLineEdit::returnPressed, [this]() { emit ui->searchPushButton->click();});
    connect(ui->searchPushButton, &QPushButton::clicked, [this]() {
        m_searchLogModel->onSearchButtonClicked(ui->searchLineEdit->text().trimmed());
    });

    connect(ui->autoScrollPushButton, &QPushButton::clicked, [this](bool checked) {
        if (checked) {
            connect(m_logModel, &LogModel::rowsInserted, this, &MainWindow::scrollToBottomLogTable);
            connect(m_logModel, &LogModel::modelReset, this, &MainWindow::scrollToBottomLogTable);
        } else {
            disconnect(m_logModel, &LogModel::rowsInserted, this, &MainWindow::scrollToBottomLogTable);
            disconnect(m_logModel, &LogModel::modelReset, this, &MainWindow::scrollToBottomLogTable);

        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    m_startStopRecording = ui->mainToolBar->addAction("Connect");
    m_startStopRecording->setCheckable(true);
    m_startStopRecording->setChecked(false);
    connect(m_startStopRecording, &QAction::triggered, this, &MainWindow::onConnectDisconnectActionTriggered);

    m_clearAction = ui->mainToolBar->addAction(tr("Clear"));
    connect(m_clearAction, &QAction::triggered, [this]() { m_logModel->clear();});

    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::onSettingsAction);
}

void MainWindow::onConnectDisconnectActionTriggered(bool checked)
{
    if (checked) {
        connectToRemote();
        m_startStopRecording->setText("Disconnect");
    } else {
        disconnectFromRemote();
        m_startStopRecording->setText("Connect");
    }
}

void MainWindow::connectToRemote()
{
    m_udpSocket = new QUdpSocket(this);
    bool status = m_udpSocket->bind(30000, QUdpSocket::ShareAddress);
    Q_ASSERT(status);
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &MainWindow::processPendingDatagrams);

    ui->statusBar->showMessage("Waiting for data");
}

void MainWindow::disconnectFromRemote()
{
    m_udpSocket->close();
    m_receivedDataSize = 0;
}

void MainWindow::processPendingDatagrams()
{
    QByteArray datagram;
    while (m_udpSocket->hasPendingDatagrams()) {
        auto packSize = static_cast<int>(m_udpSocket->pendingDatagramSize());
        datagram.resize(packSize);
        m_receivedDataSize += packSize;
        ui->statusBar->showMessage(tr("Data received %1 bytes").arg(m_receivedDataSize));
        m_udpSocket->readDatagram(datagram.data(), datagram.size());

        QStringList tokens = QString(datagram.constData()).split(",");
        LogRecord rec;
        rec.timestamp = QDateTime::fromMSecsSinceEpoch(tokens.front().toLongLong());
        tokens.pop_front();
        rec.threadId = tokens.front();
        tokens.pop_front();
        rec.logLevel = tokens.front();
        tokens.pop_front();

		rec.category = tokens.front();
		tokens.pop_front();
		rec.filename = tokens.front();
		tokens.pop_front();
		rec.lineNumber = tokens.front();
		tokens.pop_front();
		
        rec.message = tokens.join(',');
        m_logModel->addLogRecord(rec);
    }
}

void MainWindow::onSettingsAction()
{
    m_settingsDialog->exec();
}

void MainWindow::onLogTableHeaderContextMenuRequested(const QPoint &p)
{
    QMenu *menu = new QMenu(this);
    bool atleastOneHidden = false;

    for(int i=0; i< m_logModel->columnCount(); i++) {
        bool isHidden = ui->logTableView->isColumnHidden(i);
        QString displayText = QString("%1 %2")
                .arg(isHidden ? "Show" : "Hide")
                .arg(m_logModel->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        auto actionLambda = [&, isHidden, index=i]() {
            if (isHidden)
                ui->logTableView->showColumn(index);
            else
                ui->logTableView->hideColumn(index);
        };
        QAction  *act = new QAction(displayText, this);
        act->setCheckable(true);
        act->setChecked(!isHidden);
        connect(act, &QAction::triggered, actionLambda);
        menu->addAction(act);
        atleastOneHidden |= isHidden;
    }

    if (atleastOneHidden) {
        menu->addSeparator();
        QAction  *act = new QAction(tr("Show All"), this);
        connect(act, &QAction::triggered, [&]() {
            for(int i=0; i< m_logModel->columnCount(); i++) {
                if (ui->logTableView->isColumnHidden(i)) {
                    ui->logTableView->showColumn(i);
                }
            }
        });
        menu->addAction(act);
    }

    menu->popup(ui->logTableView->horizontalHeader()->viewport()->mapToGlobal(p));
}


void MainWindow::scrollToBottomLogTable()
{
    ui->logTableView->scrollToBottom();
}
