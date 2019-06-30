#include "projectwizard.h"
#include "newprojecwizardpage.h"
#include "projectattributeswizardpage.h"
#include "remoteendwizardpage.h"

namespace ProjectManager {

ProjectWizard::ProjectWizard(QWidget *parent) :
    QWizard(parent)
{
    setPage(NewProjectPageId, new NewProjecWizardPage);
    setPage(RemoteEndpointPageId, new RemoteEndWizardPage);
    setPage(ProjectAttributePageId, new ProjectAttributesWizardPage);
    setStartId(NewProjectPageId);

    setModal(true);
}

ProjectWizard::~ProjectWizard()
{
}

} // ProjectManager
