#include "Lib.h"
#include "Def.h"

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 60) { // Retry for 30 seconds
    delay(500);
    Serial.print(".");
    attempts++;
  }
//---------------------------------------------------------//
 if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
//------------------------------------------------------//

uint16_t tabMain = ESPUI.addControl(Tab,"", "Main");
manualops = ESPUI.addControl(Switcher, "Manual Operation", "0", Emerald, tabMain, SwitchChanged);
tempinmain = ESPUI.addControl(Label, "Temperature in C", "0", Turquoise, tabMain);
huminmain = ESPUI.addControl(Label, "Humidity", "0", Alizarin, tabMain);
//opttemp = ESPUI.addControl(Text, "Optimum Temperature", String(optimum).c_str(), Emerald, tabMain, optimumset);



uint16_t tab1 = ESPUI.addControl(Tab, "", "Light Controls");
uint16_t positionMax = ESPUI.addControl(Slider, "Brightness", "0", Alizarin, tab1, sliderled);
ESPUI.addControl(Min, "", "0", None, positionMax);
ESPUI.addControl(Max, "", "255",None, positionMax);
ESPUI.updateControlValue(positionMax, "0"); // Default value (if needed)
ESPUI.updateControl(positionMax);

uint16_t tab2 = ESPUI.addControl(Tab, "", "Temperature Controls");
uint16_t inputtemp = ESPUI.addControl(Text, "Optimal Temp , Temperature", " ", Alizarin, tab2, temperatureset);
//ESPUI.text("Optimal Temp , Temperature", &temperatureset, ControlColor::Alizarin,tab2, "");

//
//uint16_t opttemp = ESPUI.addControl(Text, "Set Humidity", "25", Emerald, tab2, optimumset);

ESPUI.begin("IS SOSE24 TEAM 17");

//-------------------------------------------------------------//
}
else { 
    Serial.println("\nFailed to connect to WiFi");
  }
    //------------------------------------------------//
    dht22.begin(); 
    //-----------------------------------------------//
    serv1.attach(servopin1); 
    serv2.attach(servopin2); 
    serv1.write(90); 
    serv2.write(90);
    //-------------------------------------------------//
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0X3C))
    {
        Serial.println("SSD1306 Allocate failed");
        while (true);
    }
    display.clearDisplay();
    display.setTextColor(WHITE);

    //-------------------------------------------------//
    nfc.begin();
    if (!nfc.getFirmwareVersion())
    {
        Serial.println("Didn't find PN53x board");
        while (true)
        {
            delay(1);
        }
    }
    //-------------------------------------------------------//
    pinMode(ledPin, OUTPUT); 

    //--------------------------------------------------------//
    pinMode(interruptpin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptpin), button_intfunc, FALLING);

}
void loop()
{
    
    if (!stateauto)
    { 
      if(value) {
      Serial.println("Please enter the value to set the optimum temperature: ");
      display.clearDisplay();
      display.setCursor(0, 28);
      display.print("Please enter the value to set the optimum temperature: "); // Code for printing Temp AND Hum in OLED
        display.display();
      while (Serial.available()==0)
      {

      }
      String optval = Serial.readStringUntil('\n');
      optimvalue = optval.toInt();
      Serial.print("You entered: ");
      Serial.println(optimvalue);
      value = false;
      }
  
      else{
      float temp = dht22.readTemperature(); //Read the temperature
      float hum =  dht22.readHumidity();
        if(manual){
          //Serial.println("Inside Manual Operation");
           display.display();
           display.clearDisplay();
        }
        else{

        //Serial.println("INSIDEELSELOOP");
        int currentCount = getCount();
        Serial.print("Count: ");
        Serial.println(currentCount);

        display.clearDisplay();
        display.setCursor(0, 28);
        display.print("Count: "); // Code for printing Temp AND Hum in OLED
        display.println(currentCount);
        display.display();
        delay(2000);
        
        delay(1000);
        if (currentCount == 0)
        {
        String valueString = String(temp);
        String valueString1 = String(hum);
        ESPUI.print(tempinmain, valueString);
        ESPUI.print(huminmain, valueString1);
        Serial.print("Temperature in C: ");
        Serial.print(temp);
        Serial.print(" C");
        Serial.println();
        Serial.print(" Humidity: ");
        Serial.println(hum);
        Serial.println();
        delay(2000);
        
        display.clearDisplay();
        display.setCursor(0, 28);
        display.print("Temp in C: "); // Code for printing Temp AND Hum in OLED
        display.println(temp);
        display.display();
        display.print("Humidity: ");
        display.println(hum);
        display.display();
        delay(2000);
        analogWrite(ledPin, 0); // Set the LED brightness
        
  
        Controlservotemp(temp, optimvalue); 
        }
        if (currentCount > 0)
            { 
                int temperature = int(temp) + (currentCount * 0.2);
                int humidity = int(hum) + (currentCount * 0.2); // update the temperature and humidity according to the count value set.
                String valueString2 = String(temperature);
                String valueString3 = String(humidity);
                ESPUI.print(tempinmain, valueString2);
                ESPUI.print(huminmain, valueString3);
                display.print("Temp in C: "); // Code for printing Temp AND Hum in OLED
                display.println(temperature);
                display.display();
                display.print("Humidity: ");
                display.println(humidity);
                display.display();
                delay(2000);
                display.clearDisplay();
                display.setCursor(0, 28);

                Serial.print("Temperature in C: ");
                Serial.print(temperature);
                Serial.print(" C");
                Serial.println();
                Serial.print(" Humidity: ");
                Serial.println(humidity);
                Serial.println();
                delay(2000); //Measure temp and hum in Serial monitor
                
               if (currentCount == 1 || currentCount == 2)
                {
                  //Serial.println("inside count 1");
                  analogWrite(ledPin, 25); // Set the LED brightness
                  delay(1000); // Wait for 1 second
                }
                else if (currentCount == 3 || currentCount == 4)
                {
                    //Serial.println("inside count 3");
                    analogWrite(ledPin, 100); // Set the LED brightness
                    delay(1000); // Wait for 1 second
                }
                else if (currentCount == 5 || currentCount == 6)
                {
                    analogWrite(ledPin, 200); // Set the LED brightness
                    delay(1000); // Wait for 1 second
                }
                else if (currentCount >= 7)
                {
                    analogWrite(ledPin, 255); // Set the LED brightness
                    delay(1000); // Wait for 1 second
                }

                Controlservotemp(temperature, optimvalue);
            }
        
        }
      }
        }
    
    else
    {
        Serial.print("PushButton pressed");
        analogWrite(ledPin, 0);
        display.display();
        display.clearDisplay();
        serv1.write(90);
        serv2.write(90);
        delay(1000);
        value = true;
    }

}


int getCount() {
  //Serial.println("inside getCount");
  static int lastInsideCount = 0;  
  uint8_t success = 0;
  uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0}; 
  uint8_t uidLength = 0; 
  uint16_t timeout = 5000;

  Serial.println("Waiting for few seconds for the card to be read");
  display.clearDisplay();
  display.setCursor(0, 28);
  display.print("Waiting for few seconds for the card to be read "); // Code for printing Temp AND Hum in OLED
  display.display();
        
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, timeout);
  
  //Serial.println(success);  

  if (success) {
    Serial.println("Card read");
    display.clearDisplay();
    display.setCursor(0, 28);
    display.print("Card read "); // Code for printing Temp AND Hum in OLED
    display.display();
    int idx = findCard(uid, uidLength);

    if (idx == -1) {
      // New card, add to list
      addCard(uid, uidLength);
      isIn[cardIndex - 1] = true; 
    } else {
      // Existing card
      if (isIn[idx]) {
        isIn[idx] = false; 
      } else {
        isIn[idx] = true; 
      }
    }

    // Calculate the inside count
    int insideCount = 0;
    for (int i = 0; i < cardIndex; i++) {
      if (isIn[i]) {
        insideCount++;
      }
    }

    lastInsideCount = insideCount; // Update the last known inside count
    return lastInsideCount;
  } 

  Serial.println("Card not read");
  display.clearDisplay();
  display.setCursor(0, 28);
  display.print("Card not read"); // Code for printing Temp AND Hum in OLED
  display.display();
  delay(2000);
  return lastInsideCount;
}



int findCard(uint8_t *uid, uint8_t uidLength)
{
    for (int i = 0; i < cardIndex; i++)
    {
        if (cards[i].uidLength == uidLength && memcmp(cards[i].uid, uid, uidLength) == 0)
        {
            return i;
        }
    }
    return -1;
}

void addCard(uint8_t *uid, uint8_t uidLength)
{
    memcpy(cards[cardIndex].uid, uid, uidLength);
    cards[cardIndex].uidLength = uidLength;
    cardCount[cardIndex] = 1;
    cardIndex++;
}

void removeCard(int index)
{
    for (int i = index; i < cardIndex - 1; i++)
    {
        memcpy(cards[i].uid, cards[i + 1].uid, cards[i + 1].uidLength);
        cards[i].uidLength = cards[i + 1].uidLength;
        cardCount[i] = cardCount[i + 1];
        isIn[i] = isIn[i + 1];
    }
    cardIndex--;
}



void Controlservotemp(int temperature, int optimvalue)
{
    int pos;
    if (temperature == optimvalue){
      
      Serial.println("Temperature now in Optimum value ");
      display.clearDisplay();
      display.setCursor(0, 28);
      display.print("Temperature now in Optimum value ");
      display.display();
      serv1.write(90);
      serv2.write(0);
    }
    else
    {
    if ((temperature >= 45) && (temperature <= 125))
    {
        Serial.println("Temp range in C: 45 - 125 ");
        display.clearDisplay();
        display.setCursor(0, 28);
        display.print("Temp range in C: 45 - 125 ");
        display.display();
        
        for (pos = 0; pos <= 180; pos += 1)
        {
            serv1.write(pos);
            delay(25);
        }
        for (pos = 180; pos >= 0; pos -= 1)
        {
            serv1.write(pos);
            delay(25);
        }
    }
    else if ((temperature >= 28) && (temperature <= 44))
    {
        Serial.println("Temp range in C: 28 - 44 ");
        display.clearDisplay();
        display.setCursor(0, 28);
        display.print("Temp range in C: 28 - 44 ");
        display.display();
        
        for (pos = 0; pos <= 180; pos += 1)
        {
            serv1.write(pos);
            delay(50);
        }
        for (pos = 180; pos >= 0; pos -= 1)
        {
            serv1.write(pos);
            delay(50);
        }
    }
    else if ((temperature >= 24) && (temperature <= 27))
    {
        Serial.println("Temp range in C : 24-27 ");
        display.clearDisplay();
        display.setCursor(0, 28);
        display.print("Temp range in C: 24 - 27 ");
        display.display();

        
        for (pos = 0; pos <= 180; pos += 1)
        {
            serv1.write(pos);
            delay(50);
        }
        for (pos = 180; pos >= 0; pos -= 1)
        {
            serv1.write(pos);
            delay(50);
        }
    }
    else if ((temperature >= 10) && (temperature <= 23))
    {
        Serial.println("Temp range in C : 10-23 ");
        display.clearDisplay();
        display.setCursor(0, 28);
        display.print("Temp range in C: 10 - 23 ");
        display.display();
        display.clearDisplay();
        display.setCursor(0, 28);
        display.print("Heater Knob 1");
        display.display();
        serv2.write(45);
       
    }
    else if ((temperature >= -10) && (temperature <= 9))
    {
        Serial.println("Temp range in C : -10-9 ");
        display.clearDisplay();
        display.setCursor(0, 28);
        display.print("Temp range in C: -10 - 9 ");
        display.display();
         display.clearDisplay();
        display.setCursor(0, 28);
        display.print("Heater Knob 2");
        display.display();
        serv2.write(90);
    }
    else if ((temperature >= -40) && (temperature <= -11))
    {
        Serial.println("Temp range in C: -40 - -11 ");
        display.clearDisplay();
        display.setCursor(0, 28);
        display.print("Temp range in C: -40 - -11 ");
        display.display();
        display.clearDisplay();
        display.setCursor(0, 28);
        display.print(" Heater Knob 3 ");
        display.display();
        serv2.write(135);
    }
    }
}

//---------------------------Manual Operation-------------------------------------------------------//


void sliderled(Control *sender, int value) {
 
  
  if (manual==true)
  {
 
  ESPUI.updateControl(positionMax);
  value = sender->value.toInt();
  analogWrite(ledPin, value); 
  Serial.print("LED Intensity Value ");
  Serial.println(value);
  
  }
  
}

void SwitchChanged (Control* sender, int type)
{
  if (sender-> id == manualops && type == S_ACTIVE)
  {
    manual = true;
  
    Serial.println("Manual Operation On");
    ESPUI.updateControlValue(positionMax, "50");
    //ESPUI.updateControl(50);
    ESPUI.updateControlValue(positionMax, "0");
    ESPUI.updateControl(positionMax);
    analogWrite(ledPin,128);
}
  


  else if (sender ->id == manualops && type == S_INACTIVE)
  {
    manual=false;
    Serial.println("Manual Operation Off");
    ESPUI.updateControlValue(positionMax, "0");
    ESPUI.updateControl(positionMax);
    analogWrite(ledPin,128);
  }
}

void temperatureset(Control *sender, int type) {
  if (manual==true)
  {

      if (sender->type == Text) { // When the input field is updated
        String inputValue = sender->value;
        Serial.println(inputValue);
        int commaIndex = inputValue.indexOf(',');

        if (commaIndex != -1) {
            String value1 = inputValue.substring(0, commaIndex);
            String value2 = inputValue.substring(commaIndex + 1);

            optimal = value1.toInt();
            temper = value2.toInt();

            Serial.print("Input 1 Value: ");
            Serial.println(optimal);
            Serial.print("Input 2 Value: ");
            Serial.println(temper);
        } else {
            Serial.println("Invalid input format. Please use 'value1,value2'.");
        }
    }

    int pos;
    //Serial.print("Inside temp optim value");
    //Serial.print(optimvalue);
    if((optimal>= 20 && optimal <= 30) && (temper>= -40 && temper <=125))
    {

    
    if (temper == optimal){
      
      Serial.println("Temperature now in Optimum value ");
      serv1.write(90);
      serv2.write(0);
    }
    else
    {
    if ((temper >= 45) && (temper <= 125))
    {
        Serial.println("Temp range in C: 45 - 125 ");
        serv1.write(40);
        
    }
    else if ((temper >= 28) && (temper <= 44))
    {
        Serial.println("Temp range in C: 28 - 44 ");
        serv1.write(100);
       
    }
    else if ((temper >= 24) && (temper <= 27))
    {
        Serial.println("Temp range in C : 24-27 ");
        serv1.write(160);
    }
    else if ((temper >= 10) && (temper <= 23))
    {
        Serial.println("Temp range in C : 10-23 ");
        Serial.println("Heater Knob 1 ");
        serv2.write(45);
       
    }
    else if ((temper >= -10) && (temper <= 9))
    {
        Serial.println("Temp range in C : -10-9 ");
        Serial.println("Heater Knob 2");
        serv2.write(90);
    }
    else if ((temper >= -40) && (temper <= -11))
    {
        Serial.println("Temp range in C: -40 - -11 ");
        Serial.println("Heater Knob 3 ");
        serv2.write(135);
    }
   
    }
  
    }
  }
}

 

