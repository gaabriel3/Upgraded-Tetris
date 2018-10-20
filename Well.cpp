#include <iostream>
#include "Well.h"
#include "UserInterface.h"

Well::Well()
{}

Well::~Well() {
	delete i_piece;
	delete l_piece;
	delete o_piece;
	delete j_piece;
	delete t_piece;
	delete s_piece;
	delete z_piece;
	delete c_piece;
	delete v_piece;
	delete f_piece;
}

Well::Well(int width, int height) 
	:WofWELL(width), HofWELL(height) 
{
	for (int x = 0; x <= WofWELL+1; x++)
		for (int y = 0; y <= HofWELL; y++)
			m_wellGrid[x][y] = ' ';
}

void Well::initiateGrid() {
	// Well coordinates in orientation: COLUMN, ROW
	for (int i = 0; i <= HofWELL; i++) { // Prints first column of the well ( 0, 0 to 0, 18)
		m_wellGrid[0][i] = '@';
	}

	for (int i = 0; i <= HofWELL; i++) { // Prints end column of the well ( 11, 0 to 11, 18 )
		m_wellGrid[WofWELL + 1][i] = '@';
	}

	for (int i = 0; i <= WofWELL; i++) { // Prints the bottom layer of the well ( 1,18 to 10,18 )
		m_wellGrid[i][HofWELL] = '@';
	}

	for (int i = 1; i <= WofWELL; i++) {
		for (int y = 0; y < HofWELL; y++) {
			m_wellGrid[i][y] = ' ';
		}
	}
}

void Well::display(Screen& screen, int x, int y) // x and y are by default 0
{
	for (int x = 0; x <= WofWELL+1; x++) {
		for (int y = 0; y <= HofWELL; y++) {
			screen.gotoXY(x, y);
			screen.printChar(getWellChar(x, y));
			screen.refresh();
		}
	}
}

char Well::getWellChar(int x, int y) {
	return m_wellGrid[x][y];
}

void Well::setWellChar(int x, int y, char change) {
	m_wellGrid[x][y] = change;
}

bool Well::fullWellRow(int row) {
	for (int x = 1; x <= WofWELL; x++) {
		if (getWellChar(x, row) == ' ')
			return false;
	}
	return true;
}

void Well::emptyWellRow(int row) {
	int r = row;
	while (r > 0) {
		for (int x = 1; x <= WofWELL; x++) {
			setWellChar(x, r, getWellChar(x, r - 1));
		}
		r--;
	}
}

// PIECE I WELL FUNCTIONS

void Well::addPIECEI(Pieces* i_piece) { // Initial Position in Well
	i_piece->setOrientation(0);
	i_piece->orientation0();

	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = i_piece->getChar(x - 4, y); // The character that is going to be put into the well.
			if (changer == '#')
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
		}
	}
	// Well Coords go X = 12, Y = 19
	i_piece->setX(4); // Upper left of bounding box
	i_piece->setY(0); // Upper left of bounding box
}

bool Well::validAddI(Pieces* i_piece) {
	i_piece->orientation0();
	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			if ((i_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '$') || (i_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '*'))
				return false;
		}
	}
	return true;
}

void Well::dropPIECEI(Pieces* i_piece) {
	for (int x = i_piece->getX(); x < 12, x < i_piece->getX() + 4; x++) {
		for (int y = i_piece->getY(); y < 19, y < i_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = i_piece->getX();
	int currentY = i_piece->getY() + 1;

	for (int x = currentX; x < currentX+4; x++) {
		for (int y = currentY; y < currentY+4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = i_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	i_piece->setX(currentX); // Upper left of bounding box
	i_piece->setY(currentY); // Upper left of bounding box ... Only y-coord of bounding box has been changed.
}

void Well::moveRightPIECEI(Pieces* i_piece) {
	for (int x = i_piece->getX(); x < 12, x < i_piece->getX() + 4; x++) {
		for (int y = i_piece->getY(); y < 19, y < i_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = i_piece->getX()+1;
	int currentY = i_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = i_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	i_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	i_piece->setY(currentY); // Upper left of bounding box
}

void Well::moveLeftPIECEI(Pieces* i_piece) {
	for (int x = i_piece->getX(); x < 12, x < i_piece->getX() + 4; x++) {
		for (int y = i_piece->getY(); y < 19, y < i_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = i_piece->getX() - 1;
	int currentY = i_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = i_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	i_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	i_piece->setY(currentY); // Upper left of bounding box
}

void Well::rotatePIECEI(Pieces* i_piece) {
	for (int x = i_piece->getX(); x < 12, x < i_piece->getX() + 4; x++) {
		for (int y = i_piece->getY(); y < 19, y < i_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int decide = i_piece->getOrientation(); // Get current orientation to prepare for clockwise rotation.
	if (decide == 0)
		i_piece->orientation1();
	if (decide == 1)
		i_piece->orientation2();
	if (decide == 2)
		i_piece->orientation3();
	if (decide == 3)
		i_piece->orientation0();

	int currentX = i_piece->getX();
	int currentY = i_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = i_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	i_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	i_piece->setY(currentY); // Upper left of bounding box
}

bool Well::validMoveDownI(Pieces* i_piece) {
	int piece_x = i_piece->getX();
	int piece_y = i_piece->getY();

	if (i_piece->getOrientation() == 0 || i_piece->getOrientation() == 2) {
		for (int x = piece_x; x <= piece_x + 3; x++) {
			if (getWellChar(x, piece_y + 2) == '@' || getWellChar(x, piece_y + 2) == '$' || getWellChar(x, piece_y+2) == '*')
				return false;
		}
	}

	if (i_piece->getOrientation() == 1 || i_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 1, piece_y + 4) == '@' || getWellChar(piece_x + 1, piece_y + 4) == '$' || getWellChar(piece_x + 1, piece_y + 4) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveRightI(Pieces* i_piece) {
	int piece_x = i_piece->getX();
	int piece_y = i_piece->getY();

	if (i_piece->getOrientation() == 0 || i_piece->getOrientation() == 2) {
		if (getWellChar(piece_x+4, piece_y + 1) == '@' || getWellChar(piece_x + 4, piece_y + 1) == '$' || getWellChar(piece_x + 4, piece_y + 1) == '*')
			return false;
	}

	if (i_piece->getOrientation() == 1 || i_piece->getOrientation() == 3) {
		for (int y = piece_y; y < piece_y + 4; y++) {
			if (getWellChar(piece_x + 2, y) == '@' || getWellChar(piece_x + 2, y) == '$' || getWellChar(piece_x + 2, y) == '*')
				return false;
		}
	}
	return true;
}

bool Well::validMoveLeftI(Pieces* i_piece) {
	int piece_x = i_piece->getX();
	int piece_y = i_piece->getY();

	if (i_piece->getOrientation() == 0 || i_piece->getOrientation() == 2) {
		if (getWellChar(piece_x - 1, piece_y + 1) == '@' || getWellChar(piece_x - 1, piece_y + 1) == '$' || getWellChar(piece_x - 1, piece_y + 1) == '*')
			return false;
	}

	if (i_piece->getOrientation() == 1 || i_piece->getOrientation() == 3) {
		for (int y = piece_y; y < piece_y + 4; y++) {
			if (getWellChar(piece_x, y) == '@' || getWellChar(piece_x, y) == '$' || getWellChar(piece_x, y) == '*')
				return false;
		}
	}
	return true;
}

bool Well::validRotateI(Pieces* i_piece) {
	int piece_x = i_piece->getX();
	int piece_y = i_piece->getY();

	if (i_piece->getOrientation() == 0 || i_piece->getOrientation() == 2) {
		if (getWellChar(piece_x + 1, piece_y) == '@' || getWellChar(piece_x + 1, piece_y) == '$' || getWellChar(piece_x + 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
	}

	if (i_piece->getOrientation() == 1 || i_piece->getOrientation() == 3) {
		for (int x = piece_x; x <= piece_x + 3; x++) {
			if (getWellChar(x, piece_y + 1) == '@' || getWellChar(x, piece_y + 1) == '$' || getWellChar(x, piece_y + 1) == '*')
				return false;
		}
	}
	return true;
}

void Well::finishPieceI(Pieces* i_piece) {
	int currentX = i_piece->getX();
	int currentY = i_piece->getY();

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (i_piece->getChar(x, y) == '#') {
				i_piece->changeChar(x, y, '$');
			}
		}
	}

	for (int x = currentX; x < currentX+4 && x < 12; x++) {
		for (int y = currentY; y < currentY + 4 && y < 19; y++) {
			if (getWellChar(x, y) == '#')
				setWellChar(x, y, '$');
		}
	}
}

// PIECE L WELL FUNCTIONS

void Well::addPIECEL(Pieces* l_piece) { // Initial Position in Well
	l_piece->setOrientation(0);
	l_piece->orientation0();

	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = l_piece->getChar(x - 4, y); // The character that is going to be put into the well.
			if (changer == '#')
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
		}
	}
	// Well Coords go X = 12, Y = 19
	l_piece->setX(4); // Upper left of bounding box
	l_piece->setY(0); // Upper left of bounding box
}

bool Well::validAddL(Pieces* l_piece) {
	l_piece->orientation0();
	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			if ((l_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '$') || (l_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '*'))
				return false;
		}
	}
	return true;
}

void Well::dropPIECEL(Pieces* l_piece) {
	for (int x = l_piece->getX(); x < 12, x < l_piece->getX() + 4; x++) {
		for (int y = l_piece->getY(); y < 19, y < l_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = l_piece->getX();
	int currentY = l_piece->getY() + 1;

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = l_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	l_piece->setX(currentX); // Upper left of bounding box
	l_piece->setY(currentY); // Upper left of bounding box ... Only y-coord of bounding box has been changed.
}

void Well::moveRightPIECEL(Pieces* l_piece) {
	for (int x = l_piece->getX(); x < 12, x < l_piece->getX() + 4; x++) {
		for (int y = l_piece->getY(); y < 19, y < l_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = l_piece->getX() + 1;
	int currentY = l_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = l_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	l_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	l_piece->setY(currentY); // Upper left of bounding box
}

void Well::moveLeftPIECEL(Pieces* l_piece) {
	for (int x = l_piece->getX(); x < 12, x < l_piece->getX() + 4; x++) {
		for (int y = l_piece->getY(); y < 19, y < l_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = l_piece->getX() - 1;
	int currentY = l_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = l_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	l_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	l_piece->setY(currentY); // Upper left of bounding box
}

void Well::rotatePIECEL(Pieces* l_piece) {
	for (int x = l_piece->getX(); x < 12, x < l_piece->getX() + 4; x++) {
		for (int y = l_piece->getY(); y < 19, y < l_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int decide = l_piece->getOrientation(); // Get current orientation to prepare for clockwise rotation.
	if (decide == 0)
		l_piece->orientation1();
	if (decide == 1)
		l_piece->orientation2();
	if (decide == 2)
		l_piece->orientation3();
	if (decide == 3)
		l_piece->orientation0();

	int currentX = l_piece->getX();
	int currentY = l_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = l_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	l_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	l_piece->setY(currentY); // Upper left of bounding box
}

bool Well::validMoveDownL(Pieces* l_piece) {
	int piece_x = l_piece->getX();
	int piece_y = l_piece->getY();

	if (l_piece->getOrientation() == 0) {
		if (getWellChar(piece_x, piece_y + 3) == '@' || getWellChar(piece_x, piece_y + 3) == '$' || getWellChar(piece_x, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (l_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 3) == '@' || getWellChar(piece_x + 2, piece_y + 3) == '$' || getWellChar(piece_x + 2, piece_y + 3) == '*')
			return false;
	}

	if (l_piece->getOrientation() == 2) {
		for (int x = piece_x; x < piece_x + 3; x++) {
			if (getWellChar(x, piece_y + 3) == '@' || getWellChar(x, piece_y + 3) == '$' || getWellChar(x, piece_y + 3) == '*')
				return false;
		}
	}

	if (l_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 1, piece_y + 4) == '@' || getWellChar(piece_x + 1, piece_y + 4) == '$' || getWellChar(piece_x + 1, piece_y + 4) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 4) == '@' || getWellChar(piece_x + 2, piece_y + 4) == '$' || getWellChar(piece_x + 2, piece_y + 4) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveRightL(Pieces* l_piece) {
	int piece_x = l_piece->getX();
	int piece_y = l_piece->getY();

	if (l_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
	}

	if (l_piece->getOrientation() == 1) {
		for (int y = piece_y; y <= piece_y + 2; y++) {
			if (getWellChar(piece_x+3, y) == '@' || getWellChar(piece_x + 3, y) == '$' || getWellChar(piece_x + 3, y) == '*')
				return false;
		}
	}

	if (l_piece->getOrientation() == 2) {
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 2) == '@' || getWellChar(piece_x + 3, piece_y + 2) == '$' || getWellChar(piece_x + 3, piece_y + 2) == '*')
			return false;
	}

	if (l_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 3) == '@' || getWellChar(piece_x + 3, piece_y + 3) == '$' || getWellChar(piece_x + 3, piece_y + 3) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveLeftL(Pieces* l_piece) { 
	int piece_x = l_piece->getX();
	int piece_y = l_piece->getY();

	if (l_piece->getOrientation() == 0) {
		if (getWellChar(piece_x - 1, piece_y + 1) == '@' || getWellChar(piece_x - 1, piece_y + 1) == '$' || getWellChar(piece_x - 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x - 1, piece_y + 2) == '@' || getWellChar(piece_x - 1, piece_y + 2) == '$' || getWellChar(piece_x - 1, piece_y + 2) == '*')
			return false;
	}

	if (l_piece->getOrientation() == 1) {
		if (getWellChar(piece_x, piece_y) == '@' || getWellChar(piece_x, piece_y) == '$' || getWellChar(piece_x, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
	}

	if (l_piece->getOrientation() == 2) {
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x - 1, piece_y + 2) == '@' || getWellChar(piece_x - 1, piece_y + 2) == '$' || getWellChar(piece_x - 1, piece_y + 2) == '*')
			return false;
	}

	if (l_piece->getOrientation() == 3) {
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 3) == '@' || getWellChar(piece_x, piece_y + 3) == '$' || getWellChar(piece_x, piece_y + 3) == '*')
			return false;
	}
	return true;
}

bool Well::validRotateL(Pieces* l_piece) { 
	int piece_x = l_piece->getX();
	int piece_y = l_piece->getY();

	if (l_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 1, piece_y) == '@' || getWellChar(piece_x + 1, piece_y) == '$' || getWellChar(piece_x + 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y) == '@' || getWellChar(piece_x + 2, piece_y) == '$' || getWellChar(piece_x + 2, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (l_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (l_piece->getOrientation() == 2) {
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 3) == '@' || getWellChar(piece_x + 2, piece_y + 3) == '$' || getWellChar(piece_x + 2, piece_y + 3) == '*')
			return false;
	}

	if (l_piece->getOrientation() == 3) {
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
	}
	return true;
}

void Well::finishPieceL(Pieces* l_piece) {
	int currentX = l_piece->getX();
	int currentY = l_piece->getY();

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (l_piece->getChar(x, y) == '#') {
				l_piece->changeChar(x, y, '$');
			}
		}
	}

	for (int x = currentX; x < currentX + 4 && x < 12; x++) {
		for (int y = currentY; y < currentY + 4 && y < 19; y++) {
			if (getWellChar(x, y) == '#')
				setWellChar(x, y, '$');
		}
	}
}

// PIECE O WELL FUNCTIONS

void Well::addPIECEO(Pieces* o_piece) {
	o_piece->setOrientation(0);
	o_piece->orientation0();

	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = o_piece->getChar(x - 4, y); // The character that is going to be put into the well.
			if (changer == '#')
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
		}
	}
	// Well Coords go X = 12, Y = 19
	o_piece->setX(4); // Upper left of bounding box
	o_piece->setY(0); // Upper left of bounding box
}

bool Well::validAddO(Pieces* o_piece) {
	o_piece->orientation0();
	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			if ((o_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '$') || (o_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '*'))
				return false;
		}
	}
	return true;
}

void Well::dropPIECEO(Pieces* o_piece) {
	for (int x = o_piece->getX(); x < 12, x < o_piece->getX() + 4; x++) {
		for (int y = o_piece->getY(); y < 19, y < o_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = o_piece->getX();
	int currentY = o_piece->getY() + 1;

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = o_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	o_piece->setX(currentX); // Upper left of bounding box
	o_piece->setY(currentY); // Upper left of bounding box ... Only y-coord of bounding box has been changed.
}

void Well::moveRightPIECEO(Pieces* o_piece) {
	for (int x = o_piece->getX(); x < 12, x < o_piece->getX() + 4; x++) {
		for (int y = o_piece->getY(); y < 19, y < o_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = o_piece->getX() + 1;
	int currentY = o_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = o_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	o_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	o_piece->setY(currentY); // Upper left of bounding box
}

void Well::moveLeftPIECEO(Pieces* o_piece) {
	for (int x = o_piece->getX(); x < 12, x < o_piece->getX() + 4; x++) {
		for (int y = o_piece->getY(); y < 19, y < o_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = o_piece->getX() - 1;
	int currentY = o_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = o_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	o_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	o_piece->setY(currentY); // Upper left of bounding box
}

void Well::rotatePIECEO(Pieces* o_piece) {
	for (int x = o_piece->getX(); x < 12, x < o_piece->getX() + 4; x++) {
		for (int y = o_piece->getY(); y < 19, y < o_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int decide = o_piece->getOrientation(); // Get current orientation to prepare for clockwise rotation.
	if (decide == 0)
		o_piece->orientation1();
	if (decide == 1)
		o_piece->orientation2();
	if (decide == 2)
		o_piece->orientation3();
	if (decide == 3)
		o_piece->orientation0();

	int currentX = o_piece->getX();
	int currentY = o_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = o_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	o_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	o_piece->setY(currentY); // Upper left of bounding box
}

bool Well::validMoveDownO(Pieces* o_piece) {
	int piece_x = o_piece->getX();
	int piece_y = o_piece->getY();

	// if (any "orientation")
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;

	return true;
}

bool Well::validMoveRightO(Pieces* o_piece) {
	int piece_x = o_piece->getX();
	int piece_y = o_piece->getY();

	if (getWellChar(piece_x + 2, piece_y) == '@' || getWellChar(piece_x + 2, piece_y) == '$' || getWellChar(piece_x + 2, piece_y) == '*')
		return false;
	if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
		return false;

	return true;
}

bool Well::validMoveLeftO(Pieces* o_piece) { 
	int piece_x = o_piece->getX();
	int piece_y = o_piece->getY();

	if (getWellChar(piece_x - 1, piece_y) == '@' || getWellChar(piece_x - 1, piece_y) == '$' || getWellChar(piece_x - 1, piece_y) == '*')
		return false;
	if (getWellChar(piece_x - 1, piece_y + 1) == '@' || getWellChar(piece_x - 1, piece_y + 1) == '$' || getWellChar(piece_x - 1, piece_y + 1) == '*')
		return false;

	return true;
}

bool Well::validRotateO(Pieces* o_piece) { return true; }

void Well::finishPieceO(Pieces* o_piece) {
	int currentX = o_piece->getX();
	int currentY = o_piece->getY();

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (o_piece->getChar(x, y) == '#') {
				o_piece->changeChar(x, y, '$');
			}
		}
	}

	for (int x = currentX; x < currentX + 4 && x < 12; x++) {
		for (int y = currentY; y < currentY + 4 && y < 19; y++) {
			if (getWellChar(x, y) == '#')
				setWellChar(x, y, '$');
		}
	}
}

// PIECE J WELL FUNCTIONS

void Well::addPIECEJ(Pieces* j_piece) {
	j_piece->setOrientation(0);
	j_piece->orientation0();

	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = j_piece->getChar(x - 4, y); // The character that is going to be put into the well.
			if (changer == '#')
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
		}
	}
	// Well Coords go X = 12, Y = 19
	j_piece->setX(4); // Upper left of bounding box
	j_piece->setY(0); // Upper left of bounding box
}

bool Well::validAddJ(Pieces* j_piece) {
	j_piece->orientation0();
	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			if ((j_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '$') || (j_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '*'))
				return false;
		}
	}
	return true;
}

void Well::dropPIECEJ(Pieces* j_piece) {
	for (int x = j_piece->getX(); x < 12, x < j_piece->getX() + 4; x++) {
		for (int y = j_piece->getY(); y < 19, y < j_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = j_piece->getX();
	int currentY = j_piece->getY() + 1;

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = j_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	j_piece->setX(currentX); // Upper left of bounding box
	j_piece->setY(currentY); // Upper left of bounding box ... Only y-coord of bounding box has been changed.
}

void Well::moveRightPIECEJ(Pieces* j_piece) {
	for (int x = j_piece->getX(); x < 12, x < j_piece->getX() + 4; x++) {
		for (int y = j_piece->getY(); y < 19, y < j_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = j_piece->getX() + 1;
	int currentY = j_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = j_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	j_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	j_piece->setY(currentY); // Upper left of bounding box
}

void Well::moveLeftPIECEJ(Pieces* j_piece) {
	for (int x = j_piece->getX(); x < 12, x < j_piece->getX() + 4; x++) {
		for (int y = j_piece->getY(); y < 19, y < j_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = j_piece->getX() - 1;
	int currentY = j_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = j_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	j_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	j_piece->setY(currentY); // Upper left of bounding box
}

void Well::rotatePIECEJ(Pieces* j_piece) {
	for (int x = j_piece->getX(); x < 12, x < j_piece->getX() + 4; x++) {
		for (int y = j_piece->getY(); y < 19, y < j_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int decide = j_piece->getOrientation(); // Get current orientation to prepare for clockwise rotation.
	if (decide == 0)
		j_piece->orientation1();
	if (decide == 1)
		j_piece->orientation2();
	if (decide == 2)
		j_piece->orientation3();
	if (decide == 3)
		j_piece->orientation0();

	int currentX = j_piece->getX();
	int currentY = j_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = j_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	j_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	j_piece->setY(currentY); // Upper left of bounding box
}

bool Well::validMoveDownJ(Pieces* j_piece) {
	int piece_x = j_piece->getX();
	int piece_y = j_piece->getY();

	if (j_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 3) == '@' || getWellChar(piece_x + 3, piece_y + 3) == '$' || getWellChar(piece_x + 3, piece_y + 3) == '*')
			return false;
	}

	if (j_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 1, piece_y + 4) == '@' || getWellChar(piece_x + 1, piece_y + 4) == '$' || getWellChar(piece_x + 1, piece_y + 4) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 4) == '@' || getWellChar(piece_x + 2, piece_y + 4) == '$' || getWellChar(piece_x + 2, piece_y + 4) == '*')
			return false;
	}

	if (j_piece->getOrientation() == 2) {
		for (int x = piece_x + 1; x <= piece_x + 3; x++) {
			if (getWellChar(x, piece_y + 3) == '@' || getWellChar(x, piece_y + 3) == '$' || getWellChar(x, piece_y + 3) == '*')
				return false;
		}
	}

	if (j_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveRightJ(Pieces* j_piece) {
	int piece_x = j_piece->getX();
	int piece_y = j_piece->getY();

	if (j_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 4, piece_y + 1) == '@' || getWellChar(piece_x + 4, piece_y + 1) == '$' || getWellChar(piece_x + 4, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 4, piece_y + 2) == '@' || getWellChar(piece_x + 4, piece_y + 2) == '$' || getWellChar(piece_x + 4, piece_y + 2) == '*')
			return false;
	}

	if (j_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 2) == '@' || getWellChar(piece_x + 3, piece_y + 2) == '$' || getWellChar(piece_x + 3, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 3) == '@' || getWellChar(piece_x + 3, piece_y + 3) == '$' || getWellChar(piece_x + 3, piece_y + 3) == '*')
			return false;
	}

	if (j_piece->getOrientation() == 2) {
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 4, piece_y + 2) == '@' || getWellChar(piece_x + 4, piece_y + 2) == '$' || getWellChar(piece_x + 4, piece_y + 2) == '*')
			return false;
	}

	if (j_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 3, piece_y) == '@' || getWellChar(piece_x + 3, piece_y) == '$' || getWellChar(piece_x + 3, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveLeftJ(Pieces* j_piece) {
	int piece_x = j_piece->getX();
	int piece_y = j_piece->getY();

	if (j_piece->getOrientation() == 0) {
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (j_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 3) == '@' || getWellChar(piece_x, piece_y + 3) == '$' || getWellChar(piece_x, piece_y + 3) == '*')
			return false;
	}

	if (j_piece->getOrientation() == 2) {
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
	}

	if (j_piece->getOrientation() == 3) {
		if (getWellChar(piece_x, piece_y) == '@' || getWellChar(piece_x, piece_y) == '$' || getWellChar(piece_x, piece_y) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
	}
	return true;
}

bool Well::validRotateJ(Pieces* j_piece) { 
	int piece_x = j_piece->getX();
	int piece_y = j_piece->getY();

	if (j_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 3) == '@' || getWellChar(piece_x + 2, piece_y + 3) == '$' || getWellChar(piece_x + 2, piece_y + 3) == '*')
			return false;
	}

	if (j_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 2) == '@' || getWellChar(piece_x + 3, piece_y + 2) == '$' || getWellChar(piece_x + 3, piece_y + 2) == '*')
			return false;
	}

	if (j_piece->getOrientation() == 2) {
		if (getWellChar(piece_x + 1, piece_y) == '@' || getWellChar(piece_x + 1, piece_y) == '$' || getWellChar(piece_x + 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y) == '@' || getWellChar(piece_x + 2, piece_y) == '$' || getWellChar(piece_x + 2, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
	}

	if (j_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 2) == '@' || getWellChar(piece_x + 3, piece_y + 2) == '$' || getWellChar(piece_x + 3, piece_y + 2) == '*')
			return false;
	}
	return true;
}

void Well::finishPieceJ(Pieces* j_piece) {
	int currentX = j_piece->getX();
	int currentY = j_piece->getY();

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (j_piece->getChar(x, y) == '#') {
				j_piece->changeChar(x, y, '$');
			}
		}
	}

	for (int x = currentX; x < currentX + 4 && x < 12; x++) {
		for (int y = currentY; y < currentY + 4 && y < 19; y++) {
			if (getWellChar(x, y) == '#')
				setWellChar(x, y, '$');
		}
	}
}

// PIECE T WELL FUNCTIONS

void Well::addPIECET(Pieces* t_piece) {
	t_piece->setOrientation(0);
	t_piece->orientation0();

	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = t_piece->getChar(x - 4, y); // The character that is going to be put into the well.
			if (changer == '#')
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
		}
	}
	// Well Coords go X = 12, Y = 19
	t_piece->setX(4); // Upper left of bounding box
	t_piece->setY(0); // Upper left of bounding box
}

bool Well::validAddT(Pieces* t_piece) {
	t_piece->orientation0();
	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			if ((t_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '$') || (t_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '*'))
				return false;
		}
	}
	return true;
}

void Well::dropPIECET(Pieces* t_piece) {
	for (int x = t_piece->getX(); x < 12, x < t_piece->getX() + 4; x++) {
		for (int y = t_piece->getY(); y < 19, y < t_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = t_piece->getX();
	int currentY = t_piece->getY() + 1;

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = t_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	t_piece->setX(currentX); // Upper left of bounding box
	t_piece->setY(currentY); // Upper left of bounding box ... Only y-coord of bounding box has been changed.
}

void Well::moveRightPIECET(Pieces* t_piece) {
	for (int x = t_piece->getX(); x < 12, x < t_piece->getX() + 4; x++) {
		for (int y = t_piece->getY(); y < 19, y < t_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = t_piece->getX() + 1;
	int currentY = t_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = t_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	t_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	t_piece->setY(currentY); // Upper left of bounding box
}

void Well::moveLeftPIECET(Pieces* t_piece) {
	for (int x = t_piece->getX(); x < 12, x < t_piece->getX() + 4; x++) {
		for (int y = t_piece->getY(); y < 19, y < t_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = t_piece->getX() - 1;
	int currentY = t_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = t_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	t_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	t_piece->setY(currentY); // Upper left of bounding box
}

void Well::rotatePIECET(Pieces* t_piece) {
	for (int x = t_piece->getX(); x < 12, x < t_piece->getX() + 4; x++) {
		for (int y = t_piece->getY(); y < 19, y < t_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int decide = t_piece->getOrientation(); // Get current orientation to prepare for clockwise rotation.
	if (decide == 0)
		t_piece->orientation1();
	if (decide == 1)
		t_piece->orientation2();
	if (decide == 2)
		t_piece->orientation3();
	if (decide == 3)
		t_piece->orientation0();

	int currentX = t_piece->getX();
	int currentY = t_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = t_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	t_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	t_piece->setY(currentY); // Upper left of bounding box
}

bool Well::validMoveDownT(Pieces* t_piece) {
	int piece_x = t_piece->getX();
	int piece_y = t_piece->getY();

	if (t_piece->getOrientation() == 0) {
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (t_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (t_piece->getOrientation() == 2) {
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (t_piece->getOrientation() == 3) {
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveRightT(Pieces* t_piece) {
	int piece_x = t_piece->getX();
	int piece_y = t_piece->getY();

	if (t_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 2, piece_y) == '@' || getWellChar(piece_x + 2, piece_y) == '$' || getWellChar(piece_x + 2, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
	}

	if (t_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 2, piece_y) == '@' || getWellChar(piece_x + 2, piece_y) == '$' || getWellChar(piece_x + 2, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (t_piece->getOrientation() == 2) {
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (t_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 2, piece_y) == '@' || getWellChar(piece_x + 2, piece_y) == '$' || getWellChar(piece_x + 2, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveLeftT(Pieces* t_piece) { 
	int piece_x = t_piece->getX();
	int piece_y = t_piece->getY();

	if (t_piece->getOrientation() == 0) {
		if (getWellChar(piece_x, piece_y) == '@' || getWellChar(piece_x, piece_y) == '$' || getWellChar(piece_x, piece_y) == '*')
			return false;
		if (getWellChar(piece_x - 1, piece_y + 1) == '@' || getWellChar(piece_x - 1, piece_y + 1) == '$' || getWellChar(piece_x - 1, piece_y + 1) == '*')
			return false;
	}

	if (t_piece->getOrientation() == 1) {
		if (getWellChar(piece_x, piece_y) == '@' || getWellChar(piece_x, piece_y) == '$' || getWellChar(piece_x, piece_y) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
	}

	if (t_piece->getOrientation() == 2) {
		if (getWellChar(piece_x - 1, piece_y + 1) == '@' || getWellChar(piece_x - 1, piece_y + 1) == '$' || getWellChar(piece_x - 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
	}

	if (t_piece->getOrientation() == 3) {
		if (getWellChar(piece_x, piece_y) == '@' || getWellChar(piece_x, piece_y) == '$' || getWellChar(piece_x, piece_y) == '*')
			return false;
		if (getWellChar(piece_x - 1, piece_y + 1) == '@' || getWellChar(piece_x - 1, piece_y + 1) == '$' || getWellChar(piece_x - 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
	}
	return true;
}

bool Well::validRotateT(Pieces* t_piece) {
	int piece_x = t_piece->getX();
	int piece_y = t_piece->getY();

	if (t_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 1, piece_y) == '@' || getWellChar(piece_x + 1, piece_y) == '$' || getWellChar(piece_x + 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
	}

	if (t_piece->getOrientation() == 1) {
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
	}

	if (t_piece->getOrientation() == 2) {
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y) == '@' || getWellChar(piece_x + 1, piece_y) == '$' || getWellChar(piece_x + 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
	}

	if (t_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 1, piece_y) == '@' || getWellChar(piece_x + 1, piece_y) == '$' || getWellChar(piece_x + 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
	}
	return true;
}

void Well::finishPieceT(Pieces* t_piece) {
	int currentX = t_piece->getX();
	int currentY = t_piece->getY();

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (t_piece->getChar(x, y) == '#') {
				t_piece->changeChar(x, y, '$');
			}
		}
	}

	for (int x = currentX; x < currentX + 4 && x < 12; x++) {
		for (int y = currentY; y < currentY + 4 && y < 19; y++) {
			if (getWellChar(x, y) == '#')
				setWellChar(x, y, '$');
		}
	}
}

// PIECE S WELL FUNCTIONS

void Well::addPIECES(Pieces* s_piece) {
	s_piece->setOrientation(0);
	s_piece->orientation0();

	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = s_piece->getChar(x - 4, y); // The character that is going to be put into the well.
			if (changer == '#')
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
		}
	}
	// Well Coords go X = 12, Y = 19
	s_piece->setX(4); // Upper left of bounding box
	s_piece->setY(0); // Upper left of bounding box
}

bool Well::validAddS(Pieces* s_piece) {
	s_piece->orientation0();
	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			if ((s_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '$') || (s_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '*'))
				return false;
		}
	}
	return true;
}

void Well::dropPIECES(Pieces* s_piece) {
	for (int x = s_piece->getX(); x < 12, x < s_piece->getX() + 4; x++) {
		for (int y = s_piece->getY(); y < 19, y < s_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = s_piece->getX();
	int currentY = s_piece->getY() + 1;

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = s_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	s_piece->setX(currentX); // Upper left of bounding box
	s_piece->setY(currentY); // Upper left of bounding box ... Only y-coord of bounding box has been changed.
}

void Well::moveRightPIECES(Pieces* s_piece) {
	for (int x = s_piece->getX(); x < 12, x < s_piece->getX() + 4; x++) {
		for (int y = s_piece->getY(); y < 19, y < s_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = s_piece->getX() + 1;
	int currentY = s_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = s_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	s_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	s_piece->setY(currentY); // Upper left of bounding box
}

void Well::moveLeftPIECES(Pieces* s_piece) {
	for (int x = s_piece->getX(); x < 12, x < s_piece->getX() + 4; x++) {
		for (int y = s_piece->getY(); y < 19, y < s_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = s_piece->getX() - 1;
	int currentY = s_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = s_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	s_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	s_piece->setY(currentY); // Upper left of bounding box
}

void Well::rotatePIECES(Pieces* s_piece) {
	for (int x = s_piece->getX(); x < 12, x < s_piece->getX() + 4; x++) {
		for (int y = s_piece->getY(); y < 19, y < s_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int decide = s_piece->getOrientation(); // Get current orientation to prepare for clockwise rotation.
	if (decide == 0)
		s_piece->orientation1();
	if (decide == 1)
		s_piece->orientation2();
	if (decide == 2)
		s_piece->orientation3();
	if (decide == 3)
		s_piece->orientation0();

	int currentX = s_piece->getX();
	int currentY = s_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = s_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	s_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	s_piece->setY(currentY); // Upper left of bounding box
}

bool Well::validMoveDownS(Pieces* s_piece) {
	int piece_x = s_piece->getX();
	int piece_y = s_piece->getY();

	if (s_piece->getOrientation() == 0 || s_piece->getOrientation() == 2) {
		if (getWellChar(piece_x, piece_y + 3) == '@' || getWellChar(piece_x, piece_y + 3) == '$' || getWellChar(piece_x, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (s_piece->getOrientation() == 1 || s_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 3) == '@' || getWellChar(piece_x + 2, piece_y + 3) == '$' || getWellChar(piece_x + 2, piece_y + 3) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveRightS(Pieces* s_piece) {
	int piece_x = s_piece->getX();
	int piece_y = s_piece->getY();

	if (s_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (s_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 2, piece_y) == '@' || getWellChar(piece_x + 2, piece_y) == '$' || getWellChar(piece_x + 2, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 2) == '@' || getWellChar(piece_x + 3, piece_y + 2) == '$' || getWellChar(piece_x + 3, piece_y + 2) == '*')
			return false;
	}

	if (s_piece->getOrientation() == 2) {
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (s_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 2, piece_y) == '@' || getWellChar(piece_x + 2, piece_y) == '$' || getWellChar(piece_x + 2, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 2) == '@' || getWellChar(piece_x + 3, piece_y + 2) == '$' || getWellChar(piece_x + 3, piece_y + 2) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveLeftS(Pieces* s_piece) {
	int piece_x = s_piece->getX();
	int piece_y = s_piece->getY();

	if (s_piece->getOrientation() == 0) {
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x - 1, piece_y + 2) == '@' || getWellChar(piece_x - 1, piece_y + 2) == '$' || getWellChar(piece_x - 1, piece_y + 2) == '*')
			return false;
	}

	if (s_piece->getOrientation() == 1) {
		if (getWellChar(piece_x, piece_y) == '@' || getWellChar(piece_x, piece_y) == '$' || getWellChar(piece_x, piece_y) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x+1, piece_y + 2) == '@' || getWellChar(piece_x+1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
	}

	if (s_piece->getOrientation() == 2) {
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x - 1, piece_y + 2) == '@' || getWellChar(piece_x - 1, piece_y + 2) == '$' || getWellChar(piece_x - 1, piece_y + 2) == '*')
			return false;
	}

	if (s_piece->getOrientation() == 3) {
		if (getWellChar(piece_x, piece_y) == '@' || getWellChar(piece_x, piece_y) == '$' || getWellChar(piece_x, piece_y) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x+1, piece_y + 2) == '@' || getWellChar(piece_x+1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
	}
	return true;
}

bool Well::validRotateS(Pieces* s_piece) { 
	int piece_x = s_piece->getX();
	int piece_y = s_piece->getY();

	if (s_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 1, piece_y) == '@' || getWellChar(piece_x + 1, piece_y) == '$' || getWellChar(piece_x + 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (s_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
	}

	if (s_piece->getOrientation() == 2) {
		if (getWellChar(piece_x + 1, piece_y) == '@' || getWellChar(piece_x + 1, piece_y) == '$' || getWellChar(piece_x + 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (s_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
	}
	return true;
}

void Well::finishPieceS(Pieces* s_piece) {
	int currentX = s_piece->getX();
	int currentY = s_piece->getY();

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (s_piece->getChar(x, y) == '#') {
				s_piece->changeChar(x, y, '$');
			}
		}
	}

	for (int x = currentX; x < currentX + 4 && x < 12; x++) {
		for (int y = currentY; y < currentY + 4 && y < 19; y++) {
			if (getWellChar(x, y) == '#')
				setWellChar(x, y, '$');
		}
	}
}

// PIECE Z WELL FUNCTIONS

void Well::addPIECEZ(Pieces* z_piece) {
	z_piece->setOrientation(0);
	z_piece->orientation0();

	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = z_piece->getChar(x - 4, y); // The character that is going to be put into the well.
			if (changer == '#')
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
		}
	}
	// Well Coords go X = 12, Y = 19
	z_piece->setX(4); // Upper left of bounding box
	z_piece->setY(0); // Upper left of bounding box
}

bool Well::validAddZ(Pieces* z_piece) {
	z_piece->orientation0();
	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			if ((z_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '$') || (z_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '*'))
				return false;
		}
	}
	return true;
}

void Well::dropPIECEZ(Pieces* z_piece) {
	for (int x = z_piece->getX(); x < 12, x < z_piece->getX() + 4; x++) {
		for (int y = z_piece->getY(); y < 19, y < z_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = z_piece->getX();
	int currentY = z_piece->getY() + 1;

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = z_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	z_piece->setX(currentX); // Upper left of bounding box
	z_piece->setY(currentY); // Upper left of bounding box ... Only y-coord of bounding box has been changed.
}

void Well::moveRightPIECEZ(Pieces* z_piece) {
	for (int x = z_piece->getX(); x < 12, x < z_piece->getX() + 4; x++) {
		for (int y = z_piece->getY(); y < 19, y < z_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = z_piece->getX() + 1;
	int currentY = z_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = z_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	z_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	z_piece->setY(currentY); // Upper left of bounding box
}

void Well::moveLeftPIECEZ(Pieces* z_piece) {
	for (int x = z_piece->getX(); x < 12, x < z_piece->getX() + 4; x++) {
		for (int y = z_piece->getY(); y < 19, y < z_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = z_piece->getX() - 1;
	int currentY = z_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = z_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	z_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	z_piece->setY(currentY); // Upper left of bounding box
}

void Well::rotatePIECEZ(Pieces* z_piece) {
	for (int x = z_piece->getX(); x < 12, x < z_piece->getX() + 4; x++) {
		for (int y = z_piece->getY(); y < 19, y < z_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int decide = z_piece->getOrientation(); // Get current orientation to prepare for clockwise rotation.
	if (decide == 0)
		z_piece->orientation1();
	if (decide == 1)
		z_piece->orientation2();
	if (decide == 2)
		z_piece->orientation3();
	if (decide == 3)
		z_piece->orientation0();

	int currentX = z_piece->getX();
	int currentY = z_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = z_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	z_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	z_piece->setY(currentY); // Upper left of bounding box
}

bool Well::validMoveDownZ(Pieces* z_piece) {
	int piece_x = z_piece->getX();
	int piece_y = z_piece->getY();

	if (z_piece->getOrientation() == 0 || z_piece->getOrientation() == 2) {
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 3) == '@' || getWellChar(piece_x + 2, piece_y + 3) == '$' || getWellChar(piece_x + 2, piece_y + 3) == '*')
			return false;
	}

	if (z_piece->getOrientation() == 1 || z_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveRightZ(Pieces* z_piece) {
	int piece_x = z_piece->getX();
	int piece_y = z_piece->getY();

	if (z_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 2) == '@' || getWellChar(piece_x + 3, piece_y + 2) == '$' || getWellChar(piece_x + 3, piece_y + 2) == '*')
			return false;
	}

	if (z_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 3, piece_y) == '@' || getWellChar(piece_x + 3, piece_y) == '$' || getWellChar(piece_x + 3, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (z_piece->getOrientation() == 2) {
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 2) == '@' || getWellChar(piece_x + 3, piece_y + 2) == '$' || getWellChar(piece_x + 3, piece_y + 2) == '*')
			return false;
	}

	if (z_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 3, piece_y) == '@' || getWellChar(piece_x + 3, piece_y) == '$' || getWellChar(piece_x + 3, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveLeftZ(Pieces* z_piece) { 
	int piece_x = z_piece->getX();
	int piece_y = z_piece->getY();

	if (z_piece->getOrientation() == 0) {
		if (getWellChar(piece_x - 1, piece_y + 1) == '@' || getWellChar(piece_x - 1, piece_y + 1) == '$' || getWellChar(piece_x - 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
	}

	if (z_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 1, piece_y) == '@' || getWellChar(piece_x + 1, piece_y) == '$' || getWellChar(piece_x + 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
	}

	if (z_piece->getOrientation() == 2) {
		if (getWellChar(piece_x - 1, piece_y + 1) == '@' || getWellChar(piece_x - 1, piece_y + 1) == '$' || getWellChar(piece_x - 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
	}

	if (z_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 1, piece_y) == '@' || getWellChar(piece_x + 1, piece_y) == '$' || getWellChar(piece_x + 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
	}
	return true;
}

bool Well::validRotateZ(Pieces* z_piece) { 
	int piece_x = z_piece->getX();
	int piece_y = z_piece->getY();

	if (z_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 2, piece_y) == '@' || getWellChar(piece_x + 2, piece_y) == '$' || getWellChar(piece_x + 2, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
	}

	if (z_piece->getOrientation() == 1) {
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}

	if (z_piece->getOrientation() == 2) {
		if (getWellChar(piece_x + 2, piece_y) == '@' || getWellChar(piece_x + 2, piece_y) == '$' || getWellChar(piece_x + 2, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
	}

	if (z_piece->getOrientation() == 3) {
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
	}
	return true;
}

void Well::finishPieceZ(Pieces* z_piece) {
	int currentX = z_piece->getX();
	int currentY = z_piece->getY();

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (z_piece->getChar(x, y) == '#') {
				z_piece->changeChar(x, y, '$');
			}
		}
	}

	for (int x = currentX; x < currentX + 4 && x < 12; x++) {
		for (int y = currentY; y < currentY + 4 && y < 19; y++) {
			if (getWellChar(x, y) == '#')
				setWellChar(x, y, '$');
		}
	}
}

// CRAZY PIECE FUNCTIONS

void Well::addPIECEC(Pieces* c_piece) {
	c_piece->setOrientation(0);
	c_piece->orientation0();

	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = c_piece->getChar(x - 4, y); // The character that is going to be put into the well.
			if (changer == '#')
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
		}
	}
	// Well Coords go X = 12, Y = 19
	c_piece->setX(4); // Upper left of bounding box
	c_piece->setY(0); // Upper left of bounding box
}

bool Well::validAddC(Pieces* c_piece) {
	c_piece->orientation0();
	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			if ((c_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '$') || (c_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '*'))
				return false;
		}
	}
	return true;
}

void Well::dropPIECEC(Pieces* c_piece) {
	for (int x = c_piece->getX(); x < 12, x < c_piece->getX() + 4; x++) {
		for (int y = c_piece->getY(); y < 19, y < c_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = c_piece->getX();
	int currentY = c_piece->getY() + 1;

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = c_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	c_piece->setX(currentX); // Upper left of bounding box
	c_piece->setY(currentY); // Upper left of bounding box ... Only y-coord of bounding box has been changed.
}

void Well::moveRightPIECEC(Pieces* c_piece) {
	for (int x = c_piece->getX(); x < 12, x < c_piece->getX() + 4; x++) {
		for (int y = c_piece->getY(); y < 19, y < c_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = c_piece->getX() + 1;
	int currentY = c_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = c_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	c_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	c_piece->setY(currentY); // Upper left of bounding box
}

void Well::moveLeftPIECEC(Pieces* c_piece) {
	for (int x = c_piece->getX(); x < 12, x < c_piece->getX() + 4; x++) {
		for (int y = c_piece->getY(); y < 19, y < c_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = c_piece->getX() - 1;
	int currentY = c_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = c_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	c_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	c_piece->setY(currentY); // Upper left of bounding box
}

void Well::rotatePIECEC(Pieces* c_piece) {
	for (int x = c_piece->getX(); x < 12, x < c_piece->getX() + 4; x++) {
		for (int y = c_piece->getY(); y < 19, y < c_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int decide = c_piece->getOrientation(); // Get current orientation to prepare for clockwise rotation.
	if (decide == 0)
		c_piece->orientation1();
	if (decide == 1)
		c_piece->orientation2();
	if (decide == 2)
		c_piece->orientation3();
	if (decide == 3)
		c_piece->orientation0();

	int currentX = c_piece->getX();
	int currentY = c_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = c_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	c_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	c_piece->setY(currentY); // Upper left of bounding box
}

bool Well::validMoveDownC(Pieces* c_piece) {
	int piece_x = c_piece->getX();
	int piece_y = c_piece->getY();

	if (c_piece->getOrientation() == 0) {
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
	}

	if (c_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 2, piece_y + 3) == '@' || getWellChar(piece_x + 2, piece_y + 3) == '$' || getWellChar(piece_x + 2, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 4) == '@' || getWellChar(piece_x + 3, piece_y + 4) == '$' || getWellChar(piece_x + 3, piece_y + 4) == '*')
			return false;
	}

	if (c_piece->getOrientation() == 2) {
		if (getWellChar(piece_x, piece_y + 4) == '@' || getWellChar(piece_x, piece_y + 4) == '$' || getWellChar(piece_x, piece_y + 4) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 3) == '@' || getWellChar(piece_x + 2, piece_y + 3) == '$' || getWellChar(piece_x + 2, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 4) == '@' || getWellChar(piece_x + 3, piece_y + 4) == '$' || getWellChar(piece_x + 3, piece_y + 4) == '*')
			return false;
	}

	if (c_piece->getOrientation() == 3) {
		if (getWellChar(piece_x, piece_y + 4) == '@' || getWellChar(piece_x, piece_y + 4) == '$' || getWellChar(piece_x, piece_y + 4) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveRightC(Pieces* c_piece) {
	int piece_x = c_piece->getX();
	int piece_y = c_piece->getY();

	if (c_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 4, piece_y) == '@' || getWellChar(piece_x + 4, piece_y) == '$' || getWellChar(piece_x + 4, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
	}

	if (c_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 4, piece_y) == '@' || getWellChar(piece_x + 4, piece_y) == '$' || getWellChar(piece_x + 4, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 1) == '@' || getWellChar(piece_x + 3, piece_y + 1) == '$' || getWellChar(piece_x + 3, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 2) == '@' || getWellChar(piece_x + 3, piece_y + 2) == '$' || getWellChar(piece_x + 3, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 4, piece_y + 3) == '@' || getWellChar(piece_x + 4, piece_y + 3) == '$' || getWellChar(piece_x + 4, piece_y + 3) == '*')
			return false;
	}

	if (c_piece->getOrientation() == 2) {
		if (getWellChar(piece_x + 3, piece_y + 2) == '@' || getWellChar(piece_x + 3, piece_y + 2) == '$' || getWellChar(piece_x + 3, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 4, piece_y + 3) == '@' || getWellChar(piece_x + 4, piece_y + 3) == '$' || getWellChar(piece_x + 4, piece_y + 3) == '*')
			return false;
	}

	if (c_piece->getOrientation() == 3) {
		if (getWellChar(piece_x + 1, piece_y) == '@' || getWellChar(piece_x + 1, piece_y) == '$' || getWellChar(piece_x + 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 3) == '@' || getWellChar(piece_x + 1, piece_y + 3) == '$' || getWellChar(piece_x + 1, piece_y + 3) == '*')
			return false;
	}
	return true;
}

bool Well::validMoveLeftC(Pieces* c_piece) {
	int piece_x = c_piece->getX();
	int piece_y = c_piece->getY();

	if (c_piece->getOrientation() == 0) {
		if (getWellChar(piece_x - 1, piece_y) == '@' || getWellChar(piece_x - 1, piece_y) == '$' || getWellChar(piece_x - 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
	}

	if (c_piece->getOrientation() == 1) {
		if (getWellChar(piece_x + 2, piece_y) == '@' || getWellChar(piece_x + 2, piece_y) == '$' || getWellChar(piece_x + 2, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 3) == '@' || getWellChar(piece_x + 2, piece_y + 3) == '$' || getWellChar(piece_x + 2, piece_y + 3) == '*')
			return false;
	}

	if (c_piece->getOrientation() == 2) {
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x - 1, piece_y + 3) == '@' || getWellChar(piece_x - 1, piece_y + 3) == '$' || getWellChar(piece_x - 1, piece_y + 3) == '*')
			return false;
	}

	if (c_piece->getOrientation() == 3) {
		if (getWellChar(piece_x - 1, piece_y) == '@' || getWellChar(piece_x - 1, piece_y) == '$' || getWellChar(piece_x - 1, piece_y) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 2) == '@' || getWellChar(piece_x, piece_y + 2) == '$' || getWellChar(piece_x, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x - 1, piece_y + 3) == '@' || getWellChar(piece_x - 1, piece_y + 3) == '$' || getWellChar(piece_x - 1, piece_y + 3) == '*')
			return false;
	}
	return true;
}

bool Well::validRotateC(Pieces* c_piece) {
	int piece_x = c_piece->getX();
	int piece_y = c_piece->getY();

	if (c_piece->getOrientation() == 0) {
		if (getWellChar(piece_x + 3, piece_y) == '@' || getWellChar(piece_x + 3, piece_y) == '$' || getWellChar(piece_x + 3, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 3) == '@' || getWellChar(piece_x + 3, piece_y + 3) == '$' || getWellChar(piece_x + 3, piece_y + 3) == '*')
			return false;
	}

	if (c_piece->getOrientation() == 1) {
		if (getWellChar(piece_x, piece_y + 3) == '@' || getWellChar(piece_x, piece_y + 3) == '$' || getWellChar(piece_x, piece_y + 3) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 2) == '@' || getWellChar(piece_x + 2, piece_y + 2) == '$' || getWellChar(piece_x + 2, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y + 3) == '@' || getWellChar(piece_x + 3, piece_y + 3) == '$' || getWellChar(piece_x + 3, piece_y + 3) == '*')
			return false;
	}

	if (c_piece->getOrientation() == 2) {
		if (getWellChar(piece_x, piece_y) == '@' || getWellChar(piece_x, piece_y) == '$' || getWellChar(piece_x, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
			return false;
		if (getWellChar(piece_x, piece_y + 3) == '@' || getWellChar(piece_x, piece_y + 3) == '$' || getWellChar(piece_x, piece_y + 3) == '*')
			return false;
	}

	if (c_piece->getOrientation() == 3) {
		if (getWellChar(piece_x, piece_y) == '@' || getWellChar(piece_x, piece_y) == '$' || getWellChar(piece_x, piece_y) == '*')
			return false;
		if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
			return false;
		if (getWellChar(piece_x + 3, piece_y) == '@' || getWellChar(piece_x + 3, piece_y) == '$' || getWellChar(piece_x + 3, piece_y) == '*')
			return false;
	}
	return true;
}

void Well::finishPieceC(Pieces* c_piece) {
	int currentX = c_piece->getX();
	int currentY = c_piece->getY();

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (c_piece->getChar(x, y) == '#') {
				c_piece->changeChar(x, y, '$');
			}
		}
	}

	for (int x = currentX; x < currentX + 4 && x < 12; x++) {
		for (int y = currentY; y < currentY + 4 && y < 19; y++) {
			if (getWellChar(x, y) == '#')
				setWellChar(x, y, '$');
		}
	}
}

// VAPOR BOMB FUNCTIONS

void Well::addPIECEV(Pieces* v_piece) {
	v_piece->setOrientation(0);
	v_piece->orientation0();

	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = v_piece->getChar(x - 4, y); // The character that is going to be put into the well.
			if (changer == '#')
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
		}
	}
	// Well Coords go X = 12, Y = 19
	v_piece->setX(4); // Upper left of bounding box
	v_piece->setY(0); // Upper left of bounding box
}

void Well::dropPIECEV(Pieces* v_piece) {
	for (int x = v_piece->getX(); x < 12, x < v_piece->getX() + 4; x++) {
		for (int y = v_piece->getY(); y < 19, y < v_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = v_piece->getX();
	int currentY = v_piece->getY() + 1;

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = v_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	v_piece->setX(currentX); // Upper left of bounding box
	v_piece->setY(currentY); // Upper left of bounding box ... Only y-coord of bounding box has been changed.
}

void Well::moveRightPIECEV(Pieces* v_piece) {
	for (int x = v_piece->getX(); x < 12, x < v_piece->getX() + 4; x++) {
		for (int y = v_piece->getY(); y < 19, y < v_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = v_piece->getX() + 1;
	int currentY = v_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = v_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	v_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	v_piece->setY(currentY); // Upper left of bounding box
}

void Well::moveLeftPIECEV(Pieces* v_piece) {
	for (int x = v_piece->getX(); x < 12, x < v_piece->getX() + 4; x++) {
		for (int y = v_piece->getY(); y < 19, y < v_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = v_piece->getX() - 1;
	int currentY = v_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = v_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	v_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	v_piece->setY(currentY); // Upper left of bounding box
}

void Well::rotatePIECEV(Pieces* v_piece) {
	for (int x = v_piece->getX(); x < 12, x < v_piece->getX() + 4; x++) {
		for (int y = v_piece->getY(); y < 19, y < v_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int decide = v_piece->getOrientation(); // Get current orientation to prepare for clockwise rotation.
	if (decide == 0)
		v_piece->orientation1();
	if (decide == 1)
		v_piece->orientation2();
	if (decide == 2)
		v_piece->orientation3();
	if (decide == 3)
		v_piece->orientation0();

	int currentX = v_piece->getX();
	int currentY = v_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = v_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	v_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	v_piece->setY(currentY); // Upper left of bounding box
}

bool Well::validMoveDownV(Pieces* v_piece) {
	int piece_x = v_piece->getX();
	int piece_y = v_piece->getY();

	// if (any "orientation")
	if (getWellChar(piece_x + 1, piece_y + 1) == '@' || getWellChar(piece_x + 1, piece_y + 1) == '$' || getWellChar(piece_x + 1, piece_y + 1) == '*')
		return false;
	if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
		return false;

	return true;
}

bool Well::validMoveRightV(Pieces* v_piece) {
	int piece_x = v_piece->getX();
	int piece_y = v_piece->getY();

	if (getWellChar(piece_x + 3, piece_y) == '@' || getWellChar(piece_x + 3, piece_y) == '$' || getWellChar(piece_x + 3, piece_y) == '*')
		return false;

	return true;
}

bool Well::validMoveLeftV(Pieces* v_piece) {
	int piece_x = v_piece->getX();
	int piece_y = v_piece->getY();

	if (getWellChar(piece_x, piece_y) == '@' || getWellChar(piece_x, piece_y) == '$' || getWellChar(piece_x, piece_y) == '*')
		return false;

	return true;
}

bool Well::validRotateV(Pieces* v_piece) { return true; }

bool Well::validAddV(Pieces* v_piece) {
	v_piece->orientation0();
	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			if ((v_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '$') || (v_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '*'))
				return false;
		}
	}
	return true;
}

void Well::finishPieceV(Pieces* v_piece) {
	int currentX = v_piece->getX();
	int currentY = v_piece->getY();

	for (int x = currentX; x < currentX + 4 && x < 12; x++) {
		for (int y = currentY; y < currentY + 4 && y < 19; y++) {
			if (getWellChar(x, y) == '#')
				setWellChar(x, y, ' ');
		}
	}

	for (int x = currentX+1; x < currentX + 3 && x < 12; x++) {
		for (int y = currentY-2; y < currentY + 3 && y < 19; y++) {
			if (getWellChar(x, y) == '$')
				setWellChar(x, y, ' ');
		}
	}
}

// FOAM BOMB FUNCTIONS

void Well::addPIECEF(Pieces* f_piece) {
	f_piece->setOrientation(0);
	f_piece->orientation0();

	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = f_piece->getChar(x - 4, y); // The character that is going to be put into the well.
			if (changer == '#')
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
		}
	}
	// Well Coords go X = 12, Y = 19
	f_piece->setX(4); // Upper left of bounding box
	f_piece->setY(0); // Upper left of bounding box
}

void Well::dropPIECEF(Pieces* f_piece) {
	for (int x = f_piece->getX(); x < 12, x < f_piece->getX() + 4; x++) {
		for (int y = f_piece->getY(); y < 19, y < f_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = f_piece->getX();
	int currentY = f_piece->getY() + 1;

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = f_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	f_piece->setX(currentX); // Upper left of bounding box
	f_piece->setY(currentY); // Upper left of bounding box ... Only y-coord of bounding box has been changed.
}

void Well::moveRightPIECEF(Pieces* f_piece) {
	for (int x = f_piece->getX(); x < 12, x < f_piece->getX() + 4; x++) {
		for (int y = f_piece->getY(); y < 19, y < f_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = f_piece->getX() + 1;
	int currentY = f_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = f_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	f_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	f_piece->setY(currentY); // Upper left of bounding box
}

void Well::moveLeftPIECEF(Pieces* f_piece) {
	for (int x = f_piece->getX(); x < 12, x < f_piece->getX() + 4; x++) {
		for (int y = f_piece->getY(); y < 19, y < f_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int currentX = f_piece->getX() - 1;
	int currentY = f_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = f_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	f_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	f_piece->setY(currentY); // Upper left of bounding box
}

void Well::rotatePIECEF(Pieces* f_piece) {
	for (int x = f_piece->getX(); x < 12, x < f_piece->getX() + 4; x++) {
		for (int y = f_piece->getY(); y < 19, y < f_piece->getY() + 4; y++) {
			if (getWellChar(x, y) == '#') { setWellChar(x, y, ' '); }
		}
	} // This loop deletes the i_piece's old char data

	int decide = f_piece->getOrientation(); // Get current orientation to prepare for clockwise rotation.
	if (decide == 0)
		f_piece->orientation1();
	if (decide == 1)
		f_piece->orientation2();
	if (decide == 2)
		f_piece->orientation3();
	if (decide == 3)
		f_piece->orientation0();

	int currentX = f_piece->getX();
	int currentY = f_piece->getY();

	for (int x = currentX; x < currentX + 4; x++) {
		for (int y = currentY; y < currentY + 4; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			char changer = f_piece->getChar(x - currentX, y - currentY); // The character that is going to be put into the well.
			if (getWellChar(x, y) == ' ') {
				setWellChar(x, y, changer); // wellGrid pointer uses setWellChar to change m_wellGrid of well ... char to use determined by getChar of piece bounding box
			}
		}
	}

	// Well Coords go X = 12, Y = 19
	f_piece->setX(currentX); // Upper left of bounding box ... Only x-coord of bounding box has been changed.
	f_piece->setY(currentY); // Upper left of bounding box
}

bool Well::validMoveDownF(Pieces* f_piece) {
	int piece_x = f_piece->getX();
	int piece_y = f_piece->getY();

	// if (any "orientation")
	if (getWellChar(piece_x + 1, piece_y + 2) == '@' || getWellChar(piece_x + 1, piece_y + 2) == '$' || getWellChar(piece_x + 1, piece_y + 2) == '*')
		return false;

	return true;
}

bool Well::validMoveRightF(Pieces* f_piece) {
	int piece_x = f_piece->getX();
	int piece_y = f_piece->getY();

	if (getWellChar(piece_x + 2, piece_y + 1) == '@' || getWellChar(piece_x + 2, piece_y + 1) == '$' || getWellChar(piece_x + 2, piece_y + 1) == '*')
		return false;

	return true;
}

bool Well::validMoveLeftF(Pieces* f_piece) {
	int piece_x = f_piece->getX();
	int piece_y = f_piece->getY();

	if (getWellChar(piece_x, piece_y + 1) == '@' || getWellChar(piece_x, piece_y + 1) == '$' || getWellChar(piece_x, piece_y + 1) == '*')
		return false;

	return true;
}

bool Well::validRotateF(Pieces* f_piece) { return true; }

bool Well::validAddF(Pieces* f_piece) {
	f_piece->orientation0();
	for (int x = 4; x <= 7; x++) {
		for (int y = 0; y <= 3; y++) { // Starting position of bounding box is X=3, Y= 0 (which is X=4, Y=0 in the wellGrid)
			if ((f_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '$') || (f_piece->getChar(x - 4, y) == '#' && getWellChar(x, y) == '*'))
				return false;
		}
	}
	return true;
}

void Well::finishPieceF(Pieces* f_piece, int foamX, int foamY, int upLimit, int downLimit, int leftLimit, int rightLimit) {
	int x = foamX;
	int y = foamY;
	int up = upLimit;
	int down = downLimit;
	int left = leftLimit;
	int right = rightLimit;

	if (up < 0)
		up = 0;
	if (down > 17)
		down = 17;
	if (left < 1)
		left = 1;
	if (right > 10)
		right = 10;

	if (foamX < left || foamX > right || foamY < up || foamY > down)
		return;

	setWellChar(x, y, '*'); // Mark the start location as visited! (Mark the future "start" positions as visited too via recursion!) 

	if (getWellChar(x, y-1) == ' ') { // NORTH
		finishPieceF(f_piece, x, y - 1, up, down, left, right);
	}
	if (getWellChar(x+1, y) == ' ') { // WEST
		finishPieceF(f_piece, x + 1, y, up, down, left, right);
	}
	if (getWellChar(x, y+1) == ' ') { // SOUTH
		finishPieceF(f_piece, x, y + 1, up, down, left, right);
	}
	if (getWellChar(x-1, y) == ' ') { // EAST
		finishPieceF(f_piece, x - 1, y, up, down, left, right);
	}
}