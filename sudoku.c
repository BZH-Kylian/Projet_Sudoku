/**
 * \file sudoku.c
 * \brief Programme de jeu Sudoku.
 * \author HOUEDEC Kylian
 * \date 3 Décembre 2023
 * 
 * Ce programme propose au joueur de commencer une partie de Sudoku. Initialement, le joueur est invité à choisir 
 * une grille en saisissant son nom. Une fois la grille sélectionnée, elle est affichée, et le jeu commence.
 * Le joueur doit fournir le numéro de la ligne et de la colonne où il souhaite placer un chiffre. 
 * Le programme vérifie la validité de la case. Si une erreur est détectée, le joueur est invité à réessayer. 
 * Si la case est valide, le joueur est ensuite invité à saisir le chiffre qu'il souhaite placer dans cette case. 
 * Le programme vérifie ensuite si l'insertion de ce chiffre est possible.
 * Une fois la partie terminée, le programme affiche un message indiquant que la partie est finie. 
 * Enfin, le joueur a la possibilité de choisir s'il souhaite rejouer ou non.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * \def N
 * \brief Déclaration de la Taille n de la grille.
 * 
 * La Taille de la Grille dépend du nombre n saisit (3 si grille3x3, 4 si grille4x4, 5 si grille5x5 ...)
 * 
 */
#define N 4
#define TAILLE (N*N)

/**
 * \var COIN
 * \brief Déclaration de la constante permettant de saisir les coin d'une grille
*/
const char COIN = '+';

/**
 * \var LIGNE
 * \brief Déclaration de la constante permettant de saisir les lignes d'une grille
*/
const char LIGNE = '-';

/**
 * \var COLONNE
 * \brief Déclaration de la constante permettant de saisir les colonnes d'une grille
*/
const char COLONNE = '|';

/**
 * \typedef tGrille
 * \brief Type représentant la grille de Sudoku.
 * 
 * Le type tGrille sert a stocké les valeur contenu dans la grille de sudoku.
 */
typedef int tGrille[N*N][N*N];

/**
 * \fn void chargerGrille(tGrille grille)
 * @brief Charge la grille de Sudoku à partir d'un fichier.
 *
 * Cette fonction permet de charger une grille de Sudoku à partir d'un fichier.
 *
 * @param grille La grille à charger.
 */
void chargerGrille(tGrille grille);

/**
 * \fn void afficherGrille(tGrille grille)
 * @brief Affiche la grille de Sudoku.
 *
 * Cette fonction affiche la grille de Sudoku sur la console.
 *
 * @param grille La grille à afficher.
 */
void afficherGrille(tGrille grille);

/**
 * \fn void saisir(int *val)
 * @brief Saisit une valeur à partir de l'entrée standard.
 *
 * Cette fonction demande à l'utilisateur de saisir une valeur et s'assure que la valeur est valide.
 *
 * @param val Pointeur vers la variable où stocker la valeur saisie.
 */
void saisir(int *val);

/**
 * \fn bool possible(tGrille grille, int ligne, int colonne, int val)
 * @brief Vérifie si une valeur peut être placée dans une position spécifique de la grille.
 *
 * Cette fonction vérifie si une valeur peut être légalement placée dans une position donnée de la grille.
 *
 * @param grille La grille de Sudoku.
 * @param ligne La ligne de la grille.
 * @param colonne La colonne de la grille.
 * @param val La valeur à vérifier.
 * @return true si la valeur est possible, false sinon.
 */
bool possible(tGrille grille, int ligne, int colonne, int val);

/**
 * \fn bool pleine(tGrille grille)
 * @brief Vérifie si la grille de Sudoku est pleine.
 *
 * Cette fonction vérifie si la grille de Sudoku est entièrement remplie.
 *
 * @param grille La grille de Sudoku.
 * @return true si la grille est pleine, false sinon.
 */
bool pleine(tGrille grille);

/**
 * \fn int main()
 * @brief Fonction principale du jeu Sudoku.
 *
 * Cette fonction gère le déroulement principal du jeu Sudoku.
 *
 * @return EXIT_SUCCESS si le programme s'exécute correctement.
 */
int main(){
    //déclaration des variables
    int l,c,val;
    char fin[4];
    tGrille grille; 
    
    

    chargerGrille(grille);
    while(!pleine(grille)){
        afficherGrille(grille);
        printf("Saisir un numéro de ligne entre 1 et %d : \n", N*N);
        saisir(&l);
        printf("Ligne %d : Saisir un numéro de colonne entre 1 et %d : \n",l, N*N);
        saisir(&c);
        if(grille[l-1][c-1] != 0){
            printf("Ligne %d / Colonne %d : La case est déjà rempli. Veuillez resaisir une case qui est vide. \n", l,c);
        }
        else{
            printf("Ligne %d / Colonne %d : Saisir une valeur entre 1 et %d : \n",l,c, N*N);
            saisir(&val);
            if(possible(grille,l-1,c-1,val)){
                grille[l-1][c-1] = val;
            }
        }
    }
    afficherGrille(grille);
    printf("Bravo, Voulez-vous rejouer ? (tapez oui / non)");
    scanf("%s", fin);
    if(strcmp(fin, "oui") == 0){
        return main(); // sert a relancer le jeu
    }
    else{
        printf("Fin du jeu");
    }

    return EXIT_SUCCESS;
}

void chargerGrille(tGrille grille){
    /**
     * \var nomFihier
     * \brief Déclaration de la variable nomFichier permettant de stocké le nom du fichier a chargé
    */
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    while(f==NULL){
        printf("\n ERREUR (aucun fichier de ce nom) %s\n", nomFichier);
        printf("Nom du fichier ? ");
        scanf("%s", nomFichier);
        f = fopen(nomFichier, "rb");
    } 
    fread(grille, sizeof(int), N*N*N*N, f);
    fclose(f);
}

void afficherGrille(tGrille grille){
    int ligne;
    int colonne;
    int i;
    int plus;
    int moins;
    printf("     ");
    for(i = 1; i <= TAILLE; i++){
        if(i<10){
            printf("  %d ", i);
        }
        else{
            printf(" %d ", i);
        }
        if(i%N == 0){
            printf(" ");
        }
    }
    printf("\n    ");
    for(plus =1; plus <= N; plus++){
        printf("%c", COIN);
        for(moins = 0; moins < N * 4 ; moins++){
            printf("%c", LIGNE);
        }
    }
    printf("+\n");
    for (ligne = 0; ligne < TAILLE; ligne++) {
        if(ligne < 9){
            printf(" %d  %c", ligne + 1, COLONNE);
        }
        else{
            printf("%d  %c", ligne + 1, COLONNE);
        }
        
        for (colonne = 0; colonne < TAILLE; colonne++) {
            if (grille[ligne][colonne] == 0) {
                printf("  . ");
            } 
            else {
                if(grille[ligne][colonne]<10){
                    printf("  %d ", grille[ligne][colonne]);
                }
                else{
                    printf(" %d ", grille[ligne][colonne]);
                }
                
            }

            if ((colonne + 1) % N == 0) {
                printf("%c", COLONNE);
            }
        }
        printf("\n");
        if ((ligne +1) % N == 0) {//affiche la ligne de séparation a chaque fois qu'il y est n ligne
            printf("    ");
            for(plus =1; plus <= N; plus++){
                printf("%c", COIN);
                for(moins = 0; moins < N * 4 ; moins++){
                    printf("%c", LIGNE);
                }
            }
            printf("+\n");
        }
    }
}

void saisir(int *val){
    int x;
    char ch[10];
    scanf("%s", ch);
    while ((sscanf(ch, "%d", &x) == 0) || (x < 1) || (x >N*N)) {
        printf("Erreur, %s est une valeur invalide, Veuillez resaisir une valeur valide : ", ch);
        scanf("%s", ch);
    }
    printf("Valeur saisie correct\n");
    sscanf(ch, "%d", &x);
    *val = x;
}

bool possible(tGrille grille, int ligne, int colonne, int val){
    bool estPresent = true;
    int l,c;
    int debut_ligne_bloc = N*(ligne / N);
    int debut_colonne_bloc = N*(colonne / N);

    for(l = 0; l < N*N; l++){
        if(grille[l][colonne] == val){
            printf("Ligne %d/Colonne %d : Erreur, %d est déjà présent dans cette colonne.\n\n", ligne, colonne, val);
            estPresent = false;
        }
    }
    for(c=0; c<N * N; c++){
        if(grille[ligne][c] == val){
            printf("Ligne %d/Colonne %d : Erreur, %d est déjà présent dans cette ligne.\n\n", ligne, colonne, val);
            estPresent = false;
        }
        
    }
    

    for (int i = debut_ligne_bloc; i < debut_ligne_bloc + (N); i++) {
        for(int j = debut_colonne_bloc; j < debut_colonne_bloc + (N); j++) {
            if (grille[i][j] == val) {
                printf("La valeur est déjà présente dans le même bloc.\n\n");
                estPresent = false;
            }
        }
    }
    
    return estPresent;
}

bool pleine(tGrille grille){
    bool pleine = true;
    int l,c;
    for(l = 0; l< N*N; l++){
        for(c=0; c<N*N; c++){
            if(grille[l][c] == 0){
                pleine = false;
            }
        }
    }
    return pleine;
}