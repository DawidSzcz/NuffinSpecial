#include <iostream>
#include <GL/glew.h>
#include "IGameState.hpp"
#include "CardsDeck.hpp"
#include "Game.hpp"

Game::Game(CardsDeck* deck)
: current_state(new InitialState(deck)) {}

void Game::GenerateBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const {
	current_state->GenerateBufferData(vertex_buffer,color_buffer);
}

void Game::ProcessFrame(double delta) {
	IGameState* new_state = current_state->HandleFrame(delta);

	if(new_state != NULL) {
		delete current_state;
		current_state = new_state;
	}
}

void Game::ProcessKeyAction(int key,int action) {
	IGameState* new_state = current_state->HandleKeyAction(key,action);

	if(new_state != NULL) {
		delete current_state;
		current_state = new_state;
	}
}

int Game::GetRoundNum() const {
	return current_state->GetRoundNum();
}

Game::~Game() {
	delete current_state;
}