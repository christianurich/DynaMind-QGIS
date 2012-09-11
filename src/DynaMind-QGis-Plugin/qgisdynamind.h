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

#ifndef QGISDYNAMIND_H
#define QGISDYNAMIND_H

#include "qgisplugin.h"

#include <QObject>

class QAction;
class DynaMindMainWindow;

class QGisDynaMind : public QObject, public QgisPlugin
{
    Q_OBJECT
public:
    QGisDynaMind(QgisInterface* iface);
    ~QGisDynaMind();


    void initGui();
    void unload();
private:
    QgisInterface* mIface;
    DynaMindMainWindow * dm;
    QAction* mAction;
    private slots:
    void startDynaMind();

};

#endif // QGISDYNAMIND_H
