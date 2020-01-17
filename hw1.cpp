#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;
string infilename;
string outfilename;
double trueBudget;


struct nodeType
{
	string info;
	double cost;
	nodeType *link;
};
nodeType *first, *newNode, *last, *tempNode, *tempNode2;

nodeType* buildingList();
void print();
double budgetCheck();
void sortByNumber();
void removeHighCost();
void deleteNode();
double totalCheck();
void sortByName();
bool digits(const std::string& a);

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    infilename = am.get("A");
    outfilename = am.get("C");
	buildingList();
	sortByNumber();
	removeHighCost();
	sortByName();
	print();
	return 0;
}

nodeType* buildingList() {
	string filename;
	string budget;
	string name;
	string num;

	//cout << " What is the name of file?" << endl;
	//cin >> filename;
	ifstream inFile;
	inFile.open(infilename);
	getline(inFile, budget);
	if (atof(budget.c_str())>0) {
		trueBudget = stof(budget);
	}
	else {
		budget = '0';
		trueBudget = stof(budget.c_str());
	}
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			getline(inFile, name, ',');//move files into vars
			getline(inFile, num);
			if (digits(name) == 1) {
				return 0;
			}
			if (atof(name.c_str()) > 0) {
				//cout << "Skipped because of no name or negative number" << endl;
			}
			if (atof(num.c_str()) < 0 || strlen(name.c_str()) == 0) {//checks if there is negative or no name
																	 //cout << "Skipped because of no name or negative number" << endl;
			}
			else {
				newNode = new nodeType;
				newNode->cost = atof(num.c_str());
				newNode->info = name.c_str();
				newNode->link = NULL;
				if (first == NULL) {
					first = newNode;
					last = newNode;

				}
				else {
					last->link = newNode;
					last = newNode;
				}
			}
		}
		return first;
	}
}

double budgetCheck() {//Makes sure the cost is below budget
	if (trueBudget != 0) {
		tempNode2 = first;
		double data = 0;
		while (data < trueBudget && tempNode2 != NULL) {
			data = tempNode2->cost + data;
			tempNode2 = tempNode2->link;
			if (tempNode2 == NULL)
				return data;
		}
		return data;
	}
	else {
		return 0;
	}
}

void sortByNumber() {//same as sorty function from above
	nodeType *lastIO;
	nodeType *firstOOO;
	nodeType *current;
	nodeType *trailz;
	lastIO = first;
	if (first == NULL) {
		//cerr << "Cannot sort an empty list" << endl;
	}
	else if (first->link == NULL) {
		//cout << "The list if of length 1"
		//<< "it is already in order." << endl;
	}
	else {
		while (lastIO->link != NULL) {
			firstOOO = lastIO->link;
			if (firstOOO->cost < first->cost) {
				lastIO->link = firstOOO->link;
				firstOOO->link = first;
				first = firstOOO;
				first->info = firstOOO->info;
			}
			else {
				trailz = first;
				current = first->link;
				while (current->cost < firstOOO->cost) {
					trailz = current;
					trailz->cost = current->cost;
					current = current->link;
				}
				if (current != firstOOO) {
					lastIO->link = firstOOO->link;
					firstOOO->link = current;
					trailz->link = firstOOO;
				}
				else {
					lastIO = lastIO->link;
				}
			}
		}
	}
}

void removeHighCost() {//remove the highest cost
	if (trueBudget != 0) {
		while (budgetCheck() > trueBudget) {
			deleteNode();
		}
	}
	else {
		return;
	}
}

void deleteNode() {//deletes the last node
	if (first == NULL) {
		return;
	}
	if (first->link == NULL) {
		delete first;
		first = NULL;
		return;
	}
	nodeType *currNode;
	currNode = first;
	while (currNode->link && currNode->link->link != NULL) {
		currNode = currNode->link;
	}
	delete currNode->link;
	currNode->link = NULL;
}

double totalCheck() {//check the total of the after sorting
	nodeType * tempNode3;
	tempNode3 = first;
	double tot = 0;
	if (trueBudget != 0) {
		while (tot < trueBudget && tempNode3 != NULL) {
			tot = tempNode3->cost + tot;
			tempNode3 = tempNode3->link;
			if (tempNode3 == NULL)
				return tot;
		}
		return tot;
	}
	else {
		return 0;
	}
}
void sortByName() {//sames as sortyhigh by for alphabetical
	nodeType *lastIn;
	nodeType *firstOut;
	nodeType *current;
	nodeType *trailerpb;
	lastIn = first;
	if (first == NULL) {
		//cerr << "Cannot sort an empty list" << endl;
	}
	else if (first->link == NULL) {
		//cout << "The list if of length 1"
		//<< "it is already in order." << endl;
	}
	else {
		while (lastIn->link != NULL) {
			firstOut = lastIn->link;
			if (firstOut->info < first->info) {
				lastIn->link = firstOut->link;//move before first
				firstOut->link = first;
				first = firstOut;
				first->cost = firstOut->cost;
			}
			else {
				trailerpb = first;//trailer to first
				current = first->link;//make second node
				while (current->info < firstOut->info) {
					trailerpb = current;//advance trail
					trailerpb->cost = current->cost;
					current = current->link;//advance current
				}
				if (current != firstOut) {//iserts firstOut between current and trail
					lastIn->link = firstOut->link;
					firstOut->link = current;
					trailerpb->link = firstOut;
				}
				else {//firstout in first place
					lastIn = lastIn->link;
				}
			}
		}
	}
}

bool digits(const std::string& a)
{
	return isdigit(a[0]);
}

void print() {
    ofstream myfizzle;
    myfizzle.open(outfilename);
	if (trueBudget != 0) {
		tempNode = first;
		int itemcount = 0;
		while (tempNode != NULL) {
			cout << tempNode->info << ", " << fixed << setprecision(2) << tempNode->cost << endl;
			myfizzle << tempNode->info << ", " << fixed << setprecision(2) << tempNode->cost << endl;
			tempNode = tempNode->link;
			itemcount++;
		}
		if (itemcount != 0) {
			cout << endl;
			myfizzle << endl;
			cout << "Number of items: " << itemcount << endl;
			myfizzle << "Number of items: " << itemcount << endl;
			cout << "Cost: " << totalCheck() << endl;
			myfizzle << "Cost: " << totalCheck() << endl;
		}
	}
	else {
		return;
	}
    myfizzle.close();
}
