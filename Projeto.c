#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include "listaOrdenada.h"
//#include "funcoesGulosa.h"

//srand((unsigned) time(NULL));
	
typedef struct sTarefa{
	LISTA * prtlist; 
}tarefa;

int taref;
	
int retornaAgente(tarefa * listaTarefas, int numTarefa)
{
	Info *elemento; 
	//imprimirLista(&listaTarefas[numTarefa].prtlist);
	elemento = removerNoInicio(&listaTarefas[numTarefa].prtlist);
	
	return elemento->agente; 
}


int sorteador(int limite)
{	
	//int sorteado = (rand()% limite);
	int sorteado =  (rand()% limite+1);
    return sorteado; 
}

void criarMatrizBin(tarefa * listaTarefas, int matrizBinaria[][taref], int matrizRecurso[][taref],int *capacidadeAgente, int agentes, int tarefas)
{

	int  j, k,  cont =0; 
	int recursoGasto[agentes];
    for(j=0;j<agentes;j++)
		{
            recursoGasto[j]=0;
        }
		
		for(j=0;j<tarefas;j++)
		{
				cont =0;
				while(cont<agentes)
				{
					
					k=retornaAgente(listaTarefas,j);
					
					if(capacidadeAgente[k]>=recursoGasto[k]+matrizRecurso[k][j])
					{
						recursoGasto[k]+=matrizRecurso[k][j];
						matrizBinaria[k][j]= 1;
						break;
					}
					cont ++ ;
				}
		}
}


void binaria(int*vetor, int matriz[][taref], int agentes, int tarefas)
{
	int i, j, aux; 
	for(i=0;i<agentes;i++)
	{
		for(j=0;j<tarefas;j++)
		{			
			matriz[i][j]=0;
		}
	}	
	
	for(j=0;j<tarefas;j++)
	{
		aux= vetor[j];
		matriz[aux-1][j] = 1;
		//matriz[vetor[j]-1][j] = 1;

	}
}

int funcaoObjetivo(int agentes,int tarefas, int matrizBinaria[][taref], int matrizCusto[][taref])
{
 	int i, j, funcaoObj = 0;
 	for(i=0;i<agentes;i++)
	{
		for(j=0;j<tarefas;j++)
		{
			if(matrizBinaria[i][j]==1)
			{
				funcaoObj += matrizCusto[i][j];
			}
			
		}
	}
	//printf("TESTEEE: %d \n",funcaoObj);	
 	return funcaoObj;
 	
}


int verificarecurso(int*vetor ,int matrizBinaria[][taref], int recurso[][taref],  int agentes, int tarefas, int * capacidadeAg )
{
	int i, j, extrapolou, capacidadecorrente[agentes]; 
	extrapolou = 0;
	for(i=0;i<agentes;i++)
	{
		capacidadecorrente[i]=0;
	}

	for(i=0;i<agentes;i++)
	{
		for(j=0;j<tarefas;j++)
		{
			if(matrizBinaria[i][j]==1)
			{
				capacidadecorrente[i] += recurso[i][j];
				//funcaoObj += matrizCusto[i][j];
			}
			
		}
	}



	/*for(j=0;j<tarefas;j++)
	{			
		capacidadecorrente[vetor[j]-1] += recurso[vetor[j]-1][j]; 
	}*/
	for(j=0;j<agentes;j++)
	{	
		if(capacidadecorrente[j]<=capacidadeAg[j])
		{
			//printf("Capacidade Corrente Agente %d = %d || Capacidade Total Agente %d = %d \n",j,capacidadecorrente[j],j,capacidadeAg[j]);
			extrapolou = 1; 
		}
		else
		{
			//printf("Capacidade Corrente Agente %d = %d || Capacidade Total Agente %d = %d \n",j,capacidadecorrente[j],j,capacidadeAg[j]);
			extrapolou = 0;
			//break;
		}		
		
	}
		
	
	return extrapolou; 
}









/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////// FUNÇÕES PARA GULOSA ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int descidaPrimeiroTroca(int * vetorSolucaoDescida, int solucaoAleatoria,  int agentes,int  tarefas, int matrizCusto[][taref], int matrizRecurso[][taref], int * capacidadeAgen)
{
	int melhorCorrente = solucaoAleatoria, melhorou = 0, solucaoCorrente = 0,  i, j, aux, matrizBinariaGerada[agentes][tarefas];
	int funcaoObTroca = 0; 
	int verificaExtrapolacao;
	for(i=0;i<agentes;i++)
	{
		for(j=0;j<tarefas;j++)
		{			
			matrizBinariaGerada[i][j]=0;
		}
	}

	do
	{
		melhorou = 0; 
		for(i=0;i<tarefas-1;i++)
		{
			for(j=1;j<tarefas;j++)
			{
				if(vetorSolucaoDescida[i]!=vetorSolucaoDescida[j])
				{
					aux = vetorSolucaoDescida[i];				
					vetorSolucaoDescida[i]=vetorSolucaoDescida[j];
					vetorSolucaoDescida[j]=aux;
					binaria(vetorSolucaoDescida,matrizBinariaGerada,agentes,tarefas);
					//verificaExtrapolacao = verificarecurso(vetorSolucaoDescida,matrizBinariaGerada,matrizRecurso,agentes,tarefas,capacidadeAgen);
					//if(verificaExtrapolacao == 1)
					//{
						funcaoObTroca = funcaoObjetivo(agentes,tarefas,matrizBinariaGerada,matrizCusto);
						//printf("\n\nAleatoria %d - Troca %d \n\n",solucaoAleatoria,funcaoObTroca );
						//printf("Entrando no if SE E MENOR\n");
						if(funcaoObTroca<melhorCorrente)
						{
							//printf("Entrou no if de menor @@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
							melhorCorrente = funcaoObTroca;
							melhorou = 1;
							break;
						}
						else
						{
							//printf("Entrou 2 \n");
							aux = vetorSolucaoDescida[i];				
							vetorSolucaoDescida[i]=vetorSolucaoDescida[j];
							vetorSolucaoDescida[j]=aux;
							binaria(vetorSolucaoDescida,matrizBinariaGerada,agentes,tarefas);	
						}
					/*}
					else
					{
						//printf("Extrapola\n");
						//break;
						aux = vetorSolucaoDescida[i];				
						vetorSolucaoDescida[i]=vetorSolucaoDescida[j];
						vetorSolucaoDescida[j]=aux;
						//binaria(vetorSolucaoDescida,matrizBinariaGerada,agentes,tarefas);	
					}		*/			
					
				}
			
			}
			if(melhorou == 1)
			{
				break;
			}

		}
		break;
		
	}while(melhorou!=1);

	return melhorCorrente; 

}






int descidaCompletaTroca(int * vetorSolucaoDescida, int solucaoAleatoria,  int agentes,int  tarefas, int matrizCusto[][taref], int matrizRecurso[][taref], int * capacidadeAgen)
{
	int melhorCorrente = solucaoAleatoria, melhorou = 0, solucaoCorrente = 0,  i, j, aux, matrizBinariaGerada[agentes][tarefas];
	int funcaoObTroca = 0; 

	int posI = 0, posJ = 0;
	for(i=0;i<agentes;i++)
	{
		for(j=0;j<tarefas;j++)
		{			
			matrizBinariaGerada[i][j]=0;
		}
	}

	do
	{
		melhorou = 0; 
		for(i=0;i<tarefas-1;i++)
		{
			for(j=1;j<tarefas;j++)
			{
				if(vetorSolucaoDescida[i]!=vetorSolucaoDescida[j])
				{
					aux = vetorSolucaoDescida[i];				
					vetorSolucaoDescida[i]=vetorSolucaoDescida[j];
					vetorSolucaoDescida[j]=aux;
					binaria(vetorSolucaoDescida,matrizBinariaGerada,agentes,tarefas);
                    funcaoObTroca = funcaoObjetivo(agentes,tarefas,matrizBinariaGerada,matrizCusto);
                    if(funcaoObTroca<melhorCorrente)
                    {
                        //printf("Entrou no if de menor @@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
                        melhorCorrente = funcaoObTroca;
                        posI = i;
                        posJ = j; 
                        melhorou = 1;
                        
                    }
                    else
                    {
                        //printf("Entrou 2 \n");
                        aux = vetorSolucaoDescida[i];				
                        vetorSolucaoDescida[i]=vetorSolucaoDescida[j];
                        vetorSolucaoDescida[j]=aux;
                        //binaria(vetorSolucaoDescida,matrizBinariaGerada,agentes,tarefas);	
                    }
					
				}
	
								
			}
			if(melhorou == 1)
			{
				aux = vetorSolucaoDescida[posI];				
				vetorSolucaoDescida[posI]=vetorSolucaoDescida[posJ];
				vetorSolucaoDescida[posJ]=aux;
			}

		}
		break;
		
	}while(melhorou!=1);

	return melhorCorrente; 

}



int VND(int * vetorInicial, int solAleatoria, int agentes, int tarefas,int matrizCusto[][taref],int matrizRecurso[][taref], int * capacidadeAg)
{

	int k = 0, r = 2, solCorrente, i, vetorCorrente[tarefas], matrizBinariaGerada[agentes][tarefas]; 
	int melhorSolucao = solAleatoria; 

	while(k<r)
	{
		if(k==0)
		{
			


			//solCorrente = descidaPrimeiroTroca(vetorInicial,melhorSolucao,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAg); //funcaoObjetivo(agentes,tarefas,matrizBin,matrizCusto);
			solCorrente = descidaCompletaTroca(vetorInicial,melhorSolucao,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAg); 

			if(solCorrente<melhorSolucao)
			{
				melhorSolucao=solCorrente;
				k=0; 
			}
			else
			{
				k++; 
			}
			

		}
		if(k==1)
		{
			solCorrente = descidaPrimeiroTroca(vetorInicial,melhorSolucao,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAg);
			//solCorrente = descidaCompletaTroca(vetorInicial,melhorSolucao,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAg); 
			if(solCorrente<melhorSolucao)
			{
				melhorSolucao= solCorrente;
				k=0; 
			}
			else
			{
				k++; 
			}
		}
		
	} 

	return melhorSolucao; 
} 

void pertubacao(int * vetorsolucao, int * capacidadeAgen, int matrizCusto[][taref], int matrizRecurso[][taref],int agentes,  int tarefas)
{
    int custoAtual = 0, i,j, custoCorrente=0, posicao, verificao, veri = 1; 
    int matrizBinariaGerada[agentes][tarefas];

  /*  while(veri !=0)
    {
        for(i=0;i<agentes;i++)
        {
            for(j=0;j<tarefas;j++)
            {			
                matrizBinariaGerada[i][j]=0;
            }
        }*/


        srand((unsigned) time(NULL));
        int sorteado = sorteador(tarefas);
        custoAtual=matrizCusto[vetorsolucao[sorteado-1]][sorteado-1]; 
        //printf("Custo Atual: %d\n ",custoAtual);
        for(i=0;i<agentes;i++)
        {
            if(matrizCusto[i][sorteado-1]<custoAtual)
            {
                custoAtual = matrizCusto[i][sorteado-1];
                posicao = i; 
            }
        }
        vetorsolucao[sorteado-1]=posicao+1;
        //printf("Menor: %d\n",custoAtual); 
       /* binaria(vetorsolucao,matrizBinariaGerada,agentes,tarefas);
        verificao = verificarecursoG(vetorsolucao,matrizBinariaGerada,matrizRecurso,agentes,tarefas,capacidadeAgen);
        if(verificao == agentes)
        {
            veri = 0; 
        }
        else
        {
            veri = 1; 
        }
    }*/
    
	
}

int ILS(int * vetorInicial,int solAleatoria,int agentes, int tarefas,int matrizCusto[][taref],int matrizRecurso[][taref], int * capacidadeAg, int iterMax)
{
	int solucaoVND = VND(vetorInicial,solAleatoria,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAg);
	int iter = 0, melhorFo, menor = solucaoVND, posicao = 0;
	int vetorFOSolucao[iterMax], i; 
	int solucoes[iterMax][tarefas];
	
	

	while(iter<iterMax)
	{
		//iter++; 
		////PERTUBAÇÃOOOOOO
        pertubacao(vetorInicial,capacidadeAg,matrizCusto,matrizRecurso,agentes,tarefas);
		vetorFOSolucao[iter]=VND(vetorInicial,solAleatoria,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAg);
		for(i=0;i<tarefas;i++)
		{
			solucoes[iter][i]= vetorInicial[i];
		}
        iter++; 
	}
	for(i=0;i<iterMax;i++)
	{
		if(vetorFOSolucao[i]<menor)
		{
			menor = vetorFOSolucao[i];
			posicao = i;
		}
        else
        {
            printf("Não gerou menor solucao que a VND\n");
        }
        
	}
	for(i=0;i<tarefas;i++)
	{
		vetorInicial[i]=solucoes[posicao][i]; 
	}
	melhorFo = vetorFOSolucao[posicao]; 


	return melhorFo; 
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////// FUNÇÕES PARA GULOSA ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int verificarecursoG(int*vetor ,int matrizBinaria[][taref], int recurso[][taref],  int agentes, int tarefas, int * capacidadeAg )
{
	int i, j, extrapolou, capacidadecorrente[agentes]; 
	extrapolou = 0;
	for(i=0;i<agentes;i++)
	{
		capacidadecorrente[i]=0;
	}

	for(i=0;i<agentes;i++)
	{
		for(j=0;j<tarefas;j++)
		{
			if(matrizBinaria[i][j]==1)
			{
				capacidadecorrente[i] += recurso[i][j];
			}
			
		}
	}



	for(j=0;j<agentes;j++)
	{	
		if(capacidadecorrente[j]<=capacidadeAg[j])
		{
			extrapolou++; 
		}
		else
		{
			extrapolou--;
		}		
		
	}
		
	
	return extrapolou; 
}
void pertubacaoG(tarefa * listaTarefas,int * vetorsolucao, int * capacidadeAgen, int matrizCusto[][taref], int matrizRecurso[][taref],int agentes,  int tarefas)
{
    int custoAtual = 0, i,j, custoCorrente=0, posicao, verificao, veri = 1, t = 0; 
    int matrizBinariaGerada[agentes][tarefas], k;

    do
    {
        for(i=0;i<agentes;i++)
        {
            for(j=0;j<tarefas;j++)
            {			
                matrizBinariaGerada[i][j]=0;
            }
        }


        srand((unsigned) time(NULL));
        int sorteado = sorteador(tarefas);
        custoAtual=matrizCusto[vetorsolucao[sorteado-1]][sorteado-1]; 
        //k=retornaAgente(listaTarefas,sorteado-1);
        /*while(t!=1)
        {
            t = 0;
            k=retornaAgente(listaTarefas,i);
            if(matrizCusto[vetorsolucao[k]][sorteado-1]<custoAtual)
            {
                custoAtual = matrizCusto[vetorsolucao[k]][sorteado-1];
                posicao = i; 
                //vetorsolucao[sorteado]=k+1;
                t=1; 
            }
            else
            {
                t=0;
            }
            
             
            
        }
        */
        for(i=0;i<agentes;i++)
        {
            k=retornaAgente(listaTarefas,i);
            if(matrizCusto[vetorsolucao[k]][sorteado-1]<custoAtual)
            {
                custoAtual = matrizCusto[vetorsolucao[k]][sorteado-1];
                posicao = i; 
                //vetorsolucao[sorteado]=k+1;
            }
        }
        vetorsolucao[sorteado]=posicao+1;
       //printf("Custo Atual: %d\t ",custoAtual);
      /*  for(i=0;i<agentes;i++)
        {
            if(matrizCusto[i][sorteado-1]<custoAtual)
            {
                custoAtual = matrizCusto[i][sorteado-1];
                posicao = i; 
            }
        }
        vetorsolucao[sorteado]=posicao+1;*/
        //printf("Menor: %d\n",custoAtual); 
        binaria(vetorsolucao,matrizBinariaGerada,agentes,tarefas);
        //printf("\nChega aqui 1 ");
        verificao = verificarecursoG(vetorsolucao,matrizBinariaGerada,matrizRecurso,agentes,tarefas,capacidadeAgen);
        // printf("\nChega aqui 2 \n");
        if(verificao == agentes)
        {
            veri = 0; 
             //printf("\n @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ DEUUUUUUUU @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ");

        }
        else
        {
           // printf("\nExtrapola\n ");
            veri = 1; 
        }
    } while(veri !=0);
    
	
}





int descidaPrimeiroTrocaG(int * vetorSolucaoDescida, int solucaoAleatoria,  int agentes,int  tarefas, int matrizCusto[][taref], int matrizRecurso[][taref], int * capacidadeAgen)
{
	int melhorCorrente = solucaoAleatoria, melhorou = 0, solucaoCorrente = 0,  i, j, aux, matrizBinariaGerada[agentes][tarefas];
	int funcaoObTroca  = solucaoAleatoria; 
	int verificaExtrapolacao;


	do
	{
		melhorou = 0; 
		for(i=0;i<tarefas-1;i++)
		{
			for(j=1;j<tarefas;j++)
			{
				if(vetorSolucaoDescida[i]!=vetorSolucaoDescida[j])
				{
					aux = vetorSolucaoDescida[i];				
					vetorSolucaoDescida[i]=vetorSolucaoDescida[j];
					vetorSolucaoDescida[j]=aux;
					binaria(vetorSolucaoDescida,matrizBinariaGerada,agentes,tarefas);
					verificaExtrapolacao = verificarecursoG(vetorSolucaoDescida,matrizBinariaGerada,matrizRecurso,agentes,tarefas,capacidadeAgen);
					if(verificaExtrapolacao == agentes)
					{
						funcaoObTroca = funcaoObjetivo(agentes,tarefas,matrizBinariaGerada,matrizCusto);
						if(funcaoObTroca<melhorCorrente)
						{
							//printf("Entrou no if de menor @@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
							melhorCorrente = funcaoObTroca;
							melhorou = 1;
							break;
						}
						else
						{
							//printf("Entrou 2 \n");
							aux = vetorSolucaoDescida[i];				
							vetorSolucaoDescida[i]=vetorSolucaoDescida[j];
							vetorSolucaoDescida[j]=aux;
							binaria(vetorSolucaoDescida,matrizBinariaGerada,agentes,tarefas);	
						}
					}
					else
					{

						aux = vetorSolucaoDescida[i];				
						vetorSolucaoDescida[i]=vetorSolucaoDescida[j];
						vetorSolucaoDescida[j]=aux;
					}					
					
				}
			
			}
			if(melhorou == 1)
			{
				break;
			}

		}
		break;
		
	}while(melhorou!=1);

	return funcaoObTroca; 

}






int descidaCompletaTrocaG(int * vetorSolucaoDescida, int solucaoAleatoria,  int agentes,int  tarefas, int matrizCusto[][taref], int matrizRecurso[][taref], int * capacidadeAgen)
{
	int melhorCorrente = solucaoAleatoria, melhorou = 0, solucaoCorrente = 0,  i, j, aux, matrizBinariaGerada[agentes][tarefas];
	int funcaoObTroca = solucaoAleatoria; 
	int verificaExtrapolacao;
	int posI = 0, posJ = 0;
	for(i=0;i<agentes;i++)
	{
		for(j=0;j<tarefas;j++)
		{			
			matrizBinariaGerada[i][j]=0;
		}
	}

	do
	{
		melhorou = 0; 
		for(i=0;i<tarefas-1;i++)
		{
			for(j=1;j<tarefas;j++)
			{
				if(vetorSolucaoDescida[i]!=vetorSolucaoDescida[j])
				{
					aux = vetorSolucaoDescida[i];				
					vetorSolucaoDescida[i]=vetorSolucaoDescida[j];
					vetorSolucaoDescida[j]=aux;
					binaria(vetorSolucaoDescida,matrizBinariaGerada,agentes,tarefas);
					verificaExtrapolacao = verificarecursoG(vetorSolucaoDescida,matrizBinariaGerada,matrizRecurso,agentes,tarefas,capacidadeAgen);
					if(verificaExtrapolacao == agentes)
					{
						funcaoObTroca = funcaoObjetivo(agentes,tarefas,matrizBinariaGerada,matrizCusto);
						if(funcaoObTroca<melhorCorrente)
						{
							//printf("Entrou no if de menor @@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
							melhorCorrente = funcaoObTroca;
							posI = i;
							posJ = j; 
							melhorou = 1;
							
						}
						else
						{
							//printf("Entrou 2 \n");
							aux = vetorSolucaoDescida[i];				
							vetorSolucaoDescida[i]=vetorSolucaoDescida[j];
							vetorSolucaoDescida[j]=aux;
							//binaria(vetorSolucaoDescida,matrizBinariaGerada,agentes,tarefas);	
						}
					}
					else
					{
						//printf("Extrapola\n");
						//break;
						aux = vetorSolucaoDescida[i];				
						vetorSolucaoDescida[i]=vetorSolucaoDescida[j];
						vetorSolucaoDescida[j]=aux;
						//binaria(vetorSolucaoDescida,matrizBinariaGerada,agentes,tarefas);	
					}					
					
				}
	
								
			}
			if(melhorou == 1)
			{
				aux = vetorSolucaoDescida[posI];				
				vetorSolucaoDescida[posI]=vetorSolucaoDescida[posJ];
				vetorSolucaoDescida[posJ]=aux;
			}

		}
		break;
		
	}while(melhorou!=1);

	return funcaoObTroca; 

}



int VNDG(int * vetorInicial, int solAleatoria, int agentes, int tarefas,int matrizCusto[][taref],int matrizRecurso[][taref], int * capacidadeAg)
{

	int k = 0, r = 2, solCorrente, i, vetorCorrente[tarefas], matrizBinariaGerada[agentes][tarefas]; 
	int melhorSolucao = solAleatoria; 

	while(k<r)
	{
		if(k==0)
		{
			


			//solCorrente = descidaPrimeiroTroca(vetorInicial,melhorSolucao,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAg); //funcaoObjetivo(agentes,tarefas,matrizBin,matrizCusto);
			solCorrente = descidaCompletaTrocaG(vetorInicial,melhorSolucao,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAg); 

			if(solCorrente<melhorSolucao)
			{
				melhorSolucao=solCorrente;
				k=0; 
			}
			else
			{
				k++; 
			}
			

		}
		if(k==1)
		{
			solCorrente = descidaPrimeiroTrocaG(vetorInicial,melhorSolucao,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAg);
			//solCorrente = descidaCompletaTroca(vetorInicial,melhorSolucao,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAg); 
			if(solCorrente<melhorSolucao)
			{
				melhorSolucao= solCorrente;
				k=1; 
			}
			else
			{
				k++; 
			}
		}
		
	} 

	return melhorSolucao; 
} 


int ILSG(tarefa * listaTarefas,int * vetorInicial,int solAleatoria,int agentes, int tarefas,int matrizCusto[][taref],int matrizRecurso[][taref], int * capacidadeAg, int iterMax)
{
	int solucaoVND = VNDG(vetorInicial,solAleatoria,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAg);
	int iter = 0, melhorFo, menor = solucaoVND, posicao = 0;
	int vetorFOSolucao[iterMax], i; 
	int solucoes[iterMax][tarefas];
	
	

	while(iter<iterMax)
	{
		//iter++; 
		////PERTUBAÇÃOOOOOO
        pertubacaoG(listaTarefas,vetorInicial,capacidadeAg,matrizCusto,matrizRecurso,agentes,tarefas);
		vetorFOSolucao[iter]=VNDG(vetorInicial,solAleatoria,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAg);
		for(i=0;i<tarefas;i++)
		{
			solucoes[iter][i]= vetorInicial[i];
		}
        iter++; 
	}
	for(i=0;i<iterMax;i++)
	{
		if(vetorFOSolucao[i]<menor)
		{
			menor = vetorFOSolucao[i];
			posicao = i;
		}
        else
        {
            printf("Não gerou menor solucao que a VND\n");
        }
        
	}
	for(i=0;i<tarefas;i++)
	{
		vetorInicial[i]=solucoes[posicao][i]; 
	}
	melhorFo = vetorFOSolucao[posicao]; 


	return melhorFo; 
}





int main()
{
	//srand((unsigned) time(NULL));
	
	//FILE *instancias = fopen("c05100.txt","r");  // vari�vel para manipula��o do arquivo/instancia
	//FILE *instancias = fopen("e20200.txt","r");
	FILE *instancias = fopen("e10200.txt","r"); 
 
	//FILE *instancias = fopen("e20400.txt","r"); 
	int tarefas,agentes, i, j, t , solucaoCustoGulosa = 0, solucaoCustoAleatoria = 0;	
	
	
	fscanf(instancias,"%d %d",&agentes, &tarefas);
	taref=tarefas;
	
	printf("\n Agentes: %d \t Tarefas: %d", agentes, tarefas);
	int matrizCusto[agentes][tarefas]; // matriz de custo
	int matrizRecurso[agentes][tarefas]; // matriz de recurso
	int matrizBinaria[agentes][tarefas]; // matriz binaria geradora custo/recurso de solucao
	int matrizBinariaAleatoria[agentes][tarefas]; // matriz binaria gulosa de solucao
	int capacidadeAgentes[agentes]; // vetor com a capacidade dos agentes
	int contadorAgenteGuloso[agentes]; // vetor com os contadores de recursos gastos de cada agente
	int contadorAgenteAleatoria[agentes];// vetor com os contadores de recursos gastos de cada agente
	int vetorSolucaoGulosa[tarefas];
	int vetorSolucaoAleatoria[tarefas];
	int vetorSolucaoPrimeira[tarefas];
	int vetorSolucaoCompleta[tarefas];
	int vetorSolucaoVND[tarefas];
	int vetorSolucaoILS[tarefas]; 
    int primeiraGulosa[tarefas];
	int trocaGulosa[tarefas];
	int vndGulosa[tarefas];
    int ilsGulosa[tarefas];
	
	 
	Info dados;
	tarefa lTarefa[tarefas]; 
    tarefa lTarefa2[tarefas];
	
	
	
	// *******************************LA�O PARA LER DO ARQUIVO A MATRIZ DE CUSTOS*********************************
	for(i=0;i<agentes;i++)
	{
		for(j=0;j<tarefas;j++)
		{
			fscanf(instancias,"%d",&matrizCusto[i][j]);
		}
	
	}
		
	// ************************LA�O PARA LER DO ARQUIVO A MATRIZ DE RECURSOS**************************************
	for(i=0;i<agentes;i++)
	{
		for(j=0;j<tarefas;j++)
		{
			fscanf(instancias,"%d",&matrizRecurso[i][j]);
		}
	}
	// ****************************************PRINTANDO MATRIZ DE CUSTOS****************************************
	/*printf("\n\n MATRIZ CUSTOS");
	for(i=0;i<agentes;i++)
	{
		printf("\n");
		for(j=0;j<tarefas;j++)
		{
			printf("%d\t",matrizCusto[i][j]);
		}
	}*/
	
	// ****************************************PRINTANDO MATRIZ DE RECURSOS****************************************
	/*
	printf("\n\n MATRIZ RECURSOS");
	
	for(i=0;i<agentes;i++)
	{
		printf("\n");
		for(j=0;j<tarefas;j++)
		{
			printf("%d\t",matrizRecurso[i][j]);
		}
	}
	*/
	// **************************************LENDO CAPACIDADE DOS AGENTES DO ARQUIVO****************************************************
	for(i=0;i<agentes;i++)
	{
		fscanf(instancias,"%d\t",&capacidadeAgentes[i]);
	}
	//fscanf(instancias,"%d %d %d %d %d ",&capacidadeAgentes[0],&capacidadeAgentes[1],&capacidadeAgentes[2],&capacidadeAgentes[3],&capacidadeAgentes[4]);
	fclose(instancias);
	
	for(i=0;i<agentes;i++)
	{
		printf("\t%d",capacidadeAgentes[i]);
	}
	
//**************************************** INICIALIZANDO MATRIZ BINARIA(GERADORA DA SOLU��O) COM ZERO ************************************	
	for(i=0;i<agentes;i++)
	{
		for(j=0;j<tarefas;j++)
		{
			matrizBinaria[i][j]=0;
			matrizBinariaAleatoria[i][j]=0;
		}
	}
	
//************************************* INICIALIZANDO VETOR SOLU��O COM ZERO e INICIALIZANDO LISTA ************************************	
	for(j=0;j<tarefas;j++)
	{
		vetorSolucaoGulosa[j]=0;
		inicializarLista(&lTarefa[j].prtlist);	
	}
	
	
// ********************************* INSERIR ODERNADO CUSTO/RECURSOS NA LISTA PARA FUN��O GULOSA **********************************	
	
	for(i=0;i<agentes;i++)
	{
			
		for(j=0;j<tarefas;j++)
		{
					
			dados.agente=i; 
			dados.custoRecurso= (matrizCusto[i][j]/matrizRecurso[i][j]);
            dados.custo=matrizCusto[i][j];
			inserirOrdenado(&lTarefa[j].prtlist,dados);
            inserirOrdenadoCusto(&lTarefa2[j].prtlist,dados);
			//imprimirLista(&lTarefa[j].prtlist);
			
		}
	}

	
	
  
 	////////////////////////////////////SOLUCAO CUSTO/RECURSO////////////////////////////////////////////

criarMatrizBin(lTarefa,matrizBinaria,matrizRecurso,capacidadeAgentes,agentes,tarefas);


 	////////////////////////////////////IMPRIMINDO MATRIZ BINARIA CUSTO/RESURSO ////////////////////////////////////////////
	/*printf("\n\n MATRIZ BINARIA");
	
	for(i=0;i<tarefas;i++)
	{
		printf("\n");
		for(j=0;j<agentes;j++)
		{
			printf("%d\t",matrizBinaria[j][i]);
		}
	}
*/
// **********************LA�O PARA INICIALIZAR TODOS OS CONTADORES DE RECURSOS DOS AGENTES COM ZERO******************
	
    for(j=0;j<agentes;j++)
	{
		contadorAgenteAleatoria[j]=0; 
	}
	 
	//////////////////////////////////////ALEATORIA//////////////////////////////////////////////////////
	int contador = 0; 
	int chave = 0; 
	int aleatoria;
	srand((unsigned) time(NULL));
	while(contador < tarefas)
	{	//srand((unsigned) time(NULL));
		aleatoria = sorteador(agentes);
		//printf("\n Agente: %d\t", aleatoria ); 
		//if(chave == 0)
		//{
			//srand((unsigned) time(NULL));
			//aleatoria = sorteador(agentes); 
			
			if(matrizRecurso[aleatoria-1][contador]+contadorAgenteAleatoria[aleatoria-1]<=capacidadeAgentes[aleatoria-1])
			{
				//contadorAgenteAleatoria[aleatoria-1]+= matrizRecurso[aleatoria-1][contador];
				matrizBinariaAleatoria[aleatoria-1][contador]=1;
				vetorSolucaoAleatoria[contador]=aleatoria;
				solucaoCustoAleatoria+= matrizCusto[aleatoria-1][contador];
				chave = 0; 
				contador++; 

			}
			/*else
			{
				chave = 1; 
			}	*/		

		}
		/*aleatoria = sorteador(agentes);
		if(chave == 1)
		{
			//srand((unsigned) time(NULL));
			//aleatoria = sorteador(agentes); 
			
			if(matrizRecurso[aleatoria-1][contador]+contadorAgenteAleatoria[aleatoria-1]<=capacidadeAgentes[aleatoria-1])
			{
				//contadorAgenteAleatoria[aleatoria-1]+= matrizRecurso[aleatoria-1][contador];
				matrizBinariaAleatoria[aleatoria-1][contador]=1;
				vetorSolucaoAleatoria[contador]=aleatoria+1;
				solucaoCustoAleatoria+= matrizCusto[aleatoria-1][contador];
				chave = 0; 
				contador++;  

			}
			else
			{
				chave = 1; 
			}			

		}	


	}





/*
	int aleatoria;
	srand((unsigned) time(NULL));
	
	for(i=0;i<tarefas;i++)
	{
		//srand((unsigned) time(NULL));
		aleatoria = sorteador(agentes); 	
        matrizBinariaAleatoria[aleatoria-1][i]=1;
        vetorSolucaoAleatoria[i]=aleatoria;
        solucaoCustoAleatoria+= matrizCusto[aleatoria-1][tarefas];
			
		//}
	
	}

*/
   /*  srand((unsigned) time(NULL));
    int aleatoria; 
	for(i=0;i<tarefas;i++)
	{
	//srand((unsigned) time(NULL));
	aleatoria = sorteador(agentes);
	//if(matrizRecurso[aleatoria-1][tarefas]+contadorAgenteAleatoria[aleatoria-1]<=capacidadeAgentes[aleatoria-1])
	//{
		vetorSolucaoAleatoria[i]=aleatoria;
		solucaoCustoAleatoria+= matrizCusto[aleatoria-1][tarefas];
	//}
	
	}
 	////////////////////////////////////IMPRIMINDO MATRIZ BINARIA ALEATORIA ////////////////////////////////////////////	
	/*printf("\n\n MATRIZ BINARIA ALEATORIA");
	
	for(i=0;i<tarefas;i++)
	{
		printf("\n");
		for(j=0;j<agentes;j++)
		{
			printf("%d\t",matrizBinariaAleatoria[j][i]);
		}
	}*/
	
	
	



    printf("\n\n\n@@@@@@@@@@@@@  Solucao Aleatoria:  @@@@@@@@@@@@@\n");
	for(j=0;j<tarefas;j++)
	{
		//printf("%d\t",vetorSolucaoAleatoria[j]);
	}
	printf("\nValor de Custo da Solucao:  %d \n",solucaoCustoAleatoria);


    for(i=0;i<agentes;i++)
	{
		for(j=0;j<tarefas;j++)
		{
			if(matrizBinaria[i][j]==1)
			{
				vetorSolucaoGulosa[j]=i+1;
			}
			
		}
	}




	for(j=0;j<tarefas;j++)
	{
		vetorSolucaoPrimeira[j]=vetorSolucaoAleatoria[j];
		vetorSolucaoCompleta[j]=vetorSolucaoAleatoria[j];
		vetorSolucaoVND[j]=vetorSolucaoAleatoria[j];
		vetorSolucaoILS[j]=vetorSolucaoAleatoria[j];

		primeiraGulosa[j] =vetorSolucaoGulosa[j];
		trocaGulosa[j]=vetorSolucaoGulosa[j];
		vndGulosa[j]=vetorSolucaoGulosa[j];
        ilsGulosa[j]=vetorSolucaoGulosa[j];
		//printf("%d\t",vetorSolucaoGulosa[j]);
	}
	
	
	
	

	
	printf("\n\n@@@@@@@@@@@@@  Refinamento: Descida Primeiro Troca  @@@@@@@@@@@@@\n");	
	
	int solucaoDescida = descidaPrimeiroTroca(vetorSolucaoPrimeira,solucaoCustoAleatoria,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAgentes);	
	//int solucaoDescida = descidaPrimeiroTroca(vetorSolucaoGulosa,solucaoCustoGulosa,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAgentes);
	for(j=0;j<tarefas;j++)
	{
		//printf("%d\t",vetorSolucaoPrimeira[j]);
		//printf("%d\t",vetorSolucaoGulosa[j]);
	}
	printf("\nValor de Custo da Solucao Descida:  %d \n",solucaoDescida);	


	
	printf("\n\n@@@@@@@@@@@@@  Refinamento: Descida Completa Troca  @@@@@@@@@@@@@\n");	
	
	int solucaoDescidaCompleta = descidaCompletaTroca(vetorSolucaoCompleta,solucaoCustoAleatoria,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAgentes);	
	for(j=0;j<tarefas;j++)
	{
		//printf("%d\t",vetorSolucaoCompleta[j]);
	}
	printf("\nValor de Custo da Solucao Descida Completa:  %d \n",solucaoDescidaCompleta);




	printf("\n\n@@@@@@@@@@@@@  VND  @@@@@@@@@@@@@\n");	
	
	int solucaoVND = VND(vetorSolucaoVND,solucaoCustoAleatoria,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAgentes);	
	for(j=0;j<tarefas;j++)
	{
		//printf("%d\t",vetorSolucaoVND[j]);
	}
	printf("\nValor de Custo da Solucao VND:  %d \n",solucaoVND);



    printf("\n\n@@@@@@@@@@@@@  ILS  @@@@@@@@@@@@@\n");	
	
	int solucaoILS = ILS(vetorSolucaoILS,solucaoCustoAleatoria,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAgentes,3);	
	for(j=0;j<tarefas;j++)
	{
		//printf("%d\t",vetorSolucaoILS[j]);
	}
	printf("\nValor de Custo da Solucao ILS:  %d \n",solucaoILS);



   
	

    /////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////
	//////////////////////
	///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////




    printf("\n\n@@@@@@@@@@@@@  Solucao GULOSA:  CUSTO POR RECURSO  @@@@@@@@@@@@@\n");	
	
	solucaoCustoGulosa = funcaoObjetivo(agentes,tarefas,matrizBinaria,matrizCusto);
	//int copiaSGulosa[tarefas];


    for(j=0;j<tarefas;j++)
	{
        //printf("%d\t",vetorSolucaoGulosa[j]);
    }
    printf("\nValor de Custo da Solucao Gulosa:  %d \n",solucaoCustoGulosa);


	

	printf("\n\n@@@@@@@@@@@@@  Refinamento: Descida Primeiro Troca GULOSA  @@@@@@@@@@@@@\n");	
	
	int solucaoDescidaG = descidaPrimeiroTrocaG(primeiraGulosa,solucaoCustoGulosa,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAgentes);	
	//int solucaoDescida = descidaPrimeiroTroca(vetorSolucaoGulosa,solucaoCustoGulosa,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAgentes);
	for(j=0;j<tarefas;j++)
	{
		//printf("%d\t",primeiraGulosa[j]);
		//printf("%d\t",vetorSolucaoGulosa[j]);
	}
	printf("\nValor de Custo da Solucao Descida:  %d \n",solucaoDescidaG);	


	
	printf("\n\n@@@@@@@@@@@@@  Refinamento: Descida Completa Troca GULOSA  @@@@@@@@@@@@@\n");	
	
	int solucaoDescidaCompletaG = descidaCompletaTrocaG(trocaGulosa,solucaoCustoGulosa,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAgentes);	
	for(j=0;j<tarefas;j++)
	{
		//printf("%d\t",trocaGulosa[j]);
	}
	printf("\nValor de Custo da Solucao Descida Completa:  %d \n",solucaoDescidaCompletaG);




	printf("\n\n@@@@@@@@@@@@@  VND GULOSA @@@@@@@@@@@@@\n");	
	
	int solucaoVNDG = VNDG(vndGulosa,solucaoCustoGulosa,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAgentes);	
	for(j=0;j<tarefas;j++)
	{
		//printf("%d\t",vndGulosa[j]);
	}
	printf("\nValor de Custo da Solucao VND:  %d \n",solucaoVNDG);

	
    printf("\n\n@@@@@@@@@@@@@  ILS  @@@@@@@@@@@@@\n");	
	
	int solucaoILSG = ILSG(lTarefa2,ilsGulosa,solucaoCustoGulosa,agentes,tarefas,matrizCusto,matrizRecurso,capacidadeAgentes,1);	
	for(j=0;j<tarefas;j++)
	{
		//printf("%d\t",ilsGulosa[j]);
	}
	printf("\nValor de Custo da Solucao ILS:  %d \n",solucaoILSG);





	return 0; 
}
