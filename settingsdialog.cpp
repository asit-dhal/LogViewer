#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "configuration.h"

#include <QFileDialog>

SettingsDialog *SettingsDialog::m_settingsDialog = nullptr;

SettingsDialog *SettingsDialog::getSettingsDialog()
{
    return m_settingsDialog;
}

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    m_configuration(new Configuration(this))
{
    ui->setupUi(this);

    m_settingsDialog = this;

    connect(m_configuration, &Configuration::portChanged, [this](unsigned int port) {
        ui->portNumberLineEdit->setText(QString::number(port));
    });
    connect(m_configuration, &Configuration::ipAddressChanged, [this](const QHostAddress &hostAddress) {
        ui->hostnameLineEdit->setText(hostAddress.toString());
    });

    connect(m_configuration, &Configuration::fieldChanged, this, &SettingsDialog::populateFields);
    connect(ui->loadConfigPushButton, &QPushButton::clicked, this, &SettingsDialog::onLoadConfigClicked);
    connect(ui->browseFilePushButton, &QPushButton::clicked, this, &SettingsDialog::onBrowseConfigClicked);

    ui->loadConfigPushButton->setDisabled(true);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::onLoadConfigClicked()
{
    m_configuration->load(ui->filenameLineEdit->text().trimmed());
}

void SettingsDialog::onBrowseConfigClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Config File"), "", tr("Config File (*.xml)"));
    if (fileName.isEmpty()) {
        updateStatus(tr("Select a file"));
        ui->loadConfigPushButton->setDisabled(true);
    } else {
        ui->filenameLineEdit->setText(fileName);
        ui->loadConfigPushButton->setDisabled(false);
    }
}

void SettingsDialog::populateFields()
{
    ui->selectedFieldsTableWidget->setColumnCount(3);
    ui->selectedFieldsTableWidget->setRowCount(m_configuration->fieldCount());

    QStringList tableHeader;
    tableHeader << "Index" << "Name" << "Type";
    ui->selectedFieldsTableWidget->setHorizontalHeaderLabels(tableHeader);
    ui->selectedFieldsTableWidget->verticalHeader()->setVisible(false);

    for(int i = 0; i < m_configuration->fieldCount(); i++) {
        Configuration::Field field = m_configuration->fieldAt(static_cast<unsigned int>(i));
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
