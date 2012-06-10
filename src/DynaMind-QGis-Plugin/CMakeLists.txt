file(GLOB MODULE_CPPS *.cpp)

include_directories(.)
include_directories(../DMToolboxes)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(/home/c8451045/programms/Quantum-GIS/src/plugins)
include_directories(/home/c8451045/programms/Quantum-GIS/src/gui)
include_directories(/home/c8451045/programms/Quantum-GIS/src/core)
include_directories(/home/c8451045/Documents/DynaMind-Gui/src/libdynamind-gui)
ADD_DEFINITIONS("-DCORE_EXPORT=${DLLIMPORT}")
ADD_DEFINITIONS("-DGUI_EXPORT=${DLLIMPORT}")
ADD_DEFINITIONS("-DPYTHON_EXPORT=${DLLIMPORT}")
ADD_DEFINITIONS("-DANALYSIS_EXPORT=${DLLIMPORT}")
set(MOC_FILES  qgisdynamind.h)

QT4_WRAP_CPP(MODULE_CPPS ${MOC_FILES})



add_library(qgisdynamindplugin SHARED  ${CPP_GUI_FILES} ${MODULE_CPPS})

target_link_libraries(qgisdynamindplugin dynamindtoolbox dynamindcore /home/c8451045/Documents/DynaMind-Gui/build/debug/libdynamindgui.so ${QT_LIBRARIES})

INSTALL(TARGETS qgisdynamindplugin
        DESTINATION "lib"
        PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)


