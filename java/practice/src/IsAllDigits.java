import java.util.Scanner;

public class IsAllDigits {

    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        boolean outcome = isAllDigits(scanner);
        if(outcome)
        {
            System.out.println("Congrats you have a proper Stirng");
        }else {
            System.out.println("Your string is not all digits");
        }


    }

    public static boolean isAllDigits(Scanner scanner)
    {
        System.out.println("Please input a string");
        String input = scanner.nextLine();
        String inputArr[] = input.split("");
        String inputCheck[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        
        while(input.compareTo("") == 0)
        {
            System.out.println("Please input a proper String, no empty Strings");
            input = scanner.nextLine();
        }

        for(int i = 0; i < inputArr.length; i ++)
        {
            for(int j = 0; j < inputCheck.length; j++)
            {
                if(!inputCheck[j].contains(inputArr[i]))
                    {
                       return false;
                    }

            }
        }
        return true;
    }

}
