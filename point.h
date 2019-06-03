#ifndef POINT_H
#define POINT_H
#include <QString>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
class Point
{
    int x,y,rad;//координаты и радиус
    QString name;//имя вершины пока не используется
    QGraphicsEllipseItem* QGEI;
    public:
            Point() : x(0), y(0), name(""), QGEI(nullptr) {}//пустой конструктор
            Point(const int& _x, const int& _y, const QString& _name, int _rad=10) : x(_x), y(_y), rad(_rad), name(_name), QGEI(nullptr){}//полный конструктор
            const int& X() const {return x;}//возвращает ссылку на x
            const int& Y() const {return y;}//возвращает ссылку на y
            const int& R() const {return rad;}//возвращает ссылку на радиус
            const QString& Name() const {return name;}//возвращает ссылку на имя
            void SetPont(int _x, int _y) {x = _x; y = _y;}//позволяет поменять координаты
            void SetName(QString& _name) {name = _name;}//позволяет поменять имя
            void SetR(int _r) {rad = _r;}//позволяет поменять радиус
            QGraphicsItem* GEI();
            void UpDate();
            void Del(){
                delete QGEI;
            }
};
bool operator ==(const Point p1, const Point p2);
#endif // POINT_H
