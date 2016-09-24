BINDIR=./bin
OBJDIR=./obj
SRCDIR=./src
INCDIR=./include
TESTDIR=./testsuite

CC=clang
CFLAGS=-std=c99 -O0 -g -Wall -Wextra -I$(INCDIR)
LDFLAGS=-g

SRC_FILES=$(wildcard $(SRCDIR)/*.c)
OBJ_FILES=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC_FILES))

TESTS=$(TESTDIR)/test_chainage $(TESTDIR)/test_ensemble

EXEC=$(BINDIR)/quiestce

all: $(BINDIR)/quiestce

# Règle générique

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h
	$(CC) -c $(CFLAGS) $< -o $@

# Coeur du fil rouge

$(EXEC): $(OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_FILES) : | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

$(OBJDIR)/jeu.o: $(INCDIR)/ensemble.h $(INCDIR)/suspect.h

$(OBJDIR)/suspect.o: $(INCDIR)/ensemble.h

.PHONY: clean check

check: $(TESTS)
	$(TESTDIR)/test_chainage
	$(TESTDIR)/test_ensemble

$(TESTDIR)/test_chainage.o: $(TESTDIR)/test_chainage.c include/ensemble.h include/suspect.h $(TESTDIR)/tests.h
	$(CC) -c $(CFLAGS) $< -o $@

$(TESTDIR)/test_chainage: $(TESTDIR)/test_chainage.o $(OBJDIR)/suspect.o $(OBJDIR)/ensemble.o
	$(CC) $(LDFLAGS) $^ -o $@

$(TESTDIR)/test_ensemble.o: $(TESTDIR)/test_ensemble.c include/ensemble.h $(TESTDIR)/tests.h
	$(CC) -c $(CFLAGS) $< -o $@

$(TESTDIR)/test_ensemble: $(TESTDIR)/test_ensemble.o $(OBJDIR)/ensemble.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -rf $(EXEC) $(OBJ_FILES) $(TESTS_OBJ) $(TESTS) $(TESTDIR)/*.o
