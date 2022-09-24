package chilistuff1;

public class StarbucksCup {
    public String name;
    public int size;    //in half cups
    
    public StarbucksCup(String size) {
        this.name=size;

        switch (name.toLowerCase()) {
            case "short":
                this.size=2;
                break;
            case "tall":
                this.size=3;
                break;
            case "grande":
                this.size=4;
                break;
            case "venti":
                this.size=5;
                break;
        }
    }
}
