#include "mescene.h"
#include <QGraphicsSceneMouseEvent>
#include "point.cpp"
mescene::mescene() : QGraphicsScene(){
    v = new QSpinBox(reinterpret_cast<QWidget*>(this->parent()));
    algv = new QComboBox(reinterpret_cast<QWidget*>(this->parent()));
    podpis = new QLabel(reinterpret_cast<QWidget*>(this->parent()));
    name = new QLabel(reinterpret_cast<QWidget*>(this->parent()));
    text = new QLineEdit(reinterpret_cast<QWidget*>(this->parent()));
    v->setVisible(false);
    algv->setVisible(false);
    podpis->setVisible(false);
    name->setVisible(false);
    text->setVisible(false);
    algv->addItem("Ford_Bellman", QVariant(0));
    algv->addItem("Dijcstra", QVariant(1));
    algv->setItemData(0, algv->itemData(0));
}

mescene::mescene(qreal x,qreal y,qreal w,qreal h,QObject* p) : QGraphicsScene(x,y,w,h,p){
    v = new QSpinBox(reinterpret_cast<QWidget*>(this->parent()));
    algv = new QComboBox(reinterpret_cast<QWidget*>(this->parent()));
    podpis = new QLabel(reinterpret_cast<QWidget*>(this->parent()));
    name = new QLabel(reinterpret_cast<QWidget*>(this->parent()));
    text = new QLineEdit(reinterpret_cast<QWidget*>(this->parent()));
    v->setVisible(false);
    algv->setVisible(false);
    podpis->setVisible(false);
    name->setVisible(false);
    text->setVisible(false);
    algv->addItem("Ford_Bellman", QVariant(0));
    algv->addItem("Dijcstra", QVariant(1));
    algv->setItemData(0, algv->itemData(0));
}

void mescene::mouseMoveEvent (QGraphicsSceneMouseEvent *e){//переопределенная функция обработки движений мыши с зажатой ЛКМ
    name->setVisible(false);
    QPointF p = e->scenePos();//координаты относительно левого верхнего угла сцены
    int index = g.IndexOf(Point(p.x()-5, p.y()-5,""));//ищем вершину в графе над которой находится курсор
    if(e->buttons() == Qt::LeftButton){
        if(action != MOVE)
            mousePressEvent(e);//если выбран не мув вызываем обработку обычных кликов
        else {
            if(index != -1 && p.x() > 0 && p.x() < this->width() && p.y() > 40 && p.y() < this->height()+40){
                g[index].SetPont(p.x()-5, p.y()-5);//если курсор в пределах сцены и захвачена точка меняем её координаты
                Draw();
            }
        }
    }
    else
            if(index != -1){
                name->setText(g[index].Name());
                name->setGeometry(p.x()-20, p.y()-20, 40, 20);
                name->setVisible(true);}
            else {
                index=g.IndexOf(p.x()-5, p.y()-5);
                if(index!=-1 && true == g.retEdge(index).Norm()){
                    name->setText(QString :: number(g.retEdge(index).retVes()));
                    name->setGeometry(p.x()-20, p.y()-20, 40, 20);
                    name->setVisible(true);
                }
            }
}

void mescene::mousePressEvent (QGraphicsSceneMouseEvent *e){//переопределенная функция обработки кликов ЛКМ
    QPointF p = e->scenePos();
    int index = g.IndexOf(Point(p.x()-5, p.y()-5, ""));//индекс точки в в графе если клик не на точку -1
    switch (action){
        case CRE_POINT://ветвь создания вершины
            if(index == -1 || !(Point(g[index].X(), g[index].Y(),"",v->value()*2) == Point(p.x(), p.y(), "", v->value()))){//условие что бы точки не создавались друг на друге
                g.AddPoint(Point(p.x()-v->value()/2, p.y()-v->value()/2, text->text(), v->value()));
                this->addItem(g[g.Size()-1].GEI());
                Change = true;
                text->setText(QString :: number(g.Size()));
            }
            break;
        case CRE_EDGE:{
            if(index != -1){//ветвь создающая ребро и задающая её начало
                if(false == BegEdge){
                    g.AddEdge(Edge());
                    g.LastEdge().SetBegin(g[index]);
                    BegEdge = true;
                }
                else {//ветвь задающая конец ребра
                    if(&g.LastEdge().retBegin() != &g[index]){//конец не равен начало то устанавливаем этот конец
                        g.LastEdge().SetEnd(g[index]);
                        g.LastEdge().SetVes(v->value());//устанавливаем вес
                        if(false == g.DelCopy(g.LastEdge()))//удаляем если подобное ребро уже есть
                            this->addItem(g.LastEdge().GLI());
                        BegEdge = false;
                        Change = true;
                    }
                }
            }
            break;
        }
        case FIND:{
            DelL();
            if(index != -1){
                QVector <QString> text = g.Poisk(index, algv->currentIndex());//ветвь для исполнения Деикстры и подписи растояний до вершин
                for(int i = 0; i < g.Size(); i++){//создание и отрисовка лэйблов
                    LabelD.append(new QLabel(text[i], (QWidget*)this->parent()));
                    LabelD[i]->move(g[i].X()+g[i].R()/2, g[i].Y()-g[i].R()/2-2);
                    LabelD[i]->show();
                }
            }
            break;
        }
        case DEL_POINT://удаление вершины из графа по индексу
            if(index != -1){
                g.RemovePoint(index);
                Change=true;
            }
            break;
        case DEL_EDGE:{//удаление ребра
            g.RemoveEdge(Point(p.x()-5, p.y()-5,""));
            Change = true;
            break;
        }
        case WAY:
            for(int i = 0; i < g.countR(); i++)
                g.retEdge(i).setColore();
            if(index != -1){
                if(false == BegEdge){
                    Beg = index;
                    BegEdge = !BegEdge;
                    g.UpDate();
                }
                else {
                    QVector <QString> text = g.Poisk(Beg, 2, index);
                    for(int i = 1; i < text.length(); i++){
                        if(text[i-1] != "-1" && text[i] != "-1"){
                            int j = g.IndexOf(&g[text[i-1].toInt()], &g[text[i].toInt()]);
                            if(j != -1)
                                g.retEdge(j).setColore(Qt :: green, 3);
                        }
                    }
                BegEdge = !BegEdge;
                Beg = -1;
                }
            }
            break;
    }
    if(Change)
        Draw();//вызов отрисовки графа
    Change = false;
}

void mescene::CreatePoint(){//метод перключает action и создает спинбокс для выбора размера вершин
    action = CRE_POINT;
    DelL();
    podpis->setVisible(true);
    podpis->setText("Выберете имя и размер вершины");
    podpis->setGeometry(100, 30, 300, 20);
    podpis->show();
    v->setVisible(true);
    v->setRange(10, 50);
    v->setValue(10);
    v->setGeometry(500, 30, 42, 22);
    v->show();
    text->setVisible(true);
    text->setGeometry(400, 30, 50, 22);
    text->setText(QString :: number(g.Size()));
}
void mescene::CreateEdge(){//метод перключает action и создает спинбокс для выбора веса ребра
    action = CRE_EDGE;
    DelL();
    podpis->setVisible(true);
    podpis->setText("Выберете вес ребра");
    podpis->setGeometry(100, 30, 300, 20);
    podpis->show();
    v->setVisible(true);
    v->setRange(1, 50);
    v->setValue(1);
    v->setGeometry(400, 30, 50, 22);
    v->show();
}
void mescene::DelPoint(){//метод перключает action
    action = DEL_POINT;
    DelL();
}
void mescene::DelEdge(){//метод перключает action
    action = DEL_EDGE;
    DelL();
}
void mescene::Find(){//метод перключает action
    action = FIND;
    DelL();
    podpis->setVisible(true);
    podpis->setText("Выберете Алгоритм поиска растояний между вершинами");
    podpis->setGeometry(100, 25, 300, 20);
    podpis->show();
    algv->setVisible(true);
    algv->setGeometry(500, 25, 100,  25);
    algv->show();
}

void mescene::MoveP(){//метод перключает action
    action = MOVE;
    DelL();
}

void mescene::Clear(){//метод очищающий граф
    action = NONE;
    g.Clear();
    Draw();
    DelL();
}

void mescene::Way(){//метод перключает action
    action = WAY;
    DelL();
    podpis->setText("При работе с особо большими и сложными графами поиск может занять много времени\n или привести к RuntimeError");
    podpis->setGeometry(100, 20, 600, 50);
    podpis->setVisible(true);
}

void mescene::Draw(){//метод отрисовки графа
    g.UpDate();
}

void mescene::DelL(){//метод удаляющий лишнее (спинбоксы и лэйблы)
    for(int i = 0; i < g.countR(); i++)
        g.retEdge(i).setColore(Qt::black, 1);
    if(BegEdge && g.countR() != 0){
        g.RemoveEdge(g.countR()-1);
        BegEdge = false;
    }
    if(action != FIND)
        algv->setVisible(false);

    if(action != CRE_POINT && action != CRE_EDGE)
        v->setVisible(false);

    if(action != CRE_POINT)
        text->setVisible(false);

    podpis->setVisible(false);

    for(auto& i:LabelD)
        delete i;
    LabelD.clear();
}
