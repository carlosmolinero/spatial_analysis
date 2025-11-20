#ifndef BST_H
#define BST_H
#include <iostream>
#include "Node.h"

using namespace std;

template<class T>
class TreeNode
{
private:
public:
    unsigned long long longData;
    T object;
    TreeNode *Llink;
    TreeNode *Rlink;
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
    void clearMemory(TreeNode<T> *D);
    void deleteAll();
private:
    std::vector<TreeNode<T>> addLater;
    long Node_Number;
    long Top;
    long PopCount;
    long DeleteData;
    TreeNode<T> *STACK;
    TreeNode<T> *root;
    TreeNode<T> *ptr;
    TreeNode<T> *current;
    TreeNode<T> *pre;
//    TreeNode<T> *clear;
    TreeNode<T>* FindFather(unsigned long long num);
    TreeNode<T>* SearchNumber(unsigned long long num);
    void push(TreeNode<T> *temp);
    T pop();
    TreeNode<T>* findLargestSonOfLeftSide(TreeNode<T>* temp);
    TreeNode<T>* findSmallestSonOfRightSide(TreeNode<T>* temp);


};



template<class T>
BST<T>::BST()
{
    root=NULL;
    Node_Number=0;
    Top=-1;
    PopCount=0;
}

template<class T>
BST<T>::~BST()
{
//    current=root;
    if (Node_Number>0)
    {
        clearMemory(root);
    }
    //    cout<<"The memory is released"<<endl;
    //    system("Pause");
}
template<class T>
void BST<T>::add(unsigned long long id,T object)
{
    Node_Number++;
//    ptr=new TreeNode<T>;
    TreeNode<T> *ptr;
    ptr->Llink=NULL;
    ptr->Rlink=NULL;
    ptr->longData=id;
    ptr->object=object;
    if(root==NULL)         //For now the tree is still empty so the new node will be root!
    {
        root=ptr;
    }
    else      //The tree is not empty!
    {
        TreeNode<T>* possibleNode=SearchNumber(ptr->longData);
        if(possibleNode!=NULL)         //Binary Search tree can not have the same data!
        {
            //                cout<<"Error! You have the same longeger!!"<<endl;
            //                SearchNumber(ptr->longData)->node=node;
            Node_Number--;
            possibleNode->object=object;
            return;        //Jump to the menu!
        }
        current=root;
        while(current!=NULL)
        {
            if(ptr->longData<current->longData)     //Compare two longeger. If node of ptr is less than node of currnet then put
            {
                //the node of ptr to left subtree.
                if(current->Llink==NULL)     //Consider the node is a leaf!
                {
                    current->Llink=ptr;
                    ptr->Llink=NULL;
                    ptr->Rlink=NULL;
                    current=NULL;
                }
                else
                {
                    current=current->Llink;  //Move to the next left child
                }
            }
            else      //If node of ptr is bigger than node of currnet then put the node of ptr to right subtree.
            {
                if(current->Rlink==NULL)     //Consider the node is a leaf!
                {
                    current->Rlink=ptr;
                    ptr->Llink=NULL;
                    ptr->Rlink=NULL;
                    current=NULL;
                }
                else
                {
                    current=current->Rlink;  //Move to the next right child
                }
            }

        }
    }
}
template<class T>
void BST<T>::deleteNode(unsigned long long id)
{
    if(root==NULL)
    {
        cout<<"The tree is empty!"<<endl;
    }
    //    cout<<"Which one do you want delete? :"<<endl;
    DeleteData=id;
    if(SearchNumber(DeleteData)==NULL)
    {
        //        cout<<"Error!! Can not find this longeger!!"<<endl;
        return;
    }
    else
    {
        current=SearchNumber(DeleteData);        //Find the longeger
    }
    TreeNode<T> *temp;
    if(current==root&&Node_Number==1)     //Consider the delete longeger is root node and it is only one node in tree!
    {
//        clear=current;
        root=NULL;
//        delete clear;
        current=NULL;
        Node_Number--;
        return;
    }
    else if(current==root)      //Consider the delete longeger is root node and it is not only one node in tree!
    {
        if(root->Llink==NULL)     //Consider it is no left subtree!
        {
//            clear=root;
            root=root->Rlink;
//            delete clear;
            Node_Number--;
            return;
        }
        else if(root->Rlink==NULL)      //Consider it is no right subtree!
        {
//            clear=root;
            root=root->Llink;
//            delete clear;
            Node_Number--;
            return;
        }
        else      //If the root have left subtree and right subtree!
        {
            temp=current;
            temp=temp->Llink;    //Move to the left child! Beacuse I want to choose the biggest node of left subtree to replace the node of root!
            if(temp->Rlink==NULL)     //In the left subtree. The biggest node always at right node! Now Consider if the left subtree have no right node!
            {
                temp->Rlink=root->Rlink;
//                clear=root;
                root=temp;
//                delete clear;
                Node_Number--;
                return;
            }
            else
            {
                while(temp->Rlink!=NULL)     //Last right node is the bigest node in left subtree of root!
                {
                    temp=temp->Rlink;        //Keep move to the right node!
                }
                pre=FindFather(temp->longData);    //Find this node's parent
                if(temp->Llink==NULL)     //Consider two case. if temp node have no leftchild then his parent doesn't need to link any node!
                {
                    pre->Rlink=NULL;
                }
                else
                {
                    pre->Rlink=temp->Llink;    //The other case is if temp node have leftchild then his parent need to link leftchild!
                }
                temp->Llink=root->Llink;    //Replace the delete node!
                temp->Rlink=root->Rlink;
//                clear=root;
                root=temp;
//                delete clear;    //Delete
                Node_Number--;
                return;
            }
        }
    }

    if(current->Llink==NULL&&current->Rlink==NULL)         //if the node we want to delete is a leaf
    {
        pre=FindFather(current->longData);    //Find parent of delete node
        if(pre->longData>current->longData)     //After remove delete node. The parent node will link to NULL.
        {
            pre->Llink=NULL;
//            clear=current;
//            delete clear;
            current=NULL;
            Node_Number--;
            return;
        }
        else
        {
            pre->Rlink=NULL;
//            clear=current;
//            delete clear;
            current=NULL;
            Node_Number--;
            return;
        }
    }
    pre=FindFather(DeleteData);
    if(current->Llink==NULL)
    {
        if(((current->Rlink)->Llink==NULL)&&((current->Rlink)->Rlink==NULL))     //if the node we want to delete is only have one child node
        {
//            clear=current;
            if(pre->longData>current->longData)     //parent node will link to the child of delete node
            {
                current=current->Rlink;
                pre->Llink=current;
//                delete clear;
                
                Node_Number--;
                return;
            }
            else      //parent node will link to the child of delete node
            {
                current=current->Rlink;
                pre->Rlink=current;
//                delete clear;
                Node_Number--;
                return;
            }
        }
    }
    else if(current->Rlink==NULL)
    {
        if((current->Llink)->Llink==NULL&&(current->Llink)->Rlink==NULL)     //if the node we want to delete is only have one child node
        {
//            clear=current;
            if(pre->longData>current->longData)     //parent node will link to the child of delete node
            {
                current=current->Llink;
                pre->Llink=current;
//                delete clear;
                Node_Number--;
                return;
            }
            else      //parent node will link to the child of delete node
            {
                current=current->Llink;
                pre->Rlink=current;
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
    if (current->Llink!=NULL)
    {
        temp=findLargestSonOfLeftSide(current);
        if (temp!=current->Llink)
        {
            if (temp->Llink!=NULL)
            {
                TreeNode<T>* pre1=FindFather(temp->longData);
                TreeNode<T>* pre2=FindFather(current->longData);
                pre1->Rlink=temp->Llink;
                temp->Llink=current->Llink;
                temp->Rlink=current->Rlink;
                if(pre2->Rlink==current)
                {
                    pre2->Rlink=temp;
                }
                else
                {
                    pre2->Llink=temp;
                }
//                delete current;
                current=NULL;
                Node_Number--;
            }

        }
        else
        {
            TreeNode<T>* pre2=FindFather(current->longData);
            temp->Rlink=current->Rlink;
            if(pre2->Rlink==current)
            {
                pre2->Rlink=temp;
            }
            else
            {
                pre2->Llink=temp;
            }
//            delete current;
            current=NULL;
            Node_Number--;
        }
    }
    else if (current->Rlink!=NULL)
    {
        temp=findSmallestSonOfRightSide(current);
        if (temp!=current->Rlink)
        {
            if (temp->Llink!=NULL)
            {
                TreeNode<T>* pre1=FindFather(temp->longData);
                TreeNode<T>* pre2=FindFather(current->longData);
                pre1->Llink=temp->Rlink;
                temp->Rlink=current->Rlink;
                temp->Llink=current->Llink;
                if(pre2->Rlink==current)
                {
                    pre2->Rlink=temp;
                }
                else
                {
                    pre2->Llink=temp;
                }
//                delete current;
                current=NULL;
                Node_Number--;
            }

        }
        else
        {
            TreeNode<T>* pre2=FindFather(current->longData);
            temp->Llink=current->Llink;
            if(pre2->Rlink==current)
            {
                pre2->Rlink=temp;
            }
            else
            {
                pre2->Llink=temp;
            }
//            delete current;
            current=NULL;
            Node_Number--;
        }
    }
}
template<class T>
std::vector<T> BST<T>::getAll()
{
    std::vector<T> objects;
    if(root==NULL)
    {
        return objects;
    }
    STACK=new TreeNode<T>[Node_Number];    //Create a structure array as a stack!
    PopCount=0;
    current=root;


    while(1)     // Non-Recursive of inorder .The order is follow this rule. parent,leftchild,rightchild
    {
        if(current!=NULL)
        {
            push(current);
            current=current->Llink;
        }
        else
        {

            current=STACK[Top].Rlink;
            objects.push_back(pop());
            PopCount++;
        }
        if(PopCount==Node_Number)
        {
            //            cout<<endl;
            break;
        }
    }
    delete []STACK;
    return objects;
}
template<class T>
T BST<T>::get(unsigned long long id)
{
    unsigned long long num=id;
    //    cout<<"Please Enter the longeger"<<endl;
    //    cin>>num;
    TreeNode<T>* element=SearchNumber(num);
    if(element!=NULL)
    {
        return element->object;
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
    TreeNode<T>* element=SearchNumber(num);
    if(element!=NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
TreeNode<T>* BST<T>::SearchNumber(unsigned long long num)     //Search a number
{
    TreeNode<T> *temp;
    temp=root;
    while(temp!=NULL)
    {
        if(temp->longData==num)
        {
            return temp;
        }
        else if(temp->longData<num)
        {
            temp=temp->Rlink;
        }
        else
        {
            temp=temp->Llink;
        }
    }
    return temp;
}
template<class T>
TreeNode<T>* BST<T>::findLargestSonOfLeftSide(TreeNode<T>* temp)     //Search a number
{
//    TreeNode<T> *temp;
//    temp=root;
//    if(temp->Llink!=NULL){
    temp=temp->Llink;
    while(temp->Rlink!=NULL)
    {
        temp=temp->Rlink;
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
TreeNode<T>* BST<T>::findSmallestSonOfRightSide(TreeNode<T>* temp)     //Search a number
{
    //    TreeNode<T> *temp;
    //    temp=root;
//    if(temp->Llink!=NULL){
    temp=temp->Rlink;
    while(temp->Llink!=NULL)
    {
        temp=temp->Llink;
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
TreeNode<T>* BST<T>::FindFather(unsigned long long num)     //Search parent
{
    TreeNode<T> *Find;
    Find=root;
    while(Find!=NULL)
    {
        if(Find->Llink!=NULL)
        {
            if(Find->Llink->longData==num)
            {
                return Find;
            }
        }
        if(Find->Rlink!=NULL)
        {
            if(Find->Rlink->longData==num)
            {
                return Find;
            }
        }
        if(num<Find->longData)
        {
            Find=Find->Llink;
        }
        else
        {
            Find=Find->Rlink;
        }
    }
    return NULL;
}
template<class T>
void BST<T>::push(TreeNode<T> *temp)
{
    if(Top==Node_Number-1)
    {

    }
    else
    {
        Top++;
        STACK[Top]=*temp;
    }
}
template<class T>
T BST<T>::pop()
{
    //        cout<<STACK[Top].longData<<"\t";
    Top--;
    return STACK[Top+1].object;
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
template<class T>
void BST<T>::clearMemory(TreeNode<T> *D)
{
    if (D->Llink!=NULL){
        clearMemory(D->Llink);
    }
    if(D->Rlink!=NULL){
        clearMemory(D->Rlink);
    }
//        delete D;
    D=NULL;

    STACK=NULL;
}
template<class T>
void BST<T>::deleteAll()
{
    clearMemory(root);
    root=NULL;
    Node_Number=0;
    Top=-1;
    PopCount=0;
}



#endif
