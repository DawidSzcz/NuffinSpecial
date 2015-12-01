#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include "IGameState.hpp"
#include "CardsDeck.hpp"

class Game {
public:
	Game(CardsDeck* deck);
	virtual void GenerateBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const;
	virtual void ProcessFrame(double delta);
	virtual void ProcessKeyAction(int key,int action);
	virtual int GetRoundNum() const;
	virtual ~Game();
protected:
	IGameState* current_state; // State design pattern
};

#endif
