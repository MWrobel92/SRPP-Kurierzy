#include"MemethicSolver.h"
#include "Solver2opt.h"
#include "Solver3opt.h"
#include "RandomSolver.h"
#include <iostream>
#include <cstdlib>

MemethicSolver::MemethicSolver()
{
	softMutations = 0;
	crossbreedings = 0;
}

MemethicSolver::~MemethicSolver()
{
}

Solution* MemethicSolver::process(InputData* input) {

	getK = input->getK();
	generationSize = getK * 10;
	hardMutations = generationSize;
	generations = 1000 / generationSize;
	// Generowanie populacji pocz¹tkowej
	PizzaSolver pizzaSolver;
	NearestNeighbourSolver nnSolver;
	Solver2opt solver2opt(false);
	Solver3opt solver3opt(true);
	RandomSolver randomSolver;
	vector<Solution*> solutions;
	//	solutions.push_back(pizzaSolver.makeSolutions(input));
	solutions.push_back(solver3opt.process(input));
	//solutions.push_back(pizzaSolver.process(input));
	for (int i = 0; i < generationSize; ++i) {
//		solutions.push_back(randomSolver.process(input));
		solutions.push_back(new Solution(*solutions[0]));
	}
	//	solutions.push_back(nnSolver.process(input));

	Solution* bestSolution = findBestSolution(solutions);
	Solution* copyOfBestSolution = new Solution(*bestSolution);

	// Pokolenia
	int i;
	for (i=0; i<generations; ++i) {

		// Wygenerowanie kolejnego pokolenia
		bestSolution = generation(solutions);
		std::cerr << bestSolution->getLength() << " " << solutions.size() << endl;
		// Zapisanie kopii najlepszego elementu w historii, aby siê nie utraci³
		if (bestSolution->getLength() < copyOfBestSolution->getLength()) {
			delete copyOfBestSolution;
			copyOfBestSolution = new Solution(*bestSolution);
		}

	}

	// TYLKO DO TESTOWANIA!!!
	// copyOfBestSolution = copyOfBestSolution->crossbreed(solutions.at(getK), getK);

	// Usuniêcie ca³ej populacji (najlepszy rezultat i tak ma swoj¹ kopiê)
	for (i=0; i<solutions.size(); ++i) {
		delete solutions.at(i);
	}

	return copyOfBestSolution;
}

Solution* MemethicSolver::findBestSolution(vector<Solution*> &solutions) {

	// Wybór najlepszego rozwi¹zania
	Solution* bestSolution = solutions.at(0);
	for (int i = 1; i < solutions.size(); ++i) { // Ma siê wykonaæ k-1 razy

		if (solutions.at(i)->getLength() < bestSolution->getLength()) {
			bestSolution = solutions.at(i);
		}
	}
	return bestSolution;
};

Solution* MemethicSolver::generation(vector<Solution*> &solutions) {
	
	// Uwaga: Funkcja MODYFIKUJE wektor przekazywany przez referencjê!
	// Zwraca wskaŸnik do najlepszego rozwi¹zania
	int i;
	int numberOfSolutions = solutions.size();

	// Krzy¿owanie
	for (i=0; i<crossbreedings; ++i) {
		solutions.push_back(solutions.at(rand()%numberOfSolutions)->crossbreed(solutions.at(rand()%numberOfSolutions), getK));
	}

	// Mutacja
	for (i=0; i<hardMutations; ++i) {
		Solution* solutionToMutate = solutions.at(rand()%numberOfSolutions);
		solutions.push_back(new Solution(*solutionToMutate)); // Zapamiêtanie kopii
		solutionToMutate->mutate();
	}
	
	for (i=0; i<softMutations; ++i) {
		Solution* solutionToMutate = solutions.at(rand()%numberOfSolutions);		
		//solutions.push_back(new Solution(*solutionToMutate)); // Zapamiêtanie kopii
		solutionToMutate->mutateSoftly();
	}

	//Ulepsz rozwi¹zania (2-opt)
	Solver2opt solver2opt(false);
	for (i = 0; i < solutions.size(); ++i) {
		Solution* old = solutions[i];
		vector<Route*> routes;
		for (int j = 0; j < old->getRouteCount(); ++j) {
			routes.push_back(solver2opt.solveTSP(old->getRouteAsInputData(j)));
		}
		solutions[i] = new Solution(routes);
		delete old;
	}

	// Selekcja
	int j;
	Solution* temp;

	// // Sortowanie przez proste wstawianie
	for (i=1; i<solutions.size(); ++i) {
		temp = solutions.at(i);
		for (j=i; j>0; --j) {
//			if (solutions.at(j - 1) < solutions.at(j)) {
			if (solutions.at(j - 1)->getLength() > temp->getLength()) {
					solutions.at(j) = solutions.at(j - 1);
			}
			else {
				break;
			}
		}
		solutions.at(j) = temp;
	}

	// // Usuniêcie nadmiarowych rozwi¹zañ
	for (i=solutions.size(); i>generationSize; --i) {
		Solution* toDelete = solutions.at(i-1);
		solutions.pop_back();
		delete toDelete;
	}

	return solutions.at(0);
}

