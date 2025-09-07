#include "parser.hpp"

namespace parser {

void parseNExecuteCommand(
    std::istream& is, 
    mmpd::MPDConnection& con,
    bool& exit) 
{
    static const std::string help = 
        "help, playcur, play, pause, unpause, exit";
    std::string com;

    is >> com;
    if (com == "playcur") {
        con.playCur();
    } else if (com == "play") {
        int i;
        is >> i;
        con.play(i);
    } else if (com == "pause") {
        con.pause();
    } else if (com == "unpause") {
        con.unpause();
    } else if (com == "help") {
        std::cout << help << '\n';
    } else if (com == "exit") {
        exit = true;
    } else {
        std::cout << help;
    }
} 

}

