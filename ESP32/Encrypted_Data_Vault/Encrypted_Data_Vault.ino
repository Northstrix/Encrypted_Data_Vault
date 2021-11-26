/*
Encrypted Data Vault: ESP32 Version
Distributed under the MIT License
© Copyright Maxim Bortnikov 2021
For more information please visit
https://github.com/Northstrix/Encrypted_Data_Vault
Required library:
https://github.com/peterferrie/serpent
*/
#include "serpent.h"
#include <sys/random.h>
#include "mbedtls/md.h"
#include "mbedtls/aes.h"
#include "SPIFFS.h"
char *keys[]=
{"761087A94F7C7FBC955AC330F61A4797A2FE095D6114C7168F7C75954C5281BE"};// Serpent's key
String dec_stuff;
int count;
char tmp_st[8];
char * AES_key = "e=Alvy+-$kI>#57?";
void read_f(String name){
  File file = SPIFFS.open(name);
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  Serial.println("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}

void write_f(String name, String cont){
  File file = SPIFFS.open(name, FILE_WRITE);
 
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }
  if (file.print(cont)) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }
 
  file.close();
}
void encrypt(char * plainText, char * AES_key, unsigned char * outputBuffer){
 
  mbedtls_aes_context aes;
 
  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_enc( &aes, (const unsigned char*) AES_key, strlen(AES_key) * 8 );
  mbedtls_aes_crypt_ecb( &aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)plainText, outputBuffer);
  mbedtls_aes_free( &aes );
}
 
void decrypt(unsigned char * chipherText, char * AES_key, unsigned char * outputBuffer){
 
  mbedtls_aes_context aes;
 
  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_dec( &aes, (const unsigned char*) AES_key, strlen(AES_key) * 8 );
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)chipherText, outputBuffer);
  mbedtls_aes_free( &aes );
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

void split_by_eight(char plntxt[], int k, int str_len){
  char plt_data[] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 8; i++){
      if(i+k > str_len - 1)
      break;
      plt_data[i] = plntxt[i+k];
  }
  int d = plt_data[0];
  int f = plt_data[1];
  int g = plt_data[2];
  int h = plt_data[3];
  int r = plt_data[4];
  int t = plt_data[5];
  int y = plt_data[6];
  int u = plt_data[7];
  /*
   for (int i = 0; i < 8; i++){
     Serial.print(res[i]);
  }
  Serial.println();
  */
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
  char to_AES_enc[16];
  int p = esp_random()%25;
  //Serial.println(y);
  to_AES_enc[0] = d;
  to_AES_enc[1] = f;
  to_AES_enc[2] = g;
  to_AES_enc[3] = h;
  to_AES_enc[4] = r;
  to_AES_enc[5] = t;
  to_AES_enc[6] = y;
  to_AES_enc[7] = u;
  int m = 8;
  for(int i = p; i< p+8; i++){
    to_AES_enc[m] = hmacResult[p+i];
    m++;
  }
  unsigned char cipherTextOutput[16];
  encrypt(to_AES_enc, AES_key, cipherTextOutput);
  //Serial.println(to_AES_enc);
  /*
  Serial.println("\nCiphertext:");
  for (int i = 0; i < 16; i++) {
 
    char str[3];
 
    sprintf(str, "%02X", (int)cipherTextOutput[i]);
    Serial.print(str);
  }
  */
  unsigned char to_serpent[8];
  unsigned char to_serpent_two[8];
  for(int n = 0; n<8; n++){
    to_serpent[n] = cipherTextOutput[n];
    to_serpent_two[n] = cipherTextOutput[n+8];
  }
  serp_enc(to_serpent);
  serp_enc(to_serpent_two);
}

void serp_enc(unsigned char plntxt[]){
  int tmp_s[8];
  for(int i = 0; i<8; i++){
    tmp_s[i] = plntxt[i];
  }
  /*
   for (int i = 0; i < 8; i++){
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
  int p = esp_random()%25;
  for(int i = 0; i<8; i++){
    ct2.b[i] = tmp_s[i];
  }
  int m = 8;
  for(int i = 0; i< 8; i++){
    ct2.b[m] = hmacResult[p+i];
    m++;
  }

  serpent_encrypt (ct2.b, &skey, SERPENT_ENCRYPT);
    for (int i=0; i<16; i++) {
      if(ct2.b[i]<16)
        Serial.print("0");
      Serial.print(ct2.b[i],HEX);
  }
 }
}

void split_dec(char ct[], int ct_len, int p, bool ch){
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
  unsigned char decipheredTextOutput[16];
  unsigned char t_dec[16];
  for(int i = 0; i<8; i++){
    t_dec[i] = tmp_st[i];
  }
  for(int i = 0; i<8; i++){
    t_dec[i+8] = char(sh[i]);
  }
  decrypt(t_dec, AES_key, decipheredTextOutput);
  for (int i = 0; i < 8; i++) {
    dec_stuff += (char)decipheredTextOutput[i];
  }
}

void setup() {
  Serial.begin(115200);
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
}

void loop() {
    Serial.println();
    Serial.println("What do you want to do?");
    Serial.println("1.Encrypt record");
    Serial.println("2.Decrypt record");
    Serial.println("3.Save record");
    Serial.println("4.Load record");
    Serial.println("5.Remove record");
    Serial.println("6.list all stored records");
    while (!Serial.available()) {}
    int x = Serial.parseInt();
    if(x == 1){
      Serial.println("Enter plaintext:");
      String str;
      while (!Serial.available()) {}
      str = Serial.readString();
      int str_len = str.length() + 1;
      char char_array[str_len];
      str.toCharArray(char_array, str_len);
      Serial.println("Ciphertext:");
      int p = 0;
      while(str_len > p+1){
        split_by_eight(char_array, p, str_len);
        p+=8;
      }
    }
    if(x == 2){
      String ct;
      Serial.println("Enter ciphertext");
      while (!Serial.available()) {}
      ct = Serial.readString();
      int ct_len = ct.length() + 1;
      char ct_array[ct_len];
      ct.toCharArray(ct_array, ct_len);
      int ext = 0;
      count = 0;
      dec_stuff = "";
      bool ch = false;
      while(ct_len > ext){
      if(count%2 == 1 && count !=0)
        ch = true;
      else
        ch = false;
      split_dec(ct_array, ct_len, 0+ext, ch);
      ext+=32;
      count++;
      }
      Serial.println("Plaintext");
      Serial.println(dec_stuff);
      dec_stuff = "";
    }
    if(x == 3){
      String cf;
      Serial.println("Enter the name of the new file");
      while (!Serial.available()) {}
      cf = Serial.readString();
      String cont;
      Serial.println("Enter the content of the new file");
      while (!Serial.available()) {}
      cont = Serial.readString();
      write_f("/" + cf, cont);
    }
    if(x == 4){
      String opn;
      Serial.println("Enter the name of the file to open");
      while (!Serial.available()) {}
      opn = Serial.readString();
      read_f("/" + opn);
    }
    if(x == 5){
      String rm;
      Serial.println("Enter the name of the file to remove");
      while (!Serial.available()) {}
      rm = Serial.readString();
      SPIFFS.remove("/" + rm);
    }
    if(x == 6){
      File root = SPIFFS.open("/");
      File file = root.openNextFile();
      while(file){
        Serial.print("FILE: ");
        Serial.println(file.name());
        file = root.openNextFile();
      }
    }
}
