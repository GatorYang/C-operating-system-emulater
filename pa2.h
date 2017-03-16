#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
int argc;
const char* argv [3];
int menu();
int choice;
int loc;
void bestFit();
void worstFit();
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
    void makeList(int size);
    void insert(int loc, int numb, int numbPages);
    int bestins(int numbPages);
    void worsins(int nub, int numbPages);
    void remove(int number, int numbPages);
    int fragCount();
    void printList();

};
