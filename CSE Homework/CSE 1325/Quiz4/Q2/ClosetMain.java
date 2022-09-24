public class ClosetMain {

    public static void main(String[] args) {
  
        Closet c1=new Closet();
  
        c1.addItem("pants", 2); 
  
        c1.addItem("shoes",100);
  
        c1.addItem("pants",4);    //should update existing total to 6 since 4+2=6
  
        c1.pickItem();
  
        c1.pickItem("pants"); 
  
    }
  
   }