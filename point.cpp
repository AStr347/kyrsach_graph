#include "point.h"

bool operator ==(const Point p1,const Point p2){//перегрузка операции == для Point
    int r=p1.X()+p1.R();//тк используется для анализа попадания клика область чуть чуть увеличена
    int r2=p2.X()+p2.R();
    int b=p1.Y()+p1.R();
    int b2=p2.Y()+p2.R();
    return !(r <= p2.X() || p1.X() > r2 || b <= p2.Y() || p1.Y() > b2);
}
