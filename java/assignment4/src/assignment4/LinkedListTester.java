/**
 * *Andrew Vreeland PID and NID *PID:5759863
 *
 * *NID:AN627713
 *
 * *This program is done for COP3330 course at year 2026 This program
 * *reads a file builds a linked list processes it and writes output to a file
 */
package assignment4;

import java.util.Scanner;

public class LinkedListTester {

    public static void main(String[] args) 
    {
        LinkedList list = new LinkedList();
        // closes scanner after use
        try(Scanner scanner = new Scanner(System.in))
        {
            // prompt user for file name
            System.out.println("Enter the data file name:");
            String fname = scanner.nextLine();
            // build the linked list from the file
            list.construct(fname);
            // process the linked list
            list.process();
            // write the processed list to a file
            list.printToFile(fname);
        }
    }
}