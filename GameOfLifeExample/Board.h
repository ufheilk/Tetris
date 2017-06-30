//
// Created by Keaton Ufheil on 4/12/17.
//

#include <vector>
#include <cstddef>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#ifndef GOL_BOARD_H
#define GOL_BOARD_H

typedef std::tuple<bool, size_t, sf::RectangleShape> cell;
typedef std::vector<cell> cellLine;
typedef std::vector<cellLine> cellGrid;


class Board
{
private:
    size_t dim_x;

    size_t dim_y;

    // value of 'true' - alive. value of 'false' - dead.
    cellGrid board;

public:

    // ctor
    Board(size_t x, size_t y);

    /*
     * Allow user to select a cell to automatically switch its status
     */
    void userSet(size_t x, size_t y);

    /*
     * Evaluates the number of adjacent neighbors for each cell, updating
     * the value in the cell's pair
     */
    void evalCells();

    /*
     * Updates every cell based on the following guidelines:
     * 1) Any cell with fewer than 2 neighbors dies
     * 2) Any cell with 2 to 3 neighbors lives on if alive
     * 3) Any cell with more than 3 neighbors dies
     * 4) Any dead cell with exactly 3 neighbors comes to life
     */
    void updateCells();


    /*
     * Clears the board, with new, dead cells
     */
    void clear();

    // returns dim_x
    size_t getX() const;

    // returns dim_y
    size_t getY() const;

    // displays board to the window
    void display(sf::RenderWindow & rend);

    // initializes all rectangle shapes to the proper specifications
    void initRects(size_t cellSize, size_t margin, int outlineSize);
};

#endif //GOL_BOARD_H
