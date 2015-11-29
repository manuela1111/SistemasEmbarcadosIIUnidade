#include <Wire.h>
#include "RCSwitch.h"
#include "ADXL345.h"

//instâncias do emissor e do receptor
RCSwitch emissor  = RCSwitch();
RCSwitch receptor = RCSwitch();

//instância do acelerômetro
ADXL345 acel = ADXL345();

#define RFID_LIMITE_INFERIOR 12345
#define RFID_LIMITE_SUPERIOR 12355
#define DESLOCAMENTO_RFID  17
#define DESLOCAMENTO_MOVMT 16
#define DESLOCAMENTO_BATMT 8

#define PINO_BATIMENTOS  0
#define PINO_TEMPERATURA 1

struct InfoRF{
  int id;
  int batimentos;
  int temperatura;
  int movimento;
}infoRF;

 
void setup() {
  Serial.begin(9600);

  //Configuração do emissor receptor RF
  emissor.enableTransmit(4);
  receptor.enableReceive(0);

  //Configuração do acelerômetro para detecção de movimento
  //Ligar o acelerômetro
  //quando detecta o movimento é o activity nos 3 eixos
  acel.powerOn();
  acel.setInactivityX(1);
  acel.setInactivityY(1);
  acel.setInactivityZ(1);

  acel.setActivityX(1);
  acel.setActivityY(1);
  acel.setActivityZ(1);

  //A detecção da inatividade ou atividade tem um limite
  //valor muito alto torna o sensor insensível thrashold
  acel.setActivityThreshold(50);
  acel.setInactivityThreshold(50);
  //notificar uma situação de inatividade
  acel.setTimeInactivity(10);

  //Acionamento da detecção da atividade e inatividade
  acel.setInterruptMapping(ADXL345_INT_ACTIVITY_BIT,ADXL345_INT1_PIN);
  acel.setInterruptMapping(ADXL345_INT_INACTIVITY_BIT, ADXL345_INT1_PIN);

  acel.setInterrupt(ADXL345_INT_ACTIVITY_BIT,1);
  acel.setInterrupt(ADXL345_INT_INACTIVITY_BIT,1);

  
}
//tirou os parâmetros pq já vai pegar direto dos sensores
long lerSensoresRF() {

  //no anologRead vai passar o pino do potenciômetro
  long batimentos = analogRead(PINO_BATIMENTOS);
  long temperatura= batimentos; //analogRead(PINO_TEMPERATURA);
  //long movimento= 0; estava sem sensor 
  long movimento;

  batimentos = map(batimentos, 0, 1023, 0, 200);
  temperatura = map(temperatura, 0, 1023, 0, 40);

  byte interrupAcel = acel.getInterruptSource();

  if (acel.triggered(interrupAcel,ADXL345_INT_ACTIVITY_BIT)){
    movimento=1;
  }
  
  long rf = RFID_LIMITE_INFERIOR;
  long info = rf << DESLOCAMENTO_RFID;
  info = info | (movimento << DESLOCAMENTO_MOVMT);
  info = info | (batimentos << DESLOCAMENTO_BATMT);
  info = info | temperatura;
  
  return info;  
}

boolean RFIDValido(long info) {
  boolean valido = false;
  
  infoRF.id = info >> DESLOCAMENTO_RFID;
  if ((infoRF.id >= RFID_LIMITE_INFERIOR) && (infoRF.id <= RFID_LIMITE_SUPERIOR)){
     valido = true; 
  }

  return valido;  
}

void enviarParaUSB(){
   //int tam = sizeof(dados);
  char buff[sizeof(InfoRF)] = {0};
 
  //char buff[tam];

  memcpy(&buff, &infoRF, sizeof(InfoRF));

  Serial.write("I");
  Serial.write((uint8_t*)&buff, sizeof(InfoRF));
  Serial.write("T");
  
  
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

int extrairMovimento(long info) {
  int movimento = (info & 65536) >> DESLOCAMENTO_MOVMT;
   
  return (movimento == 1);
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
  long info = lerSensoresRF(); 
  emitir(info);
    
  delay(20);
  
  // RECEPCAO DE DADOS
  info = receber();
  
  if (info != -1) {
    if (RFIDValido(info)) {
      
    
      infoRF.movimento = extrairMovimento(info);
      infoRF.batimentos = extrairBatimentos(info);
      infoRF.temperatura = extrairTemperatura(info);

      enviarParaUSB();
   
      /*int batimentos = extrairBatimentos(info);
      Serial.print("O coracao de Avemarilson estah batendo a ");
      Serial.print(batimentos);
      Serial.println(" bpm");
      
      int temperatura = extrairTemperatura(info);
      Serial.print("A temperatura de Avemarilson eh ");
      Serial.print(temperatura);
      Serial.println(" graus celsius");*/
    }
  }
}


