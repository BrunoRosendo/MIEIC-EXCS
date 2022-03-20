package nPuzzle;

import problemSolver.state.CostfulState;
import problemSolver.state.State;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

import static java.lang.Math.pow;

public class PuzzleState extends CostfulState {
    protected final int[][] matrix;
    private int emptyRow;
    private int emptyCol;

    public PuzzleState(int n) {
        this(buildWinningMatrix(n), 0, 0, null, 0);
        this.shuffle(matrix);
        this.setEmptyCell();
    }

    public PuzzleState(final int[][] matrix) {
        this(matrix, 0, 0, null, 0);
        this.setEmptyCell();
    }

    private PuzzleState(final int[][] matrix, int emptyRow, int emptyCol,
                        final PuzzleState parent, final int transitionCost) {
        super(parent, transitionCost);
        this.matrix = matrix;
        this.emptyRow = emptyRow;
        this.emptyCol = emptyCol;
    }

    private void setEmptyCell() {
        for (int i = 0; i < matrix.length; ++i)
            for (int j = 0; j < matrix[i].length; ++j)
                if (matrix[i][j] == 0) {
                    emptyRow = i;
                    emptyCol = j;
                    return;
                }
    }

    public static PuzzleState getWinningState(int n) {
        return new PuzzleState(buildWinningMatrix(n), n - 1, n - 1, null, 0);
    }

    @Override
    public List<State> getPossibleStates() {
        final List<State> possibleStates = new ArrayList<>();

        if (emptyCol < matrix[emptyRow].length - 1) {
            int[][] newMatrix = Arrays.stream(matrix).map(int[]::clone).toArray(int[][]::new);
            newMatrix[emptyRow][emptyCol] = matrix[emptyRow][emptyCol + 1];
            newMatrix[emptyRow][emptyCol + 1] = 0;
            possibleStates.add(new PuzzleState(newMatrix, emptyRow, emptyCol + 1, this, 1));
        }
        if (emptyCol > 0) {
            int[][] newMatrix = Arrays.stream(matrix).map(int[]::clone).toArray(int[][]::new);
            newMatrix[emptyRow][emptyCol] = matrix[emptyRow][emptyCol - 1];
            newMatrix[emptyRow][emptyCol - 1] = 0;
            possibleStates.add(new PuzzleState(newMatrix, emptyRow, emptyCol - 1, this, 1));
        }
        if (emptyRow < matrix.length - 1) {
            int[][] newMatrix = Arrays.stream(matrix).map(int[]::clone).toArray(int[][]::new);
            newMatrix[emptyRow][emptyCol] = matrix[emptyRow + 1][emptyCol];
            newMatrix[emptyRow + 1][emptyCol] = 0;
            possibleStates.add(new PuzzleState(newMatrix, emptyRow + 1, emptyCol, this, 1));
        }
        if (emptyRow > 0) {
            int[][] newMatrix = Arrays.stream(matrix).map(int[]::clone).toArray(int[][]::new);
            newMatrix[emptyRow][emptyCol] = matrix[emptyRow - 1][emptyCol];
            newMatrix[emptyRow - 1][emptyCol] = 0;
            possibleStates.add(new PuzzleState(newMatrix, emptyRow - 1, emptyCol, this, 1));
        }

        return possibleStates;
    }

    @Override
    public boolean test(final State target) {
        if (!(target instanceof PuzzleState))
            return false;

        final PuzzleState puzzleTarget = (PuzzleState) target;
        return this.equals(puzzleTarget);
    }

    protected static int[][] buildWinningMatrix(int n) {
        final int[][] winMatrix = new int[n][n];
        winMatrix[n-1][n-1] = 0;
        for (int i = 0; i < pow(n, 2) - 1; ++i) {
            int row = i / n;
            int col = i % n;
            winMatrix[row][col] = i + 1;
        }
        return winMatrix;
    }

    private void shuffle(int[][] a) {
        Random random = new Random();

        for (int i = a.length - 1; i > 0; i--) {
            for (int j = a[i].length - 1; j > 0; j--) {
                int m = random.nextInt(i + 1);
                int n = random.nextInt(j + 1);

                int temp = a[i][j];
                a[i][j] = a[m][n];
                a[m][n] = temp;
            }
        }
    }

    @Override
    public String toString() {
        return Arrays
                .stream(matrix)
                .map(Arrays::toString)
                .collect(Collectors.joining(System.lineSeparator())) + "\n";
    }

    @Override
    public int hashCode() {
        return Arrays.deepHashCode(matrix);
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) {
            return true;
        }

        if (!(obj instanceof PuzzleState)) {
            return false;
        }

        final PuzzleState state = (PuzzleState) obj;
        return Arrays.deepEquals(state.matrix, matrix);
    }

    /**
      Number of incorrectly placed pieces
     */
    @Override
    public int getHeuristicCost() {
        int incorrectPieces = 0;
        int[][] correctMatrix = PuzzleState.buildWinningMatrix(matrix.length);

        for (int i = 0; i < matrix.length; ++i)
            for (int j = 0; j < matrix[i].length; ++j)
                if (matrix[i][j] != correctMatrix[i][j])
                    incorrectPieces++;

        return incorrectPieces;
    }
}
