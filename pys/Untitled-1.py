board = [['-' for i in range(10)] for j in range(10)]

def print_board(board):
  for row in board:
    print(' '.join(row))

def place_piece(board, player, row, col):
  if board[row][col] == '-':
    board[row][col] = player
    return True
  else:
    return False

def check_win(board, player):
  # check rows
  for i in range(10):
    if board[i] == [player] * 10:
      return True

  # check columns
  for j in range(10):
    if all(board[i][j] == player for i in range(10)):
      return True

  # check diagonals
  if all(board[i][i] == player for i in range(10)):
    return True
  if all(board[i][9-i] == player for i in range(10)):
    return True

  return False

def play_game():
  current_player = 'X'
  while True:
    print_board(board)
    row = int(input('Enter row for player ' + current_player + ': '))
    col = int(input('Enter column for player ' + current_player + ': '))

    if not place_piece(board, current_player, row, col):
      print('Invalid move, try again.')
      continue

    if check_win(board, current_player):
      print('Player ' + current_player + ' wins!')
      break

    if current_player == 'X':
      current_player = 'O'
    else:
      current_player = 'X'

play_game()
