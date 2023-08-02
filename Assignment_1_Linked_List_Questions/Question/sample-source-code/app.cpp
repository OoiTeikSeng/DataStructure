#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"


using namespace std;


bool ReadFile(const std::string& filename , List& studentRecord, int lineNumber){
	LibStudent studentDetail;
	
	ifstream file(filename);
	
	if(!file.is_open()) {
		cout <<"Fail to open the file: " << filename << endl;
		return false;
	}

	string line;
	int lineAmount = 1;
	while (getline(file, line) && lineAmount <= lineNumber) {
		//Insert each record into a a node
		if(!studentRecord.insert(1, studentDetail)){
			cout << "Fail to insert student details" << lineNumber << "into the record" << endl;
			file.close();
			return false;
		}
		lineAmount++;
	}
	file.close();
	cout <<"Student details successfully recroded" << endl;
	return true;
}
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




