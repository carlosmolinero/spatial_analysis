#ifndef COMPARE_H
#define COMPARE_H
//#include "ArchivoTexto.h"
//#include <vector>

template<class T>
class CompareFunc
{
public:
    int indexDistance;
    int type;
    static const int BYDISTANCE=1;
    static const int BYDISTANCE_INVERTED=4;
    static const int BYNUMBERCHILDREN=2;
//        static const int BYDEGREE=5;
    static const int BY_DISTANCE_AND_HEURISTIC=3;
//    static const int COMPARE_CLUSTER_STRINGS_BY_SIZE=5;
    CompareFunc(int indexDistance,int type);
    CompareFunc();
    void set(int indexDistance,int type);
//    CompareFunc(int type);
    virtual ~CompareFunc();
    bool operator() ( const T &a, const T &b );
    double getValue(T &a);
protected:
private:
};
template<class T>
CompareFunc<T>::CompareFunc(int indexDistance,int type)
{
    //ctor
    this->indexDistance=indexDistance;
    this->type=type;
}
template<class T>
CompareFunc<T>::CompareFunc()
{

}
template<class T>
void CompareFunc<T>::set(int indexDistance,int type)
{

    this->indexDistance=indexDistance;
    this->type=type;
}
//template<class T>
//CompareFunc<T>::CompareFunc(int type)
//{
//    //ctor
//    this->indexDistance=-1;
//    this->type=type;
//}
template<class T>
CompareFunc<T>::~CompareFunc()
{
    //dtor
}

template<class T>
bool CompareFunc<T>::operator() (const T &a, const T &b )
{
    if (type==BYDISTANCE)
    {
        return ((a->minOtherDistances[indexDistance])>(b->minOtherDistances[indexDistance]));
    }
    else if (type==BYNUMBERCHILDREN)
    {
        return ((a->numOtherChildren[indexDistance])<(b->numOtherChildren[indexDistance]));
    }
    else if(type==BY_DISTANCE_AND_HEURISTIC)
    {
        return ((a->minOtherDistances[indexDistance]+a->heuristicDistanceToGoal)>(b->minOtherDistances[indexDistance]+b->heuristicDistanceToGoal));
    }
    else if(type==BYDISTANCE_INVERTED)
    {
        return ((a->minOtherDistances[indexDistance])<(b->minOtherDistances[indexDistance]));
    }
    
//    else if(type==COMPARE_CLUSTER_STRINGS_BY_SIZE)
//    {
//        ArchivoTexto textFile;
//        std::vector<std::string> textfile.extractWords
//        return ((a->minOtherDistances[indexDistance])<(b->minOtherDistances[indexDistance]));
//    }
    else
    {
        return false;
    }
}

template<class T>
double CompareFunc<T>::getValue(T &a)
{
    if (type==BYDISTANCE)
    {
        return a->minOtherDistances[indexDistance];
    }
    else if (type==BYNUMBERCHILDREN)
    {
        return a->numOtherChildren[indexDistance];
    }
    else if(type==BY_DISTANCE_AND_HEURISTIC)
    {
        return a->minOtherDistances[indexDistance]+a->heuristicDistanceToGoal;
    }
    else if(type==BYDISTANCE_INVERTED)
    {
        return a->minOtherDistances[indexDistance];
    }
    
    //    else if(type==COMPARE_CLUSTER_STRINGS_BY_SIZE)
    //    {
    //        ArchivoTexto textFile;
    //        std::vector<std::string> textfile.extractWords
    //        return ((a->minOtherDistances[indexDistance])<(b->minOtherDistances[indexDistance]));
    //    }
    else
    {
        return 0;
    }
}
#endif // COMPARE_H
