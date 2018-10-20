#include "Game.h"
#include "UserInterface.h"
#include <string>
#include <iostream>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
	: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_well(width, height) // added m_well construction!
{}

Game::~Game() {
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

void Game::play()
{
	m_well.initiateGrid();
    m_well.display(m_screen, WELL_X, WELL_Y); // Screen member object, and default WELL_X (0) and default WELL_Y (0)
											  // Displays the well

	displayStatus();  //  score, rows left, level
	displayPrompt("Press the Enter key to begin playing Chetyris!");
	waitForEnter();  // [in UserInterface.h]

	while (!quit) {
			if (!playOneLevel())
				break;
			displayPrompt("Good job!  Press the Enter key to start next level!");
			waitForEnter();
			m_well.initiateGrid();
			++m_level;
			rowsDeleted = 0;
			displayStatus();
	}
	
	pieceQueue.clear();
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
	m_screen.refresh();
}

void Game::displayStatus()
{
	m_screen.gotoXY(SCORE_X, SCORE_Y);
	m_screen.printStringClearLine("Score: ");

	m_screen.gotoXY(SCORE_X + 7, SCORE_Y);
	std::string score = std::to_string(totalScore);
	m_screen.printStringClearLine(score);
	m_screen.refresh();

	m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
	m_screen.printStringClearLine("Rows left: ");
	m_screen.gotoXY(ROWS_LEFT_X+11, ROWS_LEFT_Y);
	std::string rows = std::to_string((m_level * 5) - rowsDeleted);
	if (((m_level * 5) - rowsDeleted) > 0)
		m_screen.printStringClearLine(rows);
	else
		m_screen.printChar('0');
	m_screen.refresh();

	m_screen.gotoXY(LEVEL_X, LEVEL_Y);
	m_screen.printStringClearLine("Level: ");

	m_screen.gotoXY(LEVEL_X + 7, LEVEL_Y);
	std::string level = std::to_string(m_level);
	m_screen.printStringClearLine(level);
	m_screen.refresh();
}

void Game::displayNextPiece() {
	m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
	m_screen.printStringClearLine("Next piece: ");
	m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
	switch (pieceQueue.front()) {
	case PIECE_I:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printStringClearLine("####");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
		m_screen.printStringClearLine("");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
		m_screen.printStringClearLine("");
		break;
	case PIECE_L:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printStringClearLine("###");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
		m_screen.printStringClearLine("#");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
		m_screen.printStringClearLine("");
		break;
	case PIECE_J:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printStringClearLine(" ###");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
		m_screen.printStringClearLine("   #");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
		m_screen.printStringClearLine("");
		break;
	case PIECE_T:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
		m_screen.printStringClearLine(" #  ");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printStringClearLine("###");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
		m_screen.printStringClearLine("");
		break;
	case PIECE_O:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
		m_screen.printStringClearLine("##");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printStringClearLine("##");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
		m_screen.printStringClearLine("");
		break;
	case PIECE_S:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printStringClearLine(" ##");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
		m_screen.printStringClearLine("##");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
		m_screen.printStringClearLine("");
		break;
	case PIECE_Z:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printStringClearLine("##");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
		m_screen.printStringClearLine(" ##");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
		m_screen.printStringClearLine("");
		break;
	case PIECE_CRAZY:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printStringClearLine(" ## ");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
		m_screen.printStringClearLine("#  #");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
		m_screen.printStringClearLine("");
		break;
	case PIECE_VAPOR:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printStringClearLine("");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
		m_screen.printStringClearLine(" ## ");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
		m_screen.printStringClearLine("");
		break;
	case PIECE_FOAM:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printStringClearLine(" #");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
		m_screen.printStringClearLine("");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
		m_screen.printStringClearLine("");
		break;
	}
	m_screen.refresh();
}

bool Game::playOneLevel()
{
	rowsDeleted = 0;
	bool success = false;
	int current = m_level * 5;
	int rowCombo = 0;
	bool gameValid = true;

	while (rowsDeleted < current && gameValid) {
		PieceType next = chooseRandomPieceType();
		if (pieceQueue.empty())
			pieceQueue.push_front(next);
		switch (pieceQueue.front()) {
		case PIECE_I:
			pieceQueue.pop_front();
			pieceQueue.push_back(chooseRandomPieceType());
			displayNextPiece();
			if (m_well.validAddI(i_piece)) {
				m_well.addPIECEI(i_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				playPieceI(i_piece);
				if (quit)
					return false;
			}
			else
				gameValid = false;
			m_well.display(m_screen, WELL_X, WELL_Y);
			break;
		case PIECE_L:
			pieceQueue.pop_front();
			pieceQueue.push_back(chooseRandomPieceType());
			displayNextPiece();
			if (m_well.validAddL(l_piece)) {
				m_well.addPIECEL(l_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				playPieceL(l_piece);
				if (quit)
					return false;
			}
			else
				gameValid = false;
			m_well.display(m_screen, WELL_X, WELL_Y);
			break;
		case PIECE_O:
			pieceQueue.pop_front();
			pieceQueue.push_back(chooseRandomPieceType());
			displayNextPiece();
			if (m_well.validAddO(o_piece)) {
				m_well.addPIECEO(o_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				playPieceO(o_piece);
				if (quit)
					return false;
			}
			else
				gameValid = false;
			m_well.display(m_screen, WELL_X, WELL_Y);
			break;
		case PIECE_J:
			pieceQueue.pop_front();
			pieceQueue.push_back(chooseRandomPieceType());
			displayNextPiece();
			if (m_well.validAddJ(j_piece)) {
				m_well.addPIECEJ(j_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				playPieceJ(j_piece);
				if (quit)
					return false;
			}
			else
				gameValid = false;
			m_well.display(m_screen, WELL_X, WELL_Y);
			break;
		case PIECE_T:
			pieceQueue.pop_front();
			pieceQueue.push_back(chooseRandomPieceType());
			displayNextPiece();
			if (m_well.validAddT(t_piece)) {
				m_well.addPIECET(t_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				playPieceT(t_piece);
				if (quit)
					return false;
			}
			else
				gameValid = false;
			m_well.display(m_screen, WELL_X, WELL_Y);
			break;
		case PIECE_S:
			pieceQueue.pop_front();
			pieceQueue.push_back(chooseRandomPieceType());
			displayNextPiece();
			if (m_well.validAddS(s_piece)) {
				m_well.addPIECES(s_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				playPieceS(s_piece);
				if (quit)
					return false;
			}
			else
				gameValid = false;
			m_well.display(m_screen, WELL_X, WELL_Y);
			break;
		case PIECE_Z:
			pieceQueue.pop_front();
			pieceQueue.push_back(chooseRandomPieceType());
			displayNextPiece();
			if (m_well.validAddZ(z_piece)) {
				m_well.addPIECEZ(z_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				playPieceZ(z_piece);
				if (quit)
					return false;
			}
			else
				gameValid = false;
			m_well.display(m_screen, WELL_X, WELL_Y);
			break;
		case PIECE_CRAZY:
			pieceQueue.pop_front();
			pieceQueue.push_back(chooseRandomPieceType());
			displayNextPiece();
			if (m_well.validAddC(c_piece)) {
				m_well.addPIECEC(c_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				playPieceC(c_piece);
				if (quit)
					return false;
			}
			else
				gameValid = false;
			m_well.display(m_screen, WELL_X, WELL_Y);
			break;
		case PIECE_VAPOR:
			pieceQueue.pop_front();
			pieceQueue.push_back(chooseRandomPieceType());
			displayNextPiece();
			if (m_well.validAddV(v_piece)) {
				m_well.addPIECEV(v_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				playPieceV(v_piece);
				if (quit)
					return false;
			}
			else
				gameValid = false;
			m_well.display(m_screen, WELL_X, WELL_Y);
			break;
		case PIECE_FOAM:
			pieceQueue.pop_front();
			pieceQueue.push_back(chooseRandomPieceType());
			displayNextPiece();
			if (m_well.validAddF(f_piece)) {
				m_well.addPIECEF(f_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				playPieceF(f_piece);
				if (quit)
					return false;
			}
			else
				gameValid = false;
			m_well.display(m_screen, WELL_X, WELL_Y);
		break;
		}
		for (int x = 17; x >= 0; x--) {
			if (m_well.fullWellRow(x)) {
				m_well.emptyWellRow(x);
				++rowsDeleted;
				++rowCombo;
			}
		}
		for (int x = 17; x >= 0; x--) {
			if (m_well.fullWellRow(x)) {
				m_well.emptyWellRow(x);
				++rowsDeleted;
				++rowCombo;
			}
		}
		for (int x = 17; x >= 0; x--) {
			if (m_well.fullWellRow(x)) {
				m_well.emptyWellRow(x);
				++rowsDeleted;
				++rowCombo;
			}
		}
		for (int x = 17; x >= 0; x--) {
			if (m_well.fullWellRow(x)) {
				m_well.emptyWellRow(x);
				++rowsDeleted;
				++rowCombo;
			}
		}
		for (int x = 17; x >= 0; x--) {
			if (m_well.fullWellRow(x)) {
				m_well.emptyWellRow(x);
				++rowsDeleted;
				++rowCombo;
			}
		}
		switch (rowCombo) {
		case 0:
			break;
		case 1:
			totalScore += 100;
			break;
		case 2:
			totalScore += 200;
			break;
		case 3:
			totalScore += 400;
			break;
		case 4:
			totalScore += 800;
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			totalScore += 1600;
			break;
		}
		displayStatus();
		m_screen.refresh();
		rowCombo = 0;
	}

	if (rowsDeleted >= current)
		success = true;

	// if well fills to the top or piece is unable to be dropped due to space in bounded box being filled, LOSE

	return success;
}

void Game::playPieceI(Pieces* i_piece) {
	while (m_well.validMoveDownI(i_piece)) {
		// Start a timer
		Timer timer;
		// Repeat as long as 2000 milliseconds have not yet elapsed
		while (timer.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom && !bypassTimer)
		{
			char ch;
			if (getCharIfAny(ch))
			{
				// There was a character typed; it's now in ch
				switch (ch)
				{
				case 'q':
				case 'Q':
					quit = true;
					break;
				case ' ':
					while (m_well.validMoveDownI(i_piece))
						m_well.dropPIECEI(i_piece);
					notAtBottom = false; // to counteract delay of 2000ms
					break;
				case 'a':
				case ARROW_LEFT: // LEFT
					if (m_well.validMoveLeftI(i_piece))
						m_well.moveLeftPIECEI(i_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case'd':
				case ARROW_RIGHT: // RIGHT
					if (m_well.validMoveRightI(i_piece))
						m_well.moveRightPIECEI(i_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 's':
				case ARROW_DOWN: // DOWN
					if (m_well.validMoveDownI(i_piece))
						m_well.dropPIECEI(i_piece);
					if (m_well.validMoveDownI(i_piece) == false)
						bypassTimer = true;
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 'w':
				case ARROW_UP: // ROTATE
					if (m_well.validRotateI(i_piece))
						m_well.rotatePIECEI(i_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				}
				if (quit)
					break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
		bypassTimer = false;
		// 2 seconds have elapsed
		if (m_well.validMoveDownI(i_piece))
			m_well.dropPIECEI(i_piece);
		m_well.display(m_screen, WELL_X, WELL_Y);
	}
	if (quit)
		return;

	Timer timer2;
	while (timer2.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom) // For last second moves (a.k.a. when the piece is about to hit the bottom point)
	{
		char ch;
		if (getCharIfAny(ch))
		{
			// There was a character typed; it's now in ch
			switch (ch)
			{
			case 'q':
			case 'Q':
				quit = true;
				break;
			case ' ':
				notAtBottom = false;
				break;
			case 'a':
			case ARROW_LEFT: // LEFT
				if (m_well.validMoveLeftI(i_piece))
					m_well.moveLeftPIECEI(i_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case'd':
			case ARROW_RIGHT: // RIGHT
				if (m_well.validMoveRightI(i_piece))
					m_well.moveRightPIECEI(i_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case 's':
			case ARROW_DOWN: // DOWN
				if (m_well.validMoveDownI(i_piece))
					m_well.dropPIECEI(i_piece);
				notAtBottom = false;
				break;
			case 'w':
			case ARROW_UP: // ROTATE
				if (m_well.validRotateI(i_piece))
					m_well.rotatePIECEI(i_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
	}
	if (quit)
		return;
	// 2 seconds have elapsed
	if (m_well.validMoveDownI(i_piece))
		m_well.dropPIECEI(i_piece);
	m_well.display(m_screen, WELL_X, WELL_Y);

	if (m_well.validMoveDownI(i_piece)) // Recursion!
		playPieceI(i_piece);			// Recursion!
	m_well.finishPieceI(i_piece);
	notAtBottom = true;
	m_well.display(m_screen, WELL_X, WELL_Y);
}

void Game::playPieceL(Pieces* l_piece) {
	while (m_well.validMoveDownL(l_piece)) {
		// Start a timer
		Timer timer;
		// Repeat as long as 2000 milliseconds have not yet elapsed
		while (timer.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom && !bypassTimer)
		{
			char ch;
			if (getCharIfAny(ch))
			{
				// There was a character typed; it's now in ch
				switch (ch)
				{
				case 'q':
				case 'Q':
					quit = true;
					break;
				case ' ':
					while (m_well.validMoveDownL(l_piece))
						m_well.dropPIECEL(l_piece);
					notAtBottom = false; // to counteract delay of 2000ms
					break;
				case 'a':
				case ARROW_LEFT: // LEFT
					if (m_well.validMoveLeftL(l_piece))
						m_well.moveLeftPIECEL(l_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case'd':
				case ARROW_RIGHT: // RIGHT
					if (m_well.validMoveRightL(l_piece))
						m_well.moveRightPIECEL(l_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 's':
				case ARROW_DOWN: // DOWN
					if (m_well.validMoveDownL(l_piece))
						m_well.dropPIECEL(l_piece);
					if (m_well.validMoveDownL(l_piece) == false)
						bypassTimer = true;
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 'w':
				case ARROW_UP: // ROTATE
					if (m_well.validRotateL(l_piece))
						m_well.rotatePIECEL(l_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				}
				if (quit)
					break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
		bypassTimer = false;
		// 2 seconds have elapsed
		if (m_well.validMoveDownL(l_piece))
			m_well.dropPIECEL(l_piece);
		m_well.display(m_screen, WELL_X, WELL_Y);
	}
	if (quit)
		return;

	Timer timer2;
	while (timer2.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom) // For last second moves (a.k.a. when the piece is about to hit the bottom point)
	{
		char ch;
		if (getCharIfAny(ch))
		{
			// There was a character typed; it's now in ch
			switch (ch)
			{
			case 'q':
			case 'Q':
				quit = true;
				break;
			case ' ':
				notAtBottom = false;
				break;
			case 'a':
			case ARROW_LEFT: // LEFT
				if (m_well.validMoveLeftL(l_piece))
					m_well.moveLeftPIECEL(l_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case'd':
			case ARROW_RIGHT: // RIGHT
				if (m_well.validMoveRightL(l_piece))
					m_well.moveRightPIECEL(l_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case 's':
			case ARROW_DOWN: // DOWN
				if (m_well.validMoveDownL(l_piece))
					m_well.dropPIECEL(l_piece);
				notAtBottom = false;
				break;
			case 'w':
			case ARROW_UP: // ROTATE
				if (m_well.validRotateL(l_piece))
					m_well.rotatePIECEL(l_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
	}
	if (quit)
		return;
	// 2 seconds have elapsed
	if (m_well.validMoveDownL(l_piece))
		m_well.dropPIECEL(l_piece);
	m_well.display(m_screen, WELL_X, WELL_Y);

	if (m_well.validMoveDownL(l_piece)) // Recursion!
		playPieceL(l_piece);			// Recursion!
	m_well.finishPieceL(l_piece);
	notAtBottom = true;
	m_well.display(m_screen, WELL_X, WELL_Y);
}

void Game::playPieceO(Pieces* o_piece) {
	while (m_well.validMoveDownO(o_piece)) {
		// Start a timer
		Timer timer;
		// Repeat as long as 2000 milliseconds have not yet elapsed
		while (timer.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom && !bypassTimer)
		{
			char ch;
			if (getCharIfAny(ch))
			{
				// There was a character typed; it's now in ch
				switch (ch)
				{
				case 'q':
				case 'Q':
					quit = true;
					break;
				case ' ':
					while (m_well.validMoveDownO(o_piece))
						m_well.dropPIECEO(o_piece);
					notAtBottom = false; // to counteract delay of 2000ms
					break;
				case 'a':
				case ARROW_LEFT: // LEFT
					if (m_well.validMoveLeftO(o_piece))
						m_well.moveLeftPIECEO(o_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case'd':
				case ARROW_RIGHT: // RIGHT
					if (m_well.validMoveRightO(o_piece))
						m_well.moveRightPIECEO(o_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 's':
				case ARROW_DOWN: // DOWN
					if (m_well.validMoveDownO(o_piece))
						m_well.dropPIECEO(o_piece);
					if (m_well.validMoveDownO(o_piece) == false)
						bypassTimer = true;
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 'w':
				case ARROW_UP: // ROTATE
					if (m_well.validRotateO(o_piece))
						m_well.rotatePIECEO(o_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				}
				if (quit)
					break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
		bypassTimer = false;
		// 2 seconds have elapsed
		if (m_well.validMoveDownO(o_piece))
			m_well.dropPIECEO(o_piece);
		m_well.display(m_screen, WELL_X, WELL_Y);
	}
	if (quit)
		return;

	Timer timer2;
	while (timer2.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom) // For last second moves (a.k.a. when the piece is about to hit the bottom point)
	{
		char ch;
		if (getCharIfAny(ch))
		{
			// There was a character typed; it's now in ch
			switch (ch)
			{
			case 'q':
			case 'Q':
				quit = true;
				break;
			case ' ':
				notAtBottom = false;
				break;
			case 'a':
			case ARROW_LEFT: // LEFT
				if (m_well.validMoveLeftO(o_piece))
					m_well.moveLeftPIECEO(o_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case'd':
			case ARROW_RIGHT: // RIGHT
				if (m_well.validMoveRightO(o_piece))
					m_well.moveRightPIECEO(o_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case 's':
			case ARROW_DOWN: // DOWN
				if (m_well.validMoveDownO(o_piece))
					m_well.dropPIECEO(o_piece);
				notAtBottom = false;
				break;
			case 'w':
			case ARROW_UP: // ROTATE
				if (m_well.validRotateO(o_piece))
					m_well.rotatePIECEO(o_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
	}
	if (quit)
		return;
	// 2 seconds have elapsed
	if (m_well.validMoveDownO(o_piece))
		m_well.dropPIECEO(o_piece);
	m_well.display(m_screen, WELL_X, WELL_Y);

	if (m_well.validMoveDownO(o_piece)) // Recursion!
		playPieceO(o_piece);			// Recursion!
	m_well.finishPieceO(o_piece);
	notAtBottom = true;
	m_well.display(m_screen, WELL_X, WELL_Y);
}

void Game::playPieceJ(Pieces* j_piece) {
	while (m_well.validMoveDownJ(j_piece)) {
		// Start a timer
		Timer timer;
		// Repeat as long as 2000 milliseconds have not yet elapsed
		while (timer.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom && !bypassTimer)
		{
			char ch;
			if (getCharIfAny(ch))
			{
				// There was a character typed; it's now in ch
				switch (ch)
				{
				case 'q':
				case 'Q':
					quit = true;
					break;
				case ' ':
					while (m_well.validMoveDownJ(j_piece))
						m_well.dropPIECEJ(j_piece);
					notAtBottom = false; // to counteract delay of 2000ms
					break;
				case 'a':
				case ARROW_LEFT: // LEFT
					if (m_well.validMoveLeftJ(j_piece))
						m_well.moveLeftPIECEJ(j_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case'd':
				case ARROW_RIGHT: // RIGHT
					if (m_well.validMoveRightJ(j_piece))
						m_well.moveRightPIECEJ(j_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 's':
				case ARROW_DOWN: // DOWN
					if (m_well.validMoveDownJ(j_piece))
						m_well.dropPIECEJ(j_piece);
					if (m_well.validMoveDownJ(j_piece) == false)
						bypassTimer = true;
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 'w':
				case ARROW_UP: // ROTATE
					if (m_well.validRotateJ(j_piece))
						m_well.rotatePIECEJ(j_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				}
				if (quit)
					break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
		bypassTimer = false;
		// 2 seconds have elapsed
		if (m_well.validMoveDownJ(j_piece))
			m_well.dropPIECEJ(j_piece);
		m_well.display(m_screen, WELL_X, WELL_Y);
	}
	if (quit)
		return;

	Timer timer2;
	while (timer2.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom) // For last second moves (a.k.a. when the piece is about to hit the bottom point)
	{
		char ch;
		if (getCharIfAny(ch))
		{
			// There was a character typed; it's now in ch
			switch (ch)
			{
			case 'q':
			case 'Q':
				quit = true;
				break;
			case ' ':
				notAtBottom = false;
				break;
			case 'a':
			case ARROW_LEFT: // LEFT
				if (m_well.validMoveLeftJ(j_piece))
					m_well.moveLeftPIECEJ(j_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case'd':
			case ARROW_RIGHT: // RIGHT
				if (m_well.validMoveRightJ(j_piece))
					m_well.moveRightPIECEJ(j_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case 's':
			case ARROW_DOWN: // DOWN
				if (m_well.validMoveDownJ(j_piece))
					m_well.dropPIECEJ(j_piece);
				notAtBottom = false;
				break;
			case 'w':
			case ARROW_UP: // ROTATE
				if (m_well.validRotateJ(j_piece))
					m_well.rotatePIECEJ(j_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
	}
	if (quit)
		return;
	// 2 seconds have elapsed
	if (m_well.validMoveDownJ(j_piece))
		m_well.dropPIECEJ(j_piece);
	m_well.display(m_screen, WELL_X, WELL_Y);

	if (m_well.validMoveDownJ(j_piece)) // Recursion!
		playPieceJ(j_piece);			// Recursion!
	m_well.finishPieceJ(j_piece);
	notAtBottom = true;
	m_well.display(m_screen, WELL_X, WELL_Y);
}

void Game::playPieceT(Pieces* t_piece) {
	while (m_well.validMoveDownT(t_piece)) {
		// Start a timer
		Timer timer;
		// Repeat as long as 2000 milliseconds have not yet elapsed
		while (timer.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom && !bypassTimer)
		{
			char ch;
			if (getCharIfAny(ch))
			{
				// There was a character typed; it's now in ch
				switch (ch)
				{
				case 'q':
				case 'Q':
					quit = true;
					break;
				case ' ':
					while (m_well.validMoveDownT(t_piece))
						m_well.dropPIECET(t_piece);
					notAtBottom = false; // to counteract delay of 2000ms
					break;
				case 'a':
				case ARROW_LEFT: // LEFT
					if (m_well.validMoveLeftT(t_piece))
						m_well.moveLeftPIECET(t_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case'd':
				case ARROW_RIGHT: // RIGHT
					if (m_well.validMoveRightT(t_piece))
						m_well.moveRightPIECET(t_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 's':
				case ARROW_DOWN: // DOWN
					if (m_well.validMoveDownT(t_piece))
						m_well.dropPIECET(t_piece);
					if (m_well.validMoveDownT(t_piece) == false)
						bypassTimer = true;
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 'w':
				case ARROW_UP: // ROTATE
					if (m_well.validRotateT(t_piece))
						m_well.rotatePIECET(t_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				}
				if (quit)
					break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
		bypassTimer = false;
		// 2 seconds have elapsed
		if (m_well.validMoveDownT(t_piece))
			m_well.dropPIECET(t_piece);
		m_well.display(m_screen, WELL_X, WELL_Y);
	}
	if (quit)
		return;

	Timer timer2;
	while (timer2.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom) // For last second moves (a.k.a. when the piece is about to hit the bottom point)
	{
		char ch;
		if (getCharIfAny(ch))
		{
			// There was a character typed; it's now in ch
			switch (ch)
			{
			case 'q':
			case 'Q':
				quit = true;
				break;
			case ' ':
				notAtBottom = false;
				break;
			case 'a':
			case ARROW_LEFT: // LEFT
				if (m_well.validMoveLeftT(t_piece))
					m_well.moveLeftPIECET(t_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case'd':
			case ARROW_RIGHT: // RIGHT
				if (m_well.validMoveRightT(t_piece))
					m_well.moveRightPIECET(t_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case 's':
			case ARROW_DOWN: // DOWN
				if (m_well.validMoveDownT(t_piece))
					m_well.dropPIECET(t_piece);
				notAtBottom = false;
				break;
			case 'w':
			case ARROW_UP: // ROTATE
				if (m_well.validRotateT(t_piece))
					m_well.rotatePIECET(t_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
	}
	if (quit)
		return;
	// 2 seconds have elapsed
	if (m_well.validMoveDownT(t_piece))
		m_well.dropPIECET(t_piece);
	m_well.display(m_screen, WELL_X, WELL_Y);

	if (m_well.validMoveDownT(t_piece)) // Recursion!
		playPieceT(t_piece);			// Recursion!
	m_well.finishPieceT(t_piece);
	notAtBottom = true;
	m_well.display(m_screen, WELL_X, WELL_Y);
}

void Game::playPieceS(Pieces* s_piece) {
	while (m_well.validMoveDownS(s_piece)) {
		// Start a timer
		Timer timer;
		// Repeat as long as 2000 milliseconds have not yet elapsed
		while (timer.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom && !bypassTimer)
		{
			char ch;
			if (getCharIfAny(ch))
			{
				// There was a character typed; it's now in ch
				switch (ch)
				{
				case 'q':
				case 'Q':
					quit = true;
					break;
				case ' ':
					while (m_well.validMoveDownS(s_piece))
						m_well.dropPIECES(s_piece);
					notAtBottom = false; // to counteract delay of 2000ms
					break;
				case 'a':
				case ARROW_LEFT: // LEFT
					if (m_well.validMoveLeftS(s_piece))
						m_well.moveLeftPIECES(s_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case'd':
				case ARROW_RIGHT: // RIGHT
					if (m_well.validMoveRightS(s_piece))
						m_well.moveRightPIECES(s_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 's':
				case ARROW_DOWN: // DOWN
					if (m_well.validMoveDownS(s_piece))
						m_well.dropPIECES(s_piece);
					if (m_well.validMoveDownS(s_piece) == false)
						bypassTimer = true;
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 'w':
				case ARROW_UP: // ROTATE
					if (m_well.validRotateS(s_piece))
						m_well.rotatePIECES(s_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				}
				if (quit)
					break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
		bypassTimer = false;
		// 2 seconds have elapsed
		if (m_well.validMoveDownS(s_piece))
			m_well.dropPIECES(s_piece);
		m_well.display(m_screen, WELL_X, WELL_Y);
	}
	if (quit)
		return;

	Timer timer2;
	while (timer2.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom) // For last second moves (a.k.a. when the piece is about to hit the bottom point)
	{
		char ch;
		if (getCharIfAny(ch))
		{
			// There was a character typed; it's now in ch
			switch (ch)
			{
			case 'q':
			case 'Q':
				quit = true;
				break;
			case ' ':
				notAtBottom = false;
				break;
			case 'a':
			case ARROW_LEFT: // LEFT
				if (m_well.validMoveLeftS(s_piece))
					m_well.moveLeftPIECES(s_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case'd':
			case ARROW_RIGHT: // RIGHT
				if (m_well.validMoveRightS(s_piece))
					m_well.moveRightPIECES(s_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case 's':
			case ARROW_DOWN: // DOWN
				if (m_well.validMoveDownS(s_piece))
					m_well.dropPIECES(s_piece);
				notAtBottom = false;
				break;
			case 'w':
			case ARROW_UP: // ROTATE
				if (m_well.validRotateS(s_piece))
					m_well.rotatePIECES(s_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
	}
	if (quit)
		return;
	// 2 seconds have elapsed
	if (m_well.validMoveDownS(s_piece))
		m_well.dropPIECES(s_piece);
	m_well.display(m_screen, WELL_X, WELL_Y);

	if (m_well.validMoveDownS(s_piece)) // Recursion!
		playPieceS(s_piece);			// Recursion!
	m_well.finishPieceS(s_piece);
	notAtBottom = true;
	m_well.display(m_screen, WELL_X, WELL_Y);
}

void Game::playPieceZ(Pieces* z_piece) {
	while (m_well.validMoveDownZ(z_piece)) {
		// Start a timer
		Timer timer;
		// Repeat as long as 2000 milliseconds have not yet elapsed
		while (timer.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom && !bypassTimer)
		{
			char ch;
			if (getCharIfAny(ch))
			{
				// There was a character typed; it's now in ch
				switch (ch)
				{
				case 'q':
				case 'Q':
					quit = true;
					break;
				case ' ':
					while (m_well.validMoveDownZ(z_piece))
						m_well.dropPIECEZ(z_piece);
					notAtBottom = false; // to counteract delay of 2000ms
					break;
				case 'a':
				case ARROW_LEFT: // LEFT
					if (m_well.validMoveLeftZ(z_piece))
						m_well.moveLeftPIECEZ(z_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case'd':
				case ARROW_RIGHT: // RIGHT
					if (m_well.validMoveRightZ(z_piece))
						m_well.moveRightPIECEZ(z_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 's':
				case ARROW_DOWN: // DOWN
					if (m_well.validMoveDownZ(z_piece))
						m_well.dropPIECEZ(z_piece);
					if (m_well.validMoveDownZ(z_piece) == false)
						bypassTimer = true;
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 'w':
				case ARROW_UP: // ROTATE
					if (m_well.validRotateZ(z_piece))
						m_well.rotatePIECEZ(z_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				}
				if (quit)
					break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
		bypassTimer = false;
		// 2 seconds have elapsed
		if (m_well.validMoveDownZ(z_piece))
			m_well.dropPIECEZ(z_piece);
		m_well.display(m_screen, WELL_X, WELL_Y);
	}
	if (quit)
		return;

	Timer timer2;
	while (timer2.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom) // For last second moves (a.k.a. when the piece is about to hit the bottom point)
	{
		char ch;
		if (getCharIfAny(ch))
		{
			// There was a character typed; it's now in ch
			switch (ch)
			{
			case 'q':
			case 'Q':
				quit = true;
				break;
			case ' ':
				notAtBottom = false;
				break;
			case 'a':
			case ARROW_LEFT: // LEFT
				if (m_well.validMoveLeftZ(z_piece))
					m_well.moveLeftPIECEZ(z_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case'd':
			case ARROW_RIGHT: // RIGHT
				if (m_well.validMoveRightZ(z_piece))
					m_well.moveRightPIECEZ(z_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case 's':
			case ARROW_DOWN: // DOWN
				if (m_well.validMoveDownZ(z_piece))
					m_well.dropPIECEZ(z_piece);
				notAtBottom = false;
				break;
			case 'w':
			case ARROW_UP: // ROTATE
				if (m_well.validRotateZ(z_piece))
					m_well.rotatePIECEZ(z_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
	}
	if (quit)
		return;
	// 2 seconds have elapsed
	if (m_well.validMoveDownZ(z_piece))
		m_well.dropPIECEZ(z_piece);
	m_well.display(m_screen, WELL_X, WELL_Y);

	if (m_well.validMoveDownZ(z_piece)) // Recursion!
		playPieceZ(z_piece);			// Recursion!
	m_well.finishPieceZ(z_piece);
	notAtBottom = true;
	m_well.display(m_screen, WELL_X, WELL_Y);
}

void Game::playPieceC(Pieces* c_piece) {
	while (m_well.validMoveDownC(c_piece)) {
		// Start a timer
		Timer timer;
		// Repeat as long as 2000 milliseconds have not yet elapsed
		while (timer.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom && !bypassTimer)
		{
			char ch;
			if (getCharIfAny(ch))
			{
				// There was a character typed; it's now in ch
				switch (ch)
				{
				case 'q':
				case 'Q':
					quit = true;
					break;
				case ' ':
					while (m_well.validMoveDownC(c_piece))
						m_well.dropPIECEC(c_piece);
					notAtBottom = false; // to counteract delay of 2000ms
					break;
				case 'a':
				case ARROW_LEFT: // RIGHT (crazy)
					if (m_well.validMoveRightC(c_piece))
						m_well.moveRightPIECEC(c_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case'd':
				case ARROW_RIGHT: // LEFT (crazy)
					if (m_well.validMoveLeftC(c_piece))
						m_well.moveLeftPIECEC(c_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 's':
				case ARROW_DOWN: // DOWN
					if (m_well.validMoveDownC(c_piece))
						m_well.dropPIECEC(c_piece);
					if (m_well.validMoveDownC(c_piece) == false)
						bypassTimer = true;
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 'w':
				case ARROW_UP: // ROTATE
					if (m_well.validRotateC(c_piece))
						m_well.rotatePIECEC(c_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				}
				if (quit)
					break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
		bypassTimer = false;
		// 2 seconds have elapsed
		if (m_well.validMoveDownC(c_piece))
			m_well.dropPIECEC(c_piece);
		m_well.display(m_screen, WELL_X, WELL_Y);
	}
	if (quit)
		return;

	Timer timer2;
	while (timer2.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom) // For last second moves (a.k.a. when the piece is about to hit the bottom point)
	{
		char ch;
		if (getCharIfAny(ch))
		{
			// There was a character typed; it's now in ch
			switch (ch)
			{
			case 'q':
			case 'Q':
				quit = true;
				break;
			case ' ':
				notAtBottom = false;
				break;
			case 'a':
			case ARROW_LEFT: // RIGHT (crazy)
				if (m_well.validMoveRightC(c_piece))
					m_well.moveRightPIECEC(c_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case'd':
			case ARROW_RIGHT: // LEFT (crazy)
				if (m_well.validMoveLeftC(c_piece))
					m_well.moveLeftPIECEC(c_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case 's':
			case ARROW_DOWN: // DOWN
				if (m_well.validMoveDownC(c_piece))
					m_well.dropPIECEC(c_piece);
				notAtBottom = false;
				break;
			case 'w':
			case ARROW_UP: // ROTATE
				if (m_well.validRotateC(c_piece))
					m_well.rotatePIECEC(c_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
	}
	if (quit)
		return;
	// 2 seconds have elapsed
	if (m_well.validMoveDownC(c_piece))
		m_well.dropPIECEC(c_piece);
	m_well.display(m_screen, WELL_X, WELL_Y);

	if (m_well.validMoveDownC(c_piece)) // Recursion!
		playPieceC(c_piece);			// Recursion!
	m_well.finishPieceC(c_piece);
	notAtBottom = true;
	m_well.display(m_screen, WELL_X, WELL_Y);
}

void Game::playPieceV(Pieces* v_piece) {
	while (m_well.validMoveDownV(v_piece)) {
		// Start a timer
		Timer timer;
		// Repeat as long as 2000 milliseconds have not yet elapsed
		while (timer.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom && !bypassTimer)
		{
			char ch;
			if (getCharIfAny(ch))
			{
				// There was a character typed; it's now in ch
				switch (ch)
				{
				case 'q':
				case 'Q':
					quit = true;
					break;
				case ' ':
					while (m_well.validMoveDownV(v_piece))
						m_well.dropPIECEV(v_piece);
					notAtBottom = false; // to counteract delay of 2000ms
					break;
				case 'a':
				case ARROW_LEFT: // LEFT
					if (m_well.validMoveLeftV(v_piece))
						m_well.moveLeftPIECEV(v_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case'd':
				case ARROW_RIGHT: // RIGHT
					if (m_well.validMoveRightV(v_piece))
						m_well.moveRightPIECEV(v_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 's':
				case ARROW_DOWN: // DOWN
					if (m_well.validMoveDownV(v_piece))
						m_well.dropPIECEV(v_piece);
					if (m_well.validMoveDownV(v_piece) == false)
						bypassTimer = true;
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 'w':
				case ARROW_UP: // ROTATE
					if (m_well.validRotateV(v_piece))
						m_well.rotatePIECEV(v_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				}
				if (quit)
					break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
		bypassTimer = false;
		// 2 seconds have elapsed
		if (m_well.validMoveDownV(v_piece))
			m_well.dropPIECEV(v_piece);
		m_well.display(m_screen, WELL_X, WELL_Y);
	}
	if (quit)
		return;

	Timer timer2;
	while (timer2.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom) // For last second moves (a.k.a. when the piece is about to hit the bottom point)
	{
		char ch;
		if (getCharIfAny(ch))
		{
			// There was a character typed; it's now in ch
			switch (ch)
			{
			case 'q':
			case 'Q':
				quit = true;
				break;
			case ' ':
				notAtBottom = false;
				break;
			case 'a':
			case ARROW_LEFT: // LEFT
				if (m_well.validMoveLeftV(v_piece))
					m_well.moveLeftPIECEV(v_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case'd':
			case ARROW_RIGHT: // RIGHT
				if (m_well.validMoveRightV(v_piece))
					m_well.moveRightPIECEV(v_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case 's':
			case ARROW_DOWN: // DOWN
				if (m_well.validMoveDownV(v_piece))
					m_well.dropPIECEV(v_piece);
				notAtBottom = false;
				break;
			case 'w':
			case ARROW_UP: // ROTATE
				if (m_well.validRotateV(v_piece))
					m_well.rotatePIECEV(v_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
	}
	if (quit)
		return;
	// 2 seconds have elapsed
	if (m_well.validMoveDownV(v_piece))
		m_well.dropPIECEV(v_piece);
	m_well.display(m_screen, WELL_X, WELL_Y);

	if (m_well.validMoveDownV(v_piece)) // Recursion!
		playPieceV(v_piece);			// Recursion!
	m_well.finishPieceV(v_piece);
	notAtBottom = true;
	m_well.display(m_screen, WELL_X, WELL_Y);
}

void Game::playPieceF(Pieces* f_piece) {
	while (m_well.validMoveDownF(f_piece)) {
		// Start a timer
		Timer timer;
		// Repeat as long as 2000 milliseconds have not yet elapsed
		while (timer.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom && !bypassTimer)
		{
			char ch;
			if (getCharIfAny(ch))
			{
				// There was a character typed; it's now in ch
				switch (ch)
				{
				case 'q':
				case 'Q':
					quit = true;
					break;
				case ' ':
					while (m_well.validMoveDownF(f_piece))
						m_well.dropPIECEF(f_piece);
					notAtBottom = false; // to counteract delay of 2000ms
					break;
				case 'a':
				case ARROW_LEFT: // LEFT
					if (m_well.validMoveLeftF(f_piece))
						m_well.moveLeftPIECEF(f_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case'd':
				case ARROW_RIGHT: // RIGHT
					if (m_well.validMoveRightF(f_piece))
						m_well.moveRightPIECEF(f_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 's':
				case ARROW_DOWN: // DOWN
					if (m_well.validMoveDownF(f_piece))
						m_well.dropPIECEF(f_piece);
					if (m_well.validMoveDownF(f_piece) == false)
						bypassTimer = true;
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				case 'w':
				case ARROW_UP: // ROTATE
					if (m_well.validRotateF(f_piece))
						m_well.rotatePIECEF(f_piece);
					m_well.display(m_screen, WELL_X, WELL_Y);
					break;
				}
				if (quit)
					break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
		bypassTimer = false;
		// 2 seconds have elapsed
		if (m_well.validMoveDownF(f_piece))
			m_well.dropPIECEF(f_piece);
		m_well.display(m_screen, WELL_X, WELL_Y);
	}
	if (quit)
		return;

	Timer timer2;
	while (timer2.elapsed() < std::max(1000 - (100 * (m_level - 1)), 100) && notAtBottom) // For last second moves (a.k.a. when the piece is about to hit the bottom point)
	{
		char ch;
		if (getCharIfAny(ch))
		{
			// There was a character typed; it's now in ch
			switch (ch)
			{
			case 'q':
			case 'Q':
				quit = true;
				break;
			case ' ':
				notAtBottom = false;
				break;
			case 'a':
			case ARROW_LEFT: // LEFT
				if (m_well.validMoveLeftF(f_piece))
					m_well.moveLeftPIECEF(f_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case'd':
			case ARROW_RIGHT: // RIGHT
				if (m_well.validMoveRightF(f_piece))
					m_well.moveRightPIECEF(f_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			case 's':
			case ARROW_DOWN: // DOWN
				if (m_well.validMoveDownF(f_piece))
					m_well.dropPIECEF(f_piece);
				notAtBottom = false;
				break;
			case 'w':
			case ARROW_UP: // ROTATE
				if (m_well.validRotateF(f_piece))
					m_well.rotatePIECEF(f_piece);
				m_well.display(m_screen, WELL_X, WELL_Y);
				break;
			}
			if (quit)
				break;
		}
		if (quit)
			break;
	}
	if (quit)
		return;
	// 2 seconds have elapsed
	if (m_well.validMoveDownF(f_piece))
		m_well.dropPIECEF(f_piece);
	m_well.display(m_screen, WELL_X, WELL_Y);

	if (m_well.validMoveDownF(f_piece)) // Recursion!
		playPieceF(f_piece);			// Recursion!
	int foamX = f_piece->getX();
	int foamY = f_piece->getY();
	m_well.finishPieceF(f_piece, foamX + 1, foamY + 1, foamY - 1, foamY + 3, foamX - 1, foamX + 3);
	notAtBottom = true;
	m_well.display(m_screen, WELL_X, WELL_Y);
}