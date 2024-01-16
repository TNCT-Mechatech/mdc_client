#ifndef _MDC_CLIENT_SETTING_CLIENT_HPP_
#define _MDC_CLIENT_SETTING_CLIENT_HPP_

#include "SettingMessage.hpp"
#include "EncoderType.hpp"

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
} setting_struct_t;

#endif