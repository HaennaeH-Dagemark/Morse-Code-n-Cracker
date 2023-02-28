char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
char numbers[] = "0123456789";
String morsephabet[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
String morseber[] = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

int mode = 0;
int arraynum = 0;
int pastindex = 0;
bool falsecheck;


String output;
String outputchar;
String input;
String manualInput;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Ran loop");

  if (mode == 0)
  {
    Serial.println("State your errand, 1 for encoding, 2 for decoding, 3 for recording manual input");
    Serial.println(output);
    while (Serial.available() == 0)
    {}
    mode = Serial.parseInt();
  }

  if (mode == 1)
  {
    output = "";
    input = "";
    encoderfunction();
    mode = 0;
  }

  if (mode == 2)
  {
    pastindex = 0;
    output = "";
    input = "";
    decoderfunction();
    mode = 0;
  }
  if (mode == 3)
  {
    output = "";
    input = "";
    manualInput = "";
    readerfunction();
    mode = 0;
  }
}

void encoderfunction()
{
  Serial.println("Selected Encoder");
  delay(1000);
  Serial.print("Input text: ");
  while (input.length() <= 1)
  {
    input = Serial.readString();
  }
  Serial.println(input + input.length());
  for (int i = 0; i != (input.length() - 1); i++)
  {
    for (int x = 0; x != 27; x++)
    {
      if ((input[i]) == (alphabet[x]))
      {
        outputchar = morsephabet[x];
      }
    }
    for (int x = 0; x != 10; x++)
    {
      if (input[i] == numbers[x])
      {
        outputchar = morseber[x];
      }
    }
    if (String(input[i]) == String(" "))
    {
      outputchar = ("/");
    }
    output = output + outputchar + " ";
  }
  Serial.println("Output: " + output);
}

void decoderfunction()
{
  Serial.println("Selected Decoder");
  delay(1000);
  Serial.print("Input text: ");
  while (input.length() <= 1)
  {
    input = Serial.readString();
  }
  Serial.print(input);

  falsecheck = false;
  while (falsecheck == false)
  {
    int i;
    i++;
    int index = 0;

    index = input.indexOf(' ', pastindex);

    if (index == -1)
    {
      Serial.println("ending");
      falsecheck = true;
      break;
    }

    String SubInput = input.substring(pastindex, index);
    Serial.print(index);
    Serial.println(SubInput);
    pastindex = index + 1;

    for (int x = 0; x != 27; x++)
    {
      if (String(SubInput) == String(morsephabet[x]))
      {
        outputchar = alphabet[x];
        Serial.println("Outputchar: " + outputchar);
      }
    }

    for (int x = 0; x != 10; x++)
    {
      if (SubInput == morseber[x])
      {
        outputchar = numbers[x];
      }
    }

    if (String(SubInput) == String("/"))
    {
      outputchar = (" ");
      Serial.println("Outputchar: Space");
    }
    output = output + outputchar;
  }
  Serial.println("Output: " + output);
}

void readerfunction()
{
  int completeread = 0;
  while (completeread != 1)
  {
    int readmillis = 0;
    while (digitalRead(2) == HIGH)
    {
      readmillis += 1;
      delay(1);
    }
    if (readmillis != 0)
    {
      if (readmillis <= 250)
      {
        Serial.print(".");
      }
      else
      {
        Serial.print("-");
      }
      delay(10);
      readmillis = 0;
    }
    while (digitalRead(3) == HIGH)
    {
      readmillis += 1;
      delay(1);
    }
    if (readmillis != 0)
    {
      if (readmillis <= 250)
      {
        Serial.print(" ");
      }
      else if (readmillis <= 500)
      {
        Serial.print("///");
      }
      else
      {
        completeread = 1;
      }
      delay(10);
    }
  }
  Serial.println("Ending read");
}
