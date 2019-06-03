#include "edge.h"
/**
    при необходимости создает графический объект ребра
    @return         - указатель на графический объект
*/
QGraphicsItem* Edge::GLI(){
    if(QGLI==nullptr){
        double SB=Begin->R()/2;
        double SE=End->R()/2;
        QGLI=new QGraphicsLineItem(Begin->X()+SB,Begin->Y()+SB,End->X()+SE,End->Y()+SE);
        QGLI->setAcceptHoverEvents(true);
    }
    return QGLI;
}

/**
    обновляет данные графического объекта
*/
void Edge::UpDate(){
    if(QGLI!=nullptr && Norm()){
        double SB=Begin->R()/2;
        double SE=End->R()/2;
        QGLI->setLine(Begin->X()+SB,Begin->Y()+SB,End->X()+SE,End->Y()+SE);
    }
}

/**
    меняет цвет и ширину графического объекта
    @param c        - [in] будущий цвет объекта
    @param w        - [in] будущая ширина объекта
*/
void Edge::setColore(QColor c,int w) const{
    if(QGLI!=nullptr && Norm()){
        QPen pen;
        pen.setColor(c);
        pen.setWidth(w);
        QGLI->setPen(pen);
    }
}
