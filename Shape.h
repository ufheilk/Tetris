
#include "Board.h"

#ifndef TETRIS_SHAPE_H
#define TETRIS_SHAPE_H
enum colors {RED, BLUE, GREEN, YELLOW, PURPLE, ORANGE};
enum directions {LEFT, RIGHT};
enum rotations {CLOCKWISE, COUNTERCLOCKWISE};
typedef std::pair<size_t, size_t> pair;
typedef std::vector<std::pair<int, int>> relativeArray;
const size_t BLOCKS_PER_SHAPE;

class Shape{
private:
    colors color;
    pair headCoord;
    relativeArray bodyPositions;

public:
    // ctor, allows shape to be specified
    Shape(pair headCoords, relativeArray relativePositions, colors color);

    // moves the shape 1 to the left or right
    void move(directions direction, Board & board);

    // moves the shape down 1
    void moveDown(Board & board);

    // rotates the shape clockwise or counter clockwise
    // does this by modifying head coord and body coords
    void rotate(rotations rotation, Board & board);

    // force the whole block down (if user presses space)
    void forceDown(Board & board);

    // makes the blocks set (as opposed to unset) when the shape hits something
    void setBlocks(Board & board);

    // resets the shape, putting it back up at the top
    void reset(pair headCoords, relativeArray relativePositions, colors color,
                Board & board);

};
#endif //TETRIS_SHAPE_H
