#include<iostream>
#include<unistd.h>
#include<iomanip>
#include "GPIO.hpp"
#include "Adafruit_GFX.h"
#include "BBB_OLED.h"
#include "BBB_OLED_lib.h"
//#include "bcm2835.h"
//#include "GPIO.hpp"
using namespace std;

#define USING_DHT11      false   // The DHT11 uses only 8 bits
#define DHT_GPIO         RPI_GPIO_P1_15
#define LH_THRESHOLD     22      // Low=~14, High=~38 - pick avg.

int humid=0, temp=0;

void waitDelay(int delay=100){
   for (int i=0; i<delay; i++) {}        // blocking delay
}


int main(){

   string overlay;
   export_overlay(overlay="BvL-GPIO");

   BBB_OLED display(1,ADAFRUIT_I2C_ADDRESS); // bus /dev/ic-1 P9_20 and P9_19  I2c address 3d hex
   if(!display.init(OLED_I2C_RESET)){
      perror("Failed to set up the display\n");
      return -1;
   }

   printf("Setting up the I2C Display output!\n");
   display.begin();
   display.clearDisplay();

   display.setTextSize(1);
   display.setTextColor(WHITE);
   display.setCursor(2,5);
   display.print("Exploring Beaglebone");
    time_t t = time(0);
    struct tm *now = localtime(&t);
   display.setCursor(35,18);
   display.printf("%2d/%2d/%2d", now->tm_mday, now->tm_mon+1, (now->tm_year+1900));
   display.setCursor(21,37);
   display.setTextSize(3);
   display.printf("%02d:%02d", now->tm_hour, now->tm_min );
   display.drawRect(16, 32, 96, 32, WHITE);
   display.display();
   display.close();
   printf("End of the I2C Display program\n");
   return 0;
}


