/*
  Showing number 0-9 on a Common Anode 7-segment LED display
  Displays the numbers 0-9 on the display, with one second inbetween.
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D
  This example code is in the public domain.
 */


const byte interruptPin = 2;

volatile int mycounter = 0;

//ABCDEFG,dp
const int numeral[10]= {
B00111111, //0
B00000110, //1
B01011011, //2
B01001111, //3
B01100110, //4
B01101101, //5
B01111100, //6
B00000111, //7
B01111111, //8
B01100111, //9
};

//pins for decimal point and each segment
//A,B,C,D,E,F,G
const int segmentPins[]= { 13,3,4,5,6,7,8};

const int numberofDigits=4;

const int digitPins[numberofDigits] = { 9,10,11,12}; //digits 1, 2, 3, 4


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pins as outputs.
  for (int i=0; i < 8; i++)
    pinMode(segmentPins[i], OUTPUT); //set segment and DP pins to output

//sets the digit pins as outputs
  for (int i=0; i < numberofDigits; i++)
    pinMode(digitPins[i], OUTPUT); 

  for (int i=0; i < numberofDigits; i++)
    digitalWrite(digitPins[i], HIGH);   

  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), inc_count, FALLING);
  mycounter = 0;
}

void inc_count() {
  mycounter = mycounter+1;
  delayMicroseconds(10);
}

void showNumber (int number)
{
  if (number == 0)
    showDigit (0, numberofDigits-1); //display 0 in the rightmost digit
  else
    {
    for (int digit= numberofDigits-1; digit >=0; digit--)
      {
        if (number > 0)
          {
             showDigit(number % 10, digit);
             number= number/10;
          }
      }
    }
}

//Displays given number on a 7-segment display at the given digit position
void showDigit (int number, int digit)
  {
     digitalWrite(digitPins[digit], LOW);
     for (int segment= 0; segment < 7; segment++)
        {
           boolean isBitSet= bitRead(numeral[number], segment);
          // isBitSet= ! isBitSet; //remove this line if common cathode display
           digitalWrite(segmentPins[segment], isBitSet);
        }
     digitalWrite(digitPins[digit], HIGH);
  }


// the loop routine runs over and over again forever:
void loop() {
  showNumber(mycounter);
  //delay(100);
}