# Projeto 1 - Escada Rolante 

### 1- Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?

-Threads
No código revisado, a sincronização do acesso à escada rolante é alcançada através do controle da direção e do tempo de ocupação. A escada rolante opera em duas direções possíveis, e cada indivíduo tem uma direção desejada que deve coincidir com a direção atual para permitir o acesso. Quando um indivíduo acessa a escada, ele a ocupa por 10 unidades de tempo, refletido pelo ajuste na variável finalTime. Caso a direção desejada de um indivíduo não seja a mesma da escada no momento, ele espera até que a direção mude após o término do tempo de ocupação atual. Este gerenciamento assegura que em nenhum momento mais de uma pessoa utilize a escada simultaneamente, mantendo a operação segura e ordenada

-Processos

### 2- Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

-

### 3- Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta

-


## Execuções 
### Threads (E_1)

### Processos (E_1)



