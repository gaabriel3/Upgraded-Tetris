#include "Piece.h"
#include "Game.h"

// BASE CLASS
// BASE CLASS
// BASE CLASS

Pieces::Pieces() {
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			m_grid[x][y] = ' ';
		}
	}
}

Pieces::~Pieces() {}

void Pieces::empty4x4() { // Fills the array with blanks (spaces)
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			m_grid[x][y] = ' ';
		}
	}
}

void Pieces::changeChar(int h, int w, char change) { // Function to change element x, y of the 2D array
	m_grid[h][w] = change;
}

char Pieces::getChar(int h, int w) const { // Returns the char at point x, y in m_grid
	return m_grid[h][w];
}

int Pieces::getOrientation() const {
	return m_orientation;
}

void Pieces::setOrientation(int newOrientation) {
	m_orientation = newOrientation;
}

int Pieces::getX() const { // Accessor for X
	return m_x;
}

int Pieces::getY() const { // Accessor for Y
	return m_y;
}

void Pieces::setX(int newX) { // Modifier for X
	m_x = newX;
}

void Pieces::setY(int newY) { // Modifier for Y
	m_y = newY;
}

// PIECE I
// PIECE I
// PIECE I

PIECEI::PIECEI() {
	empty4x4();
	for (int x = 0; x <= 3; x++) {
		changeChar(x, 1, '#');
	}
	setOrientation(0);
}

PIECEI::~PIECEI() {}

void PIECEI::orientation0() { // Orientation #0 of "The I Piece"
	empty4x4();
	for (int x = 0; x <= 3; x++) {
		changeChar(x, 1, '#');
	}
	setOrientation(0);
}

void PIECEI::orientation1() { // Orientation #1 of "The I Piece"
	empty4x4();
	for (int x = 0; x <= 3; x++) {
		changeChar(1, x, '#');
	}
	setOrientation(1);
}

void PIECEI::orientation2() { // Orientation #2 of "The I Piece"
	empty4x4();
	for (int x = 0; x <= 3; x++) {
		changeChar(x, 1, '#');
	}
	setOrientation(2);
}

void PIECEI::orientation3() { // Orientation #3 of "The I Piece"
	empty4x4();
	for (int x = 0; x <= 3; x++) {
		changeChar(1, x, '#');
	}
	setOrientation(3);
}

// PIECE L
// PIECE L
// PIECE L

PIECEL::PIECEL() {
	empty4x4();
	for (int x = 0; x < 3; x++) {
		changeChar(x, 1, '#');
	}
	changeChar(0, 2, '#');
	setOrientation(0);
}

PIECEL::~PIECEL() {}

void PIECEL::orientation0() { // Orientation #0 of "The L Piece"
	empty4x4();
	for (int x = 0; x < 3; x++) {
		changeChar(x, 1, '#');
	}
	changeChar(0, 2, '#');
	setOrientation(0);
}

void PIECEL::orientation1() { // Orientation #1 of "The L Piece"
	empty4x4();
	for (int y = 0; y < 3; y++) {
		changeChar(2, y, '#');
	}
	changeChar(1, 0, '#');
	setOrientation(1);
}

void PIECEL::orientation2() { // Orientation #2 of "The L Piece"
	empty4x4();
	for (int x = 0; x < 3; x++) {
		changeChar(x, 2, '#');
	}
	changeChar(2, 1, '#');
	setOrientation(2);
}

void PIECEL::orientation3() { // Orientation #3 of "The L Piece"
	empty4x4();
	for (int y = 1; y < 4; y++) {
		changeChar(1, y, '#');
	}
	changeChar(2, 3, '#');
	setOrientation(3);
}

// PIECE O
// PIECE O
// PIECE O

PIECEO::PIECEO() {
	empty4x4();
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			changeChar(x, y, '#');
		}
	}
	setOrientation(0);
}

PIECEO::~PIECEO() {}

void PIECEO::orientation0() {
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			changeChar(x, y, '#');
		}
	}
	setOrientation(0);
}

void PIECEO::orientation1() {
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			changeChar(x, y, '#');
		}
	}
	setOrientation(1);
}

void PIECEO::orientation2() {
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			changeChar(x, y, '#');
		}
	}
	setOrientation(2);
}

void PIECEO::orientation3() {
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			changeChar(x, y, '#');
		}
	}
	setOrientation(3);
}

// PIECE J

PIECEJ::PIECEJ() {
	empty4x4();
	for (int x = 1; x < 4; x++) {
		changeChar(x, 1, '#');
	}
	changeChar(3, 2, '#');
	setOrientation(0);
}

PIECEJ::~PIECEJ() {}

void PIECEJ::orientation0() {
	empty4x4();
	for (int x = 1; x < 4; x++) {
		changeChar(x, 1, '#');
	}
	changeChar(3, 2, '#');
	setOrientation(0);
}

void PIECEJ::orientation1() {
	empty4x4();
	for (int y = 1; y < 4; y++) {
		changeChar(2, y, '#');
	}
	changeChar(1, 3, '#');
	setOrientation(1);
}

void PIECEJ::orientation2() {
	empty4x4();
	for (int x = 1; x < 4; x++) {
		changeChar(x, 2, '#');
	}
	changeChar(1, 1, '#');
	setOrientation(2);
}

void PIECEJ::orientation3() {
	empty4x4();
	for (int y = 0; y < 3; y++) {
		changeChar(1, y, '#');
	}
	changeChar(2, 0, '#');
	setOrientation(3);
}

// PIECE T

PIECET::PIECET() {
	empty4x4();
	for (int x = 0; x < 3; x++) {
		changeChar(x, 1, '#');
	}
	changeChar(1, 0, '#');
	setOrientation(0);
}

PIECET::~PIECET() {}

void PIECET::orientation0() {
	empty4x4();
	for (int x = 0; x < 3; x++) {
		changeChar(x, 1, '#');
	}
	changeChar(1, 0, '#');
	setOrientation(0);
}

void PIECET::orientation1() {
	empty4x4();
	for (int y = 0; y < 3; y++) {
		changeChar(1, y, '#');
	}
	changeChar(2, 1, '#');
	setOrientation(1);
}

void PIECET::orientation2() {
	empty4x4();
	for (int x = 0; x < 3; x++) {
		changeChar(x, 1, '#');
	}
	changeChar(1, 2, '#');
	setOrientation(2);
}

void PIECET::orientation3() {
	empty4x4();
	for (int y = 0; y < 3; y++) {
		changeChar(1, y, '#');
	}
	changeChar(0, 1, '#');
	setOrientation(3);
}

// S PIECE

SPIECE::SPIECE() {
	empty4x4();
	for (int x = 0; x < 2; x++) {
		changeChar(x, 2, '#');
	}
	for (int x = 1; x < 3; x++) {
		changeChar(x, 1, '#');
	}
	setOrientation(0);
}

SPIECE::~SPIECE() {}

void SPIECE::orientation0() {
	empty4x4();
	for (int x = 0; x < 2; x++) {
		changeChar(x, 2, '#');
	}
	for (int x = 1; x < 3; x++) {
		changeChar(x, 1, '#');
	}
	setOrientation(0);
}

void SPIECE::orientation1() {
	empty4x4();
	for (int y = 0; y < 2; y++) {
		changeChar(1, y, '#');
	}
	for (int y = 1; y < 3; y++) {
		changeChar(2, y, '#');
	}
	setOrientation(1);
}

void SPIECE::orientation2() {
	empty4x4();
	for (int x = 0; x < 2; x++) {
		changeChar(x, 2, '#');
	}
	for (int x = 1; x < 3; x++) {
		changeChar(x, 1, '#');
	}
	setOrientation(2);
}

void SPIECE::orientation3() {
	empty4x4();
	for (int y = 0; y < 2; y++) {
		changeChar(1, y, '#');
	}
	for (int y = 1; y < 3; y++) {
		changeChar(2, y, '#');
	}
	setOrientation(3);
}

// Z PIECE

PIECEZ::PIECEZ() {
	empty4x4();
	for (int x = 0; x < 2; x++) {
		changeChar(x, 1, '#');
	}
	for (int x = 1; x < 3; x++) {
		changeChar(x, 2, '#');
	}
	setOrientation(0);
}

PIECEZ::~PIECEZ() {}

void PIECEZ::orientation0() {
	empty4x4();
	for (int x = 0; x < 2; x++) {
		changeChar(x, 1, '#');
	}
	for (int x = 1; x < 3; x++) {
		changeChar(x, 2, '#');
	}
	setOrientation(0);
}

void PIECEZ::orientation1() {
	empty4x4();
	for (int y = 1; y < 3; y++) {
		changeChar(1, y, '#');
	}
	for (int y = 0; y < 2; y++) {
		changeChar(2, y, '#');
	}
	setOrientation(1);
}

void PIECEZ::orientation2() {
	empty4x4();
	for (int x = 0; x < 2; x++) {
		changeChar(x, 1, '#');
	}
	for (int x = 1; x < 3; x++) {
		changeChar(x, 2, '#');
	}
	setOrientation(2);
}

void PIECEZ::orientation3() {
	empty4x4();
	for (int y = 1; y < 3; y++) {
		changeChar(1, y, '#');
	}
	for (int y = 0; y < 2; y++) {
		changeChar(2, y, '#');
	}
	setOrientation(3);
}

// CRAZY PIECE

PIECECRAZY::PIECECRAZY() {
	empty4x4();
	changeChar(0, 0, '#');
	changeChar(3, 0, '#');
	changeChar(1, 1, '#');
	changeChar(2, 1, '#');
	setOrientation(0);
}

PIECECRAZY::~PIECECRAZY() {}

void PIECECRAZY::orientation0() {
	empty4x4();
	changeChar(0, 0, '#');
	changeChar(3, 0, '#');
	changeChar(1, 1, '#');
	changeChar(2, 1, '#');
	setOrientation(0);
}

void PIECECRAZY::orientation1() {
	empty4x4();
	changeChar(3, 0, '#');
	changeChar(2, 1, '#');
	changeChar(2, 2, '#');
	changeChar(3, 3, '#');
	setOrientation(1);
}

void PIECECRAZY::orientation2() {
	empty4x4();
	changeChar(0, 3, '#');
	changeChar(1, 2, '#');
	changeChar(2, 2, '#');
	changeChar(3, 3, '#');
	setOrientation(2);
}

void PIECECRAZY::orientation3() {
	empty4x4();
	changeChar(0, 0, '#');
	changeChar(1, 1, '#');
	changeChar(1, 2, '#');
	changeChar(0, 3, '#');
	setOrientation(3);
}

// VAPOR BOMB

PIECEVAPOR::PIECEVAPOR() {
	empty4x4();
	changeChar(1, 0, '#');
	changeChar(2, 0, '#');
	setOrientation(0);
}

PIECEVAPOR::~PIECEVAPOR() {}

void PIECEVAPOR::orientation0() {
	empty4x4();
	changeChar(1, 0, '#');
	changeChar(2, 0, '#');
	setOrientation(0);
}

void PIECEVAPOR::orientation1() {
	setOrientation(1);
}

void PIECEVAPOR::orientation2() {
	setOrientation(2);
}

void PIECEVAPOR::orientation3() {
	setOrientation(3);
}

// FOAM BOMB

PIECEFOAM::PIECEFOAM() {
	empty4x4();
	changeChar(1, 1, '#');
	setOrientation(0);
}

PIECEFOAM::~PIECEFOAM() {}

void PIECEFOAM::orientation0() {
	empty4x4();
	changeChar(1, 1, '#');
	setOrientation(0);
}

void PIECEFOAM::orientation1() {
	setOrientation(1);
}

void PIECEFOAM::orientation2() {
	setOrientation(2);
}

void PIECEFOAM::orientation3() {
	setOrientation(3);
}