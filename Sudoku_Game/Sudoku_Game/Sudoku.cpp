#include <iostream> 
#include <fstream>

using namespace std;
int puzzle[9][9] = {0}, failCatch = 0, numUnfilled = 0;
int xPos = 0, yPos = 0, playVal = 0;
//const string fileName = "puzzle.txt"
char fileName[81];


int renderPuzzle(int[9][9]);

int entryVerifiy(int[9][9], int,int,int);

int readInPuzzle(int[9][9],char[81]);

int main()
{
	cout << "Please enter the name of the puzzle file: ";
	cin.getline(fileName, 81);
	//system("pause");
	failCatch = readInPuzzle(puzzle, fileName);
	if (failCatch == 1)
	{
		cout << "\nThe puzzle file could not be found...\n";
		system("pause");
		return 0;
	}
	//system("pause");
	do
	{
		numUnfilled = renderPuzzle(puzzle);
		//system("pause");
		cout << numUnfilled <<" unfilled positions remain!\n";
		//system("pause");
		
	if (numUnfilled != 0)
	{
		do
		{

			//If the user messed up entry, display error message and repromt.
			if (failCatch > 0){ cout << "That is not a legal move... Please re-enter.\n";}
			cout << "\nPlease enter a row, column and value to play: ";
			cin >> xPos >> yPos >> playVal;
			//system("pause");
			failCatch = entryVerifiy(puzzle, xPos, yPos, playVal);
		}while (failCatch > 0);
	}
		cout << "Good Move!\n";
		
		//reset failcatch flag
		failCatch = 0;

		//keep prompting until the user has won.
	}while (numUnfilled != 0);
	cout << "\n\nGame Over... A winner is you!\n";
	system("pause");
return 0;
}


int renderPuzzle(int puzzle[9][9])
{
	int numUnfilled = 0;
	cout <<"\n______________________________________________________________________________\n";									
	cout <<"\t0  \t1\t2\t3\t4\t5\t6\t7\t8\n";
	cout <<"_______________________________________________________________________________\n";

	for (int x=0; x<9; x++)
	{
		cout << x << " |\t";
		for (int y=0; y<9; y++)
		{
			if (puzzle[x][y] == 0)
			{
				cout << " \t";
				numUnfilled++;
			}
			else
			{
				cout << puzzle[x][y] << "\t";
			}
		}
		cout << "\n";
	}

	cout <<"_________________________________________\n\n";
	return numUnfilled;
}


int readInPuzzle(int puzzle[9][9], char fileName[81])
{
	ifstream inputFile;
	inputFile.open(fileName);

	//Verify that file name sent in was good. If not, return 1 for failure flag.
	if (inputFile.fail())
	{
		return 1;
	}

	else
	{

		//Start to read in puzzle. 
		for (int x=0; x < 9; x++)
		{
			for (int y=0; y < 9; y++)
			{
				inputFile >> puzzle[x][y];
			}
		}

		//Puzzle is read in. Close the file. 
		inputFile.close();
		return 0;
	}
}

//can only use numbers 1-9
//each row can only have 1 of each number 1-9
//
int entryVerifiy(int puzzle[9][9], int xPos, int yPos, int playVal)
{
	int failCatch = 0;
	int gridXPos, gridYPos; 
	
	//First, check row and column and playval for errorant input
	//system("pause");
	if ((xPos < 1)||(yPos < 1)||(xPos > 9)||(yPos > 9))
	{
		failCatch = 1;
		cout << "\nyour playVal cords are not in the right range\n";
		return failCatch;
	}
	
	//Now check if our playValue corridonates are pointing to an open playspace (=0)
	//system("pause");
	if(puzzle[xPos][yPos] != 0)
	{
		failCatch = 1;
		cout << "\nThere is already a value in the play cords!\n";
		cout <<"\n"<< xPos <<" "<<yPos <<"\n";
		return failCatch;
	}
	//Ypos is row xPos is coloum

	//Row Scan (accross)
	//system("pause");
	for (int y=0; y < 9; y++)
	{
		if (puzzle[xPos][y] == playVal)
		{
			failCatch = 1;
			cout << "\nRow Scan Fail.\n";
			return failCatch;
		}
	}
	

	//Column Scan (down)
	//system("pause");
	for (int x=0; x<9; x++)
	{
		if (puzzle[x][yPos] == playVal)
		{
			failCatch = 1;
			cout <<"\nColumn Scan Fail.\n";
			return failCatch;
		}
	}

	//3x3 Grid Scan
	//first, I want to find which of the 9 grids the playVal resides in.
	//first, I will treat the 9 3 by 3 grids as a 3 by 3 array
	//divide the search val's x and y by 3 to find the point in this grid, then use a series of case
	//statments to figure for each of the 9 grids where the search should start and end at. 
	gridXPos = xPos / 3;
	gridYPos = yPos / 3;

	//now, evaulate which grid the playVal is in, and set gridYPos and gridXPos to be
	//where we should start searching the 3 by 3 box (the upper left corner of it)
	//system("pause");
	 switch (gridXPos)
	 {
	 case 0:
		 {
			 if (gridYPos == 0){break;} //Already where we want it to be.
			 else if (gridYPos == 1){gridYPos = 3;}
			 else if (gridYPos == 2){gridYPos = 6;}
			 break;
		 }
	 case 1:
		 {
			 if (gridYPos == 0){gridXPos = 3; gridYPos = 0;}
			 else if (gridYPos == 1){gridXPos = 3; gridYPos = 3;}
			 else if (gridYPos == 2){gridXPos = 3; gridYPos = 6;}
			 break;
		 }
	 case 2:
		 {
			 if (gridYPos == 0){gridXPos = 6; gridYPos = 0;}
			 else if (gridYPos == 1){gridXPos = 6; gridYPos = 3;}
			 else if (gridYPos == 2){gridXPos = 6; gridYPos = 6;}
			 break;
		 }
	 }

	 //Finally, Evaluate that the value is not in the decided 3 by 3 box. 
	// system("pause");
	 int j=0,k=0;
	 j = gridXPos + 3;
	 k = gridYPos + 3;
	 for(int x = gridXPos; (x < j); x++)
	 {
		 for(int y = gridYPos; (y < k); y++)
		 {
			// cout << "\n" << x << " " << y << "\n" << j <<" "<< k <<"\n";
			 if (playVal == puzzle[x][y])
			 {
				 failCatch = 1;
				 cout << "\nthe value already exists in the 3x3 around it!\n";
				 return failCatch;
			 }
		 }
	 }
	 puzzle[xPos][yPos] = playVal;
return failCatch;
}
/* 
Function Puzzle entry verifiy
Input: Puzzle array, corridonates (X then Y), Value for corridonates.
Return: boolen, entry is good or bad. 
This function accepts corridonates and a value to check for validity in the sudoko puzzle for that corridonate
the machine scans the puzzle to ensure that the entry meets the rules of suduko as a vaild move. 
These rules must be followed:
1. The value must be in the range of 1 to 9.
2. the 9 block grid the block resides in must not have a dupelicate of the entered term.
3. there must be no duplicates in the same row or collum of the current entered value. 
*/ 