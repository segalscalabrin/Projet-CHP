# Variables
MPICXX = mpic++                  # Utilisation du compilateur mpic++
CXXFLAGS = -Wall -O2 -Iinclude   # Options de compilation, ajout de -Iinclude pour inclure le dossier `include`

SRC = include/*.cpp test/instationnaire/*.cpp test/personnalise/*.cpp test/stationnaire_1/*.cpp test/stationnaire_2/*.cpp main.cpp
OUT = run

# Compilation
all: $(OUT)

$(OUT): $(SRC)
	$(MPICXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
