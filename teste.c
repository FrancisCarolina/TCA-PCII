#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//defines
#define MAXLIVROS 1000

//estruturas
typedef struct {
    char *titulo;
    char **autores;
    char *editora;
    int numeroPag;
    int ano;
    char *idioma;
    char **assuntos;
    int numAutores;
    int numAssuntos;
}Livro;

//globais
Livro *biblioteca;
int qntLivros = 0;

//funcoes declaração
void mensagemErro(int erro); //mostra msg de erro
void menu();                //mostrar opcoes do menu inicial
void opcaoMenu(int op);     //dispara a ação escolhida pelo user
int incluir();              //acoes iniciais para incluir livro
Livro criaLivro();          //criar novo livro digitado
void imprimeLivro(Livro livro);//imprimir livro
void salvarArquivo();       //salvar os livros criados em um arquivo txt
void recupararArquivo();    //recuperar dados salvos no arquivo
void menuListar();          //mostrar lista de opcoes no listar
void opcaoListar(int op);   //listar livros com a opcao escolhida
int listarBiblioteca(int pause);//listar todos os livros da biblioteca
int alterar();              //alterar livro

//main
int main(){
    int op = 1;
    recupararArquivo();
    while(op != 5){
        menu();
        scanf("%d", &op);
        fflush(stdin);
        system("cls");
        opcaoMenu(op);
    }
    return 0;
}

//funcoes implementação
void mensagemErro(int erro){
    printf("\n");
    if(erro == 0){
        printf("ERRO: Opcao invalida");
    }else if(erro == -1){
        printf("ERRO: Quantidade maxima de livros atingido");
    }else if(erro == -2){
        printf("ERRO: Numero de paginas invalido");
    }else if(erro == -3){
        printf("ERRO: Ano de lancamento invalido");
    }else if(erro == -4){
        printf("ERRO: Nao é possivel fazer essa acao");
    }else if(erro == -5){
        printf("ERRO: Numero do livro invalido");
    }else if(erro == -6){
        printf("ERRO: Nao ha livros o suficiente");
    }else if(erro == -10){
        printf("ERRO: Erro de alocacao de memoria");
    }else if(erro == -11){
        printf("ERRO: Nao foi possivel criar o aquivo");
    }else{
        printf("ERRO");
    }
    printf("\n");
    system("pause");
}
void menu(){
    system("cls");
    printf("\n\n-----MENU-----\n");
    printf("1 - Incluir Livro\n");
    printf("2 - Editar Livro\n");
    printf("3 - Excluir Livro\n");
    printf("4 - Listar Livro\n");
    printf("5 - Encerrar\n");
    printf("------------------\n");
    printf("Escolha uma opcao: \n");
}
void opcaoMenu(int op){
    int erro, opSub=-1;
    if(op < 1 || op > 5){
        mensagemErro(0);
    }else if(op < 5){ //opcoes entre 1 e 4
        if(op==1){
            erro = incluir();
            
        }else if(op==2){
            erro = alterar();
        }else if(op==3){

        }else{
            if(qntLivros<=0){
                erro = -2;
                opSub = 3;
            }
            while(opSub != 3){
                if(qntLivros>1){
                    menuListar();
                    scanf("%d", &opSub);
                    fflush(stdin);
                    opcaoListar(opSub);
                }else{
                    opcaoListar(2);
                    opSub = 3;
                }
            }
        }
        if(erro<0){
            mensagemErro(erro);
        }
    }else{//ao escolher sair
        if(qntLivros > 0){
            salvarArquivo();
        }
    }
}
int incluir(){
    if(qntLivros>= MAXLIVROS){
        return -1;
    }
    if(qntLivros==0){
        biblioteca = (Livro *)malloc(1 * sizeof(Livro));
    }else{
        biblioteca = (Livro *)realloc(biblioteca, (qntLivros + 1) * sizeof(Livro));
    }

    if(!biblioteca){
        return -10;
    }

    biblioteca[qntLivros] = criaLivro();
    system("cls");
    imprimeLivro(biblioteca[qntLivros]);
    qntLivros++;
    system("pause");
    return 1;
}
Livro criaLivro(){
    Livro livro;
    char strAux[100], op;
    int add;

    //titulo
    printf("\nDigite o titulo do livro: ");
    gets(strAux);
    livro.titulo = (char*)malloc((strlen(strAux)+1) * sizeof(char));
    strcpy(livro.titulo, strAux);
    fflush(stdin);

    //autores
    add = 1;
    livro.numAutores = 0;
    while(add){ //enquanto for verdadeiro (true = 1; false = 0)
        printf("\nDigite o nome do autor: ");
        gets(strAux);
        fflush(stdin);

        if(livro.numAutores == 0){
            livro.autores = (char**)malloc(1 * sizeof(char*));
        }else{
            livro.autores = (char**)realloc(livro.autores, (livro.numAutores+1) * sizeof(char*));
        }
        if(!livro.autores){ //caso erro de alocacao
            mensagemErro(-10);
            exit(1);
        }
        livro.autores[livro.numAutores] = (char*)malloc((strlen(strAux)+1) * sizeof(char));

        if(!livro.autores[livro.numAutores]){//caso erro de alocacao
            mensagemErro(-10);
            exit(1);
        }
        strcpy(livro.autores[livro.numAutores], strAux);
        livro.numAutores++;

        op ='x';
        while(op != 's' && op != 'n'){
            printf("\nAdcionar autor (s/n)?");
            scanf("%c", &op);
            fflush(stdin);
            op = tolower(op); //converter p minusculo
            if(op == 's' || op == 'n'){
                break;
            }
            mensagemErro(0);
        }

        if(op == 'n'){
            add = 0;
        }

    }

    //editora
    printf("\nDigite o nome da editora: ");
    gets(strAux);
    livro.editora = (char*)malloc((strlen(strAux)+1) * sizeof(char));
    strcpy(livro.editora, strAux);
    fflush(stdin);

    //numeroPag
    do{
        printf("\nDigite o numero de paginas do livro: ");
        scanf("%d", &livro.numeroPag);
        fflush(stdin);
        if(livro.numeroPag <= 0){
            mensagemErro(-2);
        }
    }while(livro.numeroPag<=0);

    //ano
    do{
        printf("\nDigite o ano de lancamento do livro: ");
        scanf("%d", &livro.ano);
        fflush(stdin);
        if(livro.ano <= 0){
            mensagemErro(-3);
        }
    }while(livro.ano<=0);

    //idioma
    printf("\nDigite o idioma do livro: ");
    gets(strAux);
    livro.idioma = (char*)malloc((strlen(strAux)+1) * sizeof(char));
    strcpy(livro.idioma, strAux);
    fflush(stdin);

    //assuntos
    add = 1;
    livro.numAssuntos = 0;
    while(add){ //enquanto for verdadeiro (true = 1; false = 0)
        printf("\nDigite o assunto: ");
        gets(strAux);
        fflush(stdin);

        if(livro.numAssuntos == 0){
            livro.assuntos = (char**)malloc(1 * sizeof(char*));
        }else{
            livro.assuntos = (char**)realloc(livro.assuntos, (livro.numAssuntos+1) * sizeof(char*));
        }
        if(!livro.assuntos){
            mensagemErro(-10);
            exit(1);
        }
        livro.assuntos[livro.numAssuntos] = (char*)malloc((strlen(strAux)+1) * sizeof(char));
        if(!livro.assuntos[livro.numAssuntos]){
            mensagemErro(-10);
            exit(1);
        }
        strcpy(livro.assuntos[livro.numAssuntos], strAux);
        livro.numAssuntos++;

        op ='x';
        while(op != 's' && op != 'n'){
            printf("\nAdcionar assunto (s/n)?");
            scanf("%c", &op);
            fflush(stdin);
            op = tolower(op); //converter p minusculo
            if(op == 's' || op == 'n'){
                break;
            }
            mensagemErro(0);
        }

        if(op == 'n'){
            add = 0;
        }

    }

    return livro;
}
void imprimeLivro(Livro livro){
    printf("\n");
    printf("Livro: \ttitulo: %s", livro.titulo);

    printf("\n\tautores: ");
    for(int i = 0; i<livro.numAutores; i++){
        printf("%s", livro.autores[i]);

        if(i< livro.numAutores-1){ //só pra imprimir virgula entre os autores
            printf(", ");
        }

    }

    printf("\n\teditora: %s", livro.editora);
    printf("\n\tNum de pags: %d", livro.numeroPag);
    printf("\n\tAno: %d", livro.ano);
    printf("\n\tIdioma: %s", livro.idioma);
    
    printf("\n\tassuntos: ");
    for(int i = 0; i<livro.numAssuntos; i++){
        printf("%s", livro.assuntos[i]);

        if(i< livro.numAssuntos-1){ //só pra imprimir virgula entre os assuntos
            printf(", ");
        }

    }
    printf("\n");
}
void salvarArquivo(){
    FILE *pArq;

    //abrir o arquivo
    pArq = fopen("livros.txt", "w"); //w para sobreescrever o arquivo

    if(pArq == NULL){ //se nao abrir corretamente mostra o erro
        mensagemErro(-11);
        exit(0);
    }

    for(int i = 0; i<qntLivros; i++){
        fprintf(pArq, "%s;", biblioteca[i].titulo);
        fprintf(pArq, "%s;", biblioteca[i].editora);
        fprintf(pArq, "%s;", biblioteca[i].idioma);
        fprintf(pArq, "%d;", biblioteca[i].ano);
        fprintf(pArq, "%d;", biblioteca[i].numeroPag);
        //fprintf(pArq, "%d;", biblioteca[i].numAutores);
        //fprintf(pArq, "%d;", biblioteca[i].numAssuntos);

        for(int j = 0; j < biblioteca[i].numAutores; j++){
            fprintf(pArq, "%s#", biblioteca[i].autores[j]);
        }
        for(int j = 0; j < biblioteca[i].numAssuntos; j++){
            fprintf(pArq, "%s@", biblioteca[i].assuntos[j]);
        }
        fprintf(pArq, "%c", '\n');
    }
    fclose(pArq);
}
void recupararArquivo(){
    char str[100], c;
    int countSep;
    int i;

    FILE *pArq;
    //abrir arquivo
    pArq = fopen("livros.txt", "r"); //r para ler o arquivo
    if(pArq == NULL){ //se nao abrir corretamente mostra o erro
        mensagemErro(-11);
        exit(0);
    }else{
        countSep = 0; //contador de separadores (; @ #)
        i=0;
        while(!feof(pArq)){ //feof retorna true no final do arquivo
            c = fgetc(pArq);
            if(c!='\n' && c!=';' && c!='@'&& c!='#'&& c!=EOF){
                str[i] = c;
                i++;
            }else if(c=='\n' || c==';' || c=='@'|| c=='#'){
                str[i] = '\0';
                i=0;
                if(c==';'){
                    if(countSep==0){
                        if(qntLivros==0){
                            biblioteca = (Livro *)malloc(1 * sizeof(Livro));
                        }else{
                            biblioteca = (Livro *)realloc(biblioteca, (qntLivros + 1) * sizeof(Livro));
                        }
                        biblioteca[qntLivros].titulo = (char *)malloc((strlen(str)+1) * sizeof(char));
                        strcpy(biblioteca[qntLivros].titulo, str);
                        biblioteca[qntLivros].numAssuntos = 0;
                        biblioteca[qntLivros].numAutores = 0;
                        countSep++;
                    } else if(countSep == 1){
                        biblioteca[qntLivros].editora = (char *)malloc((strlen(str)+1) * sizeof(char));
                        strcpy(biblioteca[qntLivros].editora, str);
                        countSep++;
                    }else if(countSep == 2){
                        biblioteca[qntLivros].idioma = (char *)malloc((strlen(str)+1) * sizeof(char));
                        strcpy(biblioteca[qntLivros].idioma, str);
                        countSep++;
                    }else if(countSep == 3){
                        biblioteca[qntLivros].ano = atoi(str);
                        countSep++;
                    }else if(countSep == 4){
                        biblioteca[qntLivros].numeroPag = atoi(str); //atoi p transformar string em numero
                        countSep=0;
                    }
                }else if(c=='#'){ //autores
                    //if(countSep==0){
                        if(biblioteca[qntLivros].numAutores==0){
                            biblioteca[qntLivros].autores = (char **)malloc(1 * sizeof(char*));
                        }else{
                            biblioteca[qntLivros].autores = (char **)realloc(biblioteca[qntLivros].autores, (biblioteca[qntLivros].numAutores+1) * sizeof(char*));
                        }
                        biblioteca[qntLivros].autores[biblioteca[qntLivros].numAutores] = (char *)malloc((strlen(str)+1) * sizeof(char));
                        strcpy(biblioteca[qntLivros].autores[biblioteca[qntLivros].numAutores], str);
                        biblioteca[qntLivros].numAutores++;
                    //}
                }else if(c=='@'){ //assuntos
                    if(biblioteca[qntLivros].numAssuntos==0){
                        biblioteca[qntLivros].assuntos = (char **)malloc(1 * sizeof(char*));
                    }else{
                        biblioteca[qntLivros].assuntos = (char **)realloc(biblioteca[qntLivros].assuntos, (biblioteca[qntLivros].numAssuntos+1) * sizeof(char*));
                    }
                    biblioteca[qntLivros].assuntos[biblioteca[qntLivros].numAssuntos] = (char *)malloc((strlen(str)+1) * sizeof(char));
                    strcpy(biblioteca[qntLivros].assuntos[biblioteca[qntLivros].numAssuntos], str);
                    biblioteca[qntLivros].numAssuntos++;
                }else{
                    countSep=0;
                    qntLivros++;
                }
            }
        }
    }
    fclose(pArq);
}
void menuListar(){
    system("cls");
    printf("\n\n---------Listar Livro--------- ");
    printf("\n (1) - Listar Livro Especifico");
    printf("\n (2) - Listar Todos ");
    printf("\n (3) - Sair\n");
    printf("------------------\n");
    printf("Escolha uma opcao: \n");
}
void opcaoListar(int op){
    int erro, numLista;
    if(op<1 || op > 3){
        mensagemErro(0);
    }else if(op<3){
        system("cls");
        if(op == 1){ //listar especifico
            if(qntLivros==1){
                imprimeLivro(biblioteca[0]);
                system("pause");
                return;
            }
            numLista = -1;
            while(numLista<1 || numLista > qntLivros){
                printf("\nDigite o numero do livro: [%d - %d]", 1, qntLivros);
                scanf("%d", &numLista);
                fflush(stdin);
                if(numLista<1 || numLista > qntLivros){
                    mensagemErro(-5);
                    system("cls");
                    continue; //voltar ao inicio do while, só passará para as proximas linhas ao escrever um numLista correto
                }
                
                imprimeLivro(biblioteca[numLista-1]);
                system("pause");
            }

        }else if(op == 2){ //listar todas
            erro = listarBiblioteca(1);
            
        }
        if(erro<0){
            mensagemErro(erro);
        }
    }
}
int listarBiblioteca(int pause){
    if(qntLivros<=0){
        return -6;
    }
    system("cls");
    for(int i = 0; i<qntLivros; i++){
        printf("\n----- Livro (%d) -----\n", i+1);
        imprimeLivro(biblioteca[i]);
    }
    if(pause == 1){
        system("pause");
    }
    return 1;
}
int alterar(){
    int listaLivro = -1, resp;
    if(qntLivros <= 0 ){
        return -6;
    }
    while(listaLivro < 0 || listaLivro >= qntLivros){
        listarBiblioteca(0);
        if(qntLivros>1){
            printf("\nDigite o numero do livro que deseja alterar: [%d - %d]", 1, qntLivros);
            scanf("%d", &listaLivro);
            fflush(stdin);
            printf("\n");
           
        }else{
            listaLivro = 1;
            system("pause");
        }
        listaLivro--;
        if(listaLivro<0 || listaLivro >= qntLivros){
            mensagemErro(-5);
        }else{
            resp = 1;
        }
    }
    system("cls");
    if(resp >0){
        imprimeLivro(biblioteca[listaLivro]);
    }
    system("pause");
}