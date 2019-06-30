#ifndef PROJECTATTRIBUTESWIZARDPAGE_H
#define PROJECTATTRIBUTESWIZARDPAGE_H

#include <QWizardPage>
#include <QItemSelectionModel>

namespace ProjectManager {

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
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onPopulateDefaultAttributes();
    bool isComplete() const;

private:
    Ui::ProjectAttributesWizardPage *ui;
};

} // ProjectManager

#endif // PROJECTATTRIBUTESWIZARDPAGE_H
