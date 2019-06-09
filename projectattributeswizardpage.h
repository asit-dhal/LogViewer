#ifndef PROJECTATTRIBUTESWIZARDPAGE_H
#define PROJECTATTRIBUTESWIZARDPAGE_H

#include <QWizardPage>
#include <QItemSelectionModel>

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
    void onPortNumberChanged();
    void onIPAddressChanged();
    bool isComplete() const;

private:
    Ui::ProjectAttributesWizardPage *ui;
};

#endif // PROJECTATTRIBUTESWIZARDPAGE_H
