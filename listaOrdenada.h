#include<stdio.h>
#include<stdlib.h>

typedef struct sDados
{
	int agente; 
	double custoRecurso;
    int custo; 
	
}Info;

typedef struct sLista{
    Info elemento;
    struct sLista * prox;
}LISTA;

void inicializarLista(LISTA **lista){
    (*lista)=NULL;
}

LISTA * criarCelula(){
    LISTA *nova=(LISTA*)malloc(sizeof(LISTA));
    nova->prox=NULL;
    return nova;
}
int listaVazia(LISTA ** lista){
    if((*lista)==NULL){
        return 1;
    }
    return 0;
}
int inserirNoInicio(Info elemento,LISTA **lista){
    //criando uma nova celula
    LISTA *nova=criarCelula();
    //configurando a nova celula da lista
    nova->elemento.custoRecurso=elemento.custoRecurso;
    nova->elemento.custo=elemento.custo;
    nova->elemento.agente=elemento.agente;
    
    nova->prox=NULL;
    //para inserir no inicio devemos verificar dois casos, o primeiro é quando a lista esta vazia e o segundo é quando já se tem elementos
    //caso 1
    if(listaVazia(lista)==1){
       // printf("aqio");
        (*lista)=nova;
        return 1;
    }
    //caso 2
    nova->prox=(*lista);
    (*lista)=nova;
    return 1;

}

int inserirNoFinal(LISTA ** lista,Info elemento){
    LISTA * nova=criarCelula();
    LISTA *aux;
    nova->elemento.custoRecurso=elemento.custoRecurso;
    nova->elemento.agente=elemento.agente;
    nova->elemento.custo=elemento.custo;
    
    if(listaVazia(lista)==1){
        (*lista)=nova;
        return 1;
    }
    aux=(*lista);
    while(aux->prox!=NULL){
        aux=aux->prox;
    }
    aux->prox=nova;
    return 1;
}
int inserirOrdenado(LISTA ** lista, Info elemento){
    LISTA *aux;
    LISTA *celAnterior;
    LISTA *nova=criarCelula();
    nova->elemento.custoRecurso=elemento.custoRecurso;
    nova->elemento.agente=elemento.agente;
    nova->elemento.custo=elemento.custo;
	if(listaVazia(lista)==1){
        //inserirNoFinal(lista,elemento);
        inserirNoInicio(elemento,lista);
        return 1;
    }
    aux=(*lista); 
    while(aux!=NULL){
        if(aux->elemento.custoRecurso<elemento.custoRecurso){
            break;
        }
        celAnterior=aux;
        aux=aux->prox;
    }
    
    if(aux==(*lista)){
        nova->prox=aux;
        (*lista)=nova;

    }else{
        nova->prox=aux;
        celAnterior->prox=nova;
    }

       
    return 1;
}

int inserirOrdenadoCusto(LISTA ** lista, Info elemento){
    LISTA *aux;
    LISTA *celAnterior;
    LISTA *nova=criarCelula();
    nova->elemento.custoRecurso=elemento.custoRecurso;
    nova->elemento.agente=elemento.agente;
    nova->elemento.custo=elemento.custo;
	if(listaVazia(lista)==1){
        //inserirNoFinal(lista,elemento);
        inserirNoInicio(elemento,lista);
        return 1;
    }
    aux=(*lista); 
    while(aux!=NULL){
        if(aux->elemento.custo<elemento.custo){
            break;
        }
        celAnterior=aux;
        aux=aux->prox;
    }
    
    if(aux==(*lista)){
        nova->prox=aux;
        (*lista)=nova;

    }else{
        nova->prox=aux;
        celAnterior->prox=nova;
    }

       
    return 1;
}


void imprimirLista(LISTA **lista){
    LISTA *aux=(*lista);
    while(aux!=NULL){
        printf("\nAgente %d com  custo recurso %.2f",aux->elemento.agente,aux->elemento.custoRecurso)	;
        aux=aux->prox;
       
    }

}





Info *  removerNoInicio(LISTA **lista){
    LISTA * aux;
    Info * elemento=(Info*)malloc(sizeof(Info));
    if(listaVazia(lista)==1){
        return 0;
    }
    elemento->agente=(*lista)->elemento.agente;
    elemento->custoRecurso=(*lista)->elemento.custoRecurso;
    aux=(*lista);
    (*lista)=(*lista)->prox;
    free(aux);
    return elemento;
}

