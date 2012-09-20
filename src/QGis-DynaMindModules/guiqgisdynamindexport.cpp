#include "guiqgisdynamindexport.h"
#include "ui_guiqgisdynamindexport.h"
#include "qgisinterface.h"
#include "qgsmaplayerregistry.h"
#include <qgsmaplayer.h>
#include <qgsvectorlayer.h>
#include <qgsvectordataprovider.h>
#include "iostream"
#include <dmmodule.h>
#include "qgisdynamindexport.h"


GUIQGISDynaMindExport::GUIQGISDynaMindExport(DM::Module * m, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUIQGISDynaMindExport)
{
    ui->setupUi(this);

    this->module = (QGISDynaMindExport*)m;
    QMap<QString, QgsMapLayer*> layers = QgsMapLayerRegistry::instance()->mapLayers();
    ui->comboBox->clear();
    foreach (QString maps, layers.keys()) {
        QgsMapLayer * layer = QgsMapLayerRegistry::instance()->mapLayer(maps);

        if (layer->isEditable())
            ui->comboBox->addItem(maps);
    }

    ui->lineEdit->setText(QString::fromStdString(this->module->getParameterAsString("DataName")));
}

GUIQGISDynaMindExport::~GUIQGISDynaMindExport()
{
    delete ui;
}

void GUIQGISDynaMindExport::accept() {
    if (ui->lineEdit->text().isEmpty()) {
        QDialog::accept();
        return;
    }
    this->module->setParameterValue("DataName", ui->lineEdit->text().toStdString());
    if (ui->comboBox->currentText().isEmpty()) {
        QDialog::accept();
        return;

    }
    if (ui->comboBox->currentText().isEmpty()) {
        QDialog::accept();
        return;
    }

    std::string selectedLayer = ui->comboBox->currentText().toStdString();
    module->setLayer(selectedLayer);

    QDialog::accept();
    return;

}

