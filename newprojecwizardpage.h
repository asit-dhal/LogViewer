#ifndef NEWPROJECWIZARDPAGE_H
#define NEWPROJECWIZARDPAGE_H

#include <QWizardPage>

namespace Ui {
class NewProjecWizardPage;
}

class NewProjecWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit NewProjecWizardPage(QWidget *parent = nullptr);
    ~NewProjecWizardPage() override;
    void initializePage() override;
    bool validatePage() override;
    bool isComplete() const override;
    int nextId() const override;

private:
    void selectProjectDir();
    Ui::NewProjecWizardPage *ui;
};

#endif // NEWPROJECWIZARDPAGE_H
