package problemSolver;

import problemSolver.state.CostfulState;
import problemSolver.state.State;

import java.util.*;

public class CostfulProblemSolver extends ProblemSolver {
    public CostfulProblemSolver(final CostfulState targetState) {
        super(targetState);
    }

    static class UniformCostComparator implements Comparator<CostfulState> {
        @Override
        public int compare(CostfulState state1, CostfulState state2) {
            return state1.getCurrentCost() - state2.getCurrentCost();
        }
    }

    static class GreedyComparator implements Comparator<CostfulState> {
        @Override
        public int compare(CostfulState state1, CostfulState state2) {
            return state1.getHeuristicCost() - state2.getHeuristicCost();
        }
    }

    static class AStarComparator implements Comparator<CostfulState> {
        @Override
        public int compare(CostfulState state1, CostfulState state2) {
            return (state1.getCurrentCost() + state1.getHeuristicCost()) -
                    (state2.getCurrentCost() + state2.getHeuristicCost());
        }
    }

    public List<State> uniformCost(final CostfulState start) {
        return this.solveWithCost(start, new UniformCostComparator());
    }

    public List<State> greedy(final CostfulState start) {
        return this.solveWithCost(start, new GreedyComparator());
    }

    public List<State> AStar(final CostfulState start) {
        return this.solveWithCost(start, new AStarComparator());
    }

    private List<State> solveWithCost(CostfulState curNode, final Comparator<CostfulState> comparator) {
        final List<State> visitedStates = new ArrayList<>();
        final Queue<CostfulState> nextStates = new PriorityQueue<>(comparator);

        while (!curNode.test(this.targetState)) {
            visitedStates.add(curNode);
            final List<State> possibleStates = curNode.getPossibleStates();

            for (final State state : possibleStates) {
                if (!(state instanceof CostfulState)) continue;
                CostfulState costfulState = (CostfulState) state;
                if (!visitedStates.contains(state)) nextStates.add(costfulState);
            }

            curNode = nextStates.poll();
            if (curNode == null) {
                System.out.println("No solution found :(");
                return Collections.emptyList();
            }
        }

        return getPathFromFinalNode(curNode);
    }
}
