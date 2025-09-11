#pragma once 

#include <istream>

#include "client.hpp"

namespace parser {

bool parseNExecuteCommand(std::istream& is, client::MPDClient& con);

} // namespace parser

