const byte LATCH_PIN = 2;
const byte LATCH_PORT = _BV(2);

const byte CLOCK_PIN = 3;


// MISO
const byte DATA_OUT_PIN = 12;
const byte DATA_OUT_PORT = _BV(4);
// MOSI
const byte DATA_IN_PIN = 11;
const byte DATA_IN_PORT = _BV(3);

const short MSB_SHORT = 0x8000;
const short TO_SEND = 0xAAA0;

volatile short bufferToSend = 0;
volatile short finalCount = 0;
volatile short count = 0;

void setup()
{
  pinMode(DATA_OUT_PIN, OUTPUT);

  Serial.begin(38400);
  Serial.println("Hello Arduino!");

  attachInterrupt(digitalPinToInterrupt(LATCH_PIN), latchInterrupted, RISING);
  attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), clockInterrupted, RISING);
}

void loop()
{
  //Serial.println(finalCount);
}

void latchInterrupted()
{
  //Serial.println(~bufferToSend);
  //Serial.println(TO_SEND);
  finalCount = count;
  count = 0;

  PORTB |= DATA_OUT_PORT;
  bufferToSend = ~TO_SEND;

  while (PORTB & LATCH_PORT) {
  }

  sendOneBitToSnes();
}

void clockInterrupted()
{
  sendOneBitToSnes();
}

void sendOneBitToSnes()
{
  count++;
  if (bufferToSend & MSB_SHORT)
  {
    PORTB |= DATA_OUT_PORT;
  }
  else
  {
    PORTB &= ~DATA_OUT_PORT;
  }

  bufferToSend = bufferToSend << 1;
}
