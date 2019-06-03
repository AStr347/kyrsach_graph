#include "mescene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "point.cpp"
void mescene::mouseMoveEvent (QGraphicsSceneMouseEvent *e){//переопределенная функция обработки движений мыши с зажатой ЛКМ
    QPointF p=e->scenePos();//координаты относительно левого верхнего угла сцены
    if(action!=Move)
        mousePressEvent(e);//если выбран не мув вызываем обработку обычных кликов
    else {
        int index=g.IndexOf(Point(p.x()-5,p.y()-5,""));//ищем вершину в графе над которой находится курсор
        if(index!=-1 && p.x()>0 && p.x()<600 && p.y()>20 && p.y()<420){
            g[index].SetPont(p.x()-5,p.y()-5);//если курсор в пределах сцены и захвачена точка меняем её координаты
        Draw();}
    }
}

void mescene::mousePressEvent (QGraphicsSceneMouseEvent *e){//переопределенная функция обработки кликов ЛКМ
    QPointF p=e->scenePos();
    int index=g.IndexOf(Point(p.x()-5,p.y()-5,""));//индекс точки в в графе если клик не на точку -1
        switch (action) {
                case createPoint://ветвь создания вершины
                    if(index==-1 || !(Point(g[index].X(),g[index].Y(),"",v->value()*2)==Point(p.x(),p.y(),"",v->value()))){//условие что бы точки не создавались друг на друге
                        g.AddPoint(Point(p.x()-v->value()/2,p.y()-v->value()/2,QString::number(g.Size()),v->value()));
                        this->addItem(g[g.Size()-1].GEI());
                        Change=true;
                    }
                    break;
                case createEdge:{
                        if(index!=-1){//ветвь создающая ребро и задающая её начало
                            if(!BegEdge){
                                g.AddEdge(Edge());
                                g.LastEdge().SetBegin(g[index]);
                                BegEdge=true;
                                Change=false;
                            }
                            else {//ветвь задающая конец ребра
                                if(&g.LastEdge().retBegin()!=&g[index]){//конец не равен начало то устанавливаем этот конец
                                    g.LastEdge().SetEnd(g[index]);
                                    g.LastEdge().SetVes(v->value());//устанавливаем вес
                                    if(!g.DelCopy(g.LastEdge()))//удаляем если подобное ребро уже есть
                                        this->addItem(g.LastEdge().GLI());
                                    BegEdge=false;
                                    Change=true;
                                }
                            }
                        }
                    break;
                }
                case Poisk:{
                    DelL();
                    if(index!=-1){
                        QVector<QString> text=g.Poisk(index,algv->currentIndex());//ветвь для исполнения Деикстры и подписи растояний до вершин
                        for(int i=0;i<g.Size();i++){//создание и отрисовка лэйблов
                            LabelD.append(new QLabel(text[i],(QWidget*)this->parent()));
                            LabelD[i]->move(g[i].X()+g[i].R()/2,g[i].Y()-g[i].R()/2-2);
                            LabelD[i]->show();
                        }
                    Change=false;
                    }
                    break;
                }
                case delPoint://удаление вершины из графа по индексу
                    if(index!=-1){
                        g.RemovePoint(index);
                        Change=true;
                    }
                    break;
                case delEdge:{//удаление ребра
                    int cx=p.x()-5;
                    int cy=p.y()-5;
                    g.RemoveEdge(Point(cx,cy,""));
                    Change=true;
                    }
                    break;
                case PyT:
                    for(int i=0;i<g.countR();i++)
                        g.retEdge(i).setColore();
                    if(index!=-1){
                        if(!BegEdge){
                            Beg=index;
                            BegEdge=!BegEdge;
                            g.UpDate();
                        }
                        else {
                            QVector<QString> text=g.Poisk(Beg,2,index);
                            for(int i=1;i<text.length();i++){
                                if(text[i-1]!="-1" && text[i]!="-1"){
                                    int j=g.IndexOf(&g[text[i-1].toInt()],&g[text[i].toInt()]);
                                    if(j!=-1)
                                        g.retEdge(j).setColore(Qt::green,3);
                            }
                        }
                        BegEdge=!BegEdge;
                        Beg=-1;
                        }
                    }
                    break;
            }
            if(Change)
                Draw();//вызов отрисовки графа
            Change=false;
    }

void mescene::CreatePoint(){//метод перключает action и создает спинбокс для выбора размера вершин
    action=createPoint;
    DelL();
    podpis->setVisible(true);
    podpis->setText("Выберете размер вершины");
    podpis->setGeometry(300,25,125,20);
    podpis->show();
    v->setVisible(true);
    v->setRange(10,50);
    v->setValue(10);
    v->setGeometry(500,25,42,22);
    v->show();
}
void mescene::CreateEdge(){//метод перключает action и создает спинбокс для выбора веса ребра
    action=createEdge;
    DelL();
    podpis->setVisible(true);
    podpis->setText("Выберете вес ребра");
    podpis->setGeometry(300,  25,125,20);
    podpis->show();
    v->setVisible(true);
    v->setRange(1,50);
    v->setValue(1);
    v->setGeometry(500,  25,42,22);
    v->show();
}
void mescene::DelPoint(){//метод перключает action
    action=delPoint;
    DelL();
}
void mescene::DelEdge(){//метод перключает action
    action=delEdge;
    DelL();
}
void mescene::D(){//метод перключает action
    action=Poisk;
    DelL();
    podpis->setVisible(true);
    podpis->setText("Выберете Алгоритм поиска растояний между вершинами");
    podpis->setGeometry(200, 25,295,20);
    podpis->show();
    algv->setVisible(true);
    algv->setGeometry(500, 25,100,  25);
    algv->show();
}

void mescene::MoveP(){//метод перключает action
    action=Move;
    DelL();
}

void mescene::Clear(){//метод очищающий граф
    action=none;
    g.Clear();
    Draw();
    DelL();
}

void mescene::PYT(){//метод перключает action
    action=PyT;
    DelL();
}

void mescene::Draw(){//метод отрисовки графа
    g.UpDate();
}

void mescene::DelL(){//метод удаляющий лишнее (спинбоксы и лэйблы)
    for(int i=0;i<g.countR();i++)
        g.retEdge(i).setColore(Qt::black,1);
    if(BegEdge && g.countR()!=0){
        g.RemoveEdge(g.countR()-1);
        BegEdge=false;
    }
    if(algv!=nullptr && action!=Poisk){
        algv->setVisible(false);
    }
    if(action!=createPoint && action!=createEdge){
        v->setVisible(false);
    }
    podpis->setVisible(false);
    for(auto& i:LabelD)
        delete i;
    LabelD.clear();
}
