#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
int argc;
const char* argv [3];
int menu();
int choice;
int pages;
int loc;

struct node
{
    int number;
	int count;
	string name;
	node * next;
};

class LinkedList{
    private:
        node* head;
    public:
    LinkedList()
    {
        head = NULL;
    };
    void setHead(node* n1){ head = n1;};
    node* getHead(){ return head;};
    void makeList(int size);
    void insert(int loc, int numb, int numbPages);
    int bestins(LinkedList Free, int numbPages);
    int worstins(LinkedList Free, int numbPages);
    void remove(int number);
    int fragCount();
    void printList();

};
