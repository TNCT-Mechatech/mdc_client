#include "MDCClient.hpp"
#include <cstdio>

MDCClient::MDCClient(CANSerialBridge *serial, uint8_t device_id)
    :   _serial(serial), _device_id(device_id),
    PING_ID(resolve_id(device_id, MessageID::PING)),
    COMMAND_ID(resolve_id(device_id, MessageID::COMMAND)),
    ACKNOWLEDGE_ID(resolve_id(device_id, MessageID::ACKNOWLEDGE)),
    SETTING_ID(resolve_id(device_id, MessageID::SETTING)),
    TARGET_ID(resolve_id(device_id, MessageID::TARGET)),
    FEEDBACK_ID(resolve_id(device_id, MessageID::FEEDBACK))
{
    //  add frame
    serial->add_frame(PING_ID, &ping_msg);
    serial->add_frame(COMMAND_ID, &command_msg);
    serial->add_frame(ACKNOWLEDGE_ID, &acknowledge_msg);
    serial->add_frame(SETTING_ID, &setting_msg);
    serial->add_frame(TARGET_ID, &target_msg);
    serial->add_frame(FEEDBACK_ID, &feedback);
}

bool MDCClient::update() {
    bool is_received = false;

    if(ping_msg.was_updated()) {
        _serial->write(PING_ID);
    }

    if (acknowledge_msg.was_updated()) {
        //  todo remove hash

        is_received = true;
    }

    if (feedback.was_updated()) {
        is_received = true;
    }

    return is_received;
}

bool MDCClient::update_setting(uint8_t node_id, setting_struct_t settings)
{
    if (node_id > 3) {
        return false;
    }

    setting_msg.data.nodeId = node_id;
    //  copy
    setting_msg.data.mode = settings.mode;
    setting_msg.data.encoderType = settings.encoderType;
    setting_msg.data.scale = settings.scale;
    setting_msg.data.reverse = settings.reverse;
    setting_msg.data.kp = settings.kp;
    setting_msg.data.ki = settings.ki;
    setting_msg.data.cp = settings.cp;
    setting_msg.data.ci = settings.ci;
    setting_msg.data.cd = settings.cd;

    //  write
    _serial->write(SETTING_ID);
    return true;
}

bool MDCClient::set_target(uint8_t node_id, float target)
{
    if (node_id > 3) {
        return false;
    }

    //  set
    target_msg.data.target[node_id] = target;
    return true;
}

void MDCClient::send_target()
{
    //  send
    _serial->write(TARGET_ID);
}