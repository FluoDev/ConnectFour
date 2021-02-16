#include <stdio.h>

char grid[6][7];
int directions[8][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1},\
  {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void initGrid(void)
{
  // To initialize the grid
  for (int i = 0; i < 6; ++i)
  {
    for (int j = 0; j < 7; ++j)
    {
      grid[i][j] = ' ';
    }
  }
}

void showGrid(void)
{
  // To draw the grid
  printf("  1   2   3   4   5   6   7  \n");
  printf("+---+---+---+---+---+---+---+\n");
  for (int i = 0; i < 6; ++i)
  {
    printf("| %c | %c | %c | %c | %c | %c | %c |\n",
           grid[i][0], grid[i][1], grid[i][2], grid[i][3],
           grid[i][4], grid[i][5], grid[i][6]);
    printf("+---+---+---+---+---+---+---+\n");
  }
  printf("  1   2   3   4   5   6   7  \n");
}

_Bool recur(int x, int y, int direction[2], int searchingPawn, int depth)
{
  if (depth == 4) // If 4 pawns in a line
    return 1;
  // Else seek for the next pawn
  int i = x + direction[0];
  int j = y + direction[1];
  // Check if it's in the grid
  if (0 <= i && i < 7 && 0 <= j < 6)
  {
    // If the pawn is the right color
    if (grid[i][j] == searchingPawn)
    {
      // Go on
      return recur(i, j, direction, searchingPawn, depth+1);
    }
  }
  // Didn't win yet
  return 0;
}

int checkWin(void)
{
  for (int i = 0; i < 6; ++i)
  {
    for (int j = 0; j < 7; ++j)
    {
      if (grid[i][j] != ' ')
      {
        for (int dir = 0; dir < 8; ++dir)
        {
          if (recur(i, j, directions[dir], grid[i][j], 1))
          {
            switch (grid[i][j])
            {
              case 'O':
                return 1;
              case 'X':
                return 2;
            }
          }
        }
      }
    }
  }

  return 0;
}


int main(void)
{
  _Bool ended = 0;
  int winner = 0;
  int playerTurn = 1;

  initGrid();

  while (!ended)
  {
    showGrid();
    // Game Part
    int column = -1; // Column = the col chosen
    while (column < 1 || column > 7) {
      printf("\n\tJoueur %d : ", playerTurn);
      if (scanf("%d", &column) != 1)
      {
        column = -1;
        printf("\nErreur lors de la saisie.\n");
      }
      while(getchar() != '\n');
    }
    --column; 
    // Seek an empty row
    for (int i = 5; i >= 0; --i)
    {
      if (grid[i][column] == ' ')
      {
        switch (playerTurn)
        {
        case 1:
          grid[i][column] = 'O';
          playerTurn = 2;
          break;
        case 2:
          grid[i][column] = 'X';
          playerTurn = 1;
          break;
        }
        break;
      }
    }
    // Check if someone won
    winner = checkWin();
    if (winner != 0)
    {
      ended = 1;
    }
  }

  printf("Le joueur %d a gagné !\n", winner);
  showGrid();

  return 0;
}
