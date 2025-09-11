#include "client.hpp"

#include <memory>
#include <string>
#include <filesystem>

namespace client {

MPDClient::MPDClient(const char* host, 
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

void MPDClient::playCur() {
    mpd_run_play(con());
    clearErr_();
}

void MPDClient::play(int index) {
    mpd_run_play_pos(con(), index);
    clearErr_();
}

void MPDClient::pause() {
    mpd_run_pause(con(), true);
    clearErr_();
} 

void MPDClient::unpause() {
    mpd_run_pause(con(), false);
    clearErr_();
}

std::string MPDClient::curSongName() {
    auto song = curSong_();
    if (!song) return "unknown";
    auto uri = mpd_song_get_uri(song.get());
    std::filesystem::path path(uri);
    return path.filename();
}

void MPDClient::clearErr_() {
    if (mpd_connection_get_error(con()) 
        != MPD_ERROR_SUCCESS) 
    {   
        std::string msg(mpd_connection_get_error_message(con()));

        if (!mpd_connection_clear_error(con())) {
            throw std::runtime_error(msg);
        }

        std::cerr << msg << '\n';
    } 
}

MPDClient::UniqueMPDSong MPDClient::curSong_() {
    auto* st = mpd_run_status(con());
    if (mpd_status_get_state(st) == MPD_STATE_UNKNOWN) 
        return nullptr;
    auto id = mpd_status_get_song_id(st);
    mpd_status_free(st);
    auto* song = mpd_run_get_queue_song_id(con(), id);
    return {song, MPDClient::MPDSongDestr()};
}


} // namespace client