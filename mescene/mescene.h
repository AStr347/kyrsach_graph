#ifndef MESCENE_H
#define MESCENE_H

#include <QGraphicsScene>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include "graph/graph.h"

class mescene: public QGraphicsScene
{
    Graph g;//наш граф
    int Beg;//запоминает индекс вершины начала пути
    bool BegEdge = false;
    bool Change = false;//началии мы ребро? и были ли изменения
    int action = NONE;//выбранное действие
    enum {CRE_POINT,CRE_EDGE,FIND,DEL_POINT,DEL_EDGE,NONE,MOVE,WAY};//перечень действий
    QVector <QLabel*> LabelD;//вектор лэйблов для подписи растояний после Деикстры
    QSpinBox *v;//спинбокс для выбора размеров точки и веса ребра
    QComboBox *algv;//комбобокс для выюора алгоритма
    QLabel *podpis;
    QLabel *name;//лэйблы для информации и подписи имен вершин и веса ребер
    QLineEdit *text;//лайнэдит для выбора имени вершины

    void mouseMoveEvent (QGraphicsSceneMouseEvent *e);//переопределенная функция обработки движений мыши с зажатой ЛКМ и Hover событий

    void mousePressEvent (QGraphicsSceneMouseEvent *e);//переопределенная функция обработки кликов ЛКМ

public:
    mescene();//пустой конструктор
    mescene(qreal x, qreal y, qreal w, qreal h, QObject* p);//полный конструктор

    void Draw();//метод отрисовки графа
    void Clear();//метод очищающий граф

    //методы переключающие action
    void DelPoint();
    void DelEdge();
    void MoveP();
    void Way();
    void CreatePoint();//создает спинбокс для выбора размера вершин и лайнэдит для выбора имен
    void CreateEdge();//создает спинбокс для выбора веса ребра
    void Find();//создает комбобокс для выбора алгоритма

    void DelL();//метод удаляющий лишнее (спинбоксы и лэйблы)
    ~mescene(){DelL(); delete v; delete algv; delete podpis; delete name; delete text;}
};




















/*todo: mmmmmmmmmmmmmmmmmmmmmmmmmm*/
#endif // MESCENE_H
