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


const byte analog_in = 0;

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

const int digitPins[numberofDigits] = {9,10,11,12}; //digits 1, 2, 3, 4

int analog_input_pin = 0;

int hall_value = 0;


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
  
 

  mycounter = 0;
 // Serial.begin(9600);
}


void showNumber (int number)
{
  if (number == 0)
    showDigit (0, 0); //display 0 in the rightmost digit
  else
    {
 //   for (int digit= numberofDigits-1; digit >=0; digit--)
    for (int digit= 0; digit < numberofDigits; digit++)
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
/*     Serial.print("the digit to print ");
     Serial.print(digitPins[digit]);
     Serial.print("  the number to print ");
     Serial.println(number);  */

     for (int segment= 0; segment < 7; segment++)
        {
           boolean isBitSet= bitRead(numeral[number], segment);
          // isBitSet= ! isBitSet; //remove this line if common cathode display
           digitalWrite(segmentPins[segment], isBitSet);
        }
     digitalWrite(digitPins[digit], LOW);   
     delay(5);
     digitalWrite(digitPins[digit], HIGH);
  }


// the loop routine runs over and over again forever:
void loop() {
  int low = 0;
  int mid = 1;
  int high = 2;
  int state = low;

  hall_value = analogRead(analog_input_pin);
  
  if((hall_value > 650) and (state = low))
  {
    state = high;
    mycounter ++;
  } 
  else if ((state = high) and (hall_value < 650))
  {
    state = low;
  }
  else
     __asm__("nop");

  showNumber(mycounter);
  //showNumber(hall_value);
 // Serial.println(mycounter);
 // delay(1000);
}