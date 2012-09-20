#ifndef GUIPREFDYNAMIND_H
#define GUIPREFDYNAMIND_H

#include <QDialog>

namespace Ui {
class GUIPrefDynaMind;
}

class GUIPrefDynaMind : public QDialog
{
    Q_OBJECT
    
public:
    explicit GUIPrefDynaMind(QWidget *parent = 0);
    ~GUIPrefDynaMind();
    
private:
    Ui::GUIPrefDynaMind *ui;
protected slots:
    void on_pushSelectDir_clicked();
    void accept();
};

#endif // GUIPREFDYNAMIND_H
