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

#include <Base/Console.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/Document.h>
#include <Gui/MainWindow.h>
#include <Gui/FileDialog.h>
#include <Gui/ViewProviderDocumentObject.h>
#include <Gui/ViewProviderDocumentObjectGroup.h>
#include <App/DocumentObjectGroup.h>
#include <QString>
#include <cstdlib>
#include <ctime>
#include "McCadUtils.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===========================================================================
// CmdMcCadTest THIS IS JUST A TEST COMMAND
//===========================================================================
//DEF_STD_CMD(CmdMcCadTest);

//CmdMcCadTest::CmdMcCadTest()
//  :Command("McCad_Test")
//{
//    sAppModule    = "McCad";
//    sGroup        = QT_TR_NOOP("McCad");
//    sMenuText     = QT_TR_NOOP("Hello");
//    sToolTipText  = QT_TR_NOOP("McCad Test function");
//    sWhatsThis    = QT_TR_NOOP("McCad Test function");
//    sStatusTip    = QT_TR_NOOP("McCad Test function");
//    sPixmap       = "Test1";
//    sAccel        = "CTRL+H";
//}

//void CmdMcCadTest::activated(int iMsg)
//{
//    Base::Console().Message("Hello, World!\n");
//}

//void CreateMcCadCommands(void)
//{
//    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
//    rcCmdMgr.addCommand(new CmdMcCadTest());
//}

// New Command/Function
DEF_STD_CMD(CmdMcCadSplit)

CmdMcCadSplit::CmdMcCadSplit()
    :Command("McCad_Split")
{
    sAppModule      = "McCad";
    sGroup          = QT_TR_NOOP("McCad");
    sMenuText       = QT_TR_NOOP("Split");
    sToolTipText    = QT_TR_NOOP("Split");
    sWhatsThis      = QT_TR_NOOP("Split");
    sStatusTip      = QT_TR_NOOP("Split");
    sPixmap         = "axe.svg";
    sAccel          = "CTRL+S";
}

void CmdMcCadSplit::activated(int iMsg)
{
    Base::Console().Message("McCad Split activated!\n");
}

DEF_STD_CMD(CmdMcCadSplit2)

CmdMcCadSplit2::CmdMcCadSplit2()
    :Command("McCad_Split2")
{
    sAppModule      = "McCad";
    sGroup          = QT_TR_NOOP("McCad");
    sMenuText       = QT_TR_NOOP("Split2");
    sToolTipText    = QT_TR_NOOP("Split2");
    sWhatsThis      = QT_TR_NOOP("Split2");
    sStatusTip      = QT_TR_NOOP("Split2");
    sPixmap         = "axe.svg";
    sAccel          = "CTRL+T";
}

void CmdMcCadSplit2::activated(int iMsg)
{
    Base::Console().Message("McCad Split 2 activated!\n");
}


DEF_STD_CMD(CmdMcCadImport)

CmdMcCadImport::CmdMcCadImport()
    : Command("McCad_Import")
{
    sAppModule      = "McCad";
    sGroup          = QT_TR_NOOP("McCad");
    sMenuText       = QT_TR_NOOP("Import");
    sToolTipText    = QT_TR_NOOP("Import");
    sWhatsThis      = QT_TR_NOOP("Import");
    sStatusTip      = QT_TR_NOOP("Import");
    sPixmap         = "open.svg";
    sAccel          = "CTRL+I";

}

void CmdMcCadImport::activated(int iMsg)
{
    McCadUtils::importStepFile();
}


DEF_STD_CMD(CmdMcCadColorGroups)

CmdMcCadColorGroups::CmdMcCadColorGroups()
    : Command("McCad_ColorGroups")
{
    sAppModule      = "McCad";
    sGroup          = QT_TR_NOOP("McCad");
    sMenuText       = QT_TR_NOOP("Auto color for groups");
    sToolTipText    = QT_TR_NOOP("Auto color for groups");
    sWhatsThis      = QT_TR_NOOP("Auto color for groups");
    sStatusTip      = QT_TR_NOOP("Auto color for groups");
    sPixmap         = "color.svg";
    //sAccel          = "CTRL+I";

}

void CmdMcCadColorGroups::activated(int iMsg)
{
    McCadUtils::colorAllGroups();
}

void CreateMcCadCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdMcCadSplit());
    rcCmdMgr.addCommand(new CmdMcCadColorGroups());
    rcCmdMgr.addCommand(new CmdMcCadImport());
}


