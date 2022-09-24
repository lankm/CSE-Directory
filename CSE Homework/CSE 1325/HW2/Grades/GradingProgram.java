/* README
 * The Scanner import is never used so I made it a comment.
 * The main method is the one given from the assignment.
 * 
 * program matches sample run.
 */

//import java.util.Scanner;
import gradestuff.ExamPaper;
import gradestuff.GradingStack;

public class GradingProgram{ 
 
    public static void main(String [] args) 
    { 
        ExamPaper e1=new ExamPaper("Abdu"); //student name, no grade yet 
        ExamPaper e2=new ExamPaper("Adamma", 96); //student name, grade on paper 
 
        e1.showGrade(); 
        e2.showGrade(); 
 
        GradingStack g1=new GradingStack(); 
        g1.addExamToStack(e1); //gets added to stack because no grade yet 
        g1.addExamToStack(e2); //already graded, doesn't get added to stack 
 
    } 
}; 