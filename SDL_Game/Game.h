#pragma once
#include "SDL/SDL.h"

class Game {
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Finalize();
private:
	void ProcessInput();
	void Update();
	void Draw();

	SDL_Window*   m_window;
	SDL_Renderer* m_renderer;
	Uint32 m_ticksCount;
	bool m_isRunning;
};