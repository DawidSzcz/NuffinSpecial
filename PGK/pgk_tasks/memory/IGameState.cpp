#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "common/text2D.hpp"
#include "IGameState.hpp"
using namespace std;

extern GLFWwindow* window; // I'll try to fix that later

const double uncovered_pair_duration = 1.0f;
static const int vs_per_card = 6;
static const GLfloat selection_border = 0.02f;
static const GLfloat border_offset[vs_per_card*3] = { 
	-selection_border, -selection_border, 0.0f,
	-selection_border,  selection_border, 0.0f,
	 selection_border, -selection_border, 0.0f,
	-selection_border,  selection_border, 0.0f,
	 selection_border, -selection_border, 0.0f,
	 selection_border,  selection_border, 0.0f,
};
static const GLfloat border_color[3] = {1.0f, 1.0f, 0.0f};

IGameState::IGameState(CardsDeck* deck,int round)
: cards(deck), round_num(round) {}

void IGameState::GenerateBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const {
	auto deck = cards->GetDeck();
	for(auto it=deck.begin() ; it < deck.end() ; it++) {
		Card* card = *it;
		if(card == NULL) continue;
		
		*vertex_buffer = copy(card->Coords,card->Coords + card->CoordsSize,*vertex_buffer);
		
		//GLfloat* color_array = (card->IsFaceUp) ? card->FaceColor : card->BackColor;
		GLfloat* color_array = card->BackColor;

		for(int i=0 ; i < card->VerticesNum ; i++) {
			*color_buffer = copy(color_array,color_array + card->CardColorSize,*color_buffer);
		}
	}
}

int IGameState::GetRoundNum() const {
	return round_num;
}

void IGameState::ReportRoundNumber() const {
	ostringstream ss; ss << "round:" << GetRoundNum();
	printText2D(ss.str().c_str(), 20, 20, 50);
}

ILastingState::ILastingState(CardsDeck* deck,int round,double state_duration)
: IGameState(deck,round), duration(state_duration), time_elapsed(0.0), wait_for_enter(duration <= 0.001) {}

IGameState* ILastingState::HandleFrame(double delta) {
	if(!wait_for_enter && time_elapsed >= duration)
		return NextStateTransition();
	else {
		time_elapsed += delta;
		return NULL;
	}
}

IGameState* ILastingState::HandleKeyAction(int key,int action) {
	if(key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		return HandleKeyEnter();
	else
		return NULL;
}

IGameState* ILastingState::HandleKeyEnter() {
	return NextStateTransition();
}

ISelectableState::ISelectableState(CardsDeck* deck,int round)
: IGameState(deck,round), is_selected(false), selected_i(0), selected_j(0) {}

ISelectableState::ISelectableState(CardsDeck* deck,int round,int sel_i,int sel_j)
: IGameState(deck,round), is_selected(false), selected_i(sel_i), selected_j(sel_j) {
	if(!trySelect(sel_i,sel_j))
		cerr << "Cannot select ("  << sel_i << "," << sel_j << ")\n";
}

void ISelectableState::GenerateBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const {
	GenerateSelectionBufferData(vertex_buffer,color_buffer);
	IGameState::GenerateBufferData(vertex_buffer,color_buffer);
}

void ISelectableState::GenerateSelectionBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const {
	if(is_selected && cards->at(selected_i,selected_j) != NULL) {
		Card* c = cards->at(selected_i,selected_j);
		GLfloat* vbit = *vertex_buffer;
		GLfloat* cbit = *color_buffer;

		assert(c->CoordsSize == vs_per_card*3);
		for(int i=0 ; i < c->CoordsSize ; i++) {
			*vbit = c->Coords[i] + border_offset[i];
			vbit++;
		}
		for (int i = 0; i < c->VerticesNum; i++)
			cbit = copy(border_color,border_color+3,cbit);

		*vertex_buffer = vbit;
		*color_buffer = cbit;
	}
}

IGameState* ISelectableState::HandleFrame(double /*delta*/) {
	ReportRoundNumber();
	return NULL;
}

IGameState* ISelectableState::HandleKeyAction(int key,int action) {
	if(action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_UP:
				return HandleKeyUp();
				break;
			case GLFW_KEY_DOWN:
				return HandleKeyDown();
				break;
			case GLFW_KEY_LEFT:
				return HandleKeyLeft();
				break;
			case GLFW_KEY_RIGHT:
				return HandleKeyRight();
				break;
			case GLFW_KEY_ENTER:
				return HandleKeyEnter();
				break;
			default:
				return NULL;
		}
	} else
		return NULL;
}

IGameState* ISelectableState::HandleKeyUp() {
	trySelect(selected_i-1,selected_j);
	return NULL;
}

IGameState* ISelectableState::HandleKeyDown() {
	trySelect(selected_i+1,selected_j);
	return NULL;
}

IGameState* ISelectableState::HandleKeyRight() {
	trySelect(selected_i,selected_j+1);
	return NULL;
}

IGameState* ISelectableState::HandleKeyLeft() {
	trySelect(selected_i,selected_j-1);
	return NULL;
}

bool ISelectableState::trySelect(int i,int j) {
	if(i >= 0 && i < cards->GetHeight() && j >= 0 && j < cards->GetWidth()) {
		selected_i = i;
		selected_j = j;
		is_selected = true;

		return true;
	} else
		return false;
}

InitialState::InitialState(CardsDeck* deck,int round,double duration)
: ILastingState(deck,round,duration) {}

IGameState* InitialState::HandleFrame(double delta) {
	ostringstream ss; ss << "Let's play!\n" << "press ENTER";
	printText2D(ss.str().c_str(), 45, 275, 65);
	return ILastingState::HandleFrame(delta);
}

IGameState* InitialState::NextStateTransition() {
	return new IdleState(cards,0,0,0);
}

IdleState::IdleState(CardsDeck* deck,int round)
: ISelectableState(deck,round) {}

IdleState::IdleState(CardsDeck* deck,int round,int sel_i,int sel_j)
: ISelectableState(deck,round,sel_i,sel_j) {}

IGameState* IdleState::HandleKeyEnter() {
	if(is_selected && cards->at(selected_i,selected_j) != NULL)
		return new UncoveredCardState(cards,round_num,selected_i,selected_j);		
	else
		return NULL;
}

UncoveredCardState::UncoveredCardState(CardsDeck* deck,int round,int unc_i,int unc_j,int sel_i,int sel_j)
: ISelectableState(deck,round,sel_i,sel_j), uncovered_i(unc_i), uncovered_j(unc_j) {}

UncoveredCardState::UncoveredCardState(CardsDeck* deck,int round,int unc_i,int unc_j)
: ISelectableState(deck,round,unc_i,unc_j), uncovered_i(unc_i), uncovered_j(unc_j) {}

void UncoveredCardState::GenerateBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const {
	GenerateSelectionBufferData(vertex_buffer,color_buffer);

	auto deck = cards->GetDeck();
	for(auto it=deck.begin() ; it < deck.end() ; it++) {
		Card* card = *it;
		if(card == NULL) continue;
		
		*vertex_buffer = copy(card->Coords,card->Coords + card->CoordsSize,*vertex_buffer);
		
		GLfloat* color_array = ( card == cards->at(uncovered_i,uncovered_j) ) ? card->FaceColor : card->BackColor;
		
		for(int i=0 ; i < card->VerticesNum ; i++) {
			*color_buffer = copy(color_array,color_array + card->CardColorSize,*color_buffer);
		}
	}
}

IGameState* UncoveredCardState::HandleKeyEnter() {
	if(is_selected && cards->at(selected_i,selected_j) != NULL) {
		if(selected_i == uncovered_i && selected_j == uncovered_j)
			return new IdleState(cards,round_num+1,selected_i,selected_j);
		else
			return new UncoveredPairState(cards,round_num,uncovered_i,uncovered_j,selected_i,selected_j);
	} else
		return NULL;
}

UncoveredPairState::UncoveredPairState(CardsDeck* deck,int round,int unc1_i,int unc1_j,int unc2_i,int unc2_j)
: ILastingState(deck,round,uncovered_pair_duration), uncovered1_i(unc1_i), uncovered1_j(unc1_j), uncovered2_i(unc2_i), uncovered2_j(unc2_j) {}

void UncoveredPairState::GenerateBufferData(GLfloat** vertex_buffer,GLfloat** color_buffer) const {
	auto deck = cards->GetDeck();
	for(auto it=deck.begin() ; it < deck.end() ; it++) {
		Card* card = *it;
		if(card == NULL) continue;
		
		*vertex_buffer = copy(card->Coords,card->Coords + card->CoordsSize,*vertex_buffer);
		
		GLfloat* color_array = ( card == cards->at(uncovered1_i,uncovered1_j) || card == cards->at(uncovered2_i,uncovered2_j) ) ? card->FaceColor : card->BackColor;
		
		for(int i=0 ; i < card->VerticesNum ; i++) {
			*color_buffer = copy(color_array,color_array + card->CardColorSize,*color_buffer);
		}
	}
}

IGameState* UncoveredPairState::HandleFrame(double delta) {
	ReportRoundNumber();
	return ILastingState::HandleFrame(delta);
}

IGameState* UncoveredPairState::NextStateTransition() {
	if(cards->at(uncovered1_i,uncovered1_j) != NULL && cards->at(uncovered2_i,uncovered2_j) != NULL)
		if(cards->at(uncovered1_i,uncovered1_j)->GetId() == cards->at(uncovered2_i,uncovered2_j)->GetId()) {
			cards->RemoveCard(uncovered1_i,uncovered1_j);
			cards->RemoveCard(uncovered2_i,uncovered2_j);
		}

	if(cards->GetCardsLeftNum() > 0)
		return new IdleState(cards,round_num+1,uncovered2_i,uncovered2_j);
	else
		return new GameWonState(cards,round_num+1);
}

GameWonState::GameWonState(CardsDeck* deck,int round,double duration)
: ILastingState(deck,round,duration) {}

void GameWonState::GenerateBufferData(GLfloat** /*vertex_buffer*/,GLfloat** /*color_buffer*/) const
{}

IGameState* GameWonState::HandleFrame(double delta) {
	ReportRoundNumber();
	ostringstream ss; ss << "You've won!\n" << "press ENTER";
	printText2D(ss.str().c_str(), 45, 275, 65);
	return ILastingState::HandleFrame(delta);
}

IGameState* GameWonState::NextStateTransition() {
	return new TerminatingState(cards,round_num);
}

TerminatingState::TerminatingState(CardsDeck* deck,int round)
: IGameState(deck,round) {}


IGameState* TerminatingState::HandleFrame(double /*delta*/) {
	 glfwSetWindowShouldClose(window, GL_TRUE);
	 return NULL;
}


IGameState* TerminatingState::HandleKeyAction(int /*key*/,int /*action*/) {
	return NULL;
}