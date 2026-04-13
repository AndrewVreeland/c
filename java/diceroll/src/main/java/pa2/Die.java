package pa2;

import java.util.Random;

/**
 *  * Andrew Vreeland PID and NID * PID:5759863
 *
 * *NID:AN627713 PA2 *This program is done for COP3330 course at year 2026. I
 * created this Die class to simulate a single six-sided die. It keeps track of
 * its own face value and has a method so I can roll it to get a new random
 * value between 1 and 6.
 */
public final class Die {

    //  use a static Random object here as to not instantiate a new random number generator for every single die instance
    private static final Random random = new Random();
    // This variable holds the current number showing on die
    private int faceValue;

    // constructor sets the default face value to 1 when new die is created
    Die() {
        setFaceValue(1);
    }

    // call this method to return value of die
    public int getFaceValue() {
        return faceValue;
    }

    // allows the manual setting of the die
    public void setFaceValue(int value) {
        faceValue = value;
    }

    // method to roll the die.
    public void roll() {
        // generate a random integer from 0 to 5, and then add 1
        int randomNum = random.nextInt(0, 6) + 1;
        //  assign the newly rolled number to faceValue variable
        faceValue = randomNum;
    }
}
