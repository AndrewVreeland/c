public class App {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");

        String theBrand = "Honda";
        int year = 1999;
        Car car = new Car(theBrand, year);
        System.out.println( car.year+" "+ car.brand + " is car running? -> " + car.isRunning);
        car.run();
        System.out.println( car.year+" "+ car.brand + " is car running? -> " + car.isRunning);
        car.roar();

    }
}
/*
    ? Class 
    * -Blue print/ template moold
     - properties / states
     - functionality/ serives 

     ? objects - 
     * individual/unique thing : Instance
    - particiular value for each property/state
    - & functionality of all member of class 
*/
