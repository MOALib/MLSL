#include <ctime>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

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
 * @mainpage LibMLSL Doc Home.
 * 
 * @section intro_sec Introduction
 * So, this is the documentation of the LibMLSL library.
 * 
 * A C++ 98 compatible Library with a simple API.
 * 
 * Licensed under LGPL-2.1-or-later.
 * 
 * @section install_sec Installation
 * Just drop this file into your project, or fetchcontent it with CMake.
 * 
 * @section usage_sec Usage
 * MXPSQL::MLSL::MLSLLogger* logger = new MXPSQL::MLSL::MLSLLogger();
 * 
 * logger->setOutputStream(std::cout);
 * 
 * logger->setLevel(MLSL_DEBUG);
 * 
 * logger->log(MXPSQL::MLSL::MLSLLevels::MLSL_HIGH_HEEL, "This is a test");
 * 
 * delete logger;
 * 
 * @file mlsl.hpp
 * @brief This is the logging namespace, contains the classes and levels.
 * @copyright Copyright (c) 2022 MXPSQL, LGPL-2.1-or-later
 */

#ifndef MXPSQL_MLSL_HPP
#define MXPSQL_MLSL_HPP

namespace MXPSQL{
    namespace MLSL{

        /**
         * @enum MLSLLevels Levels of severity.
         * @brief The levels are here, not macros. And yes, the log function will check if the threshold or the current severity is MLSL_OFF, so you cannot just cheat by setting the treshold below and log OFF messages.
         */
        enum MLSLLevels{
            /**
             * @brief You don't know the level, use it.
             * 
             */
            MLSL_UNKNOWN = -3,

            /**
             * @brief Comments, not meant to be parsed by a log reader
             * 
             */
            MLSL_COMMENT = -2,

            /**
             * @brief No level, can be used for  "nothing to see here"
             * 
             */
            MLSL_NO_LEVEL = -1,

            /**
             * @brief It's a severity for debug messages
             * 
             */
            MLSL_DEBUG = 0,

            /**
             * @brief It's a severity for informations.
             * 
             */
            MLSL_INFO = 1,

            /**
             * @brief Kate Middleton, totally not an absoloute prick.
             * 
             * Kate Middleton, she's fine. Wears black pumps and Emilia Wickstead Alice blue dress (Yes, Emilia Wickstead is her favourite cloth brand), the former which gets stuck on grate and the latter, gets stuck on doors.
             */
            MLSL_HIGH_HEEL = 2,

            /**
             * @brief Notices should use this
             * 
             */
            MLSL_NOTICE = 3,

            /**
             * @brief Warning for almost errors and stuff.
             * 
             */
            MLSL_WARNING = 4,

            /**
             * @brief Errors, but not enough to crash.
             * 
             */
            MLSL_ERROR = 5,

            /**
             * @brief Errors, but critically fatal enough to crash
             * 
             */
            MLSL_CRITICAL = 6,

            /**
             * @brief Turn off the logger, the code will check if this is set as the threshold or the current severity and if it is, nothing will be logged.
             * 
             */
            MLSL_OFF = 7
        };

        /**
         * @class MLSLLogger Logger object.
         * @brief The logger object, so you can have multiple loggers, but only one output stream.
         * @warning The logger object's output stream needs to be closed manually if needed (file stream).
         * @warning The logger will not track if the output stream is nullified, it up to you to check if it is null.
         */
        class MLSLLogger{
            protected:

                /**
                 * @brief String builder for logs
                 * 
                 */
                std::stringstream ssbuilder;

                /**
                 * @brief The output stream
                 * 
                 */
                std::ostream* outStream;

                /**
                 * @brief The current threshold level
                 * 
                 */
                MLSLLevels thresholdLevel;

                /**
                 * @brief Clear the ssbuilder
                 * 
                 */
                void clearBuilder(){
                    ssbuilder.str("");
                    ssbuilder.clear();
                }

            public:

            /**
             * @brief Construct a new MLSLLogger object
             * 
             */
            MLSLLogger(){
                outStream = &std::cout;
                thresholdLevel = MLSL_DEBUG;
            }

            /**
             * @brief Construct a new MLSLLogger object
             * 
             * @param out the output stream
             */
            MLSLLogger(std::ostream& out){
                outStream = &out;
                thresholdLevel = MLSL_DEBUG;
            }

            /**
             * @brief Construct a new MLSLLogger object
             * 
             * @param out the output stream
             * @param threshold the logging threshold
             */
            MLSLLogger(std::ostream& out, MLSLLevels threshold){
                outStream = &out;
                thresholdLevel = threshold;
            }



            /**
             * @brief Set the Threshold for logging
             * 
             * @param threshold the new threshold
             */
            void setThreshold(MLSLLevels threshold){
                thresholdLevel = threshold;
            }

            /**
             * @brief Set the Output Stream
             * 
             * @param out the new output stream
             */
            MLSLLevels getThreshold(){
                return thresholdLevel;
            }

            /**
             * @brief Turns off the logger, a shortcut for setThreshold(MLSLLevels::MLSL_OFF)
             * @note You have to set the threshold manually, the logger will not remember it.
             */
            void turnOff(){
                thresholdLevel = MLSL_OFF;
            }

            /**
             * @brief Set the Output Stream
             * 
             * @param out the new output stream
             */
            void setOutputStream(std::ostream& out){
                outStream = &out;
            }

            /**
             * @brief Get the Output Stream
             * 
             * @return std::ostream& the output stream
             */
            void setOutputStream(std::ostream* out){
                outStream = out;
            }

            /**
             * @brief Get the Output Stream
             * 
             * @return std::ostream& the output stream
             */
            std::ostream& getOutputStream(){
                return *outStream;
            }






            /**
             * @brief Log out a message to the stream
             * 
             * @param level The message severity level
             * @param message The message to log
             */
            void log(MLSLLevels level, std::string message){
                clearBuilder();


                std::time_t rawtime = std::time(0);

                std::string time = "[" + std::string(std::ctime(&rawtime)) + "]";

                time.erase(std::remove(time.begin(), time.end(), '\n'), time.end());

                std::string severity = "";

                switch(level){
                    case MLSL_NO_LEVEL:
                        break;
                    case MLSL_OFF:
                        break;
                    case MLSL_COMMENT:
                        severity = "#";
                        break;
                    case MLSL_DEBUG:
                        severity = "[debug]";
                        break;
                    case MLSL_INFO:
                        severity = "[info]";
                        break;
                    case MLSL_HIGH_HEEL:
                        severity = "[high-heel]";
                        break;
                    case MLSL_NOTICE:
                        severity = "[notice]";
                        break;
                    case MLSL_WARNING:
                        severity = "[warning]";
                        break;
                    case MLSL_ERROR:
                        severity = "[error]";
                        break;
                    case MLSL_CRITICAL:
                        severity = "[critical]";
                        break;
                    default:
                        severity = "[unknown]";
                        break;
                }

                // ignores OFF value
                if(level != MLSL_OFF || thresholdLevel != MLSL_OFF){
                    if(level >= thresholdLevel){

                        if(level == MLSL_COMMENT){
                            ssbuilder << severity << " " << message;
                        }
                        else if(level == MLSL_NO_LEVEL){
                            ssbuilder << time << " " << message;
                        }
                        else{
                            ssbuilder << time << " " << severity << " " << message;
                        }

                        ssbuilder << std::endl;

                        *outStream << ssbuilder.str();
                    }
                }
            }

            /**
             * @brief Log out a message to the stream, but with the stream insertion operator.
             * 
             * @param message The message to log
             */
            MLSLLogger& operator<<(std::string message){
                log(MLSL_INFO, message);
                return *this;
            }

        };
    }
}



#endif
