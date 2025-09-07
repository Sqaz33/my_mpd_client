#include "mmpd.hpp"
#include "parser.hpp"

int main() try {
    mmpd::MPDConnection con;


    bool exit = false;
    while (!exit) {
        parser::parseNExecuteCommand(
            std::cin, con, exit);
    }

    con.pause();
    return 0;
} catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
} catch (...) {
    std::cerr << "Unknown error\n";
    return 1;
}