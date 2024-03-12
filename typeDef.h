/**
 * @file typedef.h
 *
 * @brief This file defines various enums and structures used in the game.
 *
 * @author JMB - IUT Informatique La Rochelle
 * @date 03/10/2023
 */

#ifndef TYPEDEF_H
#define TYPEDEF_H

// Maximum size of the game board
const int BOARD_SIZE_MAX = 13;

// Possible board sizes
enum BoardSize
{
    LITTLE = 11,  // Represents the smaller board size (11x11).
    BIG = 13      // Represents the larger board size (13x13).
};

// Player roles
enum PlayerRole
{
    ATTACK,   // Represents the role of the attacker.
    DEFENSE   // Represents the role of the defender.
};

// Cell types
enum CellType
{
    NORMAL,    // Represents a normal game board cell.
    FORTRESS,  // Represents a fortress cell.
    CASTLE     // Represents a castle cell.
};

// Piece types
enum PieceType
{
    NONE,    // Represents an empty cell (no piece).
    SHIELD,  // Represents a shield piece.
    SWORD,   // Represents a sword piece.
    KING     // Represents the king piece.
};

// Structure to store information about a cell
struct Cell
{
    CellType itsCellType;   // The type of the cell (e.g., NORMAL, FORTRESS, CASTLE).
    PieceType itsPieceType; // The type of piece on the cell (e.g., NONE, SHIELD, SWORD, KING).
};

// Structure for the coordinates of a cell
struct Position
{
    int itsRow;  // The row (vertical position) of a cell.
    int itsCol;  // The column (horizontal position) of a cell.
};

#endif // TYPEDEF_H
