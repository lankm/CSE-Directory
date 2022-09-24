/* README
 * Main method in GradingProgram.java.
 * Further README instructions are in GradingProgram.java.
 * 
 * Stack datastructure is used but this is personal practice.
 */

package gradestuff;

import java.util.Stack;

public class GradingStack {
    private Stack<ExamPaper> ungraded = new Stack<>();

    public void addExamToStack(ExamPaper e1) {
        String name=e1.getName();
        int grade=e1.getGrade();

        if(e1.getGrade()==-1) {
            System.out.printf("\nPaper for %s not graded yet. Adding to grading stack.\n", name);

            ungraded.add(e1);
            showStackInfo();
        } else {
            System.out.printf("\nPaper for %s already graded. Grade for %s is: %d\n", name, name, grade);
        }
    }

    public void showStackInfo() {
        System.out.printf("\nTotal papers to grade: %d\n", ungraded.size());

        System.out.printf("Students to grade:\n");
        for(ExamPaper elem : ungraded) {
            System.out.printf("%s\n", elem.getName());
        }
    }
}