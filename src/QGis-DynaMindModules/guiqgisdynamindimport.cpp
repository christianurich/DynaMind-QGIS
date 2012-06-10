#include "guiqgisdynamindimport.h"
#include "ui_guiqgisdynamindimport.h"
#include "qgisinterface.h"
#include "qgsmaplayerregistry.h"
#include "iostream"
#include <dmmodule.h>
#include "qgisdynamindimport.h"

GUIQGisDynaMindImport::GUIQGisDynaMindImport(DM::Module * m, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUIQGisDynaMindImport)
{
    ui->setupUi(this);

    this->module = (QGisDynaMindImport*)m;
    QMap<QString, QgsMapLayer*> layers = QgsMapLayerRegistry::instance()->mapLayers();
    ui->comboBox->clear();
    foreach (QString maps, layers.keys()) {
        ui->comboBox->addItem(maps);
    }

    ui->lineEdit->setText(QString::fromStdString(this->module->getParameterAsString("DataName")));

}

GUIQGisDynaMindImport::~GUIQGisDynaMindImport()
{
    delete ui;
}

void GUIQGisDynaMindImport::accept() {
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

