#define Forward 1 // 전진
#define Backward 2 // 후진
#define Turn_Right 3 // 우회전
#define Turn_Left 4 // 좌회전
#define Stop 5 // 정지
int g_carDirection = 0; // 차량 운행상태 전역변수 선언
int speed = 200;
#define ENA 6 // 모터 제어드라이버 ENA와 Shield의 S6핀 연결
#define EN1 7 // 모터 제어드라이버 EN1와 Shield의 S7핀 연결
#define EN2 3 // 모터 제어드라이버 EN2와 Shield의 S3핀 연결
#define EN3 4 // 모터 제어드라이버 EN3와 Shield의 S4핀 연결
#define EN4 2 // 모터 제어드라이버 EN4와 Shield의 S2핀 연결
#define ENB 5 // 모터 제어드라이버 ENB와 Shield의 S5핀 연결

#define LT_MODULE_L A0
#define LT_MODULE_F A2
#define LT_MODULE_R A4 

void setup() {
  // put your setup code here, to run once:

}

void init_line_tracer_modules()
{
 pinMode(LT_MODULE_L , INPUT);
 pinMode(LT_MODULE_F , INPUT);
 pinMode(LT_MODULE_R , INPUT);
}

bool lt_isLeft() // 왼쪽 Line Tracer 모듈
{
 int ret = digitalRead(LT_MODULE_L);
 return (ret == 1) ? (true) : (false);
}
bool lt_isForward() // 중간 Line Tracer 모듈
{
int ret = digitalRead(LT_MODULE_F);
return (ret == 1) ? (true) : (false);
}
bool lt_isRight() // 오른쪽 Line Tracer 모듈
{
 int ret = digitalRead(LT_MODULE_R);
 return (ret == 1) ? (true) : (false);
}

void lt_mode_update()
{
 bool ll = lt_isLeft();
 bool ff = lt_isForward();
 bool rr = lt_isRight();
 if (ll&&ff&&rr)
 {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0); // stop
 }
 else if (!ll&&!ff&&!rr)
 {
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, HIGH);
  analogWrite(ENA, speed);

  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
  analogWrite(ENB, speed); // back
 }
 else if (ll&ff)
 {
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
  analogWrite(ENB, speed); //forward
 }
 else if (ll)
 {
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, HIGH);
  analogWrite(ENA, speed);

  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
  analogWrite(ENB, speed); // left
 }
 else if (rr)
 {
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
  analogWrite(ENB, speed); // right
 }
 else if (ff)
 {
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
  analogWrite(ENB, speed); // right
 }
}

void loop() {
  // put your main code here, to run repeatedly:
  lt_mode_update();
}
