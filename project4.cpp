/*Project 4
 *Completed: April 2020
 *Author: Jackson Bradshaw, 113474543
 */

#include <iostream>
using namespace std;

template <class DT>
class GLRow; //class prototype
template <class DT>
ostream& operator <<(ostream& s, const GLRow<DT>& oneGLRow);

template <class DT>
class GLRow {
    template <class T>
    friend ostream& operator<< (ostream& s, const GLRow<T>& oneGLRow);
protected:
    DT* _info;
    int _next;
    int _down;
public:
    GLRow(); //no-args constructor
    GLRow(DT& newInfo); //arg constructor
    GLRow(GLRow<DT>& anotherOne); //copy constructor
    GLRow<DT>& operator= (GLRow<DT>& anotherOne);
    int getNext(); //returns next
    int getDown(); //returns down
    DT& getInfo(); //returns info
    void setNext(int n); //sets next
    void setDown(int d); //sets down
    void setInfo(DT& i); //sets info
    ~GLRow(); //destructor
};

template <class DT>
ostream& operator<< (ostream& s, const GLRow<DT>& oneGLRow) {
    s << *(oneGLRow._info);
    return s;
}

template <class DT>
GLRow<DT>::GLRow() {
    //cout << "baseline constructor called" << endl;
    int temp = 999;
    _info = &temp;
    _next = -1;
    _down = -1;
}

template <class DT>
GLRow<DT>::GLRow(DT& newInfo) {
    _info = &newInfo;
    *_info = newInfo;
    _next = -1;
    _down = -1;
}

template <class DT>
GLRow<DT>::GLRow(GLRow<DT>& anotherOne) {
    _info = new DT;
    *_info = *(anotherOne._info);
    _next = anotherOne._next;
    _down = anotherOne._down; //deep copies all variables from anotherOne
}

template <class DT>
GLRow<DT>& GLRow<DT>::operator= (GLRow<DT>& anotherOne) {
    _info = new DT;
    *_info = *(anotherOne._info);
    _next = anotherOne._next;
    _down = anotherOne._down; //deep copies all variables from anotherOne
    return *this;
}

template <class DT>
int GLRow<DT>::getNext() {
    return _next;
}

template <class DT>
int GLRow<DT>::getDown() {
    return _down;
}

template <class DT>
DT& GLRow<DT>::getInfo() {
    return *_info;
}

template <class DT>
void GLRow<DT>::setNext(int n) {
    _next = n;
}

template <class DT>
void GLRow<DT>::setDown(int d) {
    _down = d;
}

template <class DT>
void GLRow<DT>::setInfo(DT& i) {
    *_info = i;
}

template <class DT>
GLRow<DT>::~GLRow() {
    delete[] _info;
}

template <class DT>
class ArrayGLL; //class prototype
template <class DT>
ostream& operator <<(ostream& s, ArrayGLL<DT>& oneGLL);

template <class DT>
class ArrayGLL {
    template <class T>
    friend ostream& operator<< (ostream& s, ArrayGLL<T>& oneGLL);
protected:
    GLRow<DT>* myGLL; //array of GLRows
    int maxSize; //maximum size of the array of GLRows
    int firstElement;
    int firstFree;
public:
    ArrayGLL(); //no-args constructor
    ArrayGLL(int size); //args (size input) constructor
    ArrayGLL(ArrayGLL<DT>& anotherOne); //copy constructor
    ArrayGLL<DT>& operator= (ArrayGLL<DT>& anotherOne);
    void display(); //display in parenthesis format
    int find(DT& key);  //returns index position of the element key
                        //returns -1 if key is not present
    void findDisplayPath(DT& key); /*prints the values of nodes
                                          *visited along the route to
                                          *the element key
                                          */
    int noFree(); //returns the number of free locations
    int size(); //return number of elements stored
    int parentPos(DT& key); //provides the location of the parent
                            //of the element key in the array
    GLRow<DT>& operator [] (int pos); //returns the GLRow that is in
                                      //the position pos in the array
    int getFirstFree();
    int getFirstElement();
    void setFirstFree(int pos);
    void setFirstElement(int pos);
    int findFree(); //returns firstFree and sets the next free node to firstFree
    void insertAChild(DT& parent, DT& child); //inserts a child onto a parent node
    void removeANode(DT& node); //removes input node from list structure
    ~ArrayGLL(); //destructor
private:
    void recurDisplay(int startPos); //recursive call for display
    int find(DT& key, int startPos); //part of find recursive algorithm
    void printPath(DT path[], int length); //prints out path for findDisplayPath
    void findPathRecur(DT& key, int startPos, DT path[], int length); //recursive call for print path method
    int recurSize(int startPos); //recursive call for size
    int recurParentPos(DT& key, int startPos, int lastPos); //part of parentPos recursive call
};

template <class DT>
ostream& operator<< (ostream& s, ArrayGLL<DT>& oneGLL) {
    s << "\t_Info\t_Next\t_Down" << endl;
    for (int i = 0; i < oneGLL.maxSize; ++i) {
        s << i << "\t" << oneGLL.myGLL[i].getInfo()
            << "\t" << oneGLL.myGLL[i].getNext() << "\t"
            << oneGLL.myGLL[i].getDown() << endl;
    }
    return s;
}

template <class DT>
ArrayGLL<DT>::ArrayGLL() {
    myGLL = NULL;
    maxSize = 0;
    firstElement = -1;
    firstFree = -1;
}

template <class DT>
ArrayGLL<DT>::ArrayGLL(int size) {
    myGLL = new GLRow<DT>[size];
    for (int i = 0; i < size - 1; ++i) {
        myGLL[i].setNext(i + 1);
    }
    maxSize = size;
    firstElement = -1;
    firstFree = 0;
}

template <class DT>
ArrayGLL<DT>::ArrayGLL(ArrayGLL<DT>& anotherOne) {
    myGLL = new GLRow<DT>[anotherOne.maxSize];
    for (int i = 0; i < anotherOne.maxSize; ++i) {
        myGLL[i] = anotherOne.myGLL[i];
    }
    maxSize = anotherOne.maxSize;
    firstElement = anotherOne.firstElement;
    firstFree = anotherOne.firstFree; //deep copy
}

template <class DT>
ArrayGLL<DT>& ArrayGLL<DT>::operator= (ArrayGLL<DT>& anotherOne) {
    myGLL = new GLRow<DT>[anotherOne.maxSize];
    for (int i = 0; i < anotherOne.maxSize; ++i) {
        myGLL[i] = anotherOne.myGLL[i];
    }
    maxSize = anotherOne.maxSize;
    firstElement = anotherOne.firstElement;
    firstFree = anotherOne.firstFree; //deep copy
    return *this;
}

template <class DT>
void ArrayGLL<DT>::recurDisplay(int startPos) {
    cout << myGLL[startPos].getInfo() << " "; //prints out current GLRow
    int currPos = myGLL[startPos].getDown();
    if (currPos != -1) { //if node has a down connection
        cout << "(";
        recurDisplay(currPos); //recursive call to next GLRow and its children
        while (myGLL[currPos].getNext() != -1) { //while there is a next node
            currPos = myGLL[currPos].getNext();
            recurDisplay(currPos);
        }
        cout << ") ";
    }
}

template <class DT>
void ArrayGLL<DT>::display() {
    recurDisplay(firstElement);
}

template <class DT>
int ArrayGLL<DT>::find(DT& key, int startPos) {
    if (myGLL[startPos].getInfo() == key) {
        return startPos; //index with the correct key
    }
    int currPos = myGLL[startPos].getDown();
    if (currPos != -1) { //if node has a down connection
        int result = find(key, currPos); //first recursive call
                                         //set to result so that -1 is not automatically returned
        while (myGLL[currPos].getNext() != -1 && result == -1) { //while there is a next node
            currPos = myGLL[currPos].getNext();                  //and result is still -1 (key not found)
            result = find(key, currPos); //recursive call
        }
        return result; //returns result, -1 or otherwise
    }
    return -1; //returns -1 if startPos node lacks key and has no down node
}

template <class DT>
int ArrayGLL<DT>::find(DT& key) {
    return find(key, firstElement);
}

template <class DT>
void ArrayGLL<DT>::printPath(DT path[], int length) {
    for (int i = 0; i < length; ++i) {
        cout << path[i];
        if (i < length - 1) {
            cout << "->";
        }
        else {
            cout << endl;
        }
    }
}

template <class DT>
void ArrayGLL<DT>::findPathRecur(DT& key, int startPos, DT path[], int length) {
    if (myGLL[startPos].getInfo() == key) { //index with the correct key
        path[length] = myGLL[startPos].getInfo();
        printPath(path, length + 1);
    }
    int currPos = myGLL[startPos].getDown();
    if (currPos != -1) { //if node has a down connection
        path[length] = myGLL[startPos].getInfo();
        findPathRecur(key, currPos, path, length + 1);
        while (myGLL[currPos].getNext() != -1) { //while there is a next node
            currPos = myGLL[currPos].getNext();
            findPathRecur(key, currPos, path, length + 1);
        }
    }
}
template <class DT>
void ArrayGLL<DT>::findDisplayPath(DT& key) {
    DT* path = new DT[maxSize]; //creates path to store GLRows on the way to key
    findPathRecur(key, firstElement, path, 0);
    delete[] path;
}

template <class DT>
int ArrayGLL<DT>::noFree() {
    int currPos = firstFree; //starts at first free location in myGLL array
    int numFree = 1; //initialized to 1 for first free location
    while (myGLL[currPos].getNext() != -1) { //while the node has a next
        currPos = myGLL[currPos].getNext(); //sets freeRow to next node
        numFree++; //adds to numFree per node travelled
    }
    return numFree;
}

template <class DT>
int ArrayGLL<DT>::recurSize(int startPos) {
    int size = 1;
    int currPos = myGLL[startPos].getDown();
    if (currPos != -1) { //if node has a down connection
        size += recurSize(currPos);
        while (myGLL[currPos].getNext() != -1) { //while there is a next node
            currPos = myGLL[currPos].getNext();
            size += recurSize(currPos);
        }
    }
    return size;
}

template <class DT>
int ArrayGLL<DT>::size() {
    return recurSize(firstElement);
}

template <class DT>
int ArrayGLL<DT>::recurParentPos(DT& key, int startPos, int lastPos) {
    if (myGLL[startPos].getInfo() == key) {
        return lastPos; //index with the correct key
    }
    int pastPos = startPos; //set to parent GLRow
    int currPos = myGLL[startPos].getDown(); //start of the children of startPos/pastPos
    if (currPos != -1) { //if node has a down connection 
        int result = recurParentPos(key, currPos, pastPos);
        while (myGLL[currPos].getNext() != -1 && result == -1) { //while there is a next node
            currPos = myGLL[currPos].getNext(); //sends currPos to next node
            result = recurParentPos(key, currPos, pastPos); //recursive call
        }
        return result; //returns result, -1 or otherwise
    }
    return -1; //returns -1 if startPos node lacks key and has no down node
}

template <class DT>
int ArrayGLL<DT>::parentPos(DT& key) {
    return recurParentPos(key, firstElement, -1); //goes to recursive parentPos algorithm
    //lastPos initially set to -1, as the first element has no parent position
}

template <class DT>
GLRow<DT>& ArrayGLL<DT>::operator [] (int pos) {
    return myGLL[pos];
}

template <class DT>
int ArrayGLL<DT>::getFirstFree() {
    return firstFree;
}

template <class DT>
int ArrayGLL<DT>::getFirstElement() {
    return firstElement;
}

template <class DT>
void ArrayGLL<DT>::setFirstFree(int pos) {
    firstFree = pos;
}

template <class DT>
void ArrayGLL<DT>::setFirstElement(int pos) {
    firstElement = pos;
}

template <class DT>
int ArrayGLL<DT>::findFree() {
    int free = firstFree; //index of current firstFree
    firstFree = myGLL[free].getNext(); //firstFree set to next free index
    return free; //returns former firstFree index
}

template <class DT>
void ArrayGLL<DT>::insertAChild(DT& parent, DT& child) {
    int newIndex = findFree(); //index of new node (former free node)
    myGLL[newIndex].setInfo(child); //creates new node
    if (parent == -1) { //if there is no parent
        firstElement = newIndex; //root set to new node
    }
    else { //if there is a parent
        int parentIndex = find(parent); //index of parent node
        myGLL[newIndex].setNext(myGLL[parentIndex].getDown()); //next of child set to down of parent
        myGLL[parentIndex].setDown(newIndex); //down of parent set to child index
    }
}

template <class DT>
void ArrayGLL<DT>::removeANode(DT& node) {
    int nodeIndex = find(node); //index of node to be removed
    int parentIndex = parentPos(node); //index of parent of node

    if (myGLL[nodeIndex].getDown() == -1) { //if node is a leaf node:
        if (myGLL[parentIndex].getDown() == nodeIndex) { //if the node is the down of parent:
            if (myGLL[nodeIndex].getNext() == -1) { //if node has no next
                myGLL[parentIndex].setDown(-1); //down set to -1
            }
            else { //if node has a next
                myGLL[parentIndex].setDown(myGLL[nodeIndex].getNext()); //down set to node's next
            }
        }
        else { //if node is not the down of parent:
            int currPos = myGLL[parentIndex].getDown();
            while (myGLL[currPos].getNext() != nodeIndex) { //finding node with next leading to removed node
                currPos = myGLL[currPos].getNext();
            }
            if (myGLL[nodeIndex].getNext() == -1) { //if node has no next
                myGLL[currPos].setNext(-1); //next set to -1
            }
            else { //if node has a next
                myGLL[currPos].setNext(myGLL[nodeIndex].getNext()); //next set to node's next
            }
        }
        //removing node and adding it to free nodes:
        myGLL[nodeIndex];
        myGLL[nodeIndex].setNext(firstFree); //set next to current first free
        firstFree = nodeIndex; //first free set to removed node index
    }

    else { //if node is not a leaf node:
        int leftIndex = nodeIndex;
        while (myGLL[leftIndex].getDown() != -1) {
            leftIndex = myGLL[leftIndex].getDown();
        } //finds left-most element

        myGLL[nodeIndex].setInfo(myGLL[leftIndex].getInfo());//left-most info set to index to be removed
        myGLL[parentPos(leftIndex)].setDown(myGLL[leftIndex].getNext());
        //sets down to -1 if leftIndex has no next or to leftIndex's next

        //removes left-most index
        myGLL[leftIndex];
        myGLL[leftIndex].setNext(firstFree);
        firstFree = leftIndex;
    }
}

template <class DT>
ArrayGLL<DT>::~ArrayGLL() {
    delete[] myGLL;
}

int main() {
    ArrayGLL<int>* firstGLL;
    int noElements;
    char command;
    int node1, node2;
    int value;
    //variables initialized

    cin >> noElements;

    firstGLL = new ArrayGLL<int>(noElements);
    while (cin.eof()) {
        cin >> command;
        switch (command) {
            case 'I':
                cin >> node1 >> node2;
                (*firstGLL).insertAChild(node1, node2);
                cout << "Element inserted";
                break;
            case 'R':
                cin >> node1;
                (*firstGLL).removeANode(node1);
                cout << "Element removed";
                break;
            case 'F':
                cin >> node1;
                value = (*firstGLL).find(node1);
                cout << "The element " << node1 << " is found at index: " << value;
                break;
            case 'P':
                cin >> node1;
                value = (*firstGLL).parentPos(node1);
                cout << "The parent of " << node1 << " is: " << (*firstGLL)[value].getInfo();
                break;
            case 'D':
                (*firstGLL).display();
                break;
            default:
                break;
        }
        cout << endl;
    }

    return 0;
}