#include <QtWidgets>
#include <QApplication>
#include "editormainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Setup EditoWindow
    EditorMainWindow window;
    window.show();

    return a.exec();
}
