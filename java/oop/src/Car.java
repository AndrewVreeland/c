public class Car {

    String brand;
    int year;
    boolean isRunning;

    // constructs
    public Car(String theBrand, int theYear)
    {
        brand = theBrand;
        year = theYear;
        isRunning = false;
    }

    // methods
    public void run()
    {
        isRunning = true;
    }

    public void roar()
    {
        if(isRunning)
            System.out.println(brand + " car is roaring");
        else
            {
            System.out.println(brand + " car is not running ");

            }
    }
}
