
#include "Arduboy.h"
Arduboy arduboy;

 

//counter for sound
float floatI = 0;

float tempo = 0.5;

int currentsound = 4;


void setup() {
  arduboy.begin();
  arduboy.setFrameRate(15);
  pinMode(PIN_SPEAKER_1, OUTPUT);

}


byte sound1(int i)
{
  return i / 13 >> (1 + ((i >> 12) & 3)) | i / 2 >> 2 & (i / 6) >> 7 | i & 31 * i * (i >> 8);
}

byte sound2(int i)
{
  return (i / 3 >> (i % 40 + 5) | i / (24 + i & 3) >> (i % (15 - ((i >> 15) % 8) * 6) + 5)) / 8;
}

byte sound3(int i)
{
  return i >> 2;
}


byte sound4(int i)
{
  return int( ((sin(i * 0.005) / 2.0) + 1) * 127);
}


byte getSound(byte soundtype, int i)
{
  //yes yes, can be done with function array pointers.

  switch (soundtype)
  {
    case 1:
      {
        return  sound1(i);
      }
    case 2:
      {
        return  sound2(i);
      }
    case 3:
      {
        return  sound3(i);
      }

    case 4:
      {
        return  sound4(i);
      }



  }
}

void loop() {

  // always write the sound out begore doing or not doing arduboy stuff
  int i = (int)floatI;
  int a = getSound(currentsound, i);

  digitalWrite(PIN_SPEAKER_1, a % 2); //writing the output sound

  floatI += tempo; //float counter so that you can set tempo


  if (!(arduboy.nextFrame()))
    return;


  arduboy.clear();

  for (int x = 0; x < 128; x++)
  {
    int y = getSound(currentsound, floatI + x);
    arduboy.drawPixel(x, y % 64, 1);
  }

  if (arduboy.pressed(A_BUTTON) ) {
    tempo += 0.1;
  }

  if (arduboy.pressed(B_BUTTON) ) {
    tempo -= 0.1;
  }

  if (arduboy.pressed(UP_BUTTON) ) {
    currentsound = 1;
    floatI = 0;
  }

  if (arduboy.pressed(DOWN_BUTTON) ) {
    currentsound = 2;
    floatI = 0;
  }

  if (arduboy.pressed(LEFT_BUTTON) ) {
    currentsound = 3;
    floatI = 0;
  }

  if (arduboy.pressed(RIGHT_BUTTON) ) {
    currentsound = 4;
    floatI = 0;
  }



  arduboy.display();


}
