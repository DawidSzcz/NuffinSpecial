#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Ball.hpp"
#include "Brick.hpp"
#include "DrawingManager.hpp"
#include "MotionManager.hpp"
#include "CollisionManager.hpp"
#include "OnscreanText.hpp"
#include "Paddle.hpp"
#include "Borders.hpp"
#include "EscapeLine.hpp"
#include "Background.hpp"
#include "Game.hpp"

Paddle* Game::paddle = NULL; GLfloat Game::paddle_velocity=0.6;

void Game::InitNewGame() {
	// background
	Background* bg = new Background(&sh,0.055);
	bg->SetupBuffers();
	picasso.Register(bg);
	objects.push_back(bg);

	// borders
	Borders* borders = new Borders(&sh);
	borders->SetupBuffers();
	borders->SetPrimitives();
	picasso.Register(borders);
	cern.Register(borders);
	objects.push_back(borders);

	// bricks
	GLfloat h = 0.6;
	GLfloat step = 0.072;
	int n = 5;
	bricksNumber = n+n-1;
	Brick* b;
	for(int i=0 ; i < n ; i++) {	
		b = new Brick(&sh);
		b->Position = glm::vec3(i*step,h,0.0);
		b->SetupBuffers();
		b->SetPrimitives();
		b->RegisterObserver(this);
		picasso.Register(b);
		cern.Register(b);
		objects.push_back(b);

		if(i != 0) {
			b = new Brick(&sh);
			b->Position = glm::vec3(-i*step,h,0.0);
			b->SetupBuffers();
			b->SetPrimitives();
			b->RegisterObserver(this);
			picasso.Register(b);
			cern.Register(b);
			objects.push_back(b);
		}
	}

	//escape line
	EscapeLine* l = new EscapeLine();
	l->Position = glm::vec3(0.0,-0.88,0.0);
	l->SetPrimitives();
	l->RegisterObserver(this);
	cern.Register(l);
	objects.push_back(l);

	// paddle
	paddle = new Paddle(&sh);
	paddle->Position = glm::vec3(0.0,-0.853,0.0);
	paddle->Velocity = glm::vec3(0.0,0.0,0.0);
	paddle->SetupBuffers();
	paddle->SetPrimitives();
	picasso.Register(paddle);
	newton.Register(paddle);
	cern.Register(paddle);
	objects.push_back(paddle);

	// ball
	Ball* ball = new Ball(&sh);
	ball->Position = glm::vec3(0.0,0.0,0.0);
	ball->Velocity = glm::vec3(0.0,-0.95,0.0);
	ball->SetupBuffers();
	ball->SetPrimitives();
	picasso.Register(ball);
	newton.Register(ball);
	cern.Register(ball);
	objects.push_back(ball);

	// onscrean text, raporting game score
	score_text = new OnscreanText(buildScoreString());
	score_text->Position = glm::vec3(20,20,0);
	score_text->Size = 30;
	picasso.Register(score_text);
	objects.push_back(score_text);

	// onscrean text, displayed when game is finished
	end_of_game_text = new OnscreanText();
	end_of_game_text->Position = glm::vec3(200,350,0);
	end_of_game_text->Size = 40;
}

void Game::HandleFrame(double delta_sec) {
	if(!freeze) {
		newton.HandleFrameMotion(delta_sec);
		cern.HandleCollisions();
		picasso.DrawAll();
	} else
		end_of_game_text->Draw();
}

void Game::KeyCallback(GLFWwindow* w,int key,int /*scancode*/,int action,int /*mods*/) {
	if(paddle == NULL) return;

	switch(key) {
	case GLFW_KEY_LEFT:
		if(action == GLFW_RELEASE) {
			if(paddle->Velocity[0] < 0.0) paddle->Velocity = glm::vec3(0.0);
		} else
			paddle->Velocity = paddle_velocity*glm::vec3(-1.0,0.0,0.0);
		break;
	case GLFW_KEY_RIGHT:
		if(action == GLFW_RELEASE) {
			if(paddle->Velocity[0] > 0.0) paddle->Velocity = glm::vec3(0.0);
		} else
			paddle->Velocity = paddle_velocity*glm::vec3(1.0,0.0,0.0);
		break;
	case GLFW_KEY_ESCAPE:
		if(action == GLFW_PRESS) glfwSetWindowShouldClose(w,1);
		break;
	}
}

void Game::Notify(Notification n) {
	if(n.type == Notification::BRICK_HIT) {
		score++;
		if(score_text != NULL)
			score_text->Text = buildScoreString();
		if(score == bricksNumber)
			Win();
	} else { // BALL_ESCAPE
		Lose();
	}
}

void Game::Cleanup() {
	for(auto it=objects.begin() ; it != objects.end() ; it++) {
		if(*it != NULL) delete *it;
	}
	objects.clear();
}

void Game::Win() {
	freeze = true;
	end_of_game_text->Text = "You've won!";
}

void Game::Lose() {
	freeze = true;
	end_of_game_text->Text = "Game over.";
}