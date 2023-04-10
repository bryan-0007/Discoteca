//-------Bibliotecas aqui --------
#include "header.h"
//------------------------------------
// #define NULL ((void *)0)

// #define MAX_LENGTH 1000;
char data[MAX_LINE][MAX_LENGTH]; // array 2D onde ir� estar os dados de configura��o presentes no momento onde as colunas representa o numero de linhas e as linhas representa o comprimento da frase
char NumeroDePessoas[6];		 // onde ir� guardar o Numero de pessoas presente na discoteca
char NumeroDeGrupos[6];
char TempoMedioDeChegada[6];			
char TempoMedioDeDesistencia[6];			 
char TempoMedioDeConsumo[6];			 
char TempoMedioDeProducao[6];				 
char CustoDoHamburguer[6];
char CustoDeProducao[6];
char CapitalMedioPorCliente[6];
char TempoMedioNaZona[6];
char Numero_Total_TempoDeSimulacao[6];
char ClientesCriados[6];
char ProdutoresCriados[6];
char NumeroMaxNaZonaA[6];
char NumeroMaxNaZonaB[6];  
char NumeroMaxNaZonaC[6];  
char NumeroMaxNaZonaD[6];

int custo_hamb;
int id = 0;
int NumeroNafila4 = 0;

int CLIENTES_CRIADOS;
int PRODUTORES_CRIADOS;
int NMaxA;
int NMaxB;
int NMaxC;
int NMaxD;

int connection_socket;


bool flag_thr_messagem = false;
bool finalizar_simulacao = false;
bool uma_vez = true;

pthread_mutex_t mutexfilaA;
pthread_mutex_t mutexfilaB;
pthread_mutex_t mutexfilaD;
pthread_mutex_t NumeroNafilaC;

extern pthread_mutex_t mutexFinalizarSim;
extern pthread_mutex_t mutex;
pthread_mutex_t mutexCliente;
pthread_mutex_t mutexCriar;
pthread_mutex_t mutexSair;
pthread_mutex_t mutexComer;
pthread_mutex_t sairDiscoteca;

pthread_t th[100];
pthread_t thrProd_id[100];

pthread_t create_prod;
pthread_t threadTime;
pthread_t threadMessage;
pthread_mutex_t threadC1;

sem_t sem;
sem_t sem2;
sem_t sem3;
sem_t sem4;
sem_t semL;
sem_t semL2;
sem_t semEmpty; // Semaphore to count the number of empty slots in the buffer
sem_t semFull;	// Semaphore to count the number of full slots in the buffer
sem_t semFilaA;
sem_t semFilaB;
sem_t semFilaD;

bool flaq_criar_prod = false;
bool flag_threads_acabam = false;
int counter = 0;

// Mutex to protect access to the shared buffer
pthread_mutex_t mutexBuffer;
int bufferHamburg[3]; // Shared buffer
int count = 0;		  // Count of the number of items in the buffer
int contadorProd = 0; // Counter for producer threads
int idProd = 0;		  // ID of the producer thread

struct cliente
{					   // array clientes o que cada um vai ter
	int numeroPessoas; // numero de pessoas adicionadas
	int prioridade;
	char *zona;
	int id;
	int tempoChegada;
	int tempoMedio;
	int tempoDesistencia;
	int tempoConsumo;
	int contadorTempoA;
	int contadorTempoB;
	int contadorTempoC;
	int contadorTempoD;
	int tempoNaFilaA;
	int tempoNaFilaB;
	int tempoNaFilaC;
	int tempoNaFilaD;
	int VIP;
	int capital;
	int custoHamburguer;
	bool listaPrioridade;
	bool inicializado;
	bool entrouNaFila;
};

struct cliente array_clientes[100];

struct produtores // array produtores o que cada um vai ter
{
	int id;
	int contadorTempoProducao;
	int tempoMedioProducao;
	int custoProducao;
	bool inicializado;
};

struct produtores array_produtores[100];

typedef struct
{
	int num_evento;
	struct cliente cli;
	struct produtores prod;
	int numero_de_clientes_total;
} msg;

typedef struct Node
{
	int x;
	struct Node *next;

} Node;

Node *root = NULL;

pthread_mutex_t threadLista;
pthread_mutex_t threadLista2;

// void deallocate(Node **root){
//     Node * curr = *root;
//     while(curr!=NULL){
//         Node *aux =curr;
//         curr=curr->next;
//         free(aux);
//     }
//     *root=NULL;
// }

void insert_begining(Node **root, int value)
{
	Node *new_Node = malloc(sizeof(Node));

	new_Node->x = value;
	new_Node->next = *root;

	*root = new_Node;
}

void insert_after(Node *node, int value)
{
	Node *new_node = malloc(sizeof(Node));
	new_node->x = value;
	new_node->next = node->next;

	node->next = new_node;
}

void insert_sorted(Node **root, int value)
{ // ordenação descendente da lista ligada ou seja 7,4,2

	if (*root == NULL || (*root)->x <= value)
	{
		insert_begining(root, value);
		return;
	}

	Node *curr = *root;

	while (curr->next != NULL)
	{

		if (curr->next->x <= value)
		{
			break;
		}
		curr = curr->next;
	}

	insert_after(curr, value);
}

void remove_element(Node **root, int value)
{

	if (*root == NULL)
	{
		return;
	}

	if ((*root)->x == value)
	{
		Node *to_remove = *root;
		*root = (*root)->next;
		free(to_remove);
		return;
	}

	for (Node *curr = *root; curr->next != NULL; curr = curr->next)
	{
		if (curr->next->x == value)
		{
			Node *to_remove = curr->next;
			curr->next = curr->next->next;
			free(to_remove);
			return;
		}
	}
}

struct Queue {
    int front, rear;
    msg array[MAX_SIZE];
    int count;
    pthread_mutex_t lock;
};

struct Queue q; // queue of messages
struct Queue filaA; // queue da fila A
struct Queue filaB; // queue da fila B
struct Queue filaD; // queue da fila D

void init(struct Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
    pthread_mutex_init(&q->lock, NULL);
}

bool enqueueCli(struct Queue* q, int n_event, struct cliente client) {
    pthread_mutex_lock(&q->lock);
    if (q->count == MAX_SIZE) {
        pthread_mutex_unlock(&q->lock);
        return false;
    }
	msg mensagem;
	mensagem.num_evento = n_event;
	mensagem.cli = client;
	mensagem.prod.inicializado = false;
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->array[q->rear] = mensagem;
    q->count++;
    pthread_mutex_unlock(&q->lock);
    return true;
}

bool enqueueNPessoas(struct Queue* q, int n_event, int n_total_pessoas) {
    pthread_mutex_lock(&q->lock);
    if (q->count == MAX_SIZE) {
        pthread_mutex_unlock(&q->lock);
        return false;
    } 
	msg mensagem;
	mensagem.num_evento = n_event;
	mensagem.numero_de_clientes_total = n_total_pessoas;
	mensagem.cli.inicializado = false;
	mensagem.prod.inicializado = false;
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->array[q->rear] = mensagem;
    q->count++;
    pthread_mutex_unlock(&q->lock);
    return true;
}

bool enqueueProd(struct Queue* q, int n_event, struct produtores produtor) {
    pthread_mutex_lock(&q->lock);
    if (q->count == MAX_SIZE) {
        pthread_mutex_unlock(&q->lock);
        return false;
    }
	msg mensagem;
	mensagem.num_evento = n_event;
	mensagem.prod = produtor;
	mensagem.cli.inicializado = false;
	mensagem.numero_de_clientes_total = 0;
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->array[q->rear] = mensagem;
    q->count++;
    pthread_mutex_unlock(&q->lock);
    return true;
}

msg dequeue(struct Queue* q) {
    pthread_mutex_lock(&q->lock);
    if (q->count == 0) {
        pthread_mutex_unlock(&q->lock);
		printf("retorno: %d", INT_MIN);
	}
	else{
		msg x = q->array[q->front];
    	q->front = (q->front + 1) % MAX_SIZE;
    	q->count--;
    	pthread_mutex_unlock(&q->lock);
    	return x;
	}
}

void display(struct Queue* q) {
    pthread_mutex_lock(&q->lock);
    int i = q->front;
	printf("\nQueue: ");
	while (i != q->rear)
	{
		printf("%d ", q->array[i].num_evento);
        i = (i + 1) % MAX_SIZE;
	}
	printf("%d\n", q->array[i].num_evento);
    pthread_mutex_unlock(&q->lock);
}

void displayFila(struct Queue* q, char *zona) {
    pthread_mutex_lock(&q->lock);
    int i = q->front;
	printf("\nQueue %s: ", zona);
	while (i != q->rear)
	{
		printf("%d ", q->array[i].num_evento);
        i = (i + 1) % MAX_SIZE;
	}
	printf("%d\n", q->array[i].num_evento);
    pthread_mutex_unlock(&q->lock);
}

bool isEmpty(struct Queue* q) {
    pthread_mutex_lock(&q->lock);
    bool result = (q->count == 0);
    pthread_mutex_unlock(&q->lock);
    return result;
}

msg getFirstElement(struct Queue* q) {
    pthread_mutex_lock(&q->lock);
    if (q->count == 0) {
        pthread_mutex_unlock(&q->lock);
        printf("Queue is empty!\n");
        return (msg){0};
    } else {
        msg first = q->array[q->front];
        pthread_mutex_unlock(&q->lock);
        return first;
    }
}


struct cliente *varStructCliente;

struct produtores *varStructProdutor;

// Function to display the current state of the buffer
void BufferDisplay()
{
	// Print top border
	for (int i = 0; i < 3; i++)
	{
		printf(" --- ");
	}
	printf("\n");
	// Print contents of buffer
	for (int i = 0; i < 3; i++)
	{
		if (bufferHamburg[i] < 3)
		{
			printf("| %d |", bufferHamburg[i]);
		}
		else
		{
			printf("|%d |", bufferHamburg[i]);
		}
	}
	// Print bottom border
	printf("\n");
	for (int i = 0; i < 3; i++)
	{
		printf(" --- ");
	}
	printf("\n");
}

void substring(char *orig, char *substr, int index, int length)
{ // fun��o com o objetivo de retirar apenas parte do que queremos de uma string que esta dentro de um array

	if (index >= strlen(orig)) // se o indice inserido for superior ao comprimento da string original ir� returnar uma substring vazia
	{
		substr[0] = '\0';
		return;
	}
	int i = 0;
	while (i < length && orig[index + i] != '\0') // ir� come�ar a ler a string original a partir do indice dado igualando esse valor depois a substring e ir� ler at� o valor for null
	{
		substr[i] = orig[index + i];
		i++;
	}
	substr[length] = '\0';
}

void atualizaValores(char variavel[], int valor, int linha)
{

	// Pointers de arquivo para o arquivo original e arquivo tempor�rio
	FILE *file, *temp;
	char str_valor[10];

	// Guarde o nome do arquivo e o nome do arquivo tempor�rio
	char filename[FILENAME_SIZE] = "Configuracoes.conf";
	char temp_filename[FILENAME_SIZE];

	// buffer ir� armazenar cada linha do arquivo original
	char buffer[MAX_LINE];

	// replace vai guardar a linha a reescrever com o valor ja atualizado(str_valor)
	char replace[MAX_LINE] = "";
	strcat(replace, variavel);
	sprintf(str_valor, "%d", valor); // passar valor da variavel para string
	strcat(replace, ":");
	strcat(replace, str_valor);
	strcat(replace, "\n");

	// replace_line vai gurdar a linha que desejamos mudar
	int replace_line = linha;

	// Vai ser feito um ficheiro tempor�rio no formato "temp__filename"
	strcpy(temp_filename, "temp____");
	strcat(temp_filename, filename);

	// Abrir o ficheiro original para ler e o ficheiro tempor�rio para escrever
	file = fopen(filename, "r");
	temp = fopen(temp_filename, "w");

	// Verificar se algum dos ficheiros fallaram ao abrir e se tamb�m sa�ram com error status
	if (file == NULL || temp == NULL)
	{
		printf("Error opening files(s).\n");
	}

	// Vai ser usado para manter em estado de leitura do ficheiro, enquanto que keep_reading � true
	bool keep_reading = true;

	// Ir� acompanhar o n�mero da linha atual que estamos lendo do arquivo
	int current_line = 1;

	do

	{
		fgets(buffer, MAX_LINE, file); // Leia a pr�xima linha do arquivo no buffer

		if (feof(file))
			keep_reading = false; // Se chegamos ao final do arquivo, pare de ler

		else if (current_line == replace_line)
			fputs(replace, temp); // Se a linha que alcan�amos for a que desejamos substituir, escreva o texto de substitui��o nesta linha do arquivo tempor�rio

		else
			fputs(buffer, temp); // Caso contr�rio, escreva esta linha no arquivo tempor�rio

		current_line++; // incremente a linha atual, pois agora estaremos lendo a pr�xima linha
	} while (keep_reading);

	// Para que feche o nosso acesso a ambos os arquivos quando terminarmos com eles
	fclose(file);
	fclose(temp);

	// Exclua o arquivo original, renomeie o arquivo tempor�rio para o nome do arquivo original
	remove(filename);
	rename(temp_filename, filename);
}

void *funcThreadTime(void *args)
{
	struct cliente *res;
	printf("\nMutex lock Finalizar Simulacao\n");
	int i = 0;
	printf("args: %d \n", *(int *)args);
	while (i <= *(int *)args)
	{
		printf("Tempo: %d\n", i);
		sleep(1);
		i++;
	}

	for (int i = 0; i < CLIENTES_CRIADOS; i++)
	{
		pthread_cancel(th[i]);
		printf("\nThread cliente %d acabada\n", i);
	}

	for (int i = 0; i < PRODUTORES_CRIADOS; i++) 
	{
		pthread_cancel(thrProd_id[i]);
		printf("\nThread produtor %d acabado\n", i);
	}

	enqueueNPessoas(&q, 10, CLIENTES_CRIADOS);
	display(&q);
	finalizar_simulacao = true;
	printf("finalizar_simulacao: %s\n", finalizar_simulacao ? "true" : "false");

	while(1){
		if (!finalizar_simulacao)
		{
			printf("Evento finalizar simulação foi enviado\n");
			flag_thr_messagem = true;
			break;
		}
	}

	pthread_cancel(threadTime);
}

void ficheiro_de_leitura()
{ // função com o objetivo de ler o ficheiro de configuração

	printf("---------------------------Thread Cliente----------------------\n");

	FILE *fd = fopen("Configuracoes.conf", "r"); // abre o ficheiro para ter acesso e utiliza o comando read

	if (fd == NULL)
	{ // se o ficheiro estiver vazio ir� dar informa��o de erro
		printf("O ficheiro com as configura��es n�o abre!! \n");
		// return -1;
	}

	else
	{
		int line = 0;

		while (!feof(fd) && !ferror(fd))
		{ // verifica se esta no final do ficheiro e testa se ocorre erro
			if (fgets(data[line], 1000, fd) != NULL)
			{ // l� linha a linha o ficheiro de configura��o, sendo 1000 o numero de caracteres maximo a seres lido, e o array data � onde a strign ir� ser guardada
				line++;
			}
		}
		//---------------------------------Apartir daqui coloco o array numa substring e vou buscar os valores que quero consoante o seu indice e comprimento
		substring(data[0], ClientesCriados, 16, 5);
		substring(data[1], ProdutoresCriados, 18, 5);
		substring(data[2], NumeroMaxNaZonaA, 17, 5);
		substring(data[3], NumeroMaxNaZonaB, 17, 5);
		substring(data[4], NumeroMaxNaZonaC, 17, 5);
		substring(data[5], NumeroMaxNaZonaD, 17, 5);
		substring(data[6], TempoMedioDeChegada, 20, 5);
		substring(data[7], TempoMedioNaZona, 17, 5);
		substring(data[8], TempoMedioDeDesistencia, 24, 5);
		substring(data[9], TempoMedioDeConsumo, 20, 5);
		substring(data[10], TempoMedioDeProducao, 21, 5);
		substring(data[11], CustoDoHamburguer, 18, 5);
		substring(data[12], CustoDeProducao, 16, 5);
		substring(data[13], CapitalMedioPorCliente, 23, 5);
		substring(data[14], Numero_Total_TempoDeSimulacao, 22, 5);

		fclose(fd); // fecha o ficheiro aberto a cima
	}
}


void zonaA(struct cliente *args)
{
	while (true)
	{
		bool mutexfilaA = false;
		int valorSemaforo;
		int Prim_el;
		printf("\nThread %d na zona A\n", args->id);

		sem_getvalue(&sem, &valorSemaforo); // tenho aqui o valor do semaforo sempre que uma thread entra
		if(valorSemaforo != 0 && !isEmpty(&filaA)){
			sem_wait(&semFilaA);
			mutexfilaA = true;
		}
		if (valorSemaforo == 0)
		{ // mal a thread entra e ver que o semaforo é zero vai para a fila
			printf("\nThread %d na fila zona A\n", args->id);
			Prim_el = getFirstElement(&filaA).num_evento;
			enqueueCli(&q, 2, *args);
			display(&q);
			enqueueNPessoas(&filaA, args->id, 1);
			args->entrouNaFila = true;
			displayFila(&filaA, "A");
			printf("\nPrimeiro elemento da queue a entrar: %d\n", Prim_el);

			while (true)
			{
				sem_getvalue(&sem, &valorSemaforo);
				Prim_el = getFirstElement(&filaA).num_evento;
				printf("Valor semaforo: %d",valorSemaforo);
				if(valorSemaforo != 0 && Prim_el == args->id){
					break;
				}
				else if (args->tempoNaFilaA >= args->tempoDesistencia)
				{
					printf("\nThread %d desiste da zona A\n", args->id);
					enqueueCli(&q, 8, *args);
					display(&q);
					break;
				}
				sleep(1);
				args->tempoNaFilaA++;
				//printf("Valor semaforo: %d",valorSemaforo);
			}

			if (args->tempoNaFilaA >= args->tempoDesistencia)
			{
				dequeue(&filaA);
				if(!isEmpty(&filaA))
					displayFila(&filaA, "A");
				else{
					printf("Fila A vazia\n");
				}
				args->entrouNaFila = false;
				break;
			}
		}

		if(args->entrouNaFila){
			dequeue(&filaA);
			if(!isEmpty(&filaA))
				displayFila(&filaA, "A");
			else{
				printf("Fila A vazia\n");
			}
			args->entrouNaFila = false;
		}

		sem_wait(&sem); // semaforo inicializado a 2
		if(mutexfilaA){
			mutexfilaA = false;
			sem_post(&semFilaA);
		}

		printf("\nThread %d entrou na zona A\n", args->id);
		enqueueCli(&q, 3, *args);
		display(&q);

		// print que irá entrar na zona
		// seguidamente ira contar o tempo que está na zona
		while (args->contadorTempoA <= args->tempoMedio)
		{
			sleep(1);
			args->contadorTempoA++;	
		}

		printf("\nThread %d saiu na zona A\n", args->id);
		enqueueCli(&q, 4, *args);
		display(&q);
		sem_post(&sem); // incrementa semaforo o que quer dizer que saiu da zona

		break;
	}
}

void zonaB(struct cliente *args)
{
	while (true)
	{
		bool mutexfilaB = false;
		int valorSemaforo;
		int Prim_el;
		printf("\nThread %d na zona B\n", args->id);

		sem_getvalue(&sem, &valorSemaforo); // tenho aqui o valor do semaforo sempre que uma thread entra
		if(valorSemaforo != 0 && !isEmpty(&filaB)){
			sem_wait(&semFilaB);
			mutexfilaB = true;
		}
		if (valorSemaforo == 0)
		{ // mal a thread entra e ver que o semaforo é zero vai para a fila
			printf("\nThread %d na fila zona B\n", args->id);
			Prim_el = getFirstElement(&filaB).num_evento;
			enqueueCli(&q, 5, *args);
			display(&q);
			enqueueNPessoas(&filaB, args->id, 1);
			args->entrouNaFila = true;
			displayFila(&filaB, "B");
			printf("\nPrimeiro elemento da queue a entrar: %d\n", Prim_el);

			while (true)
			{
				sem_getvalue(&sem2, &valorSemaforo);
				Prim_el = getFirstElement(&filaB).num_evento;
				printf("Valor semaforo: %d",valorSemaforo);
				if(valorSemaforo != 0 && Prim_el == args->id){
					break;
				}
				else if (args->tempoNaFilaB >= args->tempoDesistencia)
				{
					printf("\nThread %d desiste da zona B\n", args->id);
					enqueueCli(&q, 11, *args);
					display(&q);
					break;
				}
				sleep(1);
				args->tempoNaFilaB++;
				//printf("Valor semaforo: %d",valorSemaforo);
			}

			if (args->tempoNaFilaB >= args->tempoDesistencia)
			{
				dequeue(&filaB);
				if(!isEmpty(&filaB))
					displayFila(&filaB, "B");
				else{
					printf("Fila B vazia\n");
				}
				args->entrouNaFila = false;
				break;
			}
		}

		if(args->entrouNaFila){
			dequeue(&filaB);
			if(!isEmpty(&filaB))
				displayFila(&filaB, "B");
			else{
				printf("Fila B vazia\n");
			}
			args->entrouNaFila = false;
		}

		sem_wait(&sem2); // semaforo inicializado a 2
		if(mutexfilaB){
			mutexfilaB = false;
			sem_post(&semFilaB);
		}

		printf("\nThread %d entrou na zona B\n", args->id);
		enqueueCli(&q, 6, *args);
		display(&q);

		// print que irá entrar na zona
		// seguidamente ira contar o tempo que está na zona
		while (args->contadorTempoB <= args->tempoMedio)
		{
			sleep(1);
			args->contadorTempoB++;
		}

		printf("\nThread %d saiu na zona B\n", args->id);
		enqueueCli(&q, 7, *args);
		display(&q);
		sem_post(&sem2); // incrementa semaforo o que quer dizer que saiu da zona

		break;
	}
}

void zonaC(struct cliente *args)
{
	while (true)
	{
		int valorSemaforo3;
		int valorSemaforoListas;
		int valorMaximo = 0;

		printf("\nThread %d na zona C\n", args->id);

		sem_getvalue(&sem3, &valorSemaforo3);

		if (valorSemaforo3 == 0 || NumeroNafila4 > 0)
		{
			args->listaPrioridade = true;
			pthread_mutex_lock(&threadC1);
			printf("\nThread %d na fila da zona C\n", args->id);
			enqueueCli(&q, 13, *args);
			pthread_mutex_lock(&NumeroNafilaC);
			NumeroNafila4=NumeroNafila4+1;
			pthread_mutex_unlock(&NumeroNafilaC);
			display(&q);

			pthread_mutex_lock(&threadLista);
			insert_sorted(&root, args->prioridade); // adiciono na lista ligada de forma ordenada do maior para menor
			pthread_mutex_unlock(&threadLista);

			// for(Node * curr= root; curr!=NULL; curr=curr->next){
			// 	//printf("AValorLista:%d\n",curr->x);
			// }

			while (true)
			{
				sem_wait(&semL2);
				while (valorSemaforo3 == 0)
				{
					Node *curr2 = root;
					// printf("A maior da lista sera: %d\n",curr2->x);
					valorMaximo = curr2->x;
					sem_getvalue(&sem3, &valorSemaforo3);
				}

				pthread_mutex_lock(&threadLista2);

				if (args->prioridade == valorMaximo)
				{
					// printf("Vai passar a thread com maior prioridade: %d",valorMaximo);
					pthread_mutex_lock(&NumeroNafilaC);
					NumeroNafila4=NumeroNafila4-1;
					pthread_mutex_unlock(&NumeroNafilaC);
					break;
				}

				if (args->prioridade != valorMaximo)
				{
					Node *curr2 = root;
					// printf("A maior da lista sera: %d\n",curr2->x);
					valorMaximo = curr2->x;
					pthread_mutex_unlock(&threadLista2);
					sem_post(&semL2);
				}
			}
		}

		sem_wait(&sem3); // semaforo inicializado a 2

		if (args->listaPrioridade == true)
		{
			// printf("Entrou aqui a thread de maior prioridade %d com o id %d",args->prioridade,args->id);
			Node *curr2 = root;
			remove_element(&root, valorMaximo);
			if (curr2->x != NULL)
			{
				// printf("A maior da lista sera: %d\n",curr2->x);
				valorMaximo = curr2->x;
			}
			sem_post(&semL2);
			pthread_mutex_unlock(&threadLista2);
		}

		printf("\nThread %d entra na zona C\n", args->id);

		enqueueCli(&q, 14, *args);
		display(&q);


		while (args->contadorTempoC <= args->tempoMedio) // while (args->contadorTempoC <= args->tempoMedio)
		{
			sleep(1);
			args->contadorTempoC++;
		}

		printf("\nThread %d sai da zona C\n", args->id);
		enqueueCli(&q, 15, *args);
		display(&q);
		sem_post(&sem3);

		break;
	}
}

void zonaD(struct cliente *args)
{
	while (true)
	{
		bool mutexfilaD = false;
		int valorSemaforo;
		int Prim_el;
		printf("\nThread %d na zona D\n", args->id);

		sem_getvalue(&sem, &valorSemaforo); // tenho aqui o valor do semaforo sempre que uma thread entra
		if(valorSemaforo != 0 && !isEmpty(&filaD)){
			sem_wait(&semFilaD);
			mutexfilaD = true;
		}
		if (valorSemaforo == 0)
		{ // mal a thread entra e ver que o semaforo é zero vai para a fila
			printf("\nThread %d na fila zona D\n", args->id);
			Prim_el = getFirstElement(&filaD).num_evento;
			enqueueCli(&q, 16, *args);
			display(&q);
			enqueueNPessoas(&filaD, args->id, 1);
			args->entrouNaFila = true;
			displayFila(&filaD, "D");
			printf("\nPrimeiro elemento da queue a entrar: %d\n", Prim_el);

			while (true)
			{
				sem_getvalue(&sem, &valorSemaforo);
				Prim_el = getFirstElement(&filaD).num_evento;
				printf("Valor semaforo: %d",valorSemaforo);
				if(valorSemaforo != 0 && Prim_el == args->id){
					break;
				}
				else if (args->tempoNaFilaD >= args->tempoDesistencia)
				{
					printf("\nThread %d desiste da zona D\n", args->id);
					enqueueCli(&q, 17, *args);
					display(&q);
					break;
				}
				sleep(1);
				args->tempoNaFilaD++;
				//printf("Valor semaforo: %d",valorSemaforo);
			}

			if (args->tempoNaFilaD >= args->tempoDesistencia)
			{
				dequeue(&filaD);
				if(!isEmpty(&filaD))
					displayFila(&filaD, "D");
				else{
					printf("Fila D vazia\n");
				}
				args->entrouNaFila = false;
				break;
			}
		}

		if(args->entrouNaFila){
			dequeue(&filaD);
			if(!isEmpty(&filaD))
				displayFila(&filaD, "D");
			else{
				printf("Fila D vazia\n");
			}
			args->entrouNaFila = false;
		}

		sem_wait(&sem4); // semaforo inicializado a 2
		if(mutexfilaD){
			mutexfilaD = false;
			sem_post(&semFilaD);
		}

		printf("\nThread %d entra na zona D\n", args->id);
		enqueueCli(&q, 18, *args);
		display(&q);

		if(uma_vez){
			flaq_criar_prod = true; // produtores são criados
			uma_vez = false;
		}

		// Wait for a full slot in the buffer and lock the mutex
		sem_wait(&semFull);
		// To ensure that only one thread can access the buffer at a time, lock the mutex
		pthread_mutex_lock(&mutexBuffer);

		if(args->capital < custo_hamb){
			enqueueCli(&q, 26, *args);
			display(&q);
			printf("Thread %d nao tem dinheiro suficiente para comprar o hamburguer", args->id);
			pthread_mutex_unlock(&mutexBuffer);
			// Unlock the mutex and increment the semEmpty semaphore to signal that the buffer has one more empty slot
			sem_post(&semEmpty);

			printf("\nThread %d sai da zona D\n", args->id);
			enqueueCli(&q, 19, *args);
			display(&q);
			sem_post(&sem4); // incrementa semaforo o que quer dizer que saiu da zona
			break;
		}

		// int y;
		//  Check if it is the buffer is empty

		while (bufferHamburg[0] == 0)
		{
			if(bufferHamburg[0] != 0){
				break;
			}
		}
		
		
		if (bufferHamburg[0] != 0)
		{
			// seguidamente ira contar o tempo que demora a consumir o hamburger
			printf("\nThe Consumer %d is eating a hamburguer\n", args->id);
			enqueueCli(&q, 20, *args);
			display(&q);

			while (args->contadorTempoD <= args->tempoConsumo)
			{
				sleep(1);
				args->contadorTempoD++;
			}
			printf("\nThe Consumer %d has already eated a hamburguer\n", args->id);
			enqueueCli(&q, 21, *args);
			display(&q);

			// Remove the last item in the buffer
			// y = bufferHamburg[count - 1];
			bufferHamburg[count - 1] = 0;
			count--;
			// Consume the item

			// Display the current state of the buffer
			BufferDisplay();
		}

		pthread_mutex_unlock(&mutexBuffer);
		// Unlock the mutex and increment the semEmpty semaphore to signal that the buffer has one more empty slot
		sem_post(&semEmpty);

		printf("\nThread %d sai da zona D\n", args->id);
		enqueueCli(&q, 19, *args);
		display(&q);
		sem_post(&sem4); // incrementa semaforo o que quer dizer que saiu da zona
		break;
	}
}

void estatisticaFunction(struct cliente *args)
{
	int valorSemaforoEstatistica;

	sem_wait(&semL); // TER EM ETENÇÃO QUE A INICIALIZACAO DO SEMAFRO VARIA CONSOANTE O NUMERO DE THREADS INSERIDAS
	sem_getvalue(&semL, &valorSemaforoEstatistica);
	if (valorSemaforoEstatistica == 0)
	{
		enqueueNPessoas(&q, 9, args->id);
		display(&q);
		enqueueNPessoas(&q, 24, 0);
		display(&q);
		flag_threads_acabam = true;
		while(1){
			if(isEmpty(&q)){
				pthread_cancel(threadTime);
				pthread_cancel(create_prod);
				pthread_cancel(threadMessage);
				break;
			}
		}
	}
}

void *atribuirtAtributos(struct cliente *args)
{

	pthread_mutex_lock(&mutexCliente);

	FILE *fd = fopen("log.txt", "a"); // abre o ficheiro para ter acesso e utiliza o comando append

	ficheiro_de_leitura(); // coloca sempre os valores atuais do ficheiro de configuracao no array

	int Numero_DeGrupos = atoi(NumeroDeGrupos);
	int Numero_DePessoas = atoi(NumeroDePessoas);
	int tempo_chegada = atoi(TempoMedioDeChegada);
	int tempo_desistencia = atoi(TempoMedioDeDesistencia);
	int tempo_consumo = atoi(TempoMedioDeConsumo);
	int tempo_zona = atoi(TempoMedioNaZona);
	int capital_cliente = atoi(CapitalMedioPorCliente);
	custo_hamb = atoi(CustoDoHamburguer);

	args->id = id;
	args->numeroPessoas = rand() % 5 + 1;
	args->prioridade = rand() % 100 + 1;
	args->zona = "PistaA";
	args->tempoMedio = rand() % 7 + tempo_zona; // 15
	args->tempoNaFilaA = 0;
	args->tempoNaFilaB = 0;
	args->tempoNaFilaC = 0;
	args->tempoNaFilaD = 0;
	args->tempoDesistencia = rand() % 5 + tempo_desistencia; // 11
	args->capital = rand() % 5 + capital_cliente;
	args->tempoConsumo = rand() % 7 +tempo_consumo; // 11
	args->tempoChegada = rand() % 2 + tempo_chegada; // 11
	args->custoHamburguer = custo_hamb;
	args->inicializado = true;
	args->entrouNaFila = false;
	args->VIP = rand() % 2;

	printf("Preco de hamburguer: %d", args->custoHamburguer);

	printf("\nThread criada\n");

	printf("id: %d;\n numero de Pessoas: %d;\n prioridade: %d;\n zona: %s\n", args->id, args->numeroPessoas, args->prioridade, args->zona);

	fclose(fd); // fecha o ficheiro

	enqueueCli(&q, 1, *args);
	display(&q);

	id++;

	pthread_mutex_unlock(&mutexCliente);

	args->contadorTempoA = 0;
	while (args->contadorTempoA <= args->tempoChegada)
	{
		args->contadorTempoA++;
		sleep(1);
	}

	enqueueCli(&q, 25, *args);
	display(&q);


	zonaA(args);

	if (args->VIP == 1)
	{
		args->zona = "PistaB";
		zonaB(args);
	}
	else
	{
		enqueueCli(&q, 12, *args);
		display(&q);
	}

	args->zona = "PistaC";

	zonaC(args);

	args->zona = "PistaD";

	zonaD(args);

	estatisticaFunction(args);

	pthread_mutex_lock(&mutexSair);
	if (pthread_join(th[args->id], NULL) != 0)
	{
		perror("Failed to join thread");
	}
	enqueueNPessoas(&q, 9, args->id);
	display(&q);
	printf("\nAcabou a thread %d\n", args->id);

	return NULL;
	// return args;
}

// Thread function for producer threads
void *producer(struct produtores *prod)
{
	int tempo_producao = atoi(TempoMedioDeProducao);
	int custo_producao = atoi(CustoDeProducao);
	prod->id = idProd;
	prod->contadorTempoProducao = 0;
	prod->tempoMedioProducao = rand() % 3 + tempo_producao;
	prod->custoProducao = custo_producao;
	prod->inicializado = true;
	idProd++;
	printf("\n Producer %d\n", prod->id);
	while (1)
	{
		// Produce a number ("1") that represents a hamburguer
		int x = 1;
		// Add the number to the buffer
		sem_wait(&semEmpty);
		pthread_mutex_lock(&mutexBuffer);
		if (contadorProd == prod->id)
		{ // Check if it is this thread's turn to produce

			// enqueueProd(19, *prod);

			printf("\nThe Producer %d is cooking a hamburguer\n", prod->id);
			enqueueProd(&q, 22, *prod);
			display(&q);
			while (prod->contadorTempoProducao <= prod->tempoMedioProducao)
			{
				sleep(1);
				prod->contadorTempoProducao++;
			}
			prod->contadorTempoProducao = 0;

			// enqueueProd(20, *prod);

			printf("The Producer %d made a hamburguer\n", prod->id);
			enqueueProd(&q, 23, *prod);
			display(&q);

			// Add the number to the buffer
			bufferHamburg[count] = x;
			count++;

			// Display the current state of the buffer
			BufferDisplay();
			printf("Contador Producer: %d\n\n", contadorProd);
			// Reset the counter if it has reached the maximum value
			if (contadorProd == 1)
			{
				contadorProd = 0;
			}
			else
			{
				contadorProd++;
			}
			// Unlock the mutex and increment the semFull semaphore to signal that the buffer has one more full slot
		}
		pthread_mutex_unlock(&mutexBuffer);
		sem_post(&semFull);
	}
}

void *funcThreadMessage(void *args)
{
	struct sockaddr_un name;
	int ret;
	connection_socket;
	int data_socket;
	int result;
	int data;
	int i;
	char buffer[BUFFER_SIZE];
	int contadorTempoNaZonaA = 0;
	int lock = 0;

	// no caso de o programa ter saido sem exito no ultimo run, remove a socket

	unlink(SOCKET_NAME);

	// cria a socket
	connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);

	if (connection_socket == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	printf("Master socket created\n");

	// inicializacao
	memset(&name, 0, sizeof(struct sockaddr_un));

	name.sun_family = AF_UNIX;
	strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);

	ret = bind(connection_socket, (const struct sockaddr *)&name, sizeof(struct sockaddr_un));

	if (ret == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	printf("bind() call succeed\n");

	// esta preparado para 20 clintes
	ret = listen(connection_socket, 20);
	if (ret == -1)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	//------------------------------------------------------------------------------------------------------------
	/*esta sempre a correr o servidor*/
	for (;;)
	{
		// espera por conecao
		printf("Waiting on accept() sys call\n");

		data_socket = accept(connection_socket, NULL, NULL);

		if (data_socket == -1)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}

		printf("Connection accepted from client\n");

		for (;;)
		{
			int w = 0;
			// printf("\nMutex lock %d from simulador\n\n", w); // so para ver se esta a entrar no mutex
			memset(buffer, 0, BUFFER_SIZE); // coloca a buffer  a zero para mandar os dados
			pthread_mutex_lock(&mutex);		// numero de grupos vem do cliente é como se fosse o indice para cada grupo

			if(flag_thr_messagem){
				printf("\n\nThread finish mensagem\n\n");
				break;
			}

			//sleep(1);
			if (!isEmpty(&q))
			{
				msg m = dequeue(&q);
				if (m.prod.inicializado)
				{
					// Convert the message data to a string to send over the socket
					sprintf(buffer, "%d#%d#%d", m.num_evento, m.prod.id, m.prod.custoProducao);
					printf("Sending message to client: %s\n", buffer);
					ret = write(data_socket, buffer, BUFFER_SIZE);
					if (ret == -1)								   // se der erro ao escrever
					{
						perror("write");	// se der erro a escrever
						exit(EXIT_FAILURE); // sai do programa
					}
					// Send the message to the client
					if(!isEmpty(&q)){
						display(&q);
					}
					else{
						printf("\nQueue is empty\n");
					}
				}
				else if (m.cli.inicializado)
				{
					// Convert the message data to a string to send over the socket
					sprintf(buffer, "%d#%d#%d#%s#%d#%d#%d", m.num_evento, m.cli.numeroPessoas, m.cli.prioridade, m.cli.zona, m.cli.id, m.cli.VIP, m.cli.custoHamburguer);
					printf("Sending message to client: %s\n", buffer);
					// Send the message to the client
					ret = write(data_socket, buffer, BUFFER_SIZE); // manda para o socket o que esta dentro da buffer
					if(!isEmpty(&q)){
						display(&q);
					}
					else{
						printf("\nQueue is empty\n");
					}
					if (ret == -1)								   // se der erro ao escrever
					{
						perror("write");	// se der erro a escrever
						exit(EXIT_FAILURE); // sai do programa
					}

					if (m.num_evento == 1)
					{
						pthread_mutex_unlock(&mutexCriar);
						printf("\nMutexCriar unlock from simulador\n\n");
					}
					else if (m.num_evento == 13)
					{
						pthread_mutex_unlock(&threadC1);
						printf("\nMutexC1 unlock from simulador\n\n");
					}
				}
				else
				{
					if (m.num_evento == 9)
					{
						sprintf(buffer, "%d#%d", m.num_evento, m.numero_de_clientes_total);
						printf("Sending message to client: %s\n", buffer);
						ret = write(data_socket, buffer, BUFFER_SIZE);
						if (ret == -1)
						{
							perror("write");
							exit(EXIT_FAILURE);
						}
						if(!isEmpty(&q)){
							display(&q);
						}
						else{
							printf("\nQueue is empty\n");
						}
						printf("\nMutex sair unlock from simulador\n\n");
						pthread_mutex_unlock(&mutexSair);
					}
					else if (m.num_evento == 10)
					{
						sprintf(buffer, "%d#%d", m.num_evento, CLIENTES_CRIADOS);
						printf("Sending message to client: %s\n", buffer);
						ret = write(data_socket, buffer, BUFFER_SIZE);
						if (ret == -1)
						{
							perror("write");
							exit(EXIT_FAILURE);
						}
						if(!isEmpty(&q)){
							display(&q);
						}
						else{
							printf("\nQueue is empty\n");
						}
						finalizar_simulacao = false;
					}
					else if (m.num_evento == 24)
					{
						sprintf(buffer, "%d", m.num_evento);
						printf("Sending message to client: %s\n", buffer);
						ret = write(data_socket, buffer, BUFFER_SIZE);
						if (ret == -1)
						{
							perror("write");
							exit(EXIT_FAILURE);
						}
						if(!isEmpty(&q)){
							display(&q);
						}
						else{
							printf("\nQueue is empty\n");
						}
					}
				}
			}
			pthread_mutex_unlock(&mutex);
			// printf("\nMutex unlock %d from simulador\n\n", w);
		}
		if(flag_thr_messagem){
			printf("\n\nThread finish 2\n\n");
			break;
		}
		memset(buffer, 0, BUFFER_SIZE); // volta a esvaziar a buffer aqui para proximas interacoes
		close(data_socket);				// fecho o conexao com o socket
	}

	// fecha a socket
	close(connection_socket);
	printf("connection closed..\n");

	unlink(SOCKET_NAME);
	//exit(EXIT_SUCCESS);
}

void createThread()
{
	sem_init(&sem, 0, NMaxA);
	sem_init(&sem2, 0, NMaxB);
	sem_init(&sem3, 0, NMaxC);
	sem_init(&sem4, 0, NMaxD);
	sem_init(&semL, 0, CLIENTES_CRIADOS);
	sem_init(&semL2, 0, 1);
	sem_init(&semFilaA, 0, 0);
	sem_init(&semFilaB, 0, 0);
	sem_init(&semFilaD, 0, 0);

	sem_init(&semEmpty, 0, 3); // Initialize the semEmpty semaphore with a count of 3
	sem_init(&semFull, 0, 0);  // Initialize the semFull semaphore with a count of 0

	int TempoTotalDeSimulacao = atoi(Numero_Total_TempoDeSimulacao);
	struct cliente *res;

	if (pthread_create(&threadMessage, NULL, &funcThreadMessage, NULL) != 0)
	{
		perror("Failed to create thread");
	}

	if (pthread_create(&threadTime, NULL, &funcThreadTime, &TempoTotalDeSimulacao) != 0)
	{
		perror("Failed to create thread");
	}


	for (int i = 0; i < CLIENTES_CRIADOS; i++)
	{
		pthread_mutex_lock(&mutexCriar);
		if (pthread_create(&th[i], NULL, (void *)&atribuirtAtributos, &array_clientes[i]) != 0)
		{
			perror("Nao foi criado uma thread cliente");
		}
	}

	if (pthread_join(threadMessage, NULL) != 0)
	{
		perror("Failed to join thread");
	}
	printf("\nAcabou a threadMensage\n");

	// Destroy the semaphores
	sem_destroy(&semEmpty);
	sem_destroy(&semFull);

	sem_destroy(&semFilaA);
	sem_destroy(&semFilaB);
	sem_destroy(&semFilaD);
	sem_destroy(&semL2);
	sem_destroy(&semL);
	sem_destroy(&sem4);
	sem_destroy(&sem3);
	sem_destroy(&sem2);
	sem_destroy(&sem);

	//exit(EXIT_SUCCESS);
}

void *CreateProdThread()
{
	while (true)
	{
		if (flaq_criar_prod)
		{
			for (int i = 0; i < PRODUTORES_CRIADOS; i++) {
				if(pthread_create(&thrProd_id[i], NULL, (void *)&producer, &array_produtores[i]) != 0){
					perror("Failed to create thread");
				}
				printf("Produtor %d criado\n", i);
			}
			flaq_criar_prod = false;
		}
	}
}

int main()
{
	printf("------------------------------SIMULADOR--------------------------------\n");
	init(&q);
	init(&filaA);
	init(&filaB);
	init(&filaD);

	ficheiro_de_leitura();

	CLIENTES_CRIADOS = atoi(ClientesCriados);
	PRODUTORES_CRIADOS = atoi(ProdutoresCriados);
	NMaxA = atoi(NumeroMaxNaZonaA);
	NMaxB = atoi(NumeroMaxNaZonaB);  
	NMaxC = atoi(NumeroMaxNaZonaC);  
	NMaxD = atoi(NumeroMaxNaZonaD);  

	//print in green CLIENTES_CRIADOS
	printf("\033[0;32mCLIENTES_CRIADOS: %d\033[0m\n", CLIENTES_CRIADOS);

	time_t mytime = time(NULL);
	srand((unsigned)time(&mytime));

	if(pthread_create(&create_prod, NULL, &CreateProdThread, NULL) != 0){
		perror("Failed to create thread");
	}
	createThread();

	pthread_cancel(create_prod);
	printf("\nAcabou a create_prod\n");

	return 0;
}