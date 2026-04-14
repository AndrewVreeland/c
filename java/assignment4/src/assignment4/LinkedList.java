/**
 * *Andrew Vreeland PID and NID *PID:5759863
 *
 * *NID:AN627713
 *
 * *This program is done for COP3330 course at year 2026 This program
 * *implements a LinkedList class that constructs processes and prints a linked list
 */
package assignment4;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class LinkedList {

    // head and tail of the linked list
    private Node head;
    private Node tail;

    // constructor initializes head and tail to null
    public LinkedList() {
        head = null;
        tail = null;
    }

    // sets the head node
    public void setHead(Node gHead) {
        head = gHead;
    }

    // sets the tail node
    public void setTail(Node gTail) {
        tail = gTail;
    }

    // returns the head node
    public Node getHead() {
        return head;
    }

    // returns the tail node
    public Node getTail() {
        return tail;
    }

    // appends a new node with given data to the end of the list
    public void insert(int data) {
        Node node = new Node(data);
        if (head == null) {
            head = node;
            tail = node;
        } else {
            tail.setNext(node);
            tail = node;
        }
    }

    // reads file and inserts positive numbers into the linked list
    public void construct(String fname) {
        try (BufferedReader br = new BufferedReader(new FileReader(fname))) {
            String line = br.readLine();
            String[] tokens = line.split(" ");
            for (String token : tokens) {
                int num = Integer.parseInt(token);
                // only insert positive numbers
                if (num > 0) {
                    insert(num);
                }
            }
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }

    // traverses the list and replaces pairs matching X[i] = X[i-1] * 2 + 7 with a count node
    public void process() {
        if (head == null) {
            return;
        }
        if (head.getNext() == null) {
            return;
        }

        int count = -100;
        Node anchor = head;
        Node prev = head;
        Node curr = head.getNext();

        // handles edge case where first two nodes need to be processed
        if (curr.getData() == prev.getData() * 2 + 7) {
            Node node = new Node(count);
            count++;
            node.setNext(head.getNext().getNext());
            head = node;
            curr = node.getNext().getNext();
            prev = node.getNext();
            anchor = node;
        }

        // traverse the rest of the list
        while (curr != null) {
            if (curr.getData() == prev.getData() * 2 + 7) {
                // condition met so replace prev and curr with count node
                Node node = new Node(count);
                count++;
                node.setNext(curr.getNext());
                anchor.setNext(node);
                anchor = node;
                prev = node.getNext();

                if (curr.getNext() == null) {
                    curr = null;
                } else {
                    curr = node.getNext().getNext();
                }
            } else {
                // advance all pointers
                anchor = prev;
                prev = curr;
                curr = curr.getNext();
            }
        }
        // append final count node at the end
        if (tail == null || tail.getData() >= 0) {
            insert(count);
        }
    }

    // writes the linked list elements to a file space separated
    public void printToFile(String fname) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter("processed" + fname))) {
            Node curr = head;
            while (curr != null) {
                bw.write(String.valueOf(curr.getData()));
                // add space between elements but not after the last one
                if (curr.getNext() != null) {
                    bw.write(" ");
                }
                curr = curr.getNext();
            }
        } catch (IOException e) {
            System.out.println("Error writing file: " + e.getMessage());
        }
        System.out.println("processed" + fname + " is created");
    }
}