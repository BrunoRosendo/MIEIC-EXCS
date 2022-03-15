package problemSolver;

import problemSolver.state.State;

import java.util.*;

public class ProblemSolver {
    private int depthLimit = 100;
    private final State targetState;

    public ProblemSolver(final State targetState) {
        this.targetState = targetState;
    }

    public List<State> bfs(State curNode) {
        final List<State> visitedStates = new ArrayList<>();
        final Queue<State> nextStates = new LinkedList<>();

        while (!curNode.test(this.targetState)) {
            visitedStates.add(curNode);
            final List<State> possibleStates = curNode.getPossibleStates();

            for (final State state : possibleStates) {
                if (!visitedStates.contains(state)) nextStates.add(state);
            }

            curNode = nextStates.poll();
            if (curNode == null) {
                System.out.println("No solution found :(");
                return Collections.emptyList();
            }
        }

        return getPathFromFinalNode(curNode);
    }

    public List<State> dfs(State curNode) {
        final List<State> visitedStates = new ArrayList<>();
        final Stack<State> nextStates = new Stack<>();

        while (!curNode.test(this.targetState)) {
            visitedStates.add(curNode);
            final List<State> possibleStates = curNode.getPossibleStates();

            for (final State state : possibleStates) {
                if (!visitedStates.contains(state)) nextStates.push(state);
            }

            try {
                curNode = nextStates.pop();
            } catch (final EmptyStackException e) {
                System.out.println("No solution found :(");
                return Collections.emptyList();
            }
        }

        return getPathFromFinalNode(curNode);
    }

    public List<State> ids(final State start) {
        final List<State> visitedStates = new ArrayList<>();
        final Stack<State> nextStates = new Stack<>();

        State curNode = start;
        int maxDepth = 1;

        while (!curNode.test(this.targetState)) {
            visitedStates.add(curNode);
            final List<State> possibleStates = curNode.getPossibleStates();

            for (final State state : possibleStates) {
                if (!visitedStates.contains(state) && state.getDepth() <= maxDepth)
                    nextStates.push(state);
            }

            try {
                curNode = nextStates.pop();
            } catch (final EmptyStackException e) {
                if (maxDepth == this.depthLimit) {
                    System.out.println("No solution found :( Try to increase the depth limit");
                    return Collections.emptyList();
                }

                maxDepth++;
                curNode = start;
                visitedStates.clear();
                nextStates.clear();
            }
        }

        return getPathFromFinalNode(curNode);
    }

    public void setDepthLimit(int limit) {
        this.depthLimit = limit;
    }

    private List<State> getPathFromFinalNode(State curNode) {
        final List<State> path = new ArrayList<>();

        do {
            path.add(curNode);
            curNode = curNode.getParent();
        } while (curNode != null);
        Collections.reverse(path);

        return path;
    }
}
