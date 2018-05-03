#include "editormainwindow.h"
#include "ui_mainwindow.h"

#include "editor.h"
#include "connections.h"
#include "port.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <unistd.h>

#include <QGraphicsScene>
#include <QFileDialog>
#include <QInputDialog>
#include <QThread>
#include <QMessageBox>
#include <algorithm>

using namespace std;

EditorMainWindow::EditorMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Nova scena
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,850,850);

    // Vytvoreni akci pro menu
    QAction *QA_add = new QAction(tr("&Add Block+"), this);
    QA_add->setStatusTip(tr("Add new block+"));
    connect(QA_add, SIGNAL(triggered()), this, SLOT(add_block_add()));

    QAction *QA_sub = new QAction(tr("&Add Block-"), this);
    QA_add->setStatusTip(tr("Add new block-"));
    connect(QA_sub, SIGNAL(triggered()), this, SLOT(add_block_sub()));

    QAction *QA_div = new QAction(tr("&Add Block/"), this);
    QA_add->setStatusTip(tr("Add new block/"));
    connect(QA_div, SIGNAL(triggered()), this, SLOT(add_block_div()));

    QAction *QA_mul = new QAction(tr("&Add Block*"), this);
    QA_add->setStatusTip(tr("Add new block*"));
    connect(QA_mul, SIGNAL(triggered()), this, SLOT(add_block_mul()));

    QAction *QA_pow = new QAction(tr("&Add Block^"), this);
    QA_pow->setStatusTip(tr("Add new block^"));
    connect(QA_pow, SIGNAL(triggered()), this, SLOT(add_block_pow()));

    QAction *QA_output = new QAction(tr("&Add Block Output"), this);
    QA_add->setStatusTip(tr("Add new OUTPUT"));
    connect(QA_output, SIGNAL(triggered()), this, SLOT(add_block_output()));

    QAction *QA_input = new QAction(tr("&Add Block Input"), this);
    QA_add->setStatusTip(tr("Add new INPUT"));
    connect(QA_input, SIGNAL(triggered()), this, SLOT(add_block_input()));

    QAction *QA_run = new QAction(tr("&Run"), this);
    QA_add->setStatusTip(tr("Run"));
    connect(QA_run, SIGNAL(triggered()), this, SLOT(run_app()));

    QAction *QA_reset = new QAction(tr("&Reset"), this);
    QA_add->setStatusTip(tr("Stop"));
    connect(QA_reset, SIGNAL(triggered()), this, SLOT(reset_app()));

    QAction *QA_debug = new QAction(tr("&Debug"), this);
    QA_add->setStatusTip(tr("Debug"));
    connect(QA_debug, SIGNAL(triggered()), this, SLOT(debug_app()));

    QAction *QA_load = new QAction(tr("&Load"), this);
    QA_load->setShortcuts(QKeySequence::Open);
    QA_load->setStatusTip(tr("Open file"));
    connect(QA_load, SIGNAL(triggered()), this, SLOT(load_schema()));

    QAction *QA_save = new QAction(tr("&Save"), this);
    QA_save->setShortcuts(QKeySequence::Save);
    QA_save->setStatusTip(tr("Save file"));
    connect(QA_save, SIGNAL(triggered()), this, SLOT(save_schema()));

    QAction *QA_new = new QAction(tr("&New"), this);
    QA_new->setStatusTip(tr("New file"));
    connect(QA_new, SIGNAL(triggered()), this, SLOT(new_schema()));

    QAction *QA_quit = new QAction(tr("&Quit"), this);
    QA_quit->setShortcuts(QKeySequence::Quit);
    QA_quit->setStatusTip(tr("Quit the app"));
    connect(QA_quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Vytvoreni menu
    menu1 = menuBar()->addMenu(tr("&Schema"));
    menu2 = menuBar()->addMenu(tr("&Block"));
    menu3 = menuBar()->addMenu(tr("&Action"));

    // Nastaveni akci pro menu
    menu1->addAction(QA_new);
    menu1->addAction(QA_save);
    menu1->addAction(QA_load);
    menu1->addSeparator();
    menu1->addAction(QA_quit);

    menu2->addAction(QA_add);
    menu2->addAction(QA_sub);
    menu2->addAction(QA_div);
    menu2->addAction(QA_mul);
    menu2->addAction(QA_pow);
    menu2->addAction(QA_input);
    menu2->addAction(QA_output);

    menu3->addAction(QA_debug);
    menu3->addAction(QA_run);
    menu3->addAction(QA_reset);

    setWindowTitle(tr("BlockEditor"));

    // Vytvoreni docku
    QDockWidget *dock = new QDockWidget(tr(""), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    // Pohled pro dock
    view = new QGraphicsView(dock);
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing, true);

    dock->setWidget(view);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    // Prirazeni
    editor = new Editor(this);
    editor->install(scene);


    // Priprava 5 bloku pro ukazku

    add_block_add();
    add_block_div();
    add_block_sub();
    add_block_pow();
    add_block_mul();

}

EditorMainWindow::~EditorMainWindow()
{

}

void EditorMainWindow::save_schema()
{
    QString filename = QFileDialog::getSaveFileName();
    if(filename.isEmpty())
    {
        return;
    }

    QFile file(filename);
    file.open(QFile::WriteOnly);
    QDataStream DS(&file);

    editor->save(DS);
}

void EditorMainWindow::load_schema()
{
    QString fname = QFileDialog::getOpenFileName();
    if (fname.isEmpty())
        return;

    QFile f(fname);
    f.open(QFile::ReadOnly);
    QDataStream DS(&f);
    this->vector_block.clear();
    editor->load(DS);

    foreach(QGraphicsItem *item, editor->scene->items()){
        if (item->type() == Block::Type)
        {
        this->vector_block.push_back((Block*) item);
        }
    }

}

void EditorMainWindow::add_block_add()
{
    Block *b = new Block(0);

    scene->addItem(b);
    b->set_oper(1);
    b->add_port("ADD(+)", 0, Port::NamePort);
    b->add_port("In", 0, 0, 0);
    b->add_port("In", 0, 0, 0);
    b->add_port("Out", 1, 0, 0);
    b->add_port("", 1, Port::TypePort);
    b->setPos(view->sceneRect().center().toPoint());

    this->vector_block.push_back(b);
}

void EditorMainWindow::add_block_sub()
{
    Block *b = new Block(0);

    scene->addItem(b);
    b->set_oper(2);
    b->add_port("SUB(-)", 0, Port::NamePort);
    b->add_port("In", 0, 0, 0);
    b->add_port("In", 0, 0, 0);
    b->add_port("Out", 1, 0, 0);
    b->add_port("", 1, Port::TypePort);
    b->setPos(view->sceneRect().center().toPoint());

    this->vector_block.push_back(b);
}

void EditorMainWindow::add_block_mul()
{
    Block *b = new Block(0);

    scene->addItem(b);
    b->set_oper(3);
    b->add_port("MUL(*)", 0, Port::NamePort);
    b->add_port("In", 0, 0, 0);
    b->add_port("In", 0, 0, 0);
    b->add_port("Out", 1, 0, 0);
    b->add_port("", 1, Port::TypePort);
    b->setPos(view->sceneRect().center().toPoint());

    this->vector_block.push_back(b);
}

void EditorMainWindow::add_block_div()
{
    Block *b = new Block(0);

    scene->addItem(b);
    b->set_oper(4);
    b->add_port("DIV(/)", 0, Port::NamePort);
    b->add_port("In", 0, 0, 0);
    b->add_port("In", 0, 0, 0);
    b->add_port("Out", 1, 0, 0);
    b->add_port("", 1, Port::TypePort);
    b->setPos(view->sceneRect().center().toPoint());

    this->vector_block.push_back(b);
}

void EditorMainWindow::add_block_input()
{
    float input_val;
    input_val = QInputDialog::getDouble(0, "INPUT VALUE",
                "Please enter your value:", 0,-10000, 10000, 3);

    Block *b = new Block(0);
    scene->addItem(b);
    b->set_oper(5);
    b->add_port("INPUT", 0, Port::NamePort);
    b->add_port(QString::number(input_val,'f',3), 0, Port::NamePort);
    b->add_port("Out", 1, 0, 0);
    b->add_port("", 1, Port::TypePort);
    b->setPos(view->sceneRect().center().toPoint());
    b->set_input1(input_val);
    b->set_input1def(true);

    this->vector_block.push_back(b);
}

void EditorMainWindow::add_block_output()
{
    Block *b = new Block(0);

    scene->addItem(b);
    b->set_oper(6);
    b->add_port("OUTPUT", 0, Port::NamePort);
    b->add_port("In", 0, 0, 0);
    b->add_port("", 0, Port::TypePort);
    b->setPos(view->sceneRect().center().toPoint());

    this->vector_block.push_back(b);
}

void EditorMainWindow::add_block_pow()
{
    Block *b = new Block(0);

    scene->addItem(b);
    b->set_oper(7);
    b->add_port("POW(^)", 0, Port::NamePort);
    b->add_port("In", 0, 0, 0);
    b->add_port("In", 0, 0, 0);
    b->add_port("Out", 1, 0, 0);
    b->add_port("", 1, Port::TypePort);
    b->setPos(view->sceneRect().center().toPoint());

    this->vector_block.push_back(b);
}

void EditorMainWindow::debug_app(){
    // Znovu nacteni bloku na scene
    this->vector_block.clear();

    foreach (QGraphicsItem * current, editor->scene->items()) { // nastaveni vsech bloku na puvodni barvu
        if (current && current->type() == Block::Type)
        {
        Block* b = (Block*) current;
        this->vector_block.push_back(b);
        }
    }

    // Validace
    bool valid = this->validate_scheme();
    if(valid){

        foreach (Block * current, vector_block) { // nastaveni vsech bloku na puvodni barvu
            current->setSelected(false);
        }

        foreach (Block* current, vector_block) {

            if (!(current->get_def())){
            current->calculate();
            }

            if(current->get_def() == true && current->get_calculated() == true){
                QVector<Port*> arrayport = current->ports();

                current->setSelected(true); // zmena barvy prave pocitaneho bloku

                // zmena hodnoty calculated bloku
                if(current->get_oper() < 5)
                    arrayport[4]->set_name(QString::number(current->get_value(),'f',3));
                else if(current->get_oper() == 5)
                    arrayport[3]->set_name(QString::number(current->get_value(),'f',3));
                else if(current->get_oper() == 6)
                    arrayport[2]->set_name(QString::number(current->get_value(),'f',3));
                else if(current->get_oper() == 7)
                    arrayport[4]->set_name(QString::number(current->get_value(),'f',3));
                break;
            }

        }

        foreach (Block* current, vector_block) {
            current->set_calculated(false);
        }

    }
}

void EditorMainWindow::run_app(){
    // Znovu nacteni bloku na scene
    this->vector_block.clear();

    foreach (QGraphicsItem * current, editor->scene->items()) { // nastaveni vsech bloku na puvodni barvu
        if (current && current->type() == Block::Type)
        {
        Block* b = (Block*) current;
        this->vector_block.push_back(b);
        }
    }

    // Validace
    bool valid = this->validate_scheme();
    if(valid){

        reset_app();

        while(1){

            bool definition = false;

            foreach (Block* current, vector_block) {
                // Provede calculate nad blokama ktere nejsou nadefinovane
                if (!(current->get_def())){
                    current->calculate();
                    if(current->get_def()){
                        definition = true;
                    }
                }

                if(current->get_def() == true  && current->get_calculated() == true){

                    // Přidání výpisu hodnoty
                    QVector<Port*> arrayport = current->ports();

                    // Zmena label textu vysledku calculated bloku
                    if(current->get_def()){

                        foreach (Block * b, vector_block) { // nastaveni vsech bloku na puvodni barvu
                            b->setSelected(false);
                        }

                        current->setSelected(true); // nastaveni barvy pocitaneho bloku

                        // Zmena hodnoty calculated bloku
                        if(current->get_oper() < 5)
                            arrayport[4]->set_name(QString::number(current->get_value(),'f',3));
                        else if(current->get_oper() == 5)
                            arrayport[3]->set_name(QString::number(current->get_value(),'f',3));
                        else if(current->get_oper() == 6)
                            arrayport[2]->set_name(QString::number(current->get_value(),'f',3));
                        else if(current->get_oper() == 7)
                            arrayport[4]->set_name(QString::number(current->get_value(),'f',3));

                        this->delay(); // pozastaveni aplikace

                    }
                }
            }

            // Vymazani atributu calculated pro danou sekvenci -> 1 krok debugu
            foreach (Block* current, vector_block) {
                current->set_calculated(false);
            }

            // Pokud se nadefinuje ani jeden blok -> konec
            if(definition == false){
                break;
            }
        }
     }
}

void EditorMainWindow::reset_app(){
    // Znovu nacteni bloku na scene
    this->vector_block.clear();

    foreach (QGraphicsItem * current, editor->scene->items()) { // nastaveni vsech bloku na puvodni barvu
        if (current && current->type() == Block::Type)
        {
        Block* b = (Block*) current;
        this->vector_block.push_back(b);
        }
    }

    foreach (Block* current, vector_block) {
        // Hodnoty bloku se nastavi na default
        current->setSelected(false);

        // Input
        QVector<Port*> arrayport = current->ports();
        if(current->get_oper() == 5){
            arrayport[3]->set_name("");
            current->set_def(false);
            current->set_calculated(false);
            continue;
        }

        // Ostatni typy bloku
        if(current->get_def()){
            if(current->get_oper() < 5)
                arrayport[4]->set_name("");
            if(current->get_oper() == 6)
                arrayport[2]->set_name("");
            if(current->get_oper() == 7)
                arrayport[4]->set_name("");
        }

        current->set_value(0);

        current->set_input1(0);
        current->set_input2(0);

        current->set_input1def(false);
        current->set_input2def(false);

        current->set_calculated(false);
        current->set_def(false);

    }
}

void EditorMainWindow::delay(){
    QTime dieTime= QTime::currentTime().addSecs(2);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void EditorMainWindow::new_schema(){
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "NEW SCHEME", "Do you really want to create new scheme?\n"
                                                        "Current unsaved scheme will be deleted!!!",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          this->vector_block.clear();
          editor->clear();
      } else {

      }

}

bool EditorMainWindow::validate_scheme(){
    foreach(Block *current, vector_block){

        QVector<Port*> current_ports = current->ports();
        //kontrola pripojeni inputs
        if(current->get_oper() != 5){ // nejedna se o InputBlock
            foreach(Port *thisport, current_ports){
                if(!(thisport->is_output()) && !(thisport->get_typed()) && (thisport->my_connections.empty())){
                     QMessageBox::information(this, "WARNING: MISSING INPUT", "shceme contains unattached INPUT!!!\n"
                                                                              "Calculation stopped. Please modify your scheme.");
                     return false;
                }
            }
        }


        //kontrola pripojeni outputs
        if(current->get_oper() != 6){ // nejdna se o ConstBlock
            foreach(Port *thisport, current_ports){
                if((thisport->is_output()) && !(thisport->get_typed()) && (thisport->my_connections.empty())){
                     QMessageBox::information(this, "WARNING: MISSING OUTPUT", "Scheme contains unattached OUTPUT!!!\n"
                                                                               "Calculation stopped. Please modify your scheme.");
                     return false;
                }
            }
        }

        //kontrola cyklu
        if(current->get_oper() == 5){ // vychazime z Input Bloku
           std::vector<Block*> in_path; // nove pole jiz kontrolovanych bloku
           in_path.push_back(current);
           if(!(this->check_cycles(current, in_path))){ // pokud je nalezen cyklus
               QMessageBox::information(this, "WARNING: CYCLE DETECTED", "Scheme contains CYCLE!!!\n"
                                                                         "Calculation stopped. Please modify your scheme.");

               return false;
           }
        }

    }
    return true;
}

bool EditorMainWindow::check_cycles(Block* current, std::vector<Block*> in_path){
     QVector<Port*> current_ports = current->ports();
     foreach(Port *thisport, current_ports){ // pro kazdy port bloku
        if((thisport->is_output()) && !(thisport->get_typed()) && !(thisport->my_connections.empty())){ // pokud je vystupni a neni prazdny
            Block * next = thisport->my_connections[0]->port2()->block(); // ulozeni dalsiho bloku
            if(std::find(in_path.begin(), in_path.end(), next) != in_path.end()) { // pokud uz pole tento blok obsahuje, je to cyklus
                return false;
            } else { // pokud ne, rekurzivne spoustime nad dalsim blokem
                in_path.push_back(next);
                bool returned_recursion =  this->check_cycles(next ,in_path);
                return returned_recursion;
            }
        }
    }

    return true;
}


