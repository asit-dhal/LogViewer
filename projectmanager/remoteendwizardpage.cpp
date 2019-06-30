#include "remoteendwizardpage.h"
#include "ui_remoteendwizardpage.h"
#include "projectwizard.h"

namespace ProjectManager {

RemoteEndWizardPage::RemoteEndWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::RemoteEndWizardPage)
{
    ui->setupUi(this);
}

RemoteEndWizardPage::~RemoteEndWizardPage()
{
    delete ui;
}

int RemoteEndWizardPage::nextId() const
{
    return ProjectWizard::ProjectAttributePageId;
}

} // ProjectManager
