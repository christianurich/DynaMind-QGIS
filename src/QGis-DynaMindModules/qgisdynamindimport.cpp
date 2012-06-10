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
    if (this->isEdge) {
        QgsMapLayer * layer = QgsMapLayerRegistry::instance()->mapLayer(QString::fromStdString(this->currentLayer));
        QgsVectorLayer * vectorLayer= (QgsVectorLayer*) layer;
        for (int id = 0; id < vectorLayer->featureCount(); id++ ) {
            QgsFeature feature;            vectorLayer->featureAtId(id, feature);
            QgsAttributeMap attrmap = feature.attributeMap();
            QgsGeometry * geo = feature.geometry();
            QgsPolyline pol= geo->asPolyline();
            DM::Node * prev = 0;
            DM::Node * cur = 0;

            foreach (QgsPoint p, pol) {
                cur = sys->addNode(p.x(), p.y(), 0);
                if (prev) {
                    DM::Edge * e = sys->addEdge(cur, prev, v);
                    foreach (int id, attrmap.keys()) {
                        QVariant val = attrmap[id];
                        if (val.canConvert(QVariant::Double)) {
                            e->addAttribute(vectorLayer->attributeDisplayName(id).toStdString(), val.toDouble());
                            continue;
                        }
                        if (val.canConvert(QVariant::String)) {
                            DM::Attribute at(vectorLayer->attributeDisplayName(id).toStdString());
                            at.setString(val.toString().toStdString());
                            e->addAttribute(at);
                            continue;
                        }

                    }

                }
                prev = cur;
            }


        }


    }
    DM::Logger(DM::Debug) << "Number of added Elements " << sys->getUUIDsOfComponentsInView(v).size();

}

void QGisDynaMindImport::setLayer(string name) {
    this->currentLayer = name;
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
