#include "projectattributeswizardpage.h"
#include "ui_projectattributeswizardpage.h"
#include "project.h"

ProjectAttributesWizardPage::ProjectAttributesWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ProjectAttributesWizardPage)
{
    ui->setupUi(this);

    ui->fieldsTableWidget->setColumnCount(3);
    ui->fieldsTableWidget->setRowCount(Project::instance()->fieldCount());

    QStringList tableHeader;
    tableHeader << "Index" << "Name" << "Type";
    ui->fieldsTableWidget->setHorizontalHeaderLabels(tableHeader);
    ui->fieldsTableWidget->verticalHeader()->setVisible(false);

    connect(ui->addPushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onFieldAdd);
    connect(ui->removePushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onFieldRemove);
    connect(ui->moveUpPushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onFieldMoveUp);
    connect(ui->moveDownPushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onFieldMoveDown);
}

ProjectAttributesWizardPage::~ProjectAttributesWizardPage()
{
    delete ui;
}

void ProjectAttributesWizardPage::onFieldAdd()
{

    int rowIndex = ui->fieldsTableWidget->rowCount();
    ui->fieldsTableWidget->insertRow(rowIndex);

    QLineEdit *indexItem = new QLineEdit();
    indexItem->setText(QString::number(rowIndex));
    ui->fieldsTableWidget->setCellWidget(rowIndex, 0, indexItem);

    QLineEdit *nameLineEdit = new QLineEdit();
    nameLineEdit->setText(tr("Default"));
    ui->fieldsTableWidget->setCellWidget(rowIndex, 1, nameLineEdit);

    QComboBox *fieldTypeComboBox = new QComboBox();
    fieldTypeComboBox->addItem(tr("String"));
    fieldTypeComboBox->addItem(tr("Number"));
    fieldTypeComboBox->addItem(tr("Timestamp"));
    fieldTypeComboBox->setCurrentIndex(0);
    ui->fieldsTableWidget->setCellWidget(rowIndex, 2, fieldTypeComboBox);
}

void ProjectAttributesWizardPage::onFieldRemove()
{

}

void ProjectAttributesWizardPage::onFieldMoveUp()
{

}

void ProjectAttributesWizardPage::onFieldMoveDown()
{

}
