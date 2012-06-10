#include <QObject>

#include "qgisdynamindimport.h"
#include "guiqgisdynamindimport.h"



DM_DECLARE_NODE_NAME(QGisDynaMindImport, QGIS)
QGisDynaMindImport::QGisDynaMindImport()
{
    this->currentLayer = "";
    this->oldLayer = "";
    this->addParameter("CurrentLayer", DM::STRING, &this->currentLayer);
}

void QGisDynaMindImport::run() {

}

void QGisDynaMindImport::init() {

}

bool QGisDynaMindImport::createInputDialog() {
    QWidget * w = new GUIQGisDynaMindImport(this);
    w->show();
    return true;
}
