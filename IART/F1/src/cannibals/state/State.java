package cannibals.state;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class State {
    private enum BoatPos {
        START,
        DEST
    }

    private final int nMisStart;
    private final int nCanStart;
    private final int nMisDest;
    private final int nCanDest;
    private final BoatPos boatPos;

    private final State parent; // Auxiliary for constructing path
    private final int depth; // Auxiliary for IDS

    public State() { // Example default
        this(3, 3);
    }

    public State(int nMisStart, int nCanStart) {
        this(nMisStart, nCanStart, 0, 0, BoatPos.START, null);
    }

    private State(int nMisStart, int nCanStart, int nMisDest, int nCanDest, BoatPos boatPos, State parent) {
        this.nMisStart = nMisStart;
        this.nCanStart = nCanStart;
        this.nMisDest = nMisDest;
        this.nCanDest = nCanDest;
        this.boatPos = boatPos;
        this.parent = parent;
        this.depth = parent == null ? 0 : parent.getDepth() + 1;
    }

    public List<State> getPossibleStates() {
        List<State> possibleStates = new ArrayList<>();

        switch (this.boatPos) {
            case START -> {
                if ((nMisStart > nCanStart || nMisStart == 1) && nMisDest + 1 >= nCanDest)
                    possibleStates.add(transportMissionaries(1));
                if ((nMisStart > nCanStart + 1 || nMisStart == 2) && nMisDest + 2 >= nCanDest)
                    possibleStates.add(transportMissionaries(2));
                if ((nMisDest > nCanDest || nMisDest == 0) && nCanStart > 0)
                    possibleStates.add(transportCannibals(1));
                if ((nMisDest > nCanDest + 1 || nMisDest == 0) && nCanStart > 1)
                    possibleStates.add(transportCannibals(2));
                if (nMisStart > 0 && nCanStart > 0 && nMisDest >= nCanDest)
                    possibleStates.add(transportCannibalAndMissionary());
            }
            case DEST -> {
                if ((nMisDest > nCanDest || nMisDest == 1) && nMisStart + 1 >= nCanStart)
                    possibleStates.add(transportMissionaries(1));
                if ((nMisDest > nCanDest + 1 || nMisDest == 2) && nMisStart + 2 >= nCanStart)
                    possibleStates.add(transportMissionaries(2));
                if ((nMisStart > nCanStart || nMisStart == 0) && nCanDest > 0)
                    possibleStates.add(transportCannibals(1));
                if ((nMisStart > nCanStart + 1 || nMisStart == 0) && nCanDest > 1)
                    possibleStates.add(transportCannibals(2));
                if (nMisDest > 0 && nCanDest > 0 && nMisDest >= nCanDest)
                    possibleStates.add(transportCannibalAndMissionary());
            }
        }

        return possibleStates;
    }

    public boolean anyoneOnStart() {
        return this.nMisStart != 0 || this.nCanStart != 0;
    }

    private State transportMissionaries(int numMis) {
        return this.boatPos == BoatPos.START ?
                new State(
                        this.nMisStart - numMis,
                        this.nCanStart,
                        this.nMisDest + numMis,
                        this.nCanDest,
                        switchBoatPos(),
                        this
                ) :
                new State(
                        this.nMisStart + numMis,
                        this.nCanStart,
                        this.nMisDest - numMis,
                        this.nCanDest,
                        switchBoatPos(),
                        this
                );
    }

    private State transportCannibals(int numCan) {
        return this.boatPos == BoatPos.START ?
                new State(
                        this.nMisStart,
                        this.nCanStart - numCan,
                        this.nMisDest,
                        this.nCanDest + numCan,
                        switchBoatPos(),
                        this
                ) :
                new State(
                        this.nMisStart,
                        this.nCanStart + numCan,
                        this.nMisDest,
                        this.nCanDest - numCan,
                        switchBoatPos(),
                        this
                );
    }

    private State transportCannibalAndMissionary() {
        return this.boatPos == BoatPos.START ?
                new State(
                        this.nMisStart - 1,
                        this.nCanStart - 1,
                        this.nMisDest + 1,
                        this.nCanDest + 1,
                        switchBoatPos(),
                        this
                ) :
                new State(
                        this.nMisStart + 1,
                        this.nCanStart + 1,
                        this.nMisDest - 1,
                        this.nCanDest - 1,
                        switchBoatPos(),
                        this
                );
    }

    private BoatPos switchBoatPos() {
        return this.boatPos == BoatPos.START ?
                BoatPos.DEST : BoatPos.START;
    }

    public State getParent() {
        return parent;
    }

    public int getDepth() {
        return depth;
    }

    @Override
    public String toString() {
        return "nMisStart: " + nMisStart + ", nCanStart: " + nCanStart +
                ", nMisDest: " + nMisDest + ", nCanDest: " + nCanDest +
                ", boat: " + boatPos;
    }

    @Override
    public int hashCode() {
        return Objects.hash(nMisStart, nMisDest, nCanStart, nCanDest, boatPos);
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
        return this.nMisStart == state.nMisStart && this.nCanStart == state.nCanStart
                && this.nMisDest == state.nMisDest && this.nCanDest == state.nCanDest
                && this.boatPos == state.boatPos;
    }
}
