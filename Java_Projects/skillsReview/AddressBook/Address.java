package skillsReview.AddressBook;

public class Address {
    String address;
    private String phoneNumber;
    private String email;


    Address(String address, String phoneNumber, String email) {
        setAddress(address);
        setPhoneNumber(phoneNumber);
        setEmail(email);
    }
    public String getAddress() {
        return address;
    }
    public String getPhoneNumber() {
        return phoneNumber;
    }
    public String getEmail() {
        return email;
    }
    public void setAddress(String a) {
        address=a;
    }
    public void setPhoneNumber(String p) {
        phoneNumber=p;
    }
    public void setEmail(String e) {
        email=e;
    }

    public String tostring() {
        return address+"|"+phoneNumber+"|"+email;
    }
}
