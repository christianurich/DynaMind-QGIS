#ifndef GUIQGISDYNAMINDEXPORT_H
#define GUIQGISDYNAMINDEXPORT_H

#include <QDialog>
#include "dmcompilersettings.h"
#define CORE_EXPORT  __attribute__((dllexport))
#define GUI_EXPORT __attribute__((dllexport))
namespace Ui {
class GUIQGISDynaMindExport;
}

class QGISDynaMindExport;

namespace DM {
class Module;
}
class GUIQGISDynaMindExport : public QDialog
{
    Q_OBJECT
    
public:
    explicit GUIQGISDynaMindExport(DM::Module * m, QWidget *parent = 0);
    ~GUIQGISDynaMindExport();
    
private:
    Ui::GUIQGISDynaMindExport *ui;
    QGISDynaMindExport * module;
public slots:
    void accept();
};

#endif // GUIQGISDYNAMINDEXPORT_H
