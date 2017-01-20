/***************************************************************************
 *   Copyright (c) YEAR YOUR NAME         <Your e-mail address>            *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#include "PreCompiled.h"

#ifndef _PreComp_
#endif

#include "Workbench.h"
#include <Gui/MenuManager.h>
#include <Gui/ToolBarManager.h>
#include "McCadUtils.h"

using namespace McCadGui;

/// @namespace McCadGui @class Workbench
TYPESYSTEM_SOURCE(McCadGui::Workbench, Gui::StdWorkbench)

Workbench::Workbench()
{
    McCadUtils::setSeed();
}

Workbench::~Workbench()
{
}

Gui::MenuItem* Workbench::setupMenuBar() const
{
//    Gui::MenuItem* root = StdWorkbench::setupMenuBar();
//    Gui::MenuItem* item = root->findItem( "&Windows" );
//    Gui::MenuItem* test = new Gui::MenuItem;
//    root->insertItem( item, test );
//    test->setCommand("McCad");
//    *test << "McCad_Test";
//    return root;

    Gui::MenuItem* root = StdWorkbench::setupMenuBar();
    Gui::MenuItem* item = root->findItem("&Windows"); // find menu item in menu bar labelled "Windows"
    Gui::MenuItem* mccad = new Gui::MenuItem;
    root->insertItem(item, mccad);                      // insert new item before item "Windows"
    mccad->setCommand("McCad");                         // name if menu item
    *mccad << "McCad_Import" << "McCad_ColorGroups" << "McCad_ShowMaterialWindow";
           //<< "Separator" << "McCad_Split";          // entries in menu

//    Gui::MenuItem* mccadTest = new Gui::MenuItem;
//    Gui::MenuItem* newItem = root->findItem("McCad");
//    root->insertItem(newItem, mccadTest);
//    mccadTest->setCommand("McCad2");
//    *mccadTest << "McCad_ShowMaterialWindow";

    return root;
}

Gui::ToolBarItem* Workbench::setupToolBars() const
{
//    Gui::ToolBarItem* root = StdWorkbench::setupToolBars();
//    Gui::ToolBarItem* test = new Gui::ToolBarItem(root);
//    test->setCommand( "McCad Tools" );
//    *test << "McCad_Test";
//    return root;

    Gui::ToolBarItem* root = StdWorkbench::setupToolBars();
    Gui::ToolBarItem* mccad = new Gui::ToolBarItem(root);
    mccad->setCommand("McCad Tools");
    *mccad << "McCad_Import" << "McCad_ColorGroups" << "McCad_ShowMaterialWindow";
    return root;
}

void Workbench::setupContextMenu(const char* recipient, Gui::MenuItem* menuItem) const
{
    if(strcmp(recipient, "View")){
        //Base::Console().Message(recipient);
        *menuItem << "McCad_ShowMaterialWindow" << "Separator"
                  << "Std_ShowSelection" << "Std_HideSelection" << "Std_ToggleSelectability" << "Separator"
                  << "Std_SetAppearance" << "Std_ToggleVisibility" << "Std_RandomColor" << "Separator"
                  << "Std_Delete";
    }
}
