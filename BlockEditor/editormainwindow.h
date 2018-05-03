#ifndef EDITORMAINWINDOW_H
#define EDITORMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <vector>

#include "block.h"


class Editor;

class EditorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorMainWindow(QWidget *parent = 0);
    ~EditorMainWindow();

private slots:
    void save_schema();
    void load_schema();
    void new_schema();

    void add_block_add();
    void add_block_sub();
    void add_block_div();
    void add_block_mul();
    void add_block_pow();
    void add_block_input();
    void add_block_output();

    void run_app();
    void reset_app();
    void debug_app();

    bool validate_scheme();
    bool check_cycles(Block* current, std::vector<Block*> in_path);
    void delay();

private:

    Editor *editor;
    QMenu *menu1;
    QMenu *menu2;
    QMenu *menu3;
    QGraphicsView *view;
    QGraphicsScene *scene;
    std::vector<Block*> vector_block;
};

#endif
