#include "Game.h"

Game::Game()
:m_window(nullptr)
,m_renderer(nullptr)
,m_isRunning(true)
,m_ticksCount(0)
{

}

bool Game::Initialize(const char* windowTitle) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		/* SDLを初期化できません */
		return false;
	}

	m_window = SDL_CreateWindow(windowTitle, 100, 100, 1024, 768, 0);
	if (!m_window) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		/* ウィンドウの生成に失敗しました */
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_renderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		/* レンダラーの生成に失敗しました */
		return false;
	}

	m_ticksCount = SDL_GetTicks();
	return true;
}

void Game::Finalize() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::RunLoop() {
	while (m_isRunning) {
		ProcessInput();
		Update();
		Draw();
	}
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			m_isRunning = false;
			break;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		m_isRunning = false;
	}
}

void Game::Update() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksCount + 16));
	float deltaTime = (SDL_GetTicks() - m_ticksCount) / 1000.0f;
	if (deltaTime > 0.05f) deltaTime = 0.05f;
	m_ticksCount = SDL_GetTicks();


}

void Game::Draw() {
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);


	SDL_RenderPresent(m_renderer);
}