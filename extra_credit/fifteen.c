/**
 * fifteen.c
 *
 * Refer to Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

#ifndef INT_MAX
    #define INT_MAX 12345678
#endif // INT_MAX

// board
//int board[DIM_MAX][DIM_MAX];

// dimensions
//int d; removed

// prototypes
void greet(void);
void init(int **board, int d);
void draw(int **board, int d);
short move(int **board, int d, int tile);
short won(int **board, int d);
int get_int();

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    //initializing dimension size
    int d = atoi(argv[1]);

     // ensure valid dimensions
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }
   
    //allocating heap memory for board row pointers
    int **board = malloc(sizeof(int*) * d);

    //allocating memory for each row's integer pointers
    for(int i = 0; i < d; ++i) {
        board[i] = malloc(sizeof(int) * d);
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init(board, d);

    // accept moves until game is won
    while (1)
    {
        // draw the current state of the board
        draw(board, d);

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won(board, d))
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        printf("\n");

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(board, d, tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(50000);
    }

    // close log
    fclose(file);

    //clearing heap memory
    for(int i = 0; i < d; ++i) {
        free(board[i]);
    }
    free(board);

    // success
    return 0;
}

/**
 * Get an non-negative integer from user input
 * If the input is not non-negative integer, return INT_MAX
 */
 int get_int()
 {
    int input = 0;
    short invalid = 0;

    char c = getchar();
    if (c == '\n')
        return INT_MAX;

    while (c != '\n') 
    {
        if ((c >= '0') && ( c <= '9'))
        {
            input = input * 10 + (c - '0');
        } else {
            invalid = 1;
        }

        c = getchar();
    }

    if (invalid)
        return INT_MAX;
    else 
        return input;
 }

/**
 * Greets player.
 */
void greet(void)
{    
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(int **board, int d)
{
    int insert = (d * d) - 1;
    for(int i = 0; i < d; ++i) {
        for(int j = 0; j < d; ++j) {
            board[i][j] = insert; //zero is the value placed in the blank cell.
            insert--;
        }
    }

    if(d % 2 == 0) { //For even sided game the 1 and 2 are swapped.
        board[d - 1][d - 3] = 1;
        board[d - 1][d - 2] = 2;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(int **board, int d)
{
    for(int i = 0; i < d; ++i) {
        printf("  "); //Indent space before grid of numbers
        for(int j = 0; j < d; ++j) {
            if(board[i][j] == 0) { //for printing the special case underscore
                printf("_   ");
            } else {
                printf("%d  ",board[i][j]); //prints number and spacing
                if(board[i][j] <= 9) { //adding extra sapcing for one digit numbers
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * If tile borders empty space, moves tile and returns 1, else
 * returns 0.
 */
short move(int **board, int d,int tile)
{
    for(int i = 0; i < d; ++i) {
        for(int j = 0; j < d; ++j) {
            if(tile == board[i][j]) { //when the tile is found, the checks begin
                if(i + 1 < d && board[i + 1][j] == 0) { //space below tile
                    board[i+1][j] = tile; //assigning tile value to empty space
                    board[i][j] = 0; //assigning zero to tile space
                    return 1;
                }
                if(i - 1 >= 0 && board[i - 1][j] == 0) {//space above tile
                    board[i-1][j] = tile;
                    board[i][j] = 0;
                    return 1;
                }
                if(j - 1 >= 0 && board[i][j - 1] == 0) {//space left of the tile
                    board[i][j-1] = tile;
                    board[i][j] = 0;
                    return 1;
                }
                if(j + 1 < d && board[i][j + 1] == 0) { //space right of the tile
                    board[i][j + 1] = tile;
                    board[i][j] = 0;
                    return 1;
                }
            }
        }
    }
    return 0;
}

/**
 * Returns 1 if game is won (i.e., board is in winning configuration),
 * else 0.
 */
short won(int **board, int d)
{   
    int checkValue = 1;
    int i = 0;
    int j = 0;
    while(checkValue < (d * d)) {
        if(board[i][j] != checkValue) {
            return 0; //if one or more values do not match winning config, return 0
        }
        if(j == d - 1) { //Incrementing the rows and columns
            j = 0;
            ++i;
        } else {
            ++j;
        }
        ++checkValue; 
    }
    return 1;
}
