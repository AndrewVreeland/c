public class Car {

    String brand;
    int year;
    boolean isRunning;
    private static int count = 0;
    private int orderNum;

    // constructs
    public Car(String theBrand, int theYear)
    {
        brand = theBrand;
        year = theYear;
        isRunning = false;
        count ++;
        orderNum = count;
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
