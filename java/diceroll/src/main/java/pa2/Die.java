package pa2;

import java.util.Random;

public class Die {
    private static  final Random random = new Random();
    private int faceValue;
    
    Die()
    {
        faceValue = 1;
    }

    public int getFaceValue() {
        return faceValue;
    }

    public void setFaceValue(int value)
    {
        faceValue = value;
    }

    public void roll()
    {
        int randomNum = random.nextInt(0 , 6) + 1;
        faceValue = randomNum;
    }
}