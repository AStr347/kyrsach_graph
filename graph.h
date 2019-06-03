#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include "point.h"
#include <QList>
class Graph
{
private:
    QList <Point> p;//список вершин (перешел на него из за того что вектор переодически сдвигает себя в памяти)
    QList <Edge> r;//вектор ребер
    int** matrix=nullptr;//матрица смежности
    int oldSize=-1;//запоминание старого размера что бы не вычищать лишне

    void DelMatrix();//метод вычищающий матрицу
    void zero();//метод заполняющий матрицу INT_MAX нужно для Деикстры
    double ygol_meg_3_Point (const Point& a, const Point& b, const Point& c);//расчитывает угол между 3 Point для RemoveEdge()
    void Dijcstra(const int& st,bool* visited,int* D,const int& Size,QVector <QVector <Edge>>& ot);//Сам Деикстра
    void Ford_Bellman(const int& st,int* D,const int& Size);
    void Way(int& s, int& f, int iskomaya,int *way,bool *include,const int& size,QVector<QVector<int>>& ways,int& v);

public:
            void AddPoint(Point _p){p.append(_p);}//метод добавляющий вершину
            void AddEdge(Edge _r){r.append(_r);}//метод добовляющий ребро
            void CreatMatrix();//метод создающий матрицу смежности

            int Size()const {return p.length();}//возвращает количество вершин
            int countR(){return r.length();}//возвращает количество ребер

            QVector<QString> Poisk(int st, int alg,int end=0);//оболочный метод

            int IndexOf(Point _p);//совой indexof тк листовый не видит перегрузку == для Point
            int IndexOf(Point* beg,Point* end);
            void UpDate();

            Point& operator [](const int& i){return p[i];}//перегрузка оператора [] возвращает [i] вершину
            Edge& LastEdge(){return r[r.length()-1];}//возвращает последнее ребро
            const Edge& retEdge(const int& i){return r[i];}//возвращает [i] ребро

            void RemovePoint(const int& i);//удаляет [i] вершину и все ребра связаные с этой вершиной
            void RemoveEdge(const Point& l);//удаляет ребро на котором лежит Point& l
            void RemoveEdge(const int& i){r.removeAt(i);}//удаляет [i] ребро
            bool DelCopy(Edge& _r);//метод удаляющий ребро если такое уже существует
            /*мой граф не ориентированный этот метод присекает ребра вида a->b b-> a*/

            void Clear();//очищение графа удаление всех ребер и вершин
            ~Graph(){Clear();delete this;}//деструктор
};
#endif // GRAPH_H
