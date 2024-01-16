#include "MDCClient.hpp"
#include "CommandMessage.hpp"
#include <cstdint>
#include <cstdio>

MDCClient::MDCClient(CANSerialBridge *serial, uint8_t device_id)
    : _serial(serial), _device_id(device_id),
      COMMAND_ID(resolve_id(device_id, MessageID::COMMAND)),
      ACKNOWLEDGE_ID(resolve_id(device_id, MessageID::ACKNOWLEDGE)),
      SETTING_ID(resolve_id(device_id, MessageID::SETTING)),
      TARGET_ID(resolve_id(device_id, MessageID::TARGET)),
      FEEDBACK_ID(resolve_id(device_id, MessageID::FEEDBACK)) {
  //  add frame
  serial->add_frame(COMMAND_ID, &command_msg);
  serial->add_frame(ACKNOWLEDGE_ID, &acknowledge_msg);
  serial->add_frame(SETTING_ID, &setting_msg);
  serial->add_frame(TARGET_ID, &target_msg);
  serial->add_frame(FEEDBACK_ID, &feedback);
}

bool MDCClient::update() {
  bool is_received = false;

  if (command_msg.was_updated()) {
    if (command_msg.data.command == Command::PING) {
      //  acknowledge
      acknowledge_msg.data.timestamp = command_msg.data.timestamp;

      _serial->write(ACKNOWLEDGE_ID);
    }

    is_received = true;
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

bool MDCClient::update_setting(Motor motor, setting_struct_t settings) {
  if ((uint8_t)motor > 3) {
    return false;
  }

  setting_msg.data.motorId = motor;
  //  copy
  setting_msg.data.mode = settings.mode;
  setting_msg.data.encoderType = settings.encoderType;
  setting_msg.data.scale = settings.scale;
  setting_msg.data.reverse = settings.reverse;
  setting_msg.data.kp = settings.kp;
  setting_msg.data.ki = settings.ki;

  //  write
  _serial->write(SETTING_ID);
  return true;
}

bool MDCClient::set_target(Motor motor, float target) {
  if ((int8_t)motor > 3) {
    return false;
  }

  //  set
  target_msg.data.target[(uint8_t)motor] = target;
  return true;
}

void MDCClient::send_target() {
  //  send
  _serial->write(TARGET_ID);
}