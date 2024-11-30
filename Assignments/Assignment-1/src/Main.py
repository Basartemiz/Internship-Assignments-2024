board_file = input()
opponent_file = input()


# DO_NOT_EDIT_ANYTHING_ABOVE_THIS_LINE


def deep_copy(list):
    result_list = []
    for line in list:
        list1 = line.copy()
        result_list.append(list1)
    return result_list


# boardı oluşturuyoruz
boardfile = open(board_file, "r")
color = boardfile.readline()
pieces = []
for line in boardfile:
    pieces.append(line.split())
board = []
for a in range(8):
    temp = []
    for b in range(8):
        temp.append("--")
    board.append(temp)


def print_board(board1, bosluk):
    board_string = ""
    vertical = len(board1[0])
    horizontal = len(board1)
    count = 8
    for linex in range(len(board1) - 1, -1, -1):
        line = board1[linex]
        board_string += f"{count}{bosluk}"

        count -= 1
        for line2 in line:
            board_string += f"{line2}{bosluk}"

        board_string = board_string[:-len(bosluk)]
        board_string += "\n"
    board_string += f" {bosluk}a {bosluk}b {bosluk}c {bosluk}d {bosluk}e {bosluk}f {bosluk}g {bosluk}h"
    print(board_string)


##print_board(board,"     ")
for piece, position in pieces:
    p1 = position[0]
    p2 = position[1]
    p2 = int(p2) - 1
    if (p1 == "a"):
        p1 = 0
    elif (p1 == "b"):
        p1 = 1
    elif (p1 == "c"):
        p1 = 2
    elif (p1 == "d"):
        p1 = 3
    elif (p1 == "e"):
        p1 = 4
    elif (p1 == "f"):
        p1 = 5
    elif (p1 == "g"):
        p1 = 6
    elif (p1 == "h"):
        p1 = 7
    board[p2][p1] = piece
##print_board(board,"   ")
opponentfile = open(opponent_file, "r")
if color.strip() == "white":
    ourcolor = "white"
    opponentcolor = "black"

else:
    ourcolor = "black"
    opponentcolor = "white"


## ilgili fonksiyonları yazdırıyoruz

def pion_go(color1, board1, x, y):
    list_moves = []
    if (color1 == "white"):
        if (0 <= y + 1 <= 7 and 0 <= x <= 7):
            if (board1[y + 1][x] == "--"):
                list_moves.append([y, x, y + 1, x])
        if (0 <= y + 2 <= 7 and 0 <= x <= 7):
            if (board1[y + 2][x] == "--" and board1[y + 1][x] == "--"):
                list_moves.append([y, x, y + 2, x])
        if (0 <= y + 1 <= 7 and 0 <= x + 1 <= 7):
            if (board1[y + 1][x + 1] != "--" and board1[y + 1][x + 1][0].lower() != color1[0]):
                list_moves.append([y, x, y + 1, x + 1])
        if (0 <= y + 1 <= 7 and 0 <= x - 1 <= 7):
            if (board1[y + 1][x - 1] != "--" and board1[y + 1][x - 1][0].lower() != color1[0]):
                list_moves.append([y, x, y + 1, x - 1])
    if (color1 == "black"):
        if (0 <= y - 2 <= 7 and 0 <= x <= 7):
            if (board1[y - 1][x] == "--"):
                list_moves.append([y, x, y - 1, x])
        if (0 <= y - 1 <= 7 and 0 <= x <= 7):
            if (board1[y - 2][x] == "--" and board1[y - 1][x] == "--"):
                list_moves.append([y, x, y - 2, x])
        if (0 <= y - 1 <= 7 and 0 <= x + 1 <= 7):
            if (board1[y - 1][x + 1] != "--" and board1[y - 1][x + 1][0].lower() != color1[0]):
                list_moves.append([y, x, y - 1, x + 1])
        if (0 <= y - 1 <= 7 and 0 <= x - 1 <= 7):
            if (board1[y - 1][x - 1] != "--" and board1[y - 1][x - 1][0].lower() != color1[0]):
                list_moves.append([y, x, y - 1, x - 1])

    return list_moves


def rook_go(color1, board1, x, y):
    list_moves = []
    y1 = y - 1

    while y1 >= 0:
        if (board1[y1][x] == "--"):
            list_moves.append([y, x, y1, x])
            y1 -= 1
        else:
            if (board1[y1][x][0].lower() != color1[0]):
                list_moves.append([y, x, y1, x])
            break
    y1 = y + 1
    while y1 <= 7:
        if (board1[y1][x] == "--"):
            list_moves.append([y, x, y1, x])
            y1 += 1
        else:
            if (board1[y1][x][0].lower() != color1[0]):
                list_moves.append([y, x, y1, x])
            break

    x1 = x - 1
    while x1 >= 0:
        if (board1[y][x1] == "--"):
            list_moves.append([y, x, y, x1])
            x1 -= 1
        else:
            if (board1[y][x1][0].lower() != color1[0]):
                list_moves.append([y, x, y, x1])
            break
    x1 = x + 1
    while x1 <= 7:
        if (board1[y][x1] == "--"):
            list_moves.append([y, x, y, x1])
            x1 += 1
        else:
            if (board1[y][x1][0].lower() != color1[0]):
                list_moves.append([y, x, y, x1])
            break
    return list_moves


def knight_go(color1, board1, x, y):
    list1 = [2, -2]
    list2 = [1, -1]
    list_moves = []
    for a in list1:
        for b in list2:
            if (0 <= x + a <= 7 and 0 <= y + b <= 7):
                if (board1[y + b][x + a][0].lower() != color1[0]):
                    list_moves.append([y, x, y + b, x + a])
    for a in list2:
        for b in list1:
            if (0 <= x + a <= 7 and 0 <= y + b <= 7):
                if (board1[y + b][x + a][0].lower() != color1[0]):
                    list_moves.append([y, x, y + b, x + a])
    return list_moves


def bishop_go(color1, board1, x, y):
    list_moves = []

    x1 = x - 1
    y1 = y - 1
    while 0 <= x1 <= 7 and 0 <= y1 <= 7:
        if (board1[y1][x1] == "--"):
            list_moves.append([y, x, y1, x1])
            x1 = x1 - 1
            y1 -= 1
            continue
        else:
            if (board1[y1][x1][0].lower() != color1[0]):
                list_moves.append([y, x, y1, x1])
            break
    x1 = x - 1
    y1 = y + 1
    while 0 <= x1 <= 7 and 0 <= y1 <= 7:
        if (board1[y1][x1] == "--"):
            list_moves.append([y, x, y1, x1])
            x1 = x1 - 1
            y1 += 1
            continue
        else:
            if (board1[y1][x1][0].lower() != color1[0]):
                list_moves.append([y, x, y1, x1])
            break
    x1 = x + 1
    y1 = y - 1
    while 0 <= x1 <= 7 and 0 <= y1 <= 7:
        if (board1[y1][x1] == "--"):
            list_moves.append([y, x, y1, x1])
            x1 = x1 + 1
            y1 -= 1
            continue
        else:
            if (board1[y1][x1][0].lower() != color1[0]):
                list_moves.append([y, x, y1, x1])
            break
    x1 = x + 1
    y1 = y + 1
    while 0 <= x1 <= 7 and 0 <= y1 <= 7:
        if (board1[y1][x1] == "--"):
            list_moves.append([y, x, y1, x1])
            x1 = x1 + 1
            y1 += 1
            continue
        else:
            if (board1[y1][x1][0].lower() != color1[0]):
                list_moves.append([y, x, y1, x1])
            break
    return list_moves


def queen_go(color1, board1, x, y):
    list_moves = rook_go(color1, board1, x, y) + bishop_go(color1, board1, x, y)
    return list_moves


def king_go(color1, board1, x, y):
    list1 = [-1, 0, 1]
    list_moves = []
    for x1 in list1:
        for y1 in list1:
            if (x1 == 0 and y1 == 0):
                continue
            if (0 <= x + x1 <= 7 and 0 <= y + y1 <= 7 and board1[y + y1][x + x1][0].lower() != color1[0]):
                list_moves.append([y, x, y + y1, x + x1])
    return list_moves


def possible_moves(color1, board1):
    global ourcolor
    allmoves = []
    for y in range(len(board1)):
        for x in range(len(board1[y])):
            if (board1[y][x][0].lower() == color1[0]):
                item = board1[y][x][1]
                if (item == "P"):
                    allmoves += pion_go(color1, board1, x, y)
                elif (item == "R"):
                    allmoves += rook_go(color1, board1, x, y)
                elif (item == "N"):
                    allmoves += knight_go(color1, board1, x, y)
                elif (item == "B"):
                    allmoves += bishop_go(color1, board1, x, y)
                elif (item == "Q"):
                    allmoves += queen_go(color1, board1, x, y)
                if (color1 != ourcolor):
                    if (item == "K"):
                        allmoves += king_go(color1, board1, x, y)

    return allmoves


def isthere_check(board1):
    global opponentcolor
    global ourcolor
    king_position = []
    for y in range(len(board1)):
        for x in range(len(board1[y])):
            if (board1[y][x][1] == "K" and board1[y][x][0].lower() == opponentcolor[0]):
                king_position.append(y)
                king_position.append(x)
    allmoves = possible_moves(ourcolor, board1)
    for item in allmoves:
        item = [item[2], item[3]]
        if item == king_position:
            return True
        else:
            continue
    return False


## opponent hamlelerini çekiyoruz
opponent_moves = []
opponent_moves2 = []

for line in opponentfile:
    opponent_moves_line = []
    str1 = ""
    for charlen in range(len(line)):
        char = line[charlen]
        if (char != ","):
            str1 += char

        else:
            opponent_moves_line.append(str1)
            str1 = ""
    if (charlen == len(line) - 1):
        opponent_moves_line.append(str1)
    opponent_moves.append(opponent_moves_line)
for line in opponent_moves:
    opponent_moves3 = []
    for a in line:

        moves = a.split()

        if (moves[0][0] == "a"):
            moves[0] = "0" + moves[0][1]
        elif (moves[0][0] == "b"):
            moves[0] = "1" + moves[0][1]
        elif (moves[0][0] == "c"):
            moves[0] = "2" + moves[0][1]
        elif (moves[0][0] == "d"):
            moves[0] = "3" + moves[0][1]
        elif (moves[0][0] == "e"):
            moves[0] = "4" + moves[0][1]
        elif (moves[0][0] == "f"):
            moves[0] = "5" + moves[0][1]
        elif (moves[0][0] == "g"):
            moves[0] = "6" + moves[0][1]
        elif (moves[0][0] == "h"):
            moves[0] = "7" + moves[0][1]

        if (moves[1][0] == "a"):
            moves[1] = "0" + moves[1][1]
        elif (moves[1][0] == "b"):
            moves[1] = "1" + moves[1][1]
        elif (moves[1][0] == "c"):
            moves[1] = "2" + moves[1][1]
        elif (moves[1][0] == "d"):
            moves[1] = "3" + moves[1][1]
        elif (moves[1][0] == "e"):
            moves[1] = "4" + moves[1][1]
        elif (moves[1][0] == "f"):
            moves[1] = "5" + moves[1][1]
        elif (moves[1][0] == "g"):
            moves[1] = "6" + moves[1][1]
        elif (moves[1][0] == "h"):
            moves[1] = "7" + moves[1][1]
        moves1 = [int(moves[0][1]) - 1, int(moves[0][0]), int(moves[1][1]) - 1, int(moves[1][0])]
        opponent_moves3.append(moves1)
    opponent_moves2.append(opponent_moves3)

# print(opponent_moves2)
# print(opponent_moves)

## asıl fonsksiyonu yazıyoruz
our_moves = []
CheckMate = False

b = deep_copy(opponent_moves2)


def main(color1, board1, lastmove1, lastboard1):
    global CheckMate
    global ourcolor
    global opponentcolor
    global opponent_moves2
    global our_moves
    global b

    if (color1 == ourcolor):

        allmoves = possible_moves(color1, board1)
        kald = -1
        for move_count in range(len(allmoves)):

            move = allmoves[move_count]
            if (lastmove1 == ""):
                board2 = deep_copy(board1)
                board2[move[2]][move[3]] = board2[move[0]][move[1]]
                board2[move[0]][move[1]] = "--"

                return main(opponentcolor, board2, move, board1)
            else:
                if (move == lastmove1):
                    kald = move_count

                elif (kald >= 0):
                    board2 = deep_copy(board1)
                    board2[move[2]][move[3]] = board2[move[0]][move[1]]
                    board2[move[0]][move[1]] = "--"

                    return main(opponentcolor, board2, move, board1)
                elif (kald < 0):
                    continue
    else:
        allmoves = possible_moves(color1, board1)

        if (b == []):
            for move in allmoves:
                board2 = deep_copy(board1)
                board2[move[2]][move[3]] = board2[move[0]][move[1]]
                board2[move[0]][move[1]] = "--"
                if (isthere_check(board2) == False):
                    return main(ourcolor, lastboard1, lastmove1, lastboard1)
            CheckMate = True
            our_moves.append(lastmove1)

        else:
            oppo_moves = []
            for move in allmoves:
                board2 = deep_copy(board1)
                board2[move[2]][move[3]] = board2[move[0]][move[1]]
                board2[move[0]][move[1]] = "--"
                if (isthere_check(board2) == False):
                    oppo_moves.append([move[0], move[1], move[2], move[3]])

            c = deep_copy(b)
            c[0].sort()

            oppo_moves.sort()
            if (oppo_moves == c[0]):
                board2 = deep_copy(board1)
                move = b[0][0]
                board2[move[2]][move[3]] = board2[move[0]][move[1]]
                board2[move[0]][move[1]] = "--"
                our_moves.append(lastmove1)
                b.pop(0)

                main(ourcolor, board2, "", lastboard1)
                if (CheckMate == False):
                    our_moves.pop(len(our_moves) - 1)
                    b = [opponent_moves2[len(opponent_moves2) - len(b) - 1]] + b
                    main(ourcolor, lastboard1, lastmove1, lastboard1)
            else:
                return main(ourcolor, lastboard1, lastmove1, lastboard1)


main(ourcolor, board, "", board)


##moveları adam ediyoruz
def sayı_kelime(sayı):
    if (sayı == 0):
        return "a"
    if (sayı == 1):
        return "b"
    if (sayı == 2):
        return "c"
    if (sayı == 3):
        return "d"
    if (sayı == 4):
        return "e"
    if (sayı == 5):
        return "f"
    if (sayı == 6):
        return "g"
    if (sayı == 7):
        return "h"


def move_adam_et(moves):
    s = ""
    for move in moves:
        x1 = sayı_kelime(move[1])
        x2 = sayı_kelime(move[3])
        y1 = str(move[0] + 1)
        y2 = str(move[2] + 1)
        s += f"{x1}{y1} {x2}{y2}\n"
    s = s[:-1]
    return s


result = move_adam_et(our_moves)
print(result)

# DO_NOT_EDIT_ANYTHING_BELOW_THIS_LINE

