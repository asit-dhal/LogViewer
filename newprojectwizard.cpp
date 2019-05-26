#include "newprojectwizard.h"
#include "newprojecwizardpage.h"
#include "projectattributeswizardpage.h"

NewProjectWizard::NewProjectWizard(QWidget *parent) :
    QWizard(parent)
{
    setPage(NewProjectPageId, new NewProjecWizardPage);
    setPage(ProjectAttributePageId, new ProjectAttributesWizardPage);
    setStartId(NewProjectPageId);

    setModal(true);
}

NewProjectWizard::~NewProjectWizard()
{
}
