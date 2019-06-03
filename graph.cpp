#include "graph.h"
#include <QDebug>
void Graph::DelMatrix(){//метод вычищающий матрицу
    oldSize=oldSize==-1?p.length():oldSize;
    if (matrix!=nullptr){//удаляем старую матрицу если она существовала
        for(int i=0;i<oldSize;i++)
            delete[] matrix[i];
        delete[] matrix;
    }
    matrix=nullptr;
}

void Graph::zero(){//метод заполняющий матрицу INT_MAX нужно для Деикстры
    for(int i=0;i<p.length();i++)
        for(int j=0;j<p.length();j++)
            matrix[i][j]=2000000;
}

double Graph::ygol_meg_3_Point (const Point& a, const Point& b, const Point& c){//расчитывает угол между 3 Point для RemoveEdge()
   double x1 = a.X() - b.X(), x2 = c.X() - b.X();
   double y1 = a.Y() - b.Y(), y2 = c.Y() - b.Y();
   double d1 = sqrt (x1 * x1 + y1 * y1);
   double d2 = sqrt (x2 * x2 + y2 * y2);
   return acos ((x1 * x2 + y1 * y2) / (d1 * d2));
}

void Graph::Dijcstra(const int& st,bool* visited,int* D,const int& Size,QVector <QVector <Edge>>& ot){//сам Деикстра
    D[st]=0;//расстояние до начальной вершины всегда 0
    int index=0,u=0;
    for (int i=0;i<Size;i++){//идем по всем вершинам
        QVector <Edge> pyt;
        int min=2000000;//изначально минимальный путь равен мак возможному
        for (int j=0;j<Size;j++){//идем по строке связей i-ой вершины
            if (!visited[j] && D[j]<min){//если вершина не посещена и расстояние до неё меньше min
                min=D[j];//присваиваем min это расстояние
                index=j;
            }
        }
        u=index;
        visited[u]=true;//помечаем вершину как посещенная
        for(int j=0;j<Size;j++)//проходим по массиву расстояний
        {
            if (!visited[j] && matrix[u][j]!=2000000 && D[u]!=2000000 && (D[u]+matrix[u][j]<D[j])){
                D[j]=D[u]+matrix[u][j];
                pyt.append(Edge(p[u],p[j]));
            }//если вершина не посещена И у неё есть связь с u-ой И растояние до u-ой не является макс возможным И растояние до u-ой сложенное c растоянием между u-ой и j-ой меньше растояния до j-ой
        }    //присваиваем растоянию до j-ой сумму растояния до u-ой и растояние между u-ой и j-ой
    ot.append(pyt);
    }
}

void Graph::Ford_Bellman(const int &st, int *D, const int &Size){
    D[st] = 0;
    for (int i=0;i<Size;i++)
        for (int j=0;j<r.length();j++){
            int first=r[j].retBegin().Name().toInt(),second=r[j].retEnd().Name().toInt(),ves=r[j].retVes();
            if (D[second] > D[first] + ves)
                D[second] = D[first] + ves;
            if (D[first] > D[second] + ves)
                D[first] = D[second] + ves;
            }
}

void Graph::CreatMatrix(){//метод создающий матрицу смежности
    DelMatrix();
    matrix=new int*[p.length()];//создаем новую матрицу
    for(int i=0;i<p.length();i++)
        matrix[i]=new int[p.length()];
    zero();//заполняем её нулями
    for(int i=0;i<r.length();i++){//заполняем связи вежду вершинами весами их ребер
        int bi=IndexOf(r[i].retBegin()),ei=IndexOf(r[i].retEnd());
        matrix[bi][ei]=r[i].retVes();
        matrix[ei][bi]=r[i].retVes();
    }
    oldSize=p.length();
}

QVector<QString> Graph::Poisk(int st, int alg,int end){//оболочная функция для Деикстры
    int Size=p.length();//запоминаем размер матрицы
    bool* visited=new bool[Size];//создаем массив для запоминания посещали мы эту вершину или нет
    int* D=new int[Size];//массив хранящий расстояния до вершин
    QVector <QVector <Edge>> pyti;
    CreatMatrix();//создаем матрицу смежности
    for(int i=0;i<Size;i++){//инициализируем масив посещения false и массив растояний значениями из строки матрицы смежности
        D[i]=matrix[st][i];
        visited[i]=false;
    }
    switch(alg){
    case 0:
        Ford_Bellman(st,D,Size);
        break;
    case 1:
        Dijcstra(st,visited,D,Size,pyti);
        break;
    case 2:
        for(int i=0;i<Size;i++)
            D[i]=-1;
        D[0]=st;
        visited[st]=true;
        QVector<QVector<int>> ways;
        int tmp=0;
        Way(st,end,1,D,visited,Size,ways,tmp);
        tmp=0;
        for(int i=1;i<ways.length();i++)
            if(ways[i][Size]<ways[tmp][Size])
                tmp=i;
        if(ways.length()!=0)
            for(int i=0;i<Size;i++)
                D[i]=ways[tmp][i];
        break;
    }
    QVector<QString> ot;
    //QVector<QString> ot;//создаем вектор строк хранящих расстояния
    for (int i=0; i<Size; i++){
        if(D[i]!=2000000)
            ot.append(QString::number(D[i]));
        else
            ot.append("Not Found");
    }
    delete [] D;
    delete [] visited;
    DelMatrix();
    return ot;
}

int Graph::IndexOf(Point _p){//совой indexof тк листовый не видит перегрузку == для Point
    for (auto i=p.begin();i<p.begin()+p.length();i++) {
        if(_p==*i)
            return reinterpret_cast<int>(i-p.begin());//если в векторе p есть такая Point вернет её индекс
    }
    return -1;//если нет вернем -1
}

void Graph::RemovePoint(const int& i){//удаляет [i] вершину и все ребра связаные с этой вершиной
    QVector<int> del;
    for (int j=0;j<r.length();j++){
        if(&r[j].retBegin()==&p[i])
            del.append(j);
        if(&r[j].retEnd()==&p[i])
            del.append(j);
    }
    int move=0;
    for(auto j:del){
        r.removeAt(j-move);
        move++;
    }
    p[i].Del();
    p.removeAt(i);
}

void Graph::RemoveEdge(const Point& l){//удаляет ребро на котором лежит Point& l
    for (int i=0;i<r.length();i++) {
        double radian=ygol_meg_3_Point(r[i].retBegin(),l,r[i].retEnd());
        if(radian<=3.3 && radian>=2.8){
            r.removeAt(i);
            break;
        }
    }
}

bool Graph::DelCopy(Edge& _r){//метод удаляющий ребро если такое уже существует
/*мой граф не ориентированный этот метод присекает ребра вида a->b b-> a*/
    int sysh=0;
    for (int i=0;i<r.length();i++){
        if(&r[i].retBegin()==&_r.retBegin() && &r[i].retEnd()==&_r.retEnd())
            sysh++;
        if(&r[i].retBegin()==&_r.retEnd() && &r[i].retEnd()==&_r.retBegin())
            sysh++;
        if(sysh>1){
            r.removeAt(r.length()-1);
            return true;}
    }
    return false;
}

void Graph::Clear(){//очищает граф от вершин и ребер
    for(auto& i:p)
        i.Del();
    r.clear();
    p.clear();
    DelMatrix();
    matrix=nullptr;
    oldSize=-1;
}


void Graph::UpDate(){
    for(auto& i:p)
        i.UpDate();
    for(auto& i:r)
        i.UpDate();
}

void Graph::Way(int& s, int& f, int iskomaya,int *way,bool *include,const int& size,QVector<QVector<int>>& ways,int& v){
        if(s!=f)
            for(int tek=0; tek<size; tek++){
                if((matrix[s][tek]!=2000000 || matrix[tek][s]!=2000000)&&(!include[tek])){
                    v+=matrix[s][tek];
                    way[iskomaya]=tek;
                    include[tek]=true;
                    Way(tek, f, iskomaya+1,way,include,size,ways,v);
                    v-=matrix[s][tek];
                    include[tek]=false;
                    way[iskomaya]=-1;
                }
            }
        else {
            QVector<int> tmp(size+1);
            for(int i=0;i<size;i++)
                tmp[i]=way[i];
            tmp[size]=v;
            //v=0;
            ways.append(tmp);
        }
}


int Graph::IndexOf(Point* beg,Point* end){
    for(int i=0;i<r.length();i++)
        if((&r[i].retBegin()==beg && &r[i].retEnd()==end) || (&r[i].retBegin()==end && &r[i].retEnd()==beg))
            return i;
    return -1;
}
