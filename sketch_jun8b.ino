#include <ctype.h>

const int buzzerPin = 8;
const int frequency = 4000;
const int unit = 100;

struct MorseCode
{
  char letter;
  const char* code;
};

MorseCode morseTable[] =
{
  {'A', ".-"}, {'B', "-..."}, {'C', "-.-."},
  {'D', "-.."}, {'E', "."}, {'F', "..-."},
  {'G', "--."}, {'H', "...."}, {'I', ".."},
  {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
  {'M', "--"}, {'N', "-."}, {'O', "---"},
  {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},
  {'S', "..."}, {'T', "-"}, {'U', "..-"},
  {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
  {'Y', "-.--"}, {'Z', "--.."},

  {'0', "-----"}, {'1', ".----"},
  {'2', "..---"}, {'3', "...--"},
  {'4', "....-"}, {'5', "....."},
  {'6', "-...."}, {'7', "--..."},
  {'8', "---.."}, {'9', "----."}
};

void playDot()
{
  tone(buzzerPin, 1000);
  delay(unit);
  noTone(buzzerPin);
  delay(unit);
}

void playDash()
{
  tone(buzzerPin, 1000);
  delay(3 * unit);
  noTone(buzzerPin);
  delay(unit);
}

void playMorseChar(char c)
{
  c = toupper(c);

  for (int i = 0; i < sizeof(morseTable)/sizeof(morseTable[0]); i++)
  {
    if (morseTable[i].letter == c)
    {
      const char* code = morseTable[i].code;

      for (int j = 0; code[j] != '\0'; j++)
      {
        if (code[j] == '.')
        {
          playDot();
          Serial.print(".");
        }
        else
        {
          playDash();
          Serial.print("-");
        }
      }

      Serial.print(" ");
      delay(2 * unit);
      return;
    }
  }
}

void setup()
{
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  Serial.println("=== MORSE CODE BUZZER ===");
  Serial.println("Type text and press Enter");
}

void loop()
{
  if (Serial.available())
  {
    String message = Serial.readStringUntil('\n');

    Serial.print("Received: ");
    Serial.println(message);

    for (int i = 0; i < message.length(); i++)
    {
      if (message[i] == ' ')
      {
        delay(7 * unit);
        Serial.print(" / ");
      }
      else
      {
        playMorseChar(message[i]);
      }
    }

    Serial.println();
    Serial.println("Transmission Complete");
  }
}