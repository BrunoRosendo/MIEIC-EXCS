package buckets;

import problemSolver.CostfulProblemSolver;
import problemSolver.state.State;

import java.util.List;
import java.util.Scanner;

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
        System.out.println("1- BFS (Uniform Cost)");
        System.out.println("2- DFS (depth)");
        System.out.println("3- Iterative Deepening Strategy");
        System.out.println("4- Greedy");
        System.out.println("5- A*");
        int choice = scanner.nextInt();

        final BucketState start = new BucketState(start_b1, start_b2, max_b1, max_b2, target);

        final CostfulProblemSolver solver = new CostfulProblemSolver(null);
        final List<State> states;

        switch (choice) {
            case 1 -> states = solver.uniformCost(start);
            case 2 -> states = solver.dfs(start);
            case 3 -> states = solver.ids(start);
            case 4 -> states = solver.greedy(start);
            case 5 -> states = solver.AStar(start);
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
