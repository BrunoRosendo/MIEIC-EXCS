package problemSolver.state;

public abstract class CostfulState extends State implements Comparable<CostfulState> {
    private final int cost;

    public CostfulState(final CostfulState parent, final int transitionCost) {
        super(parent);
        this.cost = (parent == null ? 0 : parent.cost) + transitionCost;
    }

    public int getCurrentCost() {
        return this.cost;
    }

    public abstract int getHeuristicCost();
}
