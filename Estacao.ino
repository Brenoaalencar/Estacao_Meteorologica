//Estação Meteorológica 2020.2
//Grupo: Breno Alencar, Renato Laffranchi e Stephan Böttcher

//O código a seguir instrui ao Arduino UNO a leitura e impressão de dados via Serial e Display LCD

//Importando bibliotecas necessárias
#include <Adafruit_Sensor.h>
#include<DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp;

//Para DHT22
//const int para somente leitura de variável
const int DHT_PIN = 2;
DHT dht(DHT_PIN,DHT22);
float umidade,tempdht;

// LiquidCrystal_I2C
// Endereço= 0x27
//Colunas  = 16
// Linhas  = 2
LiquidCrystal_I2C lcd(0x27, 16, 2);

//LEDs para DHT22
//Para umidades relativas abaixo de 12%
int vermelho=6;
//Para umidades relativas entre 12% e 30%
int amarelo=8;
//Para umidades relativas acima de 60%
int verde=7;
//Percentuais de acordo com os recomendados pela OMS


void setup() {
  // Comunicação Serial 9600 bps
  Serial.begin(9600);
  // Referência AD Interna
  analogReference(INTERNAL);
  
  //Iniicaliza DHT22
  dht.begin();

  //Saída para os LEDs
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);

  //Inicializa BMP280
  bmp.begin(0x76);

  //Inicializa display e apresenta grupo
  lcd.init();
  lcd.setBacklight(1);
  lcd.setCursor(0,0);
  lcd.print("Ola, Carlos!");
  lcd.setCursor(0,1);
  lcd.print("Fala, Caue!");
  delay(1590);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Sejam");
  lcd.setCursor(0,1);
  lcd.print("  bem-vindos a");
  delay(1590);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("     Estacao");
  lcd.setCursor(0,1);
  lcd.print("  Meteorologica");
  delay(1590);
  lcd.clear();
  lcd.print("   InstruMed    ");
  lcd.setCursor(0,1);
  lcd.print("     2020.2     ");
  delay(1590);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("by Breno, Renato");
  lcd.setCursor(0,1);
  lcd.print("e Stephan  ");
  delay(1590);
  //Finaliza apresentação dos integrantes
  lcd.clear();
  
  //Criando caracteres especiais

 byte grau[] = {
  B00111,
  B00101,
  B00111, 
  B00000,
  B00000,
  B00000,
  B00000,
};


  lcd.createChar(0, grau);
  


  //Apresentação pelo Serial
  Serial.println("\n\n********Instrumed 2020.2*******");
  Serial.println("Caro usuário, bem-vindo a nossa Estação Meteorológica!\n A seguir, apresentamos valores de:\n Temperatura\n Umidade\n Pressão\n Altitude\n Luminosidade");
    
}

void loop() {
  // Sensor LM35
  
// Lê tensão analógica na porta A0 
  int lm35 = analogRead(A0);
  
  // Converte para um valor em volts (PWM)
  float voltagem = lm35 * (1.1/1023);
  
  // Calcula a temperatura
  //
  float temperatura = 1.008*(voltagem * 100)+0.521; // coeficientes ajustados pelo Método dos Mínimos Quadrados: f-1(x)=1.008y+0.521
  
  //Apresentando valores medidos para o usuário (Serial e display)
  Serial.println("\n\n********INSPER*******");
  //Infelizmente os sensores Lm35 estão avariados e optamos por utilizar o sensor de temperatura do DHT22, caso utilizássemos o do Lm35, segue código
  //lcd.setCursor(0,0);
  //lcd.print("  Temperatura   ");
  //lcd.setCursor(6,1);
  //lcd.print(temperatura)
  //lcd.write(byte(0)); //grau
  //lcd.print("C "); 

  //Sensor DHT22
  
  //Lê umidade e temperatura com as funções seguintes
  umidade = dht.readHumidity();
  tempdht = dht.readTemperature();
  umidade=0.975*umidade-0.089; //coeficientes ajustados pelo Método dos Mínimos Quadrados: f-1(x)=0.975y-0.089
 //incertDHT = 2.00; //incerteza do tipo B
  //Apresentando valores medidos para o usuário (Serial e display)
  Serial.print("Temperatura : ");
  Serial.print(tempdht);
  Serial.println(" *C (Grau Celsius)");
  Serial.print("Umidade relativa: ");
  Serial.println(umidade);

lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura");
  lcd.setCursor(0,1);
  lcd.print(tempdht);
  lcd.write(byte(0)); //símbolo de grau
  lcd.print("C ");
 
  delay (2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Umidade");
  lcd.setCursor(0,1);
  lcd.print(umidade);
  lcd.print (" %");
 
  //Sinaliza visualmente ao usuário a condição da umidade do ar
  //verde para umidade acima de 60%
  //amarelo entre 12% e 30%
  //vermelho para umidades inferiores a 12%
  digitalWrite(vermelho, umidade<12);
  digitalWrite(amarelo, umidade>12 and umidade<60);
  digitalWrite(verde, umidade>60);
  
  delay (2000);

  

  //Sensor BMP280
  
  //Apresentando valores medidos de pressão e altitude para o usuário (Serial e display)
  Serial.print(F("Pressão: ")); 
  Serial.print(bmp.readPressure()/101325); //Conversão pascal para atmosfera
  Serial.println(" atm"); 

lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pressao");
  lcd.setCursor(0,1);
  lcd.print(bmp.readPressure()/101325);
  lcd.print(" atm");
  delay (2000);
  
  Serial.print(F("Altitude aprox.: ")); 
  Serial.print(bmp.readAltitude(1013.25),0); 
  //Serial.print(bmp.readAltitude(1020.6),0); 
  Serial.println(" m (Metros)"); 

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Altitude");
  lcd.setCursor(0,1);
  lcd.print(bmp.readAltitude(1013.25));
  lcd.print(" m");
  delay (2000);


//Sensor LDR

//Definindo variáveis
  int bin;
  float tensao, res, lum;

//Lê tensão analógica na porta A2
  bin = analogRead(A2);
  tensao = bin*1.1/1023.0;
  res = 330*(5.0/tensao+1);
  lum = pow(10, 5-log10(res));

  Serial.print("Luminosidade :");
  Serial.println(lum);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Luminosidade");
  lcd.setCursor(0,1);
  lcd.print(lum);
  lcd.print(" lux");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Obrigado!");
    
  Serial.println("*******INSPER********\n");

  
  delay(2000);
//Por motivos didáticos optamos por apresentar as infomrmações em paralelo  

}
