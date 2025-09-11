#include <sstream>

#include "client.hpp"
#include "parser.hpp"

int main(int argc, const char** argv) try {
    using parser::parseNExecuteCommand;

    client::MPDClient con;

    if (argc > 1) {
        std::stringstream ss;
        for (int i = 1; i < argc; ++i) {
            if (i > 1) 
                ss << ' ';
            ss << argv[i];
        }
        parseNExecuteCommand(ss, con);
        return 0;
    }

    bool exit = false;
    while (!exit) {
        exit = parseNExecuteCommand(std::cin, con);
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