#include <Dynamixel_Serial.h>
#define SERVO_ID   0x01
#define SERVO_ID_2 0x03
#define SERVO_ID_3 0x02
#define SERVO_ID_4 0x04

#define SERVO_ControlPin 0x02 
#define SERVO_SET_Baudrate 9600
#define CW_LIMIT_ANGLE_2 0x00 
#define CCW_LIMIT_ANGLE_2 0xFFF
#define CW_LIMIT_ANGLE 0x800 
#define CCW_LIMIT_ANGLE 0x400

//definción de variables
String entrada="";  //variable que servirá para guardar la entrada del puerto serial
String encabezado=""; //variable que servirá para saber si la instrucción recibida es valida
String angulo_inst=""; // el ángulo que se recibe a la entrada del puerto serial
String id="";   //el identificador del motor que se desea controlar
String velocidad=""; // la velocidad recibida del puerto serial
unsigned int angulo_int;  //numero de 0 a 4095 que es el angulo que se envía al motor
unsigned int velocidad_int; //velocidad que se envia al motor como entero
int id_int=0; // id en forma de entero


void setup() {
  Serial.begin(9600); //se inicializa el puerto serial a un baudrate de 9600
  Dynamixel.begin(SERVO_SET_Baudrate); //se incializa la transmisión a los servos
  Dynamixel.setMode(SERVO_ID, SERVO, CW_LIMIT_ANGLE, CCW_LIMIT_ANGLE); 
  Dynamixel.setMode(SERVO_ID_2, SERVO, CW_LIMIT_ANGLE_2, CCW_LIMIT_ANGLE_2);
}


void loop() {
  // Se lee el dato entrante del puerto serial
  entrada=Serial.readString();
  // Para que sea una instruccion validad los primeros dos caracteres del string deben ser do arrrobas(@@)
  encabezado=entrada.substring(0,2);
  if(encabezado.equals("@@")){
    //Si es una instruccion con el encabezado correcto se realiza el siguiente procedimiento
    angulo_inst=entrada.substring(2,4); //Se toma el angulo que deberia ser los caracteres 2 y 3
    id=entrada.substring(4,5); // Se toma el id que deberia corresponder al 4 caracter
    id_int=id.toInt();
    if(id==1){
      id_int=0x01;
    }
    if(id==2){
      id_int=0x03;
    }
    if(id==3){
      id_int=0x02;
    }
    if(id==4){
      id_int=0x04;
    }
    velocidad=entrada.substring(5); // Se toma la velocidad que son los ultimos tres digitos
    angulo_int=round(angulo_inst.toInt()*11.378+1024); //Se convierte el angulo a un numero que va de 0 a 4095
    velocidad_int=velocidad.toInt();
    //Salidas para debugging
    //Serial.println(entrada);
    //Serial.println(angulo_int);
    //Serial.println(id);
    //Serial.println(velocidad_int);
    Dynamixel.servo(id_int,angulo_int,velocidad_int);//se envian las instrucciones a los motores
  }
}
