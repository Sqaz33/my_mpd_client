#pragma once

#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>

#include <mpd/client.h>

namespace mmpd {

class MPDConnection {
    struct MPDConnDel {
        void operator()(mpd_connection* conn) {
            mpd_connection_free(conn);
        }
    };

    using UniqueMPDConn =
        std::unique_ptr<mpd_connection, MPDConnDel>;

    UniqueMPDConn con_;

    auto* con() { return con_.get(); }

    void clearErr_();

public:
    MPDConnection(const char* host = nullptr, 
                  int port = 0, 
                  int timeout = 0);   

    void playCur();
    void play(int index);
    void pause();
    void unpause();
};

}