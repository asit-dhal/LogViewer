#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logmodel.h"
#include "searchlogmodel.h"
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

    ui->logTableView->setModel(m_logModel);
    ui->logTableView->horizontalHeader()->setStretchLastSection(true);
    ui->logTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

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
}

void MainWindow::processPendingDatagrams()
{
    QByteArray datagram;
    while (m_udpSocket->hasPendingDatagrams()) {
        auto packSize = static_cast<int>(m_udpSocket->pendingDatagramSize());
        datagram.resize(packSize);
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
