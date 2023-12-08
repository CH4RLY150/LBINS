
#define BLYNK_PRINT Serial
#include <ESP8266.h>
#include <BlynkSimpleShieldEsp8266.h>
// librería del acelerómetro
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
// parte del acelerómetro
const int mpuAddress = 0x68;  // Puede ser 0x68 o 0x69
MPU6050 mpu(mpuAddress);
// Auth Token o código de autentificación de Blynk App.
char auth[] = ;
//credenciales de la red WIFI
char ssid[] = ;
char pass[] = ;
//Nombre del módulo ESP
#define EspSerial Serial1
//tasa de baudios a los que trabajará el módulo ESP
#define ESP8266_BAUD 9600
//inicialización del ESP
ESP8266 wifi(&EspSerial);
WidgetLCD lcd(V2);//asignación del pin virtual 2
SimpleTimer timer2;//temporizador
byte timerID;//ID del temporizador
byte repeticiones;// numero de repeticiones
byte ej;//numero de ejercicio escogido
byte contador=0;//contador de lectura de datos
int valorMax=0;//valor máximo recogido
int valorMin=140;//valor mínimo leído
int position; //posición del potenciómetro en tanto por ciento
String cadena ="";//cadena que se enviará por email con los datos del ejercicio
/*****************************************FUNCIÓN QUE ESCRIBE EN LA 
PANTALLA LED DE LA APP***********************/
void imprime1(String cadena){
 lcd.clear();
 lcd.print(0, 0, cadena);
}
void imprime2(String cadena){
 lcd.print(0, 1, cadena);
}
/********************************FUNCION DE LECTURA DEL EJERCICIO 
ESCOGIDO EN LA APP***************************/
BLYNK_WRITE(V0){ 
  ej = param.asInt();//Lee el ejercicio escogido
 switch (param.asInt()){
    case 1://se elige el ejercicio 1
    Blynk.virtualWrite(V1, 1); //se cambia la imagen 1 en el widget de IMAGE GALERY
    repeticiones=20;
    cadena ="";
    imprime1("Has elegido");
    imprime2("ejercicio 1");
    delay(2000);
    break;
    case 2://se elige el ejercicio 2
    Blynk.virtualWrite(V1, 2); //se cambia la imagen 2
    repeticiones=20;
    cadena ="";
    imprime1("Has elegido");
    imprime2("ejercicio 2");;
    delay(2000);
    break;
    case 3://se elige el ejercicio 3
    Blynk.virtualWrite(V1, 3); //se cambia la imagen 3
    repeticiones=20;
    cadena ="";
    imprime1("Has elegido");
    imprime2("ejercicio 3");
    delay(2000);
    break;
    case 4://se elige el ejercicio 4
    Blynk.virtualWrite(V1, 4); //se cambia la imagen 4
    repeticiones=20;
    cadena ="";
    imprime1("Has elegido");
    imprime2("ejercicio 4");
    delay(2000);
    break;
    case 5://se elige el ejercicio 5
    Blynk.virtualWrite(V1, 5); //se cambia la imagen 5
    repeticiones=20;
    cadena ="";
    imprime1("Has elegido");
    imprime2("ejercicio 5");
    delay(2000);
    break;
    default:
    imprime1("No se ha");
    imprime2("escogido nada");
  }
}
/**************************************FUNCIÓN QUE LEE LOS DATOS DEL 
POTENCIÓMETRO Y ACELERÓMETRO***************************/
void leedatos(){
 // POTENCIÓMETRO
 const int analogPin = A0; //variable que almacena el valor del potenciometro
 int value = analogRead(A0); //variable que almacena la lectura analógica raw
 position = round(map(value, 0, 1023, 0, 370)); //posicion del potenciometro en tanto por ciento
 Blynk.virtualWrite(V5, position);//escribe en la aplicacion en el widget SUPERCHART
 //Serial.print(position);
 valorMax = max(position, valorMax);//Actualiza el valor máximo recogido
 valorMin = min(position, valorMin);//Actualiza el valor mínimo recogido
 cadena=cadena+","+position;

 // ACELERÓMETRO
 // parte del acelerómetro
 int ax, ay, az;
 int gx, gy, gz;
 // Leer las aceleraciones 
 mpu.getAcceleration(&ax, &ay, &az);
 //Calcular los angulos de inclinacion
 float accel_ang_x = atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);
 float accel_ang_y = atan(ay / sqrt(pow(ax, 2) + pow(az, 2)))*(180.0 / 3.14);
 acl_x_MAX = max(accel_ang_x, acl_x_Max);//Actualiza el valor máximo recogido
 acl_x_MIN = min(accel_ang_x, acl_x_Min);//Actualiza el valor mínimo recogido
 acl_y_MAX = max(accel_ang_y, acl_y_Max);//Actualiza el valor máximo recogido
 acl_y_MIN = min(accel_ang_y, acl_y_Min);//Actualiza el valor mínimo recogido

 // EJERCICIO
 switch (ej)//llama a el ejercicio correspondiente
 {
    case 1: ejercicio1();//comprobaciones del ej 1
    break;
    case 2: ejercicio2();//comprobaciones del ej 2
    break;
    case 3: ejercicio3();//comprobaciones del ej 3
    break;
    case 4: ejercicio4();//comprobaciones del ej 4
    break;
    case 5: ejercicio5();//comprobaciones del ej 5
    break;
    default:
    imprime1("Escoge un");
    imprime2("ejercicio ");
    delay(1000);
    break;
  }
}
/*****************************FUNCION QUE HACE LAS COMPROBACIONES DEL 
EJERCICIO 1********************************/
void ejercicio1()//Sentada flexiona y estira la rodilla al máximo
{
  if(repeticiones==20){
    if(acl_x_MAX<___ && acl_x_MIN>____ && acl_y_MAX<____ && acl_y_MIN>_____){
      imprime1("Recuerda estar");
      imprime2("sentado");
    }
  }
  contador++;//Aumenta el contador para la escritura en LCD
  if (valorMax < 130)//comprobacion para ver si NO flexiona la rodilla
  {
    if (contador >= 40)//si el contador llega a 40 que escriba en LCD
    {
      imprime1("Flexiona mas la");
      imprime2("rodilla");
      contador = 0;//Se restauran los valores
      valorMin = 140;//Se restauran los valores
      valorMax = 0;//Se restauran los valores
    }
  }
  else if (valorMin > 10)//comprobabcion para ver si NO estira la rodilla
  {
    if (contador >= 40)//si el contador llega a 40 que escriba en LCD
    {
      imprime1("Estira mas la");
      imprime2("rodilla");
      contador = 0;
      valorMin = 140;
      valorMax = 0;
    }
  }
  else //si consigue cumplir los ángulos correctos
  {
    if(valorMin <10 && valorMax > 130)
    {
      if(contador>=4)
      {
        imprime1("Sigue asi");
        contador=0;
      }
 
      valorMin = 140;
      valorMax = 0;
      repeticiones--;//se disminuye una repeticion de la serie
      Blynk.virtualWrite(V4, repeticiones);//se imprime en la aplicación en el widjet de DISPLAY
      if (repeticiones <= 0)//si termina con las repeticiones
      {
        imprime1("Enhorabuena, has");
        imprime2("terminado el ej");//termina el ejercicio (imprime lcd)
        Blynk.virtualWrite(V3, 1);//pone el boton a STOP y para de leer datos
        timer2.disable(timerID);//deshabilita el temporizador que llama a Leedatos
        Blynk.email(_______, "Subject","Ejercicio1:"+cadena);
      }
    } 
  }
}
/*****************************FUNCION QUE HACE LAS COMPROBACIONES DEL 
EJERCICIO 2********************************/
void ejercicio2()//Sentadilla contra la pared
{
  if(repeticiones==20){
    if(acl_x_MAX<___ && acl_x_MIN>____ && acl_y_MAX<____ && acl_y_MIN>_____){
      imprime1("Recuerda estar");
      imprime2("sentado");
    }
  }
  contador++;
  if (valorMax < 90)//comprobabcion de flexión
  {
    if (contador >= 40)
    {
      imprime1("Flexiona mas la");
      imprime2("rodilla");
      contador = 0;
      valorMin = 140;
      valorMax = 0;
    }
  }
  else if (valorMin > 10)//comprobabción de estiramiento
  {
    if (contador >= 40)
    {
      imprime1("Estira mas la");
      imprime2("rodilla");
      contador = 0;
      valorMin = 140;
      valorMax = 0;
    }
  }
  else
  {
    if(valorMin <10 && valorMax > 90)//comprobacion de movimiento correcto
    {
      imprime1("Sigue asi");
      valorMin = 140;
      valorMax = 0;
      repeticiones--;//disminuye una repetición
      Blynk.virtualWrite(V4, repeticiones);//escribe en el widget de DISPLAY
      if (repeticiones <= 0)//termina el ejercicio
      {
        imprime1("Enhorabuena, has");
        imprime2("terminado el ej");
        Blynk.virtualWrite(V3, 1);//para de leer y pone la app en STOP
        Blynk.email(________, "Subject","Ejercicio2:"+cadena);
      }
    } 
  }
}
/*****************************FUNCION QUE HACE LAS COMPROBACIONES DEL 
EJERCICIO 3********************************/
void ejercicio3()//tumbada llevar la rodilla al pecho flexionando
{
  if(repeticiones==20){
    if(acl_x_MAX<___ && acl_x_MIN>____ && acl_y_MAX<____ && acl_y_MIN>_____){
      imprime1("Recuerda estar");
      imprime2("sentado");
    }
  }
  contador++;
  if (valorMax < 130)//comparativa de flexión
  {
    if (contador >= 40)
    {
      imprime1("Flexiona mas la");
      imprime2("rodilla");
      contador = 0;
      valorMin = 140;
      valorMax = 0;
    }
  }
  else if (valorMin > 10)//comparativa de estiramiento
  {
    if (contador >= 40)
    {
      imprime1("Estira mas la");
      imprime2("rodilla");
      contador = 0;
      valorMin = 140;
      valorMax = 0;
    }
  }
  else if (position > 130)//comparativa de la rodilla al pecho
  {
    if (contador >= 5)
    {
      imprime1("lleva la rodilla");
      imprime2("al pecho");
      contador = 0;
    }
  }
  else//se realiza correctamente el ejercicio
  {
    if(valorMin <10 && valorMax > 130)
    {
      lcd.clear();
      lcd.print(0, 0, "Sigue asi");
      valorMin = 140;
      valorMax = 0;
      repeticiones--;//disminuye una repetición
      Blynk.virtualWrite(V4, repeticiones);//escribe en el widget de DISPLAY las repeticiones que quedan
      if (repeticiones <= 0)//termina el ejercicio
      {
        imprime1("Enhorabuena, has");
        imprime2("terminado el ej");
        Blynk.virtualWrite(V3, 1);
        Blynk.email(________, "Subject","Ejercicio3:"+cadena);
        timer2.disable(timerID);//deshabilita el temporizador que llama a Leedatos
      }
    } 
  }
}
/*****************************FUNCION QUE HACE LAS COMPROBACIONES DEL 
EJERCICIO 4********************************/
void ejercicio4()//boca abajo flexionar y estirar
{
  if(repeticiones==20){
    if(acl_x_MAX<___ && acl_x_MIN>____ && acl_y_MAX<____ && acl_y_MIN>_____){
      imprime1("Recuerda estar");
      imprime2("sentado");
    }
  }
  contador++;
  if (valorMax < 130)//comprobación de flexión
  {
    if (contador >= 40)
    {
      imprime1("Flexiona mas la");
      imprime2("rodilla");
      contador = 0;
      valorMin = 140;
      valorMax = 0;
    }
  }
  else if (valorMin > 10)//comparación de estiramiento
  {
    if (contador >= 40)
    {
      imprime1("Estira mas la");
      imprime2("rodilla");
      contador = 0;
      valorMin = 140;
      valorMax = 0;
    }
  }
  else//realiza correctaente el ejercicio
  {
    if(valorMin <10 && valorMax > 130)
    {
      imprime1("Sigue asi");
      valorMin = 140;
      valorMax = 0;
      repeticiones--;
      Blynk.virtualWrite(V4, repeticiones);
      if (repeticiones <= 0)
      {
        imprime1("Enhorabuena, has");
        imprime2("terminado el ej");
        Blynk.virtualWrite(V3, 1);
        Blynk.email(_______, "Subject","Ejercicio4:"+cadena);
        timer2.disable(timerID);//deshabilita el temporizador que llama a Leedatos
      }
    } 
  }
}
/*****************************FUNCION QUE HACE LAS COMPROBACIONES DEL 
EJERCICIO 5********************************/
void ejercicio5()//Levantar la pierna estirada
{
  if(repeticiones==20){
    if(acl_x_MAX<___ && acl_x_MIN>____ && acl_y_MAX<____ && acl_y_MIN>_____){
      imprime1("Recuerda estar");
      imprime2("sentado");
    }
  }
  contador++;
  if (valorMax > 20)//comprobar que no flexiona la rodilla
  {
    if (contador >= 40)
    {
      imprime1("Estira mas la");
      imprime2("rodilla");
      contador = 0;
      valorMin = 140;
      valorMax = 0;
    }
  }
  else if (valorMin > 10)//comparar que estira lo suficiente la rodilla
  {
    if (contador >= 40)
    {
      imprime1("Estira mas la");
      imprime2("rodilla");
      contador = 0;
      valorMin = 140;
      valorMax = 0;
    }
  }
  else
  {
    if(valorMin <10 && valorMax <30)//realiza correctamente el ejercicio
    {
      imprime1("Sigue asi");
      valorMin = 140;
      valorMax = 0;
      repeticiones--;//disminuye una repeticion
      Blynk.virtualWrite(V4, repeticiones);//imprime en DISPLAY las repeticiones que quedan
      if (repeticiones <= 0)//termina el ejercicio
      {
        imprime1("Enhorabuena, has");
        imprime2("terminado el ej");
        Blynk.virtualWrite(V3, 1);
        Blynk.email(________, "Subject","Ejercicio5:"+cadena);
        timer2.disable(timerID);//deshabilita el temporizador que llama a Leedatos
      }
    } 
  }
}
BLYNK_WRITE(V3){ 
  if (param.asInt() == 1)//El boton en la aplicación está a 1
  {
    timer2.disable(timerID);//deshabilita el temporizador que llama a Leedatos
    imprime1("Has salido del");//Imprime en LCD
    imprime2("ejercicio");
    delay(3000);
  }
  else{
    timer2.enable(timerID);//habilita el temporizador que llama a leedatos
    imprime1("Empieza el");//Imprime en LCD
    imprime2("ejercicio");
    delay(3000);
  }
}
/********************************************FUNCIÓN DE 
INICIALIZACIÓN****************************************/
void setup(){
  //Set acelerómetro MPU6050
  //Serial.begin(9600);//Para que aparezca por el puerto serie del ordenador los mensajes
  Wire.begin();
  mpu.initialize();
  Serial.println(mpu.testConnection() ? F("IMU iniciado correctamente") : F("Error al iniciar IMU"));
  // Set módulo wifi ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);//inicializa el módulo ESP8266
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);//conexión con la aplicación
  //Serial.println("Waiting for connections...");
  timerID= timer2.setInterval(500L, leedatos);//inicializacion del 
  //timer de leedatos cada 250ms
  Blynk.syncAll();//sincroniza la aplicacion blynk todos los pines 
  //virtuales
}
/**********************************FUNCIÓN DEL BUCLE 
PRINCIPAL*************************************************/
void loop(){
 Blynk.run();//ejecuta la apicación de blynk
 timer2.run();//ejecuta el temporizador
}

