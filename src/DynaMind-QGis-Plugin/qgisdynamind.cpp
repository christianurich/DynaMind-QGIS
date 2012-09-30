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
#include "guiprefdynamind.h"
#include <QDir>
#include <QAction>
#include <QApplication>
#include <QSettings>

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
    Q_INIT_RESOURCE(icons);

    mAction_start = new QAction(tr("&Show"), this);
    //mAction_start->setIcon(QIcon(":/resources/dynamind-icon.png"));
    connect(mAction_start, SIGNAL(activated()), this, SLOT(startDynaMind()));
    mAction_settings = new QAction(tr("&Settings"), this);
    connect(mAction_settings, SIGNAL(activated()), this, SLOT(settingsDynaMind()));
    mIface->addToolBarIcon(mAction_start);
    mIface->addPluginToMenu(tr("&DynaMind"), mAction_start);
    mIface->addPluginToMenu(tr("&DynaMind"), mAction_settings);
    dm = 0;
}
void QGisDynaMind::unload()
{
    mIface->removeToolBarIcon(mAction_start);
    mIface->removePluginMenu(tr("&DynaMind"), mAction_start);
    mIface->removePluginMenu(tr("&DynaMind"), mAction_settings);
    delete mAction_start;
    delete mAction_settings;
}

void QGisDynaMind::startDynaMind()
{
    if (dm)
        delete dm;

    QSettings settingsDynaMind("IUT", "DYNAMIND");
    QString rpath = settingsDynaMind.value("ROOTPATH").toString();
    QStringList libs = QApplication::libraryPaths();
    libs.push_back(rpath);
    QString tmp_path = QDir::currentPath();
    QDir::setCurrent(rpath);
    dm =  new DynaMindMainWindow();
    QDir::setCurrent(tmp_path);

    qWarning("start DynaMind");
    dm->createMainWindow();
}

void QGisDynaMind::settingsDynaMind()
{
    GUIPrefDynaMind * w = new GUIPrefDynaMind();
    w->show();
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
    return "";
}
QGISEXTERN QString version()
{
    return "0.1";
}
// Return the type (either UI or MapLayer plugin)
QGISEXTERN int type()
{
    return QgisPlugin::UI;
}
// Delete ourself
QGISEXTERN void unload(QgisPlugin* plugin)
{
    delete plugin;
}



