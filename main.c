#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <ctype.h>

#define TAM_TAB 9
#define TAM_POS 4

void exibeRegras();
void exibeTabuleiro(char tab[TAM_TAB][TAM_TAB]);
char naCasa(char tab[TAM_TAB][TAM_TAB], char *);
int validaPeca(char tab[TAM_TAB][TAM_TAB], char *, char);
int validaMovimento(char tab[TAM_TAB][TAM_TAB], char *, char *);
void verificaConversao(char tab[TAM_TAB][TAM_TAB], char *, char*);
int verificaVitoria(char tab[TAM_TAB][TAM_TAB], char);

int main(){

    setlocale(LC_ALL, "portuguese");

    int i, j, x, resultado;
    char tabuleiro[TAM_TAB][TAM_TAB], peca[TAM_POS], posicao[TAM_POS], menu[3], player, aliado, turno, contagem;
    srand(time(NULL));

    while(1){

        turno = 1;
        contagem = 1;

        //Menu do jogo. Aperte 1 para come�ar, 2 para ler as regras e 3 para sair.
        do{
            printf("/--------------------\\\n|  ROBERTO'S GAME    |\n\\--------------------/\n\n");
            printf("Aperte:\n\n-1 para come�ar;\n\n-2 para ver as regras;\n\n-3 para sair.\n\n");
            fgets(menu, 3, stdin);
            fflush(stdin);

            //Verifica se o n�mero digitado � v�lido.
            while(1){
                if(menu[0] >= '1' && menu[0] <= '3' && menu[1] == '\n')
                    break;
                system("cls");
                printf("/--------------------\\\n|  ROBERTO'S GAME    |\n\\--------------------/\n\n");
                printf("Numero invalido!\nAperte:\n\n-1 para comecar;\n\n-2 para ver as regras;\n\n-3 para sair.\n\n");
                fgets(menu, 3, stdin);
                fflush(stdin);
            }

            //Executa as a��es de acordo com o n�mero digitado pelo jogador.
            if(menu[0] == '1')
                break;
            else if(menu[0] == '2')
                exibeRegras();
            else{
                //Encerra o jogo.
                for(i = 0; i < 3; i++){
                    system("cls");
                    printf("\n\nEncerrando");
                    for(j = 0; j < 5; j++){
                        printf(".");
                        usleep(500000);
                    }
                }
                printf("\n\n");
                return 0;
            }
        } while(1);


        //Preenche a matriz com espa�os vazios.
        for(i=0; i<TAM_TAB; i++){
            for(j=0; j<TAM_TAB; j++){
                tabuleiro[i][j]=' ';
            }
        }

        //Preenche a matriz com as pe�as do jogo de forma aleat�ria.
        for(x=0; x<10 ; x++){
            do{
                i=rand()%TAM_TAB;
                j=rand()%TAM_TAB;
            } while(tabuleiro[i][j]!=' ');

            if(x<5)
                tabuleiro[i][j]='X';
            else
                tabuleiro[i][j]='O';
        }


        do{
            //Come�a o jogo.
            //As vari�veis contagem e player determinam os turnos e a vez de cada jogador, quando player for O, o turno muda.
            if(contagem%2==0){
                player='O';
                aliado='o';
            }
            else{
                player='X';
                aliado='�';
            }


            //Pede para o jogador escolher uma pe�a.
            system("cls");
            printf("TURNO %d\nJOGADOR %c:\n\n", turno, player);
            exibeTabuleiro(tabuleiro);
            printf("Digite a posi��o da pe�a! (Ex.: 5e): ");
            fgets(peca, TAM_POS, stdin);
            fflush(stdin);
            peca[1] = tolower(peca[1]);

            //Verifica se a pe�a escolhida pelo joador � v�lida.
            while(validaPeca( tabuleiro, peca, player)){
                system("cls");
                printf("TURNO %d\nJOGADOR %c:\n\n", turno, player);
                exibeTabuleiro(tabuleiro);
                if(peca[0] - '1' < 0 || peca[0] - '1' > 8 || peca[1] - 'a' < 0 || peca[1] - 'a' > 8 || peca[2] != '\n')
                    printf("ERRO!\nPosi��o escolhida est� fora do tabuleiro, digite novamente: ");
                else if(naCasa(tabuleiro, peca) == ' ')
                    printf("ERRO!\nPosi��o vazia, digite novamente: ");
                else if(naCasa(tabuleiro, peca) == 'X' || naCasa(tabuleiro, peca) == 'O')
                    printf("ERRO!\nPosi��o escolhida tem a pe�a '%c', digite novamente: ", naCasa(tabuleiro, peca));
                else if(naCasa(tabuleiro, peca) == '�' || naCasa(tabuleiro, peca) == 'o')
                    printf("ERRO!\nPosi��o escolhida tem o aliado '%c', digite novamente: ", naCasa(tabuleiro, peca));
                fgets(peca, TAM_POS, stdin);
                fflush(stdin);
                peca[1] = tolower(peca[1]);
            }


            //Pede para o jogador escolher a posi��o para se mover.
            system("cls");
            printf("TURNO %d\nJOGADOR %c:\n\n", turno, player);
            exibeTabuleiro(tabuleiro);
            printf("Digite a posi��o para mover a pe�a! (Ex.: 5e): ");
            fgets(posicao, TAM_POS, stdin);
            fflush(stdin);
            posicao[1] = tolower(posicao[1]);

            //Verifica se a posi��o escolhida � v�lida.
            while(validaMovimento(tabuleiro, peca, posicao)){
                x = validaMovimento(tabuleiro, peca, posicao);
                system("cls");
                printf("TURNO %d\nJOGADOR %c:\n\n", turno, player);
                exibeTabuleiro(tabuleiro);
                if(x == 1)
                    printf("ERRO!\nPosi��o escolhida est� fora do tabuleiro, digite novamente: ");
                else if(x == 2)
                    printf("ERRO!\nNenhum movimento realizado, digite novamente: ");
                else if(x == 3)
                    printf("ERRO!\nPosi��o escolhida est� ocupada, digite novamente: ");
                else if(x == 4)
                    printf("ERRO!\nN�o � permitido pular sobre outras pe�as, digite novamente: ");
                else if(x == 5)
                    printf("ERRO!\nO movimento s� pode ser na horizontal, vertical ou diagonal, digite novamente: ");
                fgets(posicao, TAM_POS, stdin);
                fflush(stdin);
                posicao[1] = tolower(posicao[1]);
            }


            //Realiza o movimento e faz a convers�o dos aliados.
            tabuleiro[posicao[0]-'1'][posicao[1]-'a']=player;
            tabuleiro[peca[0]-'1'][peca[1]-'a']=aliado;
            verificaConversao(tabuleiro, peca, posicao);

            //Altera o turno.
            if(player=='O')
                turno++;
            contagem++;

            //Verifica vit�ria.
            resultado = verificaVitoria(tabuleiro, player);
        } while(resultado == 0);

        do{
            //Informa o resultado final.
            system("cls");
            printf("FIM DE JOGO!\nTabuleiro final:\n\n");
            exibeTabuleiro(tabuleiro);
            if(resultado == 1)
                printf("\n\nA partida deu empate. Pois ambos os jogadores formaram uma sequ�ncia de 5 aliados concecutivos.\n");
            else if(resultado == 2)
                printf("\n\nO jogador 'O' venceu, pois conseguiu formar uma sequ�ncia de 5 aliados concecutivos.\n");
            else if(resultado == 3)
                printf("\n\nO jogador 'X' venceu, pois conseguiu formar uma sequ�ncia de 5 aliados concecutivos.\n");
            else if(resultado == 4){
                    if(player == 'X')
                        printf("\n\nO jogador 'X' venceu, pois o jogador 'O' n�o tem mais movimentos dispon�veis.\n");
                    else
                        printf("\n\nO jogador 'O' venceu, pois o jogador 'X' n�o tem mais movimentos dispon�veis.\n");
            }

            //Pergunta se o jogador quer sair ou voltar para o menu.
            printf("\n\nAperte 1 para retornar ao menu ou 2 para sair: ");
            fgets(menu, 3, stdin);
            fflush(stdin);
            if((menu[0] == '1' || menu[0] == '2') && menu[1] == '\n')
                break;
        }while(1);

        //Executa a a��o do jogador.
        if(menu[0] == '1')
            system("cls");
        else{
            //Encerra o jogo.
            for(i = 0; i < 3; i++){
                system("cls");
                printf("\n\nEncerrando");
                for(j = 0; j < 5; j++){
                    printf(".");
                    usleep(500000);
                }
            }
                printf("\n\n");
                return 0;
            }
        }
}

//Exibe as regras.
void exibeRegras(){

    system("cls");
    printf("REGRAS:\n\n1 - Cada jogador tem 5 pe�as.\n\n");
    printf("2 - Os jogadores alternam seus turnos durante a partida, durante seu turno o jogador dever� escolher\numa pe�a e mov�-la.\n\n");
    printf("3 - O movimento � igual � rainha do xadrez, seja seguindo uma coluna, uma linha ou diagonal do tabuleiro.\n\n");
    printf("4 - N�o � permitido pular sobre suas pe�as ou sobre as pe�as do advers�rio.\n\n");
    printf("5 - Ap�s o movimento, � deixado um aliado na posi��o onde o jogador estava.\n\n");
    printf("6 - Ap�s cada movimento, os aliados que o jogador passa por cima se invertem, isto �, seus alidos viram\ndo oponente e os aliados do oponente viram seus.\n\n");
    printf("7 - Ganha aquele que conseguir formar uma sequ�ncia de 5 aliados concecutivos, podendo ser na horizontal,\nvertical ou diagonal.\n\n");
    printf("8 - � poss�vel alcan�ar a vit�ria tamb�m caso o oponente n�o possua mais movimentos v�lidos.\n\n\n\n\n");
    system("pause");
    system("cls");

}


//Exibe o tabuleiro.
void exibeTabuleiro(char tab[TAM_TAB][TAM_TAB]){
    int i, j;

    printf("-------------------------------------\n");
    for(i=0; i<TAM_TAB; i++){
        for(j=0; j<TAM_TAB; j++){
            if(j == 0 && i != 0)
                printf("----+---+---+---+---+---+---+---+----\n");
            printf("| %c ", tab[i][j]);
        }
        printf("|  %d\n", i+1);
    }

    printf("-------------------------------------\n  A   B   C   D   E   F   G   H   I\n\n");
}


//Retorna a pe�a que est� na posi��o selecionada.
char naCasa(char tab[TAM_TAB][TAM_TAB], char *posicaoPeca){
    int i, j;

    i=(posicaoPeca[0]-'1');
    j=(posicaoPeca[1]-'a');


    return tab[i][j];
}


//Verifica se a posi��o escolhida cont�m uma pe�a v�lida.
int validaPeca(char tab[TAM_TAB][TAM_TAB], char *posicaoPeca, char jogador){
    int i, j;

    //i e j recebem a posi��o digitada convertida em n�mero.
    i = (posicaoPeca[0] - '1');
    j = (posicaoPeca[1] - 'a');

    //Verifica se a posi��o escolhida est� dentro do tabuleiro e se cont�m uma pe�a do jogador.
    if(jogador != naCasa(tab, posicaoPeca) || (i < 0 || i > 8) || (j < 0 || j > 8) || posicaoPeca[2] != '\n')
        return 1;
    else
        return 0;
}


//Verifica se o movimento � v�lido.
int validaMovimento(char tab[TAM_TAB][TAM_TAB], char *posicaoPeca, char *novaPosicao){

    char i, j, k, l;
    int m, n, a, c, d;

    //i e j recebem a posi��o da pe�a.
    //k e l recebem a nova posi��o.
    //m recebe a quantidade de movimento na vertical.
    //n recebe a quantidade de movimento na horizontal.
    // c e d recebem a posi��o  da pe�a convertida em n�mero.
    i = posicaoPeca[0];
    j = posicaoPeca[1];
    k = novaPosicao[0];
    l = novaPosicao[1];
    m = i - k;
    n = j - l;
    c = i - '1';
    d = j - 'a';


    //RESPECTIVAMENTE:
    //Verifica se a posi��o digitada est� dentro do tabuleiro.
    //Verifica se a posi��o digitada est� vazia.
    //Verifica se algum movimento foi realizado.
    //OS PR�XIMOS VERIFICAM O TIPO DE MOVIMENTO E SE A PE�A PULA OUTRA PE�A.
    //Verifica se o movimento na horizontal da direita para a esquerda � v�lido.
    //Verifica se o movimento na horizontal da esquerda para a direita � v�lido.
    //Verifica se o movimento na vertical de baixo para cima � v�lido.
    //Verifica se o movimento na vertical de cima para baixo � v�lido.
    //Verifica se o movimento na diagonal principal da esquerda para a direita � v�lido.
    //Verifica se o movimento na diagonal principal da direita para a esquerda � v�lido.
    //Verifica se o movimento na diagonal secund�ria da esquerda para a direita � v�lido.
    //Verifica se o movimento na diagonal secund�ria da direita para a esquerda � v�lido.
    //O �ltimo verifica se o movimento ocorre na vertical, horiontal ou diagonal.
    if(k - '1' < 0 || k - '1' > 8 || l - 'a' < 0 || l - 'a' > 8 || novaPosicao[2] != '\n')
        return 1;
    else if(m == 0 && n == 0)
        return 2;
    else if(naCasa(tab, novaPosicao)!=' ')
        return 3;
    else if(m == 0 && n > 0){
              for(a = 1; a < n; a++){
                  if(tab[c][d - a] == 'X' || tab[c][d - a] == 'O')
                      return 4;
              }
              return 0;
      } else if(m == 0 && n < 0){
              for(a = n+1; a < 0 ; a++){
                  if(tab[c][d - a] == 'X' || tab[c][d - a] == 'O')
                      return 4;
              }
              return 0;
      } else if(m > 0 && n == 0){
              for(a = 1; a < m; a++){
                  if(tab[c - a][d] == 'X' || tab[c - a][d] == 'O')
                      return 4;
              }
              return 0;
      } else if(m < 0 && n == 0){
              for(a = m+1; a < 0; a++){
                  if(tab[c - a][d] == 'X' || tab[c - a][d] == 'O')
                      return 4;
              }
              return 0;
      } else if(m == n && n > 0){
              for(a = 1; a < n; a++){
                  if(tab[c - a][d - a] == 'X' || tab[c - a][d - a] == 'O')
                      return 4;
              }
              return 0;
      } else if(m == n && n < 0){
              for(a = n+1; a < 0; a++){
                  if(tab[c - a][d - a] == 'X' || tab[c - a][d - a] == 'O')
                      return 4;
              }
              return 0;
      } else if(m == n*(-1) && n > 0){
              for(a = 1; a < n; a++){
                  if(tab[c + a][d - a] == 'X' || tab[c + a][d - a] == 'O')
                      return 4;
              }
              return 0;
      } else if(m == n*(-1) && n < 0){
              for(a = n+1; a < 0; a++){
                  if(tab[c + a][d - a] == 'X' || tab[c + a][d - a] == 'O')
                      return 4;
              }
              return 0;
      } else if(m != n && m != n*(-1))
           return 5;
        else
           return 0;
}


//Realiza a convers�o dos aliados.
void verificaConversao(char tab[TAM_TAB][TAM_TAB], char *posicaoPeca, char *novaPosicao){

    int m, n, a, c, d;

    //m recebe a quantidade de movimento na vertical.
    //n recebe a quantidade de movimento na horizontal.
    // c e d recebem a posi��o  da pe�a convertida em n�mero.
    //a � um contador para o for.
    c = posicaoPeca[0] - '1';
    d = posicaoPeca[1] - 'a';
    m = posicaoPeca[0] - novaPosicao[0];
    n = posicaoPeca[1] - novaPosicao[1];

    //RESPECTIVAMENTE:
    //Cada if verifica o tipo do movimento, se foi na horizontal, vertical ou diagonal.
    //Os dois primeiros convertem os aliados que est�o na horizontal.
    //Os dois seguintes convertem os aliados que est�o na vertical.
    //Os dois seguintes convertem os aliados que est�o na diagonal principal.
    //Os dois �timos convertem os aliados que est�o na diagonal secund�ria.
    if(m == 0 && n > 0){
            for(a = 1; a < n; a++){
                  if(tab[c][d - a] == '�')
                      tab[c][d - a] = 'o';
                  else if(tab[c][d - a] == 'o')
                      tab[c][d - a] = '�';
                  else
                      continue;
              }
              return;
      } else if(m == 0 && n < 0){
              for(a = n+1; a < 0 ; a++){
                    if(tab[c][d - a] == '�')
                        tab[c][d - a] = 'o';
                    else if(tab[c][d - a] == 'o')
                        tab[c][d - a] = '�';
                    else
                        continue;
              }
              return;
      } else if(m > 0 && n == 0){
              for(a = 1; a < m; a++){
                    if(tab[c - a][d] == '�')
                        tab[c - a][d] = 'o';
                    else if(tab[c - a][d] == 'o')
                        tab[c - a][d] = '�';
                    else
                        continue;
              }
              return;
      } else if(m < 0 && n == 0){
              for(a = m+1; a < 0; a++){
                    if(tab[c - a][d] == '�')
                        tab[c - a][d] = 'o';
                    else if(tab[c - a][d] == 'o')
                        tab[c - a][d] = '�';
                    else
                        continue;
              }
              return;
      } else if(m == n && n > 0){
              for(a = 1; a < n; a++){
                    if(tab[c - a][d - a] == '�')
                        tab[c - a][d - a] = 'o';
                    else if(tab[c - a][d - a] == 'o')
                        tab[c - a][d - a] = '�';
                    else
                        continue;
              }
              return;
      } else if(m == n && n < 0){
              for(a = n+1; a < 0; a++){
                    if(tab[c - a][d - a] == '�')
                        tab[c - a][d - a] = 'o';
                    else if(tab[c - a][d - a] == 'o')
                        tab[c - a][d - a] = '�';
                    else
                        continue;
              }
              return;
      } else if(m == n*(-1) && n > 0){
              for(a = 1; a < n; a++){
                    if(tab[c + a][d - a] == '�')
                        tab[c + a][d - a] = 'o';
                    else if(tab[c + a][d - a] == 'o')
                        tab[c + a][d - a] = '�';
                    else
                        continue;
              }
              return;
      } else if(m == n*(-1) && n < 0){
              for(a = n+1; a < 0; a++){
                    if(tab[c + a][d - a] == '�')
                        tab[c + a][d - a] = 'o';
                    else if(tab[c + a][d - a] == 'o')
                        tab[c + a][d - a] = '�';
                    else
                        continue;
              }
              return;
        }
}


//Verifica vit�tia.
int verificaVitoria(char tab[TAM_TAB][TAM_TAB], char jogador){

    //Essa fun��o � dividida em duas partes.
    //A primeira verifica se a vit�ria ocorreu pela acumula��o de aliados concecutivos.
    //A segunda verifica se a vit�ria ocorreu pela falta de movimentos do oponente.
    int i, j, k, l, vitoriaX=0, vitoriaO=0;
    char player, peca[TAM_POS], movimento[TAM_POS];

    //verifica qual pe�a deve ser testada na segunda parte da fun��o.
    if(jogador == 'X')
        player = 'O';
    else
        player = 'X';

    //PRIMEIRA PARTE DA FUN��O

    //Os primeiros 4 duplos FOR verificam se o jogador X venceu pela acumula��o de 5 aliados concecutivos.

    //Verifica se a acumula��o de 5 aliados ocorreu na horizontal.
    for(i = 0; i < TAM_TAB; i++){
        for(j = 0; j < 5; j++){
            if(tab[i][j] == '�' && tab[i][j + 1] == '�' && tab[i][j + 2] == '�' && tab[i][j + 3] == '�' && tab[i][j + 4] == '�')
                vitoriaX = 1;
        }
    }

    //Verifica se a acumula��o de 5 aliados ocorreu na vertical.
    for(i = 0; i < 5; i++){
        for(j = 0; j < TAM_TAB; j++){
            if(tab[i][j] == '�' && tab[i + 1][j] == '�' && tab[i + 2][j] == '�' && tab[i + 3][j] == '�' && tab[i + 4][j] == '�')
                vitoriaX = 1;
        }
    }

    //Verifica se a acumula��o de 5 aliados ocorreu na diagonal principal.
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            if(tab[i][j] == '�' && tab[i + 1][j + 1] == '�' && tab[i + 2][j + 2] == '�' && tab[i + 3][j + 3] == '�' && tab[i + 4][j + 4] == '�')
                vitoriaX = 1;
        }
    }

    //Verifica se a acumula��o de 5 aliados ocorreu na diagonal secund�ria.
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            if(tab[i][8 - j] == '�' && tab[i + 1][8 - (j + 1)] == '�' && tab[i + 2][8 - (j + 2)] == '�' && tab[i + 3][8 - (j + 3)] == '�' && tab[i + 4][8 - (j + 4)] == '�')
                vitoriaX = 1;
        }
    }


    //Os �ltimos 4 duplos FOR verifcam se o jogador O venceu pela acumula��o de 5 pe�es concecutivos.

    //Verifica se a acumula��o de 5 aliados ocorreu na horizontal.
    for(i = 0; i < TAM_TAB; i++){
        for(j = 0; j < 5; j++){
            if(tab[i][j] == 'o' && tab[i][j + 1] == 'o' && tab[i][j + 2] == 'o' && tab[i][j + 3] == 'o' && tab[i][j + 4] == 'o')
                vitoriaO = 1;
        }
    }

    //Verifica se a acumula��o de 5 aliados ocorreu na vertical.
    for(i = 0; i < 5; i++){
        for(j = 0; j < TAM_TAB; j++){
            if(tab[i][j] == 'o' && tab[i + 1][j] == 'o' && tab[i + 2][j] == 'o' && tab[i + 3][j] == 'o' && tab[i + 4][j] == 'o')
                vitoriaO = 1;
        }
    }

    //Verifica se a acumula��o de 5 aliados ocorreu na diagonal principal.
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            if(tab[i][j] == 'o' && tab[i + 1][j + 1] == 'o' && tab[i + 2][j + 2] == 'o' && tab[i + 3][j + 3] == 'o' && tab[i + 4][j + 4] == 'o')
                vitoriaO = 1;
        }
    }

    //Verifica se a acumula��o de 5 aliados ocorreu na diagonal secund�ria.
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            if(tab[i][8 - j] == 'o' && tab[i + 1][8 - (j + 1)] == 'o' && tab[i + 2][8 - (j + 2)] == 'o' && tab[i + 3][8 - (j + 3)] == 'o' && tab[i + 4][8 - (j + 4)] == 'o')
                vitoriaO = 1;
        }
    }

    //Verifica se a condi��o de vit�ria por ac�mulo de aliados concecutivos aconteceu.
    if(vitoriaO == 1 && vitoriaX == 1)
        return 1;
    else if(vitoriaO == 1)
        return 2;
    else if(vitoriaX == 1)
        return 3;

    //SEGUNDA PARTE DA FUN��O

    //Procura todas as pe�as do jogador e verifica se existe movimento poss�vel em alguma dire��o.
    //Os dois primeiros FOR verificam se h� movimento dispon�vel na horizontal.
    //Os dois FOR seguintes verificam se h� movimento dispon�vel na vertical.
    //Os dois FOR seguintes verificam se h� movimento dispon�vel na diagonal pricipal.
    //Os dois FOR seguintes verificam se h� movimento dispon�vel na diagonal secund�ria.
    //Caso seja detectado algum movimento dispon�vel a fun��o encerra e retorna o valor 0.
    //Caso n�o seja detectado nenhum movimento dispon�vel a fun��o retorna o valor 4.
    peca[2] = '\n';
    movimento[2] = '\n';
    for(i = 0; i < TAM_TAB; i++){
        for(j = 0; j < TAM_TAB; j++){
            if(tab[i][j] == player){
                peca[0] = i + '1';
                peca[1] = j + 'a';
                for(l = 1; l <= TAM_TAB - 1; l++){
                    movimento[0] = peca[0];
                    movimento[1] = peca[1] + l;
                    if(validaMovimento(tab, peca, movimento) == 0)
                        return 0;
                }
                    for(l = 1; l <= TAM_TAB - 1; l++){
                    movimento[0] = peca[0];
                    movimento[1] = peca[1] - l;
                    if(validaMovimento(tab, peca, movimento) == 0)
                        return 0;
                }
                for(l = 1; l <= TAM_TAB - 1; l++){
                    movimento[0] = peca[0] + l;
                    movimento[1] = peca[1];
                    if(validaMovimento(tab, peca, movimento) == 0)
                        return 0;
                }
                for(l = 1; l <= TAM_TAB - 1; l++){
                    movimento[0] = peca[0] - l;
                    movimento[1] = peca[1];
                    if(validaMovimento(tab, peca, movimento) == 0)
                        return 0;
                }
                for(l = 1; l <= TAM_TAB - 1; l++){
                    movimento[0] = peca[0] + l;
                    movimento[1] = peca[1] + l;
                    if(validaMovimento(tab, peca, movimento) == 0)
                        return 0;
                }
                for(l = 1; l <= TAM_TAB - 1; l++){
                    movimento[0] = peca[0] - l;
                    movimento[1] = peca[1] - l;
                    if(validaMovimento(tab, peca, movimento) == 0)
                        return 0;
                }
                for(l = 1; l <= TAM_TAB - 1; l++){
                    movimento[0] = peca[0] - l;
                    movimento[1] = peca[1] + l;
                    if(validaMovimento(tab, peca, movimento) == 0)
                        return 0;
                }
                for(l = 1; l <= TAM_TAB - 1; l++){
                    movimento[0] = peca[0] + l;
                    movimento[1] = peca[1] - l;
                    if(validaMovimento(tab, peca, movimento) == 0)
                        return 0;
                }
            }
        }
    }
    return 4;
}
