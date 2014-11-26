#include"MemethicSolver.h"

MemethicSolver::MemethicSolver()
{
	generations = 100;
	hardMutations = 2;
	hardMutations = 3;

}

MemethicSolver::~MemethicSolver()
{
}

Solution* MemethicSolver::process(InputData* input) {

	// Generowanie populacji pocz¹tkowej
	PizzaSolver pizzaSolver;
	vector<Solution*> solutions = pizzaSolver.makeSolutions(input);

	Solution* bestSolution = findBestSolution(solutions);
	Solution* copyOfBestSolution = new Solution(*bestSolution);

	// Pokolenia
	int i;
	for (i=0; i<generations; ++i) {

		// Wygenerowanie kolejnego pokolenia
		bestSolution = generation(solutions);

		// Zapisanie kopii najlepszego elementu w historii, aby siê nie utraci³
		if (bestSolution->getLength() < copyOfBestSolution->getLength()) {
			delete copyOfBestSolution;
			copyOfBestSolution = new Solution(*bestSolution);
		}

	}

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

	// Mutacja
	for (i=0; i<hardMutations; ++i) {
		Solution* solutionToMutate = solutions.at(rand()%numberOfSolutions);
		solutionToMutate->mutate();
	}
	
	for (i=0; i<softMutations; ++i) {
		Solution* solutionToMutate = solutions.at(rand()%numberOfSolutions);
		solutionToMutate->mutateSoftly();
	}

	// Selekcja

	return findBestSolution(solutions);
}

