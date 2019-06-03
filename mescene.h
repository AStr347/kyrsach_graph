#ifndef MESCENE_H
#define MESCENE_H
#include "graph.h"
#include <QGraphicsScene>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
class mescene: public QGraphicsScene
{
    Graph g;//наш граф
    int Beg;
    bool BegEdge=false,Change=false;//началии мы ребро?
    int action=none;//выбранное действие
    enum{createPoint,createEdge,Poisk,delPoint,delEdge,none,Move,PyT};//перечень действий
    QVector<QLabel*> LabelD;//вектор лэйблов для подписи растояний после Деикстры
    QSpinBox* v;//спинбоксы для выбора размеров точки и веса ребра
    QComboBox* algv;
    QLabel* podpis;

    void mouseMoveEvent (QGraphicsSceneMouseEvent *e);//переопределенная функция обработки движений мыши с зажатой ЛКМ
    void mousePressEvent (QGraphicsSceneMouseEvent *e);//переопределенная функция обработки кликов ЛКМ
public:
    mescene():QGraphicsScene(){
        v=new QSpinBox(reinterpret_cast<QWidget*>(this->parent()));
        algv=new QComboBox(reinterpret_cast<QWidget*>(this->parent()));
        podpis= new QLabel(reinterpret_cast<QWidget*>(this->parent()));
        v->setVisible(false);
        algv->setVisible(false);
        podpis->setVisible(false);
        algv->addItem("Ford_Bellman",QVariant(0));
        algv->addItem("Dijcstra",QVariant(1));
        algv->setItemData(0,algv->itemData(0));
    }//пустой конструктор
    mescene(qreal x,qreal y,qreal w,qreal h,QObject* p):QGraphicsScene(x,y,w,h,p){
        v=new QSpinBox(reinterpret_cast<QWidget*>(this->parent()));
        algv=new QComboBox(reinterpret_cast<QWidget*>(this->parent()));
        podpis= new QLabel(reinterpret_cast<QWidget*>(this->parent()));
        v->setVisible(false);
        algv->setVisible(false);
        podpis->setVisible(false);
        algv->addItem("Ford_Bellman",QVariant(0));
        algv->addItem("Dijcstra",QVariant(1));
        algv->setItemData(0,algv->itemData(0));
    }//полный конструктор

    void Draw();//метод отрисовки графа
    void Clear();//метод очищающий граф

    void CreatePoint();//метод перключает action и создает спинбокс для выбора размера вершин
    void CreateEdge();//метод перключает action и создает спинбокс для выбора веса ребра
    void DelPoint();//метод перключает action
    void DelEdge();//метод перключает action
    void D();//метод перключает action
    void MoveP();//метод перключает action
    void DelL();//метод удаляющий лишнее (спинбоксы и лэйблы)
    void PYT();
    ~mescene(){DelL(); delete v;delete algv;delete podpis;}
};

#endif // MESCENE_H
