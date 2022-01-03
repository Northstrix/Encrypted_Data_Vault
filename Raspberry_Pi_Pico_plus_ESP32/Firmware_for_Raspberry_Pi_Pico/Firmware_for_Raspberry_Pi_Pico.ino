/*
Encrypted Data Vault: Raspberry Pi Pico + ESP32 Version
Firmware for Raspberry Pi Pico
Distributed under the MIT License
© Copyright Maxim Bortnikov 2022
For more information please visit
https://github.com/Northstrix/Encrypted_Data_Vault
Required libraries:
https://github.com/zhouyangchao/AES
https://github.com/peterferrie/serpent
https://github.com/ulwanski/sha512
https://github.com/arduino-libraries/LiquidCrystal
*/
#include "sha512.h"
#include "aes.h"
#include "serpent.h"
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char *keys[]=
{"9a93d3e3e81ef9a9195fffffd41ae7a7a5b8262f33fe44b199559591a0e195c6"};// Serpent's key
int count;
byte tmp_st[8];
int m;
uint8_t back_key[32];
uint8_t back_s_key[32];
uint8_t key[32] = {
   0xb7,0x64,0x71,0x2b,
   0x81,0x4b,0xf1,0x7c,
   0xaf,0x3a,0x1f,0x63,
   0xe2,0x87,0x32,0x0e,
   0x56,0x0d,0xcf,0xdc,
   0xe9,0x88,0x4a,0x55,
   0xe1,0xec,0x11,0xb2,
   0x97,0xc3,0x78,0x94
};

uint8_t second_key[32] = {
   0xbf,0x91,0x36,0x23,
   0x53,0x6a,0xb5,0xdb,
   0x92,0x72,0xe8,0xad,
   0x3b,0xba,0x57,0x38,
   0x17,0x5d,0x20,0x7c,
   0x70,0x26,0xe7,0x65,
   0x41,0x10,0xc5,0xe5,
   0x82,0x69,0xce,0x76
};

void back_k(){
  for(int i = 0; i<32; i++){
    back_key[i] = key[i];
  }
}

void rest_k(){
  for(int i = 0; i<32; i++){
    key[i] = back_key[i];
  }
}

void back_s_k(){
  for(int i = 0; i<32; i++){
    back_s_key[i] = second_key[i];
  }
}

void rest_s_k(){
  for(int i = 0; i<32; i++){
    second_key[i] = back_s_key[i];
  }
}

void incr_key(){
  if(key[0] == 255){
    key[0] = 0;
    if(key[1] == 255){
      key[1] = 0;
      if(key[2] == 255){
        key[2] = 0;
        if(key[3] == 255){
          key[3] = 0;

  if(key[4] == 255){
    key[4] = 0;
    if(key[5] == 255){
      key[5] = 0;
      if(key[6] == 255){
        key[6] = 0;
        if(key[7] == 255){
          key[7] = 0;
          
  if(key[8] == 255){
    key[8] = 0;
    if(key[9] == 255){
      key[9] = 0;
      if(key[10] == 255){
        key[10] = 0;
        if(key[11] == 255){
          key[11] = 0;

  if(key[12] == 255){
    key[12] = 0;
    if(key[13] == 255){
      key[13] = 0;
      if(key[14] == 255){
        key[14] = 0;
        if(key[15] == 255){
          key[15] = 0;
        }
        else{
          key[15]++;
        }
        }
      else{
        key[14]++;
      }
    }
    else{
      key[13]++;
    }
  }
  else{
    key[12]++;
  }
          
        }
        else{
          key[11]++;
        }
        }
      else{
        key[10]++;
      }
    }
    else{
      key[9]++;
    }
  }
  else{
    key[8]++;
  }
          
        }
        else{
          key[7]++;
        }
        }
      else{
        key[6]++;
      }
    }
    else{
      key[5]++;
    }
  }
  else{
    key[4]++;
  }
          
        }
        else{
          key[3]++;
        }
        }
      else{
        key[2]++;
      }
    }
    else{
      key[1]++;
    }
  }
  else{
    key[0]++;
  }
}

void incr_second_key(){
  if(second_key[0] == 255){
    second_key[0] = 0;
    if(second_key[1] == 255){
      second_key[1] = 0;
      if(second_key[2] == 255){
        second_key[2] = 0;
        if(second_key[3] == 255){
          second_key[3] = 0;

  if(second_key[4] == 255){
    second_key[4] = 0;
    if(second_key[5] == 255){
      second_key[5] = 0;
      if(second_key[6] == 255){
        second_key[6] = 0;
        if(second_key[7] == 255){
          second_key[7] = 0;
          
  if(second_key[8] == 255){
    second_key[8] = 0;
    if(second_key[9] == 255){
      second_key[9] = 0;
      if(second_key[10] == 255){
        second_key[10] = 0;
        if(second_key[11] == 255){
          second_key[11] = 0;

  if(second_key[12] == 255){
    second_key[12] = 0;
    if(second_key[13] == 255){
      second_key[13] = 0;
      if(second_key[14] == 255){
        second_key[14] = 0;
        if(second_key[15] == 255){
          second_key[15] = 0;
        }
        else{
          second_key[15]++;
        }
        }
      else{
        second_key[14]++;
      }
    }
    else{
      second_key[13]++;
    }
  }
  else{
    second_key[12]++;
  }
          
        }
        else{
          second_key[11]++;
        }
        }
      else{
        second_key[10]++;
      }
    }
    else{
      second_key[9]++;
    }
  }
  else{
    second_key[8]++;
  }
          
        }
        else{
          second_key[7]++;
        }
        }
      else{
        second_key[6]++;
      }
    }
    else{
      second_key[5]++;
    }
  }
  else{
    second_key[4]++;
  }
          
        }
        else{
          second_key[3]++;
        }
        }
      else{
        second_key[2]++;
      }
    }
    else{
      second_key[1]++;
    }
  }
  else{
    second_key[0]++;
  }
}

int gen_r_num(){ // Suppose to generate a random integer from 0 to 255
  digitalWrite(27,HIGH);
  delayMicroseconds(400);
  digitalWrite(27,LOW);
  delayMicroseconds(3200);
  bool mltp[8];
  for(int i = 0; i<8; i++){
    mltp[i] = rand() % 2;
  }
  int rn = 0;
  if(digitalRead(16) == HIGH)
    rn += 128;
  if(digitalRead(17) == HIGH)
    rn += 64;
  if(digitalRead(18) == HIGH)
    rn += 32;
  if(digitalRead(19) == HIGH)
    rn += 16;
  if(digitalRead(20) == HIGH)
    rn += 8;
  if(digitalRead(21) == HIGH)
    rn += 4;
  if(digitalRead(22) == HIGH)
    rn += 2;
  if(digitalRead(26) == HIGH)
    rn += 1;
  return rn; 
}

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

size_t hex2bin (void *bin, char hex[]) {
  size_t len, i;
  int x;
  uint8_t *p=(uint8_t*)bin;
  
  len = strlen (hex);
  
  if ((len & 1) != 0) {
    return 0; 
  }
  
  for (i=0; i<len; i++) {
    if (isxdigit((int)hex[i]) == 0) {
      return 0; 
    }
  }
  
  for (i=0; i<len / 2; i++) {
    sscanf (&hex[i * 2], "%2x", &x);
    p[i] = (uint8_t)x;
  } 
  return len / 2;
}

void split_by_eight(char plntxt[], int k, int str_len, bool add_aes){
  char plt_data[] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 8; i++){
      if(i+k > str_len - 1)
      break;
      plt_data[i] = plntxt[i+k];
  }
  char t_encr[16];
  for(int i = 0; i<8; i++){
      t_encr[i] = plt_data[i];
  }
  for(int i = 8; i<16; i++){
      t_encr[i] = gen_r_num();
  }
  encr_AES(t_encr, add_aes);
}

void encr_AES(char t_enc[], bool add_aes){
  uint8_t text[16];
  for(int i = 0; i<16; i++){
    int c = int(t_enc[i]);
    text[i] = c;
  }
  uint8_t cipher_text[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint32_t key_bit[3] = {128, 192, 256};
  aes_context ctx;
  aes_set_key(&ctx, key, key_bit[m]);
  aes_encrypt_block(&ctx, cipher_text, text);
  /*
  for (int i = 0; i < 16; ++i) {
    Serial.printf("%02x", cipher_text[i]);
  }
  */
  char L_half[16];
  for(int i = 0; i<8; i++){
    L_half[i] = cipher_text[i];
  }
  char R_half[16];
  for(int i = 0; i<8; i++){
    R_half[i] = cipher_text[i+8];
  }
  for(int i = 8; i<16; i++){
    L_half[i] = gen_r_num();
    R_half[i] = gen_r_num();
  }
  serp_enc(L_half, add_aes);
  serp_enc(R_half, add_aes);
}

void serp_enc(char res[], bool add_aes){
  int tmp_s[16];
  for(int i = 0; i < 16; i++){
      tmp_s[i] = res[i];
  }
  /*
   for (int i = 0; i < 16; i++){
     Serial.print(res[i]);
  }
  Serial.println();
  */
  uint8_t ct1[32], pt1[32], key[64];
  int plen, clen, b, j;
  serpent_key skey;
  serpent_blk ct2;
  uint32_t *p;
  
  for (b=0; b<sizeof(keys)/sizeof(char*); b++) {
    hex2bin (key, keys[b]);
  
    // set key
    memset (&skey, 0, sizeof (skey));
    p=(uint32_t*)&skey.x[0][0];
    
    serpent_setkey (&skey, key);
    //Serial.printf ("\nkey=");
    /*
    for (j=0; j<sizeof(skey)/sizeof(serpent_subkey_t)*4; j++) {
      if ((j % 8)==0) putchar('\n');
      Serial.printf ("%08X ", p[j]);
    }
    */
    for(int i = 0; i < 16; i++){
        ct2.b[i] = tmp_s[i];
    }
  serpent_encrypt (ct2.b, &skey, SERPENT_ENCRYPT);
  if(add_aes == false){
    for (int i=0; i<16; i++) {
      if(ct2.b[i]<16)
        Serial.print("0");
      Serial.print(ct2.b[i],HEX);
    }
  }
  if(add_aes == true)
  encr_sec_AES(ct2.b);
  }
}

void encr_sec_AES(byte t_enc[]){
  uint8_t text[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for(int i = 0; i<16; i++){
    int c = int(t_enc[i]);
    text[i] = c;
  }
  uint8_t cipher_text[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint32_t second_key_bit[3] = {128, 192, 256};
  int i = 0;
  aes_context ctx;
  aes_set_key(&ctx, second_key, second_key_bit[m]);
  aes_encrypt_block(&ctx, cipher_text, text);
  for (i = 0; i < 16; ++i) {
    Serial.printf("%02x", cipher_text[i]);
  }
  incr_second_key();
}

void split_dec(char ct[], int ct_len, int p, bool ch, bool add_r){
  int br = false;
  byte res[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 32; i+=2){
    if(i+p > ct_len - 1){
      br = true;
      break;
    }
    if (i == 0){
    if(ct[i+p] != 0 && ct[i+p+1] != 0)
    res[i] = 16*getNum(ct[i+p])+getNum(ct[i+p+1]);
    if(ct[i+p] != 0 && ct[i+p+1] == 0)
    res[i] = 16*getNum(ct[i+p]);
    if(ct[i+p] == 0 && ct[i+p+1] != 0)
    res[i] = getNum(ct[i+p+1]);
    if(ct[i+p] == 0 && ct[i+p+1] == 0)
    res[i] = 0;
    }
    else{
    if(ct[i+p] != 0 && ct[i+p+1] != 0)
    res[i/2] = 16*getNum(ct[i+p])+getNum(ct[i+p+1]);
    if(ct[i+p] != 0 && ct[i+p+1] == 0)
    res[i/2] = 16*getNum(ct[i+p]);
    if(ct[i+p] == 0 && ct[i+p+1] != 0)
    res[i/2] = getNum(ct[i+p+1]);
    if(ct[i+p] == 0 && ct[i+p+1] == 0)
    res[i/2] = 0;
    }
  }
    if(br == false){
      if(add_r == true){
      uint8_t ret_text[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      uint8_t cipher_text[16] = {0};
      for(int i = 0; i<16; i++){
        int c = int(res[i]);
        cipher_text[i] = c;
      }
      uint32_t second_key_bit[3] = {128, 192, 256};
      int i = 0;
      aes_context ctx;
      aes_set_key(&ctx, second_key, second_key_bit[m]);
      aes_decrypt_block(&ctx, ret_text, cipher_text);
      for (i = 0; i < 16; ++i) {
        res[i] = (char)ret_text[i];
      }
      }
      incr_second_key();
      uint8_t ct1[32], pt1[32], key[64];
      int plen, clen, i, j;
      serpent_key skey;
      serpent_blk ct2;
      uint32_t *p;
  
  for (i=0; i<sizeof(keys)/sizeof(char*); i++) {
    hex2bin (key, keys[i]);
  
    // set key
    memset (&skey, 0, sizeof (skey));
    p=(uint32_t*)&skey.x[0][0];
    
    serpent_setkey (&skey, key);
    //Serial.printf ("\nkey=");

    for (j=0; j<sizeof(skey)/sizeof(serpent_subkey_t)*4; j++) {
      if ((j % 8)==0) putchar('\n');
      //Serial.printf ("%08X ", p[j]);
    }

    for(int i = 0; i <16; i++)
      ct2.b[i] = res[i];
    /*
    Serial.printf ("\n\n");
    for(int i = 0; i<16; i++){
    Serial.printf("%x", ct2.b[i]);
    Serial.printf(" ");
    */
    }
    //Serial.printf("\n");
    serpent_encrypt (ct2.b, &skey, SERPENT_DECRYPT);
    if (ch == false){
    for (int i=0; i<8; i++) {
      tmp_st[i] = char(ct2.b[i]);
    }
    }
    if (ch == true){
      decr_AES(ct2.b);
    }
  }
}

void decr_AES(byte sh[]){
  uint8_t ret_text[16];
  for(int i = 0; i<8; i++){
    ret_text[i] = tmp_st[i];
  }
  for(int i = 0; i<8; i++){
    ret_text[i+8] = sh[i];
  }
  uint8_t cipher_text[16] = {0};
  for(int i = 0; i<16; i++){
    int c = int(ret_text[i]);
    cipher_text[i] = c;
  }
  uint32_t key_bit[3] = {128, 192, 256};
  int i = 0;
  aes_context ctx;
  aes_set_key(&ctx, key, key_bit[m]);
  aes_decrypt_block(&ctx, ret_text, cipher_text);
  for (i = 0; i < 8; ++i) {
     Serial.print(char(ret_text[i]));
  }
}

void setup() {
  Serial.begin(115200);
  m = 2;
  pinMode(16,INPUT);
  pinMode(17,INPUT);
  pinMode(18,INPUT);
  pinMode(19,INPUT);
  pinMode(20,INPUT);
  pinMode(21,INPUT);
  pinMode(22,INPUT);
  pinMode(26,INPUT);
  pinMode(27,OUTPUT);
  lcd.begin(16,2);
  lcd.clear();
}

void loop() {
    Serial.println();
    back_k();
    back_s_k();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("What do you want");
    lcd.setCursor(0,1);
    lcd.print("to do?");
    Serial.println("What do you want to do?");
    Serial.println("1.Encrypt data with AES + Serpent");
    Serial.println("2.Decrypt data with AES + Serpent");
    Serial.println("3.Set AES to 128-bit mode");
    Serial.println("4.Set AES to 192-bit mode");
    Serial.println("5.Set AES to 256-bit mode");
    Serial.println("6.Hash data with SHA-512");
    Serial.println("7.Encrypt data in counter mode with AES + Serpent");
    Serial.println("8.Decrypt data in counter mode with AES + Serpent");
    Serial.println("9.Increment key (IV) n times");
    Serial.println("10.Encrypt data in counter mode with AES + Serpent + AES");
    Serial.println("11.Decrypt data in counter mode with AES + Serpent + AES");
    Serial.println("12.Test RNG");
    Serial.println("13.Derive part of the key from the string");
    Serial.println("14.Generate random ASCII strings");
    while (!Serial.available()) {}
    int x = Serial.parseInt();
    if(x == 1){
      Serial.println("Enter plaintext:");
      String inp_str;
      while (!Serial.available()) {}
      inp_str = Serial.readString();
      int str_len = inp_str.length() + 1;
      char char_array[str_len];
      inp_str.toCharArray(char_array, str_len);
      /*
      //Hash
      std::string str = "";
      if(str_len > 1){
        for(int i = 0; i<str_len-1; i++){
          str += char_array[i];
        }
      }
      String hstring = sha512( str ).c_str();
      Serial.println(hstring);
      int hstr_len = hstring.length() + 1;
      char hash_array[hstr_len];
      hstring.toCharArray(hash_array, hstr_len);
      Serial.println("Hash:");
      int c = 0;
      while(c < 128){
        split_by_eight(hash_array, c, 129);
        c+=8;
      }
      */
      Serial.println("Ciphertext:");
      int p = 0;
      float lngth = str_len;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Encrypting data");
      lcd.setCursor(0,1);
      lcd.print("Progress:");
      while(str_len > p+1){
        split_by_eight(char_array, p, str_len, false);
        p+=8;
        lcd.setCursor(9,1);
        lcd.print("       ");
        lcd.setCursor(9,1);
        float pq = p;
        float pr = pq/lngth;
        pr *= 100;
        String prtd = String(pr) + "%";
        lcd.print(prtd);
      }
    }
    if(x == 2 || x == 8){
      String ct;
      Serial.println("Enter ciphertext");
      while (!Serial.available()) {}
      ct = Serial.readString();
      int ct_len = ct.length() + 1;
      char ct_array[ct_len];
      ct.toCharArray(ct_array, ct_len);
      int ext = 0;
      count = 0;
      bool ch = false;
      Serial.println("Plaintext");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Decrypting data");
      lcd.setCursor(0,1);
      lcd.print("Progress:");
      Serial.println("Plaintext");
      float clngth = ct_len;
      while(ct_len > ext){
      if(count%2 == 1 && count !=0)
        ch = true;
      else{
        ch = false;
        if(x == 8)
          incr_key();
      }
      split_dec(ct_array, ct_len, 0+ext, ch, false);
      ext+=32;
      count++;
      lcd.setCursor(9,1);
      lcd.print("       ");
      lcd.setCursor(9,1);
      float extq = ext;
      float pr = extq/clngth;
      pr *= 100;
      String prtd = String(pr) + "%";
      lcd.print(prtd);
      }
      rest_k();
    }
    if(x == 3)
      m = 0;
    if(x == 4)
      m = 1;
    if(x == 5)
      m = 2;
    if(x == 6){
      Serial.print("Enter data to hash:");
      String input;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter data to");
      lcd.setCursor(0,1);
      lcd.print("hash with SHA512");
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
      Serial.println("Hash:");
      Serial.println(h);
    }
    if(x == 7){
      Serial.println("Enter plaintext:");
      String inp_str;
      while (!Serial.available()) {}
      inp_str = Serial.readString();
      int str_len = inp_str.length() + 1;
      char char_array[str_len];
      inp_str.toCharArray(char_array, str_len);
      Serial.println("Ciphertext:");
      int p = 0;
      float lngth = str_len;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Encrypting data");
      lcd.setCursor(0,1);
      lcd.print("Progress:");
      while(str_len > p+1){
        incr_key();
        split_by_eight(char_array, p, str_len, false);
        p+=8;
        lcd.setCursor(9,1);
        lcd.print("       ");
        lcd.setCursor(9,1);
        float pq = p;
        float pr = pq/lngth;
        pr *= 100;
        String prtd = String(pr) + "%";
        lcd.print(prtd);
      }
      rest_k();
    }
    if(x == 9){
      Serial.println("How many times do you want to increment the key?");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter number of");
      lcd.setCursor(0,1);
      lcd.print("incrementations");
      while (!Serial.available()) {}
      int itr = Serial.parseInt();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Incrementing key");
      for(int i = 0; i < itr; i++){
        incr_key();
      }
    }
    if(x == 10){
      Serial.println("Enter plaintext:");
      String inp_str;
      while (!Serial.available()) {}
      inp_str = Serial.readString();
      int str_len = inp_str.length() + 1;
      char char_array[str_len];
      inp_str.toCharArray(char_array, str_len);
      Serial.println("Ciphertext:");
      int p = 0;
      float lngth = str_len;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Encrypting data");
      lcd.setCursor(0,1);
      lcd.print("Progress:");
      while(str_len > p+1){
        incr_key();
        split_by_eight(char_array, p, str_len, true);
        p+=8;
        lcd.setCursor(9,1);
        lcd.print("       ");
        lcd.setCursor(9,1);
        float pq = p;
        float pr = pq/lngth;
        pr *= 100;
        String prtd = String(pr) + "%";
        lcd.print(prtd);
      }
      rest_k();
      rest_s_k();
    }
    if(x == 11){
      String ct;
      Serial.println("Enter ciphertext");
      while (!Serial.available()) {}
      ct = Serial.readString();
      int ct_len = ct.length() + 1;
      char ct_array[ct_len];
      ct.toCharArray(ct_array, ct_len);
      int ext = 0;
      count = 0;
      bool ch = false;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Decrypting data");
      lcd.setCursor(0,1);
      lcd.print("Progress:");
      Serial.println("Plaintext");
      float clngth = ct_len;
      while(ct_len > ext){
      if(count%2 == 1 && count !=0)
        ch = true;
      else{
        ch = false;
        incr_key();
      }
      split_dec(ct_array, ct_len, 0+ext, ch, true);
      ext+=32;
      count++;
      lcd.setCursor(9,1);
      lcd.print("       ");
      lcd.setCursor(9,1);
      float extq = ext;
      float pr = extq/clngth;
      pr *= 100;
      String prtd = String(pr) + "%";
      lcd.print(prtd);
      }
      rest_k();
      rest_s_k();
    }
    if(x == 12){
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Testing RNG");
     for(int cnt = 0; cnt < 16; cnt++){
      for (int i = 0; i < 32; ++i) {
        Serial.printf("%02x", gen_r_num());
      }
      lcd.setCursor(cnt,1);
      lcd.print("*");
      Serial.println();
     }
    }
    if(x == 13){
      Serial.println("Enter the string to derive a part of the key from:");
      String input;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter string to");
      lcd.setCursor(0,1);
      lcd.print("derive key from");
      while (!Serial.available()) {}
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Deriving key");
      input = Serial.readString();
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
      int h_len = h.length() + 1;
      char h_array[h_len];
      h.toCharArray(h_array, h_len);
      byte res[16] = {0};
      for (int i = 0; i < 32; i+=2){
      if (i == 0){
      if(h_array[i] != 0 && h_array[i+1] != 0)
      res[i] = 16*getNum(h_array[i])+getNum(h_array[i+1]);
      if(h_array[i] != 0 && h_array[i+1] == 0)
      res[i] = 16*getNum(h_array[i]);
      if(h_array[i] == 0 && h_array[i+1] != 0)
      res[i] = getNum(h_array[i+1]);
      if(h_array[i] == 0 && h_array[i+1] == 0)
      res[i] = 0;
      }
      else{
      if(h_array[i] != 0 && h_array[i+1] != 0)
      res[i/2] = 16*getNum(h_array[i])+getNum(h_array[i+1]);
      if(h_array[i] != 0 && h_array[i+1] == 0)
      res[i/2] = 16*getNum(h_array[i]);
      if(h_array[i] == 0 && h_array[i+1] != 0)
      res[i/2] = getNum(h_array[i+1]);
      if(h_array[i] == 0 && h_array[i+1] == 0)
      res[i/2] = 0;
      }
     }
     uint8_t ct1[32], pt1[32], key[64];
     int plen, clen, i, j;
     serpent_key skey;
     serpent_blk ct2;
     uint32_t *p;
     for (i=0; i<sizeof(keys)/sizeof(char*); i++) {
      hex2bin (key, keys[i]);
      memset (&skey, 0, sizeof (skey));
      p=(uint32_t*)&skey.x[0][0];
      serpent_setkey (&skey, key);
      for (j=0; j<sizeof(skey)/sizeof(serpent_subkey_t)*4; j++) {
        if ((j % 8)==0) putchar('\n');
      }
      for(int i = 0; i <16; i++)
        ct2.b[i] = res[i];
      }
      for(int i = 0; i<576; i++){
        serpent_encrypt (ct2.b, &skey, SERPENT_DECRYPT);
        lcd.setCursor(i/36,1);
        lcd.print("*");
      }
      key[0] = ct2.b[0];
      key[1] = ct2.b[1];
      key[3] = ct2.b[2];
      key[4] = ct2.b[3];
      key[6] = ct2.b[4];
      key[7] = ct2.b[5];
      key[8] = ct2.b[12];
      second_key[0] = ct2.b[6];
      second_key[1] = ct2.b[7];
      second_key[3] = ct2.b[8];
      second_key[4] = ct2.b[9];
      second_key[6] = ct2.b[10];
      second_key[7] = ct2.b[11];
      second_key[8] = ct2.b[13];
      Serial.print("Key derived successfully. Verification number: ");
      Serial.println(ct2.b[14]);
    }
    if(x == 14){
     Serial.println("How many strings do you want?");
     while (!Serial.available()) {}
     int nmbr = Serial.parseInt();
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Random ASCII str");
     lcd.setCursor(0,1);
     lcd.print("to do?");
     int ps = 0;
     Serial.println("Random ASCII strings:");
     for(int sn = 0; sn < nmbr; sn++){
     int pt = 80 + gen_r_num();
      for(int i = 0; i < pt; i++){
        int r = gen_r_num();
        if(r>32 && r<127){
          Serial.print(char(r));
          if(ps<16){
            lcd.setCursor(ps,1);
            lcd.print(char(r));
            ps++;
          }
        }
      }
      if(ps>15)
        ps = 0;
     Serial.println();
     }
    }
}
