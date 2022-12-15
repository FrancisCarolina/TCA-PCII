#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *titulo;
    char **autores;
    char *editora;
    int numeroPag;
    int ano;
    char *idioma;
    char **assuntos;
}Livro;

int qntLivros = 0;
Livro *livros;
int *qntAutores; //qntAutores[0] é a qnt de autores do livros[0]

int menu();
void disparaMenu(int opcao);
void dispararErro(int cod);
void incluirLivro();
Livro criarLivro();
void criarListaAutores();
void listarLivros();
void listarTodosLivros();
void escolherLivro();
void litarLivroEspecifico(Livro livro);
void editarLivro();
void listaEditarAtributos(int index);
void editarAtributoSimples(int opcao);
void editarAtributoComposto(int opcao);

int main(int argc, char const *argv[]){
    int opcao;
    while(opcao!=5){
        fflush(stdin);
        opcao = menu();
        disparaMenu(opcao);
    }
    free(livros);
    return 0;
}

int menu(){
    int escolha;
    system("cls");
    printf("\n\n-----MENU-----\n");
    printf("1 - Incluir Livro\n");
    printf("2 - Editar Livro\n");
    printf("3 - Excluir Livro\n");
    printf("4 - Listar Livro\n");
    printf("5 - Encerrar\n");
    printf("------------------\n");
    printf("Escolha uma opcao: \n");
    scanf("%d", &escolha);
    fflush(stdin);
    return escolha;
}

void disparaMenu(int opcao){
    if(opcao < 1 || opcao > 5 ){
        dispararErro(0);
    }
    else if(opcao == 1){
        incluirLivro();
    }else if(opcao == 2){
        editarLivro();
    } else if(opcao == 4){
        listarLivros();
    }else{
        printf("opcao: %d\n", opcao);
        system("pause");
        fflush(stdin);
    }
}

void dispararErro(int cod){
    if(cod == 0){
        printf("\nOpcao invalida\n");
    }else if(cod == -1){
        printf("\nData invalida\n");
    }else if(cod == -2){
        printf("\nNao tem livros para realizar essa acao\n");
    }else if(cod == -3){
        printf("\nAinda nao tem nenhum autor inserido. Insira pelo menos um.\n");
    }else if(cod == -4){
        printf("\nTitulo invalido\n");
    }else if(cod == -5){
        printf("\nEditora invalida\n");
    }else if(cod == -6){
        printf("\nNumero de paginas invalido\n");
    }else if(cod == -7){
        printf("\nAno de lancamento invalido\n");
    }else if(cod == -8){
        printf("\nIdioma invalido\n");
    }else{
        printf("\nErro\n");
    }
    system("pause");
    fflush(stdin);
}

void incluirLivro(){
    Livro livroAux;
    if(qntLivros>0){
        livros = (Livro*)realloc(livros, qntLivros+1 * sizeof(Livro));
    }else{
     livros = (Livro*)malloc(1 * sizeof(Livro));
    }
    livroAux = criarLivro();
    //livro ponteiro receber livro auxiliar
    livros[qntLivros].titulo = (char*)malloc(strlen(livroAux.titulo) * sizeof(char));
    strcpy(livros[qntLivros].titulo, livroAux.titulo);
    livros[qntLivros].editora = (char*)malloc(strlen(livroAux.editora) * sizeof(char));
    strcpy(livros[qntLivros].editora, livroAux.editora);
    livros[qntLivros].numeroPag = livroAux.numeroPag; 
    livros[qntLivros].ano = livroAux.ano; 
    livros[qntLivros].idioma = (char*)malloc(strlen(livroAux.idioma) * sizeof(char));
    strcpy(livros[qntLivros].idioma, livroAux.idioma);

    qntLivros = qntLivros+1;
    system("pause");
    fflush(stdin);
}

Livro criarLivro(){
    Livro livroAux;
    char titulo[100], editora[100], idioma[100];
    printf("\n\n---------Incluir Livro--------- ");
    do{
        printf("\nDigite o titulo do livro: ");
        gets(titulo);
        fflush(stdin);
        if(strlen(titulo) == 0){
            dispararErro(-4);
        }
    }while(strlen(titulo)==0);
    livroAux.titulo = (char*)malloc(strlen(titulo) * sizeof(char));
    strcpy(livroAux.titulo, titulo);
    criarListaAutores();
    do{
        printf("\nDigite o nome da editora: ");
        gets(editora);
        fflush(stdin);
        if(strlen(editora) == 0){
            dispararErro(-5);
        }
    }while(strlen(editora)==0);
    livroAux.editora = (char*)malloc(strlen(editora) * sizeof(char));
    strcpy(livroAux.editora, editora);
    do{
        printf("\nDigite o numero de paginas do livro: ");
        scanf("%d", &livroAux.numeroPag);
        fflush(stdin);
        if(livroAux.numeroPag <= 0){
            dispararErro(-6);
        }
    }while(livroAux.numeroPag<=0);
    do{
        printf("\nDigite o ano de lancamento do livro: ");
        scanf("%d", &livroAux.ano);
        fflush(stdin);
        if(livroAux.ano <= 0){
            dispararErro(-7);
        }
    }while(livroAux.ano<=0);
    do{
        printf("\nDigite o idioma do livro: ");
        gets(idioma);
        fflush(stdin);
        if(strlen(idioma) == 0){
            dispararErro(-8);
        }
    }while(strlen(idioma)==0);
    livroAux.idioma = (char*)malloc(strlen(idioma) * sizeof(char));
    strcpy(livroAux.idioma, idioma);
    fflush(stdin);
    return livroAux;
}
void criarListaAutores(){
    char **autores;
    char autor[100];
    int qntAutor=0, opAutor = 1;
    while(opAutor == 1){
        printf("\n\n---------Incluir Autores--------- ");
        printf("\n (1) - Incluir mais um autor");
        printf("\n (2) - Finalizar inclusao de autor");
        printf("\n------------------\n");
        printf("Escolha uma opcao: \n");
        scanf("%d", &opAutor);
        fflush(stdin);
        if(qntAutor == 0 && opAutor==2){
            dispararErro(-3);
            opAutor = 1;
        }else if(opAutor == 1){
            printf("\n\n---------Incluir Autor--------- ");
            printf("\nDigite o nome do autor (%d): ", qntAutor+1);
            gets(autor);
            fflush(stdin);
            if(qntAutor == 0){
                autores = (char**)malloc(qntAutor * sizeof(char*));
            }else{
                autores = (char**)realloc(autores, qntAutor * sizeof(char*));
            }
            autores[qntAutor] = (char*)malloc(strlen(autor) * sizeof(char));
            strcpy(autores[qntAutor], autor);
            qntAutor = qntAutor+1;
        }
    }
    if(qntLivros==0){
        qntAutores = (int*)malloc(qntLivros+1 * sizeof(int));
    }else{
        qntAutores = (int*)realloc(qntAutores, qntLivros+1 * sizeof(int));
    }
    qntAutores[qntLivros] = qntAutor;
    fflush(stdin);
    printf("\nQNT AUTORES: %d",qntAutores[qntLivros] );

}
void listarLivros(){
    int opcao=0;
    while(opcao != 3){
        printf("\n\n---------Listar Livro--------- ");
        printf("\n (1) - Listar Todos ");
        printf("\n (2) - Listar Livro Especifico");
        printf("\n (3) - Sair\n");
        printf("------------------\n");
        printf("Escolha uma opcao: \n");
        scanf("%d", &opcao);
        fflush(stdin);
        if(opcao >3 || opcao<1){
            dispararErro(0);
        }else if(opcao == 1){
            listarTodosLivros();
        }else if(opcao == 2){
            escolherLivro();
        }
    }
}
void escolherLivro(){
    int opcao=0;
    if(qntLivros>0){
        while(opcao != qntLivros+1){
            printf("\n\n------Listar Livro Especifico------ ");
            printf("\n");
            for(int i=0; i<qntLivros; i++){
                printf("(%d) - titulo: %s", i+1, livros[i].titulo);
                printf("\n");
            }
            printf("(%d) - sair\n", qntLivros+1);  
            printf("------------------\n");
            printf("Escolha uma opcao: \n");
            scanf("%d", &opcao);
            fflush(stdin);
            if(opcao < qntLivros+1 && opcao>0){
                litarLivroEspecifico(livros[opcao-1]);
            }else if(opcao != qntLivros+1){
                dispararErro(0);
            }
        }
    }else{
        dispararErro(-2);
    }
}
void litarLivroEspecifico(Livro livro){
    printf("\n");
    printf("Livro: \ttitulo: %s", livro.titulo);
    printf("\n\teditora: %s", livro.editora);
    printf("\n\tNum de pags: %d", livro.numeroPag);
    printf("\n\tAno: %d", livro.ano);
    printf("\n\tIdioma: %s", livro.idioma);
    printf("\n");
    system("pause");
    fflush(stdin);
}
void listarTodosLivros(){
    fflush(stdin);
    if(qntLivros>0){
        for(int i=0; i<qntLivros; i++){
            printf("\n");
            printf("Livro (%d): \ttitulo: %s", i+1, livros[i].titulo);
            
            /*for(int i =0; i<qntLivros; i++){
                for(int j =0; j<qntAutores[i]; j++){
                    printf("\n\t\tautor (%d): %s\n", j, livros[i].autores[j]);
                }
            }*/
            printf("\n\t\teditora: %s", livros[i].editora);
            printf("\n\t\tNum de pags: %d", livros[i].numeroPag);
            printf("\n\t\tAno: %d", livros[i].ano);
            printf("\n\t\tIdioma: %s", livros[i].idioma);
            printf("\n");
        }   
        system("pause");
        fflush(stdin);
    }else{
        dispararErro(-2);
    }
}

void editarLivro(){
   int opcao=0;
    if(qntLivros>0){
        while(opcao != qntLivros+1){
            printf("\n\n------Escolha o livro que deseja editar------ \n");
            for(int i=0; i<qntLivros; i++){
                printf("(%d) - titulo: %s", i+1, livros[i].titulo);
                printf("\n");
            }
            printf("(%d) - sair\n", qntLivros+1);  
            printf("------------------\n");
            printf("Escolha uma opcao: \n");
            scanf("%d", &opcao);
            fflush(stdin);
            if(opcao < qntLivros+1 && opcao>0){
                listaEditarAtributos(opcao-1);
            }else if(opcao != qntLivros+1){
                dispararErro(0);
            }
        }
    }else{
        dispararErro(-2);
    }
}
void listaEditarAtributos(int index){
    int opcao=0;
    while(opcao != 8){
        printf("\n\n---------Editar ");
        printf("%s---------", livros[index].titulo);
        printf("\n (1) - Editar Titulo");
        printf("\n (2) - Editar Autores");
        printf("\n (3) - Editar Editora\n");
        printf("\n (4) - Editar Numero de Paginas");
        printf("\n (5) - Editar Ano");
        printf("\n (6) - Editar Idioma\n");
        printf("\n (7) - Editar Assuntos\n");
        printf("\n (8) - Sair\n");
        printf("------------------\n");
        printf("Escolha uma opcao: \n");
        scanf("%d", &opcao);
        fflush(stdin);
        if(opcao >8 || opcao<1){
            dispararErro(0);
        }else if(opcao == 1 || opcao == 3 || opcao == 4 || opcao == 5 || opcao == 6){
            editarAtributoSimples(opcao);
        }else if(opcao == 2 || opcao == 7){
            editarAtributoComposto(opcao);
        }
    }
}

void editarAtributoSimples(int opcao){
    printf("\nDigite ");
    if(opcao == 1 || opcao == 4 || opcao == 5 || opcao == 6){  
        printf("o novo ");
        if(opcao == 1){  
            printf("titulo: ");
        }else if(opcao == 4){
            printf("numero de paginas: ");
        }else if(opcao == 4){
            printf("ano de lancamento: ");
        }else{
            printf("idioma: ");
        }
    }else {  
        printf("a nova editora: ");
    }
    printf("\n ");
}
void editarAtributoComposto(int opcao){
    int op;
    if(opcao == 2){
    //autores
        while(op != 4){
            printf("\n\n---------Editar Autor---------");
            printf("\n (1) - Inclir Autor");
            printf("\n (2) - Editar Autor");
            printf("\n (3) - Excluir Autor\n");
            printf("\n (4) - Sair\n");
            printf("------------------\n");
            printf("Escolha uma opcao: \n");
            scanf("%d", &op);
            fflush(stdin);
            if(op >4 || op<1){
                dispararErro(0);
            }else if(op!=4){
                if(op == 1){
                    //incluir autor
                }else if( op == 2){
                    //editar autor
                }else{
                    //excluir autor
                }
            }
        }
    }else {
        //assuntos
        while(op != 4){
            printf("\n\n---------Editar Assunto---------");
            printf("\n (1) - Inclir Assunto");
            printf("\n (2) - Editar Assunto");
            printf("\n (3) - Excluir Assunto\n");
            printf("\n (4) - Sair\n");
            printf("------------------\n");
            printf("Escolha uma opcao: \n");
            scanf("%d", &op);
            fflush(stdin);
            if(op >4 || op<1){
                dispararErro(0);
            }else if(op!=4){
                if(op == 1){
                    //incluir assunto
                }else if( op == 2){
                    //editar assunto
                }else{
                    //excluir assunto
                }
            }
        }
    }
}