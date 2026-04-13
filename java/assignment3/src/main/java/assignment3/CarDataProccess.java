package assignment3;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class CarDataProccess {
    public static void main(String[] args) {
        //  closes scanner after use
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.println("input file name");
            String fname = scanner.nextLine();
            
            // populates list from text file
            ArrayList<Car> list = readIntoArrayList(fname);
            // outputs all cars in list
            printCars(list);
            // calculates and displays final sum
            System.out.println("Total price is " + getTotal(list));
        }
    }

    public static int getTotal(ArrayList<Car> arr) {
        int total = 0;
        for (int i = 0; i < arr.size(); i++) {
            // dynamic binding ensures correct price version
            total += arr.get(i).getPrice();
        }
        return total;
    }

    public static void printCars(ArrayList<Car> arr) {
        for(int i = 0; i < arr.size(); i++) {
            // calls specific toString based on car type
            System.out.println(arr.get(i).toString());
        }
    }

    public static ArrayList<Car> readIntoArrayList(String fname) {
        ArrayList<Car> list = new ArrayList<>();
        // reader manages file access
        try (BufferedReader br = new BufferedReader(new FileReader(fname))) {
            String line;
            // reads until end of document
            while ((line = br.readLine()) != null) {
                // branches based on first character e or g
                if (line.startsWith("e")) {
                    list.add(new ElectricCar(line));
                } else if (line.startsWith("g")) {
                    list.add(new Car(line));
                }
            }
        } catch (IOException e) {
            // handles missing or corrupted files
            System.out.println("Error reading file: " + e.getMessage());
        }
        return list;
    }
}