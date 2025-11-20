#ifndef BST_H
#define BST_H
#include <iostream>
#include "Node.h"
#include <queue>

using namespace std;

template<class T>
class TreeNode
{
private:
public:
    unsigned long long longData;
    T object;
    long id;
    long Llink;
    long Rlink;
};

template<class T>
class BST
{
public:
    BST();
    ~BST();
    void add(unsigned long long id,T object);
    std::vector<T> getAll();
    void deleteNode(unsigned long long id);
    bool exist(unsigned long long id);
    T get(unsigned long long id);
    long size();
//    void clearMemory();
    void deleteAll();
private:
    // std::vector<TreeNode<T>> addLater;
    std::vector<TreeNode<T> > treeNodes;
    long Node_Number;
    long top;
    long PopCount;
    long DeleteData;
    // TreeNode<T> *STACK;
    std::queue<TreeNode<T> > STACK;
    long root;
    long ptr;
    long current;
    long pre;
    //    TreeNode<T> *clear;
    long FindFather(unsigned long long num);
    long SearchNumber(unsigned long long num);
    void push(long temp);
    T pop();
    long findLargestSonOfLeftSide(long temp);
    long findSmallestSonOfRightSide(long temp);
    
    
};



template<class T>
BST<T>::BST()
{
    root=-1;
    Node_Number=0;
    top=-1;
    PopCount=0;
}

template<class T>
BST<T>::~BST()
{
    //    current=root;
    if (Node_Number>0)
    {
//        clearMemory();
        deleteAll();
    }
    
   
    
    //    cout<<"The memory is released"<<endl;
    //    system("Pause");
}
template<class T>
void BST<T>::add(unsigned long long id,T object)
{
    Node_Number++;
    //    ptr=new TreeNode<T>;
    TreeNode<T> ptr;
    ptr.Llink=-1;
    ptr.Rlink=-1;
    ptr.longData=id;
    long indexOfObject=treeNodes.size();
    ptr.id=treeNodes.size();
    ptr.object=object;
    
    if(root==-1)         //For now the tree is still empty so the new node will be root!
    {
        root=0;
        treeNodes.push_back(ptr);
    }
    else      //The tree is not empty!
    {
        long indexPossibleNode=SearchNumber(ptr.longData);
        if(indexPossibleNode!=-1)         //Binary Search tree can not have the same data!
        {
            //                cout<<"Error! You have the same longeger!!"<<endl;
            //                SearchNumber(ptr->longData)->node=node;
            Node_Number--;
            treeNodes[indexPossibleNode].object=object;
            return;        //Jump to the menu!
        }
        treeNodes.push_back(ptr);
        current=root;
        while(current!=-1)
        {
            if(ptr.longData<treeNodes[current].longData)     //Compare two longeger. If node of ptr is less than node of currnet then put
            {
                //the node of ptr to left subtree.
                if(treeNodes[current].Llink==-1)     //Consider the node is a leaf!
                {
                    treeNodes[current].Llink=indexOfObject;
//                    ptr.Llink=NULL;
//                    ptr.Rlink=NULL;
                    current=-1;
                }
                else
                {
                    current=treeNodes[current].Llink;  //Move to the next left child
                }
            }
            else      //If node of ptr is bigger than node of currnet then put the node of ptr to right subtree.
            {
                if(treeNodes[current].Rlink==-1)     //Consider the node is a leaf!
                {
                    treeNodes[current].Rlink=indexOfObject;
//                    ptr->Llink=NULL;
//                    ptr->Rlink=NULL;
                    current=-1;
                }
                else
                {
                    current=treeNodes[current].Rlink;  //Move to the next right child
                }
            }
            
        }
    }
}
template<class T>
void BST<T>::deleteNode(unsigned long long id)
{
    if(root==-1)
    {
        cout<<"The tree is empty!"<<endl;
    }
    //    cout<<"Which one do you want delete? :"<<endl;
    DeleteData=id;
    if(SearchNumber(DeleteData)==-1)
    {
        //        cout<<"Error!! Can not find this longeger!!"<<endl;
        return;
    }
    else
    {
        current=SearchNumber(DeleteData);        //Find the longeger
    }
//    TreeNode<T> *temp;
    long temp;
    if(current==root&&Node_Number==1)     //Consider the delete longeger is root node and it is only one node in tree!
    {
        //        clear=current;
        root=-1;
        //        delete clear;
        current=-1;
        Node_Number--;
        return;
    }
    else if(current==root)      //Consider the delete longeger is root node and it is not only one node in tree!
    {
        if(treeNodes[root].Llink==-1)     //Consider it is no left subtree!
        {
            //            clear=root;
            root=treeNodes[root].Rlink;
            //            delete clear;
            Node_Number--;
            return;
        }
        else if(treeNodes[root].Rlink==-1)      //Consider it is no right subtree!
        {
            //            clear=root;
            root=treeNodes[root].Llink;
            //            delete clear;
            Node_Number--;
            return;
        }
        else      //If the root have left subtree and right subtree!
        {
            temp=current;
            temp=treeNodes[temp].Llink;    //Move to the left child! Beacuse I want to choose the biggest node of left subtree to replace the node of root!
            if(treeNodes[temp].Rlink==-1)     //In the left subtree. The biggest node always at right node! Now Consider if the left subtree have no right node!
            {
                treeNodes[temp].Rlink=treeNodes[root].Rlink;
                //                clear=root;
                root=temp;
                //                delete clear;
                Node_Number--;
                return;
            }
            else
            {
                while(treeNodes[temp].Rlink!=-1)     //Last right node is the bigest node in left subtree of root!
                {
                    temp=treeNodes[temp].Rlink;        //Keep move to the right node!
                }
                pre=FindFather(treeNodes[temp].longData);    //Find this node's parent
                if(treeNodes[temp].Llink==-1)     //Consider two case. if temp node have no leftchild then his parent doesn't need to link any node!
                {
                    treeNodes[pre].Rlink=-1;
                }
                else
                {
                    treeNodes[pre].Rlink=treeNodes[temp].Llink;    //The other case is if temp node have leftchild then his parent need to link leftchild!
                }
                treeNodes[temp].Llink=treeNodes[root].Llink;    //Replace the delete node!
                treeNodes[temp].Rlink=treeNodes[root].Rlink;
                //                clear=root;
                root=temp;
                //                delete clear;    //Delete
                Node_Number--;
                return;
            }
        }
    }
    
    if(treeNodes[current].Llink==-1&&treeNodes[current].Rlink==-1)         //if the node we want to delete is a leaf
    {
        pre=FindFather(treeNodes[current].longData);    //Find parent of delete node
        if(treeNodes[pre].longData>treeNodes[current].longData)     //After remove delete node. The parent node will link to NULL.
        {
            treeNodes[pre].Llink=-1;
            //            clear=current;
            //            delete clear;
            current=-1;
            Node_Number--;
            return;
        }
        else
        {
            treeNodes[pre].Rlink=-1;
            //            clear=current;
            //            delete clear;
            current=-1;
            Node_Number--;
            return;
        }
    }
    pre=FindFather(DeleteData);
    if(treeNodes[current].Llink==-1)
    {
        if((treeNodes[(treeNodes[current].Rlink)].Llink==-1)&&(treeNodes[(treeNodes[current].Rlink)].Rlink==-1))     //if the node we want to delete is only have one child node
        {
            //            clear=current;
            if(treeNodes[pre].longData>treeNodes[current].longData)     //parent node will link to the child of delete node
            {
                current=treeNodes[current].Rlink;
                treeNodes[pre].Llink=current;
                //                delete clear;
                
                Node_Number--;
                return;
            }
            else      //parent node will link to the child of delete node
            {
                current=treeNodes[current].Rlink;
                treeNodes[pre].Rlink=current;
                //                delete clear;
                Node_Number--;
                return;
            }
        }
    }
    else if(treeNodes[current].Rlink==-1)
    {
        if(treeNodes[(treeNodes[current].Llink)].Llink==-1&&treeNodes[(treeNodes[current].Llink)].Rlink==-1)     //if the node we want to delete is only have one child node
        {
            //            clear=current;
            if(treeNodes[pre].longData>treeNodes[current].longData)     //parent node will link to the child of delete node
            {
                current=treeNodes[current].Llink;
                treeNodes[pre].Llink=current;
                //                delete clear;
                Node_Number--;
                return;
            }
            else      //parent node will link to the child of delete node
            {
                current=treeNodes[current].Llink;
                treeNodes[pre].Rlink=current;
                //                delete clear;
                Node_Number--;
                return;
            }
        }
    }
    
    //    temp=current;
    //    temp=temp->Llink;
    //    if(temp->Rlink==NULL){
    //        pre=FindFather(current->longData);
    //        temp->Rlink=current->Rlink;
    //        if(temp->longData<pre->longData){
    //            pre->Llink=temp;
    //        }else{
    //            pre->Rlink=temp;
    //        }
    //        clear=current;
    //        delete clear;
    //        Node_Number--;
    //    }else{
    //        while(temp->Rlink!=NULL){
    //            temp=temp->Rlink;
    //        }
    //        pre=FindFather(temp->longData);
    //        if(temp->Llink==NULL){
    //            pre->Rlink=NULL;
    //        }else{
    //            pre->Rlink=temp->Llink;
    //        }
    //        temp->Llink=current->Llink;
    //        temp->Rlink=current->Rlink;
    //        pre=FindFather(current->longData);
    //        if(temp->longData<pre->longData){
    //            pre->Llink=temp;
    //        }else{
    //            pre->Rlink=temp;
    //        }
    //        clear=current;
    //        delete clear;
    //        Node_Number--;
    //    }
    if (treeNodes[current].Llink!=-1)
    {
        temp=findLargestSonOfLeftSide(current);
        if (temp!=treeNodes[current].Llink)
        {
            if (treeNodes[temp].Llink!=-1)
            {
                long pre1=FindFather(treeNodes[temp].longData);
                long pre2=FindFather(treeNodes[current].longData);
                treeNodes[pre1].Rlink=treeNodes[temp].Llink;
                treeNodes[temp].Llink=treeNodes[current].Llink;
                treeNodes[temp].Rlink=treeNodes[current].Rlink;
                if(treeNodes[pre2].Rlink==current)
                {
                    treeNodes[pre2].Rlink=temp;
                }
                else
                {
                    treeNodes[pre2].Llink=temp;
                }
                //                delete current;
                current=-1;
                Node_Number--;
            }
            
        }
        else
        {
            long pre2=FindFather(treeNodes[current].longData);
            treeNodes[temp].Rlink=treeNodes[current].Rlink;
            if(treeNodes[pre2].Rlink==current)
            {
                treeNodes[pre2].Rlink=temp;
            }
            else
            {
                treeNodes[pre2].Llink=temp;
            }
            //            delete current;
            current=-1;
            Node_Number--;
        }
    }
    else if (treeNodes[current].Rlink!=-1)
    {
        temp=findSmallestSonOfRightSide(current);
        if (temp!=treeNodes[current].Rlink)
        {
            if (treeNodes[temp].Llink!=-1)
            {
                long pre1=FindFather(treeNodes[temp].longData);
                long pre2=FindFather(treeNodes[current].longData);
                treeNodes[pre1].Llink=treeNodes[temp].Rlink;
                treeNodes[temp].Rlink=treeNodes[current].Rlink;
                treeNodes[temp].Llink=treeNodes[current].Llink;
                if(treeNodes[pre2].Rlink==current)
                {
                    treeNodes[pre2].Rlink=temp;
                }
                else
                {
                    treeNodes[pre2].Llink=temp;
                }
                //                delete current;
                current=-1;
                Node_Number--;
            }
            
        }
        else
        {
            long pre2=FindFather(treeNodes[current].longData);
            treeNodes[temp].Llink=treeNodes[current].Llink;
            if(treeNodes[pre2].Rlink==current)
            {
                treeNodes[pre2].Rlink=temp;
            }
            else
            {
                treeNodes[pre2].Llink=temp;
            }
            //            delete current;
            current=-1;
            Node_Number--;
        }
    }
}
template<class T>
std::vector<T> BST<T>::getAll()
{
    std::vector<T> objects;
    if(root==-1)
    {
        return objects;
    }
//    std::vector<TreeNode
//    STACK=new TreeNode<T>[Node_Number];    //Create a structure array as a stack!
//    long popCount;
//    popCount=0;
    current=root;
    
    
    while(1)     // Non-Recursive of inorder .The order is follow this rule. parent,leftchild,rightchild
    {
        if(current!=-1)
        {
            push(current);
            current=treeNodes[current].Llink;
        }
        else
        {
            
            current=STACK.front().Rlink;
            objects.push_back(pop());
            PopCount++;
        }
        if(STACK.empty()&&current==-1)
        {
            //            cout<<endl;
            std::queue<TreeNode<T> > empty;
            std::swap( STACK, empty );
            break;
        }
    }
//    delete []STACK;
    return objects;
}
template<class T>
T BST<T>::get(unsigned long long id)
{
    unsigned long long num=id;
    //    cout<<"Please Enter the longeger"<<endl;
    //    cin>>num;
    long element=SearchNumber(num);
    if(element!=-1)
    {
        return treeNodes[element].object;
    }
    else
    {
        return NULL;
    }
}

template<class T>
bool BST<T>::exist(unsigned long long id)
{
    unsigned long long num=id;
    long element=SearchNumber(num);
    if(element!=-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
long BST<T>::SearchNumber(unsigned long long num)     //Search a number
{
    long temp;
    temp=root;
    while(temp!=-1)
    {
        if(treeNodes[temp].longData==num)
        {
            return temp;
        }
        else if(treeNodes[temp].longData<num)
        {
            temp=treeNodes[temp].Rlink;
        }
        else
        {
            temp=treeNodes[temp].Llink;
        }
    }
    return temp;
}
template<class T>
long BST<T>::findLargestSonOfLeftSide(long temp)     //Search a number
{
    //    TreeNode<T> *temp;
    //    temp=root;
    //    if(temp->Llink!=NULL){
    temp=treeNodes[temp].Llink;
    while(treeNodes[temp].Rlink!=-1)
    {
        temp=treeNodes[temp].Rlink;
        //            if(temp->longData==num){
        //                return temp;
        //            }else if(temp->longData<num){
        //                temp=temp->Rlink;
        //            }else{
        //                temp=temp->Llink;
        //            }
    }
    //    }
    return temp;
}
template<class T>
long BST<T>::findSmallestSonOfRightSide(long temp)     //Search a number
{
    //    TreeNode<T> *temp;
    //    temp=root;
    //    if(temp->Llink!=NULL){
    temp=treeNodes[temp].Rlink;
    while(treeNodes[temp].Llink!=-1)
    {
        temp=treeNodes[temp].Llink;
        //            if(temp->longData==num){
        //                return temp;
        //            }else if(temp->longData<num){
        //                temp=temp->Rlink;
        //            }else{
        //                temp=temp->Llink;
        //            }
    }
    //    }
    return temp;
}

template<class T>
long BST<T>::FindFather(unsigned long long num)     //Search parent
{
    long find;
    find=root;
    while(find!=-1)
    {
        if(treeNodes[find].Llink!=-1)
        {
            if(treeNodes[treeNodes[find].Llink].longData==num)
            {
                return find;
            }
        }
        if(treeNodes[find].Rlink!=-1)
        {
            if(treeNodes[treeNodes[find].Rlink].longData==num)
            {
                return find;
            }
        }
        if(num<treeNodes[find].longData)
        {
        
            find=treeNodes[find].Llink;
        }
        else
        {
            find=treeNodes[find].Rlink;
        }
    }
    return -1;
}
template<class T>
void BST<T>::push(long temp)
{
    if(top==Node_Number-1)
    {
        
    }
    else
    {
        top++;
        STACK.push(treeNodes[temp]);
    }
}
template<class T>
T BST<T>::pop()
{
    //        cout<<STACK[Top].longData<<"\t";
    top--;
    T object=STACK.front().object;
    STACK.pop();
    return object;
}

//std::vector<Node*> BST::inorder(TreeNode *D,std::vector<Node*> nodes){    //Recursive of inorder
//
//    if(D!=NULL){
//        inorder(D->Llink,nodes);
//        nodes.push_back(D->node);
//        inorder(D->Rlink,nodes);
//    }
//    return nodes;
//}
//template<class T>
//void BST<T>::clearMemory()
//{
////    if (D->Llink!=NULL){
////        clearMemory(D->Llink);
////    }
////    if(D->Rlink!=NULL){
////        clearMemory(D->Rlink);
////    }
////    //        delete D;
////    D=NULL;
//    
////    STACK=NULL;
//    
//    
//}
template<class T>
void BST<T>::deleteAll()
{
//    clearMemory();
    std::queue<TreeNode<T> > empty;
    std::swap( STACK, empty );
    
    treeNodes.clear();
    std::vector<TreeNode<T> > empty2;
    std::swap( treeNodes, empty2 );
    root=-1;
    Node_Number=0;
    top=-1;
    PopCount=0;
}



#endif
