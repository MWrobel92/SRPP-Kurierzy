#include <ctime>
#include "DataFileReader.h"
#include "RandomDataGenerator.h"
#include "InputData.h"
#include "RandomSolver.h"
#include "PizzaSolver.h"
#include "BruteforceSolver.h"
#include "Solution.h"
#include "NearestNeighbourSolver.h"
#include "Solver2opt.h"
#include <Windows.h>
#include <iostream>

int main(int argc, char* argv[]) {

	srand(time(NULL));
	if (argc == 1) {
		std::cout << "Podaj argument: nazwa pliku z zadaniem.\n";
	}
	DataSource* dataFile = new DataFileReader(argv[1]);

	InputData* input = dataFile->getData();
	delete dataFile;

	//Start pomiaru czasu

	//Inicjalizacja timera
	long long time;
	time = GetTickCount();
	//	Solver* solver = new BruteforceSolver();
	//	Solver* solver = new PizzaSolver();
	//  Solver* solver = new NearestNeighbourSolver();
	Solver* solver = new Solver2opt();
	Solution* solution = solver->process(input);
	time = GetTickCount() - time;

	delete input;
	delete solver;
	std::cout << argv[1] << "; ";
	std::cout << solution->getLength() << "; ";
	std::cout << time << "ms\n";

	solution->saveToFile("output\\" + string(argv[1]) + "_out");
	return 0;
}