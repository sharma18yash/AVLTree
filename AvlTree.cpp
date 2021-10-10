#include<iostream>
#include<stdio.h>
using namespace std;
template <class T>
class Node{
    public:
    T key;
    Node* left;
    Node* right;
    int h; // for storing the height of current node
    int count; //count is for storing the number of duplicates present for the given item
};
class AVL{
public:
    template<class T>
    bool cmpLess(T val1, T val2) // write comprator function logic here
    {
        if(val1 < val2)
            return true;
        else   
            return false;
    }
    template<class T>
    bool cmpGreater(T val1, T val2)
    {
        if(val1 > val2)
            return true;
        else
            return false;
    }
    template <class T>
    bool isEqual(T val1, T val2)
    {
        if(val1==val2)
            return true;
        return false;
    }
    template <class T>
    int height(Node<T>* N)
    {
        if(N==NULL)
            return 0;
        return N->h;
    }
    // template <class T> 
    // int max(T a, T b)
    // {
    //     return (a>b)?a:b;
    // }
    template <class T>
    Node<T>* newNode(T key)
    {
        Node<T>* node = new Node<T>();
        node->key=key;
        node->left=NULL;
        node->right=NULL;
        node->h=1;
        node->count=1;
        return node;
    }
    template <class T>
    Node<T> *rightRotate(Node<T> *y)
    {
        Node<T> *x = y->left;
        Node<T> * T2 = x->right;
        x->right = y;
        y->left = T2;
        y->h = max(height(y->left), height(y->right)) + 1;
        x->h = max(height(x->left), height(x->right)) + 1;
        return x;
    }
    template <class T>
    Node<T> *leftRotate(Node<T> *x)
    {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->h = max(height(x->left), height(x->right))+1;
        y->h = max(height(y->left), height(y->right))+1;
        return y;
    }
    template <class T>
    int getBalance(Node<T> *n)
    {
        if(n==NULL)
            return 0;
        return height(n->left) - height(n->right);
    }
    template <class T>
    Node<T>* insert(Node<T>* node, T key)
    {
        if(node==NULL)
            return(newNode(key));
        if(isEqual(key, node->key)) // to handle diplicate cases
        {
            node->count++;
            return node;
        }
        if(cmpLess(key, node->key))
            node->left = insert(node->left, key);
        else if(cmpGreater(key, node->key))
            node->right = insert(node->right, key);
        else    
            return node;

        node->h = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);
        // if(balance > 1 && key < node->left->key)
        if(balance > 1 && cmpLess(key, node->left->key))
            return rightRotate(node);
        if(balance<-1 && cmpGreater(key , node->right->key))
            return leftRotate(node);
        if(balance > 1 && cmpGreater(key , node->left->key))
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if(balance < -1 && cmpLess(key , node->right->key))
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    template <class T>
    void inorder(Node<T>* root)
    {
        if(root!=NULL)
        {
            inorder(root->left);
            for(int i=0;i<root->count; i++)
                cout<<root->key<<" ";
            inorder(root->right);
        }
    }
    template <class T>
    void preorder(Node<T>* root)
    {
        if(root!=NULL)
        {
            for(int i=0;i<root->count; i++)
                cout<<root->key<<" ";
            preorder(root->left);
            preorder(root->right);
        }
    }
    template <class T>
    Node<T>* minNode(Node<T>* n)
    {
        Node<T>* curr = n;
        while(curr->left!=NULL)
            curr=curr->left;
        return curr;
    }
    template <class T>
    Node<T>* deleteNode(Node<T>* root, T key)
    {
        if(root==NULL)
            return root;
        if(cmpLess(key , root->key))
            root->left = deleteNode(root->left, key);
        else if(cmpGreater(key , root->key))
            root->right = deleteNode(root->right, key);
        else{
            // if(root->count > 1) //deleting one element if duplicates are present
            // {
            //     root->count--;
            //     return(root);
            // }
            if(root->left==NULL || root->right==NULL)
            {
                Node<T>* temp = root->left?root->left:root->right;
                if(temp==NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
                free(temp);
            }
            else
            {
                Node<T>* temp = minNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            } 
        }
        if(root==NULL)
            return root;
        root->h = 1+max(height(root->left), height(root->right));
        int balance = getBalance(root);
        if(balance > 1 && getBalance(root->left)>=0)
            return rightRotate(root);
        
        if(balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if(balance < -1 && getBalance(root->right)<=0)
        {
            // node->left = leftRotate(node->left);
            return leftRotate(root);
        }
        if(balance < -1 && getBalance(root->right)>0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
    template <class T>
    bool search(Node<T>* root, T key)
    {
        if(root==NULL)
            return false;
        if(isEqual(root->key, key))
            return true;
        else if(cmpGreater(root->key , key))
            return search(root->left, key);
        else if(cmpLess(root->key , key))
            return search(root->right, key);
        return false;
    }
    template <class T>
    int countOccurences(Node<T>* root, T key)
    {
        if(root==NULL)
            return 0;
        else if( isEqual(root->key,key))
            return root->count;
        else if(cmpGreater(root->key , key))
            return countOccurences(root->left, key);
        else if(cmpLess(root->key , key))
            return countOccurences(root->right, key);
        return 0;
    }
    template <class T>
    int closestElement(Node<T>* root, T value)
    {
        static int min_diff = 2147483647 , min_diffKey=-1;
        if(root==NULL)
            return min_diffKey;
        if(root->key==value)
        {
            min_diffKey=value;
            return min_diffKey;
        }
        if(min_diff > abs(root->key - value))
        {
            min_diff = abs(root->key - value);
            min_diffKey=root->key;
        }
        if(value < root->key)
            return closestElement(root->left, value);
        else 
            return closestElement(root->right, value);
        // return min_diffKey;
    }
    template <class T>
    void k_largest(Node<T>* root, int k)
    {
        static int c=0;
        if(root==NULL || c>=k)
            return ;
        k_largest(root->right,k);
        c = c+1;
        
        if(c==k)
        {
            cout<<root->key<<endl;
        }
        k_largest(root->left,k);
        // return 0;
    }
    template <class T>
    int range(Node<T>* root, T val1,T val2)
    {
        if(!root)
            return 0;
        if(root->key >= val1 && root->key <= val2)
            return 1+range(root->left, val1, val2) + range(root->right, val1, val2);
        if(root->key < val1)
            return range(root->right, val1, val2);
        else return range(root->left, val1, val2);
    }
    template <class T>
    void lower_bound(Node<T>* root, T bound)
    {
        static int f=0;
        if(root!=NULL)
        {
            lower_bound(root->left, bound);
            if(root->key >= bound)
            {
                if(f==0){
                    f=1;
                    cout<<root->key<<endl;
                }
                return;
            }
            else    
            lower_bound(root->right, bound);   
        }
    }
    template <class T>
    void upper_bound(Node<T>* root, T bound)
    {
        static int f=0;
        if(root!=NULL)
        {
            upper_bound(root->left, bound);
            if(root->key > bound)
            {
                if(f==0){
                    f=1;
                    cout<<root->key<<endl;
                }
                return;
            }
            else    
            upper_bound(root->right, bound);   
        }
    }


};
int main()
{ 
    Node<int> *root = NULL;
    AVL t;
    // string a = "abcd";
    root = t.insert(root, 10);
    // a = "aef";
    root = t.insert(root, 20);
    root = t.insert(root, 30);
    root = t.insert(root, 40);
    root = t.insert(root, 50);
    root = t.insert(root, 60);
    root = t.insert(root, 70);
    t.inorder(root);
    cout<<endl;
    // t.preorder(root);
    // cout<<endl;
    // t.preorder(root);
    // cout<<endl;
    cout<<t.countOccurences(root,20)<<endl;
    root = t.deleteNode(root, 40);
    t.inorder(root);
    // cout<<endl;
    cout<<t.range(root, 25,50);
    // string e = "abcd";
    // t.upper_bound(root, e);
    return 0;
}