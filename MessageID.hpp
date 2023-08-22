//
// Created by owner on 2023/08/04.
//

#ifndef MOTORDRIVER_CONTROLLER_V4_MESSAGEID_HPP
#define MOTORDRIVER_CONTROLLER_V4_MESSAGEID_HPP

#include "stdint.h"

enum class MessageID: uint32_t {
    PING,
    COMMAND,
    ACKNOWLEDGE,
    SETTING,
    TARGET,
    FEEDBACK
};

#endif //MOTORDRIVER_CONTROLLER_V4_MESSAGEID_HPP
