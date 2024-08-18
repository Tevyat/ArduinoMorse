#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int dotButton = 4;
int dashButton = 5;
int spaceButton = 6;
int endButton = 7;
String message = "";

struct morseDictionary {
  String morseCode;
  char letter;       
}

morseDictionary morse[] = {
  {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'},
  {".", 'E'}, {"..-.", 'F'}, {"--.", 'G'}, {"....", 'H'},
  {"..", 'I'}, {".---", 'J'}, {"-.-", 'K'}, {".-..", 'L'},
  {"--", 'M'}, {"-.", 'N'}, {"---", 'O'}, {".--.", 'P'},
  {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'},
  {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'},
  {"-.--", 'Y'}, {"--..", 'Z'}, {".----", '1'}, {"..---", '2'},
  {"...--", '3'}, {"....-", '4'}, {".....", '5'}, {"-....", '6'},
  {"--...", '7'}, {"---..", '8'}, {"----.", '9'}, {"-----", '0'}
};

const int dictionarySize = sizeof(morse) / sizeof(MorseDictionary);

char letterMorse(String morseCode) {
  for (int i = 0; i < dictionarySize; i++) {
    if (morse[i].morseCode == morseCode) {
      return morse[i].letter;  
    }
  }
  return '\0';  
}


String translate(String morseMessage) { 
  String decodedMessage = "";

  int start = 0;
  int end = morseMessage.indexOf(' ');

  while (end != -1) {
    String morseChar = morseMessage.substring(start, end);
    decodedMessage += letterMorse(morseChar);
    start = end + 1;
    end = morseMessage.indexOf(' ', start);
  }

  decodedMessage += letterMorse(morseMessage.substring(start));

  return decodedMessage;
}

void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(dotButton, INPUT);
  pinMode(dashButton, INPUT);
  pinMode(spaceButton, INPUT);
  pinMode(endButton, INPUT);
}

void loop() {
  int endButtonState = digitalRead(endButton);
  int dot = digitalRead(dotButton);
  int dash = digitalRead(dashButton);
  int space= digitalRead(spaceButton);

  if(dot == HIGH) {
    message += ".";
    delay(200);
  } else if (dash == HIGH) {
    message += "-";
    delay(200);
  } else if (space == HIGH) {
    message += " ";
    delay(200);
  } else if (endButtonState == HIGH) {
    String decodedMessage = translate(message);
    lcd.begin();
    lcd.backlight();
    lcd.print(decodedMessage);
  }
}
