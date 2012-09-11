#include <QObject>

#include "guiqgisdynamindexport.h"
#include "qgisdynamindexport.h"
#include <qgisplugin.h>
#include <qgsmaplayerregistry.h>
#include <qgsmaplayer.h>
#include <qgsvectorlayer.h>
#include <qgsgeometry.h>


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
    QgsAttributeList alist = vectorLayer->pendingAllAttributesList();
    foreach (int id, alist) {
        //vectorLayer->deleteAttribute(id);
    }

    //Create Attribute Tables
    std::vector<std::string> uuids = sys->getUUIDsOfComponentsInView(*v);
    std::map<std::string, int> attrtypes;
    foreach (std::string uuid, uuids) {
        Component * c = sys->getComponent(uuid);
        std::map<std::string, Attribute*> amap = c->getAllAttributes();
        for (std::map<std::string, Attribute*>::const_iterator it = amap.begin(); it != amap.end(); it++) {
            Attribute * attr = c->getAttribute(it->first);
            switch (attr->getType()) {
            case DM::Attribute::DOUBLE:
                if (attrtypes[it->first] == 0 )
                    attrtypes[it->first] = DM::Attribute::DOUBLE;
                break;
            case DM::Attribute::STRING:
                attrtypes[it->first] = DM::Attribute::STRING;
                break;
            }
        }
    }

    vectorLayer->addAttribute(QgsField("id", QVariant::Int));
    for (std::map<std::string, int>::const_iterator it = attrtypes.begin(); it != attrtypes.end(); it++) {
        if (it->second == DM::Attribute::DOUBLE)
            vectorLayer->addAttribute(QgsField(QString::fromStdString(it->first), QVariant::Double));
        if (it->second == DM::Attribute::STRING)
            vectorLayer->addAttribute(QgsField(QString::fromStdString(it->first), QVariant::String));
    }
    std::map<std::string, int> attrIndex;
    alist = vectorLayer->pendingAllAttributesList();
    foreach (int id, alist) {
        attrIndex[vectorLayer->attributeAlias(id).toStdString()] = id;
    }

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
            std::map<std::string, Attribute*> amap = f->getAllAttributes();
            for (std::map<std::string, Attribute*>::const_iterator it = amap.begin(); it != amap.end(); it++) {
                Attribute * attr = f->getAttribute(it->first);

                switch (attrtypes[it->first]) {
                case DM::Attribute::DOUBLE:
                    feature.addAttribute(attrIndex[it->first], attr->getDouble());
                    break;
                case DM::Attribute::STRING:
                    feature.addAttribute(attrIndex[it->first], QString::fromStdString(attr->getString()));
                    break;
                }
            }
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
