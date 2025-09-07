#pragma once 

#include <istream>

#include "mmpd.hpp"

namespace parser {

void parseNExecuteCommand(std::istream& is, 
                          mmpd::MPDConnection& con,
                          bool& exit);

}

