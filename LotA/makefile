CFLAG = -Wall -Wextra -lcunit

all : test_cunit_lotA

	
test_cunit_lotA : LotA.c TestUnit.c LotA.h 
		gcc TestUnit.c LotA.c LotA.h -o test_cunit_lotA $(CFLAG)