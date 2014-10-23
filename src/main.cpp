#include <ctime>
#include "DataFileReader.h"
#include "RandomDataGenerator.h"
#include "InputData.h"
#include "RandomSolver.h"
#include "PizzaSolver.h"
#include "Solution.h"
#include <Windows.h>
#include <iostream>

int main() {

	srand(time(NULL));
	
	DataSource* dataFile = new DataFileReader("input.txt");

	InputData* input = dataFile->getData();
	delete dataFile;

	//Start pomiaru czasu

	//Inicjalizacja timera
	long long time;
	time = GetTickCount();
	Solver* solver = new PizzaSolver();
	Solution* solution = solver->process(input);
	time = GetTickCount() - time;

	delete input;
	delete solver;

	std::cout << "Dlugosc wszystkich sciezek:\t" << solution->getLength() << "\n";
	std::cout << "Czas wykonania algorytmu:\t" << time << "ms\n";

	solution->saveToFile("solution.txt");

	system("pause");

	return 0;
}