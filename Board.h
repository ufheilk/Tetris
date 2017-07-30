#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H
enum blockStatus {NO_BLOCK, RED_SET, RED_UNSET, BLUE_SET, BLUE_UNSET,
                    GREEN_SET, GREEN_UNSET, YELLOW_SET, YELLOW_UNSET,
                    PURPLE_SET, PURPLE_UNSET, ORANGE_SET, ORANGE_UNSET};

const size_t BOARD_WIDTH = 40;
const size_t BOARD_HEIGHT = 70;
const size_t UPPER_BORDER = 5; // how far above what the user can see can blocks be

class Board {
private:
    std::vector<std::vector<blockStatus>> blocks;
    std::vector<std::vector<sf::RectangleShape>> blockObjects;
    size_t score;

public:
    // ctor, sets all blocks to NO_BLOCK and puts all rect. shapes in the
    // correct positions
    Board();

    // check if a row is full
    // rows are counted from the top
    bool checkRow(size_t row);

    // brings all set blocks down when a row below them has been completed
    // @numRows is the number of rows down the above blocks should fall
    // e.g. if two rows have been completed at once
    void forceDown(size_t row, size_t numRows);

    // checks if the user has lost
    // defined as there being a set block in the upperBorder area
    bool checkLose();

    // all unset blocks are brought down. the rectangle objects are set properly
    void update();

    // displays the Tetris board
    void display();
};

#endif //TETRIS_BOARD_H
