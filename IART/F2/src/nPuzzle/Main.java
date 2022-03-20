package nPuzzle;

import problemSolver.CostfulProblemSolver;
import problemSolver.state.CostfulState;
import problemSolver.state.State;

import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        final Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the N-Puzzle Solver :D");
        System.out.print("Side of the matrix (NxN): ");
        int n = scanner.nextInt();

        System.out.println("Choose the type of algorithm:");
        System.out.println("1- Uniform Cost (BFS)");
        System.out.println("2- Greedy");
        System.out.println("3- A*");
        int choice = scanner.nextInt();

        final CostfulState targetState = GoodPuzzleState.getWinningState(n);
        final CostfulState start = new GoodPuzzleState(n);
/*
        int[][] matrix = {
                {5, 1, 3, 4},
                {2, 0, 7, 8},
                {10, 6, 11, 12},
                {9, 13, 14, 15}
        };
        final CostfulState start = new GoodPuzzleState(matrix);*/

        final CostfulProblemSolver solver = new CostfulProblemSolver(targetState);
        final List<State> states;

        switch (choice) {
            case 1 -> states = solver.bfs(start);
            case 2 -> states = solver.greedy(start);
            case 3 -> states = solver.AStar(start);
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
