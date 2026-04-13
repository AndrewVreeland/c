package pa2;

/**
 * Andrew Vreeland PID and NID  *
 * PID:5759863
 *
 * *NID:AN627713 PA2 *This program is done for COP3330 course at year 2026. I
 * created this Dice class to represent a pair of dice. It uses two instances of
 * the Die class to let me roll both at once and get their combined total.
 */
public class Dice {
    // instantiate two Die objects made them final so references dont change

    private final Die Die1 = new Die();
    private final Die Die2 = new Die();
    // manually set the starting face value of both dice to 1

    Dice() {
        Die1.setFaceValue(1);
        Die2.setFaceValue(1);
    }
//  grab the total sum of the dice

    public int getFaceValue() {
        return Die1.getFaceValue() + Die2.getFaceValue();
    }
//  triggers the roll method on both die objects.

    public void roll() {
        Die1.roll();
        Die2.roll();
    }
}
