bool DeleteStudent(List *list, char *student_id) {
	if (list->empty()) {
		return false; // end 
	}

	Student *student;
	for (int i = 1; i <= list->count; i++) {
		student = &list->find(i)->item;
		
		if (strcmp(student_id, student->id) == 0) {
			student = NULL;
			list->remove(i); // remove line of id, name, course and phone number of the student
			return true;
		}
	}
	return false;
}
