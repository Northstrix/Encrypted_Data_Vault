/*
Encrypted Data Vault: Raspberry Pi Pico + ESP32 Version
Firmware for the ESP32
Distributed under the MIT License
© Copyright Maxim Bortnikov 2022
For more information please visit
https://github.com/Northstrix/Encrypted_Data_Vault
*/
#include <sys/random.h>
#include "mbedtls/md.h"
unsigned long st;
unsigned long et;
int getNum(char ch)
{
    int num=0;
    if(ch>='0' && ch<='9')
    {
        num=ch-0x30;
    }
    else
    {
        switch(ch)
        {
            case 'A': case 'a': num=10; break;
            case 'B': case 'b': num=11; break;
            case 'C': case 'c': num=12; break;
            case 'D': case 'd': num=13; break;
            case 'E': case 'e': num=14; break;
            case 'F': case 'f': num=15; break;
            default: num=0;
        }
    }
    return num;
}

char getChar(int num){
  char ch;
    if(num>=0 && num<=9)
    {
        ch = char(num+48);
    }
    else
    {
        switch(num)
        {
            case 10: ch='a'; break;
            case 11: ch='b'; break;
            case 12: ch='c'; break;
            case 13: ch='d'; break;
            case 14: ch='e'; break;
            case 15: ch='f'; break;
        }
    }
    return ch;
}

void Gen_r_n(){
  char rnd_nmbr[128];
  char key[128];
  //String h = "";
  int res = 0;
  for(int i = 0; i<128; i++){
    int c = esp_random()%4;
    c += esp_random()%4;
    c += esp_random()%4;
    c += esp_random()%4;
    c += esp_random()%4;    
    int d = esp_random()%4;
    d += esp_random()%4;
    d += esp_random()%4;
    d += esp_random()%4;
    d += esp_random()%4;
    int z = esp_random()%4;
    z += esp_random()%4;
    z += esp_random()%4;
    z += esp_random()%4;
    z += esp_random()%4;
    int x = esp_random()%4;
    x += esp_random()%4;
    x += esp_random()%4;
    x += esp_random()%4;
    x += esp_random()%4;
    //Serial.println(z);
    //Serial.println(x);
    //Serial.println(c);
    //Serial.println(d);
    if(c != 0 && d != 0)
    res = (16*c)+d;
    if(c != 0 && d == 0)
    res = 16*c;
    if(c == 0 && d != 0)
    res = d;
    if(c == 0 && d == 0)
    res = 0;
    rnd_nmbr[i] = char(res);
    //Serial.println(res);
    if(z != 0 && x != 0)
    res = (16*z)+x;
    if(z != 0 && x == 0)
    res = 16*z;
    if(z == 0 && x != 0)
    res = x;
    if(z == 0 && x == 0)
    res = 0;
    key[i] = char(res);
    //Serial.println(res);
    //h += getChar(c);
    //h += getChar(d);
  }
  byte hmacResult[32];
  mbedtls_md_context_t ctx;
  mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
 
  const size_t payloadLength = strlen(rnd_nmbr);
  const size_t keyLength = strlen(key);            
 
  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
  mbedtls_md_hmac_starts(&ctx, (const unsigned char *) key, keyLength);
  mbedtls_md_hmac_update(&ctx, (const unsigned char *) rnd_nmbr, payloadLength);
  mbedtls_md_hmac_finish(&ctx, hmacResult);
  mbedtls_md_free(&ctx);
  /*
  for(int i=0; i<32; i++){
  Serial.print(hmacResult[i] + " ");
  }
  */
  //Serial.print("Hash: ");
  String rand_h = "";
  int y = esp_random()%25;
    if(hmacResult[y] > 127){
      digitalWrite(23,HIGH);
    }
    else
      digitalWrite(23,LOW);

    if(hmacResult[y+1] > 127){
      digitalWrite(22,HIGH);
    }
    else
      digitalWrite(22,LOW);

    if(hmacResult[y+2] > 127){
      digitalWrite(21,HIGH);
    }
    else
      digitalWrite(21,LOW);

    if(hmacResult[y+3] > 127){
      digitalWrite(19,HIGH);
    }
    else
      digitalWrite(19,LOW);

    if(hmacResult[y+4] > 127){
      digitalWrite(18,HIGH);
    }
    else
      digitalWrite(18,LOW);

    if(hmacResult[y+5] > 127){
      digitalWrite(5,HIGH);
    }
    else
      digitalWrite(5,LOW);

    if(hmacResult[y+6] > 127){
      digitalWrite(4,HIGH);
    }
    else
      digitalWrite(4,LOW);

    if(hmacResult[y+7] > 127){
      digitalWrite(2,HIGH);
    }
    else
      digitalWrite(2,LOW);
}

void setup() {
  //Serial.begin(115200);
  pinMode(23,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(21,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(12,INPUT);
}

void loop() {
  if(digitalRead(12) == HIGH)
    Gen_r_n();

}
