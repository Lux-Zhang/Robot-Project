#include <Servo.h>

extern const int UNLOAD_SERVO_PIN;
Servo UnloadServo;  // 定义Servo对象来控制
int pos = 0;     // 角度存储变量

void UnloadServo_initialize(void)
{
  UnloadServo.attach(UNLOAD_SERVO_PIN);  // 控制线连接数字9
  pos = 130;
  UnloadServo.write(pos); //总之初始角度先调整为10°防止卡死
}

void Unload(void)
{
  pos = 10;
  UnloadServo.write(pos); // 转120度能够将物块放置
//  for (pos = 0; pos <= 180; pos ++) { // 10°到130°
//    myservo.write(pos);  
//    delay(5);
//  }   如果太快控制速度用的
}
