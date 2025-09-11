#include "parser.hpp"

namespace parser {

bool parseNExecuteCommand(std::istream& is, client::MPDClient& client) {
    static const std::string help = 
        "help, playcur, play, pause, unpause, exit, cursong";
    std::string com;

    is >> com;
    if (com == "playcur") {
        client.playCur();
    } else if (com == "play") {
        int i;
        is >> i;
        client.play(i);
    } else if (com == "pause") {
        client.pause();
    } else if (com == "unpause") {
        client.unpause();
    } else if (com == "help") {
        std::cout << help << '\n';
    } else if (com == "exit") {
        return true;
    } else if (com == "cursong") {
        std::cout << 
            client.curSongName() << '\n';
    } else {
        std::cout << help << '\n';
    }
    return false;
} 

} // namespace parser

