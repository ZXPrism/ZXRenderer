

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
SDL_Surface *surface;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

int main(int argc, char *argv[]) {
	

	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				running = false;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (event.key.scancode == SDLK_ESCAPE) {
					running = false;
				}
				// Handle other key events here
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				// Handle mouse button down events here
				break;
			case SDL_EVENT_MOUSE_MOTION:
				// Handle mouse motion events here
				break;
				// Handle other events as needed
			}
		}

		const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;

		/* as you can see from this, rendering draws over whatever was drawn before it. */
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); /* black, full alpha */
		SDL_RenderClear(renderer);                                   /* start with a blank canvas. */

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); /* white, full alpha */
		SDL_RenderDebugText(renderer, 272, 100, "Hello world!");
		SDL_RenderDebugText(renderer, 224, 150, "This is some debug text.");

		SDL_SetRenderDrawColor(renderer, 51, 102, 255, SDL_ALPHA_OPAQUE); /* light blue, full alpha */
		SDL_RenderDebugText(renderer, 184, 200, "You can do it in different colors.");
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); /* white, full alpha */

		SDL_SetRenderScale(renderer, 4.0f, 4.0f);
		SDL_RenderDebugText(renderer, 14, 65, "It can be scaled.");
		SDL_SetRenderScale(renderer, 1.0f, 1.0f);
		SDL_RenderDebugText(renderer, 64, 350, "This only does ASCII chars. So this laughing emoji won't draw: 🤣");

		SDL_RenderDebugTextFormat(renderer, (float)((WINDOW_WIDTH - (charsize * 46)) / 2), 400, "(This program has been running for %" SDL_PRIu64 " seconds.)", SDL_GetTicks() / 1000);

		SDL_RenderPresent(renderer); /* put it all on the screen! */

		SDL_UpdateWindowSurface(window);

		SDL_Delay(16);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
