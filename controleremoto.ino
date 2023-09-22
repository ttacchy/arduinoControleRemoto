#include <IRremote.h> // Biblioteca IRemote

const int Controle_Pin = 12; // Arduino pino 12 conectado no Receptor IR
IRrecv irrecv(Controle_Pin); // criando a instância
decode_results resultados; // declarando os resultados
unsigned long key_value = 0;
bool Led_1, Led_2, Led_3 = false;

void setup(){
Serial.begin(9600);
pinMode(5, OUTPUT); // LED vermelho no pino D05
pinMode(6, OUTPUT); // LED amarelo no pino D06
pinMode(7, OUTPUT); // LED azul no pino D07
irrecv.enableIRIn();
irrecv.blink13(true); // Pisca o led 13 do arduino, apenas para uma referencia visual
// pois nao conseguimos ver a luz infravermelha do controle
}

void loop(){
if (irrecv.decode(&resultados)){
if (resultados.value == 0XFFFFFFFF)
resultados.value = key_value;
switch(resultados.value){
case 0xFF30CF:
Serial.println("Botão 1");
Led_1 = !Led_1; // alterna o estado do LED D05
digitalWrite(5, Led_1); // acende ou apaga LED vermelho (D05)
delay(300); // atraso de 300 ms
break;
case 0xFF18E7:
Serial.println("Botão 2");
Led_2 = !Led_2; // alterna o estado do LED D06
digitalWrite(6, Led_2); // acende ou apaga LED amarelo (D06)
delay(300); // atraso de 300 ms
break;
case 0xFF7A85:
Serial.println("Botão 3");
Led_3 = !Led_3; // alterna o estado do LED D07
digitalWrite(7, Led_3); // acende ou apaga LED azul (D07)
delay(300); // atraso de 300 ms
break;
}
key_value = resultados.value;
irrecv.resume(); 
}
}