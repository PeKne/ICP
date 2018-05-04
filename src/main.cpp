/*!
 * School project for subject (The C++ Programming Language).
 * This application is graphical editor of mathematical schemes.
 * For more information chech readme.txt
 *
 * @author Petr Knetl
 * @author Marek Kalabza
 */

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
