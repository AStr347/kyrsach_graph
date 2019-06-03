#ifndef EDGE_H
#define EDGE_H
#include"point.h"
#include <QGraphicsLineItem>
#include <QPen>
class Edge
{
    Point *Begin,*End;//указатели на начальную и конечную вершину
    int ves;//вес ребра
    QGraphicsLineItem* QGLI=nullptr;
    public:
            const Point& retBegin() const {return *Begin;}//возвращает ссылку на начальную вершину
            const Point& retEnd() const {return *End;}//возвращает ссылку на конечную вершину
            const int& retVes() const {return ves;}//возвращает ссылку на вес ребра
            Edge(Point& _Begin,Point& _End,const int& _ves=1):Begin(&_Begin),End(&_End),ves(_ves){}//полный конструктор
            Edge():Begin(nullptr),End(nullptr),ves(1){}//пустой конструктор
            void SetBegin(Point& p){Begin=&p;}//позволяет поменять начальную вершину
            void SetEnd(Point& p){End=&p;}//позволяет поменять коненую вершину
            void SetVes(const int& v){ves=v;}//позволяет поменять вес ребра
            bool Norm()const{return Begin!=nullptr && End!=nullptr ? true : false;}//true если имеется и начало и конец
            void Null(){Begin=nullptr;End=nullptr;delete QGLI;}//обнуляет указатели
            QGraphicsItem* GLI(){
                double SB=Begin->R()/2;
                double SE=End->R()/2;
                QGLI=new QGraphicsLineItem(Begin->X()+SB,Begin->Y()+SB,End->X()+SE,End->Y()+SE);
                return QGLI;
            }
            void UpDate(){
                if(QGLI!=nullptr && Norm()){
                    double SB=Begin->R()/2;
                    double SE=End->R()/2;
                    QGLI->setLine(Begin->X()+SB,Begin->Y()+SB,End->X()+SE,End->Y()+SE);
                }
            }
            void setColore(QColor c=Qt::black,int w=1)const{
                if(QGLI!=nullptr && Norm()){
                    QPen pen;
                    pen.setColor(c);
                    pen.setWidth(w);
                    QGLI->setPen(pen);
                }
            }
            /*перед удалением вершины удаляется и ребра связаные с этой вершиной без этого
              происходили проблемы с отрисовкой*/
            ~Edge(){Null();}
};

#endif // EDGE_H
