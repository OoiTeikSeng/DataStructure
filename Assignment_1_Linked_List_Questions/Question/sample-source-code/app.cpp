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

bool isEmpty(List* );
bool isEmpty(List* list) {
	return list->count == 0;
}
bool DeleteRecord(List* list, char* student_id) {
	if (isEmpty(list)) {
		return false; // list is empty
	}
	// ng jian nian function to find borrowed due date
	for (int i = 1; i <= list->count; i++) {
		LibStudent* LibStudent = &list->find(i)->item; // this line needs to be fixed

		if (strcmp(student_id, student->id) == 0) {
			deleteStudent(list, i);
			return true; // delete successfully
		}
	}

	return false; // no student found
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
	// Function to search for a student in the list by their ID
	bool SearchStudent(List * list, char* id, LibStudent & stu) {
		Node* current = list->head;
		while (current != nullptr) {
			// Compare the current student's ID with the target ID
			if (strcmp(current->item.id, id) == 0) {
				// If found, store the student's information in the provided stu parameter
				stu = current->item;
				return true;	// Return true to indicate successful search
			}
			current = current->next;	// Move to the next node in the list
		}
		return false;	// Return false if the student with the given ID was not found
	}
	//Law Wai Chun extra function ReadStudentData
	// Function to read student data from the file and populate the list
	void ReadStudentData(List & studentList, const char* filename) {
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
	//Lim Kai Xian's Display function
	bool Display(List * list, int source, int detail) {
		// Check if the list is empty
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
						outputFile << "Borrow Date: " << date.borrow << "\n";
						outputFile << "Due Date: " << date.due << "\n";
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
						cout << "Borrow Date: " << date.borrow << "\n";
						cout << "Due Date: " << date.due << "\n";
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
		}

		return true;
	}
	//Yong Xin Qi's printStuWithSameBook
	bool printStuWithSameBook(List * list, const char* callNum) {
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
	bool displayWarnedStudent(List * list, List * type1, List * type2) {
		// Check if the list is empty
		if (list->empty()) {
			cout << "The list is empty." << endl;
			return false;
		}

		for (const LibStudent& student : *list) {
			int overdueBooks = 0;
			double totalFine = 0.0;

			// Calculate the number of overdue books and total fine for the student
			// Assuming you have a function to calculate overdue books and fine for each student, here's an example:
			// You need to implement the function calculateOverdueBooksAndFine() in the LibStudent struct
			// student.calculateOverdueBooksAndFine(overdueBooks, totalFine);

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
		for (const LibStudent& student : *type1) {
			LibStudent student = type1Node->item;
			cout << "Student ID: " << student.id << endl;
			cout << "Name: " << student.name << endl;
			cout << "Course: " << student.course << endl;
			cout << "Phone Number: " << student.phone_no << endl;
			student.displayBooks(cout); // Display student book information
			cout << endl;

			type1Node = type1Node->next;
		}

		// Display the students in type2 list with their book information
		cout << "Type 2 Warning (Total fine > RM50.00 and every book is overdue):" << endl;
		for (const LibStudent& student : *type2) {
			LibStudent student = type2Node->item;
			cout << "Student ID: " << student.id << endl;
			cout << "Name: " << student.name << endl;
			cout << "Course: " << student.course << endl;
			cout << "Phone Number: " << student.phone_no << endl;
			student.displayBooks(cout); // Display student book information
			cout << endl;

			type2Node = type2Node->next;
		}



		return true;
	}

	//Lim Kai Xian's menu function
	int menu() {
		int choice;
		cout << "Menu\n";
		cout << endl;
		cout << "1. Read file." << endl;
		cout << "2. Search student," << endl;
		cout << "3. Search student." << endl;
		cout << "4. Insert book." << endl;
		cout << "5. Display output." << endl;
		cout << "6. Compute and Display Statistics." << endl;
		cout << "7. Student with Same Book." << endl;
		cout << "8. Display Warned Student." << endl;
		cout << "9. Exit." << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		return choice;
	}


	int main() {
		List studentList;
		List type1List; // Define and initialize type1List
		List type2List; // Define and initialize type2List
		int choice;

		do {
			choice = menu();

			if (choice == 1) {  //User enter 1 to READ FILE
				//User enter 1 to read student.txt to enter into list
				//Ooi Teik Seng bool ReadFile
			bool successRead = ReadFile("student.txt", &studentList);
			}
			else if (choice == 2) { // Delete Student
            char student_id[10];
            std::cout << "Enter student ID to delete: ";
            std::cin >> student_id;
            bool deleted = DeleteRecord(&list, student_id);
            if (deleted) {
                std::cout << "Student with ID " << student_id << " deleted." << std::endl;
            } else {
                std::cout << "Student with ID " << student_id << " not found." << std::endl;
				
			}
			else if (choice == 3) {  //User enter 3 to SEARCH STUDENT
				//Law Wai Chun bool SearchStudent
				List studentList;	// Create a List object to store student data.
				LibStudent stu;		// A variable to hold the student information after search which is stu
				const char* filename = "student_booklist.txt";		// Change to the correct filename

				// Read student data from the file and populate the studentList.
				ReadStudentData(studentList, filename);

				// Ask the user to enter the student ID for searching.
				cout << "Enter the Student ID to search: ";
				cin >> stu.id;

				// Search for the student with the entered ID in the linked list.
				if (SearchStudent(&studentList, stu.id, stu)) {
					cout << "\nStudent found!\n";
					stu.print(cout); // Print the student information after finding.
					cout << "\n\n"; // Add some space for better readability
				}
				else {
					cout << "\nStudent with ID " << stu.id << " not found.\n\n";
				}
			}
			else if (choice == 4) {  //User enter 4 to INSERT BOOK
				InsertBook("book.txt", &studentList);
			}
			else if (choice == 5) {  //User enter 5 to DISPLAY OUTPUT
				List studentList;
				myList.head = nullptr;  // Initialize the list

				// Populate the list with data (you should implement this part)

				// Call Display function with desired parameters
				int source = 2;     // Display to screen
				int detail = 1;     // Display student and book info
				Display(&myList, source, detail);

				// Call print function
				source = 1;         // Display to file
				ofstream outputFile("student_booklist.txt");
				if (outputFile.is_open()) {
					print(osstream "student_booklist.txt');
						outputFile.close();
				}
				else {
					cout << "Failed to open the output file." << endl;
				}

				return 0;
			}
			else if (choice == 6) {  //User enter 6 to COMPUTE AND DISPLAY STATISTICS
				//Law Wai CHun bool computeAndDisplayStatistics
				computeAndDisplayStatistics(&studentList);	// Call the function to compute and display statistics
				cout << "\n\n"; // Add some space for better readability
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
			else if (choice == 9) {  //User enter 9 to EXIT
				return 0;
			}
		} while (choice != 1 - 9);
		cout << "Please enter your choice again (1 - 9): ";
		cin >> choice;
		return choice;
	}
