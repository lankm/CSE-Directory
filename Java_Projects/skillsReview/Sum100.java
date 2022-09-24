package skillsReview;

public class Sum100 {
    public static void main(String[] args) {
        int lowerBound = 1;
        int upperBound = 100;
        int sum = 0;
        double avg;
        int counter;

        counter = lowerBound;
        do{
            sum+=counter;
            counter++;
        } while(counter<=upperBound);
        avg=sum/(double)(upperBound-lowerBound+1);
        System.out.println("The sum of "+lowerBound + " to " + upperBound + " is " + sum);
        System.out.println("The average is "+ avg);


        counter = lowerBound;
        sum = 0;    //reset for next loop
        avg = 0;



        while(counter<=upperBound) {
            sum+=counter;
            counter++;
        }
        avg=sum/(double)(upperBound-lowerBound+1);
        System.out.println("The sum of "+lowerBound + " to " + upperBound + " is " + sum);
        System.out.println("The average is "+ avg);
    }
}
