#include <QObject>

#include "qgisdynamindimport.h"
#include "guiqgisdynamindimport.h"
#include <qgsmaplayerregistry.h>
#include <qgsmaplayer.h>
#include <qgsvectorlayer.h>
#include <qgsvectordataprovider.h>
#include <qgsgeometry.h>

DM_DECLARE_NODE_NAME(QGisDynaMindImport, QGIS)
QGisDynaMindImport::QGisDynaMindImport()
{
    this->currentLayer = "";
    this->oldLayer = "";
    this->addParameter("CurrentLayer", DM::STRING, &this->currentLayer);
    this->addParameter("DataName", DM::STRING, &this->dataname);
    this->isNode = false;
    this->isEdge = false;
    this->isFace = false;
}

void QGisDynaMindImport::run() {
    DM::System * sys;
    sys = this->getData("QGisIn");

    QgsMapLayer * layer = QgsMapLayerRegistry::instance()->mapLayer(QString::fromStdString(this->currentLayer));
    QgsVectorLayer * vectorLayer= (QgsVectorLayer*) layer;
    for (int id = 0; id < vectorLayer->featureCount(); id++ ) {
        QgsFeature feature;
        vectorLayer->featureAtId(id, feature);
        DM::Component * cmp = 0;
        if (this->isNode) {
            cmp = this->loadNode(sys, &feature);
        }
        if (this->isEdge) {
            cmp = this->loadEdge(sys, &feature);
        }
        if (this->isFace) {
            cmp = this->loadFace(sys, &feature);
        }
        this->appendAttributes(cmp, vectorLayer, &feature);
    }

    DM::Logger(DM::Debug) << "Number of added Elements " << sys->getUUIDsOfComponentsInView(v).size();

}

void QGisDynaMindImport::setLayer(string name) {
    this->currentLayer = name;
}

void QGisDynaMindImport::appendAttributes(DM::Component *cmp,QgsVectorLayer*  vectorLayer, QgsFeature *feature)
{
    if (!cmp)
        return;
    QgsAttributeMap attrmap = feature->attributeMap();
    foreach (int id, attrmap.keys()) {
        QVariant val = attrmap[id];
        if (val.canConvert(QVariant::Double)) {
            cmp->addAttribute(vectorLayer->attributeDisplayName(id).toStdString(), val.toDouble());
            continue;
        }
        if (val.canConvert(QVariant::String)) {
            DM::Attribute at(vectorLayer->attributeDisplayName(id).toStdString());
            at.setString(val.toString().toStdString());
            cmp->addAttribute(at);
            continue;
        }

    }
}

void QGisDynaMindImport::init() {
    if (currentLayer.empty())
        return;

    QMap<QString, QgsMapLayer*> list = QgsMapLayerRegistry::instance()->mapLayers();
    QgsMapLayer * layer = QgsMapLayerRegistry::instance()->mapLayer(QString::fromStdString(this->currentLayer));
    QgsVectorLayer * vectorLayer= (QgsVectorLayer*) layer;


    if (QGis::Point == vectorLayer->geometryType()) {
        DM::Logger(DM::Debug) << "Point Selected";
        v = DM::View(dataname, DM::NODE, DM::WRITE);
        this->isNode = true;
        this->isEdge = false;
        this->isFace = false;
    }
    if (QGis::Line == vectorLayer->geometryType()) {
        DM::Logger(DM::Debug) << "Line Selected";
        v = DM::View(dataname, DM::EDGE, DM::WRITE);
        this->isNode = false;
        this->isEdge = true;
        this->isFace = false;

    }
    if (QGis::Polygon == vectorLayer->geometryType()) {
        DM::Logger(DM::Debug) << "Polygon Selected";
        v = DM::View(dataname, DM::FACE, DM::WRITE);
        this->isNode = false;
        this->isEdge = false;
        this->isFace = true;
    }
    QgsAttributeList alist = vectorLayer->pendingAllAttributesList();
    foreach (int id, alist) {
        v.addAttribute(vectorLayer->attributeDisplayName(id).toStdString());
    }
    std::vector<DM::View> data;
    data.push_back(v);
    this->addData("QGisIn", data);
}

bool QGisDynaMindImport::createInputDialog() {
    QWidget * w = new GUIQGisDynaMindImport(this);
    w->show();
    return true;
}


DM::Component *QGisDynaMindImport::loadEdge(DM::System *sys, QgsFeature *feature)
{
    QgsGeometry * geo = feature->geometry();
    QgsPolyline pol= geo->asPolyline();
    DM::Node * prev = 0;
    DM::Node * cur = 0;
    DM::Edge * e  = 0;
    foreach (QgsPoint p, pol) {
        cur = sys->addNode(p.x(), p.y(), 0);
        if (prev) {
            e = sys->addEdge(cur, prev, v);
        }
        prev = cur;
    }
    return e;
}
DM::Component *QGisDynaMindImport::loadNode(DM::System *sys, QgsFeature *feature)
{
    QgsGeometry * geo = feature->geometry();
    QgsPoint p= geo->asPoint();
    DM::Node * n = sys->addNode(p.x(), p.y(), 0, v);
    return n;
}

DM::Component *QGisDynaMindImport::loadFace(DM::System *sys, QgsFeature *feature)
{
    QgsGeometry * geo = feature->geometry();
    QgsPolygon pol= geo->asPolygon();
    DM::Face * f  = 0;
    std::vector<DM::Node *> nodes;
    foreach (QVector<QgsPoint> vpol,pol ) {
        foreach (QgsPoint p, vpol) {
            DM::Node * n = sys->addNode(p.x(), p.y(), 0);
            if (n != 0) {
                nodes.push_back(n);
            }
        }
    }
    if (nodes.size() < 3)
        return 0;
    f = sys->addFace(nodes, v);

    return f;
}
