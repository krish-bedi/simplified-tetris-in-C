/* CS288-006 Homework 2 - Krish Bedi*/
/* compilation command: gcc -ansi -Wall -Wextra -Wpedantic -Werror pentominoes.c */

#include <stdio.h>
#include <string.h>

/* define size of well*/
#define ROW 16
#define COL 10

/* function definitions */
int move(char piece, int rotation, int column, int well[ROW][COL], int *counter);
int instruct(char line[], int well[ROW][COL], int *counter);
int printWell(int well[ROW][COL]);
int drop(int piece[4][4], int col, int well[ROW][COL], int *counter);
int collision(int well[ROW][COL], int *counter);
int dropPieces(int well[ROW][COL], int *counter);
int checkLine(int well[ROW][COL]);
int squash(int well[ROW][COL]);
/* global counter variable */

int main(int argc, char *argv[])
{
    /* create well */
    int x, y;
    FILE *input;
    char line[256];
    int counter = 0;
    int well[ROW][COL];
    (void)argc; /* to prevent unused variable errors */

    /* initialize well to 0 */
    for (x = 0; x < ROW; ++x)
    {
        for (y = 0; y < COL; ++y)
        {
            well[x][y] = 0;
        }
    }
    /* Reading the input file */
    input = fopen(argv[1], "r");
    while (fgets(line, sizeof(line), input))
    {
        instruct(line, well, &counter);
    }
    printWell(well);
    fclose(input);
    return 0;
}
/* function to extract data of piece, rotation and column from input file */
int instruct(char line[], int well[ROW][COL], int *counter)
{
    char *rot;
    char *co;
    unsigned int x;
    int i = 1;
    int rotation;
    int column;
    char piece;
    for (x = 0; x < strlen(line); ++x)
    {
        if (line[x] != ' ')
        {
            piece = line[x];
            break;
        }
    }
    rot = strstr(line, "r");
    while (rot[i] != ' ')
    {
        if (i > 1)
        {
            rotation *= 10;
            rotation += (rot[i] - '0');
            i++;
        }
        else
        {
            rotation = (rot[i] - '0');
            i++;
        }
    }
    co = strstr(line, "c");
    column = (co[1] - '0');
    if (rotation > 3)
    {
        rotation = rotation % 4; /* to cover rotations that exceed 3. 4 rotations is the same as 0 rotations 4%4=0 */
    }
    move(piece, rotation, column, well, counter);
    return 0;
}
/* function to decide which piece to move */
int move(char piece, int rotation, int column, int well[ROW][COL], int *counter)
{
    /* initialize 2d array for each piece and its rotation */
    int Br0[4][4], Br1[4][4], Br2[4][4], Br3[4][4];
    int Dr0[4][4], Dr1[4][4], Dr2[4][4], Dr3[4][4];
    int Gr0[4][4], Gr1[4][4], Gr2[4][4], Gr3[4][4];
    int Hr0[4][4], Hr1[4][4], Hr2[4][4], Hr3[4][4];
    int Mr0[4][4], Mr1[4][4], Mr2[4][4], Mr3[4][4];
    int Nr0[4][4], Nr1[4][4], Nr2[4][4], Nr3[4][4];
    char pieceName[3];
    /* create pieces with rotation*/
    /* Piece B */
    Br0[0][0] = 0;
    Br0[0][1] = 0;
    Br0[0][2] = 0;
    Br0[0][3] = 0;
    Br0[1][0] = 0;
    Br0[1][1] = 1;
    Br0[1][2] = 1;
    Br0[1][3] = 0;
    Br0[2][0] = 1;
    Br0[2][1] = 1;
    Br0[2][2] = 0;
    Br0[2][3] = 0;
    Br0[3][0] = 0;
    Br0[3][1] = 1;
    Br0[3][2] = 0;
    Br0[3][3] = 0;
    Br1[0][0] = 0;
    Br1[0][1] = 0;
    Br1[0][2] = 0;
    Br1[0][3] = 0;
    Br1[1][0] = 0;
    Br1[1][1] = 1;
    Br1[1][2] = 0;
    Br1[1][3] = 0;
    Br1[2][0] = 1;
    Br1[2][1] = 1;
    Br1[2][2] = 1;
    Br1[2][3] = 0;
    Br1[3][0] = 0;
    Br1[3][1] = 0;
    Br1[3][2] = 1;
    Br1[3][3] = 0;
    Br2[0][0] = 0;
    Br2[0][1] = 0;
    Br2[0][2] = 0;
    Br2[0][3] = 0;
    Br2[1][0] = 0;
    Br2[1][1] = 1;
    Br2[1][2] = 0;
    Br2[1][3] = 0;
    Br2[2][0] = 0;
    Br2[2][1] = 1;
    Br2[2][2] = 1;
    Br2[2][3] = 0;
    Br2[3][0] = 1;
    Br2[3][1] = 1;
    Br2[3][2] = 0;
    Br2[3][3] = 0;
    Br3[0][0] = 0;
    Br3[0][1] = 0;
    Br3[0][2] = 0;
    Br3[0][3] = 0;
    Br3[1][0] = 1;
    Br3[1][1] = 0;
    Br3[1][2] = 0;
    Br3[1][3] = 0;
    Br3[2][0] = 1;
    Br3[2][1] = 1;
    Br3[2][2] = 1;
    Br3[2][3] = 0;
    Br3[3][0] = 0;
    Br3[3][1] = 1;
    Br3[3][2] = 0;
    Br3[3][3] = 0;
    /* Piece D */
    Dr0[0][0] = 0;
    Dr0[0][1] = 1;
    Dr0[0][2] = 0;
    Dr0[0][3] = 0;
    Dr0[1][0] = 0;
    Dr0[1][1] = 1;
    Dr0[1][2] = 0;
    Dr0[1][3] = 0;
    Dr0[2][0] = 0;
    Dr0[2][1] = 1;
    Dr0[2][2] = 0;
    Dr0[2][3] = 0;
    Dr0[3][0] = 1;
    Dr0[3][1] = 1;
    Dr0[3][2] = 0;
    Dr0[3][3] = 0;
    Dr1[0][0] = 0;
    Dr1[0][1] = 0;
    Dr1[0][2] = 0;
    Dr1[0][3] = 0;
    Dr1[1][0] = 0;
    Dr1[1][1] = 0;
    Dr1[1][2] = 0;
    Dr1[1][3] = 0;
    Dr1[2][0] = 1;
    Dr1[2][1] = 0;
    Dr1[2][2] = 0;
    Dr1[2][3] = 0;
    Dr1[3][0] = 1;
    Dr1[3][1] = 1;
    Dr1[3][2] = 1;
    Dr1[3][3] = 1;
    Dr2[0][0] = 1;
    Dr2[0][1] = 1;
    Dr2[0][2] = 0;
    Dr2[0][3] = 0;
    Dr2[1][0] = 1;
    Dr2[1][1] = 0;
    Dr2[1][2] = 0;
    Dr2[1][3] = 0;
    Dr2[2][0] = 1;
    Dr2[2][1] = 0;
    Dr2[2][2] = 0;
    Dr2[2][3] = 0;
    Dr2[3][0] = 1;
    Dr2[3][1] = 0;
    Dr2[3][2] = 0;
    Dr2[3][3] = 0;
    Dr3[0][0] = 0;
    Dr3[0][1] = 0;
    Dr3[0][2] = 0;
    Dr3[0][3] = 0;
    Dr3[1][0] = 0;
    Dr3[1][1] = 0;
    Dr3[1][2] = 0;
    Dr3[1][3] = 0;
    Dr3[2][0] = 1;
    Dr3[2][1] = 1;
    Dr3[2][2] = 1;
    Dr3[2][3] = 1;
    Dr3[3][0] = 0;
    Dr3[3][1] = 0;
    Dr3[3][2] = 0;
    Dr3[3][3] = 1;
    /* Piece G */
    Gr0[0][0] = 0;
    Gr0[0][1] = 0;
    Gr0[0][2] = 0;
    Gr0[0][3] = 0;
    Gr0[1][0] = 1;
    Gr0[1][1] = 1;
    Gr0[1][2] = 0;
    Gr0[1][3] = 0;
    Gr0[2][0] = 1;
    Gr0[2][1] = 1;
    Gr0[2][2] = 0;
    Gr0[2][3] = 0;
    Gr0[3][0] = 1;
    Gr0[3][1] = 0;
    Gr0[3][2] = 0;
    Gr0[3][3] = 0;
    Gr1[0][0] = 0;
    Gr1[0][1] = 0;
    Gr1[0][2] = 0;
    Gr1[0][3] = 0;
    Gr1[1][0] = 0;
    Gr1[1][1] = 0;
    Gr1[1][2] = 0;
    Gr1[1][3] = 0;
    Gr1[2][0] = 1;
    Gr1[2][1] = 1;
    Gr1[2][2] = 1;
    Gr1[2][3] = 0;
    Gr1[3][0] = 0;
    Gr1[3][1] = 1;
    Gr1[3][2] = 1;
    Gr1[3][3] = 0;
    Gr2[0][0] = 0;
    Gr2[0][1] = 0;
    Gr2[0][2] = 0;
    Gr2[0][3] = 0;
    Gr2[1][0] = 0;
    Gr2[1][1] = 1;
    Gr2[1][2] = 0;
    Gr2[1][3] = 0;
    Gr2[2][0] = 1;
    Gr2[2][1] = 1;
    Gr2[2][2] = 0;
    Gr2[2][3] = 0;
    Gr2[3][0] = 1;
    Gr2[3][1] = 1;
    Gr2[3][2] = 0;
    Gr2[3][3] = 0;
    Gr3[0][0] = 0;
    Gr3[0][1] = 0;
    Gr3[0][2] = 0;
    Gr3[0][3] = 0;
    Gr3[1][0] = 0;
    Gr3[1][1] = 0;
    Gr3[1][2] = 0;
    Gr3[1][3] = 0;
    Gr3[2][0] = 1;
    Gr3[2][1] = 1;
    Gr3[2][2] = 0;
    Gr3[2][3] = 0;
    Gr3[3][0] = 1;
    Gr3[3][1] = 1;
    Gr3[3][2] = 1;
    Gr3[3][3] = 0;
    /* Piece H */
    Hr0[0][0] = 0;
    Hr0[0][1] = 1;
    Hr0[0][2] = 0;
    Hr0[0][3] = 0;
    Hr0[1][0] = 0;
    Hr0[1][1] = 1;
    Hr0[1][2] = 0;
    Hr0[1][3] = 0;
    Hr0[2][0] = 1;
    Hr0[2][1] = 1;
    Hr0[2][2] = 0;
    Hr0[2][3] = 0;
    Hr0[3][0] = 1;
    Hr0[3][1] = 0;
    Hr0[3][2] = 0;
    Hr0[3][3] = 0;
    Hr1[0][0] = 0;
    Hr1[0][1] = 0;
    Hr1[0][2] = 0;
    Hr1[0][3] = 0;
    Hr1[1][0] = 0;
    Hr1[1][1] = 0;
    Hr1[1][2] = 0;
    Hr1[1][3] = 0;
    Hr1[2][0] = 1;
    Hr1[2][1] = 1;
    Hr1[2][2] = 0;
    Hr1[2][3] = 0;
    Hr1[3][0] = 0;
    Hr1[3][1] = 1;
    Hr1[3][2] = 1;
    Hr1[3][3] = 1;
    Hr2[0][0] = 0;
    Hr2[0][1] = 1;
    Hr2[0][2] = 0;
    Hr2[0][3] = 0;
    Hr2[1][0] = 1;
    Hr2[1][1] = 1;
    Hr2[1][2] = 0;
    Hr2[1][3] = 0;
    Hr2[2][0] = 1;
    Hr2[2][1] = 0;
    Hr2[2][2] = 0;
    Hr2[2][3] = 0;
    Hr2[3][0] = 1;
    Hr2[3][1] = 0;
    Hr2[3][2] = 0;
    Hr2[3][3] = 0;
    Hr3[0][0] = 0;
    Hr3[0][1] = 0;
    Hr3[0][2] = 0;
    Hr3[0][3] = 0;
    Hr3[1][0] = 0;
    Hr3[1][1] = 0;
    Hr3[1][2] = 0;
    Hr3[1][3] = 0;
    Hr3[2][0] = 1;
    Hr3[2][1] = 1;
    Hr3[2][2] = 1;
    Hr3[2][3] = 0;
    Hr3[3][0] = 0;
    Hr3[3][1] = 0;
    Hr3[3][2] = 1;
    Hr3[3][3] = 1;
    /* Piece M */
    Mr0[0][0] = 0;
    Mr0[0][1] = 0;
    Mr0[0][2] = 0;
    Mr0[0][3] = 0;
    Mr0[1][0] = 0;
    Mr0[1][1] = 0;
    Mr0[1][2] = 1;
    Mr0[1][3] = 0;
    Mr0[2][0] = 0;
    Mr0[2][1] = 1;
    Mr0[2][2] = 1;
    Mr0[2][3] = 0;
    Mr0[3][0] = 1;
    Mr0[3][1] = 1;
    Mr0[3][2] = 0;
    Mr0[3][3] = 0;
    Mr1[0][0] = 0;
    Mr1[0][1] = 0;
    Mr1[0][2] = 0;
    Mr1[0][3] = 0;
    Mr1[1][0] = 1;
    Mr1[1][1] = 0;
    Mr1[1][2] = 0;
    Mr1[1][3] = 0;
    Mr1[2][0] = 1;
    Mr1[2][1] = 1;
    Mr1[2][2] = 0;
    Mr1[2][3] = 0;
    Mr1[3][0] = 0;
    Mr1[3][1] = 1;
    Mr1[3][2] = 1;
    Mr1[3][3] = 0;
    Mr2[0][0] = 0;
    Mr2[0][1] = 0;
    Mr2[0][2] = 0;
    Mr2[0][3] = 0;
    Mr2[1][0] = 0;
    Mr2[1][1] = 1;
    Mr2[1][2] = 1;
    Mr2[1][3] = 0;
    Mr2[2][0] = 1;
    Mr2[2][1] = 1;
    Mr2[2][2] = 0;
    Mr2[2][3] = 0;
    Mr2[3][0] = 1;
    Mr2[3][1] = 0;
    Mr2[3][2] = 0;
    Mr2[3][3] = 0;
    Mr3[0][0] = 0;
    Mr3[0][1] = 0;
    Mr3[0][2] = 0;
    Mr3[0][3] = 0;
    Mr3[1][0] = 1;
    Mr3[1][1] = 1;
    Mr3[1][2] = 0;
    Mr3[1][3] = 0;
    Mr3[2][0] = 0;
    Mr3[2][1] = 1;
    Mr3[2][2] = 1;
    Mr3[2][3] = 0;
    Mr3[3][0] = 0;
    Mr3[3][1] = 0;
    Mr3[3][2] = 1;
    Mr3[3][3] = 0;
    /* Piece N */
    Nr0[0][0] = 0;
    Nr0[0][1] = 0;
    Nr0[0][2] = 0;
    Nr0[0][3] = 0;
    Nr0[1][0] = 0;
    Nr0[1][1] = 1;
    Nr0[1][2] = 0;
    Nr0[1][3] = 0;
    Nr0[2][0] = 1;
    Nr0[2][1] = 1;
    Nr0[2][2] = 1;
    Nr0[2][3] = 0;
    Nr0[3][0] = 0;
    Nr0[3][1] = 1;
    Nr0[3][2] = 0;
    Nr0[3][3] = 0;
    Nr1[0][0] = 0;
    Nr1[0][1] = 0;
    Nr1[0][2] = 0;
    Nr1[0][3] = 0;
    Nr1[1][0] = 0;
    Nr1[1][1] = 1;
    Nr1[1][2] = 0;
    Nr1[1][3] = 0;
    Nr1[2][0] = 1;
    Nr1[2][1] = 1;
    Nr1[2][2] = 1;
    Nr1[2][3] = 0;
    Nr1[3][0] = 0;
    Nr1[3][1] = 1;
    Nr1[3][2] = 0;
    Nr1[3][3] = 0;
    Nr2[0][0] = 0;
    Nr2[0][1] = 0;
    Nr2[0][2] = 0;
    Nr2[0][3] = 0;
    Nr2[1][0] = 0;
    Nr2[1][1] = 1;
    Nr2[1][2] = 0;
    Nr2[1][3] = 0;
    Nr2[2][0] = 1;
    Nr2[2][1] = 1;
    Nr2[2][2] = 1;
    Nr2[2][3] = 0;
    Nr2[3][0] = 0;
    Nr2[3][1] = 1;
    Nr2[3][2] = 0;
    Nr2[3][3] = 0;
    Nr3[0][0] = 0;
    Nr3[0][1] = 0;
    Nr3[0][2] = 0;
    Nr3[0][3] = 0;
    Nr3[1][0] = 0;
    Nr3[1][1] = 1;
    Nr3[1][2] = 0;
    Nr3[1][3] = 0;
    Nr3[2][0] = 1;
    Nr3[2][1] = 1;
    Nr3[2][2] = 1;
    Nr3[2][3] = 0;
    Nr3[3][0] = 0;
    Nr3[3][1] = 1;
    Nr3[3][2] = 0;
    Nr3[3][3] = 0;

    /* name of piece that will be used with its rotation */
    pieceName[0] = piece;
    pieceName[1] = 'r';
    pieceName[2] = rotation + '0';

    /* drop piece on top of well */
    if (strcmp(pieceName, "Br0") == 0)
    {
        drop(Br0, column, well, counter);
    }
    else if (strcmp(pieceName, "Br1") == 0)
    {
        drop(Br1, column, well, counter);
    }
    else if (strcmp(pieceName, "Br2") == 0)
    {
        drop(Br2, column, well, counter);
    }
    else if (strcmp(pieceName, "Br3") == 0)
    {
        drop(Br3, column, well, counter);
    }
    else if (strcmp(pieceName, "Dr0") == 0)
    {
        drop(Dr0, column, well, counter);
    }
    else if (strcmp(pieceName, "Dr1") == 0)
    {
        drop(Dr1, column, well, counter);
    }
    else if (strcmp(pieceName, "Dr2") == 0)
    {
        drop(Dr2, column, well, counter);
    }
    else if (strcmp(pieceName, "Dr3") == 0)
    {
        drop(Dr3, column, well, counter);
    }
    else if (strcmp(pieceName, "Gr0") == 0)
    {
        drop(Gr0, column, well, counter);
    }
    else if (strcmp(pieceName, "Gr1") == 0)
    {
        drop(Gr1, column, well, counter);
    }
    else if (strcmp(pieceName, "Gr2") == 0)
    {
        drop(Gr2, column, well, counter);
    }
    else if (strcmp(pieceName, "Gr3") == 0)
    {
        drop(Gr3, column, well, counter);
    }
    else if (strcmp(pieceName, "Hr0") == 0)
    {
        drop(Hr0, column, well, counter);
    }
    else if (strcmp(pieceName, "Hr1") == 0)
    {
        drop(Hr1, column, well, counter);
    }
    else if (strcmp(pieceName, "Hr2") == 0)
    {
        drop(Hr2, column, well, counter);
    }
    else if (strcmp(pieceName, "Hr3") == 0)
    {
        drop(Hr3, column, well, counter);
    }
    else if (strcmp(pieceName, "Mr0") == 0)
    {
        drop(Mr0, column, well, counter);
    }
    else if (strcmp(pieceName, "Mr1") == 0)
    {
        drop(Mr1, column, well, counter);
    }
    else if (strcmp(pieceName, "Mr2") == 0)
    {
        drop(Mr2, column, well, counter);
    }
    else if (strcmp(pieceName, "Mr3") == 0)
    {
        drop(Mr3, column, well, counter);
    }
    else if (strcmp(pieceName, "Nr0") == 0)
    {
        drop(Nr0, column, well, counter);
    }
    else if (strcmp(pieceName, "Nr1") == 0)
    {
        drop(Nr1, column, well, counter);
    }
    else if (strcmp(pieceName, "Nr2") == 0)
    {
        drop(Nr2, column, well, counter);
    }
    else if (strcmp(pieceName, "Nr3") == 0)
    {
        drop(Nr3, column, well, counter);
    }
    return 0;
}
/* function to drop piece on top of well */
int drop(int piece[4][4], int col, int well[ROW][COL], int *counter)
{
    int x, y;
    int newPiece[4][4];
    for (x = 0; x < 4; ++x)
    {
        for (y = 0; y < 4; ++y)
        {
            if (piece[x][y] == 1)
            {
                newPiece[x][y] = 1 + *counter; /* create identical new piece and replace its 1's with value of counter to detect collision later */
            }
            else
            {
                newPiece[x][y] = 0;
            }
        }
    }
    for (x = 0; x < 4; ++x)
    {
        for (y = 0; y < 4; ++y)
        {
            if (well[x][y + col] != 1)
            {
                if (newPiece[x][y] != 0)
                {
                    well[x][y + col] = newPiece[x][y]; /* drop piece in well */
                }
            }
            else
            {
                printf("game over"); /* if well is full */
            }
        }
    }
    (*counter)++;
    collision(well, counter);
    return 0;
}
/* function to detect collision anywhere in the well */
int collision(int well[ROW][COL], int *counter)
{
    int x, y, z;
    int coll = 1;
    int bottom = 0;
    for (z = 0; z < COL; ++z)
    { /* check if piece being dropped is already at the bottom of the well */
        if (well[ROW - 1][z] == *counter)
        {
            bottom = 1;
            coll = 1;
        }
    }
    if (bottom != 1)
    { /* check for collision */
        for (y = 0; y < ROW - 1; ++y)
        {
            for (x = 0; x < COL; ++x)
            {
                if (well[y][x] == *counter)
                {
                    if ((well[y + 1][x] != 0) && (well[y][x] + well[y + 1][x]) < (well[y][x] + well[y][x]))
                    {
                        /* if piece with value 4 is dropped on piece with value 3 (4+3)<(4+4). This prevents pieces from colliding with themselves */
                        coll = 1; /*collides*/
                    }
                    else
                    {
                        coll = 0; /*doesnt collide*/
                    }
                }
            }
        }
    }
    if (coll == 0)
    {
        dropPieces(well, counter);
    }
    else
    {
        checkLine(well); /* if collision is detected or piece reaches bottom of well */
    }
    return 0;
}
/* recursive function that drops current piece down by 1 and checks again for collision */
int dropPieces(int well[ROW][COL], int *counter)
{
    int x, y;
    for (x = ROW - 1; x > -1; x--)
    { /* loop through well in reverse */
        for (y = COL - 1; y > -1; y--)
        {
            if (well[x][y] == (*counter))
            {
                well[x][y] = 0;
                well[x + 1][y] = *counter;
            }
        }
    }
    collision(well, counter); /* check again for collision */
    return 0;
}
/* check for a full line then pop it */
int checkLine(int well[ROW][COL])
{
    int x, y, z, full; /* full=1 true , full=0 false */
    for (x = ROW - 1; x > -1; x--)
    {
        full = 1;
        for (y = COL - 1; y > -1; y--)
        {
            if (well[x][y] == 0)
            { /* if any index in given row is 0 then that row is not full */
                full = 0;
            }
        }
        if (full == 1)
        {
            for (z = 0; z < COL; ++z)
            {
                well[x][z] = 0;
            }
            squash(well);
        }
    }
    return 0;
}
/* squash remaining pieces after popping line */
int squash(int well[ROW][COL])
{
    int x, y;
    for (x = ROW - 1; x > -1; x--)
    { /* loop through well in reverse */
        for (y = COL - 1; y > -1; y--)
        {
            if (well[x - 1][y] != 0 && well[x][y] == 0 && x != 0)
            {
                well[x][y] = well[x - 1][y];
                well[x - 1][y] = 0;
            }
        }
    }
    return 0;
}
/* prints the well */
int printWell(int well[ROW][COL])
{
    int x, y;
    for (x = 4; x < ROW; ++x)
    {
        printf("|");
        for (y = 0; y < COL; ++y)
        {
            if (well[x][y] != 0)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("|\n");
    }
    printf("+----------+\n");
    return 0;
}