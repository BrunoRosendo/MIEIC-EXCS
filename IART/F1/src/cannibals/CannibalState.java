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

        possibleStates.add(transportMissionaries(1));
        possibleStates.add(transportMissionaries(2));
        possibleStates.add(transportCannibals(1));
        possibleStates.add(transportCannibals(2));
        possibleStates.add(transportCannibalAndMissionary());

        possibleStates.removeIf(s -> !CannibalState.isStateValid(s));
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

    private static boolean isStateValid(final State state) {
        if (!(state instanceof CannibalState))
            return false;
        final CannibalState cannibalState = (CannibalState) state;

        return (
                cannibalState.nMisStart >= cannibalState.nCanStart ||
                cannibalState.nMisStart == 0
        ) && (
                cannibalState.nMisDest >= cannibalState.nCanDest ||
                cannibalState.nMisDest == 0
            );
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
