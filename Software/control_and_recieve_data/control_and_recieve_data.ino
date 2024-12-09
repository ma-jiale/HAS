#include <Servo.h>
#include <DHT.h>

// 设置DHT11传感器的引脚
#define DHTPIN 9
#define DHTTYPE DHT11   // 定义使用的DHT传感器类型
#define LED_PIN 12
#define MOTOR_PIN 5
#define SERVO_PIN1 3
#define SERVO_PIN2 6

class Light {
  private:
    bool isOn;   // 灯的当前状态，true 表示灯开，false 表示灯关
    int pin;     // 灯连接到的引脚

  public:
    // 构造函数，初始化灯的状态（默认为关闭），并设置灯连接的引脚
    Light(int lightPin) {
      pin = lightPin;
      isOn = false;  // 默认灯的状态是关闭
      pinMode(pin, OUTPUT);  // 设置引脚为输出模式
      digitalWrite(pin, LOW);  // 初始化时设置灯为关
    }

    // 开关灯函数，根据当前灯的状态来执行开关操作
    void toggle() {
      if (isOn) {
        // 如果灯是开着的，关闭灯
        Serial.println("灯已关闭");
        digitalWrite(pin, LOW);  // 关闭灯
        isOn = false;
      } else {
        // 如果灯是关着的，打开灯
        Serial.println("灯已打开");
        digitalWrite(pin, HIGH);  // 打开灯
        isOn = true;
      }
    }

    // 获取灯的当前状态
    bool getState() 
    {
      return isOn;
    }
};

class Fan {
  private:
    bool isOn;   // 风扇的当前状态，true 表示风扇开，false 表示风扇关
    int pin;     // 风扇连接到的引脚

  public:
    // 构造函数，初始化风扇的状态（默认为关闭），并设置风扇连接的引脚
    Fan(int fan_pin) {
      pin = fan_pin;
      isOn = false;  // 默认风扇的状态是关闭
      pinMode(pin, OUTPUT);  // 设置引脚为输出模式
      digitalWrite(pin, LOW);  // 初始化时设置风扇为关
    }

    // 开关风扇函数，根据当前风扇的状态来执行开关操作
    void toggle() {
      if (isOn) {
        // 如果风扇是开着的，关闭风扇
        Serial.println("风扇已关闭");
        analogWrite(pin, 0);  // 关闭风扇
        isOn = false;
      } else {
        // 如果风扇是关着的，打开风扇
        Serial.println("风扇已打开");
        analogWrite(pin, 255);  // 打开风扇
        isOn = true;
      }
    }

    // 获取风扇的当前状态
    bool getState() 
    {
      return isOn;
    }
};

class SmartCurtain {
  private:
    Servo curtainServo1; 
    Servo curtainServo2; // 舵机对象
    int pin1;
    int pin2;            // 舵机连接的引脚
    bool isOpen;         // 窗帘的当前状态，true 表示窗帘已打开，false 表示窗帘已关闭

  public:
    // 构造函数，初始化舵机并设置引脚，默认窗帘是关闭的
    SmartCurtain(int servoPin1, int servoPin2) {
      pin1 = servoPin1;
      pin2 = servoPin2;
      isOpen = false;  // 默认窗帘是关闭的
    }

    void begin()
    {
      curtainServo1.attach(pin1);  // 将舵机连接到指定的引脚
      curtainServo1.write(0);
      curtainServo2.attach(pin2);  // 将舵机连接到指定的引脚
      curtainServo2.write(0);     // 初始化时设置窗帘为关闭状态
    }

    // 切换窗帘的开关状态
    void toggle() {
      if (isOpen) {
        // 如果窗帘已经打开，调用关闭窗帘函数
        Serial.println("关闭窗帘...");
        closeCurtain();
      } else {
        // 如果窗帘已经关闭，调用打开窗帘函数
        Serial.println("开启窗帘...");
        openCurtain();
      }
    }

    // 开启窗帘，从0度转到180度
    void openCurtain() {
      for (int pos = 0; pos <= 180; pos++) {
        curtainServo1.write(pos);  // 设置舵机的位置
        curtainServo2.write(pos);
        delay(15);  // 等待舵机移动到指定位置
      }
      isOpen = true;  // 更新窗帘状态为已打开
    }

    // 关闭窗帘，从180度转到0度
    void closeCurtain() {
      for (int pos = 180; pos >= 0; pos--) {
        curtainServo1.write(pos);  // 设置舵机的位置
        curtainServo2.write(pos); // 设置舵机的位置
        delay(15);  // 等待舵机移动到指定位置
      }
      isOpen = false;  // 更新窗帘状态为已关闭
    }

    // 获取窗帘的当前状态
    bool getState() {
      return isOpen;
    }
};

DHT dht(DHTPIN, DHTTYPE);
Light myLight(LED_PIN);
Fan myFan(MOTOR_PIN);
SmartCurtain myCurtian(SERVO_PIN1, SERVO_PIN2);
int pos = 0;
int temperature, humidity;

void setup() 
{
  Serial.begin(9600);
  dht.begin();   // 初始化DHT传感器
  myCurtian.begin();
  delay(2000);
}

void loop() 
{
    // 读取温湿度数据
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // 检查是否读取成功
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("读取传感器数据失败！");
    return;
  }

  // 打印温湿度值
  Serial.print("温度: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("湿度: ");
  Serial.print(humidity);
  Serial.println(" %");

  // 控制设备：读取串口输入，控制设备的开关状态
  if (Serial.available()) {
    char command = Serial.read();  // 读取串口数据

    switch (command) {
      case 'f':  // 切换风扇
        myFan.toggle();
        break;

      case 'c':  // 切换窗帘
        myCurtian.toggle();
        break;

      case 'l':  // 切换灯
        myLight.toggle();
        break;

      default:
        Serial.println("无效的命令,请输入f, c, 或者l");
        break;
    }
  }

  // 延迟0.2秒后再次执行
  delay(200);
}


