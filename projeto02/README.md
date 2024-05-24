# Projeto 02 - Transferências de fundos entre contas

## Código

Nesse projeto, foi fornecido um código na documentação que faz transferência entre duas contas utilizando threads, mas ele continha uma falha devido a problemas de concorrência, especificamente, a ausência de sincronização adequada ao acessar o saldo das contas. Em um ambiente multi-threads, sem a devida proteção, múltiplas threads podem acessar e modificar as variáveis compartilhadas de maneira inconsistente, levando a resultados imprevisíveis ou incorretos. 

Para resolver o problema, utilizei um mecanismo de sincronização, o mutex, para garantir que apenas uma thread modifique o saldo das contas por vez.

O código define duas contas (from e to), cada uma com saldo inicial de 100. São criadas duas funções de transferência: transferFROM, que transfere de from para to, e transferTO, que faz o oposto. Ambas utilizam mutexes para sincronização, assegurando que uma transferência ocorra de cada vez.

No main, 100 threads são criadas: 50 para cada função de transferência, permitindo múltiplas operações simultâneas. O mutex garante consistência e segurança nas operações de saldo, e as threads são sincronizadas com pthread_join para assegurar a conclusão das transferências. O código verifica o saldo antes de cada transferência, evitando operações inválidas.
Assim, o código permite múltiplas transferências simultâneas, garante que não se faça uma transferência sem saldo suficiente, e demonstra a troca de papéis entre as contas


## Requisitos
1- A conta TO pode recerber mais de uma tranferência simultânea:

Implementação no código:

![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/9a2f7c48-2c3b-47e8-be64-40d4fa83541e)

2- A conta FROM pode enviar mais de uma trasferência simultânea:

3- A conta FROM não pode enviar dinheiro se não tiver mais saldo;

4- A conta TO pode trocar de ordem com a conta FROM, ou seja, a conta que recebia pode enviar:

5- Poderão ser realizadas até 100 transações simultâneas de tranferência:


