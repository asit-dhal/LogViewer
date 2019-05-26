#ifndef NEWPROJECTWIZARD_H
#define NEWPROJECTWIZARD_H

#include <QWizard>

class NewProjectWizard : public QWizard
{
    Q_OBJECT

public:
    enum NewProjectWizard_Page {
        NewProjectPageId,
        ProjectAttributePageId
    };

    explicit NewProjectWizard(QWidget *parent = nullptr);
    ~NewProjectWizard();

private:
};

#endif // NEWPROJECTWIZARD_H
