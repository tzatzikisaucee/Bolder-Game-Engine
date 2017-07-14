#pragma once

#include <sstream>
#include "log_level.hpp"

namespace bolder {

class Logger_base;
/** \addtogroup log
 *  @{
 */

/**
 * @brief Object to accumulate whole message
 */
class Log_message {
public:
    /**
     * @brief Move constructor
     * @param msg The message to move
     */
    Log_message(Log_message&& msg);

    /**
     * @brief Move assignment
     * @param msg The message to move
     */
    Log_message& operator=(Log_message&& msg);

    /**
      * @brief Destructor output the message to its owner logger
      */
    ~Log_message();

    /**
     * @brief Accumulate a variable of type to into log message
     */
    template <typename T>
    Log_message& operator<< (const T& value);

    /**
     * @brief Accumulate iostream manipulator function into log message
     */
    Log_message& operator<< (std::ostream& (*fn)(std::ostream& os));

private:
    friend class Logger_base; // Only logger can initialize Log_message onject

    Log_message(const Logger_base* owner, Log_level level);

    std::ostringstream buffer_;
    const Logger_base* owner_; // Owner of the message
    Log_level level_;
};

template <typename T>
Log_message& Log_message::operator<< (const T& value) {
    buffer_ << value;
    return *this;
}

/** @}*/

}