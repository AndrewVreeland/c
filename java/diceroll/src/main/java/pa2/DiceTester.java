package pa2;

public class DiceTester {

    public static void main(String[] args) {
        int[] arr = new int[11];
        Dice dice = new Dice();
        for (int i = 0; i < 1000; i++) {
            dice.roll();
            int rolledValue = dice.getFaceValue();
            arr[rolledValue - 2]++;
        }
        for (int i = 0; i < arr.length; i++) {
            int number = i + 2;
            System.out.println("Number of " + number + "s are " + arr[i]);
        }

        System.out.println("Graph");
        int number = 175;
        for (int i = 0; i < 8; i++) {
            if (number > 75) {
                System.out.print(number + " |");
                for (int j = 0; j < arr.length; j++) {
                    if (arr[j] >= number) {
                        System.out.print("*  ");
                    } else {
                        System.out.print("   ");
                    }
                }
                System.out.println("");
            } else if (number != 0) {
                System.out.print(" " + number + " |");
                for (int j = 0; j < arr.length; j++) {
                    if (arr[j] >= number) {
                        System.out.print("*  ");
                    } else {
                        System.out.print("   ");
                    }
                }
                System.out.println("");

            } else {
                System.out.print("  " + number + " |");
                for (int j = 0; j < arr.length; j++) {
                    if (arr[j] >= number) {
                        System.out.print("*  ");
                    } else {
                        System.out.print("   ");
                    }
                }
                System.out.println("");

            }
            number -= 25;
        }
        System.out.println("     --------------------------------");
    }

}
