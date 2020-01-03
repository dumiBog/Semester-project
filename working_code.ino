#include <dht.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define lightSensor A0
#define LM35pin A1
#define Buzzer P8
#define Rain_sensor A3
#define dht_apin A2

int average =  PD5;
int minimum =PD6;
int maximum =PD7;
unsigned long i=0;
float s=0,avg=0,v[100]={0},minimumval=100,maximumval=-100;
int k=0;
int j;

dht DHT;
int x=1;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);

void setup() {
  // put your setup code here, to run once:
   lcd.begin(20,4); 
   lcd.setBacklightPin(3,POSITIVE);
   lcd.setBacklight(HIGH);
   pinMode(8,OUTPUT);
   pinMode(Rain_sensor,INPUT);
   pinMode(average,INPUT_PULLUP);
   pinMode(minimum,INPUT_PULLUP);
   pinMode(maximum,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
          // Temp


              int averagestat = digitalRead(average);
              int minimumstat = digitalRead(minimum);
              int maximumstat = digitalRead(maximum);
                
              float tempC=((analogRead(A1)*(5.0/1024))-0.957)/0.01;
             
              lcd.setCursor(0,0);
              lcd.print("Temp C:");
              lcd.setCursor(7,0);
              lcd.print(tempC);
               delay(150);
              if(j<=100){
                v[j]= tempC;
                if(v[j]){
                  s+=v[j];
                  k++;
                }
                if(v[j]<minimumval) minimumval=v[j];
                if(v[j]>maximumval) maximumval=v[j];
                j++;
              }
              avg= float(s/k); 
              if(averagestat==HIGH){
                lcd.setCursor(13,0);
                lcd.print("Average:");
                lcd.setCursor(13,1);
                lcd.print(avg);
              } 




               else if(minimumstat==HIGH){
                lcd.setCursor(13,0);
                lcd.print("Minimum:");
                lcd.setCursor(13,1);
                lcd.print(minimumval);
    }





              else if(maximumstat==HIGH){
                lcd.setCursor(13,0);
                lcd.print("Maximum:");
                lcd.setCursor(13,1);
                lcd.print(maximumval);

              }
                
   else {
    
                lcd.setCursor(13,0);
                lcd.print("       ");
                lcd.setCursor(13,1);
                lcd.print("     ");

   }
            /* if(minimumstat==HIGH){
                lcd.setCursor(13,0);
                lcd.print("Minimum:");
                lcd.setCursor(13,1);
                lcd.print(minimumval);
                
              } 
   else {
    
                lcd.setCursor(13,0);
                lcd.print("       ");
                lcd.setCursor(13,1);
                lcd.print("     ");
    
    }
            if(maximumstat==HIGH){
                lcd.setCursor(13,0);
                lcd.print("Maximum:");
                lcd.setCursor(13,1);
                lcd.print(maximumval);
                
              } 
   else {
    
                lcd.setCursor(13,0);
                lcd.print("       ");
                lcd.setCursor(13,1);
                lcd.print("     ");
    
    }
        */   // Light
                        int lightlevel = analogRead(A0);
                        lcd.setCursor(0,3);
                        lcd.print("Light level:");
                        lcd.setCursor(12,3);
                        lcd.print(lightlevel);
          //Rain


            int Rain_level=analogRead(A3);
                        
                          
           if (Rain_level<600){
           
                        lcd.setCursor(0,1);
                        lcd.print("Not raining");
                        //lcd.setCursor(12,1);
                        //lcd.print(Rain_level);
                        x=1;
                        
           }
           else{
                          lcd.setCursor(0,1);
                          lcd.print("Raining    ");
                          if(x==1){
                            for(int i=0;i<=1;i++)
                            { 
                                digitalWrite(8,HIGH);
                                delay(150);
                                digitalWrite(8,LOW); 
                                
                                  
                            }
                           x=2;
                          }else ;
           }
        
                   if(lightlevel<600){
                          lcd.setCursor(15,3);
                          lcd.print("Night");
                          }
                   else{
    
                          lcd.setCursor(15,3);
                          lcd.print("Day  ");

                       }

                     
                        
                       
        



                  lcd.setCursor(0,2);
                  DHT.read11(dht_apin);    
                  lcd.print("Humidity=");
                  lcd.print(DHT.humidity);
                  lcd.print("%");
                  delay(500);

           



}
