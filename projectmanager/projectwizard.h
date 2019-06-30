#ifndef NEWPROJECTWIZARD_H
#define NEWPROJECTWIZARD_H

#include <QWizard>

namespace ProjectManager {

class ProjectWizard : public QWizard
{
    Q_OBJECT

public:
    enum ProjectWizard_Page {
        NewProjectPageId,
        RemoteEndpointPageId,
        ProjectAttributePageId
    };

    explicit ProjectWizard(QWidget *parent = nullptr);
    ~ProjectWizard();
};

} // ProjectManager

#endif // NEWPROJECTWIZARD_H
