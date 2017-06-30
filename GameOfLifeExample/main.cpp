#include <iostream>
#include <ctime>
#include <chrono>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.cpp"

const size_t MAX_GRID = 40; // how many cells you can have
const size_t CELL_SIZE = 30; // how many pixels the cells are
const size_t MARGIN = CELL_SIZE*2.5; // space in the window above, below, and top
// how large the space is in which the start and stop buttons will be
const size_t BUTTON_AREA = CELL_SIZE*7;
const int OUTLINE_SIZE = -1;
const std::chrono::duration<int, std::milli> BLINK_TIME(100); // 500 ms


void centerText(sf::Text & text, const sf::Window & win);

bool checkUserInput(std::string input);

Board parseToBoard(std::string input);

void processClick(Board & board, bool & run, size_t x, size_t y,
                    sf::RectangleShape & start, sf::RectangleShape & stop);

bool rectCollision(size_t x, size_t y, sf::RectangleShape & rect);

int main() {

    // load the font
    sf::Font font;
    if(!font.loadFromFile("Arial Black.ttf"))
    {
        throw std::runtime_error("Font not loaded properly");
    }

    /*
     * INTRO SCREEN: introduce game and allow player to enter
     * grid size
     */
    sf::Text introText;
    introText.setFont(font);
    introText.setString("Welcome to the Game of Life");
    introText.setCharacterSize(40);
    introText.setFillColor(sf::Color::Black);

    // text asking to choose grid size
    sf::Text gridSizeText;
    gridSizeText.setFont(font);
    gridSizeText.setString("Please select grid size:");
    gridSizeText.setCharacterSize(35);
    gridSizeText.setFillColor(sf::Color::Black);
    gridSizeText.setPosition(0, 275);

    // text of the user's input for the grid size
    std::string userInput("");
    sf::Text userGrid;
    userGrid.setFont(font);
    userGrid.setString(userInput);
    userGrid.setCharacterSize(35);
    userGrid.setFillColor(sf::Color::Black);
    userGrid.setPosition(0, 350);

    // text if the user enters an invalid input
    sf::Text errorText;
    errorText.setFont(font);
    errorText.setString("Invalid input, please re-enter");
    errorText.setCharacterSize(35);
    errorText.setFillColor(sf::Color::Black);
    errorText.setPosition(0, 450);

    bool displayError = false;

    // window for the entire game
    sf::RenderWindow rend(sf::VideoMode(800,800), "Game of Life");

    centerText(introText, rend);
    centerText(gridSizeText, rend);
    centerText(errorText, rend);

    // bool to disallow user from inputting multiple 'x's
    bool xPresent = false;

    while(rend.isOpen())
    {
        sf::Event ev;
        while(rend.pollEvent(ev))
        {
            switch(ev.type)
            {
                case(sf::Event::Closed):
                    rend.close();
                    break;

                case(sf::Event::TextEntered):
                {
                    size_t code = ev.text.unicode;
                    if (code == 10) // return pressed
                    {
                        // if the user's input is invalid
                        if (!checkUserInput(userInput)) {
                            displayError = true;
                            xPresent = false;
                            userInput = "";
                            userGrid.setString(userInput);
                            centerText(userGrid, rend);
                        } else {
                            // close the intro window, moving into
                            // the next event loop
                            rend.close();
                        }
                    } else // normal key pressed, check if valid
                    {
                        if (code >= 48 && code <= 57) {
                            userInput += (char) code; // new char
                            userGrid.setString(userInput);
                            centerText(userGrid, rend);
                        }

                            // x has been pressed and hasn't already been
                        else if ((code == 88 || code == 120) && !xPresent) {
                            xPresent = true;
                            userInput += (char) code; // new char
                            userGrid.setString(userInput);
                            centerText(userGrid, rend);
                        }
                    }
                    break;
                }

                default:
                    break; // else, do nothing
            }
        }

        // display text
        rend.clear(sf::Color::White);
        rend.draw(introText);
        rend.draw(gridSizeText);
        rend.draw(userGrid);
        if(displayError) {
            rend.draw(errorText);
        }
        rend.display();
    }

    // ACT 2: The actual game. Parse userInput to get the number of
    // cells needed. Construct the new window based on these specifications
    Board board = parseToBoard(userInput);
    size_t rows = board.getX();
    size_t cols = board.getY();

    // start and stop boxes
    sf::RectangleShape startBox(sf::Vector2f(4*CELL_SIZE, 2*CELL_SIZE));
    startBox.setPosition(2*MARGIN + rows*CELL_SIZE, MARGIN + cols*CELL_SIZE/5);
    startBox.setFillColor(sf::Color::Green);
    startBox.setOutlineThickness(-1);
    startBox.setOutlineColor(sf::Color::Black);
    sf::FloatRect startRect = startBox.getLocalBounds();

    sf::RectangleShape stopBox(sf::Vector2f(4*CELL_SIZE, 2*CELL_SIZE));
    stopBox.setPosition(2*MARGIN + rows*CELL_SIZE, startBox.getPosition().y + CELL_SIZE *cols/2);
    stopBox.setFillColor(sf::Color::Red);
    stopBox.setOutlineThickness(-1);
    stopBox.setOutlineColor(sf::Color::Black);
    sf::FloatRect stopRect = stopBox.getLocalBounds();


    // start and stop text
    sf::Text startText;
    startText.setFont(font);
    startText.setString("START");
    startText.setCharacterSize(CELL_SIZE);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(startBox.getPosition());
    startText.move(startBox.getSize().x/15, startBox.getSize().y/5);

    sf::Text stopText;
    stopText.setFont(font);
    stopText.setString("STOP");
    stopText.setCharacterSize(CELL_SIZE);
    stopText.setFillColor(sf::Color::Black);
    stopText.setPosition(stopBox.getPosition());
    stopText.move(stopBox.getSize().x/6, stopBox.getSize().y/5);

    sf::RenderWindow game(sf::VideoMode(BUTTON_AREA + MARGIN + CELL_SIZE*rows,
                                        2*MARGIN + CELL_SIZE*cols), "Game of Life");
    bool run = false; // should the 'game' operate normally or freeze?
    std::chrono::time_point<std::chrono::system_clock> ref, check;
    ref = std::chrono::system_clock::now();
    while (game.isOpen()) {
        sf::Event ev;
        while (game.pollEvent(ev)) {
            switch (ev.type) {
                case(sf::Event::Closed):
                    game.close();
                    break;
                case(sf::Event::MouseButtonPressed):
                    processClick(board, run, ev.mouseButton.x, ev.mouseButton.y,
                                    startBox, stopBox);
                default:
                    break; // nothing to do

            }
        }

        if (run) {
            check = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = check-ref;
            if (elapsed_seconds > BLINK_TIME) {
                board.evalCells();
                board.updateCells();
                ref = std::chrono::system_clock::now();
            }
        }

        // draw to screen
        game.clear(sf::Color::White);
        board.display(game);
        game.draw(startBox);
        game.draw(startText);
        game.draw(stopBox);
        game.draw(stopText);
        game.display();

    }
}

/*
 * Centers the passed text horizontally
 * Takes in the text and the window in which the text exists
 */
void centerText(sf::Text & text, const sf::Window & win) {
    // get the index of the last character
    size_t index = text.getString().toAnsiString().length();

    // get the positions of the beginning and end of the string
    size_t begin = text.findCharacterPos(0).x;
    size_t end = text.findCharacterPos(index).x;

    // set the string to be offset right of the left edge of the window by
    // half the amount of the window's length - string's length
    size_t offset = (win.getSize().x - (end - begin))/2;
    text.setPosition(offset, text.getPosition().y);
}

bool checkUserInput(std::string input) {
    size_t xIndex = input.find("x");
    if(xIndex == std::string::npos)
    {
        xIndex = input.find("X");
        if(xIndex == std::string::npos)
            return false; // no X -> invalid
    }

    std::string first = input.substr(0, xIndex); // piece before X
    std::string second = input.substr(xIndex+1); // piece after X

    return (first != "" && second != "" && std::stoi(first)
                                           < MAX_GRID && std::stoi(second) < MAX_GRID);
}

Board parseToBoard(std::string input) {
    size_t xIndex = input.find("x");
    if (xIndex == std::string::npos) {
        xIndex = input.find("X");
    }
    std::string rows = input.substr(0, xIndex);
    std::string cols = input.substr(xIndex + 1);
    Board board((size_t)std::stoi(rows), (size_t)std::stoi(cols));
    board.initRects(CELL_SIZE, MARGIN, OUTLINE_SIZE);
    return board;
}

void processClick(Board & board, bool & run, size_t x, size_t y,
                    sf::RectangleShape & start, sf::RectangleShape & stop) {
    if ((x > MARGIN && x < MARGIN + CELL_SIZE*board.getX()) &&
            (y > MARGIN && y < MARGIN + CELL_SIZE * board.getY())) {
        // user clicked a cell
        board.userSet((x-MARGIN)/CELL_SIZE, (y-MARGIN)/CELL_SIZE);
    } else {
        if (rectCollision(x, y, start)){
            run = true;
        } else if(rectCollision(x,y,stop)){
            run = false;
        }
    }
}

bool rectCollision(size_t x, size_t y, sf::RectangleShape & rect) {
    double xCoord = rect.getPosition().x;
    double yCoord = rect.getPosition().y;
    double xSize = rect.getSize().x;
    double ySize = rect.getSize().y;
    return ((x > xCoord && x < xCoord + xSize) && y > yCoord && y < yCoord
                + ySize);
}
