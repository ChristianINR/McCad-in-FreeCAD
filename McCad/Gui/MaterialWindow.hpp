#ifndef MATERIALWINDOW_HPP
#define MATERIALWINDOW_HPP

#include "PreCompiled.h"
#ifndef _PreComp_
#endif

#include <QDialog>

namespace Ui {
class MaterialWindow;
}

class MaterialWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MaterialWindow(QWidget *parent = 0);
    ~MaterialWindow();

private:
    Ui::MaterialWindow *ui;
};

#endif // MATERIALWINDOW_HPP
