#include "RCSwitch.h"

RCSwitch emissor  = RCSwitch();
RCSwitch receptor = RCSwitch();

#define RFID 12345
#define DESLOCAMENTO_RFID  17
#define DESLOCAMENTO_CHORO 16
#define DESLOCAMENTO_BATMT 8

void setup() {
  Serial.begin(9600);
  
  emissor.enableTransmit(4);
  receptor.enableReceive(0);
}

long simularSensoresRF(long chorando, long batimentos, 
  long temperatura) {
  
  long rf = RFID;
  long info = rf << DESLOCAMENTO_RFID;
  info = info | (chorando << DESLOCAMENTO_CHORO);
  info = info | (batimentos << DESLOCAMENTO_BATMT);
  info = info | temperatura;
  
  return info;  
}

boolean RFIDValido(long info) {
  boolean valido = false;
  
  int rfid = info >> DESLOCAMENTO_RFID;
  if (rfid == RFID) {
     valido = true; 
  }

  return valido;  
}

void emitir(long info) {
  emissor.send(info, 32);  
}

long receber() {
  long info = -1;
  
  if (receptor.available()) {
    info = receptor.getReceivedValue();
    
    receptor.resetAvailable();    
  }
  
  return info;
}

boolean extrairChoro(long info) {
  int choro = (info & 65536) >> DESLOCAMENTO_CHORO;
   
  return (choro == 1);
}

int extrairBatimentos(long info) {
  int batimentos = (info & 65280) >> DESLOCAMENTO_BATMT;
  
  return batimentos;
}

int extrairTemperatura(long info) {
  int temperatura = (info & 255);

  return temperatura;  
}

void loop() {
  // EMISSAO DE DADOS
  long info = simularSensoresRF(0, 100, 35); 
  emitir(info);
    
  delay(50);
  
  // RECEPCAO DE DADOS
  info = receber();
  
  if (info != -1) {
    if (RFIDValido(info)) {
      boolean chorando = extrairChoro(info);
      if (chorando) {
        Serial.println("Avemarilson estah chorando!");  
      }
      int batimentos = extrairBatimentos(info);
      Serial.print("O coracao de Avemarilson estah batendo a ");
      Serial.print(batimentos);
      Serial.println(" bpm");
      
      int temperatura = extrairTemperatura(info);
      Serial.print("A temperatura de Avemarilson eh ");
      Serial.print(temperatura);
      Serial.println(" graus celsius");
    }
  }
}


