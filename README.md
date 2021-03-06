# Sumário

* [1] Módulo de monitoramento em CPU
* [2] Módulo de monitoramento em GPU
* [3] Módulo de visualização - GraphCis

## Download

Os arquivos podem ser baixados pelo link https://github.com/ViniciusPrataKloh/SMCis.git

```shell
git clone https://github.com/ViniciusPrataKloh/SMCis.git
```

## Vídeo tutorial

Para auxiliar na utilização do SMCis foi desenvolvido um vídeo demonstrativo da ferramenta, disponível em https://youtu.be/0ueFhr6JvtM.

## Descrição
Para contornar as limitações encontradas nas ferramentas de monitoramento estudadas foi desenvolvido o SMCis, um sistema de monitoramento que possibilita a coleta dos parâmetros de desempenho e energia sobre a execução da aplicação em diferentes arquiteturas, com altas taxas de amostragem e baixo impacto no consumo de recursos computacionais. Além disso, possui fácil utilização e provê a visualização gráfica dos parâmetros relevantes simultaneamente.

## Características

* Coletar o consumo dos recursos de hardware (utilização de CPU, memória, disco e rede)
* Coletar informações dos sensores internos (potência e temperatura)
* Visualização gráfica e dados salvos para análise

## Dependências comuns

Os módulos de monitoramento coletam as informações dos sensores de potência e temperatura com o IPMItool. O mesmo pode ser instalado com o comando:

```shell
sudo apt-get install ipmitool
```

É necessário também configurar os sensores com os seguinte comando:

```shell
sudo modprobe ipmi_si && sudo modprobe ipmi_devintf && sudo modprobe ipmi_msghandler
```

## Importante

Como é necessária a permissão de sudo, é importante deixar a senha temporariamente salva, para que não seja preciso digitá-la a cada comando que necessite da permissão. Exemplo:

```shell
sudo -i
```

```shell
exit                                                  
```

# [1] Módulo de monitoramento em CPU

## Dependências:

```shell
sudo apt-get install gcc python3-psutil freeipmi/ipmitool
```

## Utilização

Para monitorar aplicações em CPU com o SMCis é preciso executar dois scripts: 'launcher.sh' e 'process_monitor.py'.

O 'launcher.sh' é responsável por executar a aplicação com as configurações de experimentos necessárias. Por exemplo, número de threads e intervalo para monitoramento do consumo estático do sistema.

Assim como em um escalonador, é preciso configurar as variáveis básicas no arquivo 'launcher.sh' com as informações:

* APP="nome da aplicação"
* NUM_THREADS="número de threads"
* BIN="comando para executar a aplicação"

O 'process_monitor.py' é responsável pelo monitoramento da aplicação, e para seu funcionamento é necessário passar como parâmetos o nome da aplicação a ser monitorada e a interface de rede.

Para listar as interfaces de rede ativas, pode ser utilizado o comando:

```shell
ifconfig -a
```

O monitoramento pode ser realizado utilizando dois Terminais, sendo um para executar cada script:

```shell
./launcher.sh
```

```shell
sudo python3 cpu_monitoring_module.py <nome da aplicação> <nome da interface de rede>
```

Ou utilizando apenas um Terminal com o comando:

```shell
./launcher.sh & sudo python3 cpu_monitoring_module.py <nome da aplicação> <nome da interface de rede>
```

Obs: O launcher deve sempre iniciar a execução antes do módulo de monitoramento.

## Arquivos de saída

* [nome_da_aplicação.dat] - contendo as informações de tempo e consumo dos recursos de hardware.
* power.dat - contendo as coletas instantâneas do consumo de potência.
* temperature.dat - contendo as informações de temperatura das CPUs.
* [start_end.dat] - contendo os horários de início e fim da execução da aplicação.

# [2] Módulo de monitoramento em GPU

## Dependências

Instalação do CUDA Toolkit que pode ser baixado pelo link https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&target_distro=Ubuntu&target_version=1604.

## Utilização

Para monitorar aplicações em GPU com o SMCis, também é preciso executar dois scripts: 'launcher.sh' e 'gpu_monitoring_module.sh'.

No 'launcher.sh' é necessário configurar as seguintes variáveis:

* APP="nome da aplicação"
* BIN="comando para executar a aplicação"

O script 'GPU_monitor.cu' precisa ser compilado pois é utilizado pelo 'gpu_monitoring_module.sh':

```shell
/usr/local/cuda-8.0/bin/nvcc -o GPU_monitor GPU_monitor.cu -lnvidia-ml
```

O monitoramento pode ser realizado com os comandos:

```shell
./launcher.sh
```

```shell
./gpu_monitoring_module.sh > output.dat
```

## Arquivo de saída

* output.dat - contendo todas as informações referentes ao monitoramento da aplicação.

# [3] Módulo de visualização - GraphCis

## URL do servidor

Por ser uma ferramenta web, o módulo de visualização GraphCis pode ser acessado pela URL http://graphs-comcidis.surge.sh/#!/

## Utilização

Inicialmente, o usuário faz o upload do arquivo com os dados que deseja analisar e solicita abrir esse arquivo clicando no botão "open with GraphCis". Em seguida, especifica os requisitos do gráfico (Título, modelo e parâmetros que deseja associar ao eixo das abscissas e ordenadas) e clica no botão "Generate".

## Conversão dos resultados para o formato json

Atualmente GraphCis trabalha com arquivos de entrada somente no formato JSON.

Examplo de um arquivo json:

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

Para converter os dados dos experimentos em CPU para serem visualizados no GraphCis, é preciso apenas executar o script "parse_json_CPU.sh".

```shell
./parse_json_CPU.sh <nome da aplicação.dat> <power.dat> <temperature.dat>
```

Para converter os dados do monitoramento em GPU, é preciso executar o script 'parse_json_GPU.cpp'.

O script pode ser compilado e executado com os comandos:

```shell
g++ -o parse_json_GPU parse_json_GPU.cpp
```

```shell
./parse_json_GPU output.dat
```

## Nota
 
Para que o GraphCis coloque corretamente cada parâmetro em seu eixo, os que se referem a temperatura devem conter a palavra temp (como por exemplo cpu0_temp), os que se referem a energia devem conter a palavra power (como por exemplo total_power). Os que não tiverem essas identificações serão colocados no eixo de percentuais de utilização.

Por padrão, atualmente os parâmetros de temperatura são apresentados em graus Celsius, os de energia em Watts e os demais em percentuais de utilização.

