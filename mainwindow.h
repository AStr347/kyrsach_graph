#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mescene.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
        void ClickPoint();//функция для выбора создания вершин
        void ClickEdge();//функция для выбора создания ребер
        void Clear();//функция очищения сцены
        void D();//функция для выбора вершины начала Деикстры
        void DelPoint();//функция для выбора удаления вершин
        void DelEdge();//функция для выбора удаления ребер
        void Move();//функция для выбора перемещения вершин

        void WAy();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QMenu *cre,*del,*alg,*other;
    QAction *Point,*Edge,*DelP,*DelE,*Al,*MOve,*Way,*Cle;
};

#endif // MAINWINDOW_H
