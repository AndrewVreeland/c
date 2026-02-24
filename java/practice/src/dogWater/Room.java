package dogWater;

import java.util.ArrayList;

public class Room {
    private int roomNumber;
    private String roomType;// single double suite
    private boolean occupied;

    public Room() {
        roomNumber = 1;
        roomType = "single";
        occupied = false;
    }

    public Room(int rn, String givenRoomType, boolean occ) {
        setRoomNumber(rn);
        // roomNumber = rn; is also possible
        // using the setters are more appropriate
        // so that we won't be adding invalid entries
        setRoomType(givenRoomType);
        // roomType = givenRoomType; is also possible
        occupied = occ;
    }

    public int getRoomNumber() {
        return roomNumber;
    }

    // this method should be only callable by the class
    // we will make this method private
    private void setRoomNumber(int rn) {
        roomNumber = rn;
    }

    public boolean isOccupied() {
        return occupied;
    }

    public void checkin() {
        if (!isOccupied()) {
            occupied = true;
        }
    }

    public void checkout() {
        occupied = false;
        // checking if occupied is redundant here
        // but to make it more appropriate we can check

    }

    public void setRoomType(String givenRoom) {
        if (givenRoom.equals("single") ||
                givenRoom.equals("double") || givenRoom.equals("suite")) {
            roomType = givenRoom;
        } else {
            System.out.println("Invalid room type entered");
        }
    }

    public String getRoomType() {
        return roomType;
    }

    public String toString() {
        String result = "number " + roomNumber;
        if (isOccupied())
            result += " is occupied";
        else
            result += " is vacant";
        return result;
    }

    public String showRoom() {
        String result = "[ ]"; // assume the room is vacant
        if (isOccupied())
            result = "[x]"; // if occupied change the output.
        return result;
    }

    public static void main(String[] args) {
        System.out.println("Showing the partA output below");
        // PART A
        Room room1 = new Room(101, "single", false);
        Room room2 = new Room(102, "double", false);
        Room room3 = new Room(103, "suite", true);

        String str = "hello my name is dog";
        System.out.println("this is the old str: " + str);
        String[] arr;
        arr = str.split("");
        for(int i = 0; i < arr.length; i ++)
        {
            if(arr[i].equals("o"))
            {arr[i] = "pop";}
        }
        String newStr = String.join("", arr);
        System.out.println("this is the joined arr : " + newStr);
        ArrayList<Room> hotel = new ArrayList<>();
        hotel.add(room1);
        hotel.add(room2);
        hotel.add(room3);
        // now let us change the room type of room at pos 1
        // hotel.get(1) will give/return us the Room object
        // for that room object we will change the roomType
        hotel.get(1).setRoomType("double");
        // room1.setRoomType("double"); will also work.
        for (int i = 0; i < hotel.size(); i++) {
            System.out.println(hotel.get(i).toString());
        }
        System.out.println("Showing the partB output below");
        // PART B
        Room[] arrHotel = new Room[3];
        Room room1array = new Room(101, "single", false);
        Room room2array = new Room(102, "double", false);
        Room room3array = new Room(103, "suite", true);
        arrHotel[0] = room1array;
        arrHotel[1] = room2array;
        arrHotel[2] = room3array;
        arrHotel[1].checkin();
        // room2array.checkin(); will also work
        // now we have 2 occupied rooms
        for (int i = 0; i < arrHotel.length; i++) {
            System.out.print(arrHotel[i].showRoom());
        } // end of for loop for array
    }// end of main
}
