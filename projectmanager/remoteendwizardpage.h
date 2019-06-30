#ifndef REMOTEENDWIZARDPAGE_H
#define REMOTEENDWIZARDPAGE_H

#include <QWizardPage>

namespace ProjectManager {

namespace Ui {
class RemoteEndWizardPage;
}

class RemoteEndWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit RemoteEndWizardPage(QWidget *parent = nullptr);
    ~RemoteEndWizardPage();
    int nextId() const override;

private:
    Ui::RemoteEndWizardPage *ui;
};

} // ProjectManager

#endif // REMOTEENDWIZARDPAGE_H
