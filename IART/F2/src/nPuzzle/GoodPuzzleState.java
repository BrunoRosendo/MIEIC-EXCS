package nPuzzle;

public class GoodPuzzleState extends PuzzleState {
    public GoodPuzzleState(int n) {
        super(n);
    }

    public GoodPuzzleState(int[][] matrix) {
        super(matrix);
    }

    @Override
    public int getHeuristicCost() {
        int[][] correctMatrix = PuzzleState.buildWinningMatrix(matrix.length);
        int distance = 0;

        for (int i = 0; i < matrix.length; ++i)
            for (int j = 0; j < matrix[i].length; ++j) {
                int i0 = i, j0 = j;
                for (int a = 0; a < correctMatrix.length; ++a)
                    for (int b = 0; b < correctMatrix[a].length; ++b)
                        if (matrix[i][j] == correctMatrix[a][b]) {
                            i0 = a;
                            j0 = b;
                        }
                distance += Math.abs(i - i0) + Math.abs(j - j0);
            }

        return distance;
    }
}
