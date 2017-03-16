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
    if (argc !=2 ){ //if is not "pa2.cpp" + "conditon", quit
    	cout << "Error, not a proper argument. Please try again using \"best\" or \"worst\"." <<endl;
    	return 0;
    }
    string algorithm;
	algorithm = argv[1]; //string so easier to manage
	if (algorithm != "best" && algorithm != "worst") //make sure the "conditon" fit is either best or worst
	{
		cout << "Error, not a proper argument. Please try again using \"best\" or \"worst\"." << endl;
		return 0;
	}
	cout << endl << "Using " << algorithm << " fit algorithm" << endl;

	LinkedList Free;

	Free.makeList(32); //make the list

	int number;
	int numbPages;
	int loc;
	cout << "1. Add Program\n";
	cout << "2. Kill Program\n";
	cout << "3. Fragmentation\n";
	cout << "4. Print\n";
	cout << "5. Exit";


	while(choice != 5){  //while not quiting

		choice = menu();				//which choice they want to do

		switch(choice){
			case 1:	cout << "\nProgram Name- P";			//if input is to add call the insertion with "fit" method add programs
						cin >> number;
						if (cin.fail()){  //if input is not a number
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

			case 2:	cout << "Program Name: P";				//if input is to kill program then call remove method
					cin >> number;
					if (cin.fail()){                 //if input is nto a number
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

			case 5:	cout << "Program Exit\n";   //exit program
						break;
		}

	}
}
int LinkedList::bestins(LinkedList Free, int numbPages) //returns the location for best fit to insert
{

    head = Free.getHead();
    node * temp = head;
    int list [32];    //make an array, each location array corsponding to each pages in the linkedlist
    int loc = 0;
    int l = 0;
    int max = 100;
    bool isSpace = true; //bool see if there is enough space
    for (int i = 0; i <32; i++) //set the array list to 0
    {
        list [i]= 0;
    }

    for (int i = 0; i < 32; i++)
    {
        if (temp -> name == "FREE")  //the array store how much free "pages" it has from that point
        {
            list [l]+=1;
        }
        if(temp -> name != "FREE") // free "pages" counter move to next page if not "free"
        {
            l = i+1;
        }
        temp = temp->next;

    }
    //following is just printing out the array for debuging purpose
    // for (int i = 0; i < 32; i++){
    // 	cout << list [i] << '\t';
    // 	if((i+1)%8==0){
    // 		cout << '\n';
    // 	}
    // }
    // cout << '\n';

    for(int i = 0; i < 32; i++) //compares and find smallest posible sarting point
    {
    	if(list[i] >= numbPages ){ //if non of the free pages are big enough for the method need
    		isSpace = false;
    	}

        if(list[i] < max && list[i] >= numbPages && list[i] > 0){ //go down list find smallest free page
            loc = i;
            max = list[i];
        }

    }
    if (isSpace){
    	return -1; //reutnr -1 so know not enough space in whole linkedlist
    }
    return loc; //return locaiton where to start
}

int LinkedList::worstins(LinkedList Free, int numbPages) //give the location for worst fit to insert
{
    //basic much same as bestins but just there last part during compares different
    head = Free.getHead();
    node * temp = head;
    int list [32];
    int loc = 0;
    int l = 0;
    int min = 0;
    bool isSpace = true;
    for (int i = 0; i < 32; i++) //set the list to 0
    {
        list [i]= 0;
    }

    for (int i = 0; i < 32; i++)
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

    for(int i = 0; i < 32; i++) //compares and find biggest posible sarting point
    {
    	if(list[i] >= numbPages ){
    		isSpace = false;
    	}

        if(list[i] > min && list[i] >= numbPages && list[i] > 0){ //find biggest free space
            loc = i;
            min = list[i];
        }

    }
    if (isSpace){
    	return -1;
    }
    return loc;
}

void LinkedList::makeList(int size) // make the list of FREEs
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

int menu(void){ //take in the choice and see if is correct

	int choice;
	cout << "\nChoice- ";
	cin >> choice;
	if (cin.fail()){
		cin.clear();
		cout << "Error bad input, please only enter a number choice."<< endl;
		cout << "Choice- ";
	    cin.ignore(256,'\n');
		cin >> choice;
	}
	while(choice > 5){ //if choice picked is not on the menu
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
	while(temp != NULL){					// go through whole linkedlist
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

void LinkedList::insert(int loc, int number, int numbPages){ //insert program starting from the location given

	node * temp = head;
	while (temp != NULL){
		if(temp -> name == ("P" + to_string(number))){		//check if program is already running
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

		temp -> name = nodeName;				//set the node = program name as given
		temp = temp -> next;
	}
	cout << "Program P" << number << " added succesfully: " << numbPages << " page(s) used.\n";
}

void LinkedList::remove(int number){ //go through the whole list and remvoe the program given
	bool check = true;
	int killcount = 0;
	node * temp = head;
	while (temp != NULL){
		if(temp -> name == ("P" + to_string(number))){		//if the node is not equal to program then move to the next
			temp->name = "FREE";
			killcount += 1;
			check = false;// so if a page is freed, so we know we removed osmthing
		}
		temp = temp->next;
	}
	if (check){ //if we didn't remove anything, then progarm is not running
		cout << "Error, program P" <<number << " is not running." <<endl;
	}
	if (!check){ //if we removed stuff, the program was running
		cout << "Program P" << number << " succesfully killed, " << killcount << " page(s) reclaimed.\n";
	}
}
