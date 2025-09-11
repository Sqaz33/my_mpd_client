#pragma once

#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>

#include <mpd/client.h>

namespace client {

class MPDClient {
private:
    struct MPDConnDestr {
        void operator()(mpd_connection* con) {
            mpd_connection_free(con);
        }
    };
    using UniqueMPDConn =
        std::unique_ptr<mpd_connection, MPDConnDestr>;

     
    struct MPDSongDestr {
        void operator()(mpd_song* song) {
            mpd_song_free(song);
        }
    };
    using UniqueMPDSong =
        std::unique_ptr<mpd_song, MPDSongDestr>;


public:
    MPDClient(const char* host = nullptr, 
                  int port = 0, 
                  int timeout = 0);   

    void playCur();
    void play(int index);
    void pause();
    void unpause();
    std::string curSongName();
    std::string status();

private:
    UniqueMPDConn con_;

private:
    auto* con() { return con_.get(); }
    void clearErr_();
    UniqueMPDSong curSong_();
};

} // namespace client