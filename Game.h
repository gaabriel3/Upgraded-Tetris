#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include <string>
#include "Piece.h"
#include <list>
#include <algorithm>

class Game
{
  public:
    Game(int width, int height);
	~Game();
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
	void displayNextPiece();
	
	void playPieceI(Pieces* i_piece);
	void playPieceL(Pieces* l_piece);
	void playPieceO(Pieces* o_piece);
	void playPieceJ(Pieces* j_piece);
	void playPieceT(Pieces* t_piece);
	void playPieceS(Pieces* s_piece);
	void playPieceZ(Pieces* z_piece);
	void playPieceC(Pieces* c_piece);
	void playPieceV(Pieces* v_piece);
	void playPieceF(Pieces* f_piece);

  private:
    Well    m_well;
    Screen  m_screen;
	int     m_level = 1;

	Pieces* i_piece = new PIECEI();
	Pieces* l_piece = new PIECEL();
	Pieces* o_piece = new PIECEO();
	Pieces* j_piece = new PIECEJ();
	Pieces* t_piece = new PIECET();
	Pieces* s_piece = new SPIECE();
	Pieces* z_piece = new PIECEZ();
	Pieces* c_piece = new PIECECRAZY();
	Pieces* v_piece = new PIECEVAPOR();
	Pieces* f_piece = new PIECEFOAM();

	bool notAtBottom = true;
	bool bypassTimer = false;
	bool trueBottom = false;

	int		rowsDeleted = 0;
	bool	quit = false;
	int		totalScore = 0;

	std::list<PieceType> pieceQueue;
};

#endif // GAME_INCLUDED
