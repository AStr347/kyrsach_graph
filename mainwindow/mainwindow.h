#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mescene/mescene.h"
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
        void AlgAction();//функция для выбора вершины начала Деикстры
        void DelPoint();//функция для выбора удаления вершин
        void DelEdge();//функция для выбора удаления ребер
        void MoveAction();//функция для выбора перемещения вершин
        void WayAction();//функция для выбора построения пути

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;//наша сцена для отображения и взаимодействий с графом
    QMenu *cre,*del,*alg;//выпадающие меню
    QAction *A_Point,*A_Edge,*A_DelP,*A_DelE,*A_Alg,*A_Move,*A_Way,*A_Cle;//элементы меню
};

#endif // MAINWINDOW_H
