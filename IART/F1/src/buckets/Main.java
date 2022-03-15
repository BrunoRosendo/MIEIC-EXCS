package buckets;

import problemSolver.ProblemSolver;
import problemSolver.state.State;

import java.util.*;

public class Main {
    public static void main(String[] args) {
        final Scanner scanner = new Scanner(System.in);

        System.out.print("Target quantity (L): ");
        int target = scanner.nextInt();

        System.out.print("Capacity of bucket 1 (L): ");
        int max_b1 = scanner.nextInt();
        System.out.print("Capacity of bucket 2 (L): ");
        int max_b2 = scanner.nextInt();

        System.out.print("Start of bucket 1 (L): ");
        int start_b1 = scanner.nextInt();
        System.out.print("Start of bucket 2 (L): ");
        int start_b2 = scanner.nextInt();

        System.out.println("Choose the type of algorithm:");
        System.out.println("1- BFS (breadth)");
        System.out.println("2- DFS (depth)");
        System.out.println("3- Iterative Deepening Strategy");
        int choice = scanner.nextInt();

        // Only B1's quantity is important
        final State targetState = new BucketState(target, 0, 0, 0);
        final BucketState start = new BucketState(start_b1, start_b2, max_b1, max_b2);

        final ProblemSolver solver = new ProblemSolver(targetState);
        final List<State> states;

        switch (choice) {
            case 1 -> states = solver.bfs(start);
            case 2 -> states = solver.dfs(start);
            case 3 -> states = solver.ids(start);
            default -> {
                System.out.println("Invalid choice!");
                return;
            }
        }

        for (final State state : states) {
            System.out.println(state);
        }
    }
}
