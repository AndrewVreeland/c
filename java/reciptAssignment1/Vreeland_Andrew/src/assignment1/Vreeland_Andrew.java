package assignment1;
import java.util.Random;
import java.util.Scanner;
/**

 * *Andrew Vreeland PID and NID *PID:5759863
 *
 * *NID:AN627713
 *
 * *This program is done for COP3330 course at year 2026. This program creates
 * *a formatted receipt.

 */

public class Vreeland_Andrew {

    static final double TAX_RATE = 0.30;

    public static void main(String[] args) {

        Random random = new Random();
        int reciptUpperBound = 2000; // exclusive
        int reciptLowerBound = 1000; // inclusive
        int randomReciptNum = random.nextInt(reciptLowerBound, reciptUpperBound); // generates random recipt number

        printRecipt(randomReciptNum); // main method call

    }

    private static void userInput() {

        Scanner scanner = new Scanner(System.in); // opens scanner
        double totalCost = 0; // total cost tracker
        int itemCounter = 0; // item counter
        System.out.println("Write item name");
        String userInput = scanner.nextLine(); // captures first line of input
        userInput = userInput.substring(0, 1).toUpperCase() + userInput.substring(1);

        while (!userInput.equals("DONE")) { // while input is not DONE continue loop
            itemCounter++; // increments item counter
            System.out.println("Write price"); // asks user for price
            Double userPriceInput = scanner.nextDouble(); // captures next double
            scanner.nextLine(); // clears line that isnt captured with the double

            if (userInput.contentEquals("Food") || userInput.contentEquals("food")) { // if item is Food or food fo not
                totalCost += userPriceInput; // adds input to totalcost with no tax

            } else { // applies 0.30 * item cost for tax
                userPriceInput = userPriceInput + (userPriceInput * TAX_RATE); // totals the userprice +* tax
                totalCost += userPriceInput; // adds to total cost
            }

            System.out.println( // prints the standard format
                            "item number "
                            + itemCounter
                            + " "
                            + userInput
                            + " "
                            + String.format("%,.2f", userPriceInput));

            System.out.println("Write item name "); // takes user input for item name

            userInput = scanner.nextLine(); // captures the next line if DONE loop will end
            userInput = userInput.substring(0, 1).toUpperCase() + userInput.substring(1); // capatalizes first letter by subtring
        }
        
        System.out.println("Write item name " + userInput); // make sure to print DONE
        System.out.println(itemCounter + " items      total " + String.format("%,.2f", totalCost)); // final print.
        
        scanner.close();
    }

    private static void printRecipt(int reciptNum) {

        StringBuilder sb; // initalizes string builder

        System.out.println("******************************");
        System.out.println("****** S store ***************");
        System.out.println("******************************");
        System.out.println("receipt number      " + reciptNum);

        sb = generateDate(); // sb is assinged the result of generate date
        System.out.println(sb.toString()); // prints the string value of sb
        userInput(); // this method reads the file and captures items and item costs

        for (int i = 0; i < 3; i++) { // prints 3 rows of *'s for recipt formatting
            System.out.println("******************************");
        }
    }

    public static StringBuilder generateDate() {

        StringBuilder sb = new StringBuilder(); // initalizes string builder
        Random random = new Random(); // initalizes randome num generator
        int yearUpperBound = 2100; // exclusive
        int yearLowerBound = 1900; // inclusive
        int year = random.nextInt(yearLowerBound, yearUpperBound); // generates random year between 1900 and 2099
        int dayLowerBound = 0; // inclusive
        int dayUpperBound = 28; // exclusive
        int day = random.nextInt(dayLowerBound, dayUpperBound) + 1; // adds 1 to total so days are between 1-28

        String monthArr[] = { // list of months
                "January",
                "February",
                "March",
                "April",
                "May",
                "June",
                "July",
                "August",
                "September",
                "October",
                "November",
                "December"
        };

        int monthLowerBound = 0; // inclusive
        int monthUpperBound = 12;// exclusive

        String month = monthArr[random.nextInt(monthLowerBound, monthUpperBound)]; // randomly picks month from month array
        sb.append(month); // utilizing string builder to build string following formatting
        sb.append(" ");

        if (day < 10) {
            sb.append("0");
        }
        sb.append(day);
        sb.append(" ");
        sb.append(year);

        return sb;
    }

}

