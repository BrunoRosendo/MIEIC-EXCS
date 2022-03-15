package cannibals;

import problemSolver.ProblemSolver;
import problemSolver.state.State;

import java.util.*;

public class Main {
    public static void main(String[] args) {
        final Scanner scanner = new Scanner(System.in);

        System.out.print("Number of missionaries: ");
        int numMis = scanner.nextInt();

        System.out.print("Number of cannibals: ");
        int numCan = scanner.nextInt();

        System.out.println("Choose the type of algorithm:");
        System.out.println("1- BFS (breadth)");
        System.out.println("2- DFS (depth)");
        System.out.println("3- Iterative Deepening Strategy");
        int choice = scanner.nextInt();

        // Target state not needed
        final ProblemSolver solver = new ProblemSolver(null);
        final CannibalState start = new CannibalState(numMis, numCan);
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
