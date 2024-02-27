#include <Servo.h>

Servo myservo;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int buzzer = 13;
int trigPin = 7;
int echoPin = 8;
int trigPin2 = 12;
int echoPin2 = 2;
int s1 = 90;
int s2 = 90;
int s3 = 180;
int s4 = 110;
int s5 = 90;
int s6 = 60;
int mudanca = 8;
int d2;
int  Automatico = 0; 
int tempo_anterior = 0;
int tempo_atual = 0;
float v2 = 331.5 + 0.6 * 20;
float v = 331.5 + 0.6 * 20;
bool Manual = false;
bool bracomovimento = false;
 
void setup() {
  Serial.begin(9600);
  myservo.attach(4);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(6);
  servo4.attach(5);
  servo5.attach(11);
  servo6.attach(3);
  servo1.write(s1);
  servo2.write(s2);
  servo3.write(s3);
  servo4.write(s4);
  servo5.write(s5);
  servo6.write(s6);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}
float distanceCm(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(51);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(11);
  digitalWrite(trigPin, LOW);
  float tUs = pulseIn(echoPin, HIGH);
  float t = tUs / 1000.0 / 1000.0 / 2.0;
  float d = t * v;
  return d * 100;
}
int andaServo(int servoID, int angSx, int angAlvo, int mudanca) {
    Servo* servo;
    if (servoID == 1) {
        servo = &servo1;
    } else if (servoID == 2) {
        servo = &servo2;
    } else if (servoID == 3) { 
        servo = &servo3;
    } else if (servoID == 4) {
        servo = &servo4;
    } else if (servoID == 5) {
        servo = &servo5;
    } else if (servoID == 6) {
        servo = &servo6;
    }
    if (angSx < angAlvo) {
        if (angSx + mudanca > angAlvo) {
            angSx = angAlvo;
        } else {
            angSx += mudanca;
        }
    }
    else if (angSx > angAlvo) { 
        if (angSx - mudanca < angAlvo) {
            angSx = angAlvo;
        } else {
            angSx -= mudanca;
        }
    }
    delay(15);
    servo->write(angSx); 
    return angSx; 
}
 
void servo(char dado_recebido){
  if (Manual == true){
    if (dado_recebido == 'U') {
    s1 = s1 + mudanca;
    if (s1 <= 5)
      s1 = 5;
    servo1.write(s1);
    delay(50);
  } else if (dado_recebido == 'R') {
    s2 = s2 - mudanca;
    if (s2 <= 5)
      s2 = 5;
    servo2.write(s2);
    delay(10);
  } else if (dado_recebido == 'D') {
    s1 = s1 - mudanca;  
    if (s1 >= 170)
      s1 = 170;
    servo1.write(s1);
    delay(50);
  } else if (dado_recebido == 'L') {
    s2 = s2 + mudanca;
    if (s2 >= 170)
      s2 = 170;
    servo2.write(s2);
    delay(10);
  } else if (dado_recebido == 'T') {
    s3 = s3 + mudanca;
    if (s3 <= 5)
      s3 = 5;
    servo3.write(s3);
    delay(10);
  } else if (dado_recebido == 'S') {
    s4 = s4 - mudanca;
    if (s4 <= 5)
      s4 = 5;
    servo4.write(s4);
    delay(10);
  } else if (dado_recebido == 'X') {
    s3 = s3 - mudanca;
    if (s3 >= 170)
      s3 = 170;
    servo3.write(s3);
    delay(10);
  } else if (dado_recebido == 'C') {
    s4 = s4 + mudanca;
    if (s4 >= 170)
      s4 = 170;
    servo4.write(s4);
    delay(10);
  } else if (dado_recebido == 'P') {
    s5 = s5 + mudanca;
    if (s5 <= 5)
      s5 = 5;
    servo5.write(s5);
    delay(10);
  } else if (dado_recebido == 'A') {
    s5 = s5 - mudanca;
    if (s5 >= 170)
      s5 = 170;
    servo5.write(s5);
    delay(10);
  } else if (dado_recebido == 'Q') {
    s6 = s6 + mudanca;
    if (s6 >= 170)
      s6 = 170;
    servo6.write(s6);
    delay(10);
  } else if (dado_recebido == 'F') {
    s6 = s6 - mudanca;
    if (s6 <= 5)
      s6 = 5;
    servo6.write(s6);
    delay(10);
  }
}
}
void trajetobraco(){
  if (Automatico == 1){
   s6 = andaServo(6, s6, 90, 2); 
   if (s6 <= 90) Automatico++; 
   Serial.print(s6);
   Serial.println(" graus.");
   delay(400);
  }
  else if (Automatico == 2){
   s3 = andaServo(3, s3, 180, 2); 
   if (s3 <= 180) Automatico++; 
   Serial.print(s3);
   Serial.println(" graus.");
   delay(400);
  }
   else if (Automatico == 3){
   s2 = andaServo(2, s2, 90, 2); 
   if (s2 <= 90) Automatico++; 
   Serial.print(s3);
   Serial.println(" graus.");
   delay(400);
  } 
   else if (Automatico == 4){
   s3 = andaServo(3, s3, 180, 2); 
   if (s3 <= 180) Automatico++; 
   Serial.print(s3);
   Serial.println(" graus.");
   delay(400);
  }
   else if (Automatico == 5){
   s4 = andaServo(4, s4, 60, 2); 
   if (s4 <= 60) Automatico++; 
   Serial.print(s4);
   Serial.println(" graus.");
   delay(400);
  }
  else if (Automatico == 6){
   s2 = andaServo(2, s2, 10, 2); 
   if (s2 <= 10) Automatico++; 
   Serial.print(s3);
   Serial.println(" graus.");
   delay(400);
  }
   else if (Automatico == 7){
   s4 = andaServo(4, s4, 150, 2); 
   if (s4 <= 150) Automatico++; 
   Serial.print(s4);
   Serial.println(" graus.");
   delay(400);
   }
   else if (Automatico == 8){
    s6 = andaServo(6, s6, 40, 2); 
   if (s6 <= 40) Automatico++; 
   Serial.print(s6);
   Serial.println(" graus.");
   delay(400);
   }
   else if (Automatico == 9){
   s4 = andaServo(4, s4, 40, 2); 
   if (s4 <= 60) Automatico++; 
   Serial.print(s4);
   Serial.println(" graus.");
   delay(400);
  }
   else if (Automatico == 10){
   s2 = andaServo(2, s2, 90, 2); 
   if (s2 <= 90) Automatico++; 
   Serial.print(s3);
   Serial.println(" graus.");
   delay(400);
  }
   else if (Automatico == 11){
   s4 = andaServo(4, s4, 150, 2); 
   if (s4 <= 150) Automatico++; 
   Serial.print(s4);
   Serial.println(" graus.");
   delay(400);
  }
  else if (Automatico ==12){
   s6 = andaServo(6, s6, 90, 2); 
   if (s6 <= 90) Automatico++; 
   Serial.print(s6);
   Serial.println(" graus.");
   delay(400); 
  }
  else if (Automatico == 13){
    posinicial ();
  }
}
void posinicial() {
  servo1.write(90);
  servo2.write(90);
  servo3.write(180);
  servo4.write(110);
  servo5.write(90);
  servo6.write(90);
  myservo.writeMicroseconds(1600);
  Automatico = 0;
  bracomovimento = false;
  Manual = true;
}
void loop() {
  if (Serial.available()) {
    char dado_recebido = Serial.read();
    Serial.println(dado_recebido);
    servo(dado_recebido);
    if (dado_recebido == 'O') {
    Manual = false;
    bracomovimento = true;
    Automatico = 1;
  } 
    if (dado_recebido == 'J'){
    Manual = true;
  }
  }
  tempo_atual = millis();
  if (tempo_atual - tempo_anterior >= 1000){
  Serial.print(s1); 
  Serial.print(" | ");
  Serial.print(s2);
  Serial.print(" | ");  
  Serial.print(s3); 
  Serial.print(" | ");
  Serial.print(s4);
  Serial.print(" | ");
  Serial.print(s5); 
  Serial.print(" | ");   
  Serial.println(s6); 
  tempo_anterior = tempo_atual;
}
  int d = distanceCm(trigPin,echoPin);
  if (d >= 8) {
    myservo.writeMicroseconds(1600);
  } else {
    myservo.writeMicroseconds(1500);
  }
  int d2 = distanceCm(trigPin2,echoPin2);
  digitalWrite(buzzer,LOW);
  while (d2 <= 5){
    d2 = distanceCm(trigPin2,echoPin2);
    Serial.print(d);
    Serial.print("/");
    Serial.println(d2);
    digitalWrite(buzzer,HIGH);
    myservo.writeMicroseconds(1500);
    delay(500);
  }
  while (bracomovimento) {
    trajetobraco();
  }
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
