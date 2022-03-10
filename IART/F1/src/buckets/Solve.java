package buckets;

import buckets.state.State;

import java.util.*;

public class Solve {
    public static final int IDS_DEPTH_LIMIT = 100;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

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

        Solve solve = new Solve();
        State start = new State(start_b1, start_b2, max_b1, max_b2);
        List<State> states;

        switch (choice) {
            case 1 -> states = solve.bfs(start, target);
            case 2 -> states = solve.dfs(start, target);
            case 3 -> states = solve.ids(start, target);
            default -> {
                System.out.println("Invalid choice!");
                return;
            }
        }

        for (State state : states) {
            System.out.println(state);
        }
    }

    List<State> bfs(State start, int target) {
        List<State> visitedStates = new ArrayList<>();
        Queue<State> nextStates = new LinkedList<>();

        while (start.hasNotReachedTarget(target)) {
            visitedStates.add(start);
            List<State> possibleStates = start.getPossibleStates();
            for (State state : possibleStates) {
                if (!visitedStates.contains(state))
                    nextStates.add(state);
            }
            start = nextStates.poll();
            if (start == null) {
                System.out.println("No solution found :(");
                return Collections.emptyList();
            }
        }

        List<State> path = new ArrayList<>();
        do {
            path.add(start);
            start = start.getParent();
        } while (start != null);
        Collections.reverse(path);

        return path;
    }

    List<State> dfs(State start, int target) {
        List<State> visitedStates = new ArrayList<>();
        Stack<State> nextStates = new Stack<>();

        while (start.hasNotReachedTarget(target)) {
            visitedStates.add(start);
            List<State> possibleStates = start.getPossibleStates();
            for (State state : possibleStates) {
                if (!visitedStates.contains(state))
                    nextStates.push(state);
            }

            try {
                start = nextStates.pop();
            } catch (EmptyStackException e) {
                System.out.println("No solution found :(");
                return Collections.emptyList();
            }
        }

        List<State> path = new ArrayList<>();
        do {
            path.add(start);
            start = start.getParent();
        } while (start != null);
        Collections.reverse(path);

        return path;
    }

    List<State> ids(State start, int target) {
        List<State> visitedStates = new ArrayList<>();
        Stack<State> nextStates = new Stack<>();
        State curState = start;

        int maxDepth = 1;

        while (curState.hasNotReachedTarget(target)) {
            visitedStates.add(curState);
            List<State> possibleStates = curState.getPossibleStates();
            for (State state : possibleStates) {
                if (!visitedStates.contains(state) && state.getDepth() <= maxDepth)
                    nextStates.push(state);
            }

            try {
                curState = nextStates.pop();
            } catch (EmptyStackException e) {
                if (maxDepth == IDS_DEPTH_LIMIT) {
                    System.out.println("No solution found :( Try to increase the depth limit");
                    return Collections.emptyList();
                }

                maxDepth++;
                curState = start;
                visitedStates.clear();
                nextStates.clear();
            }
        }

        List<State> path = new ArrayList<>();
        do {
            path.add(curState);
            curState = curState.getParent();
        } while (curState != null);
        Collections.reverse(path);

        return path;
    }
}
