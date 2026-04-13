package pa2;

/**
 * Andrew Vreeland PID and NID * PID:5759863
 *
 * *NID:AN627713 PA2 *This program is done for COP3330 course at year 2026.
 * This is my main tester class where I execute the dice rolling. I
 * roll the pair of dice 1000 times, tally up the results, print the counts, and
 * then I print a histogram to show the distribution of the rolls.
 */
public class DiceTester {

    public static void main(String[] args) {
        //  array of size 11 to hold the frequencies for  possible sums (which range from 2 to 12)

        int[] arr = new int[11];
        //  instance of Dice pair

        Dice dice = new Dice();

        // run this loop exactly 1000 times FOR dice throws
        for (int i = 0; i < 1000; i++) {
            // roll dice.

            dice.roll();
            //  grab the sum of the newly rolled dice

            int rolledValue = dice.getFaceValue();
            // subtract 2 from rolled value to map it to array index (so a roll of 2 increments arr[0], a roll of 12 increments arr[10]).

            arr[rolledValue - 2]++;
        }
        // iterate through frequency array to print out the raw tallies for print

        for (int i = 0; i < arr.length; i++) {
            // add 2 back to the index so I can print out the actual dice sum instead of the index number.

            int number = i + 2;
            System.out.println("Number of " + number + "s are " + arr[i]);
        }
        // proper print order

        System.out.println("Graph");
        // Y-axis threshold at 175.

        int number = 175;
        // loop 8 times to draw the 8 vertical steps of graph (from 175 down to 0, decreasing by 25 each time)

        for (int i = 0; i < 8; i++) {
            // format the Y-axis labels that are 3 digits long (100 and up)

            if (number > 75) {
                // print the number and axis line without extra padding

                System.out.print(number + " |");
                // check every column in array to see if I need to draw a star for this row

                for (int j = 0; j < arr.length; j++) {
                    // If tallied frequency is greater than or equal to the current row's value print a star

                    if (arr[j] >= number) {
                        System.out.print("*  ");
                    } else {
                        // ELSE, print blank spaces to keep columns aligned.

                        System.out.print("   ");
                    }
                }
                // move to the next line after checking all columns for this row.

                System.out.println("");
                // use this block to format Y-axis labels that are 2 digits long (between 25 and 75).

            } else if (number != 0) {
                // add a single space of padding to keep the vertical bar aligned with the 3-digit numbers.

                System.out.print(" " + number + " |");
                for (int j = 0; j < arr.length; j++) {
                    // use the same logic here to draw stars or spaces 

                    if (arr[j] >= number) {
                        System.out.print("*  ");
                    } else {
                        System.out.print("   ");
                    }
                }
                System.out.println("");
                // use this final block to format SINGLE DIGIT row 

            } else {
                // add two spaces of padding so the 0 aligns perfectly under the tens and hundreds places

                System.out.print("  " + number + " |");
                for (int j = 0; j < arr.length; j++) {
                    //  print bottom row of stars or spaces.

                    if (arr[j] >= number) {
                        System.out.print("*  ");
                    } else {
                        System.out.print("   ");
                    }
                }
                System.out.println("");

            }
            //  subtract 25 from Y-axis value before moving down to the next row of graph

            number -= 25;
        }
        // print the bottom border of graph

        System.out.println("     --------------------------------");
        System.out.println("     2  3  4  5  6  7  8  9 10 11 12");
    }

}
