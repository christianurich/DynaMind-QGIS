#include <QObject>

#include "guiqgisdynamindexport.h"
#include "qgisdynamindexport.h"
#include <qgisplugin.h>
#include <qgsmaplayerregistry.h>
#include <qgsmaplayer.h>
#include <qgsvectorlayer.h>
#include <qgsgeometry.h>
#include <qgsvectordataprovider.h>


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

    //Create Attribute Tables
    std::vector<std::string> uuids = sys->getUUIDsOfComponentsInView(*v);
    QMap<std::string, int> attrTypes;
    foreach (std::string uuid, uuids) {
        Component * c = sys->getComponent(uuid);
        std::map<std::string, Attribute*> amap = c->getAllAttributes();
        for (std::map<std::string, Attribute*>::const_iterator it = amap.begin(); it != amap.end(); it++) {
            Attribute * attr = c->getAttribute(it->first);
            switch (attr->getType()) {
            case DM::Attribute::DOUBLE:
                if (attrTypes[it->first] == 0 )
                    attrTypes[it->first] = DM::Attribute::DOUBLE;
                break;
            case DM::Attribute::STRING:
                attrTypes[it->first] = DM::Attribute::STRING;
                break;
            }
        }
    }
    QList<QgsField> attributes;
    QMap<QString, int> attrIndex = vectorLayer->dataProvider()->fieldNameMap();
    foreach(std::string key, attrTypes.keys()) {
        if (attrIndex.contains((QString::fromStdString(key))))
            continue;
        if (attrTypes[key] == DM::Attribute::DOUBLE) {
            attributes.push_back(QgsField(QString::fromStdString(key), QVariant::Double));

        }
        if (attrTypes[key]  == DM::Attribute::STRING) {
            attributes.push_back(QgsField(QString::fromStdString(key), QVariant::String));
        }
    }
    vectorLayer->dataProvider()->addAttributes(attributes);
    vectorLayer->updateFieldMap();

    attrIndex = vectorLayer->dataProvider()->fieldNameMap();

    foreach (std::string uuid, uuids) {
        QgsFeature feature;
        if (v->getType() == DM::NODE) {
            if (!createNode(&feature, uuid, sys))
                continue;
        }
        if (v->getType() == DM::EDGE) {
            if (!createEdge(&feature, uuid, sys))
                continue;
        }
        if (v->getType() == DM::FACE) {
            if (!createFace(&feature, uuid, sys))
                continue;
        }

        appenAttributes(&feature, sys->getComponent(uuid), attrIndex, attrTypes);
        vectorLayer->addFeature(feature);
    }
}
bool QGISDynaMindExport::createFace(QgsFeature * feature, std::string uuid, DM::System * sys) {
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
    feature->setGeometry(QgsGeometry::fromPolygon(pol));

    return true;
}

bool QGISDynaMindExport::createEdge(QgsFeature * feature, std::string uuid, DM::System * sys) {
    QVector<QgsPoint> points;
    DM::Edge * e = sys->getEdge(uuid);
    DM::Node * n1 = sys->getNode(e->getStartpointName());
    DM::Node * n2 = sys->getNode(e->getEndpointName());
    QgsPoint p1 (n1->getX(), n1->getY());
    QgsPoint p2 (n2->getX(), n2->getY());
    points.push_back(p1);
    points.push_back(p2);
    QgsPolyline poly = QgsPolyline(points);
    feature->setGeometry(QgsGeometry::fromPolyline(poly));
    return true;
}

bool QGISDynaMindExport::createNode(QgsFeature * feature, std::string uuid, DM::System * sys) {
    DM::Node * n = sys->getNode(uuid);
    QgsPoint p (n->getX(), n->getY());
    feature->setGeometry(QgsGeometry::fromPoint(p));
    return true;
}


void QGISDynaMindExport::appenAttributes(QgsFeature * feature, Component * cmp, QMap<QString, int> & attrIndex, QMap<std::string, int> & attrTypes) {
    std::map<std::string, Attribute*> amap = cmp->getAllAttributes();
    for (std::map<std::string, Attribute*>::const_iterator it = amap.begin(); it != amap.end(); it++) {
        Attribute * attr = cmp->getAttribute(it->first);
        switch (attrTypes[it->first]) {
        case DM::Attribute::DOUBLE:
            feature->addAttribute(attrIndex[QString::fromStdString(it->first)], attr->getDouble());
            break;
        case DM::Attribute::STRING:
            feature->addAttribute(attrIndex[QString::fromStdString(it->first)], QString::fromStdString(attr->getString()));
            break;
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
