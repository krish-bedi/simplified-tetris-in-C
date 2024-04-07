
# Pentominoes Game in C

## Overview
This C program simulates a game similar to Tetris but uses pentomino pieces. Each piece is a different arrangement of five connected squares, and the player must rotate and place them to form complete rows.

## Compilation
Compile the program using the following command:

```
gcc -ansi -Wall -Wextra -Wpedantic -Werror pentominoes.c -o pentominoes
```

## Running the Program
To run the program, use:

```
./pentominoes input.txt
```

Replace `input.txt` with the path to your input file containing the commands for dropping pentomino pieces.

## Input File Format
The input file should contain lines with commands that specify the piece to drop, its rotation, and the column for placement. For example:

```
B r0 c4
D r1 c2
G r3 c5
```

- `B`, `D`, `G`, etc., refer to the type of pentomino piece.
- `r0`, `r1`, `r3`, etc., indicate the rotation state of the piece (0-3).
- `c4`, `c2`, `c5`, etc., specify the column where the piece is dropped.

## Features
- **Well Initialization**: Creates a 16x10 grid representing the game area.
- **Piece Handling**: Supports multiple types of pentominoes, each with four possible rotations.
- **Collision Detection**: Ensures pieces stack correctly and checks for game-over conditions.
- **Line Clearing**: Complete rows are removed from the grid, mimicking the classic game behavior.
- **Display**: Prints the current state of the game grid after each move.

## Function Descriptions
- `main`: Initializes the game and processes the input file.
- `instruct`: Parses and executes commands from the input file.
- `move`: Determines the piece to move based on the command and initiates its placement.
- `drop`: Places the piece onto the game grid, checking for collisions.
- `collision`: Detects whether the dropped piece collides with existing pieces or the bottom of the grid.
- `dropPieces`: Moves the piece down in the grid after initial placement.
- `checkLine`: Identifies and clears completed rows in the grid.
- `squash`: Compacts the grid by moving pieces down to fill cleared lines.
- `printWell`: Outputs the current state of the grid to the console.

## Developer
- Krish Bedi

## License
This project is open-source and available under the [MIT License](https://opensource.org/licenses/MIT).
