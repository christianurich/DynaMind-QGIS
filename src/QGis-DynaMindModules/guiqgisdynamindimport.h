#ifndef GUIQGISDYNAMINDIMPORT_H
#define GUIQGISDYNAMINDIMPORT_H

#include <QDialog>

#define CORE_EXPORT  __attribute__((dllexport))
#define GUI_EXPORT __attribute__((dllexport))

class QGisDynaMindImport;
namespace DM {
    class Module;
}

namespace Ui {
class GUIQGisDynaMindImport;
}

class GUIQGisDynaMindImport : public QDialog
{
    Q_OBJECT
    
public:
    explicit GUIQGisDynaMindImport(DM::Module * m, QWidget *parent = 0);
    ~GUIQGisDynaMindImport();
    
private:
    Ui::GUIQGisDynaMindImport *ui;
   GUIQGisDynaMindImport * module;
};

#endif // GUIQGISDYNAMINDIMPORT_H
