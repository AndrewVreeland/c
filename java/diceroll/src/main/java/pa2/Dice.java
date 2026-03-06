package pa2;

public class Dice {
    private final Die Die1 = new Die();
    private final Die Die2 = new Die();
    
    Dice()
    {
    Die1.setFaceValue(1);
    Die2.setFaceValue(1);
}

public int getFaceValue()
{
    return Die1.getFaceValue() + Die2.getFaceValue();
}

public void roll()
{
    Die1.roll();
    Die2.roll();
}
}
