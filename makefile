# Variables
MPICXX = mpicxx  # Utilisation du compilateur local mpicxx
CXXFLAGS = -Wall -O2 

SRC = include/*.cpp main.cpp
OUT = run.exe

# Compilation
all: $(OUT)

$(OUT): $(SRC)
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) $(MPICXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
