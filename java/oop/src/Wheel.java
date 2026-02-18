import java.util.Random;

public class Wheel {

private int diameter;

Random random = new Random();
public Wheel()
{
    diameter = random.nextInt(20, 25); // between 20 and 24
    System.out.println("wheel created");
}

public void turn()
{
    System.out.println("Wheel is turning");
}

public String toString()
{
    StringBuilder sb = new StringBuilder();
    sb.append("The diameter of the wheel is :");
    sb.append(diameter);
    return sb.toString();
}
    
}
