#include <stdio.h>
#include <stdlib.h>


#define TAILLE 5

typedef struct tPosition{
    short nX;
    short nY;
}tPosition;

tPosition fctCase(const short nX, const short nY);
void pcdInitTab(int tCarre[TAILLE][TAILLE]);
short fctTestCase(const int tCarre[TAILLE][TAILLE], const tPosition stPos);
short fctTestTailleMin(const int nCoord);
short fctTestTailleMax(const int nCoord);
void fctCorriger(int *nCoord);
void pcdPlacer(const short nPos, int tCarre[TAILLE][TAILLE], const tPosition stPos);
void pcdAvancerDroite(int *pI, int *pJ, const tPosition stPos);
void pcdAvancerGauche(int *pJ, int *pI, const tPosition stPos);
void pcdAfficher(const int tCarre[TAILLE][TAILLE]);

int main()
{
    int tCarre[TAILLE][TAILLE];
    tPosition stPos;
    // nI, nJ, nCpt sont des compteurs
    int nI = 0, nJ = 0, nCpt = 1;

    pcdInitTab(tCarre);

    //nI et nJ sont à 2 car on souhaite commencer au milieu de la grille
    nI = (TAILLE/2)- 1;
    nJ = TAILLE/2;

    //cette boucle sert à remplir le carré magique
    do{
        //A chaque passage de la boucle on met à jour nX et nY
        stPos = fctCase(nI,nJ);
        //On test si la case est égale à 0 (c'est à dire si elle n'est pas encore complétée)
        //Si elle est égale à 0, elle prend la valeur du compteur et on se déplace d'un cran vers le haut et d'un cran vers la droite
        if (fctTestCase(tCarre, stPos) == 1){
            pcdPlacer(nCpt, tCarre, stPos);
            nCpt++;
            pcdAvancerDroite(&nI, &nJ, stPos);
        //Si la case n'est pas égale à 0 on se déplace d'une case vers le haut et une vers la gauche par rapport à la case déjà remplie
        }else{
            //On vérifie que ni nX, ni nY ne sortent pas de la grille
            pcdAvancerGauche(&nJ, &nI, stPos);
        }
    //On sort de la boucle une fois que le compteur ait atteint 25
    }while (nCpt <= TAILLE*TAILLE);

    //Affichage du carré magique
    pcdAfficher(tCarre);

    return 0;
}


void pcdInitTab(int tCarre[TAILLE][TAILLE]){
    int nI = 0, nJ = 0;
     //Boucle qui rempli le tableau de 0
    for(nI=0;nI<TAILLE;nI++){
        for(nJ=0;nJ<TAILLE;nJ++){
            tCarre[nI][nJ] = 0;
        }
    }
}

//###########################################
//FONCTION DE CASE
//*****************************************************************************************************//
//
// DESCRIPTION Permet d'avoir les coordonnées nx et ny
//
// ENTREE
//
// SORTIE   Renvoi les coordonnées nx et ny
//
// NOTE
//
//*****************************************************************************************************//



tPosition fctCase(const short nX, const short nY){
    tPosition stPosition;

    stPosition.nX = nX;
    stPosition.nY = nY;

    return stPosition;
}

//###########################################
//FONCTION DE TEST DE CASE
//*****************************************************************************************************//
//
// DESCRIPTION Booléen qui vérifie qu'une case est bien égale à 0
//
// ENTREE
//
// SORTIE   1 ou 0 (1 = vrai, 0 = faux)
//
// NOTE
//
//*****************************************************************************************************//


short fctTestCase(const int tCarre[TAILLE][TAILLE], const tPosition stPos){
    short snBool = 0;

    if (tCarre[stPos.nX][stPos.nY] == 0){
        snBool = 1;
    }
    return snBool;
}


//###########################################
//FONCTION DE TEST DE TAILLE MINIMUM DU PLATEAU
//*****************************************************************************************************//
//
// DESCRIPTION Vérifie que les coordonnées ne soient pas plus petites que la taille minimum
//
// ENTREE
//
// SORTIE   1 ou 0 (1 = vrai, 0 = faux)
//
// NOTE
//
//*****************************************************************************************************//

short fctTestTailleMin(const int nCoord){
    short snBool = 0;

    if (nCoord - 1 >= 0){
        snBool = 1;
    }

    return snBool;
}

//###########################################
//FONCTION DE TEST DE TAILLE MAXIMUM DU PLATEAU
//*****************************************************************************************************//
//
// DESCRIPTION Vérifie que les coordonnées ne soient pas plus grandes que la taille maximum
//
// ENTREE
//
// SORTIE   1 ou 0 (1 = vrai, 0 = faux)
//
// NOTE
//
//*****************************************************************************************************//

short fctTestTailleMax(const int nCoord){
    short snBool = 0;

    if (nCoord + 1 < 5){
        snBool = 1;
    }

    return snBool;
}


void fctCorriger(int *nCoord){

    if (*nCoord < 0){
        *nCoord = 4;
    }else if (*nCoord > 4){
        *nCoord = 0;
    }
   // return nCoord;
}

void pcdPlacer(const short nPos, int tCarre[TAILLE][TAILLE], const tPosition stPos){

    tCarre[stPos.nX][stPos.nY] = nPos;
}

void pcdAvancerDroite(int *pI, int *pJ, const tPosition stPos){

    (*pI)--;
    (*pJ)++;
    int  tmp;
    //On vérifie que ni nX, ni nY ne sortent pas de la grille
    if (fctTestTailleMin(stPos.nX) == 0){
        tmp = *pI;
        fctCorriger(&tmp);
        *pI = tmp;
    }
    if (fctTestTailleMax(stPos.nY) == 0){
        tmp = *pJ;
        fctCorriger(&tmp);
        *pJ = tmp;
    }
}

void pcdAvancerGauche(int *pJ, int *pI, const tPosition stPos){

    (*pJ)--;
    (*pI)--;
    int tmp;
    if (fctTestTailleMin(stPos.nY) == 0){
        tmp = *pJ;
        fctCorriger(&tmp);
        *pJ = tmp;
    }
    if (fctTestTailleMin(stPos.nX) == 0){
        tmp = *pI;
        fctCorriger(&tmp);
        *pI = tmp;
    }
}

void pcdAfficher(const int tCarre[TAILLE][TAILLE]){
    int nI = 0, nJ = 0;

    for(nI=0;nI<TAILLE;nI++){
        for(nJ=0;nJ<TAILLE;nJ++){
            printf("%i|", tCarre[nI][nJ]);
        }
        printf("\n");
    }
}
