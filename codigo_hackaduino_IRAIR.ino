#include <SoftwareSerial.h> //Biblioteca de comunicação com o bluetooth
#include <HX711.h> //Biblioteca do módulo HX711 que vai converter a pressão da célula de carga para o arduíno
#include <Wire.h> //biblioteca para receber ou enviar dados dos sensores por meio de interface 

//criando comunicação entre o bluetooth no arduíno, através das portas 0,1 (RX - TX)
SoftwareSerial bluetooth(0,1);


//Configurando os pinos 2 e 3 para o modulo HX711
const int PINO_DT = 2;
const int PINO_SCK = 3;

//declaração do intervalo de espera para as leituras do módulo
const int TEMPO_ESPERA = 500;

HX711 escala; //declarando o objeto escala na classe HX711 da biblioteca do módulo 

const int FATOR_CALIBRACAO = 1503100.00; //valor de calibração da célula de carga

void setup ()
{
  Serial.begin(9600); //define a para comunicação serial e a taxa de bits de comunicação por segundo
  bluetooth.begin(9600); //define a comunicação com o bluetooth e a taxa de bits por segundo da comunicação
  escala.begin (PINO_DT, PINO_SCK); //inicializacao e definicao dos pinos DT e SCK dentro do objeto ESCALA
  escala.tare(); //zera a escala
  escala.set_scale(FATOR_CALIBRACAO); //ajusta a escala para o fator de calibracao
  
}

void loop ()
{
  //verifica se o modulo HX711 está pronto para realizar leituras
  if (escala.is_ready())
  {
  //mensagens de leitura no monitor serial
    Serial.print(" Peso: ");// se a escala está pronta para realizar as leituras, essa mensagem será impressa no console do serial
    Serial.print(escala.get_units(), 1); //retorna a leitura da variavel escala com a unidade quilogramas
    Serial.print(" kg");// se a escala está pronta para realizar as leituras, essa mensagem será impressa no console do serial
    Serial.println("");// se a escala está pronta para realizar as leituras, essa mensagem será impressa no console do serial
    //verifica se o valor pego na escala > 1.0
    if(escala.get_units() > 1.0){
      Serial.print("A"); // se o valor pego na escala for maior que 1, esta mensagem será escrita no console do Serial e o envia para o bluetooth
    }


  
  }
  else
  {
    bluetooth.print(" Aguarde  . . . "); //caso a condição de modulo pronto for falsa, essa mensagem sera impressa no console Serial
  }
  delay(TEMPO_ESPERA); //intervalo de espera para leitura
}