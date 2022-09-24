public class Person{
    String name;
    boolean brushesMorning;
    boolean brushesNight;
    int dentistVisitsPerYear;

    Person(String name, boolean brushesNight, boolean brushesMorning, int dentistVisitsPerYear) {
        this.name=name;
        this.brushesMorning=brushesMorning;
        this.dentistVisitsPerYear=dentistVisitsPerYear;
        this.brushesNight=brushesNight;
    }
}
