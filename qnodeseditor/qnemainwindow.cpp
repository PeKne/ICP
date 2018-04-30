/* Copyright (c) 2012, STANISLAW ADASZEWSKI
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of STANISLAW ADASZEWSKI nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "qnemainwindow.h"
#include "ui_qnemainwindow.h"

#include "qnodeseditor.h"

#include <QGraphicsScene>
#include <QFileDialog>
#include <QInputDialog>
#include <QThread>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "qneport.h"
#include <iostream>
#include <unistd.h>

using namespace std;


QNEMainWindow::QNEMainWindow(QWidget *parent) :
    QMainWindow(parent)
{


    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,800);

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
    connect(QA_load, SIGNAL(triggered()), this, SLOT(loadFile()));

    QAction *QA_save = new QAction(tr("&Save"), this);
    QA_save->setShortcuts(QKeySequence::Save);
    QA_save->setStatusTip(tr("Save file"));
    connect(QA_save, SIGNAL(triggered()), this, SLOT(saveFile()));

    QAction *QA_quit = new QAction(tr("&Quit"), this);
    QA_quit->setShortcuts(QKeySequence::Quit);
    QA_quit->setStatusTip(tr("Quit the app"));
    connect(QA_quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Nastaveni menu
    menu1 = menuBar()->addMenu(tr("&Schema"));
    menu2 = menuBar()->addMenu(tr("&Block"));
    menu3 = menuBar()->addMenu(tr("&Action"));



    menu1->addAction(QA_save);
    menu1->addAction(QA_load);
    menu1->addSeparator();
    menu1->addAction(QA_quit);

    menu2->addAction(QA_add);
    menu2->addAction(QA_sub);
    menu2->addAction(QA_div);
    menu2->addAction(QA_mul);
    menu2->addAction(QA_input);
    menu2->addAction(QA_output);

    menu3->addAction(QA_debug);
    menu3->addAction(QA_run);
    menu3->addAction(QA_reset);
/*
    float input_val;
    input_val = QInputDialog::getDouble(0, "INPUT VALUE",
                "Please enter your value:", 0);
*/



    setWindowTitle(tr("Schema editor v1"));

    QDockWidget *dock = new QDockWidget(tr("New Schema"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    view = new QGraphicsView(dock);
    view->setScene(scene);

    view->setRenderHint(QPainter::Antialiasing, true);

    dock->setWidget(view);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    nodesEditor = new QNodesEditor(this);
    nodesEditor->install(scene);

}

QNEMainWindow::~QNEMainWindow()
{

}

void QNEMainWindow::saveFile()
{
	QString fname = QFileDialog::getSaveFileName();
	if (fname.isEmpty())
		return;

	QFile f(fname);
	f.open(QFile::WriteOnly);
	QDataStream ds(&f);
	nodesEditor->save(ds);
}

void QNEMainWindow::loadFile()
{
	QString fname = QFileDialog::getOpenFileName();
	if (fname.isEmpty())
		return;

	QFile f(fname);
	f.open(QFile::ReadOnly);
	QDataStream ds(&f);
	nodesEditor->load(ds);

}
void QNEMainWindow::add_block_add()
{
    QNEBlock *b = new QNEBlock(0);

    scene->addItem(b);
    b->oper = 1;
    b->addPort("ADD(+)", 0, QNEPort::NamePort);
    b->addPort("In", 0, 0, 0);
    b->addPort("In", 0, 0, 0);
    b->addPort("Out", 1, 0, 0);
    b->addPort("", 1, QNEPort::TypePort);
    b->setPos(view->sceneRect().center().toPoint());
    this->vector_bloku.push_back(b);
}
void QNEMainWindow::add_block_sub()
{
    QNEBlock *b = new QNEBlock(0);

    scene->addItem(b);
    b->oper = 2;
    b->addPort("SUB(-)", 0, QNEPort::NamePort);
    b->addPort("In", 0, 0, 0);
    b->addPort("In", 0, 0, 0);
    b->addPort("Out", 1, 0, 0);
    b->addPort("", 1, QNEPort::TypePort);
    b->setPos(view->sceneRect().center().toPoint());
    this->vector_bloku.push_back(b);
}

void QNEMainWindow::add_block_mul()
{
    QNEBlock *b = new QNEBlock(0);

    scene->addItem(b);
    b->oper = 3;
    b->addPort("MUL(*)", 0, QNEPort::NamePort);
    b->addPort("In", 0, 0, 0);
    b->addPort("In", 0, 0, 0);
    b->addPort("Out", 1, 0, 0);
    b->addPort("", 1, QNEPort::TypePort);
    b->setPos(view->sceneRect().center().toPoint());
    this->vector_bloku.push_back(b);
}

void QNEMainWindow::add_block_div()
{
    QNEBlock *b = new QNEBlock(0);

    scene->addItem(b);
    b->oper = 4;
    b->addPort("DIV(/)", 0, QNEPort::NamePort);
    b->addPort("In", 0, 0, 0);
    b->addPort("In", 0, 0, 0);
    b->addPort("Out", 1, 0, 0);
    b->addPort("", 1, QNEPort::TypePort);
    b->setPos(view->sceneRect().center().toPoint());
    this->vector_bloku.push_back(b);
}
void QNEMainWindow::add_block_input()
{
    float input_val;
    input_val = QInputDialog::getDouble(0, "INPUT VALUE",
                "Please enter your value:", 0,-10000, 10000, 3);

    QNEBlock *b = new QNEBlock(0);
    scene->addItem(b);
    b->oper = 5;
    b->addPort("INPUT", 0, QNEPort::NamePort);
    b->addPort(QString::number(input_val,'f',3), 0, QNEPort::NamePort);
    b->addPort("Out", 1, 0, 0);
    b->addPort("", 1, QNEPort::TypePort);
    b->setPos(view->sceneRect().center().toPoint());
    b->input1 = input_val;
    b->input1def = true;
    this->vector_bloku.push_back(b);
}
void QNEMainWindow::add_block_output()
{
    QNEBlock *b = new QNEBlock(0);

    scene->addItem(b);
    b->oper = 6;
    b->addPort("OUTPUT", 0, QNEPort::NamePort);
    b->addPort("In", 0, 0, 0);
    b->addPort("", 0, QNEPort::TypePort);
    b->setPos(view->sceneRect().center().toPoint());
    this->vector_bloku.push_back(b);
}

void QNEMainWindow::debug_app(){

    foreach (QNEBlock * current, vector_bloku) { // nastaveni vsech bloku na puvodni barvu
        current->setSelected(false);
    }



        foreach (QNEBlock* current, vector_bloku) {


            if (!(current->def)){
                current->calculate();
            }

            if(current->def == true  && current->calculated == true){
                QVector<QNEPort*> arrayport = current->ports();


                current->setSelected(true); // zmena barvy prave pocitaneho bloku

                if(current->oper < 5)
                    arrayport[4]->setName(QString::number(current->value,'f',3));
                else if(current->oper == 5)
                    arrayport[3]->setName(QString::number(current->value,'f',3));
                else if(current->oper == 6)
                    arrayport[2]->setName(QString::number(current->value,'f',3));
            }

        }

        foreach (QNEBlock* current, vector_bloku) {
            current->calculated = false;
        }
}
void QNEMainWindow::run_app(){
    while(1){

        bool definition = false;

        foreach (QNEBlock* current, vector_bloku) {
            // Provede calculate nad blokama ktere nejsou nadefinovane
            if (!(current->def)){
                current->calculate();
                if(current->def){
                    definition = true;
                }
            }

            if(current->def == true  && current->calculated == true){

                // Přidání výpisu hodnoty
                QVector<QNEPort*> arrayport = current->ports();

                // Zmena label textu vysledku calculated bloku
                if(current->def){

                    foreach (QNEBlock * b, vector_bloku) { // nastaveni vsech bloku na puvodni barvu
                        b->setSelected(false);
                    }

                    current->setSelected(true); // nastaveni barvy pocitaneho bloku


                    if(current->oper < 5)
                        arrayport[4]->setName(QString::number(current->value,'f',3));
                    else if(current->oper == 5)
                        arrayport[3]->setName(QString::number(current->value,'f',3));
                    else if(current->oper == 6)
                        arrayport[2]->setName(QString::number(current->value,'f',3));

                    this->delay(); // pozastaveni aplikace

                }
            }
        }

        // Vymazani atributu calculated pro danou sekvenci -> 1 krok debugu
        foreach (QNEBlock* current, vector_bloku) {
            current->calculated = false;
        }

        // Pokud se nadefinuje ani jeden blok -> konec
        if(definition == false){
            break;
        }
    }
}
void QNEMainWindow::reset_app(){
    foreach (QNEBlock* current, vector_bloku) {
        // Input / Output

        current->setSelected(false);

        QVector<QNEPort*> arrayport = current->ports();
        if(current->oper == 5){
             arrayport[3]->setName("");
            current->def = false;
            continue;
        }


        if(current->def){
            if(current->oper < 5)
                arrayport[4]->setName("");
            if(current->oper == 6)
                arrayport[2]->setName("");
        }

        current->value = 0;

        current->input1 = 0;
        current->input2 = 0;

        current->input1def = false;
        current->input2def = false;

        current->calculated = false;
        current->def = false;

    }
}

void QNEMainWindow::delay(){
    QTime dieTime= QTime::currentTime().addSecs(2);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
