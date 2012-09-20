#include "guiprefdynamind.h"
#include "ui_guiprefdynamind.h"
#include <QSettings>
#include <QFileDialog>

GUIPrefDynaMind::GUIPrefDynaMind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUIPrefDynaMind)
{
    ui->setupUi(this);
    QSettings settingsDynaMind("IUT", "DYNAMIND");
    QString rpath = settingsDynaMind.value("ROOTPATH").toString();
    ui->editPath->setText(rpath);



}

GUIPrefDynaMind::~GUIPrefDynaMind()
{
    delete ui;
}

void GUIPrefDynaMind::on_pushSelectDir_clicked()
{
    QString s = QFileDialog::getExistingDirectory(this, tr("Path to"), "");
    if(!s.isEmpty()) {
        ui->editPath->setText(s);
    }
}

void GUIPrefDynaMind::accept()
{
    QSettings settingsDynaMind("IUT", "DYNAMIND");
    settingsDynaMind.setValue("ROOTPATH", ui->editPath->text());
    QDialog::accept();
}
