#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //создание и установка нашей сцены
    scene= new mescene(0, 40, 605, 485, this);
    ui->graphicsView->setScene(scene);
    //связывание меню и их слотов
    A_Point = new QAction("Вершину", this);
    connect(A_Point, SIGNAL(triggered()), this, SLOT(ClickPoint()));

    A_Edge = new QAction("Ребро", this);
    connect(A_Edge, SIGNAL(triggered()), this, SLOT(ClickEdge()));

    A_DelP = new QAction("Вершину", this);
    connect(A_DelP, SIGNAL(triggered()), this, SLOT(DelPoint()));

    A_DelE = new QAction("Ребро", this);
    connect(A_DelE, SIGNAL(triggered()), this, SLOT(DelEdge()));

    A_Alg = new QAction("расчет расстояния от одной до всех остальных", this);
    connect(A_Alg, SIGNAL(triggered()), this, SLOT(AlgAction()));

    A_Move = new QAction(tr("&Двигать Вершины"), this);
    connect(A_Move, SIGNAL(triggered()), this, SLOT(MoveAction()));

    A_Cle = new QAction(tr("&Очистить Граф"), this);
    connect(A_Cle, SIGNAL(triggered()), this, SLOT(Clear()));

    A_Way = new QAction("Найти путь между Вершинами", this);
    connect(A_Way, SIGNAL(triggered()), this, SLOT(WayAction()));

    //создание меню
    //создания
    cre = ui->menuBar->addMenu(tr("&Создать"));
    cre->addAction(A_Point);
    cre->addAction(A_Edge);
    //удаления
    del = ui->menuBar->addMenu(tr("&Удалить"));
    del->addAction(A_DelP);
    del->addAction(A_DelE);
    //алгоритмы
    alg = ui->menuBar->addMenu(tr("&Алгоритмы"));
    alg->addAction(A_Alg);
    alg->addAction(A_Way);
    //движение и очистку пришлось засунуть в oter
    ui->menuBar->addAction(A_Move);
    ui->menuBar->addAction(A_Cle);
}

MainWindow::~MainWindow()
{
    mescene* s = reinterpret_cast<mescene*>(scene);
    s->DelL();
    s->Clear();
    delete A_Point; delete A_Edge; delete A_DelP; delete A_DelE; delete A_Alg; delete A_Move; delete A_Way; delete A_Cle;
    delete cre; delete del; delete alg;
    delete scene;
    delete ui;
}

void MainWindow::ClickPoint(){//функция для выбора создания вершин
    mescene* s = reinterpret_cast<mescene*>(scene);
    s->CreatePoint();
}
void MainWindow::ClickEdge(){//функция для выбора создания ребер
    mescene* s = reinterpret_cast<mescene*>(scene);
    s->CreateEdge();
}
void MainWindow::DelPoint(){//функция для выбора удаления вершин
    mescene* s = reinterpret_cast<mescene*>(scene);
    s->DelPoint();
}
void MainWindow::DelEdge(){//функция для выбора удаления ребер
    mescene* s = reinterpret_cast<mescene*>(scene);
    s->DelEdge();
}
void MainWindow::AlgAction(){//функция для выбора вершины начала Деикстры
    mescene* s = reinterpret_cast<mescene*>(scene);
    s->Find();
}
void MainWindow::Clear(){
    mescene* s = reinterpret_cast<mescene*>(scene);
    s->Clear();
}
void MainWindow::MoveAction(){//функция для выбора перемещения вершин
    mescene* s = reinterpret_cast<mescene*>(scene);
    s->MoveP();
}

void MainWindow::WayAction()
{
    mescene* s = reinterpret_cast<mescene*>(scene);
    s->Way();
}
