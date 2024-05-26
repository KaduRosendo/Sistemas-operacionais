# Projeto 02 - Transferências de fundos entre contas

## Código

Nesse projeto, foi fornecido um código na documentação que faz transferência entre duas contas utilizando threads, mas ele continha uma falha devido a problemas de concorrência, especificamente, a ausência de sincronização adequada ao acessar o saldo das contas. Em um ambiente multi-threads, sem a devida proteção, múltiplas threads podem acessar e modificar as variáveis compartilhadas de maneira inconsistente, levando a resultados imprevisíveis ou incorretos. 

Para resolver o problema, utilizei um mecanismo de sincronização, o mutex, para garantir que apenas uma thread modifique o saldo das contas por vez.

O código define duas contas (from e to), cada uma com saldo inicial de 100. São criadas duas funções de transferência: `transferFROM`, que transfere de from para to, e `transferTO`, que faz o oposto. Ambas utilizam mutexes para sincronização, assegurando que uma transferência ocorra de cada vez.

No main, 100 threads são criadas: 50 para cada função de transferência, permitindo múltiplas operações simultâneas. O mutex garante consistência e segurança nas operações de saldo, e as threads são sincronizadas com `pthread_join` para assegurar a conclusão das transferências. O código verifica o saldo antes de cada transferência, evitando operações inválidas.
Assim, o código permite múltiplas transferências simultâneas, garante que não se faça uma transferência sem saldo suficiente, e demonstra a troca de papéis entre as contas


## Requisitos
1- A conta TO pode recerber mais de uma tranferência simultânea:

Implementação: Mesma implementação da imagem abaixo

Resultado:

![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/880be43f-fef2-473c-a02e-321541be6f8a)


2- A conta FROM pode enviar mais de uma trasferência simultânea:

Implementação:
![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/9a2f7c48-2c3b-47e8-be64-40d4fa83541e)
Resultado: 

![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/f78134db-a8a1-4bbb-a70c-50f18ad42329)


3- A conta FROM não pode enviar dinheiro se não tiver mais saldo;

Implementação:
![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/c21b7547-a0ed-4c7c-9db6-1c7c4c556c43)
Resultado:![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/0f1af849-4854-40a4-a7cb-d41599544946)


4- A conta TO pode trocar de ordem com a conta FROM, ou seja, a conta que recebia pode enviar:

Implementação:
![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/28c5e775-30a6-4f7f-a1c6-fb0abfde7e70)
Resultado:

![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/7ee89eab-397b-4367-90fe-19ef44965557)


5- Poderão ser realizadas até 100 transações simultâneas de tranferência:

Implementação:
![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/ae79eb4d-756f-47f5-80a1-90ebec85358d)
Resultado:

![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/f845bfb2-9998-4f3a-992e-8ed5e576463b)
![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/124835c6-3b81-48f6-9e3d-39fbc66ba792)
![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/eba9fbcd-b819-427b-b302-743aa8ecea89)
![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/0321c13c-cc48-486f-9420-d86dafceed96)
![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/6915aeb5-5fda-4b44-b661-8206e760bac6)
![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/357a8626-de83-4146-882d-a0efd047cbff)




