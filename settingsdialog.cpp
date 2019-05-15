#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "configuration.h"

#include <QFileDialog>
#include <QFileInfo>

namespace {

bool checkIfFileExists(const QString& filename) {
    QFileInfo checkFile(filename);
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    }
    return false;
}

}

SettingsDialog *SettingsDialog::m_settingsDialog = nullptr;

SettingsDialog *SettingsDialog::getSettingsDialog()
{
    return m_settingsDialog;
}

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    QSettings::setDefaultFormat(QSettings::IniFormat);

    m_settingsDialog = this;

    connect(Configuration::getInstance(), &Configuration::portChanged, [this](unsigned int port) {
        ui->portNumberLineEdit->setText(QString::number(port));
    });
    connect(Configuration::getInstance(), &Configuration::ipAddressChanged, [this](const QHostAddress &hostAddress) {
        ui->hostnameLineEdit->setText(hostAddress.toString());
    });

    connect(Configuration::getInstance(), &Configuration::fieldChanged, this, &SettingsDialog::populateFields);
    connect(ui->loadConfigPushButton, &QPushButton::clicked, this, &SettingsDialog::onLoadConfigClicked);
    connect(ui->browseFilePushButton, &QPushButton::clicked, this, &SettingsDialog::onBrowseConfigClicked);


     m_appSettings.beginGroup("last-config-file");
     QString recentFile = m_appSettings.value("file-path").toString();
     if (!recentFile.isEmpty() && checkIfFileExists(recentFile)) {
        ui->filenameLineEdit->setText(recentFile);
        ui->loadConfigPushButton->setDisabled(false);
     } else {
         ui->loadConfigPushButton->setDisabled(true);
     }
     m_appSettings.endGroup();

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::onLoadConfigClicked()
{
    Configuration::getInstance()->load(ui->filenameLineEdit->text().trimmed());
}

void SettingsDialog::onBrowseConfigClicked()
{
    QString lastFilePath;
    if (!ui->filenameLineEdit->text().isEmpty()) {
        lastFilePath = QFileInfo(ui->filenameLineEdit->text()).absoluteDir().absolutePath();
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Config File"), lastFilePath, tr("Config File (*.xml)"));
    if (fileName.isEmpty() && checkIfFileExists(fileName)) {
        updateStatus(tr("Select a file"));
        ui->loadConfigPushButton->setDisabled(true);
    } else {
        m_appSettings.beginGroup("last-config-file");
        m_appSettings.setValue("file-path", fileName);
        m_appSettings.endGroup();
        ui->filenameLineEdit->setText(fileName);
        ui->loadConfigPushButton->setDisabled(false);
    }
}

void SettingsDialog::populateFields()
{
    ui->selectedFieldsTableWidget->setColumnCount(3);
    ui->selectedFieldsTableWidget->setRowCount(Configuration::getInstance()->fieldCount());

    QStringList tableHeader;
    tableHeader << "Index" << "Name" << "Type";
    ui->selectedFieldsTableWidget->setHorizontalHeaderLabels(tableHeader);
    ui->selectedFieldsTableWidget->verticalHeader()->setVisible(false);

    for(int i = 0; i < Configuration::getInstance()->fieldCount(); i++) {
        Configuration::Field field = Configuration::getInstance()->fieldAt(static_cast<unsigned int>(i));
        ui->selectedFieldsTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(field.index)));
        ui->selectedFieldsTableWidget->setItem(i, 1, new QTableWidgetItem(field.name));
        switch (field.fieldType) {
        case Configuration::FieldType::eTimestamp:
            ui->selectedFieldsTableWidget->setItem(i, 2, new QTableWidgetItem("Timestamp"));
            break;
        case Configuration::FieldType::eString:
            ui->selectedFieldsTableWidget->setItem(i, 2, new QTableWidgetItem("String"));
            break;
        case Configuration::FieldType::eInt:
            ui->selectedFieldsTableWidget->setItem(i, 2, new QTableWidgetItem("Number"));
            break;
        }
    }
}

void SettingsDialog::updateStatus(const QString& statusMessage)
{
    ui->statusLabel->setText(statusMessage);
}
