# Estacao_Meteorologica
Estação Meteorológica utilizando um Arduino, projeto concluído em 19/11/2020. Por Breno Alencar, Renato Laffranchi e Stephan Böttcher.

## Introdução:

Este projeto tem o objetivo de orientar a construção de uma pequena estação meteorológica que afere temperatura, umidade, pressão, altitude e luminosidade, além de apresentar essas medições em um display LCD serial.

### Materiais:
* Protoboard
* Arduino UNO
* Sensor LM35
* Sensor DHT22
* Sensor BMP280
* Sensor LDR
* Display de Cristal Líquido
* 3x resistores de 1 kΩ
* 1x resistor de 330 Ω
* Jumpers
* 3x LEDs

### Calibração de sensores:
#### Calibração do LM35

<div align="center">
<img src ="https://user-images.githubusercontent.com/72100554/236974343-4d9de551-2451-4c08-ac77-5220fe16717e.png" width="200px"/>
</div>

Ao iniciar a montagem do sensor de temperatura (LM35) junto ao Arduino, é prudente verificar o Datasheet do fabricante e avaliar se as incertezas que o dispositivo possui são passíveis de interferirem significativamente nas medições. No caso deste sensor, o grau de suas incertezas fazem necessária uma calibração e, portanto, utilizando fornos de calibração, foram realizadas cinco medições em diferentes temperaturas utilizando o LM35.
Pino 1 do sensor ligado aos 5V, pino 3, ao ground e pino 2 à porta A0.

Calculou-se então a média, o desvio padrão, a incerteza do tipo A, a incerteza do tipo B e a incerteza padrão. Em seguida, utilizou-se então o método dos mínimos quadrados (MMQ) para obtenção de uma função que permite a correção dos valores medidos. Dessa forma foi possível encontrar a função inversa e sua respectiva função que relaciona o valor medido e o real valor. 

f(x) = 0,992x + 0,517


#### Calibração do DHT22
<div align="center">
<img src ="https://user-images.githubusercontent.com/72100554/236975967-29b8e025-adfb-438e-a638-045ea87fafc4.png" width="200px"/>
</div>
Para o sensor  de umidade (DHT22), a análise do Datasheet revela incertezas elevadas e uma calibração é fortemente recomendada. Utilizando de uma simulação em Excel, foi medida a temperatura em cada becker de solução salina, e foram realizadas cinco medições de umidade relativa em cada becker utilizando o DHT22.
Realizando processos de interpolação e de extrapolação usando os valores de uma tabela de referência de experimentos com sais, é possível obter valores de referência de umidade relativa para a temperatura de medição em cada solução salina para a calibração do sensor de umidade. Como existe incerteza tanto na medição da temperatura como na medição da umidade, precisa-se transferir essas incertezas para um único “eixo”, que é o eixo com os valores de umidade relativa medidos pelo sensor. Após realizar a transferência das incertezas, foi possível calcular, com as medidas de umidade realizadas anteriormente, a média, o desvio padrão, as incertezas do tipo A e B, a incerteza padrão e combinar essa incerteza com a incerteza que foi transferida. Utilizou-se então o método dos mínimos quadrados (MMQ) para obtenção de uma função que permite a correção dos valores medidos. 

f(x) = 1,025x + 0,091

#### Caliração do BMP280 e do LDR
<div align="center">
<img src ="https://user-images.githubusercontent.com/72100554/236976279-97317dbb-a9b4-481c-a929-b28a6072c56a.png" width="200px"/>
</div>
Analisando o Datasheet do sensor BMP280 é possível notar alta confiabilidade e uma calibração neste caso seria desnecessária, portanto apenas é preciso montá-lo à protoboard. Este afere pressão e temperatura. Não é necessária calibração do LDR.

### Montagens

<div align="center">
<img src ="https://user-images.githubusercontent.com/72100554/236974649-9f8a0551-05d3-4742-a8ea-87b7b961d818.png" width="400px"/>
</div>

Com o auxílio de uma protoboard, realizou-se a conexão dos sensores, do display e dos LEDs ao Arduino UNO. 
Após a montagem completa da estação e calibração individual dos sensores, guarda-se as portas em que cada sensor se comunica com o Arduino e passa-se para o código.
A inicialização se dá pela importação de todas as bibliotecas necessárias, logo em seguida, declara-se as variáveis utilizadas e inicia-se o display apresentando o grupo. Durante o void loop, cada sensor mede e faz a gravação dos dados em suas respectivas portas, guardando-os em variáveis próprias, ajustando de acordo com a calibração e apresentando via serial e display.

#### Montagem do display
<div align="center">
<img src ="https://user-images.githubusercontent.com/72100554/236975007-1db52eb8-c006-48e9-867a-8638840a3d63.png" width="400px"/>
</div>


#### Montagem final
<div align="center">
<img src ="https://user-images.githubusercontent.com/72100554/236974842-a3d6b533-88da-474a-861c-a0e078c32bcc.png" width="400px"/>
</div>
