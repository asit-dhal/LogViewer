#ifndef PROJECTATTRIBUTESWIZARDPAGE_H
#define PROJECTATTRIBUTESWIZARDPAGE_H

#include <QWizardPage>

namespace Ui {
class ProjectAttributesWizardPage;
}

class ProjectAttributesWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ProjectAttributesWizardPage(QWidget *parent = nullptr);
    ~ProjectAttributesWizardPage();

private:
    void onFieldAdd();
    void onFieldRemove();
    void onFieldMoveUp();
    void onFieldMoveDown();

private:
    Ui::ProjectAttributesWizardPage *ui;
};

#endif // PROJECTATTRIBUTESWIZARDPAGE_H
