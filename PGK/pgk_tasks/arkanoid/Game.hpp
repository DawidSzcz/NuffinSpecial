#ifndef GAME_HPP
#define GAME_HPP

#include <list>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "IPositionable.hpp"
#include "TranslationVertexShader.hpp"
#include "DrawingManager.hpp"
#include "MotionManager.hpp"
#include "CollisionManager.hpp"
#include "IObserver.hpp"
#include "OnscreanText.hpp"
#include "Paddle.hpp"

class Game : public IObserver {
public:
	Game() : score_text(NULL) { InitNewGame(); }
	virtual void InitNewGame();
	virtual void HandleFrame(double delta_sec);
	virtual void Win();
	virtual void Lose();
	virtual void Cleanup();
	virtual void Notify(Notification n);
	virtual ~Game() { Cleanup(); }
	static void KeyCallback(GLFWwindow* w,int key,int scancode,int action,int mods);
protected:
	// managers
	DrawingManager picasso;
	MotionManager newton;
	CollisionManager cern;

	// shaders
	const char* const vshader = "TranslationVertexShader.vertexshader";
	const char* const fshader = "ColorFragmentShader.fragmentshader";
	const TranslationVertexShader sh = TranslationVertexShader(vshader,fshader);
	
	// game objects
	static Paddle* paddle;
	OnscreanText* score_text;
	OnscreanText* end_of_game_text;
	std::list<IPositionable*> objects;

	// mechanics
	bool freeze = false;

	// score
	int bricksNumber;
	int score = 0;
	static GLfloat paddle_velocity;
	virtual std::string buildScoreString() const { return "Score:" + std::to_string(score); }
};

#endif