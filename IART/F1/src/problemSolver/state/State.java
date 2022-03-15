package problemSolver.state;

import java.util.List;

public abstract class State {
    private final State parent; // Auxiliary for constructing path
    private final int depth; // State's depth in the tree

    public State(State parent) {
        this.parent = parent;
        this.depth = parent == null ? 0 : parent.getDepth() + 1;
    }

    public State getParent() {
        return parent;
    }

    public int getDepth() {
        return depth;
    }

    public abstract List<State> getPossibleStates();
    public abstract boolean test(final State target);

    @Override
    public abstract String toString();

    @Override
    public abstract int hashCode();

    @Override
    public abstract boolean equals(Object obj);
}
