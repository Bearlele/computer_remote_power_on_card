/* 电脑远程开机卡V1.1
   2020.2.11创建项目
   最后修改时间2020.3.16
   作者：梦程MI  Bilibili uid：88809897
   使用平台： Blinker & Aruino
   ESP8266开发板 2.6.3
   pwr信号-D5-GPIO14
   rst信号-D7-GPIO13
   
   未经 梦程MI 许可，禁止用作商业用途。
   本项目软硬件均由 梦程MI 独立制作，请尊重版权。
   本项目适合有一定基础的开发者编译制作，没有arduino基础的请学习完arduino后在进行实践操作。
*/
#define BLINKER_WIFI
#define BLINKER_DUEROS_MULTI_OUTLET  //设置小度多插座模式
#define BLINKER_ESP_SMARTCONFIG

#include <Blinker.h>

const int pwr = D5;       //D5-PWR信号
const int rst = D7;       //D7-RST信号

//---------------定义初始信息------------------
char auth[] = "**************";     //Your Device Secret Key
//-------------------------------------------

bool oState[3] = { false };

//-----------------------------------------------

BlinkerButton Button1("PWR");
BlinkerButton Button2("RST");
BlinkerButton Button3("QPWR");

//---------------Smartconfig---------------
void dataRead(const String & data)
{
  BLINKER_LOG("Blinker readString: ", data);

  Blinker.vibrate();

  uint32_t BlinkerTime = millis();

  Blinker.print("millis", BlinkerTime);
}

//----------------按钮PWR----------------------
void button1_callback(const String & state)
{
  BLINKER_LOG("get button state: ", state);
  digitalWrite(pwr, HIGH);
  Blinker.delay(200);
  digitalWrite(pwr, LOW);
  Button1.print("tap");


}
//-----------按钮RST------------------------
void button2_callback(const String & state)
{
  BLINKER_LOG("get button state: ", state);
  digitalWrite(rst, HIGH);
  Blinker.delay(200);
  digitalWrite(rst, LOW);
  Button2.print("tap");

}
//-------（V1.1新增）强制关机【长按关机键】---------
void button3_callback(const String & state)
{
  BLINKER_LOG("get button state: ", state);
  digitalWrite(pwr, HIGH);
  Blinker.delay(5000);
  digitalWrite(pwr, LOW);
  Button3.print("tap");

}

void duerPowerState(const String &state, uint8_t num)
{
  BLINKER_LOG("need set outlet: ", num, ", power state: ", state);

  if (num == 1)
  {
    if (state == BLINKER_CMD_ON)
    {
      digitalWrite(pwr, HIGH);
      Blinker.delay(200);
      digitalWrite(pwr, LOW);

      BlinkerDuerOS.powerState("on", num);
      BlinkerDuerOS.print();
    }
    if (state == BLINKER_CMD_OFF)
    {
      digitalWrite(pwr, HIGH);
      Blinker.delay(200);
      digitalWrite(pwr, LOW);

      BlinkerDuerOS.powerState("off", num);
      BlinkerDuerOS.print();
    }
  }
  else if (num == 2)
  {
    if (state == BLINKER_CMD_ON)
    {
      digitalWrite(rst, HIGH);
      Blinker.delay(200);
      digitalWrite(rst, LOW);

      BlinkerDuerOS.powerState("on", num);
      BlinkerDuerOS.print();
    }
    if (state == BLINKER_CMD_OFF)
    {
      digitalWrite(rst, HIGH);
      Blinker.delay(200);
      digitalWrite(rst, LOW);

      BlinkerDuerOS.powerState("off", num);
      BlinkerDuerOS.print();
    }
  }

  else if (num == 3)
  {
    if (state == BLINKER_CMD_ON)
    {
      digitalWrite(pwr, HIGH);
      Blinker.delay(5000);
      digitalWrite(pwr, LOW);

      BlinkerDuerOS.powerState("on", num);
      BlinkerDuerOS.print();
    }
    if (state == BLINKER_CMD_OFF)
    {
      digitalWrite(pwr, HIGH);
      Blinker.delay(5000);
      digitalWrite(pwr, LOW);

      BlinkerDuerOS.powerState("off", num);
      BlinkerDuerOS.print();
    }
  }
  oState[num] = false;

  if (num == 0)
  {
    for (uint8_t o_num = 0; o_num < 5; o_num++)
    {
      oState[o_num] = false;
    }
  }
}

void duerQuery(int32_t queryCode)
{
  BLINKER_LOG("DuerOS Query codes: ", queryCode);

  switch (queryCode)
  {
    case BLINKER_CMD_QUERY_POWERSTATE_NUMBER :
      BLINKER_LOG("DuerOS Query power state");
      BlinkerDuerOS.powerState(oState ? "on" : "off");
      BlinkerDuerOS.print();
      break;
    case BLINKER_CMD_QUERY_TIME_NUMBER :
      BLINKER_LOG("DuerOS Query time");
      BlinkerDuerOS.time(millis());
      BlinkerDuerOS.print();
      break;
    default :
      BlinkerDuerOS.powerState(oState ? "on" : "off");
      BlinkerDuerOS.print();
      break;
  }
}


void setup()
{
  //开启blinker 若不出错此命令可以不执行
  Blinker.deleteTimer();

  // 初始化串口
  Serial.begin(115200);

  //开启DEBUG（监视器可以查看）
  BLINKER_DEBUG.stream(Serial);

  // 初始化IO
  pinMode(pwr, OUTPUT);
  pinMode(rst, OUTPUT);

  //默认写入低电平
  digitalWrite(pwr, LOW);
  digitalWrite(rst, LOW);

  // 初始化blinker
  Blinker.begin(auth);
  Blinker.attachData(dataRead);

  //回调小度
  BlinkerDuerOS.attachPowerState(duerPowerState);
  BlinkerDuerOS.attachQuery(duerQuery);

  //注册回调函数(点灯app内)
  Button1.attach(button1_callback);
  Button2.attach(button2_callback);
  Button3.attach(button3_callback);

}

void loop()
{
  Blinker.run();
}
