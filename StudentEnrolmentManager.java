import java.util.ArrayList;

public interface StudentEnrolmentManager {


    public void addCourse(String id, String semester, Course course, Boolean firstRun);
    public static void getAllEnrolment(ArrayList<StudentEnrolment> enrolmentList, ArrayList<Student> studentList){
        for (String n : enrolmentList.get(0).getStudentList().keySet()) {
            for (Student student : studentList) {
                if (n.equals(student.getID())) {
                    System.out.println(student);
                    break;
                }
            }
            for (String s : enrolmentList.get(0).getStudentList().get(n).keySet()) {
                System.out.println(" - Semester: " + s + " - " + enrolmentList.get(0).getStudentList().get(n).get(s));
            }
        }
    }
    public static void getOneEnrolment(ArrayList<StudentEnrolment> enrolmentList, ArrayList<Student> studentList, String id){
        for (String n : enrolmentList.get(0).getStudentList().keySet()) {
            if (id.equals(n)){
                for (Student student : studentList) {
                    if (id.equals(student.getID())){
                        System.out.println(student.toString());
                        break;
                    }
                }
                for (String s : enrolmentList.get(0).getStudentList().get(n).keySet()) {
                    System.out.println("Semester: " + s + " - " + enrolmentList.get(0).getStudentList().get(n).get(s));
                }
            }
        }
    }
}
