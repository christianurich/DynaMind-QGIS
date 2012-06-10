FILE(GLOB MODULE_CPPS *.cpp)
FILE(GLOB MODULE_UI_FILES *.ui)

include_directories(/home/c8451045/programms/Quantum-GIS/src/plugins)
include_directories(/home/c8451045/programms/Quantum-GIS/src/gui)
include_directories(/home/c8451045/programms/Quantum-GIS/src/core)

SET(MOC_MODULE_FILES guiqgisdynamindimport.h)



QT4_WRAP_UI(MODULE_CPPS ${MODULE_UI_FILES})
QT4_WRAP_CPP(MODULE_CPPS ${MOC_MODULE_FILES})

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
ADD_LIBRARY(qgis-dynamind-modules SHARED ${MODULE_CPPS})

TARGET_LINK_LIBRARIES(qgis-dynamind-modules ${DYNAMIND_CORE_LIBRARY} ${QT_LIBRARIES})

INSTALL(TARGETS qgis-dynamind-modules
        DESTINATION "lib/DynaMind"
        PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)



