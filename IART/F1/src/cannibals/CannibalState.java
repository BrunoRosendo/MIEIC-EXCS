package cannibals;

import problemSolver.state.State;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class CannibalState extends State {
    private enum BoatPos {
        START,
        DEST
    }

    private final int nMisStart;
    private final int nCanStart;
    private final int nMisDest;
    private final int nCanDest;
    private final BoatPos boatPos;

    public CannibalState(int nMisStart, int nCanStart) {
        this(nMisStart, nCanStart, 0, 0, BoatPos.START, null);
    }

    private CannibalState(int nMisStart, int nCanStart, int nMisDest, int nCanDest, final BoatPos boatPos, final CannibalState parent) {
        super(parent);
        this.nMisStart = nMisStart;
        this.nCanStart = nCanStart;
        this.nMisDest = nMisDest;
        this.nCanDest = nCanDest;
        this.boatPos = boatPos;
    }

    @Override
    public List<State> getPossibleStates() {
        final List<State> possibleStates = new ArrayList<>();

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

    @Override
    public boolean test(final State target) {
        return this.nMisStart == 0 && this.nCanStart == 0;
    }

    private CannibalState transportMissionaries(int numMis) {
        return this.boatPos == BoatPos.START ?
                new CannibalState(
                        this.nMisStart - numMis,
                        this.nCanStart,
                        this.nMisDest + numMis,
                        this.nCanDest,
                        switchBoatPos(),
                        this
                ) :
                new CannibalState(
                        this.nMisStart + numMis,
                        this.nCanStart,
                        this.nMisDest - numMis,
                        this.nCanDest,
                        switchBoatPos(),
                        this
                );
    }

    private CannibalState transportCannibals(int numCan) {
        return this.boatPos == BoatPos.START ?
                new CannibalState(
                        this.nMisStart,
                        this.nCanStart - numCan,
                        this.nMisDest,
                        this.nCanDest + numCan,
                        switchBoatPos(),
                        this
                ) :
                new CannibalState(
                        this.nMisStart,
                        this.nCanStart + numCan,
                        this.nMisDest,
                        this.nCanDest - numCan,
                        switchBoatPos(),
                        this
                );
    }

    private CannibalState transportCannibalAndMissionary() {
        return this.boatPos == BoatPos.START ?
                new CannibalState(
                        this.nMisStart - 1,
                        this.nCanStart - 1,
                        this.nMisDest + 1,
                        this.nCanDest + 1,
                        switchBoatPos(),
                        this
                ) :
                new CannibalState(
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

        if (!(obj instanceof CannibalState)) {
            return false;
        }

        final CannibalState state = (CannibalState) obj;
        return this.nMisStart == state.nMisStart && this.nCanStart == state.nCanStart
                && this.nMisDest == state.nMisDest && this.nCanDest == state.nCanDest
                && this.boatPos == state.boatPos;
    }
}
