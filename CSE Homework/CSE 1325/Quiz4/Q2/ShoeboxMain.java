public class ShoeboxMain {
    public static void main(String[] args) {
  
        Shoebox s1=new Shoebox(8,"Jimmy Choo");   //shoe size, designer
  
        s1.addItem("shells", 10);
  
        s1.addItem("rocks", 3);
  
        s1.addItem("candles",5);
  
        s1.addItem("candles",1); //should update total to 6 since 5+1=6
  
        s1.pickItem();
  
        s1.pickItem("toys"); //Why is this line of code done after the input. makes it look like there is a duplicate line.
  
    }
}