#include <Wire.h>
#include <AHT10.h>
#include "SPI.h"
#include "SD.h"
const int chipSelect = 53;
AHT10Class AHT10;
Sd2Card card;
void setup() {
Serial.begin(9600);
Wire.begin();
SD.begin(chipSelect); // Инициализируем библиотеку для работы с SD-картой, указав пин подключения вывода CS
//Работает ли карта
Serial.println("Initialization...");
if (!card.init(SPI_HALF_SPEED, chipSelect)) {
Serial.println("Initialization failed.");
return;
} else {
Serial.println("Card OK");
delay(1000);
}
if (AHT10.begin(eAHT10Address_Low))
Serial.println("Init AHT10 Success!");
else
Serial.println("Init AHT10 Failed!");
File myFile = SD.open("file.txt", FILE_WRITE);
myFile.println(String("") + "Humidity(%RH):\t\t" +
AHT10.GetHumidity() + "%");
myFile.println(String("") + "Temperature(℃):\t"
+ AHT10.GetTemperature() + "℃");
myFile.println(String("") + "Dewpoint(℃):\t\t"
+ AHT10.GetDewPoint() + "℃");
delay(1000);
myFile.close();
Serial.println("done");
Serial.println();
Serial.println("Start reading");
Serial.println();
File file = SD.open("file.txt", FILE_READ); // Открываем файл для чтения,
while(file.available())
Serial.write(file.read()); // выводим содержимое файла в последовательный порт,
file.close();
}
void loop() {
}
