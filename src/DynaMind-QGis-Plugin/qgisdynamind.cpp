/**
 * @file
 * @author  Chrisitan Urich <christian.urich@gmail.com>
 * @version 1.0
 * @section LICENSE
 *
 * This file is part of DynaMind
 *
 * Copyright (C) 2012  Christian Urich
 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */



#include "qgisdynamind.h"
#include "qgisinterface.h"
#include "dynamindmainwindow.h"
#include "qgsmaplayerregistry.h"
#include <QAction>

#ifdef WIN32
#define QGISEXTERN extern "C" __declspec( dllexport )
#else
#define QGISEXTERN extern "C"
#endif
QGisDynaMind::QGisDynaMind(QgisInterface* iface): mIface(iface)
{
}
QGisDynaMind::~QGisDynaMind()
{
}
void QGisDynaMind::initGui()
{
    mAction = new QAction(tr("&StartDynaMind"), this);
    connect(mAction, SIGNAL(activated()), this, SLOT(startDynaMind()));
    mIface->addToolBarIcon(mAction);
    mIface->addPluginToMenu(tr("&DynaMind"), mAction);
    QMap<QString, QgsMapLayer*> list = QgsMapLayerRegistry::instance()->mapLayers();


    dm =  new DynaMindMainWindow();
    dm->registerNativeDll("/home/c8451045/Documents/QGis-DynaMind/build/debug/libqgis-dynamind-modules.so");
}
void QGisDynaMind::unload()
{
    mIface->removeToolBarIcon(mAction);
    mIface->removePluginMenu(tr("&DynaMind"), mAction);
    delete mAction;
}

void QGisDynaMind::startDynaMind()
{

    qWarning("start DynaMind");

    dm->createMainWindow();

}
QGISEXTERN QgisPlugin* classFactory(QgisInterface* iface)
{
    return new QGisDynaMind(iface);
}
QGISEXTERN QString name()
{
    return "DynaMind Integration";
}
QGISEXTERN QString description()
{
    return "Integrates DynaMind in QGis";
}
QGISEXTERN QString version()
{
    return "0.00001";
}
// Return the type (either UI or MapLayer plugin)
QGISEXTERN int type()
{
    return QgisPlugin::UI;
}
// Delete ourself
QGISEXTERN void unload(QgisPlugin* theQgsPointConverterPluginPointer)
{
    delete theQgsPointConverterPluginPointer;
}


