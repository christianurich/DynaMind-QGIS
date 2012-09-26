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
        maps.remove(maps.length()-17, 17);
        ui->comboBox->addItem(maps);
    }
    std::string nameofLayer = m->getParameter<std::string>("CurrentLayer");
    if (!nameofLayer.empty()) {
        int index = ui->comboBox->findText(QString::fromStdString(nameofLayer));
        if (index > -1)
            ui->comboBox->setCurrentIndex(index);
    }

    ui->lineEdit->setText(QString::fromStdString(this->module->getParameterAsString("DataName")));

    bool append = m->getParameter<bool>("appendToStream");
    ui->checkBox_append->setChecked(append);

    ui->lineEditCoorindateSystem->setText(QString::fromStdString(this->module->getParameterAsString("CoordinateSystem")));

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
    if (ui->checkBox_append->isChecked()) {
        module->setParameterNative<bool>("appendToStream", true);
    } else {
        module->setParameterNative<bool>("appendToStream", false);
    }
    std::string selectedLayer = ui->comboBox->currentText().toStdString();
    module->setLayer(selectedLayer);

    long coorindateSystem = ui->lineEditCoorindateSystem->text().toLong();
    module->setParameterNative<long>("CoordinateSystem", coorindateSystem);

    QDialog::accept();
    return;

}

