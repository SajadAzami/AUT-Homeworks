import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        long startTime = System.currentTimeMillis();
        findPi();
        long endTime = System.currentTimeMillis();
        long totalTime = endTime - startTime;
        System.out.println("Execution Time: " + totalTime + "ms");

    }

    private static void findPi() {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter Radius: ");
        final int radius = sc.nextInt();

        System.out.println("Enter Random Repetition Time: ");
        int randomReps = sc.nextInt();

        final ArrayList<Boolean> isInside = new ArrayList<>();
        final Random rnd = new Random();
        ArrayList<Thread> threads = new ArrayList<>();

        Runnable check = new Runnable() {
            @Override
            public void run() {
                double height = (rnd.nextInt(radius * 2)) - radius;
                double width = (rnd.nextInt(radius * 2)) - radius;
                if ((Math.pow(height, 2) + Math.pow(width, 2)) <= Math.pow(radius, 2)) {
                    isInside.add(true);
                }
            }
        };

        for (int i = 0; i < randomReps; i++) {
            threads.add(new Thread(check));
        }
        for (Thread thread : threads) {
            thread.start();
        }
        System.out.println("Pi: " + (double) (4 * isInside.size()) / (double) randomReps);
    }
}
