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
