#ifndef QGISDYNAMINDIMPORT_H
#define QGISDYNAMINDIMPORT_H
#include "qgisplugin.h"

#include <dmmodule.h>
#include <dm.h>
#define CORE_EXPORT  __attribute__((dllexport))
#define GUI_EXPORT __attribute__((dllexport))

#include <qgsvectorlayer.h>
class QgsFeature;
class QgsVectorLayer;

class DM_HELPER_DLL_EXPORT QGisDynaMindImport : public  DM::Module {
    DM_DECLARE_NODE (QGisDynaMindImport)
private:
        std::string currentLayer;
        std::string oldLayer;
        std::string dataname;
        long coorindateSystem;
        bool isNode;
        bool isEdge;
        bool isFace;
        DM::View v;
        bool appendToStream;
        QgsAttributeList attrList;
        QString findMap(QString mapName);

public:
    QGisDynaMindImport();
    void run();
    bool createInputDialog();
    void setLayer(std::string name);

    void appendAttributes(DM::Component * cmp, QgsVectorLayer*  vectorLayer, QgsFeature *feature);
    DM::Component * loadNode(DM::System * sys,  QgsFeature *feature);
    DM::Component * loadFace(DM::System * sys,  QgsFeature *feature);
    DM::Component * loadEdge(DM::System * sys,  QgsFeature *feature);
    std::string getHelpUrl();


    void init();
};

#endif // QGISDYNAMINDIMPORT_H
