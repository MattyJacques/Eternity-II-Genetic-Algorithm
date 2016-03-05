// Title        : Mutation.cpp
// Purpose      : Mutates random boards using various methods
// Author       : Matthew Jacques
// Date         : 23/01/2016


#include "Mutation.h"
#include "GeneticAlgorithm.h" // Get random number
#include <iostream>           // Debug output


Mutation::Mutation()
{ // Initialise mutation method

  mutType = SWAP;

} // Mutation()


void Mutation::CalcMutRate(double rate, int popSize)
{ // Calculates how many mutations to implement per generation

  mutNum = (rate * popSize) / 100;

} // CalcMutRate()


void Mutation::GetRandPiece(int index[2], PieceType type)
{ // Sets the 2 dimensional index for a random piece with the type given
  // as a parameter

  if (type == CORNER)
  { // If the type of piece needs to be a corner, generation a random number
    // between 0 and 3, to randomly select which corner
    int cornerID = GeneticAlgorithm::GenRandomNum(0, 3);

    if (cornerID == 0)
    { // Set index to top left corner
      index[0] = 0;
      index[1] = 0;
    }
    else if (cornerID == 1)
    { // Set index to top right corner
      index[0] = 0;
      index[1] = BoardManager::GetInstance()->boardSize;
    }
    else if (cornerID == 2)
    { // Set index to bottom left corner
      index[0] = BoardManager::GetInstance()->boardSize;
      index[1] = 0;
    }
    else
    { // Set index to bottom right corner
      index[0] = BoardManager::GetInstance()->boardSize;
      index[1] = BoardManager::GetInstance()->boardSize;
    }
  }
  else if (type == EDGE)
  { // Set the indexs in the array to two index taken from the top, right, left
    // or bottom edges. The edge is randomly selected then select random piece
    // from chosen edge
    int mode = GeneticAlgorithm::GenRandomNum(0, 3);

    if (mode == 0)
    { // If mode is top edge set Y index to 0 and gen random index between
      // 1 and boardSize - 1 for X index
      index[0] = 0;
      index[1] = GeneticAlgorithm::GenRandomNum(1, BoardManager::GetInstance()->
                                                boardSize - 1);
    }
    else if (mode == 1)
    { // If mode is left edge gen random Y index between 1 and boardsize -1
      // and set X index to 0
      index[0] = GeneticAlgorithm::GenRandomNum(1, BoardManager::GetInstance()->
                                                boardSize - 1);
      index[1] = 0;
    }
    else if (mode == 2)
    { // If mode is right edge gen random number between 1 and boardSize - 1
      // and set X index to boardSize
      index[0] = GeneticAlgorithm::GenRandomNum(1, BoardManager::GetInstance()->
                                                boardSize - 1);
      index[1] = BoardManager::GetInstance()->boardSize;
    }
    else
    { // If mode is bottom edge set Y index to boardSize and gen random number
      // between 1 and boardSize - 1 for X index
      index[0] = BoardManager::GetInstance()->boardSize;
      index[1] = GeneticAlgorithm::GenRandomNum(1, BoardManager::GetInstance()->
                                                boardSize - 1);
    }
  }
  else
  { // Set the indexs in the array to two random number between 1 and the size
    // of the board - 1 to get two inner type pieces
    index[0] = GeneticAlgorithm::GenRandomNum(1, BoardManager::GetInstance()->
                                              boardSize - 1);
    index[1] = GeneticAlgorithm::GenRandomNum(1, BoardManager::GetInstance()->
                                              boardSize - 1);
  }

} // GetRandPiece()


void Mutation::Swap(int boardID)
{ // Swaps two random pieces in the board that has the ID given as the parameter

  int pieceIndex1[2];     // Holds index of the first piece
  int pieceIndex2[2];     // Holds index of second piece
  PuzzlePiece temp;       // Temp puzzle piece to use during the swap

  // Create pointer to board to work with and initalise to point to board
  Board* pBoard = &BoardManager::GetInstance()->currBoards->at(boardID);

  // Get random piece type for mutation, get a two random pieces of that type
  PieceType type = (PieceType)GeneticAlgorithm::GenRandomNum(0, 2);
  GetRandPiece(pieceIndex1, type);
  GetRandPiece(pieceIndex2, type);

  // Move puzzle piece to temp storage
  temp = pBoard->boardVec[pieceIndex1[0]][pieceIndex1[1]];

  // Place the second puzzle piece where first puzzle piece was located
  pBoard->boardVec[pieceIndex1[0]][pieceIndex1[1]] =
    pBoard->boardVec[pieceIndex2[0]][pieceIndex2[1]];

  // Place first puzzle piece back in second puzzle piece slot
  pBoard->boardVec[pieceIndex2[0]][pieceIndex2[1]] = temp;

} // Swap()


void Mutation::Setup(MutateType type, double rate, int popSize)
{ // Sets the method of mutation to use for this attempt

  mutType = type;                 // Set mutation method
  CalcMutRate(rate, popSize);     // Calc how many mutation per generation

} // SetMethod()


void Mutation::DoMutation()
{ // Randomly selects a board from the current population to be mutated
  // then calls the appropriate subprogram that will do the needed mutation
  // method on that board.

  for (int i = 0; i < mutNum; i++)
  { // Loop through to complete as many mutations as was calcualted on 
    // application start up


    // Get a random board ID to complete mutation on
    int boardID = GeneticAlgorithm::GenRandomNum(0, (int)BoardManager::GetInstance()
                                                ->currBoards->size() - 1);

    if (mutType == SWAP)   // If mutation method is swap, do swap
      Swap(boardID);
    //else if (mutType == ROTATE)
    //  Rotate();
    //else if (mutType == ROTATESWAP)
    //  RotateSwap();
    //else if (mutType == REGIONSWAP)
    //  RegionSwap();
    //else if (mutType == REGIONROTATE)
    //  RegionRotate();
    else                  // Mutation method not recognised, output error
      std::cout << "Mutation method not recognised" << std::endl;

  }

} // DoMutation()
