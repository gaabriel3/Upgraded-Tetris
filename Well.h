#ifndef WELL_INCLUDED
#define WELL_INCLUDED

#include "Piece.h"

class Screen;

class Well
{
  public:
	  Well(); // default constructor
	  Well(int width, int height); // setup width and height
	  ~Well(); // destructor

    void display(Screen& screen, int x, int y);
	void initiateGrid();
	char getWellChar(int x, int y);
	void setWellChar(int x, int y, char change);
	bool fullWellRow(int row);
	void emptyWellRow(int row);

	// I PIECE
	void addPIECEI(Pieces* i_piece);
	void dropPIECEI(Pieces* i_piece);
	void moveRightPIECEI(Pieces* i_piece);
	void moveLeftPIECEI(Pieces* i_piece);
	void rotatePIECEI(Pieces* i_piece);

	bool validMoveDownI(Pieces* i_piece);
	bool validMoveRightI(Pieces* i_piece);
	bool validMoveLeftI(Pieces* i_piece);
	bool validRotateI(Pieces* i_piece);
	bool validAddI(Pieces* i_piece);

	void finishPieceI(Pieces* i_piece);

	// L PIECE
	void addPIECEL(Pieces* l_piece);
	void dropPIECEL(Pieces* l_piece);
	void moveRightPIECEL(Pieces* l_piece);
	void moveLeftPIECEL(Pieces* l_piece);
	void rotatePIECEL(Pieces* l_piece);

	bool validMoveDownL(Pieces* l_piece);
	bool validMoveRightL(Pieces* l_piece);
	bool validMoveLeftL(Pieces* l_piece);
	bool validRotateL(Pieces* l_piece);
	bool validAddL(Pieces* l_piece);

	void finishPieceL(Pieces* l_piece);


	// O PIECE
	void addPIECEO(Pieces* o_piece);
	void dropPIECEO(Pieces* o_piece);
	void moveRightPIECEO(Pieces* o_piece);
	void moveLeftPIECEO(Pieces* o_piece);
	void rotatePIECEO(Pieces* o_piece);

	bool validMoveDownO(Pieces* o_piece);
	bool validMoveRightO(Pieces* o_piece);
	bool validMoveLeftO(Pieces* o_piece);
	bool validRotateO(Pieces* o_piece);
	bool validAddO(Pieces* o_piece);

	void finishPieceO(Pieces* o_piece);

	// J PIECE
	void addPIECEJ(Pieces* j_piece);
	void dropPIECEJ(Pieces* j_piece);
	void moveRightPIECEJ(Pieces* j_piece);
	void moveLeftPIECEJ(Pieces* j_piece);
	void rotatePIECEJ(Pieces* j_piece);

	bool validMoveDownJ(Pieces* j_piece);
	bool validMoveRightJ(Pieces* j_piece);
	bool validMoveLeftJ(Pieces* j_piece);
	bool validRotateJ(Pieces* j_piece);
	bool validAddJ(Pieces* j_piece);

	void finishPieceJ(Pieces* j_piece);

	// T PIECE
	void addPIECET(Pieces* t_piece);
	void dropPIECET(Pieces* t_piece);
	void moveRightPIECET(Pieces* t_piece);
	void moveLeftPIECET(Pieces* t_piece);
	void rotatePIECET(Pieces* t_piece);

	bool validMoveDownT(Pieces* t_piece);
	bool validMoveRightT(Pieces* t_piece);
	bool validMoveLeftT(Pieces* t_piece);
	bool validRotateT(Pieces* t_piece);
	bool validAddT(Pieces* t_piece);

	void finishPieceT(Pieces* t_piece);

	// S PIECE
	void addPIECES(Pieces* s_piece);
	void dropPIECES(Pieces* s_piece);
	void moveRightPIECES(Pieces* s_piece);
	void moveLeftPIECES(Pieces* s_piece);
	void rotatePIECES(Pieces* s_piece);

	bool validMoveDownS(Pieces* s_piece);
	bool validMoveRightS(Pieces* s_piece);
	bool validMoveLeftS(Pieces* s_piece);
	bool validRotateS(Pieces* s_piece);
	bool validAddS(Pieces* s_piece);

	void finishPieceS(Pieces* s_piece);

	// Z PIECE
	void addPIECEZ(Pieces* z_piece);
	void dropPIECEZ(Pieces* z_piece);
	void moveRightPIECEZ(Pieces* z_piece);
	void moveLeftPIECEZ(Pieces* z_piece);
	void rotatePIECEZ(Pieces* z_piece);

	bool validMoveDownZ(Pieces* z_piece);
	bool validMoveRightZ(Pieces* z_piece);
	bool validMoveLeftZ(Pieces* z_piece);
	bool validRotateZ(Pieces* z_piece);
	bool validAddZ(Pieces* z_piece);

	void finishPieceZ(Pieces* z_piece);

	// CRAZY PIECE
	void addPIECEC(Pieces* c_piece);
	void dropPIECEC(Pieces* c_piece);
	void moveRightPIECEC(Pieces* c_piece);
	void moveLeftPIECEC(Pieces* c_piece);
	void rotatePIECEC(Pieces* c_piece);

	bool validMoveDownC(Pieces* c_piece);
	bool validMoveRightC(Pieces* c_piece);
	bool validMoveLeftC(Pieces* c_piece);
	bool validRotateC(Pieces* c_piece);
	bool validAddC(Pieces* c_piece);

	void finishPieceC(Pieces* c_piece);

	// VAPOR BOMB
	void addPIECEV(Pieces* v_piece);
	void dropPIECEV(Pieces* v_piece);
	void moveRightPIECEV(Pieces* v_piece);
	void moveLeftPIECEV(Pieces* v_piece);
	void rotatePIECEV(Pieces* v_piece);

	bool validMoveDownV(Pieces* v_piece);
	bool validMoveRightV(Pieces* v_piece);
	bool validMoveLeftV(Pieces* v_piece);
	bool validRotateV(Pieces* v_piece);
	bool validAddV(Pieces* v_piece);

	void finishPieceV(Pieces* v_piece);

	// FOAM BOMB
	void addPIECEF(Pieces* f_piece);
	void dropPIECEF(Pieces* f_piece);
	void moveRightPIECEF(Pieces* f_piece);
	void moveLeftPIECEF(Pieces* f_piece);
	void rotatePIECEF(Pieces* f_piece);

	bool validMoveDownF(Pieces* f_piece);
	bool validMoveRightF(Pieces* f_piece);
	bool validMoveLeftF(Pieces* f_piece);
	bool validRotateF(Pieces* f_piece);
	bool validAddF(Pieces* f_piece);

	void finishPieceF(Pieces* f_piece, int foamX, int foamY, int upLimit, int downLimit, int leftLimit, int rightLimit);

private:
	int WofWELL; // width of well // 10 [1, 10]
	int HofWELL; // height of well // 18 [0, 17]

	char m_wellGrid[12][19]; // 12 is WofWELL+2, 19 is HofWELL+1

	Pieces *i_piece = new PIECEI();
	Pieces *l_piece = new PIECEL();
	Pieces *o_piece = new PIECEO();
	Pieces *j_piece = new PIECEJ();
	Pieces *t_piece = new PIECET();
	Pieces *s_piece = new SPIECE();
	Pieces *z_piece = new PIECEZ();
	Pieces* c_piece = new PIECECRAZY();
	Pieces* v_piece = new PIECEVAPOR();
	Pieces* f_piece = new PIECEFOAM();
};

#endif // WELL_INCLUDED
