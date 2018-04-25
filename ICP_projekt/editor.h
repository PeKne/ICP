#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QtWidgets>


class Editor;

class EditorMainWindow : public QMainWindow{
Q_OBJECT

public:
    explicit EditorMainWindow(QWidget *parent = 0);
    ~EditorMainWindow();

private slots:
    void save_file();
    void load_file();
    void add_block();

private:
    QMenu *fileMenu;
    QGraphicsView *view;
    Editor *nodes;
    QGraphicsScene *scene;
};

#endif // EDITOR_H
