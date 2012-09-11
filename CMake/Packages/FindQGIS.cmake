# - Try to find QGLViewer
# Once done this will define
#
#  QGIS_FOUND - system has QGLViewer
#  QGIS_INCLUDE_DIR - the QGLViewer include directory
#  QGIS_LIBRARIES - Link these to use QGLViewer
#  QGIS_DEFINITIONS - Compiler switches required for using QGLViewer
#

find_path(QGIS_INCLUDE_DIR 
          NAMES qgisinterface.h
          PATHS /usr/include/qgis
                /usr/local/include/qgis
                ENV QGISROOT
         )

find_library(QGIS_LIBRARY_RELEASE 
             NAMES qgis_core
             PATHS /usr/lib
                   /usr/local/lib
                   ENV QGISROOT
                   ENV LD_LIBRARY_PATH
                   ENV LIBRARY_PATH
            )

find_library(QGIS_LIBRARY_DEBUG
             NAMES dqgis_core
             PATHS /usr/lib
                   /usr/local/lib
                   ENV QGLVIEWERROOT
                   ENV LD_LIBRARY_PATH
                   ENV LIBRARY_PATH   
            )

if(QGIS_LIBRARY_RELEASE)
  if(QGIS_LIBRARY_DEBUG)
    set(QGIS_LIBRARIES_ optimized ${QGIS_LIBRARY_RELEASE} debug ${QGIS_LIBRARY_DEBUG})
  else()
    set(QGIS_LIBRARIES_ ${QGIS_LIBRARY_RELEASE})
  endif()

  set(QGIS_LIBRARIES ${QGIS_LIBRARIES_} CACHE FILEPATH "The QGIS library")

endif()


IF(QGIS_INCLUDE_DIR AND QGIS_LIBRARIES)
   SET(QGIS_FOUND TRUE)
ENDIF(QGIS_INCLUDE_DIR AND QGIS_LIBRARIES)

IF(QGIS_FOUND)
  IF(NOT QGIS_FIND_QUIETLY)
    MESSAGE(STATUS "Found QGIS: ${QGIS_LIBRARIES}")
  ENDIF(NOT QGIS_FIND_QUIETLY)
ELSE(QGIS_FOUND)
  IF(QQGIS_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find QGIS")
  ENDIF(QGIS_FIND_REQUIRED)
ENDIF(QGIS_FOUND)

