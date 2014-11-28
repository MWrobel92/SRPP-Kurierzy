#include <ctime>
#include "DataFileReader.h"
#include "RandomDataGenerator.h"
#include "InputData.h"
#include "RandomSolver.h"
#include "PizzaSolver.h"
#include "BruteforceSolver.h"
#include "MemethicSolver.h"
#include "Solution.h"
#include "NearestNeighbourSolver.h"
#include "Solver2opt.h"
#include "Solver3opt.h"
#include <Windows.h>
#include <iostream>

int main(int argc, char* argv[]) {

	srand(time(NULL));
	string fileName;

	if (argc == 1) {
		fileName = "input.txt";		
	}
	else {
		fileName = argv[1];
	}
	
	DataSource* dataFile = new DataFileReader(fileName);
	InputData* input = dataFile->getData();
	delete dataFile;

	//Start pomiaru czasu

	//Inicjalizacja timera
	long long time;
	time = GetTickCount();

	Solver* solver = new MemethicSolver();

	//	Solver* solver = new BruteforceSolver();
	//	Solver* solver = new PizzaSolver();
	//  Solver* solver = new NearestNeighbourSolver();
	//	Solver* solver = new Solver2opt(true);
	//  Solver* solver = new Solver3opt(true);

	Solution* solution = solver->process(input);
	time = GetTickCount() - time;

	delete input;
	delete solver;

	std::cout << "Plik: " << fileName << "\n";
	std::cout << "Dlugosc wszystkich sciezek:\t" << solution->getLength() << "\n";
	std::cout << "Czas wykonania algorytmu:\t" << time << "ms\n\n";

	solution->saveToFile("output\\" + fileName + "_out");
	system("pause");
	return 0;
}