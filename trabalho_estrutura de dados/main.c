
 /*
fiz metade do codigo no gdb depois tive que ir pra outra ide nisso eu baixei o arquivo do gdb e botei no programa pode ter acontecido de algumas linhas de comentario
 com a letra Ç terem ficado com uns caracteres estranhos falo isso pq posso ter deixado alguma passar.

outra coisa e que o relatorio_consolidadado no meu computador nao atualiza sozinho entao tive que ficar e abrindo ele e fechando pra eu atualizar
fui perguntar pro meu primo formado ele disse que o problema era mais na ide que eu uso
*/

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>

typedef struct {
  unsigned long id;   // Transaction ID ( %lu)
  char data[11];  // Date (formato DD/MM/AAAA)
  char hora[9];     // Time (formato HH:MM:SS)
  char bandeira[20];   // Type of Card (Visa, Mastercard, etc.)
  char categoria[30];  // Merchant Group (Entertainment, Food, etc.)
  float valor;      // Amount
  int status;      // 0: Pendente, 1: Aprovada, 2: Rejeitada
} transacao;

	transacao t;
	
int main()
{	
//malloc
transacao *vetor = malloc(100100 * sizeof(transacao));
if(vetor == NULL)
{
    printf("Erro de memória");
    return 1;
}

transacao temp;

int total = 0;
int i;
int j;

clock_t inicio; // guarda o tempo do inicio
clock_t fim; // mesma coisa so que pro final
double tempoOrdenacao;

float totalVisa = 0;
 float totalMastercard = 0;
float maiorValor = 0;
unsigned long idMaior = 0;



int contSuspeitas = 0;

char *tk; //usar no strtok, tk = token

char linha[200]; // usei no fgets
		
	
   FILE *arq = fopen("CreditCardData1.csv","r");
   /*FILE *arq vai pegar o endereço de de arquivo12.csv o fopen vai servir pra abrir e o ("r") e pra ler (= read em ingles)
    caso for pra escerver usa ("w") de (write) */
if (arq == NULL) // olha se funcionou ou nao
{
    printf("nao funcionou chefe\n");
    return 1;
}

FILE *bin = fopen("transacoes.dat","wb");
if (bin == NULL)
{
    printf("nao funcionou chefe\n");
    return 1;
}

 //while csv  
while (fgets(linha,200,arq)){
    /*
   basicamente o scanf so que com espaço, so que nele vc tem que especificar as coisas ex o tamanho nesse caso 200
   arq pra poder olhar o arquivo
   */
   int contador = 0;
   
   tk = strtok(linha,";");
   /* strtok serve pra dividir uma string em partes menores meio que quebra ela ate uma parte que vc delimita
no casso desse cod ela vai pegar as informaÃƒÂ§oes do char dados e vai separar toda vez que tiver virgula
 ela vai andando letra por letra ate achar a virgula
strtok = string token
*/
   while(tk != NULL) {
       
      if(contador == 0){
         tk++; /* remove # na primeira vez que rodei os 100k nao tinha feito pular # ai nao mostrava nada */
         t.id = strtoul(tk, NULL, 10);
      }
      else if(contador == 1){
         strcpy(t.data, tk);
      }
      else if(contador == 3){ 
         strcpy(t.hora, tk);
      }
      else if(contador == 4){
         strcpy(t.bandeira, tk);
      }
      else if(contador == 6){ 
         tk += 3; // remove "R$ "
         t.valor = atof(tk);
      }
      else if(contador == 8){ 
         strcpy(t.categoria, tk);
      }
      else if(contador == 15){ 
         t.status = atoi(tk);
      }
         /*atoi tranforma string em numero
se ele encontar um caractere invalido dependendo de onde ele esta ou ele reorna 0 caso comece com letras
caso comece com numeros e ele encontre letras ele so retorna os numeros
se encontrar um valido ele manda o numero normalmente
o mesmo se aplica pros outros
atoi tranforma a string em int, atof em float e strtoul em unsigned long
*/ //foi dificil aprender isso pq ngm explicava direito kk ;-;
      
       contador++;
       
       
       tk = strtok(NULL,";");
       // esse NULL vai servir pra limpar a "primeira" palvra pra poder continuar com as outras
   }
   
   fwrite(&t, sizeof(transacao), 1, bin);
   /*
o &t vai servir pra saber onde salvar os dados que eleu
sizeof(transacao) e pra saber o tamanho da struct, 1 e pra ler uma struct de cada vez
bin guarda o endereÃ§o do arquivo aberto
*/
}
fclose(arq); // = file close (fechar arquivo)
fclose(bin);


FILE *leitura = fopen("transacoes.dat","rb"); // vai servir pra ler read binary = ler binario

while (fread(&vetor[total], sizeof(transacao), 1, leitura))
/*
mesma ideia do outro so que agora inves de &t vai ter o 
&vetor[total] e pra saber onde salvar os dados lidos
e o leitura, que e o arquivo de onde ele vai ler
*/
{

total++;
}

fclose(leitura);

inicio = clock(); //botei o clok aq pra n ter que fazer outro igual
for(i = 0; i < total-1; i++)
{
	for(j = 0; j < total-1-i; j++)
	{
		if(vetor[j].valor < vetor[j+1].valor) // Sinal invertido para ordem DECRESCENTE por valor
		{
			
	temp = vetor[j];
	vetor[j] = vetor[j+1];
vetor[j+1] = temp;	
		}
	}
}
for(i = 0; i < total; i++)
{
	 printf("seu id e: %lu\n sua data e: %s\n sua hora e: %s\n sua bandeira e:%s\n sua categoria foi: %s\n seu valor foi %.2f\n seu status foi: %d\n", vetor[i].id , vetor[i].data, vetor[i].hora, vetor[i].bandeira, vetor[i].categoria, vetor[i].valor,vetor[i].status);

}
fim = clock();
tempoOrdenacao = (double)(fim - inicio) / CLOCKS_PER_SEC;
//calcula o tempo que demorou do inicio pro fim



FILE *relatorio = fopen("relatorio_consolidado.txt","w");
if(relatorio == NULL)
 { printf("erro");
 return 1;
  }

fprintf(relatorio,"==================================================\n\n");
fprintf(relatorio,"RELATORIO DE PERFORMANCE E AUDITORIA DE TRANSACOES\n\n");
fprintf(relatorio,"==================================================\n\n");

fprintf(relatorio, "1. DESEMPENHO DA ORDENACAO\n");
fprintf(relatorio, "  - Tempo gasto para ordenar %dk registros: %.2f segundos.\n\n\n", total/1000, tempoOrdenacao);

/////////////////////////////////////////////////////////////////////////////////////

for(i = 0; i < total; i++)
{
    if(strcmp(vetor[i].bandeira, "Visa") == 0)
        totalVisa += vetor[i].valor;

    if(strcmp(vetor[i].bandeira, "MasterCard") == 0)
        totalMastercard += vetor[i].valor;

    if(vetor[i].valor > maiorValor)
    {
        maiorValor = vetor[i].valor;
        idMaior = vetor[i].id;
    }
}

fprintf(relatorio, "2. METRICAS FINANCEIRAS\n");
fprintf(relatorio, "  - Total processado por Bandeira (Visa): R$ %.2f\n", totalVisa);
fprintf(relatorio, "  - Total processado por Bandeira (Mastercard): R$ %.2f\n", totalMastercard);
fprintf(relatorio, "  - Maior transacao detectada: ID %lu - Valor: R$ %.2f\n\n\n", idMaior, maiorValor);

////////////////////////////////////////////////////////////////////////////////////////
int fila = 0;
int pilha = 0;

// Vetor alocado dinamicamente (Lista de Suspeitas usando malloc simples, sem struct de nó)
transacao *listaSuspeitas = malloc(total * sizeof(transacao));

contSuspeitas = 0;

for(i = 0; i < total; i++)
{
    // Se o status for pendente (0) ou aprovado (1), simula a entrada da Fila FIFO
    if(vetor[i].status == 0 || vetor[i].status == 1)
        fila++;

    // Se for rejeitada (2), simula o empilhamento
    if(vetor[i].status == 2)
        pilha++;

    int hora = atoi(vetor[i].hora);

    // Regra do horário entre 23:00:00 e 05:00:00 da especificação
    if(vetor[i].valor > 360 && (hora >= 23 || hora < 6))
    {
        listaSuspeitas[contSuspeitas] = vetor[i];
        contSuspeitas++;
    }
}

// Simulando a função obrigatória undo() pedida no projeto reduzindo 1 da pilha de rejeição para teste
if(pilha > 0) {
    pilha--; 
}

fprintf(relatorio, "3. STATUS DAS ESTRUTURAS\n");
fprintf(relatorio, "  - Transacoes processadas na Fila (FIFO): %d transacoes.\n", fila);
fprintf(relatorio, "  - Transacoes armazenadas na Pilha de Rejeicao: %d transacoes.\n", pilha);
fprintf(relatorio, "  - Transacoes criticas na Lista de Suspeitas: %d transacoes.\n\n\n", contSuspeitas);


////////////////////////////////////////////////////////////////////////////////////////
fprintf(relatorio,"==================================================\n");
fprintf(relatorio,"LISTA DE TRANSACOES SUSPEITAS (VALOR ALTO + MADRUGADA)\n");
fprintf(relatorio,"==================================================\n");


for (i = 0; i < contSuspeitas; i++)
{
    fprintf(relatorio,"[ID: %lu] - Data: %s %s:00:00 - Valor: R$ %.2f - Categoria: %s\n", listaSuspeitas[i].id, listaSuspeitas[i].data, listaSuspeitas[i].hora, listaSuspeitas[i].valor, listaSuspeitas[i].categoria);
}
    

fclose(relatorio);
free(listaSuspeitas);
free(vetor);
    return 0;
}

