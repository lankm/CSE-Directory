package chilistuff;

public abstract class Person {  //making it abstract purely for practice.
    protected String name;

    protected Person(String name) {
        this.name=name;
    }

    public String getName() {
        return name;
    }
}
