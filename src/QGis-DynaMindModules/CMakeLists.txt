FILE(GLOB MODULE_CPPS *.cpp)
FILE(GLOB MODULE_UI_FILES *.ui)


SET(MOC_MODULE_FILES guiqgisdynamindimport.h guiqgisdynamindexport.h)



QT4_WRAP_UI(MODULE_CPPS ${MODULE_UI_FILES})
QT4_WRAP_CPP(MODULE_CPPS ${MOC_MODULE_FILES})


include_directories(.)
include_directories(${QGIS_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(qgis-dynamind-modules SHARED ${MODULE_CPPS})

target_link_libraries(qgis-dynamind-modules ${QGIS_LIBRARIES} ${DYNAMIND_TOOLBOX_LIBRARY}  ${DYNAMIND_CORE_LIBRARY} ${QT_LIBRARIES})

INSTALL(TARGETS qgis-dynamind-modules
        DESTINATION "lib/DynaMind"
        PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

