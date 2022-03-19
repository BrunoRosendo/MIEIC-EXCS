package nPuzzle;

import problemSolver.ProblemSolver;
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
        int choice = scanner.nextInt();

        final State targetState = PuzzleState.getWinningState(n);
        final State start = new PuzzleState(n);
        /*
        int[][] matrix = {
                {5, 1, 3, 4},
                {2, 0, 7, 8},
                {10, 6, 11, 12},
                {9, 13, 14, 15}
        };
        final State start = new PuzzleState(matrix);*/

        final ProblemSolver solver = new ProblemSolver(targetState);
        final List<State> states;

        switch (choice) {
            case 1 -> states = solver.bfs(start);
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
