import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class main {
    public static void main(String[] args) {

        //PART 1: POPULATE DATA FROM PROVIDED FILE INTO HASHMAPS.
        //File must in the project folder.
        System.out.print("Enter file name: ");
        Scanner scanner = new Scanner(System.in);
        String fileName = scanner.nextLine();
        if (fileName.equals("")) fileName = "default.csv";

        ArrayList<StudentEnrolment> enrolmentList = new ArrayList<>();
        ArrayList<Student> students = new ArrayList<>();
        try {
            //Put all data in provided file into multiple ArrayLists created above.
            File file = new File(fileName);
            Scanner fileScanner = new Scanner(file);

            while (fileScanner.hasNextLine()) {
                String line = fileScanner.nextLine();
                if (line.isEmpty()) continue;
                String[] data = line.split(",");
                Student student = new Student(data[0], data[1], data[2]);
                Course course = new Course(data[3], data[4], Integer.parseInt(data[5]));
                StudentEnrolment enrolment = new StudentEnrolment(student,course,data[6]);
                enrolmentList.add(enrolment);
                students.add(student);
            }
            fileScanner.close();
        } catch (FileNotFoundException e) {
            System.out.println("I cannot find your file. If you want to use default file, enter nothing and press Enter next time.");
        }
        //Enroll students base on semesters and courses.
        boolean firstRun = true;
        for (StudentEnrolment studentEnrolment : enrolmentList) {
            Student student = studentEnrolment.getStudent();
            String semester = studentEnrolment.getSemester();
            Course course = studentEnrolment.getCourse();
            enrolmentList.get(0).addCourse(student.getID(), semester, course, firstRun);
            firstRun = false;
        }
        System.out.println("\nAll students in " + fileName + " is successfully enrolled!");

        //PART 2: ADD OR DELETE FROM THE LIST.
        boolean Continue = true;
        do {
            System.out.println("""
                    How can I help you?\s
                    Type 1 to enroll another Student.\s
                    Type 2 to delete an old Student.\s
                    Type 3 to print out everything in the Enrolment List.\s
                    Type 4 to print out all courses of a Student.
                    Type 5 to end the program.""");
            int input = scanner.nextInt();
            switch (input) {
                case (1) -> { //ENROLL NEW STUDENT.
                    System.out.println("Please enter student information with the format SID,Name,Birthday: ");
                    Scanner studentScanner = new Scanner(System.in);
                    String ans = studentScanner.nextLine();
                    String[] arr = ans.split(",");
                    //Check input validation.
                    while (arr.length != 3){
                        System.out.println("Invalid input. Please try again.(SID,Name,Birthday)");
                        ans = studentScanner.nextLine();
                        arr = ans.split(",");
                    }
                    Student s = new Student(arr[0], arr[1], arr[2]);
                    students.add(s);
                    System.out.println("Please enter course information with the format CourseID,Name,Credit,Semester: ");
                    Scanner courseScanner = new Scanner(System.in);
                    ans = courseScanner.nextLine();
                    arr = ans.split(",");
                    //Check input validation.
                    while (!(arr.length == 4 && isInteger(arr[2]))){
                        System.out.println("Invalid input. Please try again.(CourseID,Name,Credit,Semester)");
                        ans = studentScanner.nextLine();
                        arr = ans.split(",");
                    }
                    Course c = new Course(arr[0], arr[1], Integer.parseInt(arr[2]));
                    enrolmentList.get(0).addCourse(s.getName(), arr[3], c, false);

                    //Write in file.
                    System.out.println("Do you want to update " + fileName + "?(Y/N)");
                    Scanner answer = new Scanner(System.in);
                    ans = answer.nextLine().toUpperCase();
                    while (!ans.equals("Y") && !ans.equals("N")) {
                        System.out.println("I don't understand. Please try again.(Y/N)");
                        ans = answer.next();
                    }
                    if (ans.equals("Y")) {
                        try (var fw = new FileWriter(fileName, true)) {
                            fw.append("\n" + s.getID() + "," + s.getName() + "," + s.getBirthday() + ","
                                    + c.getID() + "," + c.getName() + "," + c.getCredit() + "," + arr[3]);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        System.out.println("Information about " + s.getName() + " has been written to " + fileName + "!");
                    }
                }
                case (2) -> {boolean error2 = true;
                    do {
                        System.out.println("Please enter SID of the student you want to delete from enrolment: ");
                        Scanner idScanner = new Scanner(System.in);
                        String id = idScanner.nextLine().toUpperCase();
                        for (String string : enrolmentList.get(0).getStudentList().keySet()) {
                            if (id.equals(string)) {
                                //Remove student.
                                enrolmentList.get(0).getStudentList().remove(id);
                                for (Student student : students) {
                                    if (student.getID().equals(id)) {
                                        System.out.println(student + " is removed from the enrolment!");
                                    }
                                }
                                error2 = false;
                                break;
                            }
                        }
                        if (error2) System.out.println("No student found! Please try again.");
                    } while (error2);
                }
                case (3) -> {

                    break;
                }
                case (4) -> {
                    break;
                }
                case (5) -> //END PROGRAM.
                        Continue = false;
            }
            if (Continue) {
                System.out.println("Do you want to continue?(Y/N)");
                Scanner answer = new Scanner(System.in);
                String ans = answer.nextLine().toUpperCase();
                while (!ans.equals("Y") && !ans.equals("N")) {
                    System.out.println("I don't understand. Please try again.(Y/N)");
                    ans = answer.next();
                }
                if (ans.equals("N")) {
                    System.out.println("Thank you for using our service. Have a good day!");
                    Continue = false;
                }
            }
        } while (Continue);
    }
    //Method to check if inputted Credit is an Integer.
    public static boolean isInteger(String s){
        try{
            int i = Integer.parseInt(s);
        } catch (NumberFormatException exception){
            return false;
        }
        return true;
    }
}
