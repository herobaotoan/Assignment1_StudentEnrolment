public class Course {
    private String ID;
    private String name;
    private int credit;

    public Course(String ID, String name, int credit) {
        this.ID = ID;
        this.name = name;
        this.credit = credit;
    }

    public String getID() {
        return ID;
    }

    public String getName() {
        return name;
    }

    public int getCredit() {
        return credit;
    }

    @Override
    public String toString() {
        return "Course{" +
                 ID + '\'' +
                 name + '\'' +
                 credit +
                '}';
    }
}
