
#include "LotA.h"

typedef struct maillon* pile;

struct maillon{
  int num;
  pile next;
};


/*
    @param: une pile
    @retuen: tester si la est vide
*/
int estVide(pile l){
  return NULL == l;
}

/*
    @param: une pile
    @retuen: la pile apres le empilement
*/
pile empiler(pile l, int i){
  pile p = (pile) malloc(sizeof(struct maillon));
  p->num=i;
  p->next = l;
  return p;
}

/*
    @param: une pile
    @function: depiler la pile
    @retuen: rien 
*/
void depiler(pile *l){
  (*l)=(*l)->next;
}


/*
    @param: une pile
    @retuen: la longueur de la pile
*/
int longueur(pile p){
  int i=0;
  while(!estVide(p)){
    p=p->next;
    i++;
  }
  return i;
}


/*
    @param: la pointeur de grille,la taille de grille
    @retuen: 1 si le client gagne , 0 sinon
*/
int win(int** grille,int taille){
    int couleur = grille[0][0];
    int i,j;
    for(i=0;i<taille;i++){
        for(j=0;j<taille;j++){
            if(grille[i][j]!=couleur)
                return 0;
        }
    }
    return 1;
}


/*
    @param: deux pointeurs de grille,la taille de grille
    @retuen: 1 si les deux sont egal 0 sinon.
*/
int egale(int** grille1, int** grille2, int taille){
    int flag=1;
    int i=0;
    int j=0;
    for(i=0;i<taille;i++){
      for(j=0;j<taille;j++){
        if(grille1[i][j]!=grille2[i][j])
          flag=0;
      }
    }
    if(flag==1)
      return 1;
    else
      return 0;
}




/*
    @param: la pile de la solution
    @fonction: affichage de la solution
    @retuen: rien
*/
void uneSolutionTrouvee(pile solution){
  int a;
  printf("le solution plus petit (si il est la dernier) avec l'ordre \"<--\" : \n");
  while(!estVide(solution)){
    a = solution->num;
    printf("%d ",a);
    depiler(&solution);
  }
  printf("\n");
}



/*
    @param: la pointeur de grille,la taille de grille, la pile de solution, la profondeur
    @fonction: trouver  les solutions 
    @retuen: rien
*/
int max = 1000;
void solveur(int** grille,int taille, pile solution, int profondeur){
  if(profondeur+1 < max){
  int i,j,k;
  int** g1= newGrille(taille);
  int** g2= newGrille(taille);
  
  for(i=1;i<7;i++){
   
      solution = empiler(solution,i);
      //printf("empiler  %d \n",i);
      for(k=0;k<taille;k++){
	       for(j=0;j<taille;j++){
           g1[k][j]=grille[k][j];
           g2[k][j]=grille[k][j];
	       }
      } 
      //printf("i= %d \n",i);
      int pointo = g2[0][0];
      //afficher(g2,taille); 
      initChanger(g2,taille,i);
      //afficher(g2,taille); 
      initChanger(g2,taille,pointo); 
      //afficher(g2,taille);   
      //printf("egale? : %d  ",egale(g1,g2,taille));   
      if(!egale(g1,g2,taille)){
      initChanger(g1,taille,i); //on vérifie que le coup a modifié quelque chose, sinon il est null
	       if(win(g1,taille)){
	         max=longueur(solution); //profondeur a la place d'utiliser la fonction longueur
	         uneSolutionTrouvee(solution);
	        }
	        else{	  
	         solveur(g1,taille,solution,profondeur+1);
	        }
      }

      //printf("depiler  %d \n",i);
      depiler(&solution);
  }
  freeGrille(g1,taille);
  freeGrille(g2,taille);
  }
}


/*
    @param: la pointeur de grille,la taille de grille
    @retuen: rien
*/
void afficher(int** grille,int taille){
    int i,j;
    for(i=0;i<taille;i++){
        printf("\n");
        for(j=0;j<taille;j++){
            printf(" %d ",grille[i][j]);
        }
    }
    printf("\n");
}



/*@require: rien
  @assigns: rien
  @ensure : effacer le flux du input(stdin)
*/
void clearStdin()
{
    while ((getchar()) != '\n');
}


int main()
{   
    
    int taille;

    printf("votre taille( un chiffre !!!) pour le test (pas trop grande) \n");
    scanf("%d",&taille);

    

    int** grille; 
    pile solution=NULL;
   

    grille = newGrille(taille);
    iniGrille(grille,taille);
    afficher(grille,taille);
    
       
    solveur(grille,taille,solution,1);
    
    freeGrille(grille,taille);

    return 0;
}