#include "guiqgisdynamindimport.h"
#include "ui_guiqgisdynamindimport.h"
#include "qgisinterface.h"
#include "qgsmaplayerregistry.h"
#include "iostream"
#include <dmmodule.h>
#include <qgisdynamindimport.h>

GUIQGisDynaMindImport::GUIQGisDynaMindImport(DM::Module * m, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUIQGisDynaMindImport)
{
    ui->setupUi(this);

    module = (GUIQGisDynaMindImport*)m;
    QMap<QString, QgsMapLayer*> layers = QgsMapLayerRegistry::instance()->mapLayers();
     ui->comboBox->clear();
    foreach (QString maps, layers.keys()) {
        ui->comboBox->addItem(maps);
    }



}

GUIQGisDynaMindImport::~GUIQGisDynaMindImport()
{
    delete ui;
}
