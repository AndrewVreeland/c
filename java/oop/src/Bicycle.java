import java.util.ArrayList;

public class Bicycle {
    private ArrayList<Wheel> wheels;

    public Bicycle(int numWheels) {
        wheels = new ArrayList<>();

        System.out.println("Bicycle is created");
        for (int i = 0; i < numWheels; i++) {
            wheels.add(new Wheel());
        }
    }

    public String toString()
    {
        StringBuilder sb = new StringBuilder();
        for(int i =0; i < wheels.size(); i++)
        {
            sb.append(wheels.get(i).toString());
            sb.append("\n");
        }

        return sb.toString();
    }

    public void flatIt()
    {
        System.out.println("Flat tyre");
    }

    public void go() {
        for (Wheel w : wheels) { // remember this?
            w.turn();
        }
        System.out.println("Bicycle is going");
    }
}