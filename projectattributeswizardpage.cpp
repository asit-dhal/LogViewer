#include "projectattributeswizardpage.h"
#include "ui_projectattributeswizardpage.h"
#include "project.h"
#include "fieldmodel.h"
#include "fielddelegate.h"

ProjectAttributesWizardPage::ProjectAttributesWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ProjectAttributesWizardPage)
{
    ui->setupUi(this);

    ui->fieldTableView->setModel(FieldModel::instance());
    ui->fieldTableView->setItemDelegate(new FieldDelegate(this));
    ui->fieldTableView->verticalHeader()->setVisible(false);
    ui->fieldTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->fieldTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->addPushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onFieldAdd);
    connect(ui->removePushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onFieldRemove);
    connect(ui->moveUpPushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onFieldMoveUp);
    connect(ui->moveDownPushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onFieldMoveDown);
    connect(ui->fieldTableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ProjectAttributesWizardPage::onSelectionChanged);

    ui->removePushButton->setEnabled(false);
    ui->moveUpPushButton->setEnabled(false);
    ui->moveDownPushButton->setEnabled(false);
}

ProjectAttributesWizardPage::~ProjectAttributesWizardPage()
{
    delete ui;
}

void ProjectAttributesWizardPage::onFieldAdd()
{
    FieldModel::instance()->addField(Field());
}

void ProjectAttributesWizardPage::onFieldRemove()
{
    QItemSelectionModel *selectionModel = ui->fieldTableView->selectionModel();
    for (const QModelIndex &index: selectionModel->selectedRows()) {
        FieldModel::instance()->removeField(index.row());
    }
}

void ProjectAttributesWizardPage::onFieldMoveUp()
{

}

void ProjectAttributesWizardPage::onFieldMoveDown()
{

}

void ProjectAttributesWizardPage::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);

    QItemSelectionModel *selectionModel = ui->fieldTableView->selectionModel();
    ui->removePushButton->setEnabled(selectionModel->hasSelection());
    ui->moveUpPushButton->setEnabled(selectionModel->hasSelection());
    ui->moveDownPushButton->setEnabled(selectionModel->hasSelection());
}
