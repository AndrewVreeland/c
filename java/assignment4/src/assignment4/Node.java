/**
 * *Andrew Vreeland PID and NID *PID:5759863
 *
 * *NID:AN627713
 *
 * *This program is done for COP3330 course at year 2026 This program
 * *implements a Node class for use in a singly linked list
 */
package assignment4;

public class Node 
{
    // reference to the next node in the list
    private Node next;

    // data stored in the node cannot be changed after creation
    private final int data;

    // constructor sets data and initializes next to null
    public Node(int Gdata)
    {
        data = Gdata;
        next = null;
    }

    // sets the next node reference
    public void setNext(Node gNext)
    {
        next = gNext;
    }

    // returns the data stored in the node
    public int getData()
    {
        return data;
    }

    // returns the next node reference
    public Node getNext()
    {
        return next;
    }
}