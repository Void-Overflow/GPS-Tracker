//Transceiver ID = 1

int previousMillis = 0;
int interval = 500;

String incomingString;

int counter = 0;
;
bool COM_Status = false;

String last_longitude = "";
String last_latitude = "";

void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);
}

void loop()
{
    if (Serial1.available())
    {
        incomingString = Serial1.readString();
    }

    int currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
        String received_longitude = incomingString.substring(10, 19).c_str();
        String received_latitude = incomingString.substring(20, 30).c_str();

        if (received_longitude == last_longitude && received_latitude == last_latitude)
        {
            counter++;
            if (counter >= 14)
                Serial.println("COM_FAIL");
            else
                Serial.println(received_longitude + " " + received_latitude);
        }
        else
        {
            counter = 0;
            Serial.println(received_longitude + " " + received_latitude);
        }

        last_longitude = received_longitude;
        last_latitude = received_latitude;

        previousMillis = currentMillis;
    }

    if (Serial.available())
    {
        String Serial_incomingString = Serial.readString();

        if (Serial_incomingString.indexOf("hello") >= 0)
            Serial.println("world");
    }

    delay(200);
}
