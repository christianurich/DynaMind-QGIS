file(GLOB MODULE_CPPS *.cpp)

include_directories(.)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../DynaMind-Gui/src/libdynamind-gui)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${QGIS_INCLUDE_DIR})
ADD_DEFINITIONS("-DCORE_EXPORT=${DLLIMPORT}")
ADD_DEFINITIONS("-DGUI_EXPORT=${DLLIMPORT}")
ADD_DEFINITIONS("-DPYTHON_EXPORT=${DLLIMPORT}")
ADD_DEFINITIONS("-DANALYSIS_EXPORT=${DLLIMPORT}")
set(MOC_FILES  qgisdynamind.h)

QT4_WRAP_CPP(MODULE_CPPS ${MOC_FILES})



add_library(qgisdynamindplugin SHARED  ${CPP_GUI_FILES} ${MODULE_CPPS})

target_link_libraries(qgisdynamindplugin dynamindtoolbox dynamindcore dynamindgui  ${QGIS_LIBRARIES} ${QT_LIBRARIES})

INSTALL(TARGETS qgisdynamindplugin
        DESTINATION "lib"
        PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)


