#ifndef QGISDYNAMINDIMPORT_H
#define QGISDYNAMINDIMPORT_H
#include "qgisplugin.h"

#include <dmmodule.h>
#include <dm.h>

class QgsFeature;
class QgsVectorLayer;
class DM_HELPER_DLL_EXPORT QGisDynaMindImport : public  DM::Module {
    DM_DECLARE_NODE (QGisDynaMindImport)
private:
        std::string currentLayer;
        std::string oldLayer;
        std::string dataname;
        bool isNode;
        bool isEdge;
        bool isFace;
        DM::View v;

public:
    QGisDynaMindImport();
    void run();
    bool createInputDialog();
    void setLayer(std::string name);

    void appendAttributes(DM::Component * cmp, QgsVectorLayer*  vectorLayer, QgsFeature *feature);
    DM::Component * loadNode(DM::System * sys,  QgsFeature *feature);
    DM::Component * loadFace(DM::System * sys,  QgsFeature *feature);
    DM::Component * loadEdge(DM::System * sys,  QgsFeature *feature);


    void init();
};

#endif // QGISDYNAMINDIMPORT_H
