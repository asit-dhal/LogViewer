#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    ui->availableFieldsTableWidget->setColumnCount(2);
    ui->availableFieldsTableWidget->setShowGrid(true);
    ui->availableFieldsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->availableFieldsTableWidget->setHorizontalHeaderLabels({tr("Field Name"), tr("Available Types")});
    ui->availableFieldsTableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->availableFieldsTableWidget->insertRow(0);
    ui->availableFieldsTableWidget->setItem(0, 0, new QTableWidgetItem("Timestamp"));
    ui->availableFieldsTableWidget->setItem(0, 1, new QTableWidgetItem("Seconds Since Epoc"));

    ui->availableFieldsTableWidget->insertRow(1);
    ui->availableFieldsTableWidget->setItem(1, 0, new QTableWidgetItem("Thread"));
    ui->availableFieldsTableWidget->setItem(1, 1, new QTableWidgetItem("Integer|String"));

    ui->availableFieldsTableWidget->insertRow(1);
    ui->availableFieldsTableWidget->setItem(1, 0, new QTableWidgetItem("Thread"));
    ui->availableFieldsTableWidget->setItem(1, 1, new QTableWidgetItem("Integer|String"));

    ui->availableFieldsTableWidget->insertRow(1);
    ui->availableFieldsTableWidget->setItem(1, 0, new QTableWidgetItem("Thread"));
    ui->availableFieldsTableWidget->setItem(1, 1, new QTableWidgetItem("Integer|String"));

    ui->availableFieldsTableWidget->insertRow(1);
    ui->availableFieldsTableWidget->setItem(1, 0, new QTableWidgetItem("Thread"));
    ui->availableFieldsTableWidget->setItem(1, 1, new QTableWidgetItem("Integer|String"));

    ui->availableFieldsTableWidget->insertRow(1);
    ui->availableFieldsTableWidget->setItem(1, 0, new QTableWidgetItem("Thread"));
    ui->availableFieldsTableWidget->setItem(1, 1, new QTableWidgetItem("Integer|String"));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
