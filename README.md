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
./launcher2.sh & sudo python3 process_monitor3.py [PROCESS_NAME]
```
## Arquivos de saída

* [PROCESS_NAME.dat] - contendo as informações de tempo da amostras e recursos de hardware
* power.dat - contendo as coletas instantâneas do consumo de potência
* temperature.dat - contendo as informações de temperatura das CPUs

# [2] Módulo de monitoramento em GPU

# [3] Módulo de visualização - GraphCis

## URL do servidor

Por ser uma ferramenta web, o módulo de visualização GraphCis pode ser acessado pela URL ...

## Utilização

Resumo de como utilizar o GraphCis


## Conversão dos resultados para o formato json

Para converter os dados dos experimentos em CPU para serem visualizados no GraphCis, é preciso apenas executar o script "parse_json.sh".

```shell
./parse_json.sh
```
