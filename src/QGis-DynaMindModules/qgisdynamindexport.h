#ifndef QGISDYNAMINDEXPORT_H
#define QGISDYNAMINDEXPORT_H
#include <dmmodule.h>
#include <dm.h>
#include <QMap>
class QgsFeature;
using namespace DM;
class DM_HELPER_DLL_EXPORT QGISDynaMindExport : public Module
{
    DM_DECLARE_NODE(QGISDynaMindExport)
    private:
        std::string dataname;
    std::string qgisname;
public:
    void run();
    QGISDynaMindExport();
    void setLayer(std::string name);
    bool createInputDialog();
    bool createFace(QgsFeature * feature, std::string uuid, DM::System * sys);
    bool createEdge(QgsFeature * feature, std::string uuid, DM::System * sys);
    bool createNode(QgsFeature * feature, std::string uuid, DM::System * sys);
    void appenAttributes(QgsFeature * feature, Component * cmp, QMap<QString, int> & attrIndex, QMap<std::string, int> & attrTypes);
};

#endif // QGISDYNAMINDEXPORT_H
