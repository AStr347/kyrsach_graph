#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //создание и установка нашей сцены
    scene= new mescene(0,40,605,485,this);
    ui->graphicsView->setScene(scene);
    //связывание меню и их слотов
    Point=new QAction("Вершину", this);
    connect(Point, SIGNAL(triggered()), this, SLOT(ClickPoint()));

    Edge=new QAction("Ребро", this);
    connect(Edge, SIGNAL(triggered()), this, SLOT(ClickEdge()));

    DelP=new QAction("Вершину",this);
    connect(DelP,SIGNAL(triggered()),this,SLOT(DelPoint()));

    DelE=new QAction("Ребро",this);
    connect(DelE,SIGNAL(triggered()),this,SLOT(DelEdge()));

    Al=new QAction("расчет расстояния от одной до всех остальных",this);
    connect(Al,SIGNAL(triggered()),this,SLOT(D()));

    MOve=new QAction(tr("&Двигать Вершины"),this);
    connect(MOve,SIGNAL(triggered()),this,SLOT(Move()));

    Cle=new QAction(tr("&Очистить Граф"),this);
    connect(Cle,SIGNAL(triggered()),this,SLOT(Clear()));

    Way=new QAction("Найти путь между Вершинами",this);
    connect(Way,SIGNAL(triggered()),this,SLOT(WAy()));

    //создание меню
    //создания
    cre=ui->menuBar->addMenu(tr("&Создать"));
    cre->addAction(Point);
    cre->addAction(Edge);
    //удаления
    del=ui->menuBar->addMenu(tr("&Удалить"));
    del->addAction(DelP);
    del->addAction(DelE);
    //алгоритмы
    alg=ui->menuBar->addMenu(tr("&Алгоритмы"));
    alg->addAction(Al);
    alg->addAction(Way);
    //движение и очистку пришлось засунуть в oter
    ui->menuBar->addAction(MOve);
    ui->menuBar->addAction(Cle);
}

MainWindow::~MainWindow()
{
    mescene* s=reinterpret_cast<mescene*>(scene);
    s->DelL();
    s->Clear();
    delete scene;
    delete ui;
}

void MainWindow::ClickPoint(){//функция для выбора создания вершин
    mescene* s=reinterpret_cast<mescene*>(scene);
    s->CreatePoint();
}
void MainWindow::ClickEdge(){//функция для выбора создания ребер
    mescene* s=reinterpret_cast<mescene*>(scene);
    s->CreateEdge();
}
void MainWindow::DelPoint(){//функция для выбора удаления вершин
    mescene* s=reinterpret_cast<mescene*>(scene);
    s->DelPoint();
}
void MainWindow::DelEdge(){//функция для выбора удаления ребер
    mescene* s=reinterpret_cast<mescene*>(scene);
    s->DelEdge();
}
void MainWindow::D(){//функция для выбора вершины начала Деикстры
    mescene* s=reinterpret_cast<mescene*>(scene);
    s->D();
}
void MainWindow::Clear(){
    mescene* s=reinterpret_cast<mescene*>(scene);
    s->Clear();
}
void MainWindow::Move(){//функция для выбора перемещения вершин
    mescene* s=reinterpret_cast<mescene*>(scene);
    s->MoveP();
}

void MainWindow::WAy()
{
    mescene* s=reinterpret_cast<mescene*>(scene);
    s->PYT();
}
