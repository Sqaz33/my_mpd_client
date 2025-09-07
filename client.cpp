#include <memory>
#include <iostream>

#include <mpd/client.h>

struct MpdConnDel {
    void operator()(mpd_connection* conn) {
        mpd_connection_free(conn);
    }
};

using UniqueMpdConn =
     std::unique_ptr<mpd_connection, MpdConnDel>;

int main() {
    UniqueMpdConn conn(mpd_connection_new(nullptr, 0, 0));

    if (conn == nullptr) {
        std::cerr << "Out of memory\n";
        return 1;
    }

    if (mpd_connection_get_error(conn.get()) 
            != MPD_ERROR_SUCCESS) 
    {   
        std::cerr 
            << mpd_connection_get_error_message(conn.get())
            << '\n';
        return 1;
    }

    mpd_run_next(conn.get());
    mpd_run_next(conn.get());
}