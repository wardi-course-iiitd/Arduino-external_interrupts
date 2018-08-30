////////////////////////////////////////////////////////////
/* Code written by Gaurav Duggal 27-08-2018               */
//Reference: Atmega 328 datasheet and Arduino Reference page
////////////////////////////////////////////////////////////
#define positive 3
#define negative 4
#define sig 2
#define led 13


volatile unsigned int state = 0;
volatile signed long gtime =0;
volatile byte flag = 0;
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
  timer1_init();
}

void INT_ISR()
{
  if (flag ==0)
    {
      //log the time interrupt was triggered
      // frequency of a tick is 16e6/1024 = 15625Hz
      // each tick is 64 us.
      gtime = TCNT1;
      flag = 1;
      //reset the timer
      TCNT1 = 0;
    }
    
  state ^= 1;
  
}

// This sets the timer1 to count every 64 us. The counter is reset every 4.19seconds
void timer1_init()
{
  cli();
    // set up timer with no prescaling
    TCCR0A = 0;
    //prescaler = 1024
    TCCR0B |= (1 << CS00)| (1<<CS02);
 
    // initialize counter
    TCNT1 = 0;
    
    sei();
}


void loop() {
  // put your main code here, to run repeatedly:
  if (flag == 1)
  {
    Serial.print('$');
    Serial.println(gtime);
    flag = 0;
  }
  digitalWrite(led,state);


}
