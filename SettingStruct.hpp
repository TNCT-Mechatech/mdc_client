#ifndef _MDC_CLIENT_SETTING_CLIENT_HPP_
#define _MDC_CLIENT_SETTING_CLIENT_HPP_

#include "SettingMessage.hpp"

typedef struct SettingStructType {
    OperatorMode mode;
    EncoderType encoderType;
    float scale;
    bool reverse;
    //  normal pid
    float kp;
    float ki;
    float kd;
    float forward_gain;
    //  current pid
    float cp;
    float ci;
    float cd;
} setting_struct_t;

#endif