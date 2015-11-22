#include "RCSwitch.h"

RCSwitch emissor = RCSwitch();
RCSwitch receptor = RCSwitch();

void setup() {
  // para os prints vamos configurar o serial
  Serial.begin(9600);
  //para conf o emissor e receptor vc só precisa conf os pinos
  //o 4 é o pino que está conectado os dados
  emissor.enableTransmit(4);
  //o receptor é ligado ao pino de dados só que 
  //é um tipo de pino especial que permite acesso a ele atravez
  //de interrupções ex, qdo vc pressiona o teclado há uma interrupção
  //aqui o receptor vai ser "acordado" informando q recebeu algo
  //para cada tipo de arduion no uno o pino de interrupção é o 2 e o 3
  //a ligação errada é para ligar no pino 2
  //esse 0 é pq quer pegar o primeiro pino de interrupção
  receptor.enableReceive(0);
  
  

}

void loop() {
  //valor para transmitir
  long valorEmissao = 1234;
  //aceite que é 24
  emissor.send(valorEmissao, 24);
  delay(50);//para visualizar a transmissão dos dados

  //recepção de dados
  //primeiro identificar se recebeu algo, se tem dados disponíveis
  if(receptor.available()){
    long valorRecebido = receptor.getReceivedValue();
    //vamos imprimir
    Serial.print("Recebido o valor: ");
    Serial.println(valorRecebido);
    //tem q zerar o buffer para nao dar falso positivo
    receptor.resetAvailable();
  }
  


}
