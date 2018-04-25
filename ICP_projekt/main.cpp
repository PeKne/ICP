#include "editor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditorMainWindow win;
    win.show();

    return a.exec();
}
