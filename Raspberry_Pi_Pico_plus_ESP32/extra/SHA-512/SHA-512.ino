/*
Encrypted Data Vault: Raspberry Pi Pico + ESP32 Version
Distributed under the MIT License
© Copyright Maxim Bortnikov 2022
For more information please visit
https://github.com/Northstrix/Encrypted_Data_Vault
Required libraries:
https://github.com/ulwanski/sha512
*/
#include "sha512.h"

void setup(){
  Serial.begin(115200);
}
void loop(){
  Serial.print("Enter the string to hash:");
  String input;
  while (!Serial.available()) {}
  input = Serial.readString();
  Serial.println(input);
  int str_len = input.length() + 1;
  char input_arr[str_len];
  input.toCharArray(input_arr, str_len);
  std::string str = "";
  if(str_len > 1){
    for(int i = 0; i<str_len-1; i++){
      str += input_arr[i];
    }
  }
  String h = sha512( str ).c_str();
  Serial.println(h);
  //Serial.printf("sha512sum: %s\n\n",  sha512( str ).c_str());
}
