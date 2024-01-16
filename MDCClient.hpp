#ifndef _MDC_CLIENT_HPP_
#define _MDC_CLIENT_HPP_

//  sb
#include "CANSerialBridge.hpp"
//  message
#include "AcknowledgeMessage.hpp"
#include "CommandMessage.hpp"
#include "FeedbackMessage.hpp"
#include "MessageID.hpp"
#include "SettingMessage.hpp"
#include "TargetMessage.hpp"

#include <stdint.h>

#include "SettingStruct.hpp"

/**
 * MDC reserved 1000-1170(==10200)
 */
#define MDC_ID_RANGE_START 1000
#define MDC_ID_NODE_RANGE 10

class MDCClient {
public:
  MDCClient(CANSerialBridge *serial, uint8_t device_id);
  ~MDCClient();

  /**
   * @brief send settings
   */
  virtual bool update_setting(Motor motor, setting_struct_t settings);

  /**
   * @brief set target. CAUTION: This functio not send message! just update
   * local variables
   */
  virtual bool set_target(Motor motor, float target);

  /**
   * @brief send target message
   */
  virtual void send_target();

  /**
   * @brief update received messages
   */
  virtual bool update();

  //  public access message
  FeedbackMessage feedback;

private:
  CANSerialBridge *_serial;
  uint8_t _device_id;

  const uint32_t COMMAND_ID;
  const uint32_t ACKNOWLEDGE_ID;
  const uint32_t SETTING_ID;
  const uint32_t TARGET_ID;
  const uint32_t FEEDBACK_ID;

  uint32_t resolve_id(uint8_t device_id, MessageID message) {
    return MDC_ID_RANGE_START + MDC_ID_NODE_RANGE * device_id +
           (uint32_t)message;
  }

  //  private access message
  CommandMessage command_msg;
  AcknowledgeMessage acknowledge_msg;
  SettingMessage setting_msg;
  TargetMessage target_msg;
};

#endif