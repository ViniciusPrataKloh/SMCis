# Sumário

* [1] Módulo de monitoramento em CPU
* [2] Módulo de monitoramento em GPU
* [3] Módulo de visualização - GraphCis


## Descrição
Para contornar as limitações encontradas nos sistemas de monitoramento convencionais foi desenvolvido o SMCis. Esse sistema tem o objetivo de ser uma ferramenta para o monitoramento de aplicações e visualização de dados experimentais, de fácil utilização, com altas taxas de amostragem e baixo impacto no consumo de recursos do sistema. A principal característica do SMCis é monitorar o consumo dos recursos pela aplicação em execução, permitindo relacionar graficamente o desempenho e consumo de recursos computacionais com o consumo de energia.

## Características

* Coletar o consumo dos recursos de hardware (utilização de CPU, memória, disco e rede)
* Coletar informações dos sensores internos (potência e temperatura)
* Visualização gráfica e dados salvos para análise

# [1] Módulo de monitoramento em CPU

## Dependências:

```shell
sudo apt-get install gcc python3-psutil freeipmi/ipmitool
```

## Download

Os arquivos podem ser baixados pelo link https://github.com/ViniciusPrataKloh/SMCis.git

## Utilização

Para monitorar uma aplicação com o módulo de CPU, é preciso utilizar o lançador de aplicações e em seguida executar o módulo, informando como parâmetro de entrada o nome da aplicação.
Utilizando dois Terminais:

```shell
./launcher.sh
```

```shell
sudo python3 process_monitor.py [PROCESS_NAME]
```

Ou utilizar apenas um Terminal com o comando:

```shell
./launcher2.sh & sudo python3 process_monitor.py [PROCESS_NAME]
```
## Arquivos de saída

* [PROCESS_NAME.dat] - contendo as informações de tempo da amostras e recursos de hardware
* power.dat - contendo as coletas instantâneas do consumo de potência
* temperature.dat - contendo as informações de temperatura das CPUs

# [2] Módulo de monitoramento em GPU

# [3] Módulo de visualização - GraphCis

## URL do servidor

Por ser uma ferramenta web, o módulo de visualização GraphCis pode ser acessado pela URL http://graphs-comcidis.surge.sh/#!/

## Utilização

Inicialmente, o usuário faz o upload do arquivo com os dados que deseja analisar e solicita abrir esse arquivo clicando no botão "open with GraphCis". Em seguida, especifica os requisitos do gráfico (Título, modelo e parâmetros que deseja associar ao eixo das abscissas e ordenadas) e clica no botão "Generate".

## Conversão dos resultados para o formato json

Atualmente GraphCis trabalha com arquivos de entrada somente no formato JSON.

Example of a json file:

```shell
[
   {"time": 0, "cpu0_temp": 27, "gpu0_temp": 31, "core0_usage": 0, "memory0_usage": 0, "total_power": 260}, 
   {"time": 2564, "cpu0_temp": 29, "gpu0_temp": 33, "core0_usage": 0, "memory0_usage": 0, "total_power": 396}, 
   {"time": 3026, "cpu0_temp": 29, "gpu0_temp": 33, "core0_usage": 0, "memory0_usage": 0, "total_power": 396}, 
   .
   .
   .
   {"time": 7678, "cpu0_temp": 38, "gpu0_temp": 36, "core0_usage": 70, "memory0_usage": 22, "total_power": 486}, 
   {"time": 9943, "cpu0_temp": 38, "gpu0_temp": 36, "core0_usage": 0, "memory0_usage": 0, "total_power": 462}, 
   {"time": 10374, "cpu0_temp": 31, "gpu0_temp": 33, "core0_usage": 0, "memory0_usage": 0, "total_power": 396} 
]
```

Para converter os dados dos experimentos em CPU para serem visualizados no GraphCis, é preciso apenas executar o script "parse_json.sh".

```shell
./parse_json.sh
```

## Nota
 
Para que o GraphCis coloque corretamente cada parâmetro em seu eixo, os que se referem a temperatura devem conter a palavra temp (como por exemplo cpu0_temp), os que se referem a energia devem conter a palavra power (como por exemplo total_power). Os que não tiverem essas identificações serão colocados no eixo de percentuais de utilização.

Por padrão, atualmente os parâmetros de temperatura são apresentados em graus Celsius, os de energia em Watts e os demais em percentuais de utilização.

