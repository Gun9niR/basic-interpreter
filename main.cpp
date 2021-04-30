#include "MainWindow.h"
#include "Interpreter.h"

#include <QApplication>
#include "Basic.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow& w = MainWindow::getInstance();

    w.show();
    return a.exec();
}
