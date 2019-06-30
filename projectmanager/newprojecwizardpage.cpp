#include "newprojecwizardpage.h"
#include "ui_newprojecwizardpage.h"
#include "project.h"
#include "projectwizard.h"
#include "helper/appconfig.h"

#include <QDir>
#include <QFileDialog>
#include <QDebug>

namespace ProjectManager {

namespace {

QString getDefaultProjectName(const QString &path) {
    if (path.isEmpty())
        return QString();

    if (!QDir(path).exists()) {
        return QString("untitled");
    }

    QString newPath;
    int nameSuffix = 0;
    for (nameSuffix = 0; nameSuffix < 20; nameSuffix++) {
        if (nameSuffix == 0) {
            newPath = path + QDir::separator() + "untitled";
        } else {
            newPath = path + QDir::separator() + "untitled" + QString::number(nameSuffix);
        }

        QFileInfo fileInfo(newPath);
        if (fileInfo.exists() && (fileInfo.isDir() || fileInfo.isFile())) {
            break;
        }
    }

    if (nameSuffix == 0) {
        return QString("utitled");
    }
    else {
        return QString("utitled") + QString::number(nameSuffix);
    }
}

}

NewProjecWizardPage::NewProjecWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::NewProjecWizardPage)
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);

    connect(ui->projectNameLineEdit, &QLineEdit::editingFinished, this, &NewProjecWizardPage::completeChanged);
    connect(ui->projectNameLineEdit, &QLineEdit::textChanged, [this](const QString &) { emit completeChanged(); });
    connect(ui->pathLineEdit, &QLineEdit::editingFinished, this, &NewProjecWizardPage::completeChanged);
    connect(ui->pathLineEdit, &QLineEdit::textChanged, [this](const QString &) { emit completeChanged(); });
    connect(ui->browsePushButton, &QPushButton::clicked, this, &NewProjecWizardPage::selectProjectDir);
}

NewProjecWizardPage::~NewProjecWizardPage()
{
    qDebug() << Q_FUNC_INFO;
    delete ui;
}

void NewProjecWizardPage::initializePage()
{
    qDebug() << Q_FUNC_INFO;

    QString projectPath = Project::instance()->path();
    if (projectPath.isEmpty()) {
        projectPath = Helper::AppConfig::getDefaultProjectLocation();
        ui->rememberCheckBox->setChecked(!projectPath.isEmpty());
    }
    ui->pathLineEdit->setText(projectPath);

    QString projectName = Project::instance()->name();
    if (projectName.isEmpty()) {
        projectName = getDefaultProjectName(projectPath);
    }
    ui->projectNameLineEdit->setText(projectName);
}

bool NewProjecWizardPage::validatePage()
{
    qDebug() << Q_FUNC_INFO;
    const QString inputDir = ui->pathLineEdit->text().trimmed();
    const QString inputProject = ui->pathLineEdit->text().trimmed();

    if (!QDir(inputDir).exists()) {
        ui->messageLabel->setText(inputDir + " does not exist. It will be created.");
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
    qDebug() << Q_FUNC_INFO;
    return !ui->pathLineEdit->text().trimmed().isEmpty() && !ui->pathLineEdit->text().trimmed().isEmpty();
}

int NewProjecWizardPage::nextId() const
{
    qDebug() << Q_FUNC_INFO;
    if (ui->rememberCheckBox->isChecked()) {
        Helper::AppConfig::updateDefaultProjectLocation(ui->pathLineEdit->text().trimmed());
    }
    return ProjectWizard::RemoteEndpointPageId;
}

void NewProjecWizardPage::selectProjectDir()
{
    qDebug() << Q_FUNC_INFO;
    const QString previouslySelectedDir = ui->pathLineEdit->text().trimmed().isEmpty() ? "" : QDir(ui->pathLineEdit->text().trimmed()).dirName();
    const QString selectedPath = QFileDialog::getExistingDirectory(this, tr("Select Directory"), previouslySelectedDir,
                                                                   QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->pathLineEdit->setText(selectedPath);
}

} // ProjectManager
