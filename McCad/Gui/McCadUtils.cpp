#include "McCadUtils.h"
#include <cstdlib>
#include <ctime>
#include <Gui/Tree.h>
#include <string>

bool McCadUtils::isGroup(App::DocumentObject* object)
{
    return object->getTypeId() == App::DocumentObjectGroup::getClassTypeId();
}

bool McCadUtils::isAtRootLevel(App::DocumentObject* object)
{
    return object->getGroup() == 0;
}

std::vector<App::DocumentObject*> McCadUtils::findSubobjects(App::DocumentObjectGroup* group)
{
    std::vector<App::DocumentObject*> nonGroupSubobjects;

    std::vector<App::DocumentObject*> allSubobjects = group->getObjects();
    for(int i = 0; i < allSubobjects.size(); i++){
        if(!isGroup(allSubobjects[i])){
            nonGroupSubobjects.push_back(allSubobjects[i]);
        }else{
            std::vector<App::DocumentObject*> nonGroupSubSubobjects = findSubobjects(dynamic_cast<App::DocumentObjectGroup*>(allSubobjects[i]));
            nonGroupSubobjects.insert(nonGroupSubobjects.end(),
                                      nonGroupSubSubobjects.begin(),
                                      nonGroupSubSubobjects.end());
        }
    }

    return nonGroupSubobjects;
}

void McCadUtils::setSeed()
{
    std::srand(std::time(0));
}

void McCadUtils::colorObjects(std::vector<App::DocumentObject*> objects)
{
    float randomR = ((float) rand()) / (float) RAND_MAX;
    float randomG = ((float) rand()) / (float) RAND_MAX;
    float randomB = ((float) rand()) / (float) RAND_MAX;

    Gui::Command::openCommand("Color Solids");
    for(int i = 0; i < objects.size(); i++){
        const char* label = objects[i]->getNameInDocument();
        Gui::Command::doCommand(Gui::Command::DoCmd_Type::Doc, "Gui.ActiveDocument.getObject(\"%s\").ShapeColor = (%.5f, %.5f, %.5f)", label, randomR, randomG, randomB);
    }
    Gui::Command::commitCommand();
}

void McCadUtils::colorGroup(App::DocumentObjectGroup* group)
{
    std::vector<App::DocumentObject*> objects = findSubobjects(group);
    colorObjects(objects);
}

void McCadUtils::colorAllGroups()
{
    //setSeed();

    if(App::GetApplication().getActiveDocument() == nullptr){
        return;
    }

    //Base::Console().Message("color all");

    std::vector<App::DocumentObject*> objects = App::GetApplication().getActiveDocument()->getObjects();
    for(int i = 0; i < objects.size(); i++){
        if(isGroup(objects[i]) && isAtRootLevel(objects[i])){
            colorGroup(dynamic_cast<App::DocumentObjectGroup*>(objects[i]));
        }
    }
}

void McCadUtils::importStepFile()
{
    QStringList inputFiles = Gui::FileDialog::getOpenFileNames(Gui::getMainWindow(),
                                                               QString::fromAscii("Import STEP files"),
                                                               QString(),
                                                               QLatin1String("STEP (*.stp *.step)"));
    if(inputFiles.size() == 0){
        return;
    }

    if(App::GetApplication().getActiveDocument() == nullptr){
        App::GetApplication().newDocument("Unnamed", "Unnamed");
        App::GetApplication().setActiveDocument(App::GetApplication().getDocument("Unnamed"));
    }


    for(int i = 0; i < inputFiles.size(); i++){
        App::DocumentObjectGroup* newGroup = new App::DocumentObjectGroup();

        int numberOfObjects = App::GetApplication().getActiveDocument()->getObjects().size();

        App::GetApplication().getActiveDocument()->addObject(newGroup, createGroupName(inputFiles[i]).toLatin1().data());
        //App::GetApplication().getActiveDocument()->addObject("App::DocumentObjectGroup", createGroupName(inputFiles[i]).toLatin1().data());

        Gui::Command::openCommand("ImportStepFile");

        Gui::Command::doCommand(Gui::Command::DoCmd_Type::Doc,
                                "import ImportGui");
        Gui::Command::doCommand(Gui::Command::DoCmd_Type::Doc,
                                "ImportGui.insert(u\"%s\", \"%s\")",
                                (const char*)inputFiles[i].toUtf8(),
                                App::GetApplication().getActiveDocument()->getName());
        Gui::Command::doCommand(Gui::Command::DoCmd_Type::Doc,
                                "Gui.SendMsgToActiveView(\"ViewFit\")");

        Gui::Command::commitCommand();
        Gui::Command::updateActive();

        std::vector<App::DocumentObject*> objects = App::GetApplication().getActiveDocument()->getObjects();

        std::vector<App::DocumentObject*>::const_iterator first = objects.begin() + numberOfObjects + 1;
        std::vector<App::DocumentObject*>::const_iterator last = objects.end();
        std::vector<App::DocumentObject*> newObjects(first, last);

        for(int j = 0; j < newObjects.size(); j++){
            newGroup->addObject(newObjects[j]);
        }

        int largestSolidIndex = findLargestSolidIndex();
        renameSolids(newObjects, largestSolidIndex + 1);

        setSeed();
        colorGroup(newGroup);

    }

}

QString McCadUtils::createGroupName(const QString& path){
    QString separator1 = QString::fromAscii("\\");
    QString separator2 = QString::fromAscii("/");
    int lastSeparator1 = path.lastIndexOf(separator1);
    int lastSeparator2 = path.lastIndexOf(separator2);
    if(lastSeparator1 != -1){
        return path.mid(lastSeparator1 + 1);
    }else{
        return path.mid(lastSeparator2 + 1);
    }
}

int McCadUtils::findLargestSolidIndex()
{
    QString solidSearchPhrase = QString::fromAscii("Solid");
    std::vector<App::DocumentObject*> objects = App::GetApplication().getActiveDocument()->getObjects();

    int largestSolidIndex = 0;

    for(int i = 0; i < objects.size(); i++){
        QString label = QString::fromUtf8(objects[i]->Label.getValue());
        int positionOfSolidSearchPhrase = label.indexOf(solidSearchPhrase, Qt::CaseInsensitive);
        if(positionOfSolidSearchPhrase != -1){
            bool ok = false;
            int currentSolidIndex = label.mid(5).toInt(&ok);
            if(ok && currentSolidIndex > largestSolidIndex){
                largestSolidIndex = currentSolidIndex;
            }
        }
    }
    return largestSolidIndex;
}

void McCadUtils::renameSolids(std::vector<App::DocumentObject*> objects, int firstSolidIndex)
{
    for(int i = 0; i < objects.size(); i++){
        objects[i]->Label.setValue("Solid " + std::to_string(firstSolidIndex + i));
    }
}

void McCadUtils::dumpDocumentObjects()
{
    std::vector<App::DocumentObject*> documentObjects = App::GetApplication().getActiveDocument()->getObjects();
    for(int i = 0; i < documentObjects.size(); i++){
        App::DocumentObject* obj = documentObjects[i];
        Base::Console().Message(obj->getTypeId().getName());
        Base::Console().Message("\n");
    }
}
