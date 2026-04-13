package assignment3;

public class ElectricCar extends Car {
    private boolean isLithiumIon;

    public ElectricCar(String brandName, int price) {
        // passes core data to parent constructor
        super(price, brandName);
    }

    String batteryType() {
        // checks boolean flag for battery label
        if(isLithiumIon == true) {
            return "LithiumIon";
        } else {
            return "NickelMetal";
        }
    }

    ElectricCar(String gline) {
        // triggers parent string parsing logic
        super(gline);
        String[] parts = gline.split(" ");
        // evaluates 4th token for battery type
        if (parts[3].equals("1")){
            isLithiumIon = true;
        } else {
            isLithiumIon = false;
        }
    }
    
    @Override
    public String toString() {
       // builds electric car string using base and child data
       String returnString = "ECar brandname: " + getBrandName() + " price: " + getPrice() + " battery: " + batteryType();
       return returnString;
    }

    @Override
    public int getPrice() {
        int price;
        // applies specific markup for lithium models
        if(batteryType().equals("LithiumIon")) {
            // calculates 20 percent increase over base
            price = (int)(super.getPrice() * 1.2);
            return price;
        } else {
            // returns standard price for nickel batteries
            return super.getPrice();
        }
    }
}