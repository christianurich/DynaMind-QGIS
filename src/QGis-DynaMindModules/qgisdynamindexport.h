#ifndef QGISDYNAMINDEXPORT_H
#define QGISDYNAMINDEXPORT_H
#include <dmmodule.h>
#include <dm.h>

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
};

#endif // QGISDYNAMINDEXPORT_H
