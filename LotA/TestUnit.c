#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "LotA.h"

/**
\file [TestUnit.c]
\brief Code des tests CUnit pour les fonctions du lot A
\author Monsinjon Nicolas, Li Dinghao, Thiry Maxime, Halimi Yael
**/

void test_newGrille(void)
    {

      int** grille = newGrille(5);
      grille[0][0]=0;
      grille[4][4]=6;
      CU_ASSERT(grille[0][0] == 0);
      CU_ASSERT(grille[4][4] == 6);
      freeGrille(grille,5);
    }
    /**
    \fn void test_newGrille(void)
    \brief Test de la fonction newGrille
    \return Cette fonction ne retourne rien
    **/

void test_iniGrille(void)
    {

      int** grille = newGrille(5);
      iniGrille(grille,5);
      CU_ASSERT((grille[0][0] == 1)||(grille[0][0] == 2)||(grille[0][0] == 3)||(grille[0][0] == 4)||(grille[0][0] == 5)||(grille[0][0] == 6));
      CU_ASSERT((grille[4][4] == 1)||(grille[4][4] == 2)||(grille[4][4] == 3)||(grille[4][4] == 4)||(grille[4][4] == 5)||(grille[4][4] == 6));
      freeGrille(grille,5);
    }
    /**
    \fn void test_iniGrille(void)
    \brief Test de la fonction iniGrille
    \return Cette fonction ne retourne rien
    **/

void test_remplacer(void)
    {

      int** grille = newGrille(5);
      iniGrille(grille,5);
      rempalcer (grille,5,0,0,6);
      rempalcer (grille,5,4,4,1);
      CU_ASSERT(grille[0][0] == 6);
      CU_ASSERT(grille[4][4] == 1);
      freeGrille(grille,5);
    }
    /**
    \fn void test_remplacer(void)
    \brief Test de la fonction remplacer
    \return Cette fonction ne retourne rien
    **/

void test_initChange_changer(void)
    {
      int i,j,res;
      int** grille = newGrille(3);
      grille[0][0]=1;
      grille[0][1]=1;
      grille[0][2]=1;
      grille[1][0]=1;
      grille[1][1]=2;
      grille[1][2]=1;
      grille[2][0]=1;
      grille[2][1]=1;
      grille[2][2]=1;
      initChanger(grille,3,2);
      res = 1;
      for(i=0;i<3;i++){
        for(j=0;j<3;j++)
        {
          if(grille[i][j]!=2)
            res=0;
        }
      }
      freeGrille(grille,3);
      CU_ASSERT(res == 1);

    }
    /**
    \fn void test_initChange_changer(void)
    \brief Test des fonctions initChanger et changer
    \return Cette fonction ne retourne rien
    **/

  void test_creatFichier(void)
    {
      int i,j,res;
      int** grille = newGrille(3);
      int** grilleCopy = newGrille(3);
      grille[0][0]=1;
      grille[0][1]=1;
      grille[0][2]=1;
      grille[1][0]=1;
      grille[1][1]=2;
      grille[1][2]=1;
      grille[2][0]=1;
      grille[2][1]=1;
      grille[2][2]=1;
      createFichier(grille,3,"f1");
      inputFichier(grilleCopy,3,"f1");
      res = 1;
      for(i=0;i<3;i++){
        for(j=0;j<3;j++)
        {
          if(grille[i][j]!=grilleCopy[i][j])
            res=0;
        }
      }
      freeGrille(grille,3);
      freeGrille(grilleCopy,3);
      CU_ASSERT(res == 1);

    }
    /**
    \fn void test_creatFichier(void)
    \brief Test de la fonction createFichier
    \return Cette fonction ne retourne rien
    **/

    void test_inputFichier(void)
    {
      int i,j,res;
      int** grille = newGrille(3);
      int** grilleCopy = newGrille(3);
      grille[0][0]=1;
      grille[0][1]=1;
      grille[0][2]=1;
      grille[1][0]=1;
      grille[1][1]=2;
      grille[1][2]=1;
      grille[2][0]=1;
      grille[2][1]=1;
      grille[2][2]=1;
      createFichier(grille,3,"f2");
      inputFichier(grilleCopy,3,"f2");
      res = 1;
      for(i=0;i<3;i++){
        for(j=0;j<3;j++)
        {
          if(grille[i][j]!=grilleCopy[i][j])
            res=0;
        }
      }
      freeGrille(grille,3);
      freeGrille(grilleCopy,3);
      CU_ASSERT(res == 1);
    }
    /**
    \fn void test_inputFichier(void)
    \brief Test de la fonction inputFichier
    \return Cette fonction ne retourne rien
    **/



int main() {
	CU_pSuite pSuite = NULL;

	if (CU_initialize_registry() != CUE_SUCCESS) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("Suite",NULL,NULL);

	if (pSuite==NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

    if (CU_add_test (pSuite, "test of newGrille()",test_newGrille)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

      if (CU_add_test (pSuite, "test of iniGrille()",test_iniGrille)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

     if (CU_add_test (pSuite, "test of rempalcer",test_remplacer)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

      if (CU_add_test (pSuite, "test of initChanger() et changer()",test_initChange_changer)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
      if (CU_add_test (pSuite, "test of createFichier() ",test_creatFichier)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
      if (CU_add_test (pSuite, "test of inputFichier()",test_inputFichier)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

	return 0;
}
