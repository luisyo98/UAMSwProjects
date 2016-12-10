#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void imprimirMatriz(char** m);
void movimientoJugador(char** m);
void movimientoOrdenador(char** m);
char comprobarMatriz(char** m);

int main(int argc, char** argv) {
    char** matriz;
    int i = 0, j = 0, turno = 0;
    /****************************************************************/
    /**************Reserva dinámica de memoria***********************/
    /************************No tocar********************************/
    if ((matriz = calloc(3, sizeof (char*))) == NULL) {
        printf("Error no se puede iniciar el juego");
        return 1;
    }

    if (!(matriz[0] = calloc(9, sizeof (char)))) {
        printf("Error no se puede iniciar el juego");
        free(matriz);
        return 1;
    }

    for (i = 1; i < 3; i++) {
        matriz[i] = &matriz[0][i * 3];
    }
    /****************************************************************/
    /****************************************************************/
    /**
     * Desde este momento se puede aceder a la matriz usando los indices
     * matriz[1][2];
     * de la misma forma se puede aceder solo cambiando uno de los indices
     * matriz[0][4] = matriz[1][1] 
     *        ^ usando siempre el indice 0
     * Se puede ir desde matriz[0][0] hasta [0][8]
     * Esto podria simplificar las cosas a la hora de colocar X y O
     */
    
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            matriz[i][j] = ' '; /*rellenar la matriz creada con espacios*/
        }
    }


    printf("|1|2|3|\n|4|5|6|\n|7|8|9|\n\n\n\n"); /*instrucciones del juego*/
    srand(time(NULL));
    turno = rand() % 2; /*inicio aleatorio, jugador o maquina*/

    do {

        printf("\n");
        if (!turno) {
            imprimirMatriz(matriz);
            movimientoJugador(matriz);
            turno = 1;
        } else {
            movimientoOrdenador(matriz);
            turno = 0;
        }
    } while (!comprobarMatriz(matriz));


    imprimirMatriz(matriz);

    free(matriz[0]);
    free(matriz);
    return (EXIT_SUCCESS);
}

void imprimirMatriz(char** m) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("|%c", m[i][j]);
        }
        printf("|\n");
    }
}

void movimientoJugador(char** m) {
    int casilla;
    
    do{
        printf("Donde quieres colocar una X <1..9>: ");
        scanf("%d",casilla);
        if(casilla<1 || casilla > 9){
            printf("ERROR !! Casilla elegida erronea");
        }
        if(isalpha(m[casilla/3][casilla%3])){
            printf("ERROR !! La casilla elegida ya esta ocupada.");
        }
        casilla--;
    }while(casilla<1 || casilla > 9 || isalpha(m[casilla/3][casilla%3]));
    m[casilla/3][casilla%3]='X';

}

void movimientoOrdenador(char** m) {
    int r;
    srand(time(NULL));
    do {
        r = rand() % 8;
    } while (isalpha(m[0][r]));
    m[0][r] = 'O';
}

char comprobarMatriz(char** m) {
    int i = 0;

    for (i = 0; i < 3; i++) {
        if (m[i][0] == m[i][1] && m[i][0] == m[i][2]) { /*Comprobar filas*/
            if (isalpha(m[i][0])) {
                return m[i][0];
            }
        } else if (m[0][i] == m[1][i] && m[0][i] == m[2][i]) {/*Comprobar columnas*/
            if (isalpha(m[0][i])) {
                return m[0][i];
            }
        }
    }

    if ((m[0][0] == m[1][1] && m[1][1] == m[2][2]) || (m[0][2] == m[1][1] && m[1][1] == m[2][0])) {/*Comprobar diagonales*/
        if (isalpha(m[1][1])) {
            return m[1][1];
        }
    }

    return 0;
}
