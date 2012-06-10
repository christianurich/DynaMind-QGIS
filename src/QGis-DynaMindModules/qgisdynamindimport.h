#ifndef QGISDYNAMINDIMPORT_H
#define QGISDYNAMINDIMPORT_H
#include "qgisplugin.h"

#include <dmmodule.h>
#include <dm.h>
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
    void init();
};

#endif // QGISDYNAMINDIMPORT_H
