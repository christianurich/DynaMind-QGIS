#ifndef GUIQGISDYNAMINDIMPORT_H
#define GUIQGISDYNAMINDIMPORT_H


#include <QDialog>
#include "dmcompilersettings.h"
#define CORE_EXPORT  __attribute__((dllexport))
#define GUI_EXPORT __attribute__((dllexport))

namespace Ui {
class GUIQGisDynaMindImport;
}

class QGisDynaMindImport;

namespace DM {
class Module;
}



class DM_HELPER_DLL_EXPORT GUIQGisDynaMindImport : public QDialog
{
    Q_OBJECT
    
public:
    explicit GUIQGisDynaMindImport(DM::Module * m, QWidget *parent = 0);
    ~GUIQGisDynaMindImport();
    
private:
    Ui::GUIQGisDynaMindImport *ui;
    QGisDynaMindImport * module;
public slots:
    void accept();

};

#endif // GUIQGISDYNAMINDIMPORT_H
