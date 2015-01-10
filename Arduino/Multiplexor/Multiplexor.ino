/*
---------------------------------------
| Ejemplo de Multiplexado con Arduino |        Diseñado por Antony García González, del Panama Hitek Creative Team
---------------------------------------
Este es un ejemplo sobre el efecto que causa el aumento de la frecuencia de multiplexado de una fila de LEDs en el ojo humano.
A partir de determinada frecuencia dejamos de percibir el parpadeo del LED y parece que los 5 LEDs están encendidos a la vez,
cuando en realidad tenemos solo 1 LED encendido en un instante en específico, cambiando a una alta frecuencia.

Este sketch funciona junto a una aplicación en Java, la cual se puede descargar desde el siguiente enlace:
https://github.com/PanamaHitek/ArduinoMultiplexor

Un video con este ejemplo funcionando está disponible en la siguiente dirección:
https://www.youtube.com/watch?v=9youHjA_fWA

*/

//Variable que establece el delay entre un LED y otro
int time = 200;

void setup() {
  //Registro PORT
  DDRD = B11111100;
  Serial.begin(9600);
}

void loop() {
  
  if (Serial.available() > 0) {
    delay(1);
    String input = "";
    while (Serial.available() > 0) {
      //Se lee el mensaje en el puerto serie
      int incomingChar = Serial.read();
      
      //Se verifica si lo que se está recibiendo es o no un punto. Un punto es lo que separa un mensaje de otro
      //En ASCII el 46 representa un mpunto (.)
      if (incomingChar != 46) {
        input += (char)incomingChar;
      }
      else
      {
        time = input.toInt();
        break;
      }
    }
  }

  //Secuencia de encendido de LEDs usando PORT

  PORTD = B10000000;
  delay(time);
  PORTD = B01000000;
  delay(time);
  PORTD = B00100000;
  delay(time);
  PORTD = B00010000;
  delay(time);
  PORTD = B00001000;
  delay(time);

}
