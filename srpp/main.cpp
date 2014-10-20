#include <allegro.h>
#include <ctime>
#include "DataFileReader.h"
#include "RandomDataGenerator.h"
#include "InputData.h"
#include "RandomSolver.h"
#include "Solution.h"

int main() {
	srand(time(NULL));
	allegro_init();
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 600, 600, 0, 0);

	install_keyboard();
	//install_mouse();
	
	DataSource* dataFile = new DataFileReader("input.txt");
	DataSource* source = new RandomDataGenerator();

	InputData* input = dataFile->getData();
	delete dataFile;
	delete source;

	Solver* solver = new RandomSolver();
	Solution* solution = solver->process(input);
	delete input;
	delete solver;

	solution->saveToFile("solution.txt");

	BITMAP* buf = create_bitmap(SCREEN_W, SCREEN_H);

	while (!key[KEY_ESC]) {
		clear_to_color(buf, 0);
		solution->draw(buf, 0, 0);
		blit(buf, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

		rest(10);
	}
	delete solution;
	destroy_bitmap(buf);

	allegro_exit();
	return 0;
}
END_OF_MAIN();