#include "TextFile.h"
//#include "BST.h"

//TextFile::TextFile()
//{
//    //ctor
//}
void TextFile::writeToFile(std::string name,std::vector<double> values,bool append)
{
    const char * nombre;
    nombre=name.c_str();
    std::ofstream myfile;
    if (append)
    {
        myfile.open(nombre,std::ios_base::app);
    }
    else
    {
        myfile.open(nombre);
    }
    if (myfile.is_open())
    {
        for (long i=0; i<values.size(); i++)
        {
            myfile<<std::to_string(values[i])<<'\n';
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

void TextFile::writeToFile(std::string name,std::vector<long> values,bool append)
{
    const char * nombre;
    nombre=name.c_str();
    std::ofstream myfile;
    if (append)
    {
        myfile.open(nombre,std::ios_base::app);
    }
    else
    {
        myfile.open(nombre);
    }
    if (myfile.is_open())
    {
        for (long i=0; i<values.size(); i++)
        {
            myfile<<std::to_string(values[i])<<'\n';
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}
void TextFile::writeToFile(std::string name,std::vector<std::string> values,bool append)
{
    const char * nombre;
    nombre=name.c_str();
    std::ofstream myfile;
    if (append)
    {
        myfile.open(nombre,std::ios_base::app);
    }
    else
    {
        myfile.open(nombre);
    }
    if (myfile.is_open())
    {
        for (long i=0; i<values.size(); i++)
        {
            myfile<<values[i]<<'\n';
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}
bool TextFile::open (std::string name,std::ifstream &file)
{
    const char * nombre;
    nombre=name.c_str();
//    cout<<nombre;
    file.open(nombre, std::ifstream::in);
    file.is_open();
    if (file.fail())
    {
//         cout<<"false";
        return false;
    }
    else
    {
//         cout<<"true";
        return true;
    }
}
std::string TextFile::getLine(std::ifstream &file)
{
    std::string line;
    if (!file.eof())
    {
        getline(file, line);
        return line;
    }
    else
    {
        return "";
    }

}

std::vector<double> TextFile::parseSimpleNumericFile(std::string name)
{
    std::ifstream file;
    bool abierto=open(name,file);
    std::vector<double> values;
    if (abierto)
    {
//        cout<<"dentro de leer";
        std::string linea;
        linea=TextFile::getLine(file);//skipping the names of variables
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
                const char * input;
                input=linea.c_str();
                double value=atof(input);
                values.push_back(value);
            }
        }

        TextFile::close(file);
    }
    return (values);
}
void TextFile::readCoordinatesNodes(std::string name,std::string separator){
    std::ifstream file;
    std::cout<<"name of coordinates file : "<<name<<'\n';
    bool abierto=open(name,file);
    bool header=true;
    //    BST<long> ids;
    //    std::vector<double> weights;
    if (abierto)
    {
        std::string linea;
        if(header)
        {
            linea=TextFile::getLine(file);//skipping the names of variables
        }
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
                std::vector<std::string> words=extractWords(linea, separator);
                const char * input;
                input=words[0].c_str();
                unsigned long long idA=std::stoull(input);
                //                input=words[1].c_str();
                //                unsigned long long idB=stoull(input);
                //                if(idA==idB)
                //                {
                //                    // std::cout<<"loop in original file!!"<<'\n';
                //                }
                //                else
                //                {
                //                    input=words[2].c_str();
                //                    double weight=atof(input);
                input=words[1].c_str();
                double x1=atof(input);
                input=words[2].c_str();
                double y1=atof(input);
                //                    input=words[5].c_str();
                //                    double x2=atof(input);
                //                    input=words[6].c_str();
                //                    double y2=atof(input);
                //                bool existA=ids.exist(idA);
//                long idTempA;
                //                if (!existA){
                ////                    idTempA=graph->addNode();
                ////                    ids.add(idA, idTempA);
                //                }else{
                Configuration::addCoordinate(idA, Point2d(x1,y1));
//                graph->nodes[idTempA].originalID=idA;
//                graph->nodes[idTempA].location=Point2d(x1,y1);
                //                }
                //                bool existB=ids.exist(idB);
                //                    long idTempB;
                //                if (!existB){
                //                    idTempB=graph->addNode();
                //                    ids.add(idB, idTempB);
                //                }else{
                //                    idTempB=ids.get(idB);
                //                    //                }
                //                    graph->nodes[idTempB].originalID=idB;
                //                    graph->nodes[idTempB].location=Point2d(x2,y2);
                //                    std::vector<double> otherWeights;
                //                    //                std::vector<double> otherWeights;
                //                    otherWeights.clear();
                //                    //                for (long j=0;j<1.size();j++){
                //                    //                    otherWeights.push_back(1);
                //                    //                }
                //                    graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
                //                }

            }
        }

        TextFile::close(file);
    }
}
//void TextFile::parseNCOLandSeparateCoordinatesFile(std::string nameNCOLFile,std::string nameCoordinatesFile,Graph* graph,std::string separatorNCOL,std::string separatorCoordinates,bool header,bool includeIDTransitions){
//    std::ifstream file;
//    bool abierto=open(nameCoordinatesFile,file);
//    std::unordered_map<unsigned long long,long> ids;
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separatorCoordinates);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
////                input=words[1].c_str();
////                unsigned long long idB=stoull(input);
//                //                input=words[2].c_str();
//                //                double weight=atof(input);
//                //std::cout<<idB<<'\n';
////                if (idA!=idB)
////                {
//                    bool existA=true;
//                    if(ids[idA]-1==-1){
//                        existA=false;
//                    }
//                    long idTempA;
//                    if (!existA)
//                    {
//                        Node& nodeAdded=graph->addNode();
//                        idTempA=nodeAdded.id;
//                        ids[idA] =idTempA+1;
//                    }
//                    else
//                    {
//                        idTempA=ids[idA]-1;
//                    }
////                    bool existB=ids.exist(idB);
////                    long idTempB;
////
////                    if (!existB)
////                    {
////                        Node& nodeAdded=graph->addNode();
////                        idTempB=nodeAdded.id;
////                        ids.add(idB, idTempB);
////                    }
////                    else
////                    {
////                        idTempB=ids.get(idB);
////                    }
////                }
//
////                std::vector<double> otherWeights;
//                //                graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//    abierto=open(nameCoordinatesFile,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separatorCoordinates);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
////                std::cout<<idA<<'\n';
////                input=words[1].c_str();
////                unsigned long long idB=stoull(input);
////                if(idA==idB)
////                {
////                    // std::cout<<"loop in original file!!"<<'\n';
////                }
////                else
////                {
////                    input=words[2].c_str();
////                    double weight=atof(input);
//                    input=words[1].c_str();
//                    double x1=atof(input);
//                    input=words[2].c_str();
//                    double y1=atof(input);
////                    input=words[5].c_str();
////                    double x2=atof(input);
////                    input=words[6].c_str();
////                    double y2=atof(input);
//                    //                bool existA=ids.exist(idA);
//                    long idTempA;
//                    //                if (!existA){
//                    ////                    idTempA=graph->addNode();
//                    ////                    ids.add(idA, idTempA);
//                    //                }else{
//                    idTempA=ids[idA]-1;
//                    graph->nodes[idTempA].originalID=idA;
//                    graph->nodes[idTempA].location=Point2d(x1,y1);
//                    //                }
//                    //                bool existB=ids.exist(idB);
////                    long idTempB;
//                    //                if (!existB){
//                    //                    idTempB=graph->addNode();
//                    //                    ids.add(idB, idTempB);
//                    //                }else{
////                    idTempB=ids.get(idB);
////                    //                }
////                    graph->nodes[idTempB].originalID=idB;
////                    graph->nodes[idTempB].location=Point2d(x2,y2);
////                    std::vector<double> otherWeights;
////                    //                std::vector<double> otherWeights;
////                    otherWeights.clear();
////                    //                for (long j=0;j<1.size();j++){
////                    //                    otherWeights.push_back(1);
////                    //                }
////                    graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
////                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//    abierto=open(nameNCOLFile,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        long idTransitionsAutomatic=0;
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separatorNCOL);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                input=words[1].c_str();
//                unsigned long long idB=stoull(input);
//                if(idA==idB)
//                {
//                    // std::cout<<"loop in original file!!"<<'\n';
//                }
//                else
//                {
//                    input=words[2].c_str();
//                    double weight=stod(input);
//                    long idTransition=0;
//                    if(includeIDTransitions){
//
//                        input=words[3].c_str();
//                     idTransition=stol(input);
//                    }else{
//                        idTransition=idTransitionsAutomatic;
//                        idTransitionsAutomatic++;
//                    }
////                    input=words[3].c_str();
////                    double x1=atof(input);
////                    input=words[4].c_str();
////                    double y1=atof(input);
////                    input=words[5].c_str();
////                    double x2=atof(input);
////                    input=words[6].c_str();
////                    double y2=atof(input);
//                    //                bool existA=ids.exist(idA);
//                    long idTempA;
//                    //                if (!existA){
//                    ////                    idTempA=graph->addNode();
//                    ////                    ids.add(idA, idTempA);
//                    //                }else{
//                    idTempA=ids[idA]-1;
////                    graph->nodes[idTempA].originalID=idA;
////                    graph->nodes[idTempA].location=Point2d(x1,y1);
//                    //                }
//                    //                bool existB=ids.exist(idB);
//                    long idTempB;
//                    //                if (!existB){
//                    //                    idTempB=graph->addNode();
//                    //                    ids.add(idB, idTempB);
//                    //                }else{
//                    idTempB=ids[idB]-1;
////                    graph->nodes[idTempB].inDegree++;
//                    //                }
////                    graph->nodes[idTempB].originalID=idB;
////                    graph->nodes[idTempB].location=Point2d(x2,y2);
//                    std::vector<double> otherWeights;
//                    //                std::vector<double> otherWeights;
//                    otherWeights.clear();
//                    //                for (long j=0;j<1.size();j++){
//                    //                    otherWeights.push_back(1);
//                    //                }
//                    Transition trans;
//                    trans.a=&graph->nodes[idTempA];
//                    trans.b=&graph->nodes[idTempB];
//                    trans.weight=weight;
//                    trans.otherWeights=otherWeights;
////                    if(includeIDTransitions){
//                        trans.originalID=idTransition;
////                    }
////                    idTransitions++;
//                    graph->addDirectedTransition(trans);
//                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//}
//
//
//
//
//
//void TextFile::parseNCOLWithNamesEdgesAndSeparateCoordinatesFile(std::string nameNCOLFile,std::string nameCoordinatesFile,Graph* graph,std::string separatorNCOL,std::string separatorCoordinates,bool header){
//    std::ifstream file;
//    bool abierto=open(nameCoordinatesFile,file);
//    std::unordered_map<unsigned long long,long> ids;
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separatorCoordinates);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                //                input=words[1].c_str();
//                //                unsigned long long idB=stoull(input);
//                //                input=words[2].c_str();
//                //                double weight=atof(input);
//                //std::cout<<idB<<'\n';
//                //                if (idA!=idB)
//                //                {
//                bool existA=true;
//                if(ids[idA]-1==-1){
//                    existA=false;
//                }
//                long idTempA;
//                if (!existA)
//                {
//                    Node& nodeAdded=graph->addNode();
//                    idTempA=nodeAdded.id;
//                    ids[idA] =idTempA+1;
//                }
//                else
//                {
//                    idTempA=ids[idA]-1;
//                }
//                //                    bool existB=ids.exist(idB);
//                //                    long idTempB;
//                //
//                //                    if (!existB)
//                //                    {
//                //                        Node& nodeAdded=graph->addNode();
//                //                        idTempB=nodeAdded.id;
//                //                        ids.add(idB, idTempB);
//                //                    }
//                //                    else
//                //                    {
//                //                        idTempB=ids.get(idB);
//                //                    }
//                //                }
//
//                //                std::vector<double> otherWeights;
//                //                graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//    abierto=open(nameCoordinatesFile,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separatorCoordinates);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                //                input=words[1].c_str();
//                //                unsigned long long idB=stoull(input);
//                //                if(idA==idB)
//                //                {
//                //                    // std::cout<<"loop in original file!!"<<'\n';
//                //                }
//                //                else
//                //                {
//                //                    input=words[2].c_str();
//                //                    double weight=atof(input);
//                input=words[1].c_str();
//                double x1=atof(input);
//                input=words[2].c_str();
//                double y1=atof(input);
//                //                    input=words[5].c_str();
//                //                    double x2=atof(input);
//                //                    input=words[6].c_str();
//                //                    double y2=atof(input);
//                //                bool existA=ids.exist(idA);
//                long idTempA;
//                //                if (!existA){
//                ////                    idTempA=graph->addNode();
//                ////                    ids.add(idA, idTempA);
//                //                }else{
//                idTempA=ids[idA]-1;
//                graph->nodes[idTempA].originalID=idA;
//                graph->nodes[idTempA].location=Point2d(x1,y1);
//                //                }
//                //                bool existB=ids.exist(idB);
//                //                    long idTempB;
//                //                if (!existB){
//                //                    idTempB=graph->addNode();
//                //                    ids.add(idB, idTempB);
//                //                }else{
//                //                    idTempB=ids.get(idB);
//                //                    //                }
//                //                    graph->nodes[idTempB].originalID=idB;
//                //                    graph->nodes[idTempB].location=Point2d(x2,y2);
//                //                    std::vector<double> otherWeights;
//                //                    //                std::vector<double> otherWeights;
//                //                    otherWeights.clear();
//                //                    //                for (long j=0;j<1.size();j++){
//                //                    //                    otherWeights.push_back(1);
//                //                    //                }
//                //                    graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//                //                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//    abierto=open(nameNCOLFile,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        long idTransitionsAutomatic=0;
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separatorNCOL);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                input=words[1].c_str();
//                unsigned long long idB=stoull(input);
//                if(idA==idB)
//                {
//                    // std::cout<<"loop in original file!!"<<'\n';
//                }
//                else
//                {
////                    input=words[2].c_str();
////                    double weight=stod(input);
//                    long idTransition=0;
//                    int type;
//                    std::string nameRoad;
//
//                        input=words[2].c_str();
//                        nameRoad=extractWords(input, "\"")[0];
//                    input=words[3].c_str();
//                    type=stoi(input);
//
//
//                        idTransition=idTransitionsAutomatic;
//                        idTransitionsAutomatic++;
//
//                    //                    input=words[3].c_str();
//                    //                    double x1=atof(input);
//                    //                    input=words[4].c_str();
//                    //                    double y1=atof(input);
//                    //                    input=words[5].c_str();
//                    //                    double x2=atof(input);
//                    //                    input=words[6].c_str();
//                    //                    double y2=atof(input);
//                    //                bool existA=ids.exist(idA);
//                    long idTempA;
//                    //                if (!existA){
//                    ////                    idTempA=graph->addNode();
//                    ////                    ids.add(idA, idTempA);
//                    //                }else{
//                    idTempA=ids[idA]-1;
//                    //                    graph->nodes[idTempA].originalID=idA;
//                    //                    graph->nodes[idTempA].location=Point2d(x1,y1);
//                    //                }
//                    //                bool existB=ids.exist(idB);
//                    long idTempB;
//                    //                if (!existB){
//                    //                    idTempB=graph->addNode();
//                    //                    ids.add(idB, idTempB);
//                    //                }else{
//                    idTempB=ids[idB]-1;
//                    //                    graph->nodes[idTempB].inDegree++;
//                    //                }
//                    //                    graph->nodes[idTempB].originalID=idB;
//                    //                    graph->nodes[idTempB].location=Point2d(x2,y2);
//                    std::vector<double> otherWeights;
//                    //                std::vector<double> otherWeights;
//                    otherWeights.clear();
//                    //                for (long j=0;j<1.size();j++){
//                    //                    otherWeights.push_back(1);
//                    //                }
//                    Transition trans;
//                    trans.a=&graph->nodes[idTempA];
//                    trans.b=&graph->nodes[idTempB];
//
//                    trans.a->levelHierarchyRoad=min(trans.a->levelHierarchyRoad,(double)type);
//                    trans.b->levelHierarchyRoad=min(trans.b->levelHierarchyRoad,(double)type);
////                    trans.levelHierarchyRoad=min(trans.a->levelHierarchyRoad,trans.b->levelHierarchyRoad);
//                    trans.levelHierarchyRoad=type;
//                    trans.nameRoad=nameRoad;
//                    trans.weight=Functions::getDistance(trans.a->location, trans.b->location);
//                    trans.otherWeights=otherWeights;
//                    //                    if(includeIDTransitions){
//                    trans.originalID=idTransition;
//                    //                    }
//                    //                    idTransitions++;
//                    graph->addDirectedTransition(trans);
//                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//}
//
//
//
//void TextFile::parsePajekGraphAndInformationalDual(std::string nameGraphFile,std::string nameDualFile,Graph* graph,Graph* lineGraph,Graph* dualGraph){
////    Graph graph;
//    std::ifstream file;
//    bool abierto=open(nameGraphFile,file);
//    std::cout<<nameGraphFile<<'\n';
//    std::unordered_map<unsigned long long,long> ids;
//    std::vector<vector<long> > correspondances;
//    std::string separator=" ";
//
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
////        if(header)
////        {
//            linea=TextFile::getLine(file);//skipping the names of variables
////        }
//                while((linea!="*Edges\r"&&linea!="*Edges"))
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0&&linea!="*Edges\r"&&linea!="*Edges")
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                //                input=words[1].c_str();
//                //                unsigned long long idB=stoull(input);
//                //                input=words[2].c_str();
//                //                double weight=atof(input);
//                //std::cout<<idB<<'\n';
//                //                if (idA!=idB)
//                //                {
//                bool existA=true;
//                if(ids[idA]-1==-1){
//                    existA=false;
//                }
//                long idTempA;
//                if (!existA)
//                {
//                    Node& nodeAdded=graph->addNode();
//                    idTempA=nodeAdded.id;
//                    ids[idA] =idTempA+1;
//                }
//                else
//                {
//                    idTempA=ids[idA]-1;
//                }
//                //                    bool existB=ids.exist(idB);
//                //                    long idTempB;
//                //
//                //                    if (!existB)
//                //                    {
//                //                        Node& nodeAdded=graph->addNode();
//                //                        idTempB=nodeAdded.id;
//                //                        ids.add(idB, idTempB);
//                //                    }
//                //                    else
//                //                    {
//                //                        idTempB=ids.get(idB);
//                //                    }
//                //                }
//
//                //                std::vector<double> otherWeights;
//                //                graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//    abierto=open(nameGraphFile,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
////        if(header)
////        {
//            linea=TextFile::getLine(file);//skipping the names of variables
////        }
//
//        while((linea!="*Edges\r"&&linea!="*Edges"))
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0&&linea!="*Edges\r"&&linea!="*Edges")
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                //                input=words[1].c_str();
//                //                unsigned long long idB=stoull(input);
//                //                if(idA==idB)
//                //                {
//                //                    // std::cout<<"loop in original file!!"<<'\n';
//                //                }
//                //                else
//                //                {
//                //                    input=words[2].c_str();
//                //                    double weight=atof(input);
//                input=words[2].c_str();
//                double x1=atof(input);
//                input=words[3].c_str();
//                double y1=atof(input);
//                //                    input=words[5].c_str();
//                //                    double x2=atof(input);
//                //                    input=words[6].c_str();
//                //                    double y2=atof(input);
//                //                bool existA=ids.exist(idA);
//                long idTempA;
//                //                if (!existA){
//                ////                    idTempA=graph->addNode();
//                ////                    ids.add(idA, idTempA);
//                //                }else{
//                idTempA=ids[idA]-1;
//                graph->nodes[idTempA].originalID=idA;
//                graph->nodes[idTempA].location=Point2d(x1,y1);
//                //                }
//                //                bool existB=ids.exist(idB);
//                //                    long idTempB;
//                //                if (!existB){
//                //                    idTempB=graph->addNode();
//                //                    ids.add(idB, idTempB);
//                //                }else{
//                //                    idTempB=ids.get(idB);
//                //                    //                }
//                //                    graph->nodes[idTempB].originalID=idB;
//                //                    graph->nodes[idTempB].location=Point2d(x2,y2);
//                //                    std::vector<double> otherWeights;
//                //                    //                std::vector<double> otherWeights;
//                //                    otherWeights.clear();
//                //                    //                for (long j=0;j<1.size();j++){
//                //                    //                    otherWeights.push_back(1);
//                //                    //                }
//                //                    graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//                //                }
//
//            }
//        }
//
////        TextFile::close(file);
//    }
////    abierto=open(nameNCOLFile);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
////        if(header)
////        {
////            linea=TextFile::getLine(file);//skipping the names of variables
////        }
//        long idTransitionsAutomatic=0;
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0&&linea!="\r")
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                input=words[1].c_str();
//                unsigned long long idB=stoull(input);
//                if(idA==idB)
//                {
//                    // std::cout<<"loop in original file!!"<<'\n';
//                }
//                else
//                {
//                    input=words[2].c_str();
//                    long correspondance=stol(input);
//
//                    long idTransition=0;
////                    if(includeIDTransitions){
////
////                        input=words[3].c_str();
////                        idTransition=stol(input);
////                    }else{
//                        idTransition=idTransitionsAutomatic;
//
////                    }
//                    std::vector<long> completeCorrespondance;
////                    if(idTransition==1249){
////                        std::cout<<"aqui"<<'\n';
////                    }
//                    completeCorrespondance.push_back(idTransition);
//                    completeCorrespondance.push_back(correspondance);
//                    correspondances.push_back(completeCorrespondance);
//                    //                    input=words[3].c_str();
//                    //                    double x1=atof(input);
//                    //                    input=words[4].c_str();
//                    //                    double y1=atof(input);
//                    //                    input=words[5].c_str();
//                    //                    double x2=atof(input);
//                    //                    input=words[6].c_str();
//                    //                    double y2=atof(input);
//                    //                bool existA=ids.exist(idA);
//                    long idTempA;
//                    //                if (!existA){
//                    ////                    idTempA=graph->addNode();
//                    ////                    ids.add(idA, idTempA);
//                    //                }else{
//                    idTempA=ids[idA]-1;
//                    //                    graph->nodes[idTempA].originalID=idA;
//                    //                    graph->nodes[idTempA].location=Point2d(x1,y1);
//                    //                }
//                    //                bool existB=ids.exist(idB);
//                    long idTempB;
//                    //                if (!existB){
//                    //                    idTempB=graph->addNode();
//                    //                    ids.add(idB, idTempB);
//                    //                }else{
//                    idTempB=ids[idB]-1;
//                    //                    graph->nodes[idTempB].inDegree++;
//                    //                }
//                    //                    graph->nodes[idTempB].originalID=idB;
//                    //                    graph->nodes[idTempB].location=Point2d(x2,y2);
//                    std::vector<double> otherWeights;
//                    //                std::vector<double> otherWeights;
//                    otherWeights.clear();
//                    //                for (long j=0;j<1.size();j++){
//                    //                    otherWeights.push_back(1);
//                    //                }
//                    Transition trans;
//                    trans.a=&graph->nodes[idTempA];
//                    trans.b=&graph->nodes[idTempB];
//                    double weight=Functions::getDistance(graph->nodes[idTempA].location, graph->nodes[idTempB].location);
//                    trans.weight=weight;
//                    trans.otherWeights=otherWeights;
//                    //                    if(includeIDTransitions){
//                    trans.originalID=idTransition;
//                    trans.id=idTransitionsAutomatic;
//                    //                    }
//                    //                    idTransitions++;
//                    graph->addDirectedTransition(trans);
//                    idTransitionsAutomatic++;
//                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//
//
//
//
//
//
//
//
//
//
//
//
//    abierto=open(nameDualFile,file);
//    std::unordered_map<unsigned long long,long> idDuals;
//
//
//    //    std::vector<double> weights;
//    long totalNumberOfNodesAdded=0;
//    long totalNumerOfNodes=0;
//    if (abierto)
//    {
//        std::string linea;
//        //        if(header)
//        //        {
//        linea=TextFile::getLine(file);//skipping the names of variables
//        //        }
//        std::vector<std::string> words=extractWords(linea, separator);
//        const char * input;
//        input=words[1].c_str();
//        totalNumerOfNodes=stol(input);
//
//        while((linea!="*Edges\r"&&linea!="*Edges"))
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0&&linea!="*Edges\r"&&linea!="*Edges")
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                 totalNumberOfNodesAdded++;
//                //                input=words[1].c_str();
//                //                unsigned long long idB=stoull(input);
//                //                input=words[2].c_str();
//                //                double weight=atof(input);
//                //std::cout<<idB<<'\n';
//                //                if (idA!=idB)
//                //                {
//                bool existA=true;
//                if(idDuals[idA]-1==-1){
//                    existA=false;
//                }
//                long idTempA;
//                if (!existA)
//                {
//                    Node& nodeAdded=dualGraph->addNode();
//                    idTempA=nodeAdded.id;
//                    idDuals[idA] =idTempA+1;
//                }
//                else
//                {
//                    idTempA=idDuals[idA]-1;
//                }
//                //                    bool existB=ids.exist(idB);
//                //                    long idTempB;
//                //
//                //                    if (!existB)
//                //                    {
//                //                        Node& nodeAdded=graph->addNode();
//                //                        idTempB=nodeAdded.id;
//                //                        ids.add(idB, idTempB);
//                //                    }
//                //                    else
//                //                    {
//                //                        idTempB=ids.get(idB);
//                //                    }
//                //                }
//
//                //                std::vector<double> otherWeights;
//                //                graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//
//            }
//        }
//
//
//        TextFile::close(file);
//    }
//    abierto=open(nameDualFile,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
//        //        if(header)
//        //        {
//        linea=TextFile::getLine(file);//skipping the names of variables
//        //        }
//
//
//        while((linea!="*Edges\r"&&linea!="*Edges"))
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0&&linea!="*Edges\r"&&linea!="*Edges")
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//
//                //                input=words[1].c_str();
//                //                unsigned long long idB=stoull(input);
//                //                if(idA==idB)
//                //                {
//                //                    // std::cout<<"loop in original file!!"<<'\n';
//                //                }
//                //                else
//                //                {
//                //                    input=words[2].c_str();
//                //                    double weight=atof(input);
//                input=words[2].c_str();
//                double x1=atof(input);
//                input=words[3].c_str();
//                double y1=atof(input);
//                //                    input=words[5].c_str();
//                //                    double x2=atof(input);
//                //                    input=words[6].c_str();
//                //                    double y2=atof(input);
//                //                bool existA=ids.exist(idA);
//                long idTempA;
//                //                if (!existA){
//                ////                    idTempA=graph->addNode();
//                ////                    ids.add(idA, idTempA);
//                //                }else{
//                idTempA=idDuals[idA]-1;
//                dualGraph->nodes[idTempA].originalID=idA;
//                dualGraph->nodes[idTempA].location=Point2d(x1,y1);
//                //                }
//                //                bool existB=ids.exist(idB);
//                //                    long idTempB;
//                //                if (!existB){
//                //                    idTempB=graph->addNode();
//                //                    ids.add(idB, idTempB);
//                //                }else{
//                //                    idTempB=ids.get(idB);
//                //                    //                }
//                //                    graph->nodes[idTempB].originalID=idB;
//                //                    graph->nodes[idTempB].location=Point2d(x2,y2);
//                //                    std::vector<double> otherWeights;
//                //                    //                std::vector<double> otherWeights;
//                //                    otherWeights.clear();
//                //                    //                for (long j=0;j<1.size();j++){
//                //                    //                    otherWeights.push_back(1);
//                //                    //                }
//                //                    graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//                //                }
//
//            }
//        }
//
//
//        //        TextFile::close(file);
//    }
//    //    abierto=open(nameNCOLFile);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//
//    if(totalNumberOfNodesAdded==0){
//        for(long i=0;i<totalNumerOfNodes;i++){
//            unsigned long long idA=i+1;
//            bool existA=true;
//            if(idDuals[idA]-1==-1){
//                existA=false;
//            }
//            long idTempA;
//            if (!existA)
//            {
//                Node& nodeAdded=dualGraph->addNode();
//                idTempA=nodeAdded.id;
//
//                idDuals[idA] =idTempA+1;
//            }
//            else
//            {
//                idTempA=idDuals[idA]-1;
//            }
//        }
//        for(long i=0;i<totalNumerOfNodes;i++){
//            dualGraph->nodes[i].originalID=dualGraph->nodes[i].id+1;
//        }
//    }
//    if (abierto)
//    {
//        std::string linea;
//        //        if(header)
//        //        {
////        linea=TextFile::getLine(file);//skipping the names of variables
//        //        }
//        long idTransitionsAutomatic=0;
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0&&linea!="\r")
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                input=words[1].c_str();
//                unsigned long long idB=stoull(input);
//                if(idA==idB)
//                {
//                    // std::cout<<"loop in original file!!"<<'\n';
//                }
//                else
//                {
////                    input=words[2].c_str();
////                    double correspondance=stod(input);
//                    long idTransition=0;
//                    //                    if(includeIDTransitions){
//                    //
//                    //                        input=words[3].c_str();
//                    //                        idTransition=stol(input);
//                    //                    }else{
//                    idTransition=idTransitionsAutomatic;
//                    idTransitionsAutomatic++;
//                    //                    }
//                    //                    input=words[3].c_str();
//                    //                    double x1=atof(input);
//                    //                    input=words[4].c_str();
//                    //                    double y1=atof(input);
//                    //                    input=words[5].c_str();
//                    //                    double x2=atof(input);
//                    //                    input=words[6].c_str();
//                    //                    double y2=atof(input);
//                    //                bool existA=ids.exist(idA);
//                    long idTempA;
//                    //                if (!existA){
//                    ////                    idTempA=graph->addNode();
//                    ////                    ids.add(idA, idTempA);
//                    //                }else{
//                    idTempA=idDuals[idA]-1;
//                    //                    graph->nodes[idTempA].originalID=idA;
//                    //                    graph->nodes[idTempA].location=Point2d(x1,y1);
//                    //                }
//                    //                bool existB=ids.exist(idB);
//                    long idTempB;
//                    //                if (!existB){
//                    //                    idTempB=graph->addNode();
//                    //                    ids.add(idB, idTempB);
//                    //                }else{
//                    idTempB=idDuals[idB]-1;
//                    //                    graph->nodes[idTempB].inDegree++;
//                    //                }
//                    //                    graph->nodes[idTempB].originalID=idB;
//                    //                    graph->nodes[idTempB].location=Point2d(x2,y2);
//                    std::vector<double> otherWeights;
//                    //                std::vector<double> otherWeights;
//                    otherWeights.clear();
//                    //                for (long j=0;j<1.size();j++){
//                    //                    otherWeights.push_back(1);
//                    //                }
//                    Transition trans;
//                    trans.a=&dualGraph->nodes[idTempA];
//                    trans.b=&dualGraph->nodes[idTempB];
////                    double weight=Functions::getDistance(graph->nodes[idTempA].location, graph->nodes[idTempB].location);
//                    trans.weight=1;
//                    trans.otherWeights=otherWeights;
//                    //                    if(includeIDTransitions){
//                    trans.originalID=idTransition;
//                    //                    }
//                    //                    idTransitions++;
//                    if(idTempA!=idTempB){
//                        dualGraph->addDirectedTransition(trans);
//                    }
//                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//
//    graph->transformToBidirectional();
//    dualGraph->transformToBidirectional();
//    std::unordered_map<unsigned long long,Node*> nodesOfDualGraphByOriginalId;
////    std::vector<Node*> nodesToKeep;
//
//
//    for(long i=0;i<dualGraph->nodes.size();i++){
////        dualGraph->nodes[i].id=i;
//        if(dualGraph->nodes[i].transitions.size()==0){
////            dualGraph->nodes.erase(dualGraph->nodes.begin()+i);
////            i--;
//        }else{
////            nodesToKeep.push_back(&(dualGraph->nodes[i]));
//            nodesOfDualGraphByOriginalId[dualGraph->nodes[i].originalID]=&(dualGraph->nodes[i]);
//
//        }
//
//    }
//
//
//
////    Graph temp;
////    dualGraph->getInducedSubgraph(&temp, nodesToKeep);
////    dualGraph->resetGraph();
////    dualGraph->copyGraph(&temp, dualGraph);
////    for(long i=0;i<dualGraph->nodes.size();i++){
////
//////            if(nodesOfDualGraphByOriginalId[dualGraph->nodes[i].originalID]==NULL){
////                nodesOfDualGraphByOriginalId[dualGraph->nodes[i].originalID]=&(dualGraph->nodes[i]);
//////            }
////
////
////    }
//
//    std::unordered_map<long,Transition*> transitionsByOriginalID;
////        std::unordered_map<long,Transition*> transitionsByID;
////    lineGraph->pseudoGraph=true;
//    graph->createLineGraph(graph, lineGraph);
////    lineGraph->transformToBidirectional();
//    for(long i=0;i<graph->nodes.size();i++){
//        for(long j=0;j<graph->nodes[i].transitions.size();j++){
//            transitionsByOriginalID[graph->nodes[i].transitions[j]->originalID]=(graph->nodes[i].transitions[j]);
////            transitionsByID[graph->nodes[i].transitions[j].id]=&(graph->nodes[i].transitions[j]);
//
//        }
//    }
//
//
//    for(long i=0;i<correspondances.size();i++){
//
//
//
//        Transition* trans=transitionsByOriginalID[correspondances[i][0]];
////        long oppositeId=trans->oppositeTransitionId;
//        Transition* oppositeTrans=trans->getSimetricTransition();
//
//        trans->nodeOfLineGraphThatRepresentsThis->nodesRelated.push_back(nodesOfDualGraphByOriginalId[correspondances[i][1]]);
//        oppositeTrans->nodeOfLineGraphThatRepresentsThis->nodesRelated.push_back((nodesOfDualGraphByOriginalId[correspondances[i][1]]));
////        long correspondanceValue=correspondances[i][1];
////        Node* nodeOfCorrespondanceValue=nodesOfDualGraphByOriginalId[correspondances[i][1]];
//        nodesOfDualGraphByOriginalId[correspondances[i][1]]->nodesRelated.push_back((trans->nodeOfLineGraphThatRepresentsThis));
//        nodesOfDualGraphByOriginalId[correspondances[i][1]]->nodesRelated.push_back((oppositeTrans->nodeOfLineGraphThatRepresentsThis));
//    }
//    for(long i=0;i<dualGraph->nodes.size();i++){
//        double x=0;
//        double y=0;
//        for(long j=0;j<dualGraph->nodes[i].nodesRelated.size();j++){
//            x+=dualGraph->nodes[i].nodesRelated[j]->location.x;
//            y+=dualGraph->nodes[i].nodesRelated[j]->location.y;
//        }
//        x/=(double)(dualGraph->nodes[i].nodesRelated.size());
//        y/=(double)(dualGraph->nodes[i].nodesRelated.size());
//        dualGraph->nodes[i].location=Point2d(x,y);
//    }
//
//
//
//
//}
//void TextFile::includeValuesToPassBetweenness(Graph* graph,std::string nameOfFile,std::string separator,bool header){
//    std::ifstream file;
//    bool abierto=open(nameOfFile,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
////    graph->pushNewDistance(distanceType);
//    std::unordered_map<unsigned long long,Node*> nodesByOriginalID;
//
//    for(long i=0;i<graph->nodes.size();i++){
//        nodesByOriginalID[graph->nodes[i].originalID]=&graph->nodes[i];
//    }
//
//
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        //        long idTransitions=1;
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long id=stoull(input);
//                input=words[1].c_str();
//                double weight=stod(input);
//                if (nodesByOriginalID[id]!=NULL){
//                    nodesByOriginalID[id]->valueToPass=weight;
//                     nodesByOriginalID[id]->originalValueToPass=weight;
//                    for(long i=0;i<nodesByOriginalID[id]->valuesToPass.size();i++){
//                            nodesByOriginalID[id]->valuesToPass[i]=weight;
//                          nodesByOriginalID[id]->originalValuesToPass[i]=weight;
//                    }
//                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//}
//void TextFile::includeMasses(Graph* graph,std::string nameOfFile,std::string separator,bool header){
//    std::ifstream file;
//    bool abierto=open(nameOfFile,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
////    graph->pushNewDistance(distanceType);
//    std::unordered_map<unsigned long long,Node*> nodesByOriginalID;
//
//    for(long i=0;i<graph->nodes.size();i++){
//        nodesByOriginalID[graph->nodes[i].originalID]=&graph->nodes[i];
//    }
//
//
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        //        long idTransitions=1;
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long id=stoull(input);
//                input=words[1].c_str();
//                double weight=stod(input);
//                if (nodesByOriginalID[id]!=NULL){
//                    nodesByOriginalID[id]->mass=weight;
//                    //                     nodesByOriginalID[id]->originalValueToPass=weight;
//                    //                    for(long i=0;i<nodesByOriginalID[id]->valuesToPass.size();i++){
//                    //                            nodesByOriginalID[id]->valuesToPass[i]=weight;
//                    //                          nodesByOriginalID[id]->originalValuesToPass[i]=weight;
//                    //                    }
//                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//}
//void TextFile::loadBetweenness(Graph* graph,long indexOfDistance,std::string nameOfFile,std::string separator,bool header){
//    std::ifstream file;
//    bool abierto=open(nameOfFile,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//    //    graph->pushNewDistance(distanceType);
//    std::unordered_map<unsigned long long,Node*> nodesByOriginalID;
//
//    for(long i=0;i<graph->nodes.size();i++){
//        nodesByOriginalID[graph->nodes[i].originalID]=&graph->nodes[i];
//    }
//
//
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        //        long idTransitions=1;
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long id=stoull(input);
//                input=words[1].c_str();
//                double weight=stod(input);
//                if (nodesByOriginalID[id]!=NULL){
//                    graph->betweennessMeasures[indexOfDistance][nodesByOriginalID[id]->id]=weight;
//                    //                     nodesByOriginalID[id]->originalValueToPass=weight;
//                    //                    for(long i=0;i<nodesByOriginalID[id]->valuesToPass.size();i++){
//                    //                            nodesByOriginalID[id]->valuesToPass[i]=weight;
//                    //                          nodesByOriginalID[id]->originalValuesToPass[i]=weight;
//                    //                    }
//                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//}
//void TextFile::includeTripsGeneratedByType(Graph* primalGraph,Graph* lineGraph,std::string nameOfFile,std::string separator,bool header){
//    std::ifstream file;
//    bool abierto=open(nameOfFile,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//    //    graph->pushNewDistance(distanceType);
//    std::unordered_map<unsigned long long,Node*> nodesByOriginalID;
//
//    for(long i=0;i<lineGraph->nodes.size();i++){
//        nodesByOriginalID[lineGraph->nodes[i].originalID]=&lineGraph->nodes[i];
//    }
//
//
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        //        long idTransitions=1;
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long id=stoull(input);
//                input=words[1].c_str();
//                double weight=stod(input);
//                input=words[2].c_str();
//                double type=stod(input);
//                if (nodesByOriginalID[id]!=NULL){
//                    Transition* transPrimal=nodesByOriginalID[id]->transitionThatRepresents;
//                    bool unidirectional=true;
//                    if(transPrimal->getSimetricTransition()!=NULL){
//                        unidirectional=false;
//                    }
//
//                    std::vector<double> valuesTemp;
//                    valuesTemp.push_back(type);
//                    if(!unidirectional){
//                        weight=weight/2;
//                    }
//                    valuesTemp.push_back(weight);
//
//                    if(type==0){
//                        nodesByOriginalID[id]->customizedGeneratedTrips.push_back(valuesTemp);
//                    }else{
//                        nodesByOriginalID[id]->customizedAttractedTrips.push_back(valuesTemp);
//                    }
//
//                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//}
//
//void TextFile::includeOriginalDegreeOfNodes(Graph* graph,std::string nameOfFile,std::string separator,bool header){
//    std::ifstream file;
//    bool abierto=open(nameOfFile,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//
//    std::unordered_map<unsigned long long,Node*> nodesByOriginalID;
//
//    for(long i=0;i<graph->nodes.size();i++){
//        nodesByOriginalID[graph->nodes[i].originalID]=&graph->nodes[i];
//    }
//
//
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        //        long idTransitions=1;
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long id=stoull(input);
//                input=words[1].c_str();
//                double weight=stod(input);
//                if (nodesByOriginalID[id]!=NULL){
//                    nodesByOriginalID[id]->degree=weight;
//                    //                     nodesByOriginalID[id]->originalValueToPass=weight;
//                    //                    for(long i=0;i<nodesByOriginalID[id]->valuesToPass.size();i++){
//                    //                            nodesByOriginalID[id]->valuesToPass[i]=weight;
//                    //                          nodesByOriginalID[id]->originalValuesToPass[i]=weight;
//                    //                    }
//                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//}
//
//void TextFile::addWeightsToGraph(Graph* graph,std::string nameOfFile,std::string separator,bool header,int distanceType){
//    std::ifstream file;
//    bool abierto=open(nameOfFile,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//    graph->pushNewDistance(distanceType);
//    int indexOfDistance=graph->numberDistances;
//    std::unordered_map<unsigned long long,Transition*> transitionsByOriginalID;
//
//    for(long i=0;i<graph->transitions.size();i++){
////        for(long j=0;j<graph->nodes[i].transitions.size();j++)i
//            transitionsByOriginalID[graph->transitions[i].originalID]=&graph->transitions[i];
////        }
//    }
//
//
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        //        long idTransitions=1;
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long id=stoull(input);
//                input=words[1].c_str();
//                double weight=stod(input);
//                if (transitionsByOriginalID[id]!=NULL){
//                    if(transitionsByOriginalID[id]->otherWeights.size()<indexOfDistance){
//                        transitionsByOriginalID[id]->otherWeights.push_back(weight);
//                    }else{
//                        transitionsByOriginalID[id]->otherWeights[indexOfDistance]=weight;
//                    }
//                }
//
//            }
//        }
//
//        for(long i=0;i<graph->transitions.size();i++){
//            if(graph->transitions[i].otherWeights.size()<indexOfDistance){
//                graph->transitions[i].otherWeights.push_back(0);
//            }
//        }
//
//        TextFile::close(file);
//    }
//}
//void TextFile::loadClassificationOfNodes(Graph* graph,std::string nameOfFile,std::vector<Graph> &clusters,std::string separator,bool header){
//    std::ifstream file;
//    bool abierto=open(nameOfFile,file);
//    std::unordered_map<unsigned long long,Node*> nodesByIds;
//    std::unordered_map<long,long> indexClustersById;
//
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        for(long i=0;i<graph->nodes.size();i++){
//            nodesByIds[graph->nodes[i].originalID]=&(graph->nodes[i]);
//        }
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long id=stoull(input);
//                input=words[1].c_str();
//                long idCluster=atol(input);
//                Graph graphCluster;
//                Graph* graphInClusters;
//                if(indexClustersById[idCluster]-1==-1){
//                    graphCluster.id=idCluster;
//                    clusters.push_back(graphCluster);
//                    indexClustersById[idCluster]=clusters.size();
//                    graphInClusters=&clusters[clusters.size()-1];
//                }else{
//                    graphInClusters=&clusters[indexClustersById[idCluster]-1];
//                }
//                graphInClusters->addNode();
//                graphInClusters->nodes[graphInClusters->nodes.size()-1].originalID=id;
//                graphInClusters->nodes[graphInClusters->nodes.size()-1].nodeThatRepresents=nodesByIds[id];
//
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//}

void TextFile::loadPairsFileOfNodeIdAndClusterId(std::vector<std::vector<signed long long> > &pairs,std::string nameOfFile,std::string separator,bool header){
    std::ifstream file;
    bool abierto=open(nameOfFile,file);
//    std::unordered_map<signed long long,Node*> nodesByIds;
    std::unordered_map<long,long> indexClustersById;

    //    std::vector<double> weights;
    if (abierto)
    {

        std::string linea;
        if(header)
        {
            linea=TextFile::getLine(file);//skipping the names of variables
        }
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
                std::vector<std::string> words=extractWords(linea, separator);
                const char * input;
                input=words[0].c_str();
                signed long long id=std::stoull(input);
                input=words[1].c_str();
                signed long long idCluster=std::stoull(input);
                std::vector<signed long long> pair;
                pair.push_back(id);
                pair.push_back(idCluster);
                pairs.push_back(pair);


            }
        }

        TextFile::close(file);
    }
}

void TextFile::loadVectorWithIds(std::unordered_map<long,std::vector<double> >* result,std::string nameOfFile,std::string separator,bool header){
    std::ifstream file;
    bool abierto=open(nameOfFile,file);


    //    std::vector<double> weights;
    if (abierto)
    {

        std::string linea;
        if(header)
        {
            linea=TextFile::getLine(file);//skipping the names of variables
        }
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
                std::vector<std::string> words=extractWords(linea, separator);
                const char * input;
                input=words[0].c_str();
                unsigned long long id=std::stoull(input);
                std::vector<double> resultTemp;
                for(long i=1;i<words.size();i++){
                    input=words[i].c_str();
                    double value=atof(input);
                    resultTemp.push_back(value);
                }
                result->operator[](id)=resultTemp;



            }
        }

        TextFile::close(file);
    }
}

void TextFile::loadMassesPercolation(std::unordered_map<long,long>* result,std::string nameOfFile,std::string separator,bool header){
    std::ifstream file;
    bool abierto=open(nameOfFile,file);


    //    std::vector<double> weights;
    if (abierto)
    {

        std::string linea;
        if(header)
        {
            linea=TextFile::getLine(file);//skipping the names of variables
        }
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
                std::vector<std::string> words=extractWords(linea, separator);
                const char * input;
                input=words[1].c_str();
                unsigned long long id=std::stoull(input);
                long resultTemp;
//                for(long i=1;i<words.size();i++){
                    input=words[2].c_str();
                    long value=atol(input);
                    resultTemp=(value);
//                }
                result->operator[](id)=resultTemp;



            }
        }

        TextFile::close(file);
    }
}
//void TextFile::parseNCOL(std::string name,Graph* graph,std::string separator,bool header)
//{
//    std::ifstream file;
//    bool abierto=open(name,file);
//    std::unordered_map<unsigned long long,long> ids;
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                input=words[1].c_str();
//                unsigned long long idB=stoull(input);
//                //                input=words[2].c_str();
//                //                double weight=atof(input);
//                //std::cout<<idB<<'\n';
//                if (idA!=idB)
//                {
//                    bool existA=true;
//                    if(ids[idA]-1==-1){
//                        existA=false;
//                    }
//                    long idTempA;
//                    if (!existA)
//                    {
//                        Node& nodeAdded=graph->addNode();
//                        idTempA=nodeAdded.id;
//                        ids[idA] =idTempA+1;
//                    }
//                    else
//                    {
//                        idTempA=ids[idA]-1;
//                    }
//                    bool existB=true;
//                    if(ids[idB]-1==-1){
//                        existB=false;
//                    }
//                    long idTempB;
//
//                    if (!existB)
//                    {
//                        Node& nodeAdded=graph->addNode();
//                        idTempB=nodeAdded.id;
//                        ids[idB]= idTempB+1;
//                    }
//                    else
//                    {
//                        idTempB=ids[idB]-1;
//                    }
//                }
//
//                std::vector<double> otherWeights;
//                //                graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//    abierto=open(name,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                input=words[1].c_str();
//                unsigned long long idB=stoull(input);
//                if(idA==idB)
//                {
//                    // std::cout<<"loop in original file!!"<<'\n';
//                }
//                else
//                {
//                    input=words[2].c_str();
//                    double weight=atof(input);
////                    input=words[3].c_str();
////                    double x1=atof(input);
////                    input=words[4].c_str();
////                    double y1=atof(input);
////                    input=words[5].c_str();
////                    double x2=atof(input);
////                    input=words[6].c_str();
////                    double y2=atof(input);
//                    //                bool existA=ids.exist(idA);
//                    long idTempA;
//                    //                if (!existA){
//                    ////                    idTempA=graph->addNode();
//                    ////                    ids.add(idA, idTempA);
//                    //                }else{
//                    idTempA=ids[idA]-1;
//                    graph->nodes[idTempA].originalID=idA;
////                    graph->nodes[idTempA].location=Point2d(x1,y1);
//                    //                }
//                    //                bool existB=ids.exist(idB);
//                    long idTempB;
//                    //                if (!existB){
//                    //                    idTempB=graph->addNode();
//                    //                    ids.add(idB, idTempB);
//                    //                }else{
//                    idTempB=ids[idB]-1;
//                    //                }
//                    graph->nodes[idTempB].originalID=idB;
////                    graph->nodes[idTempB].location=Point2d(x2,y2);
//                    std::vector<double> otherWeights;
//                    //                std::vector<double> otherWeights;
//                    otherWeights.clear();
//                    //                for (long j=0;j<1.size();j++){
//                    //                    otherWeights.push_back(1);
//                    //                }
//                    graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//
//}
//void TextFile::parseNCOLWithCoordinates(std::string name,Graph* graph,std::string separator,bool header)
//{
//    std::ifstream file;
//    bool abierto=open(name,file);
//    std::unordered_map<unsigned long long,long> ids;
////    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                input=words[1].c_str();
//                unsigned long long idB=stoull(input);
////                input=words[2].c_str();
////                double weight=atof(input);
////std::cout<<idB<<'\n';
//                if (idA!=idB)
//                {
//                    bool existA=true;
//                    if(ids[idA]-1==-1){
//                        existA=false;
//                    }
//                    long idTempA;
//                    if (!existA)
//                    {
//                        Node& nodeAdded=graph->addNode();
//                        idTempA=nodeAdded.id;
//                        ids[idA] =idTempA+1;
//                    }
//                    else
//                    {
//                        idTempA=ids[idA]-1;
//                    }
//                    bool existB=true;
//                    if(ids[idB]-1==-1){
//                        existB=false;
//                    }
//                    long idTempB;
//
//                    if (!existB)
//                    {
//                        Node& nodeAdded=graph->addNode();
//                        idTempB=nodeAdded.id;
//                        ids[idB]= idTempB+1;
//                    }
//                    else
//                    {
//                        idTempB=ids[idB]-1;
//                    }
//                }
//
//                std::vector<double> otherWeights;
////                graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//    abierto=open(name,file);
////    BST<long> ids;
//    //    std::vector<double> weights;
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                input=words[1].c_str();
//                unsigned long long idB=stoull(input);
//                if(idA==idB)
//                {
//                    // std::cout<<"loop in original file!!"<<'\n';
//                }
//                else
//                {
//                    input=words[2].c_str();
//                    double weight=atof(input);
//                    input=words[3].c_str();
//                    double x1=atof(input);
//                    input=words[4].c_str();
//                    double y1=atof(input);
//                    input=words[5].c_str();
//                    double x2=atof(input);
//                    input=words[6].c_str();
//                    double y2=atof(input);
//                    //                bool existA=ids.exist(idA);
//                    long idTempA;
//                    //                if (!existA){
//                    ////                    idTempA=graph->addNode();
//                    ////                    ids.add(idA, idTempA);
//                    //                }else{
//                    idTempA=ids[idA]-1;
//                    graph->nodes[idTempA].originalID=idA;
//                    graph->nodes[idTempA].location=Point2d(x1,y1);
//                    //                }
//                    //                bool existB=ids.exist(idB);
//                    long idTempB;
//                    //                if (!existB){
//                    //                    idTempB=graph->addNode();
//                    //                    ids.add(idB, idTempB);
//                    //                }else{
//                    idTempB=ids[idB]-1;
//                    //                }
//                    graph->nodes[idTempB].originalID=idB;
//                    graph->nodes[idTempB].location=Point2d(x2,y2);
//                    std::vector<double> otherWeights;
//                    //                std::vector<double> otherWeights;
//                    otherWeights.clear();
//                    //                for (long j=0;j<1.size();j++){
////                    otherWeights.push_back(1);
//                    //                }
//                    graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//                }
//
//            }
//        }
//
//        TextFile::close(file);
//    }
//
//}
//
//
//void TextFile::parseNCOLWithCoordinates(std::vector<std::string> lines,Graph* graph,std::string separator)
//{
////    bool abierto=open(name,file);
//    BST<long> ids;
////    std::vector<double> weights;
////    if (abierto)
//    {
//        std::string linea;
//
//        for(long i=0;i<lines.size();i++)
//        {
//            linea=lines[i];
////            std:cout<<linea<<'\n';
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                input=words[1].c_str();
//                unsigned long long idB=stoull(input);
////                input=words[2].c_str();
////                double weight=atof(input);
////std::cout<<idB<<'\n';
//                if (idA!=idB)
//                {
//                    bool existA=ids.exist(idA);
//                    long idTempA;
//                    if (!existA)
//                    {
//                        Node& nodeAdded=graph->addNode();
//                        idTempA=nodeAdded.id;
//                        ids.add(idA, idTempA);
//                    }
//                    else
//                    {
//                        idTempA=ids.get(idA);
//                    }
//                    bool existB=ids.exist(idB);
//                    long idTempB;
//
//                    if (!existB)
//                    {
//                        Node& nodeAdded=graph->addNode();
//                        idTempB=nodeAdded.id;
//                        ids.add(idB, idTempB);
//                    }
//                    else
//                    {
//                        idTempB=ids.get(idB);
//                    }
//                }
//
//                std::vector<double> otherWeights;
////                graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//
//            }
//        }
//
////        TextFile::close(file);
//    }
////    abierto=open(name,file);
////    BST<long> ids;
//    //    std::vector<double> weights;
////    if (abierto)
//    {
//         std::string linea;
//
//        for(long i=0;i<lines.size();i++)
//        {
//            linea=lines[i];
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                input=words[1].c_str();
//                unsigned long long idB=stoull(input);
//                if(idA==idB)
//                {
//                    // std::cout<<"loop in original file!!"<<'\n';
//                }
//                else
//                {
//                    input=words[2].c_str();
//                    double weight=atof(input);
//                    input=words[3].c_str();
//                    double x1=atof(input);
//                    input=words[4].c_str();
//                    double y1=atof(input);
//                    input=words[5].c_str();
//                    double x2=atof(input);
//                    input=words[6].c_str();
//                    double y2=atof(input);
//                    //                bool existA=ids.exist(idA);
//                    long idTempA;
//                    //                if (!existA){
//                    ////                    idTempA=graph->addNode();
//                    ////                    ids.add(idA, idTempA);
//                    //                }else{
//                    idTempA=ids.get(idA);
//                    graph->nodes[idTempA].originalID=idA;
//                    graph->nodes[idTempA].location=Point2d(x1,y1);
//                    //                }
//                    //                bool existB=ids.exist(idB);
//                    long idTempB;
//                    //                if (!existB){
//                    //                    idTempB=graph->addNode();
//                    //                    ids.add(idB, idTempB);
//                    //                }else{
//                    idTempB=ids.get(idB);
//                    //                }
//                    graph->nodes[idTempB].originalID=idB;
//                    graph->nodes[idTempB].location=Point2d(x2,y2);
//                    std::vector<double> otherWeights;
//                    //                std::vector<double> otherWeights;
//                    otherWeights.clear();
//                    //                for (long j=0;j<1.size();j++){
////                    otherWeights.push_back(1);
//                    //                }
//                    graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//                }
//
//            }
//        }
//
////        TextFile::close(file);
//    }
//
//}
//void TextFile::parseNCOLWithCoordinatesAndId(std::vector<std::string> lines,Graph* graph,std::string separator)
//{
//    //    bool abierto=open(name,file);
//    BST<long> ids;
//    //    std::vector<double> weights;
//    //    if (abierto)
//    {
//        std::string linea;
//
//        for(long i=0;i<lines.size();i++)
//        {
//            linea=lines[i];
//            //            std:cout<<linea<<'\n';
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                input=words[1].c_str();
//                unsigned long long idB=stoull(input);
//                //                input=words[2].c_str();
//                //                double weight=atof(input);
//                //std::cout<<idB<<'\n';
//                if (idA!=idB)
//                {
//                    bool existA=ids.exist(idA);
//                    long idTempA;
//                    if (!existA)
//                    {
//                        Node& nodeAdded=graph->addNode();
//                        idTempA=nodeAdded.id;
//                        ids.add(idA, idTempA);
//                    }
//                    else
//                    {
//                        idTempA=ids.get(idA);
//                    }
//                    bool existB=ids.exist(idB);
//                    long idTempB;
//
//                    if (!existB)
//                    {
//                        Node& nodeAdded=graph->addNode();
//                        idTempB=nodeAdded.id;
//                        ids.add(idB, idTempB);
//                    }
//                    else
//                    {
//                        idTempB=ids.get(idB);
//                    }
//                }
//
//                std::vector<double> otherWeights;
//                //                graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//
//            }
//        }
//
////        TextFile::close(file);
//    }
//    //    abierto=open(name,file);
//    //    BST<long> ids;
//    //    std::vector<double> weights;
//    //    if (abierto)
//    {
//        std::string linea;
//
//        for(long i=0;i<lines.size();i++)
//        {
//            linea=lines[i];
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separator);
//                const char * input;
//                input=words[0].c_str();
//                unsigned long long idA=stoull(input);
//                input=words[1].c_str();
//                unsigned long long idB=stoull(input);
//                if(idA==idB)
//                {
//                    // std::cout<<"loop in original file!!"<<'\n';
//                }
//                else
//                {
//                    input=words[2].c_str();
//                    double weight=atof(input);
//                    input=words[3].c_str();
//                    double x1=atof(input);
//                    input=words[4].c_str();
//                    double y1=atof(input);
//                    input=words[5].c_str();
//                    double x2=atof(input);
//                    input=words[6].c_str();
//                    double y2=atof(input);
//                    input=words[7].c_str();
//                    long idGraph=atol(input);
//                    graph->id=idGraph;
//                    //                bool existA=ids.exist(idA);
//                    long idTempA;
//                    //                if (!existA){
//                    ////                    idTempA=graph->addNode();
//                    ////                    ids.add(idA, idTempA);
//                    //                }else{
//                    idTempA=ids.get(idA);
//                    graph->nodes[idTempA].originalID=idA;
//                    graph->nodes[idTempA].location=Point2d(x1,y1);
//                    //                }
//                    //                bool existB=ids.exist(idB);
//                    long idTempB;
//                    //                if (!existB){
//                    //                    idTempB=graph->addNode();
//                    //                    ids.add(idB, idTempB);
//                    //                }else{
//                    idTempB=ids.get(idB);
//                    //                }
//                    graph->nodes[idTempB].originalID=idB;
//                    graph->nodes[idTempB].location=Point2d(x2,y2);
//                    std::vector<double> otherWeights;
//                    //                std::vector<double> otherWeights;
//                    otherWeights.clear();
//                    //                for (long j=0;j<1.size();j++){
//                    //                    otherWeights.push_back(1);
//                    //                }
//                    graph->addDirectedTransition(idTempA, idTempB, weight, otherWeights);
//                }
//
//            }
//        }
//
////        TextFile::close(file);
//    }
//
//}


//void TextFile::writeNCOLFile(Graph* graph,std::string fileName)
//{
//    std::vector<std::string> lines;
//    for(long i=0; i<graph->nodes.size(); i++)
//    {
//        for(long j=0; j<graph->nodes[i].transitions.size(); j++)
//        {
//            std::stringstream lineSS;
//            lineSS<<graph->nodes[i].originalID<<" "<<graph->nodes[i].transitions[j]->b->originalID<<" "<<graph->nodes[i].transitions[j]->weight;
//            std::string line=lineSS.str();
//            lines.push_back(line);
//        }
//    }
//    writeToFile(fileName, lines, false);
//}
//
//void TextFile::writeNCOLPlusCoordinatesForQTreeFile(Graph* graph,std::string fileName)
//{
//    std::vector<std::string> lines;
//    for(long i=0; i<graph->nodes.size(); i++)
//    {
//        std::stringstream lineSS1;
//        lineSS1<<graph->nodes[i].originalID<<" "<<graph->nodes[i].originalID<<" "<<0<<" "<<std::to_string(graph->nodes[i].location.x)<<" "<<std::to_string(graph->nodes[i].location.y)<<" "<<std::to_string(graph->nodes[i].location.x)<<" "<<std::to_string(graph->nodes[i].location.y)<<" h";
//        std::string line=lineSS1.str();
//        lines.push_back(line);
//        for(long j=0; j<graph->nodes[i].transitions.size(); j++)
//        {
//            std::stringstream lineSS;
//            lineSS<<graph->nodes[i].originalID<<" "<<graph->nodes[i].transitions[j]->b->originalID<<" "<<std::to_string(graph->nodes[i].transitions[j]->weight)<<" "<<std::to_string(graph->nodes[i].location.x)<<" "<<std::to_string(graph->nodes[i].location.y)<<" "<<std::to_string(graph->nodes[i].transitions[j]->b->location.x)<<" "<<std::to_string(graph->nodes[i].transitions[j]->b->location.y);
//            if(graph->nodes[i].transitions[j]->a->depthInRTree==graph->nodes[i].transitions[j]->b->depthInRTree)
//            {
//                lineSS<<" h";
//            }
//            else
//            {
//                lineSS<<" t";
//            }
//            std::string line=lineSS.str();
//            lines.push_back(line);
//        }
//    }
//    writeToFile(fileName, lines, false);
//}
//void TextFile::writeNCOLPlusCoordinatesFile(Graph* graph,std::string fileName)
//{
//    std::vector<std::string> lines;
//    for(long i=0; i<graph->nodes.size(); i++)
//    {
////        std::stringstream lineSS1;
////        lineSS1<<graph->nodes[i].originalID<<" "<<graph->nodes[i].originalID<<" "<<0<<" "<<std::to_string(graph->nodes[i].location.x)<<" "<<std::to_string(graph->nodes[i].location.y)<<" "<<std::to_string(graph->nodes[i].location.x)<<" "<<std::to_string(graph->nodes[i].location.y);
////        std::string line=lineSS1.str();
////        lines.push_back(line);
//        for(long j=0; j<graph->nodes[i].transitions.size(); j++)
//        {
//            std::stringstream lineSS;
//            lineSS<<graph->nodes[i].originalID<<" "<<graph->nodes[i].transitions[j]->b->originalID<<" "<<std::to_string(graph->nodes[i].transitions[j]->weight)<<" "<<std::to_string(graph->nodes[i].location.x)<<" "<<std::to_string(graph->nodes[i].location.y)<<" "<<std::to_string(graph->nodes[i].transitions[j]->b->location.x)<<" "<<std::to_string(graph->nodes[i].transitions[j]->b->location.y);
//            std::string line=lineSS.str();
//            lines.push_back(line);
//        }
//    }
//    writeToFile(fileName, lines, false);
//}
//
//
//void TextFile::writeNCOLFileAndSeparateCoordinatesFile(Graph* graph,std::string fileNameNCOL,std::string fileNameCoordinates,std::string separatorNCOL,std::string separatorCoordinates){
//    std::vector<std::string> lines;
//    for(long i=0; i<graph->nodes.size(); i++)
//    {
//        for(long j=0; j<graph->nodes[i].transitions.size(); j++)
//        {
//            std::stringstream lineSS;
//            lineSS<<graph->nodes[i].originalID<<separatorNCOL<<graph->nodes[i].transitions[j]->b->originalID<<separatorNCOL<<graph->nodes[i].transitions[j]->weight;
//            std::string line=lineSS.str();
//            lines.push_back(line);
//        }
//    }
//    writeToFile(fileNameNCOL, lines, false);
//
//
//    lines.clear();
//    for(long i=0; i<graph->nodes.size(); i++)
//    {
//
//            std::stringstream lineSS;
//            lineSS<<graph->nodes[i].originalID<<separatorCoordinates<<std::to_string(graph->nodes[i].location.x)<<separatorCoordinates<<std::to_string(graph->nodes[i].location.y);
//            std::string line=lineSS.str();
//            lines.push_back(line);
//
//    }
//    writeToFile(fileNameCoordinates, lines, false);
//}
//
//
//
//
//void TextFile::writeNCOLPlusCoordinatesFile_PlusNamesAndHierarchicalLevel(Graph* graph,std::string fileName)
//{
//    std::vector<std::string> lines;
//    for(long i=0; i<graph->nodes.size(); i++)
//    {
//        for(long j=0; j<graph->nodes[i].transitions.size(); j++)
//        {
//            std::stringstream lineSS;
//            lineSS<<graph->nodes[i].originalID<<" "<<graph->nodes[i].transitions[j]->b->originalID<<" "<<std::to_string(graph->nodes[i].transitions[j]->weight)<<" "<<std::to_string(graph->nodes[i].location.x)<<" "<<std::to_string(graph->nodes[i].location.y)<<" "<<std::to_string(graph->nodes[i].transitions[j]->b->location.x)<<" "<<std::to_string(graph->nodes[i].transitions[j]->b->location.y)<<" \""<<graph->nodes[i].transitions[j]->nameRoad<<"\" "<<graph->nodes[i].transitions[j]->levelHierarchyRoad;
//            std::string line=lineSS.str();
//            lines.push_back(line);
//        }
//    }
//    writeToFile(fileName, lines, false);
//}
//void TextFile::writeNCOLPlusCoordinatesFile_PlusIdTransitions(Graph* graph,std::string fileName)
//{
//    std::vector<std::string> lines;
//    for(long i=0; i<graph->nodes.size(); i++)
//    {
//        for(long j=0; j<graph->nodes[i].transitions.size(); j++)
//        {
//            std::stringstream lineSS;
//            lineSS<<graph->nodes[i].originalID<<" "<<graph->nodes[i].transitions[j]->b->originalID<<" "<<std::to_string(graph->nodes[i].transitions[j]->weight)<<" "<<std::to_string(graph->nodes[i].location.x)<<" "<<std::to_string(graph->nodes[i].location.y)<<" "<<std::to_string(graph->nodes[i].transitions[j]->b->location.x)<<" "<<std::to_string(graph->nodes[i].transitions[j]->b->location.y)<<" "<<graph->nodes[i].transitions[j]->originalID;
//            std::string line=lineSS.str();
//            lines.push_back(line);
//        }
//    }
//    writeToFile(fileName, lines, false);
//}

std::vector<std::string> TextFile::extractWords(std::string line,std::string separator)
{
    std::vector<std::string> words;
    long position=line.find(separator);
    while (position>=0)
    {
        std::string word=line.substr(0,position);
        words.push_back(word);
        line=line.substr(position+separator.length());
        position=line.find(separator);
    }
    words.push_back(line);
    return words;
}



//string TextFile::subStr(int comienzo, int final){
//    return line.substr(k,i)
//}
//void TextFile::parseDXF3d(string name,ArrayList<Linea> * lineas3d){
////    ArrayList<Linea> lineas3d;
//    bool abierto=open(name,file);
//    if (abierto){
////        cout<<"dentro de leer";
//        string linea;
//        string capa;
//        while(!file.eof()){
//            linea=TextFile::getLine(file);
////            cout<<linea.substr(0,4);
//            if (linea.substr(0,4)=="LINE"){
//                for(int i=0;i<3;i++){
//                    TextFile::getLine(file);
//                }
//                capa=TextFile::getLine(file);
//                TextFile::getLine(file);
//                Punto puntoA;
//                linea=TextFile::getLine(file);
//                const char * input;
//                input=linea.c_str();
//
//                puntoA.x=atof(input);
//
//                TextFile::getLine(file);
//                linea=TextFile::getLine(file);
//                input=linea.c_str();
//
//                puntoA.y=atof(input);
//
//                TextFile::getLine(file);
//                linea=TextFile::getLine(file);
//                input=linea.c_str();
//
//                puntoA.z=-atof(input);
//
//                Punto puntoB;
//
//                TextFile::getLine(file);
//                linea=TextFile::getLine(file);
//                input=linea.c_str();
//
//                puntoB.x=atof(input);
//
//                TextFile::getLine(file);
//                linea=TextFile::getLine(file);
//                input=linea.c_str();
//
//                puntoB.y=atof(input);
//
//                TextFile::getLine(file);
//                linea=TextFile::getLine(file);
//                input=linea.c_str();
//
//                puntoB.z=-atof(input);
////                cout<<" linea ";
////                cout<<" A.x ";
////                cout<<puntoA.x;
////                cout<<" A.y ";
////                cout<<puntoA.y;
////                cout<<" A.z ";
////                cout<<puntoA.z;
////                cout<<" B.x ";
////                cout<<puntoB.x;
////                cout<<" B.y ";
////                cout<<puntoB.y;
////                cout<<" B.z ";
////                cout<<puntoB.z;
//                Linea linea3d;
//                linea3d.set(puntoA,puntoB);
//                if (capa.substr(0,5)=="VERDE"){
////                    cout<<"verde -";
////                    cout<<capa.substr(6,capa.length());
//                    input=capa.substr(6,capa.length()).c_str();
//                    linea3d.R=0;
//                    linea3d.G=atoi(input);
//                    linea3d.B=0;
//                }
//
//                if (capa.substr(0,4)=="ROJO"){
//                    input=capa.substr(5,capa.length()).c_str();
//                    linea3d.R=atoi(input);
//                    linea3d.G=0;
//                    linea3d.B=0;
//                }
//
//                if (capa.substr(0,4)=="AZUL"){
////                    cout<<"azul -";
////                    cout<<capa.substr(5,capa.length());
//                    input=capa.substr(5,capa.length()).c_str();
//                    linea3d.R=0;
//                    linea3d.G=0;
//                    linea3d.B=atoi(input);
//                }
//                (*lineas3d).add(linea3d);
//
//
//            }
//
//        }
//    }
////    return lineas3d;
//    TextFile::close(file);
//}

void TextFile::close(std::ifstream &file)
{
    file.close();
}

//TextFile::~ArchivoTexto()
//{
//    //dtor
//}
std::vector<std::vector<std::string>> TextFile::importFileClusters(std::string name,std::string separator,long minClusterSize)
{
    std::cout<<"name of clusters file : "<<name<<'\n';
    std::vector<std::vector<std::string>> ncolsTextLines;
    std::ifstream file;
    bool abierto=open(name,file);
    std::vector<double> values;
    if (abierto)
    {
//        cout<<"dentro de leer";
        std::string linea;
        linea=TextFile::getLine(file);//skipping the names of variables
        long currentCluster=1;
        long sizeClusterPrev=0;
        std::vector<std::string> lines;
        bool changeCluster=false;
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
//                const char * input;
//                input=linea.c_str();
//                double value=atof(input);
//                values.push_back(value);
                std::vector<std::string> words=extractWords(linea,separator);
                const char * input;
                input=words[0].c_str();
                long numCluster=atol(input);
                if(numCluster!=currentCluster)
                {
                    changeCluster=true;
                    currentCluster=numCluster;
                }
                input=words[1].c_str();
                long sizeCluster=atol(input);
                if(sizeClusterPrev==0)
                {
                    sizeClusterPrev=sizeCluster;

                }
                std::stringstream restLineSS;
//                const char * input;
                input=words[2].c_str();
                unsigned long long idA=std::stoull(input);
                input=words[3].c_str();
                unsigned long long idB=std::stoull(input);
                Point2d pointA=Configuration::getCoordinate(idA);
                Point2d pointB=Configuration::getCoordinate(idB);
                for(int i=2; i<words.size()-1; i++)
                {
                    restLineSS<<words[i]<<separator;
                }
                restLineSS<<words[words.size()-1];
                restLineSS<<separator<<pointA.x<<separator<<pointA.y<<separator<<pointB.x<<separator<<pointB.y;
                restLineSS<<separator<<words[0];
                std::string restLine=restLineSS.str();
                if(changeCluster)
                {
                    changeCluster=false;
                    if(sizeClusterPrev>minClusterSize)
                    {
                        ncolsTextLines.push_back(lines);
                    }
                    lines.clear();
                    sizeClusterPrev=sizeCluster;
                }
                lines.push_back(restLine);


            }
        }

        TextFile::close(file);
    }
    return (ncolsTextLines);

}







void TextFile::loadPointLocationsAndValue(std::string name,std::vector<Point2d> &points,std::vector<double> &values,bool header,std::string separator){
//    std::cout<<"name of clusters file : "<<name<<'\n';
    std::vector<std::vector<std::string>> ncolsTextLines;
    std::ifstream file;
    bool abierto=open(name,file);
//    std::vector<double> values;
    if (abierto)
    {
        //        cout<<"dentro de leer";
        std::string linea;
        if(header){
            linea=TextFile::getLine(file);//skipping the names of variables
        }
//        long currentCluster=1;
//        long sizeClusterPrev=0;
        std::vector<std::string> lines;
//        bool changeCluster=false;
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
                //                const char * input;
                //                input=linea.c_str();
                //                double value=atof(input);
                //                values.push_back(value);
                std::vector<std::string> words=extractWords(linea,separator);
                const char * input;
                input=words[0].c_str();
                double x=atof(input);
                input=words[1].c_str();
                double y=atof(input);
                Point2d point(x,y);
                points.push_back(point);
                input=words[2].c_str();
                double value=atof(input);
                values.push_back(value);

            }
        }

        TextFile::close(file);
    }
//    return (ncolsTextLines);
}





void TextFile::loadData(std::vector<std::string> &ids,std::vector<std::string> &columnNames,std::vector<std::vector<double> > &values,std::string nameOfFile,std::string separator,bool header){
    std::ifstream file;
    bool abierto=open(nameOfFile,file);

    if (abierto)
    {

        std::string linea;
        if(header)
        {
            linea=TextFile::getLine(file);//skipping the names of variables
            if (linea.length()>0)
            {
                std::vector<std::string> words=extractWords(linea, separator);
                const char * input;

                for(long i=1;i<words.size();i++){
                    input=words[i].c_str();

                    columnNames.push_back(input);
                }

                values.resize(columnNames.size()-1,std::vector<double>());


            }
        }
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
                std::vector<std::string> words=extractWords(linea, separator);
                const char * input;
                input=words[0].c_str();
                ids.push_back(input);
                std::vector<double> resultTemp;
                for(long i=1;i<words.size();i++){
                    input=words[i].c_str();
                    double value=atof(input);
                    values[i-1].push_back(value);
                }




            }
        }

        TextFile::close(file);
    }
}








std::vector<std::string> TextFile::getLineString(Grafo* G,std::string fileName,bool append){
    std::vector<std::string> lines;
    lines.reserve(G->links.size());
    for(long i=0;i<G->links.size();i++){
        std::stringstream ss;
        ss<<"LINESTRING("<<std::to_string(G->links[i]->A()->location.x)<<" "<<std::to_string(G->links[i]->A()->location.y)<<","<<std::to_string(G->links[i]->B()->location.x)<<" "<<std::to_string(G->links[i]->B()->location.y)<<")";
        lines.push_back(ss.str());
    }
    return lines;
    // TextFile::writeToFile(fileName, lines, append);
}

void TextFile::createLineString(Grafo* G,std::string fileName,bool append){
    std::vector<std::string> lines;
    lines.reserve(G->links.size());
    for(long i=0;i<G->links.size();i++){
        std::stringstream ss;
        ss<<"LINESTRING("<<std::to_string(G->links[i]->A()->location.x)<<" "<<std::to_string(G->links[i]->A()->location.y)<<","<<std::to_string(G->links[i]->B()->location.x)<<" "<<std::to_string(G->links[i]->B()->location.y)<<")";
        lines.push_back(ss.str());
    }
    // return lines;
    TextFile::writeToFile(fileName, lines, append);
}

void TextFile::parseNCOLandSeparateCoordinatesFile(Grafo* graph,bool directional,std::string nameNCOLFile,std::string nameCoordinatesFile,std::string separatorNCOL,std::string separatorCoordinates,bool header){
    std::ifstream file;
    graph->bidirectional=!directional;
    bool abierto=open(nameCoordinatesFile,file);
    std::unordered_map<std::string,long> ids;
    if (abierto)
    {
        std::string linea;
        if(header)
        {
            linea=TextFile::getLine(file);//skipping the names of variables
        }
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
                std::vector<std::string> words=extractWords(linea, separatorCoordinates);
                const char * input;
                //                input=words[0].c_str();
                std::string idA=words[0];
                input=words[1].c_str();
                double x1=atof(input);
                input=words[2].c_str();
                double y1=atof(input);
//                bool existA=true;
//                if(ids[idA]-1==-1){
//                    existA=false;
//                }
//                long idTempA;
//                if (!existA)
//                {
                    Nodo* nodeAdded=graph->addNode(idA,x1,y1);

                    long idTempA=nodeAdded->id;
                    ids[idA] =idTempA+1;
//                }
//                else
//                {
//                    idTempA=ids[idA]-1;
//                }
            }
        }
        TextFile::close(file);
    }

    abierto=open(nameNCOLFile,file);
    if (abierto)
    {
        std::string linea;
        if(header)
        {
            linea=TextFile::getLine(file);//skipping the names of variables
        }
//        long idTransitionsAutomatic=0;
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
                std::vector<std::string> words=extractWords(linea, separatorNCOL);
                const char * input;
                //                input=words[0].c_str();
                std::string idA=words[0];
                //                input=words[1].c_str();
                std::string idB=words[1];
                if(idA==idB)
                {
                }
                else
                {
                    input=words[2].c_str();
                    double weight=std::stod(input);
                    //                    long idTransition=0;
                    if(words.size()<4){
                        long idTempA;
                        idTempA=ids[idA]-1;
                        long idTempB;
                        idTempB=ids[idB]-1;
                        if(idTempA!=-1&&idTempB!=-1){
                            std::vector<double> otherWeights;
                            otherWeights.clear();
                            Link linkTemp;
                            linkTemp.setA(graph->nodes[idTempA]);
                            linkTemp.setB(graph->nodes[idTempB]);
                            linkTemp.weight=weight;
                            //                    linkTemp.originalID=idTransition;
                            graph->addLink(linkTemp);
                        }
                        //                        input=words[3].c_str();
                        //                        idTransition=stol(input);
                    }else{
                        long idTempA;
                        idTempA=ids[idA]-1;
                        long idTempB;
                        idTempB=ids[idB]-1;
                        if(idTempA!=-1&&idTempB!=-1){
                            std::vector<double> otherWeights;
                            otherWeights.clear();
                            Link linkTemp;
                            linkTemp.setA(graph->nodes[idTempA]);
                            linkTemp.setB(graph->nodes[idTempB]);
                            linkTemp.weight=weight;
                            linkTemp.identifier=words[3];
                            graph->addLink(linkTemp);
                        }
                        //                        idTransition=idTransitionsAutomatic;
                        //                        idTransitionsAutomatic++;
                    }

                }
            }
        }
        TextFile::close(file);
        graph->finishedAddingNodes();
        std::cout<<"Graph imported. number of links "<<graph->links.size()<<'\n';
    }
}




void TextFile::parseNCOLandSeparateCoordinatesFile(Grafo* graph,bool directional,std::string nameNCOLFile,std::string nameCoordinatesFile,std::string separatorNCOL,std::string separatorCoordinates,bool header,bool bypassChekingNodes){
    std::ifstream file;
    graph->bidirectional=!directional;
    bool abierto=open(nameCoordinatesFile,file);
    std::unordered_map<std::string,long> ids;
    if (abierto)
    {
        std::string linea;
        if(header)
        {
            linea=TextFile::getLine(file);//skipping the names of variables
        }
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
                std::vector<std::string> words=extractWords(linea, separatorCoordinates);
                const char * input;
                //                input=words[0].c_str();
                std::string idA=words[0];
                input=words[1].c_str();
                double x1=atof(input);
                input=words[2].c_str();
                double y1=atof(input);
                //                bool existA=true;
                //                if(ids[idA]-1==-1){
                //                    existA=false;
                //                }
                //                long idTempA;
                //                if (!existA)
                //                {
                Nodo* nodeAdded=graph->addNode(idA,x1,y1,bypassChekingNodes);

                long idTempA=nodeAdded->id;
                ids[idA] =idTempA+1;
                //                }
                //                else
                //                {
                //                    idTempA=ids[idA]-1;
                //                }
            }
        }
        TextFile::close(file);
    }

    abierto=open(nameNCOLFile,file);
    if (abierto)
    {
        std::string linea;
        if(header)
        {
            linea=TextFile::getLine(file);//skipping the names of variables
        }
        //        long idTransitionsAutomatic=0;
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
                std::vector<std::string> words=extractWords(linea, separatorNCOL);
                const char * input;
                //                input=words[0].c_str();
                std::string idA=words[0];
                //                input=words[1].c_str();
                std::string idB=words[1];
                if(idA==idB)
                {
                }
                else
                {
                    input=words[2].c_str();
                    double weight=std::stod(input);
                    //                    long idTransition=0;
                    if(words.size()<4){
                        long idTempA;
                        idTempA=ids[idA]-1;
                        long idTempB;
                        idTempB=ids[idB]-1;
                        if(idTempA!=-1&&idTempB!=-1){
                            std::vector<double> otherWeights;
                            otherWeights.clear();
                            Link linkTemp;
                            linkTemp.setA(graph->nodes[idTempA]);
                            linkTemp.setB(graph->nodes[idTempB]);
                            linkTemp.weight=weight;
                            //                    linkTemp.originalID=idTransition;
                            graph->addLink(linkTemp);
                        }
                        //                        input=words[3].c_str();
                        //                        idTransition=stol(input);
                    }else{
                        long idTempA;
                        idTempA=ids[idA]-1;
                        long idTempB;
                        idTempB=ids[idB]-1;
                        if(idTempA!=-1&&idTempB!=-1){
                            std::vector<double> otherWeights;
                            otherWeights.clear();
                            Link linkTemp;
                            linkTemp.setA(graph->nodes[idTempA]);
                            linkTemp.setB(graph->nodes[idTempB]);
                            linkTemp.weight=weight;
                            linkTemp.identifier=words[3];
                            graph->addLink(linkTemp);
                        }
                        //                        idTransition=idTransitionsAutomatic;
                        //                        idTransitionsAutomatic++;
                    }

                }
            }
        }
        TextFile::close(file);
        graph->finishedAddingNodes();
        std::cout<<"Graph imported. number of links "<<graph->links.size()<<'\n';
    }
}









//void TextFile::parseNCOLandSeparateCoordinatesFile(DualExtendedGraph* deg,bool directional,std::string nameNCOLFile,std::string nameCoordinatesFile,std::string separatorNCOL,std::string separatorCoordinates,bool header){
//    std::ifstream file;
//    deg->getPrimalGraph()->bidirectional=!directional;
//    bool abierto=open(nameCoordinatesFile,file);
//    std::unordered_map<std::string,long> ids;
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separatorCoordinates);
//                const char * input;
////                input=words[0].c_str();
//                std::string idA=words[0];
//                input=words[1].c_str();
//                double x1=atof(input);
//                input=words[2].c_str();
//                double y1=atof(input);
////                bool existA=true;
////                if(ids[idA]-1==-1){
////                    existA=false;
////                }
////                long idTempA;
////                if (!existA)
////                {
//                    Nodo* nodeAdded=deg->getPrimalGraph()->addNode(idA,x1,y1);
//
//                    long idTempA=nodeAdded->id;
//                    ids[idA] =idTempA+1;
////                }
////                else
////                {
////                    idTempA=ids[idA]-1;
////                }
//            }
//        }
//        TextFile::close(file);
//    }
//
//    abierto=open(nameNCOLFile,file);
//    if (abierto)
//    {
//        std::string linea;
//        if(header)
//        {
//            linea=TextFile::getLine(file);//skipping the names of variables
//        }
////        long idTransitionsAutomatic=0;
//        while(!file.eof())
//        {
//            linea=TextFile::getLine(file);
//            if (linea.length()>0)
//            {
//                std::vector<std::string> words=extractWords(linea, separatorNCOL);
//                const char * input;
////                input=words[0].c_str();
//                std::string idA=words[0];
////                input=words[1].c_str();
//                std::string idB=words[1];
//                if(idA==idB)
//                {
//                }
//                else
//                {
//                    input=words[2].c_str();
//                    double weight=std::stod(input);
////                    long idTransition=0;
//                    if(words.size()<4){
//                        long idTempA;
//                        idTempA=ids[idA]-1;
//                        long idTempB;
//                        idTempB=ids[idB]-1;
//                        Link linkTemp;
//                        linkTemp.a=deg->getPrimalGraph()->nodes[idTempA];
//                        linkTemp.b=deg->getPrimalGraph()->nodes[idTempB];
//                        linkTemp.weight=weight;
//
//                        deg->getPrimalGraph()->addLink(linkTemp);
//                    }else{
//                        long idTempA;
//                        idTempA=ids[idA]-1;
//                        long idTempB;
//                        idTempB=ids[idB]-1;
//                        Link linkTemp;
//                        linkTemp.a=deg->getPrimalGraph()->nodes[idTempA];
//                        linkTemp.b=deg->getPrimalGraph()->nodes[idTempB];
//                        linkTemp.weight=weight;
//                        linkTemp.originalID=words[3];
//                        deg->getPrimalGraph()->addLink(linkTemp);
//                    }
//
//                }
//            }
//        }
//        TextFile::close(file);
//    }
//    deg->getPrimalGraph()->finishedAddingNodes();
//}


void TextFile::saveCoordinates(Grafo* G,std::string nameFile){
    std::vector<std::string> lines;
    auto coordinates=Grafo::getCoordinates(G);
    std::vector<long> ids=std::get<0>(coordinates);
    std::vector<double> xs=std::get<1>(coordinates);
    std::vector<double> ys=std::get<2>(coordinates);
    lines.reserve(ids.size()+1);
    lines.push_back("id x y");
    for(long i=0;i<ids.size();i++){
        std::stringstream ss;
        ss<<std::to_string(ids[i])<<" "<<std::to_string(xs[i])<<" "<<std::to_string(ys[i]);
        lines.push_back(ss.str());
    }
    TextFile::writeToFile(nameFile, lines, false);
}

void TextFile::saveNCOL(Grafo* G,std::string nameFile){
    std::vector<std::string> lines;
    auto ncol=Grafo::getNCOL(G);
    std::vector<long> idAs=std::get<0>(ncol);
    std::vector<long> idBs=std::get<1>(ncol);
    std::vector<double> weights=std::get<2>(ncol);
    lines.reserve(idAs.size()+1);
    lines.push_back("idA idB weight");
    for(long i=0;i<idAs.size();i++){
        std::stringstream ss;
        ss<<std::to_string(idAs[i])<<" "<<std::to_string(idBs[i])<<" "<<std::to_string(weights[i]);
        lines.push_back(ss.str());
    }
    TextFile::writeToFile(nameFile, lines, false);
}
