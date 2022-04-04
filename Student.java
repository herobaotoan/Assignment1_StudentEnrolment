public class Student {
    private String ID;
    private String name;
    private String birthday;

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

    @java.lang.Override
    public java.lang.String toString() {
        return "Student{" +
                 ID + '\'' +
                 name + '\'';
    }
}
