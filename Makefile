## Version 1.2

## (vide) => all => compile trier
## tst => compile et lance tester_trier 
## tester => petit script qui compare avec sort
## debug =>  lance nemiver (debugger)
## memoire => lance valrind (fuite muc0u8730 'a9moire) 
## tgz => construit le .tgz pour rendre

# Compilateur 
CC  :=  gcc
#options de compilation
CFLAGS :=  -ansi -Wall -Wextra -pedantic -ggdb


MODULE := file trier_monotonie 
HEADERS := $(MODULE:%=%.h) 

.PHONY : all tst tester debug memoire tgz


# si vous faites un programme de test 
#all : trier tester_trier
# sinon
all : trier 


# Ruc0u8730 'aegle de compilation
%.o : %.c  $(HEADERS) 
	$(CC) -c $(CFLAGS) -o $@ $<

trier : $(MODULE:%=%.o) $(HEADERS) trier.c 
	$(CC) $(CFLAGS) -o $@  $(MODULE:%=%.o) trier.c 


# pour le programme de test 
tester_trier : $(MODULE:%=%.o) $(HEADERS) tester_trier.c 
	$(CC) $(CFLAGS) -o $@ $(MODULE:%=%.o) tester_trier.c


tst : tester_trier
	./tester_trier |head

# Fichier uc0u8730 '86 trier pour effectuer les tests
#TEST_FILE := trier_monotonie.h
TEST_FILE := Makefile.txt

tester : trier
	./trier < $(TEST_FILE) > $(TEST_FILE).trie
# pour que sort fonctionne avec 'native byte value'
	LC_ALL=C ; sort  < $(TEST_FILE) -o $(TEST_FILE).sorted
	if diff $(TEST_FILE).trie $(TEST_FILE).sorted ; then echo "OK" ; else echo "SOUCIS" ; fi

debug : trier
	nemiver ./trier < $(TEST_FILE)


memoire : trier
	valgrind --leak-check=full ./trier < $(TEST_FILE)

tgz :
	tar czf PASD_mini-projet.tgz Makefile Makefile.txt *.c *.h compte-rendu.pdf
