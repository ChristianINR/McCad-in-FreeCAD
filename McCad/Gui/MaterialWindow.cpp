#include "MaterialWindow.hpp"
#include "ui_MaterialWindow.h"
#include "moc_MaterialWindow.cpp"
#include <QListWidget>
#include <App/DocumentObject.h>
#include <App/Application.h>
#include <App/Document.h>
#include "McCadUtils.h"

MaterialWindow::MaterialWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaterialWindow)
{
    ui->setupUi(this);

    if(App::GetApplication().getActiveDocument() != nullptr){
        std::vector<App::DocumentObject*> objects = App::GetApplication().getActiveDocument()->getObjects();

        for(int i = 0; i < objects.size(); i++){
            if(McCadUtils::isGroup(objects[i])){
                App::DocumentObject* obj = objects[i];

                ui->listWidget->addItem(QString::fromUtf8(obj->Label.getValue()));
            }
        }

        std::vector<App::DocumentObject*> sel = Gui::Selection().getObjectsOfType
                (App::DocumentObject::getClassTypeId());

//        for(int i = 0; i < sel.size(); i++){
//            Base::Console().Message(sel[i]->Label.getValue());
//        }
    }

}

MaterialWindow::~MaterialWindow()
{
    delete ui;
}
