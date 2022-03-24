import numpy as np
import math

MINIMAX_DEPTH = 6
BOARD_NUM_ROWS = 6
BOARD_NUM_COLS = 7

board = [[0 for _ in range(BOARD_NUM_ROWS)] for _ in range(BOARD_NUM_COLS)]
turn = 1

def printBoard():
    for i in range(BOARD_NUM_ROWS):
        for j in range(BOARD_NUM_COLS):
            print(board[j][i], end = " ")
        print()

def isColFull(col, matrix = board):
    return 0 not in matrix[col]

def getLastEmptyRow(col, matrix = board):
    column = matrix[col].copy()
    column.reverse()
    return BOARD_NUM_ROWS - column.index(0) - 1

def playPiece(col, matrix = board, player = turn):
    if col < 0 or col >= BOARD_NUM_COLS or isColFull(col):
        print("Invalid choice! Noob")
        return False

    row = getLastEmptyRow(col, matrix)
    matrix[col][row] = player

    return True


def getDiagonals(matrix = board):
    diags = []
    matrix = np.array(matrix)

    for i in range(BOARD_NUM_COLS - 1):
        npDiag = np.diag(matrix, i)
        npDiag2 = np.diag(np.fliplr(matrix), i)

        diags.append(npDiag2.tolist())
        diags.append(npDiag.tolist())

    for i in range(BOARD_NUM_ROWS):
        npDiag = np.diag(matrix, -i - 1)
        npDiag2 = np.diag(np.fliplr(matrix), -i -1)

        diags.append(npDiag2.tolist())
        diags.append(npDiag.tolist())

    return diags


def nlines4Vertical(player, matrix = board):
    numLines = 0

    for col in matrix:
        counter = 0
        for cell in col:
            if (cell == player):
                counter += 1
                if (counter == 4):
                    numLines += 1
                    counter = 0
            else:
                counter = 0

    return numLines

def nlines4Horizontal(player, matrix = board):
    transposedBoard = np.transpose(matrix)
    return nlines4Vertical(player, transposedBoard)

def nlines4Diagonal(player, matrix = board):
    diags = getDiagonals(matrix)
    return nlines4Vertical(player, diags)


def nlines4(player, matrix = board):
    return nlines4Vertical(player, matrix) + nlines4Horizontal(player, matrix) + nlines4Diagonal(player, matrix)

def isLine3(line, player):
    return line.count(0) == 1 and line.count(player) == 3

# This does not account for lines3 which could be part of a line4 (the cell after or before)
def nlines3Vertical(player, matrix = board):
    numLines = 0

    for col in matrix:
        i = 0
        j = 4
        while (j <= len(col)):
            line = col[i:j]
            if isLine3(line, player):
                numLines += 1

            i += 1
            j += 1
    return numLines


def nlines3Horizontal(player, matrix = board):
    transposedBoard = np.transpose(matrix).tolist()
    return nlines3Vertical(player, transposedBoard)

def nlines3Diagonal(player, matrix = board):
    diags = getDiagonals(matrix)
    return nlines3Vertical(player, diags)

def nlines3(player, matrix = board):
    return nlines3Vertical(player, matrix) + nlines3Horizontal(player, matrix) + nlines3Diagonal(player, matrix)


def central(player, matrix = board):
    points = 0
    for i in range(-1, 2):
        col = matrix[BOARD_NUM_COLS // 2 + i]
        for cell in col:
            if cell == player:
                points += 2 if i == 0 else 1
    return points


def checkWinner(player):
    return nlines4(player) > 0

def minimaxPlay(player, depth, eval, matrix = board, alpha = -math.inf, beta = math.inf):
    if depth == 0 or checkWinner(3 - turn) or checkWinner(turn):
        return eval(player, matrix), -1

    bestPlay = 0
    if player == 2: # Bot -> Maximizing
        maxEval = -math.inf
        for i in range(BOARD_NUM_COLS):
            newMatrix = [col[:] for col in matrix]
            if isColFull(i, newMatrix):
                continue

            playPiece(i, newMatrix, player)
            evalRes = minimaxPlay(3 - player, depth - 1, eval, newMatrix, alpha, beta)[0]

            if evalRes > maxEval:
                maxEval = evalRes
                bestPlay = i

            alpha = max(alpha, evalRes)
            if beta <= alpha:
                break
        return maxEval, bestPlay
    else: # Player -> Minimizing
        newMatrix = [col[:] for col in matrix]
        minEval = math.inf
        for i in range(BOARD_NUM_COLS):
            if isColFull(i, newMatrix):
                continue

            playPiece(i, newMatrix, player)
            evalRes = minimaxPlay(3 - player, depth - 1, eval, newMatrix, alpha, beta)[0]

            if evalRes < minEval:
                minEval = evalRes
                bestPlay = i

            beta = min(beta, evalRes)
            if beta <= alpha:
                break
        return minEval, bestPlay


def eval1(player = turn, matrix = board):
    return nlines4(player, matrix) - nlines4(3 - player, matrix)

while True:
    printBoard()

    if turn == 1:
        col = int(input("Select the column: "))
    else:
        col = minimaxPlay(turn, MINIMAX_DEPTH, eval1)[1]
        input("The bot chose column {}".format(col))

    playPiece(col, board, turn)

    if (checkWinner(turn)):
        printBoard()
        print("Player {} won!".format(turn))
        break

    turn = 3 - turn
