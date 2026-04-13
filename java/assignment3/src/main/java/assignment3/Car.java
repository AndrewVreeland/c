package assignment3;

public class Car {
    private String brandName;
    private int price;

    Car(int gPrice, String gBrandName) {  
        // initializes fields using setter methods
        setPrice(gPrice);
        setBrandName(gBrandName);
    }

    Car(String gline) {
        // splits data line into array of strings
        String[] parts = gline.split(" ");
        // assigns brand name from second position
        brandName = parts[1];
        // converts price string to numeric integer
        price = Integer.parseInt(parts[2]);
    }

    Car() {
        // default values for invalid car objects
        brandName = "Invalid";
        price = -1;
    }

    // getters and setters 
    public int getPrice() {
        return price;
    }

    private void setPrice(int gprice) {
        price = gprice;
    }

    public String getBrandName() {
        return brandName;
    }

    private void setBrandName(String gBrandName) {
        brandName = gBrandName;
    }

    @Override
    public String toString() {
        // formats gas car info for printing
        String returnString = "GCar brandname: " + brandName + " price: " + price;
        return returnString;
    }
}