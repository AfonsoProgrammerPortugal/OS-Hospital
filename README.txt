
## Grupo SO-024
Afonso Santos - fc59808
Madalena Machado - fc59858
Liliana Valente - fc59846

## Projeto:
O objetivo geral do projeto será o desenvolvimento de uma aplicação em C, chamada hOSpital, para simular a
admissão e o atendimento de pacientes de um hospital. Esta aplicação permitirá aos pacientes fazerem a admissão
com os rececionistas do hospital e realizarem as consultas com os médicos do mesmo. Esta aplicação envolverá
múltiplos processos cooperativos para efetuar as suas operações. O fluxo de chamadas entre processos envolve: (i) a
admissão do paciente junto a um rececionista do hospital, (ii) o encaminhamento dos pacientes para a sala de espera
dos médicos e (iii) o atendimento médico dos pacientes. De forma a se poder aferir a qualidade do serviço prestado,
são também registadas informações de progresso sob a forma de um log, que podem posteriormente ser analisadas.

## Notas:
O projeto corre normalmente fazendo os comandos "cd bin" -> "./hOSpital config.txt",
mas dá Segmentation fault (core dumped) quando corre com o comando 
"./bin/hOSpital config.txt".

## Limitações na implementação do projeto:
A info das admissions começa a falhar quanto mais forem adicionadas

## O que aprendi:
- Conhecimento geral da linguagem C;
- Utilização dos recursos de um Sistema Operativo, como processos/threads, escalonador, sincronização, deadlocks, alarmes, semáforos, etc.
- Debugging de um Sistema Operativo
