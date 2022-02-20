#include <iostream>
#include <fstream>
#include <sstream>
#include "mlsl.hpp"

// MLSL, a very simple logger
// Copyright (C) 2022 MXPSQL

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @brief A sample usage and a logging utility for scripts
 * 
 */

MXPSQL::MLSL::MLSLLogger* logger = new MXPSQL::MLSL::MLSLLogger();

int main(int argc, char* argv[]){

    if(argc > 3){
        std::string file = argv[1];
        std::string severity = argv[2];
        std::string message = argv[3];

        std::ifstream in(file.c_str());
        if(!in.good()){
            std::cout << "File not found" << std::endl;
            return 1;
        }

        std::stringstream buffer;
        buffer << in.rdbuf();
        in.close();

        logger->setOutputStream(&buffer);

        if(buffer.str().empty()){
            buffer << "# EZ" << std::endl;
        }

        MXPSQL::MLSL::MLSLLevels sev;

        if(severity == "MLSL_DEBUG"){
            sev = MXPSQL::MLSL::MLSL_DEBUG;
        }else if(severity == "MLSL_NO"){
            sev = MXPSQL::MLSL::MLSL_NO_LEVEL;
        }else if(severity == "MLSL_INFO"){
            sev = MXPSQL::MLSL::MLSL_INFO;
        }else if(severity == "MLSL_NOTICE"){
            sev = MXPSQL::MLSL::MLSL_NOTICE;
        }else if(severity == "MLSL_WARNING"){
            sev = MXPSQL::MLSL::MLSL_WARNING;
        }else if(severity == "MLSL_ERROR"){
            sev = MXPSQL::MLSL::MLSL_ERROR;
        }else if(severity == "MLSL_CRITICAL"){
            sev = MXPSQL::MLSL::MLSL_CRITICAL;
        }
        else if(severity == "MLSL_COMMENT"){
            sev = MXPSQL::MLSL::MLSL_COMMENT;
        }
        else if(severity == "MLSL_UNKNOWN"){
            sev = MXPSQL::MLSL::MLSL_UNKNOWN;
        }
        else if(severity == "MLSL_OFF"){
            sev = MXPSQL::MLSL::MLSL_OFF;
        }else if(severity == "MLSL_HIGH_HEEL"){
            sev = MXPSQL::MLSL::MLSL_HIGH_HEEL;
        }else{
            sev = MXPSQL::MLSL::MLSL_OFF;
        }

        logger->log(sev, message);

        delete logger;

        std::ofstream out(file.c_str());

        if(out.good()){
            out << buffer.str();

            out.close();
        }else{
            std::cout << "Failed to write to file." << std::endl;
            return 1;
        }
    }
    else{
        std::cout << "Usage: " << argv[0] << " <file> <severity> <message>" << std::endl;
    }

    return 0;
}
