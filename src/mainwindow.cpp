/*!
 * School project for subject (The C++ Programming Language).
 * This application is graphical editor of mathematical schemes.
 * For more information chech readme.txt
 *
 * @author Petr Knetl
 * @author Marek Kalabza
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Nastaveni UI

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    // Smazani UI

    delete ui;
}
