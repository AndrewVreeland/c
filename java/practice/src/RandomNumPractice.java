

import java.util.Random;
import java.util.Scanner;

public class RandomNumPractice {

    
    public static void main(String args)
    {
        Scanner scanner = new Scanner(System.in);
        Random random = new Random();
    
        int randomNum = random.nextInt(100) + 1;
        System.out.println("pick a number between 1 and 100");
        int input = scanner.nextInt();
        int counter = 0;
        while(input != randomNum && counter < 11)
        {
            if(input > randomNum)
            {
                System.out.println("Your guess was too high");
            }else if(input < randomNum)
            {
                System.out.println("your guess was too low");
            }else
            {
                System.out.println("Congrats you guessed correctly!");
            }
            counter ++;
            System.out.println("guess again");
            input = scanner.nextInt();
        }
        System.out.println("The correct number is :" + randomNum);

        scanner.close();
    }

}
