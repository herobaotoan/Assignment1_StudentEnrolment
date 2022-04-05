# Assignment1_StudentEnrolment
Github repository: https://github.com/herobaotoan/Assignment1_StudentEnrolment

Description: 

When run the program will ask user to input File name or to read the default file.
Then all Student and Courses in the file will be automatically enrolled.
All information will be stored as
HashMap <String SID , HashMap <String semester, ArrayList <Course> > >
By doing this, student and courses can have a connection.
For example: 
Student{S101312'Alex Mike'10/13/1998}
 - Semester: 2020C - [Course{COSC4030'Theory of Computation'5}, Course{BUS2232'Business Law'3}]
 - Semester: 2021A - [Course{PHYS1230'Introductory Human Physiology'4}]

User has 5 option to choose:
1.	Enroll another Student:
-	The program will ask student and course information in a format: SID,name,birthday / CourseID,name,credit,semester
-	User will be asked again if the input is incorrect (including the Credit has to be a number).
-	The program then enrolls the student. If student information is the same, the program will update that student.
-	User can choose whether to add (write) that student, course into the File.
2.	Delete an old Student:
-	The program will ask Student ID.
-	If there is no match in the Enrolled Student List, user will be asked again.
-	The program then Remove that student out of the Enrolment List.
3.	Print all:
-	The program simply prints all enrolled Student (including new student added).
4.	Print one:
-	The program will ask student ID.
-	If there is no match in the Enrolled Student List, user will be asked again.
-	Then print semesters and courses of that student.
5.	End program.
After each option (except 5), user can choose whether to continue or quit.
 
 
Method:

addCourse(String id, String semester, Course course, Boolean firstRun) :
-	Boolean firstRun is to determind whether creating a new HashMap/ArrayList or to update it.
-	The program will check if the id. 
If new, add a new key. If old, update that key.
-	The program check semester same as the id.

getAllEnrolment(ArrayList<StudentEnrolment> enrolmentList, ArrayList<Student> studentList):
-	The program will loop through the enrolmentList.
-	Then check the key (String SID) in studentList to print out Student information.
-	Then use the index to print semester and courses in the HashMap inside the enrolmentList.

getOneEnrolment(ArrayList<StudentEnrolment> enrolmentList, ArrayList<Student> studentList, String id):
-	Same as getAllEnrolment, but this time only print out information when the id matches.
