# Projeto 02 - Transferências de fundos entre contas

### Código

Nesse projeto, foi fornecido um código na documentação que faz transferência entre duas contas utilizando threads, mas ele continha uma falha devido a problemas de concorrência, especificamente, a ausência de sincronização adequada ao acessar o saldo das contas. Em um ambiente multi-threads, sem a devida proteção, múltiplas threads podem acessar e modificar as variáveis compartilhadas de maneira inconsistente, levando a resultados imprevisíveis ou incorretos. Para resolver o problema, utilizei um mecanismo de sincronização, o mutex, para garantir que apenas uma thread modifique o saldo das contas por vez.

