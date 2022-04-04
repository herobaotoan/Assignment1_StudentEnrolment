import java.util.ArrayList;
import java.util.HashMap;

public class StudentEnrolment implements StudentEnrolmentManager {
    private Student student;
    private Course course;
    private String semester;
    private HashMap<String, HashMap<String, ArrayList<Course>>> studentList = new HashMap<>();
    //This HashMap will look like this { Student name : { Semester : List of Courses } }

    public StudentEnrolment(Student student, Course course, String semester) {
        this.student = student;
        this.course = course;
        this.semester = semester;
    }

    public Student getStudent() {
        return student;
    }

    public Course getCourse() {
        return course;
    }

    public String getSemester() {
        return semester;
    }

    public HashMap<String, HashMap<String, ArrayList<Course>>> getStudentList() {
        return studentList;
    }

    //Enroll method.
    public void addCourse(String id, String semester, Course course, Boolean firstRun) {
        //Create new HashMap on first time run, then add data in.
        if (firstRun){
            HashMap<String, ArrayList<Course>> courseList= new HashMap<>();
            studentList = new HashMap<>();
            courseList.put(semester, new ArrayList<>());
            courseList.get(semester).add(course);
            studentList.put(id, courseList);
        } else {
            //Check if provided student or semester is new.
            boolean newStudent = true;
            boolean newSemester = true;
            for (String n: studentList.keySet()) {
                if(id.equals(n)){
                    newStudent = false;
                    for (String s : studentList.get(n).keySet()) {
                        if (semester.equals(s)) {
                            newSemester = false;
                            break;
                        }
                    }
                    break;
                }

            }
            //If new create a new Student or Semester, If old update.
            if (newStudent){
                if (newSemester){
                    studentList.put(id, new HashMap<>());
                    studentList.get(id).put(semester, new ArrayList<>());
                    studentList.get(id).get(semester).add(course);
                } else {
                    studentList.get(id).get(semester).add(course);
                }
                studentList.put(id, studentList.get(id));
            } else {
                if (newSemester){
                    studentList.get(id).put(semester, new ArrayList<>());
                    studentList.get(id).get(semester).add(course);
                } else {
                    studentList.get(id).get(semester).add(course);
                }
            }
        }
    }
}
