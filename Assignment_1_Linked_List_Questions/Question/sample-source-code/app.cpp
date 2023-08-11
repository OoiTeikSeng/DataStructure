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
#include <iomanip>


using namespace std;
ifstream in;

//Ooi Teik Seng read file function
bool ReadFile(string filename, List* list) {
	LibStudent studentRecord;
	ifstream inFile(filename);

	if (!inFile) {
		std::cout << "Error opening file " << filename << endl;
		return false;
	}
	string studID, studName, studCourse, studPhone;
	string line;
	int pos;
	while (getline(inFile, line)) {


		if (line.empty()) continue;
		if (line[0] == 'I') {
			pos = line.find('=');
			studID = line.substr(pos + 2);
			std::cout << studID << endl;
			strcpy(studentRecord.id, studID.c_str());
		}
		else if (line[0] == 'N') {
			pos = line.find('=');
			studName = line.substr(pos + 2);
			strcpy(studentRecord.name, studName.c_str());
		}
		else if (line[0] == 'C') {
			pos = line.find('=');
			studCourse = line.substr(pos + 2);
			strcpy(studentRecord.course, studCourse.c_str());
		}
		else if (line[0] == 'P') {
			pos = line.find('=');
			studPhone = line.substr(pos + 2);
			strcpy(studentRecord.phone_no, studPhone.c_str());
			
			bool duplicate = false;
			for (int i = 1; i <= list->size(); i++) {
				LibStudent existingStudent;
				list->get(i, existingStudent);
				if (studentRecord.compareName1(existingStudent)) {
					duplicate = true;
					break;
				}
			}

			if (duplicate) {
				cout << "Duplicate record for " << studName << ", will be skipped." << endl;
				continue;
			}

			bool successInsert = list->insert(studentRecord);
			if (successInsert) {
				std::cout << "Student " << studentRecord.name << " has been recorded" << endl;
			}
		}
	}
	inFile.close();
	std::cout << "Total recorded: " << list->count << endl;
	return true;
};

// ng jian nian function to find and delete students based on student id

bool isEmpty(List*);
bool isEmpty(List* list) {
	return list->count == 0;
}
bool DeleteRecord(List* list, char* student_id) {
	/*if (isEmpty(list)) {
		return false; // list is empty
	}
	// ng jian nian function to find borrowed due date
	for (int i = 0; i < list->count; i++) {
		LibStudent* student = &list->students[i];

		if (strcmp(student_id, student->id) == 0) {
			// Delete the student by shifting remaining elements
			for (int j = i; j < list->count - 1; j++) {
				list->students[j] = list->students[j + 1];
			}
			list->count--; // Decrement the count to reflect the deletion
			return true; // Delete successful
		}
	}
*/
	return false; // Student not found
}

//Lim Kai Xian's Display function
bool Display(List* list, int source, int detail) {
	/*// Check if the list is empty
	if (list->head == nullptr) {
		cout << "List is empty." << endl;
		return false;
	}

	// Check the output source
	ofstream outputFile;
	if (source == 1) {
		outputFile.open("student_booklist.txt");
		if (!outputFile.is_open()) {
			cout << "Failed to open the output file." << endl;
			return false;
		}
	}

	// Traverse the list and print the details
	Node* current = list->head;
	while (current != nullptr) {
		if (source == 1) {
			outputFile << "STUDENT " << current << "\n\n";
		}
		else if (source == 2) {
			cout << "STUDENT " << current << "\n\n";
		}

		// Print student information
		if (detail == 1) {
			if (source == 1) {
				outputFile << "Name: " << current->item.name << "\n";
				outputFile << "Id: " << current->item.id << "\n";
				outputFile << "Course: " << current->item.course << "\n";
				outputFile << "Phone No: " << current->item.phone_no << "\n";
				outputFile << "Total Fine: RM" << current->item.total_fine << "\n\n";
			}
			else if (source == 2) {
				cout << "Name: " << current->item.name << "\n";
				cout << "Id: " << current->item.id << "\n";
				cout << "Course: " << current->item.course << "\n";
				cout << "Phone No: " << current->item.phone_no << "\n";
				cout << "Total Fine: RM" << current->item.total_fine << "\n\n";
			}
		}
		else if (detail == 2) {
			if (source == 1) {
				outputFile.open("student_list.txt");
				outputFile << "Name: " << current->item.name << "\n";
				outputFile << "Id: " << current->item.id << "\n";
				outputFile << "Course: " << current->item.course << "\n";
				outputFile << "Phone No: " << current->item.phone_no << "\n";
				outputFile << "Total Fine: RM" << current->item.total_fine << "\n\n";
				outputFile.close();
			}
			else if (source == 2) {
				cout << "Name: " << current->item.name << "\n";
				cout << "Id: " << current->item.id << "\n";
				cout << "Course: " << current->item.course << "\n";
				cout << "Phone No: " << current->item.phone_no << "\n";
				cout << "Total Fine: RM" << current->item.total_fine << "\n\n";
			}
		}

		// Print book information
		if (detail == 1) {
			if (source == 1) {
				outputFile << "BOOK LIST: \n\n";
			}
			else if (source == 2) {
				cout << "BOOK LIST: \n\n";
			}

			for (int i = 0; i < list->count; i++) {
				LibBook book = current->item[i];
				if (source == 1) {
					outputFile << "Book " << i + 1 << "\n";
					outputFile << "Title: " << book.title << "\n";
					outputFile << "Author: " << book.author << "\n";
					outputFile << "Publisher: " << book.publisher << "\n";
					outputFile << "Year Published: " << book.yearPublished << "\n";
					outputFile << "ISBN: " << book.ISBN << "\n";
					outputFile << "Call Number: " << book.callNum << "\n";
					//outputFile << "Borrow Date: " << book.borrow.day << "/" << book.borrow.month << "/" << book.borrow.year << "\n";
					//outputFile << "Due Date: " << book.due.day << "/" << book.due.month << "/" book.due.year << "\n";
					outputFile << "Fine: RM" << book.fine << "\n\n";
				}
				else if (source == 2) {
					cout << "Book " << i + 1 << "\n";
					cout << "Title: " << book.title << "\n";
					cout << "Author: " << book.author << "\n";
					cout << "Publisher: " << book.publisher << "\n";
					cout << "Year Published: " << book.yearPublished << "\n";
					cout << "ISBN: " << book.ISBN << "\n";
					cout << "Call Number: " << book.callNum << "\n";
					//cout << "Borrow Date: " << book.borrow.day << "/" << book.borrow.month << "/" << book.borrow.year << "\n";
					//cout << "Due Date: " << book.due.day << "/" << book.due.month << "/" book.due.year << "\n";
					cout << "Fine: RM" << book.fine << "\n\n";
				}
			}
		}

		if (source == 1) {
			outputFile << "*****************************************************************************\n\n";
		}
		else if (source == 2) {
			cout << "*****************************************************************************\n\n";
		}

		current = current->next;
	}

	if (source == 1) {
		outputFile.close();
	}*/

	return true;
}
bool InsertBook(string filename, List* list) {
	LibBook book;               //temporary LibBook storage
	ifstream inFile(filename);
	if (!inFile) {
		cout << "File can't be opened. Please try again." << endl;
		return false;
	}

	char stuID[10];
	string line, author, title, publisher, ISBN, publishedYear, callNum, borrowDate, dueDate;
	while (inFile >> stuID) {
		string tempAuthor;
		inFile >> author;
		inFile >> title;
		inFile >> publisher;
		inFile >> ISBN;
		inFile >> publishedYear;
		inFile >> callNum;
		inFile >> borrowDate;
		inFile >> dueDate;
		for (int i = 0; i < title.length(); i++) {
			if (title[i] == '_') {
				title[i] = ' ';
			}
		}
		for (int i = 0; i < author.length(); i++) {
			if (author[i] == '_') {
				author[i] = ' ';
			}
		}

		int startPos = 0, endPos = 0;
		endPos = author.find('/');
		int authorCount = 0;

		while (endPos != string::npos) {
			book.author[authorCount] = new char[strlen(author.substr(startPos, endPos - startPos).c_str()) + 1];
			strcpy(book.author[authorCount], author.substr(startPos, endPos - startPos).c_str());
			startPos = endPos + 1;
			endPos = author.find('/', startPos);
			authorCount++;
		}
		if (authorCount == 0) {
			book.author[0] = new char[strlen(author.c_str()) + 1];
			strcpy(book.author[0], author.c_str());
			authorCount++;
		}
		else {
			book.author[authorCount] = new char[strlen(author.substr(startPos).c_str()) + 1];
			strcpy(book.author[authorCount], author.substr(startPos).c_str());
			authorCount++;
		}
		int borrowDay, borrowMonth, borrowYear, pos1, pos2;
		int dueDay, dueMonth, dueYear;
		//Date borrow function
		pos1 = borrowDate.find('/');
		pos2 = borrowDate.find('/', pos1 + 1);
		borrowDay = stoi(borrowDate.substr(0, pos1));
		borrowMonth = stoi(borrowDate.substr(pos1 + 1, pos2 - pos1 - 1));
		borrowYear = stoi(borrowDate.substr(pos2 + 1));
		book.borrow.day = borrowDay;
		book.borrow.month = borrowMonth;
		book.borrow.year = borrowYear;

		//Date due function
		pos1 = dueDate.find('/');
		pos2 = dueDate.find('/', pos1 + 1);
		dueDay = stoi(dueDate.substr(0, pos1));
		dueMonth = stoi(dueDate.substr(pos1 + 1, pos2 - pos1 - 1));
		dueYear = stoi(dueDate.substr(pos2 + 1));
		book.due.day = dueDay;
		book.due.month = dueMonth;
		book.due.year = dueYear;


		double fine;
		if (book.due.month < 3 && book.due.day < 29) {
			fine = (29 - book.due.day) * 0.50;
			fine = fine + (29 * 0.50);
			book.fine = fine;
		}

		else if (book.due.day <= 29 && book.due.month == 3)
		{
			fine = (29 - book.due.day) * 0.50;
			book.fine = fine;
		}

		else {
			book.fine = 0;
		}


		strcpy(book.title, title.c_str());
		strcpy(book.publisher, publisher.c_str());
		strcpy(book.ISBN, ISBN.c_str());
		book.yearPublished = stoi(publishedYear);
		strcpy(book.callNum, callNum.c_str());

		Node* cur;
		cur = list->head;
		for (int i = 1; i <= list->size(); i++) {

			if (strcmp(stuID, cur->item.id) == 0) {
				int bookCount = cur->item.totalbook;
				for (int i = 0; i < authorCount; i++) {
					cur->item.book[bookCount].author[i] = new char[strlen(book.author[i])];
					strcpy(cur->item.book[bookCount].author[i], book.author[i]);
				}
				strcpy(cur->item.book[bookCount].title, book.title);
				strcpy(cur->item.book[bookCount].publisher, book.publisher);
				strcpy(cur->item.book[bookCount].ISBN, book.ISBN);
				strcpy(cur->item.book[bookCount].callNum, book.callNum);
				cur->item.book[bookCount].borrow.day = book.borrow.day;
				cur->item.book[bookCount].borrow.month = book.borrow.month;
				cur->item.book[bookCount].borrow.year = book.borrow.year;
				cur->item.book[bookCount].due.day = book.due.day;
				cur->item.book[bookCount].due.month = book.due.month;
				cur->item.book[bookCount].due.year = book.due.year;
				cur->item.book[bookCount].fine = book.fine;
				cur->item.totalbook += 1;
				cur->item.calculateTotalFine();
				break;              //found correct student then break; 
			}
			else {
				cur = cur->next;
			}
		}
	}
	inFile.close();
	cout << "Books inserted successfully to student list." << endl;
	return true;
}

//Law Wai Chun SearchStudent function definition
bool SearchStudent(List* list, char* id, LibStudent& stu) {
	Node* current = list->head;
	while (current != nullptr) {
		if (strcmp(current->item.id, id) == 0) {	//If found, return true
			stu = current->item;	 //return the student information using stu
			return true;
		}
		current = current->next;
	}
	return false;
}



//Law Wai Chun computeAndDisplayStatistics function definition
bool computeAndDisplayStatistics(List* list) {
	// Check if the list is empty
	if (list->empty()) {
		cout << "List is empty." << endl;
		return false;    // Return false for an empty list
	}

	// Initialize variables to store statistics for each course.
	int csStudents = 0, iaStudents = 0, ibStudents = 0, cnStudents = 0, ctStudents = 0;
	int csBooks = 0, iaBooks = 0, ibBooks = 0, cnBooks = 0, ctBooks = 0;
	int csOverdueBooks = 0, iaOverdueBooks = 0, ibOverdueBooks = 0, cnOverdueBooks = 0, ctOverdueBooks = 0;
	double csOverdueFine = 0.0, iaOverdueFine = 0.0, ibOverdueFine = 0.0, cnOverdueFine = 0.0, ctOverdueFine = 0.0;

	// Traverse the linked list to gather statistics for each course.
	Node* current = list->head;
	while (current != nullptr) {
		int overdueBooks = 0;  // Initialize the count of overdue books for the current student

		// Count the number of overdue books for the current student
		for (int i = 0; i < current->item.totalbook; i++) {
			if (current->item.book[i].fine > 0.0) {
				overdueBooks++;
			}
		}
		// Update the statistics based on the student's course and overdue books count
		if (strcmp(current->item.course, "CS") == 0) {
			csStudents++;
			csBooks += current->item.totalbook;
			csOverdueBooks += overdueBooks;
			csOverdueFine += current->item.total_fine;
		}
		else if (strcmp(current->item.course, "IA") == 0) {
			iaStudents++;
			iaBooks += current->item.totalbook;
			iaOverdueBooks += overdueBooks;
			iaOverdueFine += current->item.total_fine;
		}
		else if (strcmp(current->item.course, "IB") == 0) {
			ibStudents++;
			ibBooks += current->item.totalbook;
			ibOverdueBooks += overdueBooks;
			ibOverdueFine += current->item.total_fine;
		}
		else if (strcmp(current->item.course, "CN") == 0) {
			cnStudents++;
			cnBooks += current->item.totalbook;
			cnOverdueBooks += overdueBooks;
			cnOverdueFine += current->item.total_fine;
		}
		else if (strcmp(current->item.course, "CT") == 0) {
			ctStudents++;
			ctBooks += current->item.totalbook;
			ctOverdueBooks += overdueBooks;
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

//Yong Xin Qi's printStuWithSameBook
bool printStuWithSameBook(List* list, const char* callNum) {
	// Check if the list is empty
	if (list->empty()) {
		cout << "The list is empty." << endl;
		return false;
	}

	bool found = false;

	Node* currentNode = list->head(0, LibStudent()); // Adjust the argument based on your implementation
	while (currentNode != nullptr) {
		LibStudent student = currentNode->item;

		for (int i = 0; i < student.totalbook; ++i) {
			LibBook book = student.book[i];

			if (strcmp(book.callNum, callNum) == 0) {
				if (!found) {
					cout << "There are students who borrowed the book with call number " << callNum << " as shown below:" << endl;
					found = true;
				}

				cout << "Student Id: " << student.id << endl;
				cout << "Name: " << student.name << endl;
				cout << "Course: " << student.course << endl;
				cout << "Phone Number: " << student.phone_no << endl;
				cout << "Borrow Date: " << book.borrow.day << "/" << book.borrow.month << "/" << book.borrow.year << endl;
				cout << "Due Date: " << book.due.day << "/" << book.due.month << "/" << book.due.year << endl;
				cout << endl;
			}
		}

		currentNode = currentNode->next;
	}

	if (!found) {
		cout << "No student borrowed the book with call number " << callNum << "." << endl;
	}

	return true;
}


//Yong Xin Qi's displayWarnedStu
bool displayWarnedStudent(List* list, List* type1, List* type2) {
	// Check if the list is empty
	if (list->empty()) {
		cout << "The list is empty." << endl;
		return false;
	}

	Node* currentNode = list->head(0, LibStudent());
	while (currentNode != nullptr) {
		LibStudent student = currentNode->item;
		int overdueBooks = 0;
		double totalFine = 0.0;

		// Calculate the number of overdue books and total fine for the student
		// Assuming you have a function to calculate overdue books and fine for each student, here's an example:
		// You need to implement the function calculateOverdueBooksAndFine() in the LibStudent struct
		student.calculateTotalFine();

		if (overdueBooks > 2 && totalFine > 50.0) {
			// Copy the student to type1 list
			type1->insert(student);
		}
		else if (overdueBooks == student.totalbook && totalFine > 50.0) {
			// Copy the student to type2 list
			type2->insert(student);
		}

		currentNode = currentNode->next;
	}

	// Display the students in type1 list with their book information
	cout << "Type 1 Warning (More than 2 books overdue for >= 10 days):" << endl;
	Node* type1Node = type1->head(0, LibStudent());
	while (type1Node != nullptr) {
		LibStudent student = type1Node->item;
		cout << "Student ID: " << student.id << endl;
		cout << "Name: " << student.name << endl;
		cout << "Course: " << student.course << endl;
		cout << "Phone Number: " << student.phone_no << endl;
		int overdueBooks = 0;
		double totalFine = 0.0;
		cout << "Overdue Books:" << overdueBooks << endl; // Display overdue book count
		cout << "Total Fine: RM" << setprecision(2) << fixed << totalFine << endl; // Display total fine

		cout << "Books Borrowed:" << endl;
		for (int i = 0; i < student.totalbook; ++i) {
			student.book[i].print(cout); // Display book details, including due date
			cout << endl;

			type1Node = type1Node->next;
		}

		// Display the students in type2 list with their book information
		cout << "Type 2 Warning (Total fine > RM50.00 and every book is overdue):" << endl;
		Node* type2Node = type2->head(0, LibStudent());
		while (type2Node != nullptr) {
			LibStudent student = type2Node->item;
			cout << "Student ID: " << student.id << endl;
			cout << "Name: " << student.name << endl;
			cout << "Course: " << student.course << endl;
			cout << "Phone Number: " << student.phone_no << endl;
			cout << "Overdue Books:" << overdueBooks << endl; // Display overdue book count
			cout << "Total Fine: RM" << setprecision(2) << fixed << totalFine << endl; // Display total fine

			cout << "Books Borrowed:" << endl;
			for (int i = 0; i < student.totalbook; ++i) {
				student.book[i].print(cout); // Display book details, including due date
				cout << endl;

				type2Node = type2Node->next;
			}



			return true;
		}
	}
}

//Lim Kai Xian's menu function
int menu() {
	int choice;
	std::cout << "Menu\n";
	std::cout << endl;
	std::cout << "1. Read file." << endl;
	std::cout << "2. Delete student." << endl;
	std::cout << "3. Search student." << endl;
	std::cout << "4. Insert book." << endl;
	std::cout << "5. Display output." << endl;
	std::cout << "6. Compute and Display Statistics." << endl;
	std::cout << "7. Student with Same Book." << endl;
	std::cout << "8. Display Warned Student." << endl;
	std::cout << "9. Exit." << endl;
	std::cout << "Enter your choice: ";
	cin >> choice;
	return choice;
}

//Law Wai Chun extra function ReadStudentData
	// Function to read student data from the file and populate the list
void ReadStudentData(List& studentList, const char* filename) {
	ifstream inFile(filename);
	if (!inFile) {
		cout << "Error opening the file." << endl;
		return;
	}

	bool inBookList = false; // Flag to indicate whether you're inside a student's book list
	LibStudent student; // Current student being populated

	while (!inFile.eof()) {
		char line[100];
		inFile.getline(line, sizeof(line));

		// Check for STUDENT tag to start parsing a new student's data
		if (strstr(line, "STUDENT") != nullptr) {
			if (student.totalbook > 0) {
				studentList.insert(student); // Insert the populated student into the list
			}
			inBookList = false; // Reset the inBookList flag
			student = LibStudent(); // Reset the student object
		}

		// Parse student's data from different lines
		if (strstr(line, "Name:") != nullptr) {
			sscanf(line, "Name: %[^\n]", student.name);
		}
		else if (strstr(line, "Id:") != nullptr) {
			sscanf(line, "Id: %s", student.id);
		}
		else if (strstr(line, "Course:") != nullptr) {
			sscanf(line, "Course: %s", student.course);
		}
		else if (strstr(line, "Phone No:") != nullptr) {
			sscanf(line, "Phone No: %[^\n]", student.phone_no);
		}
		else if (strstr(line, "Total Fine:") != nullptr) {
			double totalFine;
			sscanf(line, "Total Fine: RM%lf", &totalFine);
			student.total_fine = totalFine;
		}

		// Check for BOOK LIST tag to start parsing a student's book list
		else if (strstr(line, "BOOK LIST:") != nullptr) {
			inBookList = true; // Set the inBookList flag to true
			student.totalbook = 0; // Reset the totalbook count for the current student
		}

		// Parse book data if inBookList flag is true
		else if (inBookList && strstr(line, "Title:") != nullptr) {
			LibBook book;

			// ... Skipping other book data parsing ...
			inFile.getline(line, sizeof(line)); // Read Title
			inFile.getline(line, sizeof(line)); // Read Author(s)
			inFile.getline(line, sizeof(line)); // Read Publisher
			inFile.getline(line, sizeof(line)); // Read Year Published
			inFile.getline(line, sizeof(line)); // Read ISBN
			inFile.getline(line, sizeof(line)); // Read Call Number
			inFile.getline(line, sizeof(line)); // Read Borrow Date
			inFile.getline(line, sizeof(line)); // Read Due Date

			// Parse fine amount
			double fineAmount;
			sscanf(line, "Fine: RM%lf", &fineAmount);
			book.fine = fineAmount;

			// Now add the populated book to the student's book array
			student.book[student.totalbook] = book;
			student.totalbook++;
		}
	}
	// Insert the last student outside the loop
	if (student.totalbook > 0) {
		studentList.insert(student);
	}

	inFile.close();
}



int main() {
	List studentList;
	LibStudent currentStudent;

	int choice;
	do {
		choice = menu();

		if (choice == 1){
			//User enter 1 to read student.txt to enter into list
				//Ooi Teik Seng bool ReadFile
			bool successRead = ReadFile("student.txt", &studentList);
		}
		else if (choice == 2) {	
			char student_id[10];
			std::cout << "Enter student ID to delete: ";
			std::cin >> student_id;
			bool deleted = DeleteRecord(&studentList, student_id);
			if (deleted) {
				std::cout << "Student with ID " << student_id << " deleted." << std::endl;
			}
			else {
				std::cout << "Student with ID " << student_id << " not found." << std::endl;
			}
			}
		else if (choice == 3) {
			//User enter 3 to SEARCH STUDENT
			//Law Wai Chun bool SearchStudent
			List studentList; // Created a List object.
			LibStudent stu;  // Return the student information using stu
			const char* filename = "student.txt";

			// Search for a student in the linked list based on their id
			cout << "Enter the Student ID to search: "; // Ask the user to enter the student ID to be searched
			cin >> stu.id;

			if (SearchStudent(&studentList, stu.id, stu)) {
				cout << "\nStudent found!\n";
				stu.print(cout); // Print the student information after return
			}
			else {
				cout << "\nStudent with ID " << stu.id << " not found.\n\n";
			}
		}
		else if (choice == 4) {
			InsertBook("book.txt", &studentList);
		}
		else if (choice == 5) {  //User enter 5 to DISPLAY OUTPUT
			/*studentList.head = nullptr;  // Initialize the list

			// Populate the list with data (you should implement this part)

			// Call Display function with desired parameters
			int source = 2;     // Display to screen
			int detail = 1;     // Display student and book info
			Display(&studentList, source, detail);

			// Call print function
			source = 1;         // Display to file
			ofstream outputFile("student_booklist.txt");
			if (outputFile.is_open()) {
				print(osstream 'student_booklist.txt');
					outputFile.close();
			}
			else {
				cout << "Failed to open the output file." << endl;
			}*/

			return 0;
		}
		else if (choice == 6) {
			//User enter 6 to COMPUTE AND DISPLAY STATISTICS
					//Law Wai CHun bool computeAndDisplayStatistics
					//if user want to call this function, input their choice, then call this function
			LibStudent stu;
			const char* filename = "student_booklist.txt";

			ReadStudentData(studentList, filename);
			computeAndDisplayStatistics(&studentList);
			cout << "\n\n";
		}
		else if (choice == 7) {
			const char* callNum = "QA76.73.C153S26"; // Replace with desired call number
			printStuWithSameBook(&studentList, callNum);
		}
		else if (choice == 8) {
			List type1List;
			List type2List;
			displayWarnedStudent(&studentList, &type1List, &type2List);
		}
		else if (choice == 9) {
			return 0;
		}

	} while (choice != 1 - 9);
	std::cout << "Please enter your choice again (1 - 9): ";
	cin >> choice;
	return choice;
}
