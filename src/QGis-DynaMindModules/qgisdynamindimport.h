#ifndef QGISDYNAMINDIMPORT_H
#define QGISDYNAMINDIMPORT_H
#include "qgisplugin.h"

#include <dmmodule.h>



class DM_HELPER_DLL_EXPORT QGisDynaMindImport : public  DM::Module {
    DM_DECLARE_NODE (QGisDynaMindImport)
private:
        std::string currentLayer;
        std::string oldLayer;

public:
    QGisDynaMindImport();
    void run();
    bool createInputDialog();
    void setLayer(std::string name);
    void init();
};

#endif // QGISDYNAMINDIMPORT_H
