#include "editor.h"
//#include "ui_editor.h"
#include "block.h"
#include <QFileDialog>
#include <QGraphicsScene>


EditorMainWindow::EditorMainWindow(QWidget *parent) : QMainWindow(parent){

    // Vytvoreni akci pro menu
    QAction *QA_add = new QAction(tr("&Add"), this);
    QA_add->setStatusTip(tr("Add new block"));
    connect(QA_add, SIGNAL(triggered()), this, SLOT(add_block()));

    QAction *QA_load = new QAction(tr("&Load"), this);
    QA_load->setShortcuts(QKeySequence::Open);
    QA_load->setStatusTip(tr("Open file"));
    connect(QA_load, SIGNAL(triggered()), this, SLOT(load_file()));

    QAction *QA_save = new QAction(tr("&Save"), this);
    QA_save->setShortcuts(QKeySequence::Save);
    QA_save->setStatusTip(tr("Save file"));
    connect(QA_save, SIGNAL(triggered()), this, SLOT(save_file()));

    QAction *QA_quit = new QAction(tr("&Quit"), this);
    QA_quit->setShortcuts(QKeySequence::Quit);
    QA_quit->setStatusTip(tr("Quit the app"));
    connect(QA_quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    QAction *QA_run = new QAction(tr("&Run"), this);
    QA_add->setStatusTip(tr("Run"));
    connect(QA_run, SIGNAL(triggered()), this, SLOT(run_app()));

    QAction *QA_stop = new QAction(tr("&Stop"), this);
    QA_add->setStatusTip(tr("Stop"));
    connect(QA_stop, SIGNAL(triggered()), this, SLOT(stop_app()));

    QAction *QA_debug = new QAction(tr("&Debug"), this);
    QA_add->setStatusTip(tr("Debug"));
    connect(QA_debug, SIGNAL(triggered()), this, SLOT(debug_app()));

    // Nastaveni menu
    menu1 = menuBar()->addMenu(tr("&Schema"));
    menu2 = menuBar()->addMenu(tr("&Block"));
    menu3 = menuBar()->addMenu(tr("&Action"));

    menu1->addAction(QA_save);
    menu1->addAction(QA_load);
    menu1->addSeparator();
    menu1->addAction(QA_quit);
    menu2->addAction(QA_add);
    menu3->addAction(QA_run);
    menu3->addAction(QA_stop);
    menu3->addAction(QA_debug);

    scene = new QGraphicsScene(this);

    // Nastaveni title mainwindow
    setWindowTitle(tr("Schema Editor v1"));


    QDockWidget *schema = new QDockWidget(tr("Schema"), this);
    schema->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    view = new QGraphicsView(this);
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing, true);
    schema->setWidget(view);
    addDockWidget(Qt::LeftDockWidgetArea, schema);

    //nodesEditor = new QNodesEditor(this);
    //nodesEditor->install(scene);

    Block *b = new Block(0);
    scene->addItem(b);
    //b->add_port("test", 0, QNEPort::NamePort);
    //b->add_port("TestBlock", 0, QNEPort::TypePort);
    b->add_input_port("in1");
    b->add_input_port("in2");
    b->add_input_port("in3");
    b->add_output_port("out1");
    b->add_output_port("out2");
    b->add_output_port("out3");

    b = b->clone();
    b->setPos(150, 0);

    b = b->clone();
    b->setPos(150, 150);


}

EditorMainWindow::~EditorMainWindow(){
}

void EditorMainWindow::save_file(){
    QString filename = QFileDialog::getSaveFileName();

    if(filename.isEmpty()) return;

    QFile file(filename);
    file.open(QFile::WriteOnly);
    QDataStream DS(&file);
    // Nodes->save(DS);
}

void EditorMainWindow::load_file(){
    QString filename = QFileDialog::getOpenFileName();

    if(filename.isEmpty()) return;

    QFile file(filename);
    file.open(QFile::ReadOnly);
    QDataStream DS(&file);
    //Nodes->load(DS);
}

void EditorMainWindow::add_block(){
    /*
    Block *block = new Block(0);

    scene->add_item(block);
    // TODO

    //
    static const char* names[] = {"Vin", "Voutsadfasdf", "Imin", "Imax", "mul", "add", "sub", "div", "Conv", "FFT"};
    for (int i = 0; i < 4 + rand() % 3; i++)
    {
        block->add_port(names[rand() % 10], rand() % 2, 0, 0);
        block->set_position(view->sceneRect().center().toPoint());
    }
    */
}
void EditorMainWindow::run_app(){

}
void EditorMainWindow::stop_app(){

}
void EditorMainWindow::debug_app(){

}
