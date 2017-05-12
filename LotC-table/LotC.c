#include "LotA.h"
#include <setjmp.h>

jmp_buf jmpbuffer;

int** initChanger2(int** grille,int taille, int color){
  int i=0;
  int j=0;
  int** nGrille = newGrille(taille);
  for(i=0;i<taille;i++){
    for(j=0;j<taille;j++){
      nGrille[i][j]=grille[i][j];
    }
  }
  initChanger(nGrille,taille,color);
  return nGrille;
}


void add(int* solution, int couleur, int profondeur){
	solution[profondeur] = couleur;
}


void solveur(int** grille, int taille, int n , int* solutions, int profondeur,int* solution) {
	// déclarations des variables locales i, g2, ...
		if(profondeur<=n){
			int i;
			int** nGrille = NULL ;
			for (i=1; i<=6; i=i+1) { // pour toutes les couleurs possibles
				solutions[profondeur-1]=i;
				nGrille = initChanger2(grille, taille, i);
				if (testCouleur(nGrille,taille)){
					freeGrille(nGrille,taille);
					printf("solution: \n");
					for (i=0;i<n;++i)
					{
						solution[i]=solutions[i];
					}
					longjmp(jmpbuffer,1);
						//printf("%d\n", profondeur );
					//exit(0);
				}
				else{
					solveur(nGrille,taille, n,solutions, profondeur+1,solution);
					freeGrille(nGrille,taille);
				}
			}
		}
	}

void getSolution(int** grille, int taille, int step,int* solution){
	int* solutions = (int*)calloc(step+1,sizeof(int));
	int i;
	for(i=0;i<=step;i++){
		solutions[i]=0;
	}

	solveur(grille,taille,step,solutions,1,solution);
	
	// printf("solution: \n");
	// for (i=0;i<step;++i)
	// {
	// 	printf(" %d ",solution[i]);
	// }
	free(solutions);
}

/*
    @param: la pointeur de grille,la taille de grille
    @retuen: rien
*/
// void afficher(int** grille,int taille){
//     int i,j;
//     for(i=0;i<taille;i++){
//         printf("\n");
//         for(j=0;j<taille;j++){
//             printf(" %d ",grille[i][j]);
//         }
//     }
//     printf("\n");
// }

// void saveSolution(solution,n,solutions){
// 	if(flag==0){
// 		int i;
// 		for (i = 0; i < n; ++i)
// 		{
// 			solution[i]=solutions[i];
// 		}
// 		flag=1;
// 	}
// }
void traitS(int* solution,int step,int coup){
	int i,j; 
	for(i=0;i<step;i++){
		if(solution[i]!=1)
			break;
	}

	for (j = i-coup ; j < step; ++j)
	{
		printf("  %d  ",solution[j]);
	}
}



int main()
{
	  int taille = 5;
      int** grille = newGrille(taille);
      iniGrille(grille,taille);
      // grille[0][0]=2;
      // grille[0][1]=1;
      // grille[0][2]=5;
      // grille[1][0]=3;
      // grille[1][1]=2;
      // grille[1][2]=5;
      // grille[2][0]=3;
      // grille[2][1]=3;
      //grille[2][2]=5;

      int step=1;
      int flag=0;
      int i;
      int* solution = (int*)calloc(50,sizeof(int));
     // int coup=0;
      afficher(grille,taille);
       printf("La taille de la grille est %d\n\n",taille);
      // if((grille[0][0]!=1)&&((grille[0][1]==1)||(grille[1][0]==1)))
     	// 	{
     	// 		coup=1;
     	// 	}

      while(flag==0){	
      	    i = 0;
     		i = setjmp(jmpbuffer);
     		if(i==0){
     			getSolution(grille,taille,step,solution);
     		}
     		if(solution[0]==0){
     			printf("step %d est trop petit\n",step);
     			step++;
     		}else{
     			flag = 1;
     		}	
     		
     	 }     		
     	//traitS(solution,step,coup);
          
     for (i=0;i<step;++i)
		{
			printf("  %d  ",solution[i]); 
		}
     free(solution);
    freeGrille(grille,taille);

 //   printf("%d \n",flag);
	return 0;
}
