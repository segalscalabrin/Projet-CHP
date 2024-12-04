# Variables
MPICXX = mpic++                 # Utilisation du compilateur mpic++
CXXFLAGS = -Wall -O2 -Isrc   # Options de compilation, ajout de -Iinclude pour inclure le dossier `include`

SRC = src/**/*.cpp	src/*.cpp		cas_test/**/*.cpp		test/*.cpp 
OUT = eq_chaleur

# Compilation
all: $(OUT)

$(OUT): $(SRC)
	$(MPICXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
