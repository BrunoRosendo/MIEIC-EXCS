package buckets;

import problemSolver.state.CostfulState;
import problemSolver.state.State;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class BucketState extends CostfulState {
    private final Bucket b1;
    private final Bucket b2;
    private int target;

    public BucketState(int start_b1, int start_b2, int max_b1, int max_b2, int target) {
        this(
                new Bucket(max_b1, start_b1),
                new Bucket(max_b2, start_b2),
                null,
                0
        );
        this.target = target;
    }

    private BucketState(final Bucket b1, final Bucket b2, final BucketState parent, final int transitionCost) {
        super(parent, transitionCost);
        this.b1 = b1;
        this.b2 = b2;
        target = parent != null ? parent.target : 0;
    }

    @Override
    public List<State> getPossibleStates() {
        final List<State> possibleStates = new ArrayList<>();

        if (b1.getQuantity() < b1.getCapacity()) possibleStates.add(this.fillB1());
        if (b2.getQuantity() < b2.getCapacity()) possibleStates.add(this.fillB2());
        if (b1.getQuantity() > 0) possibleStates.add(this.emptyB1());
        if (b2.getQuantity() > 0) possibleStates.add(this.emptyB2());
        if (b1.getQuantity() > 0 && b2.getQuantity() < b2.getCapacity())
            possibleStates.add(this.transfer(b1, b2, false));
        if (b2.getQuantity() > 0 && b1.getQuantity() < b1.getCapacity())
            possibleStates.add(this.transfer(b2, b1, true));

        return possibleStates;
    }

    @Override
    public boolean test(final State dummy) {
        return b1.getQuantity() == this.target;
    }

    private BucketState transfer(final Bucket b1, final Bucket b2, boolean revert) {
        Bucket newB1, newB2;

        if (b1.getQuantity() >= b2.getCapacity() - b2.getQuantity()) {
            newB1 = new Bucket(
                    b1.getCapacity(),
                    b1.getQuantity() - b2.getCapacity() + b2.getQuantity()
            );
            newB2 = new Bucket(b2.getCapacity(), b2.getCapacity());
        } else {
            newB1 = new Bucket(b1.getCapacity(), 0);
            newB2 = new Bucket(b2.getCapacity(), b1.getQuantity() + b2.getQuantity());
        }

        return revert ? new BucketState(newB2, newB1, this, 1) : new BucketState(newB1, newB2, this, 1);
    }

    private BucketState fillB1() {
        return new BucketState(b1.filled(), b2, this, 1);
    }

    private BucketState fillB2() {
        return new BucketState(b1, b2.filled(), this, 1);
    }

    private BucketState emptyB1() {
        return new BucketState(b1.empty(), b2, this, 1);
    }

    private BucketState emptyB2() {
        return new BucketState(b1, b2.empty(), this, 1);
    }

    @Override
    public String toString() {
        return "B1: " + b1.getQuantity() + " L, B2: " + b2.getQuantity() + " L";
    }

    @Override
    public int hashCode() {
        return Objects.hash(b1.getCapacity(), b1.getQuantity(), b2.getCapacity(), b2.getQuantity());
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) {
            return true;
        }

        if (!(obj instanceof BucketState)) {
            return false;
        }

        final BucketState state = (BucketState) obj;
        return this.b1.equals(state.b1)
                && this.b2.equals(state.b2);
    }

    @Override
    public int getHeuristicCost() {
        return Math.abs(b1.getQuantity() - target);
    }
}
