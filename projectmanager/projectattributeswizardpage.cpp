#include "projectattributeswizardpage.h"
#include "ui_projectattributeswizardpage.h"
#include "project.h"
#include "fieldmodel.h"
#include "fielddelegate.h"

#include <QDebug>
#include <QModelIndex>

namespace ProjectManager {

ProjectAttributesWizardPage::ProjectAttributesWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ProjectAttributesWizardPage)
{
    ui->setupUi(this);

    ui->fieldTableView->setModel(FieldModel::instance());
    ui->fieldTableView->setItemDelegate(new FieldDelegate(this));
    ui->fieldTableView->verticalHeader()->setVisible(true);
    ui->fieldTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->fieldTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->addPushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onFieldAdd);
    connect(ui->removePushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onFieldRemove);
    connect(ui->moveUpPushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onFieldMoveUp);
    connect(ui->moveDownPushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onFieldMoveDown);
    connect(ui->populateDefaultPushButton, &QPushButton::clicked, this, &ProjectAttributesWizardPage::onPopulateDefaultAttributes);
    connect(ui->fieldTableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ProjectAttributesWizardPage::onSelectionChanged);

    ui->removePushButton->setEnabled(false);
    ui->moveUpPushButton->setEnabled(false);
    ui->moveDownPushButton->setEnabled(false);

    connect(FieldModel::instance(), &FieldModel::rowsInserted, [this](const QModelIndex &, int, int) { emit completeChanged(); });
    connect(FieldModel::instance(), &FieldModel::rowsRemoved, [this](const QModelIndex &, int, int) { emit completeChanged(); });
    connect(FieldModel::instance(), &FieldModel::dataChanged, [this](const QModelIndex &, const QModelIndex &, const QVector<int> & roles) {
        bool changed = false;
        for (auto const &e: roles) {
            if (e == Qt::DisplayRole) {
                changed = true;
            }
        }
        if (changed) {
            emit completeChanged();
        }
    });
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
    for (const auto &index: selectionModel->selectedRows()) {
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

void ProjectAttributesWizardPage::onPopulateDefaultAttributes()
{
    auto model = FieldModel::instance();
    model->addField(Field(tr("Timestamp"), FieldType::eTimestamp));
    model->addField(Field(tr("Thread Id"), FieldType::eString));
    model->addField(Field(tr("Log Level"), FieldType::eString));
    model->addField(Field(tr("Category"), FieldType::eString));
    model->addField(Field(tr("Filename"), FieldType::eString));
    model->addField(Field(tr("Line"), FieldType::eNumber));
    model->addField(Field(tr("Payload"), FieldType::eString));
}

bool ProjectAttributesWizardPage::isComplete() const
{
    qDebug() << "field count: " << Project::instance()->fieldCount();
    qDebug() << "port number: " << Project::instance()->portNumber();
    qDebug() << "ipaddress: " << Project::instance()->ipAddress();

    return Project::instance()->fieldCount() > 0
            && Project::instance()->portNumber() > 0
            && (Project::instance()->ipAddress() != QHostAddress::Null);
}

} // ProjectManager
