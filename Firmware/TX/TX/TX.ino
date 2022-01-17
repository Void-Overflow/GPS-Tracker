//Transceiver ID = 0
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial gps_serial(4, 3); //RX, TX
TinyGPSPlus gps;

namespace GPS
{
    int fail_counter = 0;

    static void smartDelay(unsigned long ms)
    {
        unsigned long start = millis();
        do
        {
            while (gps_serial.available())
                gps.encode(gps_serial.read());

        } while (millis() - start < ms);
    }

    static String printFloat(float val, bool valid, int prec, String request)
    {
        if (!valid)
        {
            if (request == "Lat")
                fail_counter++;

            if (fail_counter < 16)
                return request + "Fail_0" + String(fail_counter, HEX);
            else if (fail_counter < 256)
                return request + "Fail_" + String(fail_counter, HEX);
            else if (fail_counter < 4096)
                return request + "Fail" + String(fail_counter, HEX);
            else
            {
                fail_counter = 0;
                return request + "Fail_0" + String(fail_counter, HEX);
            }
        }
        else
        {
            String result = String(val, prec);
            return result;
        }
    }
}

int previousMillis = 0;
int interval = 500;

String last_longitude = "";
String last_latitude = "";

int counter = 0;

void setup()
{
    Serial.begin(9600);
    gps_serial.begin(9600);
}

void loop()
{
    int currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
        String longitude = GPS::printFloat(gps.location.lat(), gps.location.isValid(), 6, "Lat");
        String latitude = GPS::printFloat(gps.location.lng(), gps.location.isValid(), 6, "Lon");

        if (longitude == last_longitude && latitude == last_latitude)
            counter++;
        else if (counter > 0)
        {
            GPS::fail_counter = 0;
            counter = 0;
        }

        if (counter >= 10)
        {
            longitude = GPS::printFloat(gps.location.lat(), false, 6, "Lat");
            latitude = GPS::printFloat(gps.location.lng(), false, 6, "Lon");
        }
        else
        {
            last_longitude = longitude;
            last_latitude = latitude;
        }

        Serial.println("AT+SEND=1,28," + longitude + "," + latitude);

        previousMillis = currentMillis;
    }

    GPS::smartDelay(200);
}
