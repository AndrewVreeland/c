public class Person {
    private String name;

    public void setName(String givenName)
    {
        name = givenName;
    }
    public String getName (String name)
    {
        return name;
    }

    public static void main(String[] args) {
        Person p1 = new Person();
        System.out.println(p1.name); // prints null

        p1.name = "Larry";
        System.out.println(p1.name); // prints Larry
    }
}
