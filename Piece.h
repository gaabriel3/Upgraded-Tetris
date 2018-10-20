#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

enum PieceType {
	PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
	PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

PieceType chooseRandomPieceType();

class Pieces {
public:
	Pieces(); // Constructor
	virtual ~Pieces(); // Destructor
	void empty4x4(); // Clear the 4x4 grid.
	void changeChar(int h, int w, char change); // Modifier
	char getChar(int h, int w) const; // Accessor
	int getOrientation() const; // Accessor for Orientation
	void setOrientation(int newOrientation); // Modifier for Orientation
	int getX() const; // Accessor for X
	int getY() const; // Accessor for Y
	void setX(int newX); // Modifier for X
	void setY(int newY);	// Modifier for Y
	virtual void orientation0() = 0;
	virtual void orientation1() = 0;
	virtual void orientation2() = 0;
	virtual void orientation3() = 0;
private:
	char   m_grid[4][4];
	int	   m_orientation = 0;
	int	   m_x = 0; // X-coord in well
	int    m_y = 0; // Y-coord in well
};

class PIECEI : public Pieces {
public:
	PIECEI();
	virtual ~PIECEI();
	virtual void orientation0();
	virtual void orientation1();
	virtual void orientation2();
	virtual void orientation3();
private:
	// inherited grid
};

class PIECEL : public Pieces {
public:
	PIECEL();
	virtual ~PIECEL();
	virtual void orientation0();
	virtual void orientation1();
	virtual void orientation2();
	virtual void orientation3();
private:
	// inherited grid
};

class PIECEO : public Pieces {
public:
	PIECEO();
	virtual ~PIECEO();
	virtual void orientation0();
	virtual void orientation1();
	virtual void orientation2();
	virtual void orientation3();
private:
	// inherited grid
};

class PIECEJ : public Pieces {
public:
	PIECEJ();
	virtual ~PIECEJ();
	virtual void orientation0();
	virtual void orientation1();
	virtual void orientation2();
	virtual void orientation3();
private:
	// inherited grid
};

class PIECET : public Pieces {
public:
	PIECET();
	virtual ~PIECET();
	virtual void orientation0();
	virtual void orientation1();
	virtual void orientation2();
	virtual void orientation3();
private:
	// inherited grid
};

class SPIECE : public Pieces {
public:
	SPIECE();
	virtual ~SPIECE();
	virtual void orientation0();
	virtual void orientation1();
	virtual void orientation2();
	virtual void orientation3();
private:
	// inherited grid
};

class PIECEZ : public Pieces {
public:
	PIECEZ();
	virtual ~PIECEZ();
	virtual void orientation0();
	virtual void orientation1();
	virtual void orientation2();
	virtual void orientation3();
private:
	// inherited grid
};

class PIECECRAZY : public Pieces {

public:
	PIECECRAZY();
	virtual ~PIECECRAZY();
	virtual void orientation0();
	virtual void orientation1();
	virtual void orientation2();
	virtual void orientation3();
private:
	// inherited grid
};

class PIECEVAPOR : public Pieces {
public:
	PIECEVAPOR();
	virtual ~PIECEVAPOR();
	virtual void orientation0();
	virtual void orientation1();
	virtual void orientation2();
	virtual void orientation3();
private:
	// inherited grid
};

class PIECEFOAM : public Pieces {
public:
	PIECEFOAM();
	virtual ~PIECEFOAM();
	virtual void orientation0();
	virtual void orientation1();
	virtual void orientation2();
	virtual void orientation3();
private:
	// inherited grid
};

#endif // PIECE_INCLUDED
