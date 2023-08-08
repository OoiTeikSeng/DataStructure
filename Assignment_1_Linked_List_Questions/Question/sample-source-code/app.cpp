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

bool ReadFile(const std::string& filename, List& studentRecord, int lineNumber) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Fail to open the file: " << filename << endl;
        return false;
    }
    else {
        string line;
        int lineAmount = 1;

        while (getline(file, line) && lineAmount <= lineNumber) {
            LibStudent studentDetail;

            // Parse the line and extract student details into studentDetail

            // Check if the student details have been encountered before
            Node* cur = studentRecord.head;  // Assuming the head member is public
            bool isDuplicate = false;
            while (cur != nullptr) {
                if (cur->studentDetail == studentDetail) {
                    cout << "Duplicate student details found at line " << lineNumber << ". Skipping." << endl;
                    isDuplicate = true;
                    break;
                }
                cur = cur->next;
            }

            if (!isDuplicate) {
                // Insert the record into the list
                if (!studentRecord.insert(1, studentDetail)) {
                    cout << "Fail to insert student details from line " << lineNumber << " into the record." << endl;
                    file.close();
                    return false;
                }
            }

            lineAmount++;
        }
        file.close();
        cout << "Student details successfully recorded." << endl;
        return true;
    }
}

// ng jian nian function to find and delete students based on student id
bool DeleteRecord(List *list, char *student_id) {
    if (isEmpty(list)) {
        return false; // list is empty
    }
// ng jian nian function to find borrowed due date
    for (int i = 1; i <= list->count; i++) {
        student *student = &list->find(i)->item; // this line needs to be fixed

        if (strcmp(student_id, student->id) == 0) {
            deleteStudent(list, i);
            return true; // delete successfully
        }
    }
    
    return false; // no student found
}
 
bool InsertBook(char *filename, LibStudent *student) {
    FILE *file = fopen(student_booklist.txt, "r");
    if (file == NULL) {
        // Handle file open errors
        return false;
    }
//Law Wai Chun computeAndDisplayStatistics function definition
bool computeAndDisplayStatistics(List* list) {
	if (list->empty()) {
		cout << "List is empty." << endl;
		return false;	//return false for empty list
	}

	// Initialize variables to store statistics for each course.
	int csStudents = 0, iaStudents = 0, ibStudents = 0, cnStudents = 0, ctStudents = 0;
	int csBooks = 0, iaBooks = 0, ibBooks = 0, cnBooks = 0, ctBooks = 0;
	int csOverdueBooks = 0, iaOverdueBooks = 0, ibOverdueBooks = 0, cnOverdueBooks = 0, ctOverdueBooks = 0;
	double csOverdueFine = 0.0, iaOverdueFine = 0.0, ibOverdueFine = 0.0, cnOverdueFine = 0.0, ctOverdueFine = 0.0;

	// Traverse the linked list to gather statistics for each course.
	Node* current = list->head;
	while (current != nullptr) {
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
//Law Wai Chun extra function ReadStudentData
// Function to read student data from the file and populate the list
void ReadStudentData(List& studentList, const char* filename) {
	ifstream inFile(filename);
	if (!inFile) {
		cout << "Error opening the file." << endl;
		return;
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
}

//Lim Kai Xian's Display function
bool Display(List* list, int source, int detail) {
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

			for (int i = 0; i < current->next; i++) {
				LibBook book = current->item[i];
				if (source == 1) {
					outputFile << "Book " << i + 1 << "\n";
					outputFile << "Title: " << book.title << "\n";
					outputFile << "Author: " << book.author << "\n";
					outputFile << "Publisher: " << book.publisher << "\n";
					outputFile << "Year Published: " << book.yearPublished << "\n";
					outputFile << "ISBN: " << book.ISBN << "\n";
					outputFile << "Call Number: " << book.callNum << "\n";
					outputFile << "Borrow Date: " << book.borrow << "\n";
					outputFile << "Due Date: " << book.due << "\n";
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
					cout << "Borrow Date: " << book.borrow << "\n";
					cout << "Due Date: " << book.due << "\n";
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

bool printStuWithSameBook(List *, char *);
bool displayWarnedStudent(List *, List *, List *);

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
	int choice;

	do {
		choice = menu();

		if (choice == 1) {  //User enter 1 to READ FILE
			List LibStudent;

			string filename = "student.txt";
			ReadFile("student.txt", LibStudent, 4);
		}
		else if (choice == 2) {  //User enter 2 to DELETE RECORD
			DeleteRecord(LibStudent, 4);
		}
		else if (choice == 3) {  //User enter 3 to SEARCH STUDENT
			//Law Wai Chun bool SearchStudent
			List studentList; // Created a List object.
			LibStudent stu;  // Return the student information using stu
			const char* filename = "student.txt";
			
			ReadStudentData(studentList, filename); // Read student data from the file and populate the studentList.

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
		else if (choice == 4) {  //User enter 4 to INSERT BOOK
			InsertBook(string, List*);
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
        			print(osstream outputFile);
        			outputFile.close();
   			} else {
        		cout << "Failed to open the output file." << endl;
			}

    			return 0;
		}
		else if (choice == 6) {  //User enter 6 to COMPUTE AND DISPLAY STATISTICS
			//Law Wai CHun bool computeAndDisplayStatistics
			//if user want to call this function, input their choice, then call this function
			computeAndDisplayStatistics(&studentList);
			cout << "\n\n";
		}
		else if (choice == 7) {  //User enter 7 to STUDENT WITH SAME BOOK
			printStuWithSameBook(List*, char*);
		}
		else if (choice == 8) {  //User enter 8 to DISPLAY WARNED STUDENT
			displayWarnedStudent(List*, List*, List*);
		}
		else if (choice == 9) {  //User enter 9 to EXIT
			return 0;
		}
	} while (choice != 1 - 9);
			cout << "Please enter your choice again (1 - 9): ";
			cin >> choice;
			return choice;
}
