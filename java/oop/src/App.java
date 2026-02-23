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
         String string = "nice world we have here";
         String[] tempStringArr = string.split("");
        for(int i = 0; i < tempStringArr.length; i ++)
        {
            System.out.println(tempStringArr[i]);
        }

        String newString = String.join("", tempStringArr);
        System.out.println(newString);

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
