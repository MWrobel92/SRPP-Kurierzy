#include <allegro.h>

int main() {
	allegro_init();
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

	install_keyboard();
	//install_mouse();

	BITMAP* buf = create_bitmap(SCREEN_W, SCREEN_H);

	while (!key[KEY_ESC]) {
		clear_to_color(buf, 0);
		circle(buf, 200, 200, 100, makecol(255, 255, 0));
		blit(buf, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

		rest(10);
	}
	destroy_bitmap(buf);

	allegro_exit();
	return 0;
}
END_OF_MAIN();