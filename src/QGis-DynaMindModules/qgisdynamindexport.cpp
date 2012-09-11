#include <QObject>

#include "guiqgisdynamindexport.h"
#include "qgisdynamindexport.h"
#include <qgisplugin.h>
#include <qgsmaplayerregistry.h>
#include <qgsmaplayer.h>
#include <qgsvectorlayer.h>
#include <qgsgeometry.h>

#include "ogrsf_frmts.h"

DM_DECLARE_NODE_NAME(QGISDynaMindExport, QGIS)

QGISDynaMindExport::QGISDynaMindExport()
{
    DM::View dummy("dummy", DM::SUBSYSTEM, DM::READ);
    std::vector<DM::View> data;
    data.push_back(dummy);
    this->addData("data", data);
    this->dataname = "";
    this->qgisname = "";
    this->addParameter("DataName", DM::STRING, & this->dataname);
    this->addParameter("QGISName", DM::STRING, & this->qgisname);
}

void QGISDynaMindExport::run() {
    DM::System * sys;
    sys = this->getData("data");

    DM::View * v = sys->getViewDefinition(dataname);

    QgsMapLayer * layer = QgsMapLayerRegistry::instance()->mapLayer(QString::fromStdString(this->qgisname));

    QgsVectorLayer * vectorLayer= (QgsVectorLayer*) layer;

    for (int id = 0; id < vectorLayer->featureCount(); id++ ) {
        vectorLayer->deleteFeature(id);
    }
    std::vector<std::string> uuids = sys->getUUIDsOfComponentsInView(*v);
    if (v->getType() == DM::FACE) {
        foreach (std::string uuid, uuids) {
            QgsFeature feature;
            QVector<QgsPoint> points;
            DM::Face * f = sys->getFace(uuid);
            std::vector<std::string> nodeuuids = f->getNodes();
            foreach (std::string uup, nodeuuids) {
                DM::Node * n = sys->getNode(uup);
                QgsPoint p (n->getX(), n->getY());
                points.push_back(p);
            }
            QgsPolyline poly = QgsPolyline(points);
            QVector<QgsPolyline> vpoly;
            vpoly.push_back(poly);
            QgsPolygon pol(vpoly);
            feature.setGeometry(QgsGeometry::fromPolygon(pol));
            std::cout << "Add feature" << std::endl;
            vectorLayer->addFeature(feature);
        }

    }
}

void QGISDynaMindExport::setLayer(string name) {
    this->qgisname = name;
}

bool QGISDynaMindExport::createInputDialog() {
    QWidget * w = new GUIQGISDynaMindExport(this);
    w->show();
    return true;
}
