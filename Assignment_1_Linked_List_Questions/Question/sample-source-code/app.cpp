#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"


using namespace std;


bool ReadFile(string "student.txt", List *list){
	//open file
	ifstream file("student.txt");
	if(!file){
		cout <<"File not found!"<< endl;
		return false;
	}
	//read file into linked list
	while(!file.eof()){
		int num;
		file >> num;
		list->push_back(num);
	}
	file.close();
	return true;

};
bool DeleteRecord(List *, char *);
bool Display(List, int, int);
bool InsertBook(string, List *);
bool SearchStudent(List *, char *id, LibStudent &);
bool computeAndDisplayStatistics(List *);
bool printStuWithSameBook(List *, char *);
bool displayWarnedStudent(List *, List *, List *);
int menu();


int main() {
	


	

	cout << "\n\n";
	system("pause");
	return 0;
}




