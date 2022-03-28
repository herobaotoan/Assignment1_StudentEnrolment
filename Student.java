import java.util.ArrayList;

public class Student {
    private String ID;
    private String name;
    private String birthday;
    private ArrayList<Course> coursesList;

    public Student(String ID, String name, String birthday) {
        this.ID = ID;
        this.name = name;
        this.birthday = birthday;
    }

    public String getID() {
        return ID;
    }

    public String getName() {
        return name;
    }

    public String getBirthday() {
        return birthday;
    }

    public void addCourse(Course course) {
        coursesList.add(course);
    }

    @java.lang.Override
    public java.lang.String toString() {
        return "Student{" +
                "ID='" + ID + '\'' +
                ", name='" + name + '\'' +
                ", birthday='" + birthday + '\'';
    }
}
