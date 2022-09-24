import instruments.*;

public class Practice {   
   public static void main(String args[]){    
    String musicSheet="P-do..re...mi G-doooo...re...mi P-fa..so..la G-faaa..soo..lala"; 
    Guitar g1=new Guitar("Fender", 2);    //brand, number of strings 
    g1.play(musicSheet);
   }   
} 