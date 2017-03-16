#include "pa2.h"
#include <iostream>
#include <string>


int main( int argc, char **argv)
{
	// argc == argument count
    // argv is a array, of c-strings

    std::string *cppArgs = new std::string[argc];
    for(int i = 0; i != argc; ++i){
        cppArgs[i] = string(argv[i]);
    }

    string algorithm;
	algorithm = argv[1];
	if (algorithm != "best" && algorithm != "worst")
	{
	cout << "Error, not a proper argument. Please try again using \"best\" or \"worst\"." << endl;
	return 0;
	}
	cout << endl << "Using " << algorithm << " fit algorithm" << endl;

	LinkedList Free;

	Free.makeList(32);


	//int chocie = 0;
	int number;
	int numbPages;
	int loc;
	cout << "1. Add Program\n";
	cout << "2. Kill Program\n";
	cout << "3. Fragmentation\n";
	cout << "4. Print\n";
	cout << "5. Exit";


	while(choice != 5){

		choice = menu();				//create and out put the menu

		switch(choice){
			case 1:	cout << "\nProgram Name- P";			//if input is to add call the insertion method add programs
						cin >> number;
						if (cin.fail()){
							cin.clear();
					        cin.ignore(256,'\n');
							cout << "Error bad input, please only enter a number."<< endl;
							break;
						}
						cout << "Program Size (KB)- ";
						int programSize;
						cin >> programSize;
						if (cin.fail()){
							cin.clear();
					        cin.ignore(256,'\n');
							cout << "Error bad input, please only enter a number."<< endl;
							break;
						}
						if(programSize % 4 == 0){				//if progarm size is divisible by 4 then add that many pages
							numbPages = programSize / 4;
						}
						else{
							numbPages = (programSize / 4) + 1;		//if program size is not divisible by 4 then round up to create whole pages
						}
						if(algorithm == "best"){
							loc = Free.bestins(Free, numbPages);              //give the best fit location where to add
						}
						if(algorithm == "worst"){
							loc = Free.worstins(Free, numbPages);              //give the worst location where to add
						}
						if (loc < 0){
							cout << "Error, Not enough memory for Program P"<< number <<endl;
							break;
						}
						Free.insert(loc, number, numbPages);        // insert acording to location

						break;

			case 2:	cout << "Program Name: P";				//if input is to kill program then call removal
					cin >> number;
					if (cin.fail()){
							cin.clear();
					        cin.ignore(256,'\n');
							cout << "Error bad input, please only enter a number."<< endl;
							break;
					}
					Free.remove(number);

						break;

			case 3:	cout << "There are " << Free.fragCount() << " fragment(s)\n";  //call counter to determine fragemnt(s)
						break;

			case 4:	Free.printList();			//call print function
						break;

			case 5:	cout << "Program Exit\n";   //end program
						break;
		}

	}
}
int LinkedList::bestins(LinkedList Free, int numbPages) //give the location for best fit to insert
{

    head = Free.getHead();
    node * temp = head;
    int list [31];
    int loc = 0;
    int l = 0;
    int max = 100;
    bool isSpace = true;
    for (int i = 0; i < 31; i++) //set the list to 0
    {
        list [i]= 0;
    }

    for (int i = 0; i < 31; i++)
    {
        if (temp -> name == "FREE")  //the array store how much free "pages" it has from that point
        {
            list [l]+=1;
        }
        if(temp -> name != "FREE") // free "pages" counter stop if not "free"
        {
            l = i+1;
        }
        temp = temp->next;

    }

    for(int i = 0; i < 31; i++) //compares and find smallest posible sarting point
    {
    	if(list[i] >= numbPages ){
    		isSpace = false;
    	}

        if(list[i] <= max && list[i] >= numbPages && list[i] > 0){
            loc = i;
            max = list[i];
        }

    }
    if (isSpace){
    	return -1;
    }
    return loc;
}

int LinkedList::worstins(LinkedList Free, int numbPages) //give the location for best fit to insert
{

    head = Free.getHead();
    node * temp = head;
    int list [31];
    int loc = 0;
    int l = 0;
    int min = 0;
    bool isSpace = true;
    for (int i = 0; i < 31; i++) //set the list to 0
    {
        list [i]= 0;
    }

    for (int i = 0; i < 31; i++)
    {
        if (temp -> name == "FREE")  //the array store how much free "pages" it has from that point
        {
            list [l]+=1;
        }
        if(temp -> name != "FREE") // free "pages" counter stop if not "free"
        {
            l = i+1;
        }
        temp = temp->next;

    }

    for(int i = 0; i < 31; i++) //compares and find biggest posible sarting point
    {
    	if(list[i] >= numbPages ){
    		isSpace = false;
    	}

        if(list[i] >= min && list[i] >= numbPages && list[i] > 0){
            loc = i;
            min = list[i];
        }

    }
    if (isSpace){
    	return -1;
    }
    return loc;
}

void LinkedList::makeList(int size)
{

	head = new node;
	node * temp = head;
	for(int i = 0; i < size; i++){
		temp->name = "FREE";
		temp->next = new node;
		temp = temp->next;
	}
	temp->next = NULL;
}

void LinkedList::printList() //print out the whole list
{

	node * temp = head;
	string t;
	for(int i = 0; i < 32; i++){
		t = temp->name;
		cout << t << '\t';
		temp = temp->next;
		if((i+1)%8 == 0) {
			cout << endl;
		}
	}
}

int menu(void){

	int choice;								//creating menu and print the options to be selected
	cout << "\nChoice- ";
	cin >> choice;
	if (cin.fail()){
		cin.clear();
		cout << "Error bad input, please only enter a number choice."<< endl;
		cout << "Choice- ";
	    cin.ignore(256,'\n');
		cin >> choice;
	}
	while(choice > 5){
		cin.clear();
		cout << "Error bad input, please only enter a number less than 5."<< endl;
		cout << "Choice- ";
	    cin.ignore(256,'\n');
		cin >> choice;
	}
	return choice;

}

int LinkedList::fragCount()         // return how many fragments are tehre
{

	int count = 0;							//setting the count = to 0
	bool fragment = true;
	node * temp = head;
	while(temp != NULL){					// index whole linked list
		if(temp -> name == "FREE" && fragment == true){
			count++;
			fragment = false;				//if the node is free and boolean is true then add one to count

		}

		if(temp -> name != "FREE" && fragment == false){
			fragment = true;				//if the node value is not free then do not add to count, move to next node
		}

		temp = temp -> next;				//move to next value in list
	}
		return count;
		cout << count;
}

void LinkedList::insert(int loc, int number, int numbPages){

	node * temp = head;
	while (temp != NULL){
		if(temp -> name == ("P" + to_string(number))){		//if the node is not equal to program then move to the next
			cout << "Error, Program P" << number << " already running" << endl;
			return;
		}
		temp = temp->next;
	}
	temp = head;
	for (int i = 0; i < loc; i++) //move down the list till the location
	{
		temp = temp->next;
	}
	string nodeName = "P" + to_string(number);

	for(int i = 0; i < numbPages; i++){

		temp -> name = nodeName;				//set the node = program name when input is received
		temp = temp -> next;
	}
	cout << "Program P" << number << " added succesfully: " << numbPages << " page(s) used.\n";
}

void LinkedList::remove(int number){
	bool check = true;
	int killcount = 0;
	node * temp = head;
	while (temp != NULL){
		if(temp -> name == ("P" + to_string(number))){		//if the node is not equal to program then move to the next
			temp->name = "FREE";
			killcount += 1;
			check = false;
		}
		temp = temp->next;
	}
	if (check){
		cout << "Error, program P" <<number << " is not running." <<endl;
	}
	if (!check){
		cout << "Program P" << number << " succesfully killed, " << killcount << " page(s) reclaimed.\n";
	}
}
