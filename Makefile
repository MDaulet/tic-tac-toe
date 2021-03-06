SHELL = /bin/sh

PROJECT  := tic-tac-toe

# ------------------
# External programs
# ------------------
CC  := gcc
RM  := rm -rf
DG  := doxygen

# --------------------
# Directories & Files
# --------------------
D_SRC    := ./src
D_DOC    := ./doc
D_TESTS  := $(D_SRC)/tests
FILES_C  := $(wildcard $(D_SRC)/*.c $(D_TESTS)/*.c)
FILES_O  := $(FILES_C:.c=.o)
D_UNITY  := 
D_IMG    := images


ifneq ($(D_UNITY),)
	MACRO_TESTING := -DTESTING
else
	MACRO_TESTING := 
endif

ENTRY_POINT := $(D_SRC)/main.c

FILES_PROGR_C :=  $(filter-out $(ENTRY_POINT), $(wildcard $(D_SRC)/*.c))
FILES_TESTS_C :=  $(wildcard $(D_TESTS)/*.c) $(D_UNITY)/src/unity.c $(D_UNITY)/extras/fixture/src/unity_fixture.c

PROJECT_WITHOUT_TESTS := $(FILES_PROGR_C) $(ENTRY_POINT)
PROJECT_WITH_TESTS := $(FILES_TESTS_C) $(FILES_PROGR_C)

PROJECT_WITHOUT_TESTS_O  := $(PROJECT_WITHOUT_TESTS:.c=.o)
PROJECT_WITH_TESTS_O  := $(PROJECT_WITH_TESTS:.c=.o)
FILES_C  := $(wildcard $(D_SRC)/*.c)
FILES_O  := $(FILES_C:.c=.o)

# ------------
# Flags
# ------------
CFLAGS  := -Wall -I/usr/include/allegro5 
LFLAGS  := -L/usr/lib 
LIBALLEGRO := `pkg-config --libs allegro-5 allegro_font-5 allegro_ttf-5`
INCS := -I $(D_UNITY)/src -I $(D_UNITY)/extras/fixture/src 

# ------------
# Targets
# ------------
default: $(PROJECT)

%.o: %.c
	$(CC) $(MACRO_TESTING) -c -I $(D_SRC) $(CFLAGS) $(INCS) $< -o $@ -lm

$(PROJECT): $(PROJECT_WITHOUT_TESTS_O)
	$(CC) -I $(D_SRC) $(LFLAGS) $(PROJECT_WITHOUT_TESTS_O) -o $@ $(LIBALLEGRO)

.phony: doxygen
doxygen:
	$(DG) $(D_DOC)/doxygen.config
	mkdir $(D_DOC)/output/html/doc
	cp -r -f $(D_DOC)/$(D_IMG) $(D_DOC)/output/html/doc
	cp  ./LICENSE $(D_DOC)/output/html/

.phony: html
html: doxygen

.phony: pdf
pdf: doxygen
	make -C $(D_DOC)/output/latex

.phony:	clean
clean:
	-$(RM) $(FILES_O) $(PROJECT) test-$(PROJECT) $(D_DOC)/output 

run-test: test-$(PROJECT)
	./test-$(PROJECT)

test-$(PROJECT): $(PROJECT_WITH_TESTS_O)
	$(CC) -I $(D_SRC) $(LFLAGS) $(PROJECT_WITH_TESTS_O) -o $@ $(LIBALLEGRO)
