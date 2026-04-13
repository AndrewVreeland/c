package com.example;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;

public class readwritesth {

public static ArrayList<String[]> readFile(String fName)
{
    try {
        BufferedReader bw = new BufferedReader(new FileReader(new File(dName)));
        String line = " ";
        While(line = br.readLine()) != null)
        {
            
        }
        
    } catch (Exception e) {
        e.printStackTrace();
    }
}

public static void writeFile(String dName, String[]arr  )
{
    try {
        BufferedWriter bw = new BufferedWriter(new FileWriter(dName));
        bw.write(arr[0] + ":"  + arr[1] + System.lineSeparator();
    } catch (Exception e) {
    }
}
}
