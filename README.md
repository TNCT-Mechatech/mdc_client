# mdc_client

MDC V4を使う際のライブラリです。CAN FD通信を使用してMDCと通信します。

## 使い方

### クライアントの初期化

必要なファイルをインクルードし、MDCClientを初期化してください。
この際、MDCのデバイスIDと同じIDを入力してください。

```c++
//  SerialBridge for CAN FD
#include "ACAN2517FD.h"
#include "MbedHardwareSPI.h"
#include "CANSerialBridge.hpp"

//  MDC Client
#include "mdc_client/MDCClient.hpp"

//  initialize SerialBridge
CANSerialBridge serial(&dev0_can);

//  initalize 
MDCClient mdc_client(&serial, <DEVICE_ID>);
```

### 各モーターの設定

モータには３つの動作モードがあります。
- `NO_OPERATOR` エンコーダーのみ動作します。
- `MD_OPERATOR` MDとエンコーダが動作します。
- `PID_OPERATOR` PID制御で動作します。

エンコーダーには２つの動作モードがあります。
- `VELOCITY` 回転速度で動作します。
- `ANGLE` 回転角で動作します。

ここでは、速度PID制御を行う例をあげます。

```c++
setting_struct_t mdc_setting = {
    OperatorMode::PID_OPERATOR,
    EncoderType::VELOCITY,
    //  分解能
    ENCODER_REVOLUTION,
    //  反転するか(回転方向が合わない場合にトグルしてください。)
    false,
    //  Pゲイン
    0.40,
    //  Iゲイン
    0.8,
    //  Dゲイン
    0,
    //  フォワードゲイン(1 / 最大速度) 設定しなくても大丈夫です。応答性が遅い場合に設定すると効果的
    0,
    //  電流制御用ゲイン
    0,
    0,
    0
};

//  0番目(回路側では1番)のモータ動作を設定します。
mdc_client.update_setting(0, mdc_settings);

```

### 目標値の設定

`set_target()`と`send_target()`を用いて目標値を設定します。

```c++
//  目標値を設定
mdc_client.set_target(0, percent);

//  目標値をMDCに送信
mdc_client.send_target();
```

### 測定値を取得する方法

測定値は目標値を送った際にMDC側から送信されます。

```c++
serial.update();
if(mdc_client.update()) {
    double velocity = mdc_client.feedback.data.node[0].velocity;
    double angle = mdc_client.feedback.data.node[0].velocity;
}
```

随時ドキュメント追加していきます。