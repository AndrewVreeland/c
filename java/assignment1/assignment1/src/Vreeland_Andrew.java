
import java.util.Random;

/**
 * Andrew Vreeland TODO: must update PID and NID *PID:j1234567
 *
 *  *NID:jo123456
 *
 *  *This program is done for COP3330 course at year 2026. This program created
 * a formatted receipt.
 */
public class Vreeland_Andrew {

    public static void main(String[] args) {
        StringBuilder sb;

        Random random = new Random();
        int upperBound = 2000; // exclusive
        int lowerBound = 1000; // inclusive
        int intRandom = random.nextInt(lowerBound, upperBound);

        sb = generateDate();

        System.out.println(sb.toString());
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

        String monthArr[]
                = {
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
        if (day < 10) 
        {
            sb.append("0");
        }
        sb.append(day);
        sb.append(" ");
        sb.append(year);

        return sb;

    }

}
