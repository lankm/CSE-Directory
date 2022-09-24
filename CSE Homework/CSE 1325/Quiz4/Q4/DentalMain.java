public class DentalMain {

    public static void main(String[] args) {
  
        DentalOffice d1=new DentalOffice("ABC Dental Office");
  
        d1.addCustomer("people.txt");  //goes through file and only adds patients that brush morning and night
  
        d1.showCustomers();
  
   
  
        Person p1=new Person("Faena Maena", true, false,4);
  
        d1.addCustomer(p1);
  
        d1.showCustomers();
  
    }
}
