//-------Bibliotecas aqui --------
#include "header.h"
//------------------------------------
//--------------------------------------------------------------------------------------
char *dados[10][BUFFER_SIZE];
char NumeroPessasAdiconadas[5];
char data[MAX_LINE][MAX_LENGTH];

char PessoasQueEntraramA[6];
char PessoasQueEntraramB[6];
char PessoasQueEntraramC[6];
char PessoasQueEntraramD[6];

char PessoasFilaEntraramA[6];
char PessoasFilaEntraramB[6];
char PessoasFilaEntraramC[6];
char PessoasFilaEntraramD[6];

char PessoasDesistenciaEntraramA[6];
char PessoasDesistenciaEntraramB[6];
char PessoasDesistenciaEntraramC[6];
char PessoasDesistenciaEntraramD[6];

char LucroTotalPad[6];

char NumeroTotalDiso[6];

char sairamDaZonaA[6];
char sairamDaZonaB[6];
char sairamDaZonaC[6];
char sairamDaZonaD[6];

char sairamVip[6];

char NumeroClientesNComerNaoDinherioSuf[6];
char NumeroDesisDisco[6];
char NumeroClientesSairDisc[6];
char NumeroDeHambProd[6];
char NumeroDeHambVend[6];
char DespPadaria[6];

int NumeroDePessoasEntraramA=0;
int NumeroDePessoasEntraramB=0;
int NumeroDePessoasEntraramC=0;
int NumeroDePessoasEntraramD=0;

int NumeroDePessoasFilaA=0;
int NumeroDePessoasFilaB=0;
int NumeroDePessoasFilaC=0;
int NumeroDePessoasFilaD=0;

int NumeroDeDesistenciasA=0;
int NumeroDeDesistenciasB=0;
int NumeroDeDesistenciasC=0;
int NumeroDeDesistenciasD=0;

int lucroTotalPadaria=0;

int NumeroTotalDentro=0;

int NumeroSairamDaZonaA=0;
int NumeroSairamDaZonaB=0;
int NumeroSairamDaZonaC=0;
int NumeroSairamDaZonaD=0;

int NumeroNaoEntraramVip=0;

int NumeroDeClientesNaoComeramPorNaoTerDinherioSuf = 0;
int NumeroDeDesistentesDisco = 0;
int NumeroDeClientesSairamDisco = 0;
int NumeroDeHamburgueresProduzidos = 0;
int NumeroDeHamburgueresVendidos = 0;
int DespesasPadaria = 0;

int numeroEvento;
int numeroAdicionadas;
int prioridadePessoas;
char *zona; 
int idDeGrupo;
int VIP;
char *checkVIP;
int id_cliente;
int numero_de_clientes;
int id_produtor;
//---------------------------------------------------------------------------------------


extern pthread_mutex_t mutexFinalizarSim;
extern pthread_mutex_t mutex;
pthread_mutex_t mutex_conf;

void escreveFicheiroLogVar(int n_evento,int id_grupo,int prioridade_id,int vip_id,int numeroPessoas_id)
{
	FILE *fe = fopen("log.txt", "a"); // abre o ficheiro "log.txt" para acrescentar

	char log[MAX_LINE] = "";  // string que guarda a informa��o sobre o evento
	char temp[MAX_LINE] = ""; // string que guarda o timesstamp

	time_t mytime = time(NULL);
	char *timestamp = ctime(&mytime);
	timestamp[strlen(timestamp) - 1] = 0;

	if (fe == NULL)
	{ // Caso d� erro escreve uma mensagem de erro
		printf("Dados do monitor n�o recebidos. Erro de exportacao\n");
	}

	else
	{ // Caso contr�rio indica o timestamp do evento e o numero da pessoa que acabou de passar
        if(n_evento==1){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);

            char *checkVIP;

            if(vip_id == 1){

                checkVIP = "é VIP";
            }
            else{
                checkVIP = "não é VIP";
            }
               
            
            sprintf(temp," || Foi adicionado %d pessoas do grupo %d, com prioridade %d e que %s\n",numeroPessoas_id,id_grupo, prioridade_id, checkVIP);

            strcat(log, temp);


            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==2){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp," || O grupo %d entrou na fila da Zona A\n", id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==3){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d entrou na Zona A\n", id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==4){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp," || O grupo %d vai sair da Zona A\n", id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==5){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d entrou na fila da Zona B\n", id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==6){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d entrou na Zona B\n", id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==7){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d vai sair da Zona B\n",id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==8){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d desistiu da fila da zona A\n",id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==9){ // Estes eventos nao acontcem ainda falta implementa r

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " Entrou mais %d pessoas\n", id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==10){  // Estes eventos nao acontcem ainda falta implementa r

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " Entrou mais %d pessoas\n", id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==11){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d desiste de estar na fila da zona B\n", id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==12){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d não conseguiu entrar na zona B, porque não é VIP\n", id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==13){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d entrou na fila da Zona C\n",id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==14){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp," || O grupo %d com prioridade %d entrou na Zona C\n",id_grupo,prioridade_id);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==15){  

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d vai sair da Zona C\n",id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==16){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d entrou na fila da Zona D\n",id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==17){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d desistiu da fila da zona D\n",id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==18){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp," || O grupo %d entrou na Zona D\n",id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==19){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d vai sair da Zona D\n",id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==20){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d está a comer um hambúrguer na Zona D\n",id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==21){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O grupo %d acabou de comer o hambúrguer na  Zona D\n", id_grupo);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==22){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O produtor %d está a cozinhar um hambúrguer na Zona D\n", id_produtor);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

        if(n_evento==23){

            sprintf(temp, "%s", timestamp);
            strcat(log, temp);
            sprintf(temp, " || O produtor %d acabou de cozinhar o hambúrguer na  Zona D\n", id_produtor);
            strcat(log, temp);

            for (int i = 0; log[i] != NULL; i++)
            { // Escreve caracter a caracter o que estiver no log
                fputc(log[i], fe);
            }

        }

		fclose(fe); // Bloqueia o acesso ao ficheiro
	}
}

int numSeparadores(char *orig)
{
    int conta = 0;
    for (int i = 0; i < sizeof(orig); i++)
    {
        if (orig[i] == '#')
        {
            conta++;
        }
    }
    return conta;
}

void atualizaValores(char variavel[], int valor, int linha)
{
    // Pointers de arquivo para o arquivo original e arquivo tempor�rio
    FILE *file, *temp;
    char str_valor[10];

    // Guarde o nome do arquivo e o nome do arquivo tempor�rio
    char filename[FILENAME_SIZE] = "ConfiguracoesMonitor.conf";
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
    pthread_mutex_unlock(&mutex_conf);
}

void substring(char *orig, char *substr, int index, int length) // fun��o com o objetivo de retirar apenas parte do que queremos de uma string que esta dentro de um array
{
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

void ficheiro_de_leitura()
{
    FILE *fd = fopen("ConfiguracoesMonitor.conf", "r"); // abre o ficheiro para ter acesso e utiliza o comando read

    if (fd == NULL)
    { // se o ficheiro estiver vazio ir� dar informa��o de erro
        printf("O ficheiro com as configura��es n�o abre!! \n");
        return -1;
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
        substring(data[0], PessoasQueEntraramA, 25, 5);
        substring(data[1], PessoasQueEntraramB, 25, 5);
        substring(data[2], PessoasQueEntraramC, 25, 5);
        substring(data[3], PessoasQueEntraramD, 25, 5);

        substring(data[4], PessoasFilaEntraramA, 21, 5);
        substring(data[5], PessoasFilaEntraramB, 21, 5);
        substring(data[6], PessoasFilaEntraramC, 21, 5);
        substring(data[7], PessoasFilaEntraramD, 21, 5);

        substring(data[8], PessoasDesistenciaEntraramA, 22, 5);
        substring(data[9], PessoasDesistenciaEntraramB, 22, 5);
        substring(data[10], PessoasDesistenciaEntraramD, 22, 5);

        substring(data[11], LucroTotalPad, 18, 5);

        substring(data[12],NumeroTotalDiso,30,5);

        substring(data[13], sairamDaZonaA, 20, 5);
        substring(data[14], sairamDaZonaB, 20, 5);
        substring(data[15], sairamDaZonaC, 20, 5);
        substring(data[16], sairamDaZonaD, 20, 5);

        substring(data[17], sairamVip, 13, 5);

        substring(data[18], NumeroClientesNComerNaoDinherioSuf,47, 5);
        substring(data[19], NumeroDesisDisco, 17, 5);
        substring(data[20], NumeroClientesSairDisc, 28, 5);
        substring(data[21], NumeroDeHambProd, 31, 5);
        substring(data[22], NumeroDeHambVend, 29, 5);
        substring(data[23], DespPadaria, 16,5);

        fclose(fd); // fecha o ficheiro aberto a cima
    }
}

void substring2(char orig[10], int nHash) // funcao com o objetivo de retirar apenas parte do que queremos de uma string que esta dentro de um array
{
    int i = 0;

    char *p = strtok(orig, "#"); // separa o que esta dentro da string em varias strings

    while (p)
    {
        dados[i][BUFFER_SIZE] = p;
        p = strtok(NULL, "#");
        i++;
    }
}

void conecaoCliente()
{
    struct sockaddr_un addr;
    int i;
    int ret;
    int data_socket;
    char buffer[BUFFER_SIZE];
    int pessoasParaZonaA;
    int numeroDePessoasNasZonas = 0;
    int verificaPessoas = 0;
    int prioridadePistaA = 40;

    /* Create data socket. */

    data_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if (data_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));

    /* Connect socket to socket address */

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

    ret = connect(data_socket, (const struct sockaddr *)&addr, sizeof(struct sockaddr_un));

    if (ret == -1)
    {
        fprintf(stderr, "The server is down.\n");
        exit(EXIT_FAILURE);
    }

    for (;;)
    {
        //sleep(2);
        /*Apartir daqui fação meu codigo*/
        /* Receive and read result. */
        //printf("\nMutex lock from monitor\n\n");
        ficheiro_de_leitura();
        pthread_mutex_lock(&mutex);

        memset(buffer, 0, BUFFER_SIZE);

        ret = read(data_socket, buffer, BUFFER_SIZE);
        if (ret == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        substring2(buffer, numSeparadores(buffer));

        //--------------------------------------//

        numeroEvento = atoi(dados[0][BUFFER_SIZE]);

        time_t now = time(NULL);
        struct tm *cur_time = localtime(&now);  

        // --------------------------------------------- Eventos --------------------------------------------- //

        switch (numeroEvento)
        {               
            case 1:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo
                VIP = atoi(dados[5][BUFFER_SIZE]); // vem do buffer onde contem se o grupo é VIP ou nao

                NumeroTotalDentro=atoi(NumeroTotalDiso);           
                NumeroTotalDentro=NumeroTotalDentro+1;
                atualizaValores("NumeroDePessoasQueEntraramNaD",NumeroTotalDentro,13);
                              
                if(VIP == 1){
                    checkVIP = "é VIP";
                }
                else{
                    checkVIP = "não é VIP";
                }
                // atributirStruct(array_clientes,numeroAdicionadas,prioridadePessoas);
                printf("Foi adicionado %d pessoas do", numeroAdicionadas);
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf("  com prioridade %d e que %s\n", prioridadePessoas, checkVIP);

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,prioridadePessoas,VIP,numeroAdicionadas);

                break;

            case 2:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 2\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo
                
                NumeroDePessoasFilaA=atoi(PessoasFilaEntraramA);
                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" entrou na fila da ");
                printf("\033[0;34mZona A\033[0m\n");

                NumeroDePessoasFilaA++;
                atualizaValores("NumeroDePessoasFilaA",NumeroDePessoasFilaA,5);
                
                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);
                
                break;
            
            case 3:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 3\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroDePessoasEntraramA=atoi(PessoasQueEntraramA);

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" entrou na ");
                printf("\033[0;34mZona A\033[0m\n");
                NumeroDePessoasEntraramA++;
                atualizaValores("NumeroDePessoasEntraramA",NumeroDePessoasEntraramA,1);

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;
            
            case 4:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 4\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroSairamDaZonaA=atoi(sairamDaZonaA);
                NumeroDeClientesSairamDisco = atoi(NumeroClientesSairDisc);
                NumeroDeClientesSairamDisco++;                

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" vai sair da ");
                printf("\033[0;34mZona A\033[0m\n");
                NumeroSairamDaZonaA=NumeroSairamDaZonaA+1;
                atualizaValores("NumeroSairamDaZonaA",NumeroSairamDaZonaA,14);
                atualizaValores("NumeroDeClientesSairamDisco", NumeroDeClientesSairamDisco, 21);
                
                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;
            
            case 5:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 5\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroDePessoasFilaB=atoi(PessoasFilaEntraramB);

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" entrou na fila da ");
                printf("\033[0;34mZona B\033[0m\n");
                NumeroDePessoasFilaB=NumeroDePessoasFilaB+1;
                atualizaValores("NumeroDePessoasFilaB",NumeroDePessoasFilaB,6);
                

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);
                
                break;
            
            case 6:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 6\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroDePessoasEntraramB=atoi(PessoasQueEntraramB);

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" entrou na ");
                printf("\033[0;34mZona B\033[0m\n");
                NumeroDePessoasEntraramB=NumeroDePessoasEntraramB+1;
                atualizaValores("NumeroDePessoasEntraramB",NumeroDePessoasEntraramB,2);
                

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;
            
            case 7:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 7\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroSairamDaZonaB=atoi(sairamDaZonaB);
                NumeroDeClientesSairamDisco = atoi(NumeroClientesSairDisc);
                NumeroDeClientesSairamDisco++;

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" vai sair da ");
                printf("\033[0;34mZona B\033[0m\n");
                NumeroSairamDaZonaB=NumeroSairamDaZonaB+1;
                atualizaValores("NumeroSairamDaZonaB",NumeroSairamDaZonaB,15);
                atualizaValores("NumeroDeClientesSairamDisco", NumeroDeClientesSairamDisco, 21);

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;
            
            case 8:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 8\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroDeDesistenciasA=atoi(PessoasDesistenciaEntraramA);
                NumeroDeDesistentesDisco = atoi(NumeroDesisDisco);

                NumeroDeDesistentesDisco++;

                printf("O");
                printf("\033[0;32m grupo %d\033[0m", idDeGrupo);
                printf(" desistiu de estar na fila da ");
                printf("\033[0;34mZona A\033[0m\n");
                NumeroDeDesistenciasA=NumeroDeDesistenciasA+1;
                atualizaValores("NumeroDeDesistenciasA",NumeroDeDesistenciasA,9);
                atualizaValores("NumeroDesisDisco", NumeroDeDesistentesDisco, 20);
                

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);    

                break;

            case 9:
                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 9\n");
                id_cliente = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de clientes criadas
                printf("O");
                printf("\033[0;32m grupo %d\033[0m", id_cliente);
                printf(" saiu da discoteca.\n");
                break;  
            
            case 10:
                //printf("Evento 10\n");
                numero_de_clientes = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de clientes criadas
                for (i = 0; i < numero_de_clientes /*+ 2*/; i++)
                {
                    printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                    printf("O");
                    printf("\033[0;32m grupo %d\033[0m", i);
                    printf(" saiu da discoteca.\n");
                }
                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                printf("Simulação terminada.\n");

                
                printf("------------------Estatisticas-------------------\n");
                printf("-------------------------------------------------\n");

                printf("Numero total de grupos que entraram na Discoteca: %d\n",NumeroTotalDentro);
                printf("Numero de vezes que grupos saiem em todas as zonas: %d\n",NumeroDeClientesSairamDisco);
                printf("Numero de vezes que grupos desistiram em todas as zonas: %d\n",NumeroDeDesistentesDisco);

                printf("Numero de grupos que entraram na pista A: %d\n",NumeroDePessoasEntraramA);
                printf("Numero de grupos que entraram na pista B: %d\n",NumeroDePessoasEntraramB);
                printf("Numero de grupos que entraram na pista C: %d\n",NumeroDePessoasEntraramC);
                printf("Numero de grupos que entraram na pista D: %d\n",NumeroDePessoasEntraramD);

                printf("Numero de grupos que entraram na fila da pista A: %d\n",NumeroDePessoasFilaA);
                printf("Numero de grupos que entraram na fila da pista B: %d\n",NumeroDePessoasFilaB);
                printf("Numero de grupos que entraram na fila da pista C: %d\n",NumeroDePessoasFilaC);
                printf("Numero de grupos que entraram na fila da pista D: %d\n",NumeroDePessoasFilaD);

                printf("Numero de grupos que desistiram da fila na pista A: %d\n",NumeroDeDesistenciasA);
                printf("Numero de grupos que desistiram da fila na pista B: %d\n",NumeroDeDesistenciasB);
                printf("Numero de grupos que desistiram da fila na pista D: %d\n",NumeroDeDesistenciasD);

                printf("Numero de grupos que sairam da pista A: %d\n",NumeroSairamDaZonaA);
                printf("Numero de grupos que sairam da pista B: %d\n",NumeroSairamDaZonaB);
                printf("Numero de grupos que sairam da pista C: %d\n",NumeroSairamDaZonaC);
                printf("Numero de grupos que sairam da pista D: %d\n",NumeroSairamDaZonaD);

                printf("Numero de grupos que nao entraram na pista B por nao serem VIP: %d\n",NumeroNaoEntraramVip);

                printf("Numero de grupos que nao comeram, por nao terem dinheiro suficiente: %d\n",NumeroDeClientesNaoComeramPorNaoTerDinherioSuf);

                printf("Despesas no total da padaria: %d€\n", DespesasPadaria);
                printf("Lucro total da padaria: %d€\n", lucroTotalPadaria);
                printf("Numero de hamburgueres produzidos: %d\n", NumeroDeHamburgueresProduzidos);
                printf("Numero de hamburgueres vendidos: %d\n", NumeroDeHamburgueresVendidos);

                printf("-------------------------------------------------\n");
                printf("-------------------------------------------------\n");

                close(data_socket); /* Close socket. */
                exit(EXIT_SUCCESS);

                break;

            case 11:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 11\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroDeDesistenciasB=atoi(PessoasDesistenciaEntraramB);
                NumeroDeDesistentesDisco = atoi(NumeroDesisDisco);

                NumeroDeDesistentesDisco++;

                printf("O");
                printf("\033[0;32m grupo %d\033[0m", idDeGrupo);
                printf(" desistiu de estar na fila da ");
                printf("\033[0;34mZona B\033[0m\n");
                NumeroDeDesistenciasB=NumeroDeDesistenciasB+1;
                atualizaValores("NumeroDeDesistenciasB",NumeroDeDesistenciasB,10);
                atualizaValores("NumeroDesisDisco", NumeroDeDesistentesDisco, 20);

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 12:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 12\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo
                NumeroNaoEntraramVip=atoi(sairamVip);

                NumeroNaoEntraramVip=NumeroNaoEntraramVip+1;
                atualizaValores("NumeroNaoVip", NumeroNaoEntraramVip, 18);
                
                printf("O");
                printf("\033[0;32m grupo %d\033[0m", idDeGrupo);
                printf(" não conseguiu entrar na ");
                printf("\033[0;34mZona B\033[0m, porque não é VIP\n");

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 13:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 13\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroDePessoasFilaC=atoi(PessoasFilaEntraramC);
            
                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" entrou na fila da ");
                printf("\033[0;34mZona C\033[0m\n");
                NumeroDePessoasFilaC=NumeroDePessoasFilaC+1;
                atualizaValores("NumeroDePessoasFilaC",NumeroDePessoasFilaC,7);
                

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 14:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 14\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroDePessoasEntraramC=atoi(PessoasQueEntraramC);

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" com prioridade %d entrou na ",prioridadePessoas);
                printf("\033[0;34mZona C\033[0m\n");
                NumeroDePessoasEntraramC=NumeroDePessoasEntraramC+1;
                atualizaValores("NumeroDePessoasEntraramC",NumeroDePessoasEntraramC,3);
                

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;
                
            case 15:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 15\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroSairamDaZonaC=atoi(sairamDaZonaC);
                NumeroDeClientesSairamDisco = atoi(NumeroClientesSairDisc);
                NumeroDeClientesSairamDisco++;

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" vai sair da ");
                printf("\033[0;34mZona C\033[0m\n");
                NumeroSairamDaZonaC=NumeroSairamDaZonaC+1;
                atualizaValores("NumeroSairamDaZonaC",NumeroSairamDaZonaC,16);
                atualizaValores("NumeroDeClientesSairamDisco", NumeroDeClientesSairamDisco, 21);
                
                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 16:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 16\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo
                
                NumeroDePessoasFilaD=atoi(PessoasFilaEntraramD);

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" entrou na fila da ");
                printf("\033[0;34mZona D\033[0m\n");
                NumeroDePessoasFilaD=NumeroDePessoasFilaD+1;
                atualizaValores("NumeroDePessoasFilaD",NumeroDePessoasFilaD,8);
                

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 17:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 17\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroDeDesistenciasD=atoi(PessoasDesistenciaEntraramD);

                NumeroDeDesistentesDisco = atoi(NumeroDesisDisco);
                NumeroDeDesistentesDisco++;

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" desistiu da fila da ");
                printf("\033[0;34mZona D\033[0m\n");
                NumeroDeDesistenciasD=NumeroDeDesistenciasD+1;
                atualizaValores("NumeroDesisDisco", NumeroDeDesistentesDisco, 20);
                atualizaValores("NumeroDeDesistenciasD",NumeroDeDesistenciasD,11);
                

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 18:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 18\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroDePessoasEntraramD=atoi(PessoasQueEntraramD);

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" entrou na ");
                printf("\033[0;34mZona D\033[0m\n");
                NumeroDePessoasEntraramD=NumeroDePessoasEntraramD+1;
                atualizaValores("NumeroDePessoasEntraramD",NumeroDePessoasEntraramD,4);
                

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 19:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 19\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroSairamDaZonaD=atoi(sairamDaZonaD);
                NumeroDeClientesSairamDisco = atoi(NumeroClientesSairDisc);
                NumeroDeClientesSairamDisco++;

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" vai sair da ");
                printf("\033[0;34mZona D\033[0m\n");
                NumeroSairamDaZonaD=NumeroSairamDaZonaD+1;
                atualizaValores("NumeroSairamDaZonaD",NumeroSairamDaZonaD,17);
                atualizaValores("NumeroDeClientesSairamDisco", NumeroDeClientesSairamDisco, 21);
                

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 20:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 20\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" está a comer um hambúrguer na ");
                printf("\033[0;34mZona D\033[0m\n");

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 21:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 21\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo
                int lucro =  atoi(dados[6][BUFFER_SIZE]);

                lucroTotalPadaria=atoi(LucroTotalPad);
                lucroTotalPadaria=lucroTotalPadaria+lucro;

                NumeroDeHamburgueresVendidos=atoi(NumeroDeHambVend);
                NumeroDeHamburgueresVendidos++;

                atualizaValores("lucroTotalPadaria",lucroTotalPadaria,12);
                atualizaValores("NumeroDeHamburgueresVendidos",NumeroDeHamburgueresVendidos,23);

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" acabou de comer o hambúrguer na ");
                printf("\033[0;34mZona D\033[0m\n");

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 22:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 22\n");
                id_produtor = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                printf("O");
                printf("\033[0;33m produtor %d\033[0m", id_produtor);
                printf(" está a cozinhar um hambúrguer na ");
                printf("\033[0;34mZona D\033[0m\n");

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 23:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 23\n");
                id_produtor = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                int despesa = atoi(dados[2][BUFFER_SIZE]);

                DespesasPadaria=atoi(DespPadaria);
                DespesasPadaria=DespesasPadaria+despesa;

                NumeroDeHamburgueresProduzidos=atoi(NumeroDeHambProd);
                NumeroDeHamburgueresProduzidos++;

                printf("O");
                printf("\033[0;33m produtor %d\033[0m", id_produtor);
                printf(" acabou de cozinhar o hambúrguer na ");
                printf("\033[0;34mZona D\033[0m\n");

                atualizaValores("DespesasPadaria",DespesasPadaria,24);
                atualizaValores("NumeroDeHamburgueresProduzidos",NumeroDeHamburgueresProduzidos,22);

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 24:

                printf("------------------Estatisticas-------------------\n");
                printf("-------------------------------------------------\n");

                printf("Numero total de grupos que entraram na Discoteca: %d\n",NumeroTotalDentro);
                printf("Numero de vezes que grupos saiem em todas as zonas: %d\n",NumeroDeClientesSairamDisco);
                printf("Numero de vezes que grupos desistiram em todas as zonas: %d\n",NumeroDeDesistentesDisco);

                printf("Numero de grupos que entraram na pista A: %d\n",NumeroDePessoasEntraramA);
                printf("Numero de grupos que entraram na pista B: %d\n",NumeroDePessoasEntraramB);
                printf("Numero de grupos que entraram na pista C: %d\n",NumeroDePessoasEntraramC);
                printf("Numero de grupos que entraram na pista D: %d\n",NumeroDePessoasEntraramD);

                printf("Numero de grupos que entraram na fila da pista A: %d\n",NumeroDePessoasFilaA);
                printf("Numero de grupos que entraram na fila da pista B: %d\n",NumeroDePessoasFilaB);
                printf("Numero de grupos que entraram na fila da pista C: %d\n",NumeroDePessoasFilaC);
                printf("Numero de grupos que entraram na fila da pista D: %d\n",NumeroDePessoasFilaD);

                printf("Numero de grupos que desistiram da fila na pista A: %d\n",NumeroDeDesistenciasA);
                printf("Numero de grupos que desistiram da fila na pista B: %d\n",NumeroDeDesistenciasB);
                printf("Numero de grupos que desistiram da fila na pista D: %d\n",NumeroDeDesistenciasD);

                printf("Numero de grupos que sairam da pista A: %d\n",NumeroSairamDaZonaA);
                printf("Numero de grupos que sairam da pista B: %d\n",NumeroSairamDaZonaB);
                printf("Numero de grupos que sairam da pista C: %d\n",NumeroSairamDaZonaC);
                printf("Numero de grupos que sairam da pista D: %d\n",NumeroSairamDaZonaD);

                printf("Numero de grupos que nao entraram na pista B por nao serem VIP: %d\n",NumeroNaoEntraramVip);

                printf("Numero de grupos que nao comeram, por nao terem dinheiro suficiente: %d\n",NumeroDeClientesNaoComeramPorNaoTerDinherioSuf);

                printf("Despesas no total da padaria: %d€\n", DespesasPadaria);
                printf("Lucro total da padaria: %d€\n", lucroTotalPadaria);
                printf("Numero de hamburgueres produzidos: %d\n", NumeroDeHamburgueresProduzidos);
                printf("Numero de hamburgueres vendidos: %d\n", NumeroDeHamburgueresVendidos);

                printf("-------------------------------------------------\n");
                printf("-------------------------------------------------\n");

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                close(data_socket); /* Close socket. */
                exit(EXIT_SUCCESS);

                break;

            case 25:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 21\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" chegou à discoteca.\n");

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

            case 26:

                printf("%d:%d:%d    ", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
                //printf("Evento 21\n");
                numeroAdicionadas = atoi(dados[1][BUFFER_SIZE]); // variavel vem do buffer contem o numero de pessoas adicionadas
                prioridadePessoas = atoi(dados[2][BUFFER_SIZE]); // variavel vem do buffer contem o a prioridade do grentrou
                zona = dados[3][BUFFER_SIZE];
                idDeGrupo = atoi(dados[4][BUFFER_SIZE]); // vem do buffer onde contem o id do grupo

                NumeroDeClientesNaoComeramPorNaoTerDinherioSuf = atoi(NumeroClientesNComerNaoDinherioSuf);
                NumeroDeClientesNaoComeramPorNaoTerDinherioSuf++;
                atualizaValores("NumeroDeClientesNaoComeramPorNaoTerDinherioSuf", NumeroDeClientesNaoComeramPorNaoTerDinherioSuf, 19);

                printf("O");
                printf("\033[0;32m grupo %d\033[0m",idDeGrupo);
                printf(" saiem da ");
                printf("\033[0;34mzona D\033[0m");
                printf(", porque não tinham dinheiro suficiente para o hambúrguer.\n");

                escreveFicheiroLogVar(numeroEvento,idDeGrupo,0,0,0);

                break;

        }

        memset(buffer, 0, BUFFER_SIZE);
        pthread_mutex_unlock(&mutex);
        //printf("\nMutex unlock from monitor\n\n");
    }

    close(data_socket); /* Close socket. */
    exit(EXIT_SUCCESS);
}

int main()
{
    ficheiro_de_leitura();
    atualizaValores("NumeroDePessoasEntraramA", 0, 1);
    atualizaValores("NumeroDePessoasEntraramB", 0, 2);
    atualizaValores("NumeroDePessoasEntraramC", 0, 3);
    atualizaValores("NumeroDePessoasEntraramD", 0, 4);
    atualizaValores("NumeroDePessoasFilaA", 0, 5);
    atualizaValores("NumeroDePessoasFilaB", 0, 6);
    atualizaValores("NumeroDePessoasFilaC", 0, 7);
    atualizaValores("NumeroDePessoasFilaD", 0, 8);
    atualizaValores("NumeroDeDesistenciasA", 0, 9);
    atualizaValores("NumeroDeDesistenciasB", 0,10);
    atualizaValores("NumeroDeDesistenciasD", 0, 11);
    atualizaValores("lucroTotalPadaria", 0, 12);
    atualizaValores("NumeroDePessoasQueEntraramNaD", 0, 13);
    atualizaValores("NumeroSairamDaZonaA", 0,14);
    atualizaValores("NumeroSairamDaZonaB", 0, 15);
    atualizaValores("NumeroSairamDaZonaC", 0, 16);
    atualizaValores("NumeroSairamDaZonaD", 0, 17);
    atualizaValores("NumeroNaoVip", 0, 18);
    atualizaValores("NumeroDeClientesNaoComeramPorNaoTerDinherioSuf", 0, 19);
    atualizaValores("NumeroDeDesistentesDisco", 0, 20);
    atualizaValores("NumeroDeClientesSairamDisco", 0, 21);
    atualizaValores("NumeroDeHamburgueresProduzidos", 0, 22);
    atualizaValores("NumeroDeHamburgueresVendidos", 0, 23);
    atualizaValores("DespesasDaPadaria", 0, 24);


    printf("--------------------MONITOR--------------------------\n");
    conecaoCliente();
    return 0;
}