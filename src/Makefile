OBJ = PizzaDivider.o \
BruteforceSolver.o \
City.o \
DataFileReader.o \
DataSource.o \
InputData.o \
PizzaSolver.o \
RandomDataGenerator.o \
RandomSolver.o \
Route.o \
Solution.o \
Solver.o \
main.o

.SUFFIXES: .exe .cpp .o

all: a.exe

.cpp.o:
	g++ -c $<
	
a.exe: $(OBJ)
	g++ $(OBJ)	
