////////////////////////////////////////////////////////////
/* Code written by Gaurav Duggal 27-08-2018               */
//Reference: Atmega 328 datasheet and Arduino Reference page
////////////////////////////////////////////////////////////
#define positive 3
#define negative 4
#define sig 2
#define led 13


volatile unsigned int state = 0;
volatile signed int gtime =0;
void setup() {
  // put your setup code here, to run once:
pinMode(positive,OUTPUT);
pinMode(negative,OUTPUT);
Serial.begin(9600);
digitalWrite(positive,HIGH);
digitalWrite(negative,LOW);
pinMode(sig,INPUT);
//note: sig has to be 2 or 3 in the arduino uno
attachInterrupt(digitalPinToInterrupt(sig), INT_ISR, RISING);
pinMode(led,OUTPUT);
}

void INT_ISR()
{
  state ^= 1;
  gtime = millis() - gtime;
}

void loop() {
  // put your main code here, to run repeatedly:
 
  Serial.println(gtime);
  digitalWrite(led,state);


}
