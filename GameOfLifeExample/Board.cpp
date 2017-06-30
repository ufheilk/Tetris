#include "Board.h"

Board::Board(size_t x, size_t y)
    : dim_x(x), dim_y(y)
    , board(x, cellLine(y)) // defaults all cells to being dead w/ 0 neighbors
{
}

/*
 * Allow user to select a cell to automatically switch its status
 */
void Board::userSet(size_t x, size_t y)
{
    // bool value of cell is now its opposite
    std::get<0>(board[x][y]) = !std::get<0>(board[x][y]);
    if (std::get<2>(board[x][y]).getFillColor() == sf::Color::Black) {
        std::get<2>(board[x][y]).setFillColor(sf::Color::White);
    } else {
        std::get<2>(board[x][y]).setFillColor(sf::Color::Black);
    }
}

/*
 * Evaluates the number of adjacent neighbors for each cell, updating
 * the value in the cell's pair
 */
void Board::evalCells()
{
    for (int i=0; i<dim_x; i++)
    {
        for (int j=0; j<dim_y; j++)
        {
            size_t liveAdjacent = 0;

            // check all 8 adjacent cells, also checking bounds

            //upper left
            if (i > 0 && j > 0)
            {
                if (std::get<0>(board[i-1][j-1])) {++liveAdjacent;}
            }

            // above
            if (j > 0)
            {
                if (std::get<0>(board[i][j-1])) {++liveAdjacent;}
            }

            // upper right
            if (j > 0 && i < dim_x - 1)
            {
                if(std::get<0>(board[i+1][j-1])) {++liveAdjacent;}
            }

            // left
            if (i > 0)
            {
                if (std::get<0>(board[i-1][j])) {++liveAdjacent;}
            }

            // right
            if (i < dim_x - 1)
            {
                if (std::get<0>(board[i+1][j])) {++liveAdjacent;}
            }

            // below left
            if (i > 0 && j < dim_y - 1)
            {
                if (std::get<0>(board[i-1][j+1])) {++liveAdjacent;}
            }

            // below
            if (j < dim_y - 1)
            {
                if (std::get<0>(board[i][j+1])) {++liveAdjacent;}
            }

            // below right
            if (i < dim_x - 1 && j < dim_y - 1)
            {
                if (std::get<0>(board[i+1][j+1])) {++liveAdjacent;}
            }

            // update adjacent counter
            std::get<1>(board[i][j]) = liveAdjacent;
        }
    }
}

/*
 * Updates every cell based on the following guidelines:
 * 1) Any cell with fewer than 2 neighbors dies
 * 2) Any cell with 2 to 3 neighbors lives on if alive
 * 3) Any cell with more than 3 neighbors dies
 * 4) Any dead cell with exactly 3 neighbors comes to life
 */
void Board::updateCells()
{
    for (cellLine & ln : board)
    {
        for (cell & c : ln)
        {
            if (std::get<0>(c)) // if the cell is alive
            {
                size_t numAliveAround = std::get<1>(c);
                if (numAliveAround > 3 || numAliveAround < 2) {
                    std::get<0>(c) = false;
                    std::get<2>(c).setFillColor(sf::Color::White);
                }
            }

            else // if the cell is dead
            {
                if (std::get<1>(c) == 3) {
                    std::get<0>(c) = true;
                    std::get<2>(c).setFillColor(sf::Color::Black);
                }
            }
        }
    }
}

/*
 * Clears the board, with new, dead cells
 */
void Board::clear()
{
    Board tmp(dim_x, dim_y); // has all dead cells
    *this = tmp; // swap this board's cells for the dead ones (memory managed by vector)
}

// returns dim_x
size_t Board::getX() const {return dim_x;}

// returns dim_y
size_t Board::getY() const {return dim_y;}

// displays board to the window
void Board::display(sf::RenderWindow & rend) {
    for (cellLine & l : board) {
        for (cell & c : l) {
            rend.draw(std::get<2>(c));
        }
    }
}

// initializes all rectangle shapes to the proper specifications
void Board::initRects(size_t cellSize, size_t margin, int outlineSize) {
    for (size_t i = 0; i < dim_x; ++i) {
        for (size_t j = 0; j < dim_y; ++j) {
            std::get<2>(board[i][j]).setSize(sf::Vector2f(cellSize, cellSize));
            std::get<2>(board[i][j]).setPosition(margin + i*cellSize,
                                                    margin + j*cellSize);
            std::get<2>(board[i][j]).setFillColor(sf::Color::White);
            std::get<2>(board[i][j]).setOutlineColor(sf::Color::Black);
            std::get<2>(board[i][j]).setOutlineThickness(-1);
        }
    }
}

