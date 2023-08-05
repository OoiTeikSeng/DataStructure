#define     _CRT_SECURE_NO_WARNINGS
#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"
#include	<unordered_set>
#include	<iomanip>


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
	List LibStudent;
	
	string filename = "student.txt";
	ReadFile("student.txt", LibStudent, 4);

	
	//Law Wai Chun bool SearchStudent
	List studentList; // Created a List object.
	LibStudent stu;  // Return the student information using stu

	// Reading student data from the "student.txt" file and populating the studentList.
	ifstream inFile("student.txt");
	if (!inFile) {
		cout << "Error opening the file." << endl;
		return 1;
	}

	while (!inFile.eof()) {
		LibStudent student;
		char line[100];
		inFile.getline(line, sizeof(line));

		if (strstr(line, "Student Id = ") != nullptr) {
			sscanf(line, "Student Id = %s", student.id);
			inFile.getline(line, sizeof(line)); // Read the name, Skip the line.
			sscanf(line, "Name = %[^\n]", student.name);
			inFile.getline(line, sizeof(line)); // Read the course.
			sscanf(line, "course = %s", student.course);
			inFile.getline(line, sizeof(line)); // Read the phone number.
			sscanf(line, "Phone Number = %[^\n]", student.phone_no);

			// Assuming implemented here the code to populate the 'book' array.

			studentList.insert(student);
		}
	}

	inFile.close();

	// Search for a student in the linked list based on their id
	//Ask the user to enter the student ID to be searched	
	cout << "Enter the Student ID to search: ";
	cin >> stu.id;

	if (SearchStudent(&studentList, stu.id, stu)) {	
		cout << "\nStudent found!\n";
		stu.print(cout);	//Print the student information after return
	}
	else {
		cout << "\nStudent with ID " << stu.id << " not found.\n\n";
	}

	
	//Law Wai CHun bool computeAndDisplayStatistics
	//if user input the following input, then call this function
		computeAndDisplayStatistics(&studentList);


	cout << "\n\n";
	system("pause");
	return 0;
}
//Law Wai Chun SearchStudent function definition
bool SearchStudent(List* list, char* id, LibStudent& stu) {
	Node* current = list->head;
	while (current != nullptr) {
		if (strcmp(current->item.id, id) == 0) {
			stu = current->item;
			return true;	//If found return true and return the student information
		}
		current = current->next;
	}
	return false;
}

//Law Wai Chun computeAndDisplayStatistics function definition
bool computeAndDisplayStatistics(List* list) {
	if (list->empty()) {
		cout << "List is empty." << endl;
		return false;
	}

	// Initialize variables to store statistics for each course.
	int csStudents = 0, iaStudents = 0, ibStudents = 0, cnStudents = 0, ctStudents = 0;
	int csBooks = 0, iaBooks = 0, ibBooks = 0, cnBooks = 0, ctBooks = 0;
	int csOverdueBooks = 0, iaOverdueBooks = 0, ibOverdueBooks = 0, cnOverdueBooks = 0, ctOverdueBooks = 0;
	double csOverdueFine = 0.0, iaOverdueFine = 0.0, ibOverdueFine = 0.0, cnOverdueFine = 0.0, ctOverdueFine = 0.0;

	// Traverse the linked list to gather statistics for each course.
	Node* current = list->head;
	while (current != nullptr) {
		// Based on the course, update the corresponding statistics.
		if (strcmp(current->item.course, "CS") == 0) {
			csStudents++;
			csBooks += current->item.totalbook;
			csOverdueBooks += current->item.totalbook - current->item.total_fine;
			csOverdueFine += current->item.total_fine;
		}
		else if (strcmp(current->item.course, "IA") == 0) {
			iaStudents++;
			iaBooks += current->item.totalbook;
			iaOverdueBooks += current->item.totalbook - current->item.total_fine;
			iaOverdueFine += current->item.total_fine;
		}
		else if (strcmp(current->item.course, "IB") == 0) {
			ibStudents++;
			ibBooks += current->item.totalbook;
			ibOverdueBooks += current->item.totalbook - current->item.total_fine;
			ibOverdueFine += current->item.total_fine;
		}
		else if (strcmp(current->item.course, "CN") == 0) {
			cnStudents++;
			cnBooks += current->item.totalbook;
			cnOverdueBooks += current->item.totalbook - current->item.total_fine;
			cnOverdueFine += current->item.total_fine;
		}
		else if (strcmp(current->item.course, "CT") == 0) {
			ctStudents++;
			ctBooks += current->item.totalbook;
			ctOverdueBooks += current->item.totalbook - current->item.total_fine;
			ctOverdueFine += current->item.total_fine;
		}

		current = current->next;
	}

	// Print the statistics in table format.
	cout << left << setw(10) << "Course" << setw(20) << "Number of Students" << setw(23) << "Total Books Borrowed"
		<< setw(23) << "Total Overdue Books" << setw(25) << "Total Overdue Fine (RM)" << endl;

	cout << right << setw(4) << "CS" << setw(15) << csStudents << setw(22) << csBooks << setw(21) << csOverdueBooks
		<< setw(28) << setprecision(2) << fixed << csOverdueFine << endl;

	cout << right << setw(4) << "IA" << setw(15) << iaStudents << setw(22) << iaBooks << setw(21) << iaOverdueBooks
		<< setw(28) << setprecision(2) << fixed << iaOverdueFine << endl;

	cout << right << setw(4) << "IB" << setw(15) << ibStudents << setw(22) << ibBooks << setw(21) << ibOverdueBooks
		<< setw(28) << setprecision(2) << fixed << ibOverdueFine << endl;

	cout << right << setw(4) << "CN" << setw(15) << cnStudents << setw(22) << cnBooks << setw(21) << cnOverdueBooks
		<< setw(28) << setprecision(2) << fixed << cnOverdueFine << endl;

	cout << right << setw(4) << "CT" << setw(15) << ctStudents << setw(22) << ctBooks << setw(21) << ctOverdueBooks
		<< setw(28) << setprecision(2) << fixed << ctOverdueFine << endl;

	return true;
}
