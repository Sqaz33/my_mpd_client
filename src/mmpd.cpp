#include "mmpd.hpp"

namespace mmpd {

void MPDConnection::clearErr_() {
    if (mpd_connection_get_error(con()) 
        != MPD_ERROR_SUCCESS) 
    {   
        auto msg = strdup(
            mpd_connection_get_error_message(con()));
        if (!mpd_connection_clear_error(con())) {
            throw std::runtime_error(msg);
        }
        std::cerr << msg << '\n';
    } 

}

MPDConnection::MPDConnection(const char* host, 
                             int port, 
                             int timeout):
    con_(mpd_connection_new(host, port, timeout))
{   
    if (nullptr == con_) 
        throw std::runtime_error("Out of memory");
    
    if (mpd_connection_get_error(con()) 
        != MPD_ERROR_SUCCESS)
        throw std::invalid_argument(
            mpd_connection_get_error_message(con()));
}

void MPDConnection::playCur() {
    mpd_run_play(con());
    clearErr_();
}

void MPDConnection::play(int index) {
    mpd_run_play_pos(con(), index);
    clearErr_();
}

void MPDConnection::pause() {
    mpd_run_pause(con(), true);
    clearErr_();
} 

void MPDConnection::unpause() {
    mpd_run_pause(con(), false);
    clearErr_();
}

}