// Modul Praktikum 3 Sistem Kendali kasus P
// Nama Tim : OverPower
// Nama Anggota 1 : Nur Cahya Utama 6702190046
// Nama Anggota 2 : Aditya Firmansyah H 6702190043

//Deklarasi Pin sensor analog
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;
int baca_sensor[6];

//Variable bantuan untuk menyimpan data
int LastError;
int error ;
int kecepatanMotorKanan, kecepatanMotorKiri, kecepatansetPoint = 150, moveControl;

//pin penggerak Motor
int pinEnable = 4; //Pin 1&2 harus HIGH
int pinEnable2 = 2; //Pin 3&4 harus HIGH

//pin Motorkiri 
int motor_kiri1 = 5; //input motor driver
int motor_kiri2 = 6; //input motor driver

//pin Motorkanan
int motor_kanan1 = 3;
int motor_kanan2 = 11;

void setup(){
//Sensor Photodiode sebagai INPUT
pinMode(sensor1, INPUT);
pinMode(sensor2, INPUT);
pinMode(sensor3, INPUT);
pinMode(sensor4, INPUT);
pinMode(sensor5, INPUT);
pinMode(sensor6, INPUT);

  //Motor sebagai OUTPUT
pinMode(pinEnable, OUTPUT);
pinMode(pinEnable2, OUTPUT);
pinMode(motor_kiri1, OUTPUT);
pinMode(motor_kiri2, OUTPUT);
pinMode(motor_kanan1, OUTPUT);
pinMode(motor_kanan2, OUTPUT);
Serial.begin(9600);
}
//Membaca sinyal analog dari sensor
void readsensor(){
   baca_sensor[0] = analogRead(sensor1); 
  baca_sensor[1] = analogRead(sensor2); 
    baca_sensor[2] = analogRead(sensor3);
    baca_sensor[3] = analogRead(sensor4); 
    baca_sensor[4] = analogRead(sensor5);
    baca_sensor[5] = analogRead(sensor6); 
  // Menampilkan Data sensor 1-6
  // Formatting tampilkan sensor
  /*
  for(int i=0; i<=5; i++){
    
    Serial.print("\nSensor ");
    Serial.print(i+1);
    Serial.print(" = ");
    Serial.print(baca_sensor[i]);
    delay(500);
  }
  Serial.print("\n"); */
}
void follow_line(int LastError) {
  int kp = 5, ki = 0, kd = 0;
  //int rate = error - LastError;
  //LastError = error;
  moveControl = kp*LastError;
  kecepatanMotorKanan = kecepatansetPoint + moveControl;
  kecepatanMotorKiri = kecepatansetPoint - moveControl;
  
  //Serial.print ("\nerror : ");
  //Serial.println (error);
  //delay(500);
  //Serial.print ("\nrate : ");
  //Serial.println (rate);
  //delay(500);
  //Serial.print ("\nKecepatan Motor Kanan : ");
  Serial.println (kecepatanMotorKanan);
  delay(100);
  //Serial.print ("\nKecepatan Motor Kiri : ");
  //Serial.println (kecepatanMotorKiri);
  //delay(100);
  
  digitalWrite(pinEnable, HIGH);
  analogWrite(motor_kiri1,kecepatanMotorKiri);  
  analogWrite(motor_kiri2,0);
  digitalWrite(pinEnable2, HIGH);
  analogWrite(motor_kanan1,kecepatanMotorKanan);  
  analogWrite(motor_kanan2,0);
}
void loop(){
  readsensor();

  //kondisi 1 sensor 1 dan 2 mendeteksi gelap
  if(baca_sensor[0] < 34 && baca_sensor[1] < 34 && 
     baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
     baca_sensor[4] > 34 && baca_sensor[5] > 34)
  {
    LastError=-2;
    follow_line(LastError);
  }
  
  // Kondisi 2 sensor 2 dan 3 mendeteksi gelap
  if(baca_sensor[0] > 34 && baca_sensor[1] < 34  && 
     baca_sensor[2] < 34 && baca_sensor[3] > 34  && 
     baca_sensor[4] > 34 && baca_sensor[5] > 34)
  {
    LastError=-1;
    follow_line(LastError);
    
  }
  
  //kondisi 3 sensor 3 dan 4 mendeteksi gelap
 if(baca_sensor[0] > 34 && baca_sensor[1] > 34  && 
     baca_sensor[2] < 34 && baca_sensor[3] < 34  && 
     baca_sensor[4] > 34 && baca_sensor[5] > 34)
  {
   LastError=0; 
   follow_line(LastError);
  }
  
  //kondisi 4 sensor 4 dan 5 mendeteksi gelap
  if(baca_sensor[0] > 34 && baca_sensor[1] > 34  && 
     baca_sensor[2] > 34 && baca_sensor[3] < 34  && 
     baca_sensor[4] < 34 && baca_sensor[5] > 34)
  {
    LastError=1;
    follow_line(LastError);
  }
  
  
  //kondisi 5 sensor 5 dan 6 mendeteksi gelap
  if(baca_sensor[0] > 34 && baca_sensor[1] > 34  && 
     baca_sensor[2] > 34 && baca_sensor[3] > 34  && 
     baca_sensor[4] < 34 && baca_sensor[5] < 34)
  {
    LastError=2;
    follow_line(LastError);
  }
  
  
  //Kondisi 6 Semua sensor terang
  if(baca_sensor[0] > 34 && baca_sensor[1] > 34  && 
     baca_sensor[2] > 34 && baca_sensor[3] > 34  && 
     baca_sensor[4] > 34 && baca_sensor[5] > 34)
  {
  digitalWrite(pinEnable, HIGH);
    //analogWrite(pin,value 0-255)
    analogWrite(motor_kiri1,0);  
    analogWrite(motor_kiri2,0);
    
    digitalWrite(pinEnable2, HIGH);
    analogWrite(motor_kanan1,0);  
    analogWrite(motor_kanan2,0);
    //Serial.println("Robot keluar lintasan");
    //delay(500);
   
  }
  //Kondisi Sensor 1 mendeteksi gelap
  else if(baca_sensor[0] < 34 && baca_sensor[1] > 34  && 
     baca_sensor[2] > 34 && baca_sensor[3] > 34  && 
     baca_sensor[4] > 34 && baca_sensor[5] > 34)
  {
  baca_sensor[1] = baca_sensor[0];
  LastError = -2;
  follow_line(LastError);
  showError();
  

  }
   //Kondisi Sensor 2 mendeteksi gelap
  else if(baca_sensor[0] > 34 && baca_sensor[1] < 34  && 
     baca_sensor[2] > 34 && baca_sensor[3] > 34  && 
     baca_sensor[4] > 34 && baca_sensor[5] > 34)
  {
  baca_sensor[2] = baca_sensor[1];
  LastError = -1;
  follow_line(LastError);
  showError();
  

  }
  //Kondisi Sensor 3 mendeteksi gelap
  else if(baca_sensor[0] > 34 && baca_sensor[1] > 34  && 
     baca_sensor[2] < 34 && baca_sensor[3] > 34  && 
     baca_sensor[4] > 34 && baca_sensor[5] > 34)
  {
  baca_sensor[3] = baca_sensor[2];
  LastError = 0;
  follow_line(LastError);
  showError();
  }
  //Kondisi Sensor 4 mendeteksi gelap
  else if(baca_sensor[0] > 34 && baca_sensor[1] > 34  && 
     baca_sensor[2] > 34 && baca_sensor[3] < 34  && 
     baca_sensor[4] > 34 && baca_sensor[5] > 34)
  {
  baca_sensor[2] = baca_sensor[3];
  LastError = 0;
  follow_line(LastError);
  showError();
  }
  //Kondisi Sensor 5 mendeteksi gelap
  else if(baca_sensor[0] > 34 && baca_sensor[1] > 34  && 
     baca_sensor[2] > 34 && baca_sensor[3] > 34  && 
     baca_sensor[4] < 34 && baca_sensor[5] > 34)
  {
  baca_sensor[3] = baca_sensor[4];
  LastError = 1;
  follow_line(LastError);
  showError();
  }
  //Kondisi Sensor 6 mendeteksi gelap
  else if(baca_sensor[0] > 34 && baca_sensor[1] > 34  && 
     baca_sensor[2] > 34 && baca_sensor[3] > 34  && 
     baca_sensor[4] > 34 && baca_sensor[5] < 34)
  {
  baca_sensor[4] = baca_sensor[5];
  LastError = 2;
  follow_line(LastError);
  showError();
  }
}
void showError(){
  //Serial.print("\nError : ");
  //Serial.println(LastError);
  LastError = 0;
}