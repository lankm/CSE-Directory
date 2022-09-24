/* README
 * Main method in GradingProgram.java.
 * Further README instructions are in GradingProgram.java.
 * 
 * showGrade() does not check for if the grade is greater than 100.
 * getters and setters are included and variables are made private.
 */

package gradestuff;

public class ExamPaper {
    private String name="";
    private int grade=-1;

    //CONSTRUCTORS
    public ExamPaper(String name, int grade) {
        this.name=name; //using "this" to make code more readable
        this.grade=grade;
    }
    public ExamPaper(String name) {
        this(name,-1);
    }

    //METHODS
    public void showGrade() {
        if(grade==-1)
            System.out.printf("Grade not assigned yet.\n");
        else 
            System.out.printf("Grade for %s is: %d\n", this.name, this.grade);
    }

    //GETTERS/SETTERS
    public String getName() {
        return name;
    }
    public int getGrade() {
        return grade;
    }
    public void setName(String name) {
        this.name=name;
    }
    public void setGrade(int grade) {
        this.grade=grade;
    }
}