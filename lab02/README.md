# Laboratório 2 - SO
## Questão A 
É viável discernir as partes do código realizadas pelo processo pai e pelo filho no exemplo citado. Quando o processo filho está em execução, isso é indicado pela cláusula else if (pid == 0), momento em que ele se identifica como tal e realiza a operação ls através do comando execlp. Em contrapartida, o processo pai é responsável pela seção dentro do último else, aguardando a finalização do processo filho com o uso de wait(NULL) e subsequente declaração de conclusão do processo filho.

## Questão B
No segundo exemplo apresentado, um total de oito processos é gerado. Isso se deve à propriedade de fork() de dobrar a quantidade de processos em execução a cada chamada. Assim, após três chamadas consecutivas a fork(), o número de processos aumenta progressivamente: de 1 para 2, depois de 2 para 4, e finalmente de 4 para 8.

# Console AWS

![image](https://github.com/KaduRosendo/Sistemas-operacionais/assets/100209440/3f7b0ad5-4219-49d0-b3d6-a6f914c6849f)



