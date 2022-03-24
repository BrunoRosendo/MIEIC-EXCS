import numpy as np

BOARD_NUM_ROWS = 6
BOARD_NUM_COLS = 7

board = [[0 for _ in range(BOARD_NUM_ROWS)] for _ in range(BOARD_NUM_COLS)]
turn = 1

def printBoard():
    for i in range(BOARD_NUM_ROWS):
        for j in range(BOARD_NUM_COLS):
            print(board[j][i], end = " ")
        print()

def isColFull(col):
    return 0 not in board[col]

def getLastEmptyRow(col):
    column = board[col].copy()
    column.reverse()
    return BOARD_NUM_ROWS - column.index(0) - 1

def playPiece(col):
    if col < 0 or col >= BOARD_NUM_COLS or isColFull(col):
        print("Invalid choice! Noob")
        return False

    row = getLastEmptyRow(col)
    board[col][row] = turn

    return True


def getDiagonals():
    diags = []
    matrix = np.array(board)

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

def nlines4Horizontal(player):
    transposedBoard = np.transpose(board)
    return nlines4Vertical(player, transposedBoard)

def nlines4Diagonal(player):
    diags = getDiagonals()
    return nlines4Vertical(player, diags)


def nlines4(player):
    return nlines4Vertical(player) + nlines4Horizontal(player) + nlines4Diagonal(player)

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


def nlines3Horizontal(player):
    transposedBoard = np.transpose(board).tolist()
    return nlines3Vertical(player, transposedBoard)

def nlines3Diagonal(player):
    diags = getDiagonals()
    return nlines3Vertical(player, diags)

def nlines3(player):
    return nlines3Vertical(player) + nlines3Horizontal(player) + nlines3Diagonal(player)


def central(player):
    points = 0
    for i in range(-1, 2):
        col = board[BOARD_NUM_COLS // 2 + i]
        for cell in col:
            if cell == player:
                points += 2 if i == 0 else 1
    return points


def checkWinner():
    return nlines4(turn) > 0

while True:
    printBoard()
    col = int(input("Select the column: "))
    playPiece(col)

    if (checkWinner()):
        printBoard()
        print("Player {} won!".format(turn))
        break

    turn = 3 - turn
