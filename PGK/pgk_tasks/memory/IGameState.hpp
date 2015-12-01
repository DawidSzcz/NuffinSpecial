#ifndef IGAMESTATE_HPP
#define IGAMESTATE_HPP

#include <GL/glew.h>
#include "CardsDeck.hpp"

class IGameState { // State design pattern
public:
	IGameState(CardsDeck* deck,int round);
	virtual void GenerateBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const;
	virtual IGameState* HandleFrame(double delta) = 0;
	virtual IGameState* HandleKeyAction(int key,int action) = 0;
	virtual void ReportRoundNumber() const;
	virtual ~IGameState() {}
	virtual int GetRoundNum() const;
protected:
	CardsDeck* cards;
	int round_num;
};

class ILastingState : public IGameState {
public:
	ILastingState(CardsDeck* deck,int round,double state_duration=0.0);
	virtual IGameState* HandleFrame(double delta);
	virtual IGameState* HandleKeyAction(int key,int action);
	virtual IGameState* HandleKeyEnter();
	virtual IGameState* NextStateTransition() = 0;
protected:
	const double duration;
	double time_elapsed;
	bool wait_for_enter;
};

class ISelectableState : public IGameState {
public:
	ISelectableState(CardsDeck* deck,int round);
	ISelectableState(CardsDeck* deck,int round,int sel_i,int sel_j);
	virtual void GenerateBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const;
	virtual void GenerateSelectionBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const;
	virtual IGameState* HandleFrame(double delta);
	virtual IGameState* HandleKeyAction(int key,int action);
	virtual IGameState* HandleKeyUp();
	virtual IGameState* HandleKeyDown();
	virtual IGameState* HandleKeyRight();
	virtual IGameState* HandleKeyLeft();
	virtual IGameState* HandleKeyEnter() = 0;
protected:
	bool trySelect(int i,int j);
	bool is_selected;
	int selected_i,selected_j;
};


class InitialState : public ILastingState {
public:
	InitialState(CardsDeck* deck,int round=0,double duration=0.0);
	virtual IGameState* HandleFrame(double delta);
	virtual IGameState* NextStateTransition();
};

class IdleState : public ISelectableState {
public:
	IdleState(CardsDeck* deck,int round);
	IdleState(CardsDeck* deck,int round,int sel_i,int sel_j);
	virtual IGameState* HandleKeyEnter();
};

class UncoveredCardState : public ISelectableState {
public:
	UncoveredCardState(CardsDeck* deck,int round,int unc_i,int unc_j);
	UncoveredCardState(CardsDeck* deck,int round,int unc_i,int unc_j,int sel_i,int sel_j);
	virtual void GenerateBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const;
	virtual IGameState* HandleKeyEnter();
protected:
	int uncovered_i,uncovered_j;
};

class UncoveredPairState : public ILastingState {
public:
	UncoveredPairState(CardsDeck* deck,int round,int unc1_i,int unc1_j,int unc2_i,int unc2_j);
	virtual void GenerateBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const;
	virtual IGameState* HandleFrame(double delta);
	virtual IGameState* NextStateTransition();
protected:
	int uncovered1_i,uncovered1_j,uncovered2_i,uncovered2_j;
};

class GameWonState : public ILastingState {
public:
	GameWonState(CardsDeck* deck,int round,double duration=0.0);
	virtual void GenerateBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const;
	virtual IGameState* HandleFrame(double delta);
	virtual IGameState* NextStateTransition();	
};

class TerminatingState : public IGameState {
public:
	TerminatingState(CardsDeck* deck,int round);
	virtual IGameState* HandleFrame(double delta);
	virtual IGameState* HandleKeyAction(int key,int action);
};

#endif