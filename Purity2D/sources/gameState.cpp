#include "../libs/gameState.hpp"
GameState* GameState::instance = nullptr;

GameState* GameState::get() {
	if (instance == nullptr) {
		instance = new GameState();
	}
	return instance;
}