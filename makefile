# Variables generales
CXX = g++
CXXFLAGS = -std=c++11 -O0

# Ejecutables y sus archivos fuente principales
TARGETS = uhr_bf uhr_dac

# Archivos fuente de cada ejecutable
tester1_SRC = uhr_bf.cpp 
tester2_SRC = uhr_dac.cpp 

# Objetos de cada ejecutable
tester1_OBJ = $(tester1_SRC:.cpp=.o)
tester2_OBJ = $(tester2_SRC:.cpp=.o)

# Regla por defecto
all: $(TARGETS)
# Regla genérica para compilar objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar
clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean
