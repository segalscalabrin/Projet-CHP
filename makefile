# Variables
MPICXX = g++                  # Utilisation du compilateur mpic++
CXXFLAGS = -Wall -O2 -Isrc   # Options de compilation, ajout de -Iinclude pour inclure le dossier `include`

SRC = src/**/*.cpp test/instationnaire/*.cpp test/personnalise/*.cpp test/stationnaire_1/*.cpp test/stationnaire_2/*.cpp src/*.cpp
OUT = run

# Compilation
all: $(OUT)

$(OUT): $(SRC)
	$(MPICXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
