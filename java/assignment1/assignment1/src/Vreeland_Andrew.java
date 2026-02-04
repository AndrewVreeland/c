
import java.util.Random;
import java.util.Scanner;

/**
 * Andrew Vreeland TODO: must update PID and NID *PID:j1234567
 *
 * *NID:jo123456
 *
 * *This program is done for COP3330 course at year 2026. This program creates
 * a formatted receipt.
 */
public class Vreeland_Andrew {

    static final double TAX_RATE = 0.30;

    public static void main(String[] args) {

        Random random = new Random();
        int reciptUpperBound = 2000; // exclusive
        int reciptLowerBound = 1000; // inclusive
        int randomReciptNum = random.nextInt(reciptLowerBound, reciptUpperBound);

        printRecipt(randomReciptNum);
    }

    private static void userInput() {
        Scanner scanner = new Scanner(System.in);

        double totalCost = 0;
        int itemCounter = 0;

        String itemString = "Write item name ";
        String costString = "Write price ";
        String itemNumString = "item number ";

        String userInput = scanner.nextLine();
        while (!userInput.contains("DONE")) {

            System.out.println(itemString + userInput);
            itemCounter++;

            if (userInput.contentEquals("Food") || userInput.contentEquals("food")) {
                Double userPriceInput = scanner.nextDouble();
                scanner.nextLine();
                System.out.println(costString + userPriceInput);
                totalCost += userPriceInput;
                System.out.println(
                    itemNumString 
                    + itemCounter 
                    + " "
                    + String.format("%,.2f", userPriceInput));
            } else {
                Double userPriceInput = scanner.nextDouble();
                scanner.nextLine();
                System.out.println(costString + userPriceInput);
                userPriceInput = userPriceInput +  (userPriceInput * TAX_RATE);
                totalCost += userPriceInput;
                System.out.println(
                    itemNumString 
                    + itemCounter 
                    + " "
                    + String.format("%,.2f", userPriceInput));
            }
            userInput = scanner.nextLine();
        }
        System.out.println(itemString + userInput);
        System.out.println(itemCounter + " items      total " + String.format("%,.2f", totalCost));
        scanner.close();
    }

    private static void printRecipt(int reciptNum) {
        StringBuilder sb;
        System.out.println("******************************");
        System.out.println("****** S store ***************");
        System.out.println("******************************");
        System.out.println("receipt number      " + reciptNum);
        sb = generateDate();
        System.out.println(sb.toString());
        userInput();
        for (int i = 0; i < 3; i++) {
            System.out.println("******************************");
        }
    }

    public static StringBuilder generateDate() {
        StringBuilder sb = new StringBuilder();

        Random random = new Random();
        int yearUpperBound = 2100;
        int yearLowerBound = 1900;
        int year = random.nextInt(yearLowerBound, yearUpperBound);

        int dayLowerBound = 0;
        int dayUpperBound = 27;
        int day = random.nextInt(dayLowerBound, dayUpperBound);

        String monthArr[] = {
                "January",
                "Febuary",
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

        int monthLowerBound = 0;
        int monthUpperBound = 12;
        String month = monthArr[random.nextInt(monthLowerBound, monthUpperBound)];

        sb.append(month);
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
