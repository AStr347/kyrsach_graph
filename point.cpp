#include "point.h"

bool operator ==(const Point p1,const Point p2){//перегрузка операции == для Point
    int r = p1.X()+p1.R();//тк используется для анализа попадания клика область чуть-чуть увеличена
    int r2 = p2.X()+p2.R();
    int b = p1.Y()+p1.R();
    int b2 = p2.Y()+p2.R();
    return !(r <= p2.X() || p1.X() > r2 || b <= p2.Y() || p1.Y() > b2);
}

/**
    при необходимости создает графический объект ребра
    @return         - указатель на графический объект
*/
QGraphicsItem* Point::GEI(){
    if(QGEI == nullptr){
        QGEI = new QGraphicsEllipseItem(x, y, rad, rad);
        QGEI->setAcceptHoverEvents(true);
    }
    return QGEI;
}

void Point::UpDate(){
    if(QGEI!=nullptr)
        QGEI->setRect(x, y, rad, rad);
}
