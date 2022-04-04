#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT 10  // valor fixo para a opção que finaliza a aplicação

//Struct que representa a data.
typedef struct {
	int dia;
	int mes;
} Date;

struct REC {
       char nome[50];
       int prioridade;
       Date entrega; 
	  struct REC *next;
};
typedef struct REC Task;

typedef struct listaTask{
    Task task;
    struct listaTask *proximo;
} ListaTask;

typedef struct listaToDo{
     ListaTask *topo;
} ListaToDo;

void iniciaLista(ListaToDo *listaToDo){
     listaToDo->topo = NULL;
     FILE *arquivoLeitura = fopen("listaToDo.txt", "r");
     if(arquivoLeitura == NULL){
          printf("Um arquivo com o nome listaToDo.txt foi criado\n");
          FILE *arqNovo = fopen("listaToDo.txt", "w");
          if(arqNovo == NULL){
               printf("Não foi possível criar o arquivo!\n");
          }else {
               fclose(arqNovo);
          }
     }else {
          int numeroTaksArquivo;
          fscanf(arquivoLeitura, "%d\n", &numeroTaksArquivo);
          for (int i = 0; i < numeroTaksArquivo; i++){
               Task item;
               fscanf(arquivoLeitura, "%s\n%d\n%d\n%d\n", &item.nome, &item.prioridade, &item.entrega.dia, &item.entrega.mes);
               inserirTask(listaToDo, item);
          }
          fclose(arquivoLeitura);
     }
}

int isDuplicada(ListaToDo *listaToDo, Task taskCadastrar){
     ListaTask *next, *atual;
     atual = listaToDo->topo;
     while(atual != NULL){
          next = atual->proximo;
          if(strcmp(atual->task.nome, taskCadastrar.nome) == 0){
               return 1;
          }
          atual = next;
     }  
     return 0;
}

void inserirTask(ListaToDo *listaToDo, Task taskCadastrar){
     ListaTask *aux;
     int duplicada = isDuplicada(listaToDo, taskCadastrar);
     if(duplicada){
          printf("Task já cadastrada\n");
          return;
     }else {
          aux = malloc(sizeof(ListaTask));
          aux->task = taskCadastrar;
          aux->proximo = listaToDo->topo;
          listaToDo->topo = aux;
     }
}

void deletaTaskByNome (Task itemApagar, ListaToDo *listaTopo){
     ListaTask *atual, *anteriorExcluir;
     atual = listaTopo->topo->proximo;
     anteriorExcluir = listaTopo->topo;
     if(atual == NULL){
        listaTopo->topo = NULL;
        return;
     }else {
          while (atual != NULL){
               //condicao especial para excluir do inicio
               if(strcmp(itemApagar.nome, listaTopo->topo->task.nome) == 0){
                    //exclui o primeiro
                    Task *aux;
                    aux = listaTopo->topo;
                    listaTopo -> topo = listaTopo->topo->proximo;
                    free(aux);
                    return;
               }else if(strcmp(itemApagar.nome, atual->task.nome) == 0){
                    if(atual->proximo == NULL){
                         //apaga o ulimo
                         anteriorExcluir->proximo = NULL;
                         free(atual);
                         return;
                    }else{
                         //apaga do meio
                         anteriorExcluir->proximo = atual ->proximo;
                         free(atual);
                         return;
                    }

               }else{
                    anteriorExcluir = anteriorExcluir -> proximo;
                    atual = atual -> proximo;
               }
          }
     }
}

// Lista o conteudo da lista de tarefas (todos os campos)
void listaTaskCadastradas (ListaToDo *lista){
     ordenar(lista);
     ListaTask *next, *atual;
     atual = lista->topo;
     while (atual != NULL) {
          next = atual->proximo;
          printf("Nome: %s\n", atual->task.nome);
          printf("Prioridade: %d\n", atual->task.prioridade);
          printf("Data de entrega: %d/%d\n", atual->task.entrega.dia, atual->task.entrega.mes);
          printf("___________________\n");
          atual = next;
     }
}

// Permite consultar uma tarefa da lista pelo nome
void buscaTaskCadastrada (Task item, ListaToDo *listaToDo){
     ListaTask *next, *atual;
     atual = listaToDo->topo;
     while (atual != NULL) {
          next = atual->proximo;
          if(strcmp(atual->task.nome, item.nome) == 0){
               printf("Nome: %s\n", atual->task.nome);
               printf("Quantidade: %d\n", atual->task.prioridade);
               printf("Imprimie a data la");
               printf("___________________\n");
               return;
          }
          atual = next;
    }
    printf("Bebida não cadastrada!\n");
     return;
}

// Permite a atualização dos dados de uma tarefa
//atualizar data e prioridade
void atualizaTask (Task item, ListaToDo *listaToDo){
     ListaTask *next, *atual;
     atual = listaToDo->topo;
     while(atual != NULL){
          next = atual->proximo;
          if(strcmp(atual->task.nome, item.nome) == 0){
               printf("Nova Prioridade: ");
               scanf("%d", &atual->task.prioridade);
               printf("Nova data no formato Dia/Mes: ");
               scanf("%d/%d", &atual->task.entrega.dia, &atual->task.entrega.mes);
               return;
          }
          atual = next;
     }  
     printf("Tarefa buscada não existe\n");
     return;
}

void ordenar(ListaToDo *lista) {
     if(lista == NULL) {
          printf("Lista vazia\n");
          return;
     } 
     ListaTask *aux = lista->topo, *prox;
     char s[50];
     int diaAux, mesAux, prioridadeAux;
     while(aux != NULL) {
          prox = aux->proximo;
          while(prox != NULL) {
               if(strcmp(aux->task.nome, prox->task.nome) > 0) { //se vir depois
                    //passa o nome
                    strcpy(s, aux->task.nome);
                    strcpy(aux->task.nome, prox->task.nome);
                    strcpy(prox->task.nome, s);
                    //passa o dia
                    diaAux = aux->task.entrega.dia;
                    aux->task.entrega.dia = prox->task.entrega.dia;
                    prox->task.entrega.dia = diaAux;
                    //passa o mes
                    mesAux = aux->task.entrega.mes;
                    aux->task.entrega.mes = prox->task.entrega.mes;
                    prox->task.entrega.mes = mesAux;
                    //passa a prioridade
                    prioridadeAux = aux->task.prioridade;
                    aux->task.prioridade = prox->task.prioridade;
                    prox->task.prioridade = prioridadeAux;
               }
               prox = prox->proximo;
          }
          aux = aux->proximo;
    }
}

int contaItensLista(ListaToDo *lista){
     int contador = 0;
     ListaTask *atual;
     atual = lista->topo;
     while(atual != NULL) {
          contador ++;
          atual = atual->proximo;
     }
     return contador;
}

void gravaListaNumArquivo(ListaToDo *lista){
     FILE *arq = fopen("listaToDo.txt", "w");
     if(arq == NULL){
          printf("Não foi possível criar o arquivo!");
     }
     int numeroItensGravar = contaItensLista(lista);
     fprintf(arq, "%d\n", numeroItensGravar);
     ListaTask *atual;
     atual = lista->topo;
     while(atual != NULL) {
          fprintf(arq, "%s\n%d\n%d\n%d\n", atual->task.nome, atual->task.prioridade, atual->task.entrega.dia, atual->task.entrega.mes);
          atual = atual->proximo;
     }
     fclose(arq);
}

// Programa principal
int main(){
     int op=0;
     ListaToDo lista;
     Task item;
     iniciaLista(&lista);

     while (op!=EXIT){
          printf("Escolha uma opção:\n");
          printf("1 para INSERIR uma task.\n");
          printf("2 para DELETAR uma task pelo nome\n");
          printf("3 para EDITAR a prioridade e data de uma task\n");
          printf("4 para BUSCAR uma task especifica\n");
          printf("5 para LISTAR as tarefas\n");
          printf("%d para SAIR.\n", EXIT);
          scanf("%d",&op);
          switch(op){
               case 1 : 
                    printf("Nome da task: ");
                    scanf("%s", item.nome);
                    printf("Prioridade: ");
                    scanf("%d", &item.prioridade);
                    printf("Insira a data no padrao Dia/Mes: ");
                    scanf("%d/%d", &item.entrega.dia, &item.entrega.mes);
                    if(item.entrega.dia > 31 || item.entrega.mes > 12){
                         printf("A task não foi adicionada. Data invalida.\n");
                    }else{
                         inserirTask(&lista, item);
                    }
                    break;
               case 2 : 
                    printf("Nome da task para deletar: ");
                    scanf("%s", item.nome);
                    deletaTaskByNome(item, &lista);
                    break;
               case 3 : 
                    printf("Nome da task para editar: ");
                    scanf("%s", item.nome);
                    atualizaTask(item, &lista);
                    break;
               case 4 : 
                    printf("Nome da Buscada: ");
                    scanf("%s", item.nome);
                    buscaTaskCadastrada(item, &lista);
                    break;
               case 5 : 
                    listaTaskCadastradas(&lista);
                    break;
          }
    }
    gravaListaNumArquivo(&lista);
    return 0;
}
