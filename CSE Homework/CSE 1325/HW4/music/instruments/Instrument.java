package instruments;

abstract class Instrument { 
    String brand; 
  
    protected Instrument(String brand) { 
       this.brand=brand; 
    } 
  
    public abstract void play(String musicSheet);
} 
