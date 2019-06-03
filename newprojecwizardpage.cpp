#include "newprojecwizardpage.h"
#include "ui_newprojecwizardpage.h"
#include "project.h"
#include "newprojectwizard.h"

#include <QDir>
#include <QFileDialog>

NewProjecWizardPage::NewProjecWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::NewProjecWizardPage){
    ui->setupUi(this);

    ui->projectNameLineEdit->setText(Project::instance()->name());
    ui->pathLineEdit->setText(Project::instance()->path());

    connect(ui->projectNameLineEdit, &QLineEdit::editingFinished, this, &NewProjecWizardPage::completeChanged);
    connect(ui->projectNameLineEdit, &QLineEdit::textChanged, [this](const QString &) { emit completeChanged(); });
    connect(ui->pathLineEdit, &QLineEdit::editingFinished, this, &NewProjecWizardPage::completeChanged);
    connect(ui->pathLineEdit, &QLineEdit::textChanged, [this](const QString &) { emit completeChanged(); });
    connect(ui->browsePushButton, &QPushButton::clicked, this, &NewProjecWizardPage::selectProjectDir);
}

NewProjecWizardPage::~NewProjecWizardPage()
{
    delete ui;
}

void NewProjecWizardPage::initializePage()
{
    ui->projectNameLineEdit->setText(Project::instance()->name());
    ui->pathLineEdit->setText(Project::instance()->path());
}

bool NewProjecWizardPage::validatePage()
{
    const QString inputDir = ui->pathLineEdit->text().trimmed();
    const QString inputProject = ui->pathLineEdit->text().trimmed();

    if (!QDir(inputDir).exists()) {
        return false;
    }

    const QString projectPath = QDir::cleanPath(QDir(inputDir).dirName() + QDir::separator() +  inputProject);

    if (QDir(projectPath).exists()) {
        if (QDir(projectPath).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() != 0) {
            return false;
        }
    }
    return true;
}

bool NewProjecWizardPage::isComplete() const
{
    return !ui->pathLineEdit->text().trimmed().isEmpty() && !ui->pathLineEdit->text().trimmed().isEmpty();
}

int NewProjecWizardPage::nextId() const
{
    return NewProjectWizard::ProjectAttributePageId;
}

void NewProjecWizardPage::selectProjectDir()
{
    const QString previouslySelectedDir = ui->pathLineEdit->text().trimmed().isEmpty() ? "" : QDir(ui->pathLineEdit->text().trimmed()).dirName();
    const QString selectedPath = QFileDialog::getExistingDirectory(this, tr("Select Directory"), previouslySelectedDir,
                                                                   QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->pathLineEdit->setText(selectedPath);
}
