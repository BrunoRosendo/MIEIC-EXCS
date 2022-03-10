package buckets.state;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class State {
    private final Bucket b1;
    private final Bucket b2;
    private final State parent; // Auxiliary for BFS

    public State(int start_b1, int start_b2, int max_b1, int max_b2) {
        this.b1 = new Bucket(max_b1, start_b1);
        this.b2 = new Bucket(max_b2, start_b2);
        this.parent = null;
    }

    public State() { // Example default
        this.b1 = new Bucket(4, 0);
        this.b2 = new Bucket(3, 0);
        this.parent = null;
    }

    private State(Bucket b1, Bucket b2, State parent) {
        this.b1 = b1;
        this.b2 = b2;
        this.parent = parent;
    }

    public List<State> getPossibleStates() {
        List<State> possibleStates = new ArrayList<>();

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

    public boolean validate(int target) {
        return b1.getQuantity() == target;
    }

    public State getParent() {
        return parent;
    }

    private State transfer(Bucket b1, Bucket b2, boolean revert) {
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

        return revert ? new State(newB2, newB1, this) : new State(newB1, newB2, this);
    }

    private State fillB1() {
        return new State(b1.filled(), b2, this);
    }

    private State fillB2() {
        return new State(b1, b2.filled(), this);
    }

    private State emptyB1() {
        return new State(b1.empty(), b2, this);
    }

    private State emptyB2() {
        return new State(b1, b2.empty(), this);
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

        if (!(obj instanceof State)) {
            return false;
        }

        State state = (State) obj;
        return this.b1.equals(state.b1)
                && this.b2.equals(state.b2);
    }
}