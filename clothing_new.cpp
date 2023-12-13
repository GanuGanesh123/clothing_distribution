// --------------------------------------------------------------------
//
// clothing.cpp
//
// Base file for input and output for clothing distribution problem.
//
// CS5130 Advanced Algorithms
//
// Reshma Priya Manne Muddu, Oct. 2022
//
// ---------------------------------------------------------------------

#include "clothing.h"
using namespace std;
#include <vector>
#include <cmath>
#include <string>

/*
*  allocateMemory2DMatrix() function is used multiple places in this cpp module whenever a 2D array(matrix) with
* memory as per the desired row/column size is allocated
* @param - 2D matrix
* @param rowSize - number of rows for the 2D array
* @param colSize - number of columns for the 2D array
* @return a 2D array with memory not allocated with NULL values
*/
int ** allocateMemory2DMatrix(int **matrixK, int rowSize, int colSize){
  if ((matrixK = new int * [rowSize]) == NULL)
    fatal("memory not allocated");
  for (int i = 0; i < rowSize; i++)
    if ((matrixK[i] = new int[colSize]) == NULL)
      fatal("memory not allocated");
  return matrixK;
}

/*
* getTwoDMatrixDefaultvalues() function is used multiple places in this cpp module whenever a 2D array(matrix) with
* default values 0s are needed to be created/initalized
* @param rowSize - number of rows for the 2D array
* @param colSize - number of columns for the 2D array
* @return a 2D array with initialized with 0 values at all (i,j) cells
*/
int ** getTwoDMatrixDefaultvalues(int rowSize, int colSize) {
  
  int ** matrixTwoD;
  matrixTwoD = allocateMemory2DMatrix(matrixTwoD, rowSize, colSize);
  // set the default value to 0 in all cells
  for (int i = 0; i < rowSize; i++) {
    for (int j = 0; j < colSize; j++) {
      matrixTwoD[i][j] = 0;
    }
  }
  return matrixTwoD;
}

/*
* Solution() Important data structure that holds the minimum distribution value and the combination
*/
struct Solution {
  float minDvalue;
  int ** priceMatrixUpdated;
};

Solution minimumFairPriceBetweenTwo(Solution solutionA, Solution solutionB);

/*
* setSolutionOutofBounds() function is used when it is required to set the solution to a value out of bounds
* in the cases where solution does not exist when exploring a path or combination
* @return a struct optimalsolution object with dummy out of bounds values
*/
Solution setSolutionOutofBounds(){
    Solution oobSolution;
    oobSolution.minDvalue = 8888888;
    return oobSolution;
}

/*
* copyMatrixToMatrix() acts as a helper function to clone/copy a matrix
* This function is used in multiple places in this cpp module implementation
* @return a 2d matrix that has been copied with the contents from other matric
*/
int ** copyMatrixToMatrix(int **matrixA, int **matrixB, int rowSize, int colSize){
    for (int i = 0; i < rowSize; i++) {
          for (int j = 0; j < colSize; j++) {
            matrixB[i][j] = matrixA[i][j];
          }
        }
    return matrixB;
}

/*
* computeSummationDistribution() computes the overall distribution summation for a given cloth distribution combination matrix
* Used in minFairPriceRecursionFn() function
*@param inputPriceMatrix with final mapped cloth prices
*@param numChild Number of children
*@param numClothes Number of clothes
*@param rByNRatio - R by N ratio computed as per requirements
*@return distrbution summation of type float
*/
float computeSummationDistribution(int ** inputPriceMatrix, int numChild, int numClothes, float rByNRatio){
    float currentD = 0;
    for (int i = 0; i < numChild; i++) {
      float ciThisChild = 0;
      for (int j = 0; j < numClothes; j++) {
        if (inputPriceMatrix[i][j] != 0) {
          ciThisChild += inputPriceMatrix[i][j];
        }
      }
      currentD += std::abs(rByNRatio - ciThisChild);
    }
    return currentD;
}

/*
* createSolutionFromPath() creates the solution object with give price matrix path
* Used in minFairPriceRecursionFn() function
*@param inputPriceMatrix with final mapped cloth prices
*@param numChild Number of children
*@param numClothes Number of clothes
*@param rByNRatio - R by N ratio computed as per requirements
*@return distrbution summation of type float
*/
Solution createSolutionFromPath(int **matrixSolutionPath, int numChild, int numClothes, float rByNRatio){
  Solution currentSolution;
  currentSolution.minDvalue = computeSummationDistribution(matrixSolutionPath, numChild, numClothes, rByNRatio);;
  currentSolution.priceMatrixUpdated = allocateMemory2DMatrix(currentSolution.priceMatrixUpdated, numChild, numClothes);
  currentSolution.priceMatrixUpdated = copyMatrixToMatrix(matrixSolutionPath, currentSolution.priceMatrixUpdated, numChild, numClothes);
  return currentSolution;
}

/*
* minimumFairPriceBetweenTwo() picks the solution whose D value is less than the other solution
* handles edge cases. This function is used in recursion function when iterating up and down
* @param: solutionA - One solution object
* @param: solutionB - Another solution object
* @return: solution object whose D value is lesser than the other
*/
Solution minimumFairPriceBetweenTwo(Solution solutionA, Solution solutionB) {
  if ((solutionA.minDvalue < 0) && (solutionB.minDvalue < 0)) 
  {
    return solutionA;
  }
  if ((solutionA.minDvalue < 0) && (solutionB.minDvalue >= 0)) 
  {
    return solutionB;
  }
  if ((solutionA.minDvalue >= 0) && (solutionB.minDvalue < 0)) 
  {
    return solutionA;
  }

  if (solutionA.minDvalue < solutionB.minDvalue) 
  {
    return solutionA;
  } 
  else 
  {
    return solutionB;
  }
}

/*
****** Important function*****
* minFairPriceRecursionFn() is called from minFairPriceDifference() function where all eligible paths are explored in the matrix and 
solution is computed for all eligible paths.
* this function also gets the best path whose D value is minimum
*@param currPriceMatrix with current mapped cloth prices as per recursion call
*@param numChild Number of children
*@param numClothes Number of clothes
*@param currIx current index of row in the matrix as per recursion
*@param currJx current index of column in the matrix as per recursion
*@param currMatrixPath the current matrix path as per the recursion call
*@param rByNRatio - R by N ratio computed as per requirements
*@param currGlobalOptimum Solution object
*@return optimal solution object with minimum distribution price
*/
Solution minFairPriceRecursionFn(int ** currPriceMatrix, int numChild, int numClothes, int currIx, int currJx,
                                        int ** currMatrixPath, float rByNRatio, Solution currGlobalOptimum) {
  if ((currIx < 0) || (currIx > numChild - 1) || (currJx < 0)) 
  { // breaks recursion for edge cases
    return setSolutionOutofBounds();
  } 
  else if (currJx <= numClothes - 1) 
  {
    if (currPriceMatrix[currIx][currJx] == 0) 
    { // break recursion for another edge case
      return setSolutionOutofBounds();
    }
    for (int idx = 0; idx < numChild; idx++) 
    { // explore to the right columns i.e. children
      // Initialize a path structure and create a copy of path to apppend new cell
      int ** newMatrixPath = getTwoDMatrixDefaultvalues(numChild, numClothes);
      int ** copiedNewMatrixPath = copyMatrixToMatrix(currMatrixPath, newMatrixPath, numChild, numClothes);
      copiedNewMatrixPath[currIx][currJx] = currPriceMatrix[currIx][currJx];
      Solution minTopBottomSolution = minimumFairPriceBetweenTwo(
        minFairPriceRecursionFn(currPriceMatrix, numChild, numClothes, currIx + idx,
          currJx + 1, copiedNewMatrixPath, rByNRatio, currGlobalOptimum),
        minFairPriceRecursionFn(currPriceMatrix, numChild, numClothes, currIx - idx - 1, currJx + 1,
          copiedNewMatrixPath, rByNRatio, currGlobalOptimum)
      );
      if ((minTopBottomSolution.minDvalue  >= 0) && (minTopBottomSolution.minDvalue < currGlobalOptimum.minDvalue))
      {
        currGlobalOptimum.minDvalue = minTopBottomSolution.minDvalue;
        currGlobalOptimum.priceMatrixUpdated = allocateMemory2DMatrix(currGlobalOptimum.priceMatrixUpdated, numChild, numClothes);
        currGlobalOptimum.priceMatrixUpdated = copyMatrixToMatrix(minTopBottomSolution.priceMatrixUpdated, currGlobalOptimum.priceMatrixUpdated, numChild, numClothes);
      }        
    }
    return currGlobalOptimum;
  } 
  else
  { //Full path explored
    return createSolutionFromPath(currMatrixPath, numChild, numClothes, rByNRatio);
  }
}

/*
****** Important function*******
* minfairpricedifference() is the main function being called from the main() code.
*@param 'priceMatrix' - 2D array pointer with all prices mapped to eligible children
*@param numChild - Number of Children
*@param numClothes - Number of children
*@param rByNRatio - R by N ratio computed as per requirements
@return Solution object with minimum distribution value and the combination matrix that
* resulted in the minimum distribution value
*/
Solution minFairPriceDifference(int ** priceMatrix, int numChild, int numClothes, float rByNRatio)
{
  Solution currGlobalOptimum;
  // Initially set the minvalue to a large value
  currGlobalOptimum.minDvalue = 5555555;
  for (int childIx = 0; childIx < numChild; childIx++) {
    // Initialize a path structure
    int ** firstMatrixPath;
    firstMatrixPath = getTwoDMatrixDefaultvalues(numChild, numClothes);
    int clothJx = 0;
    // recursively explore the eligible path in the matrix to get optimal solution
    Solution solutionFromRecursion = minFairPriceRecursionFn(priceMatrix, numChild, numClothes, childIx, clothJx, firstMatrixPath,
                                             rByNRatio, currGlobalOptimum);

    if ((solutionFromRecursion.minDvalue >= 0) && (solutionFromRecursion.minDvalue < currGlobalOptimum.minDvalue)) {
      currGlobalOptimum.minDvalue = solutionFromRecursion.minDvalue;
      currGlobalOptimum.priceMatrixUpdated = allocateMemory2DMatrix(currGlobalOptimum.priceMatrixUpdated, numChild, numClothes);
      // Assign best solution to the currGlobalOptimum object
      for (int i = 0; i < numChild; i++) {
        for (int j = 0; j < numClothes; j++) {
          currGlobalOptimum.priceMatrixUpdated[i][j] = solutionFromRecursion.priceMatrixUpdated[i][j];
        }
      }
    }
  }
  return currGlobalOptimum;
}

int main(int argc, char ** argv) {
  if (argc != 3)
    fatal("Usage:\n\n   clothing inputFile outputFile\n\n");

  timer t;
  t.start("Timer started.");

  cout << "\nCommand line arguments: \n\t";
  for (int i = 0; i < argc; i++)
    cout << argv[i] << " ";
  cout << "\n" << endl;

  char * inputFileName = argv[1];
  char * outputFileName = argv[2];

  FILE * logfile; // log file that records screen output

  char logfileName[2 * STRING_LENGTH]; // hold name of logfile
  char base[STRING_LENGTH]; // base for logfile name
  const char logSuffix[] = "_clothing.log"; // suffix for logfile name

  // determine name for logfile
  for (int i = 0; i < STRING_LENGTH; i++) {
    base[i] = outputFileName[i]; // copy output file name
    if (base[i] == '\0') {
      if (i < 5)
        fatal("Expected output file name to have at least 5 characters");

      base[i - 4] = '\0'; // set end of string to not include 4 char suffix 
      break;
    }
  }
  sprintf(logfileName, "%s%s", base, logSuffix); // string together file name

  if (LOG_FILE)
    cout << "Screen output will be recorded in '" << logfileName << "'.\n\n";

  if ((logfile = fopen(logfileName, "w")) == NULL)
    fatal("Log file could not be opened.\n");

  if (LOG_FILE) {
    fprintf(logfile, "\nCommand line arguments: \n\t");
    for (int i = 0; i < argc; i++)
      fprintf(logfile, "%s ", argv[i]);
    fprintf(logfile, "\n\n");
  }

  if (!QUIET)
    cout << "Input will be read from '" << inputFileName << "' and results will be written to '" << outputFileName << "'." << endl;

  if (LOG_FILE)
    fprintf(logfile, "\nInput will be read from '%s' and results will be written to '%s'.\n", inputFileName, outputFileName);

  int numChild = 0;
  int numClothes = 0;

  // count number of children and clothing items
  // read in data
  char tempStrng[STRING_LENGTH]; // string for temporary storage
  int tempInt; // temporary int storage
  float tempFloat; // temporary float storage

  ifstream inputFile;
  ofstream outputFile;

  inputFile.open(inputFileName);
  outputFile.open(outputFileName);

  if (!inputFile.is_open())
    fatal("Unable to open input file.");

  if (!outputFile.is_open())
    fatal("Unable to open output file.");

  inputFile >> tempStrng; // read in 'Clothes'
  if (strncmp(tempStrng, "Clothes", 7) != 0)
    fatal("Expected input file to begin with 'Clothes'.");

  inputFile >> tempStrng; // read in first clothing ID

  while (strncmp(tempStrng, "Children", 8) != 0) {
    for (int i = 0; i < 4; i++) // read in 4 strings on each line
      inputFile >> tempStrng;
    numClothes++;
  }

  inputFile >> tempStrng; // read in first child ID

  while (!inputFile.eof()) {
    for (int i = 0; i < 2; i++) // read in 2 strings on each line
      inputFile >> tempStrng;
    numChild++;
  }

  if (!QUIET)
    cout << "Read in data for " << numChild << " children and " << numClothes << " clothing items." << endl;

  if (LOG_FILE) {
    fprintf(logfile, "Read in data for %d children and %d clothing items.\n\n", numChild, numClothes);
  }

  // check validity of values
  if (numChild < 2)
    fatal("Must have at least 2 children.");

  if (numClothes < 2 * numChild)
    fatal("Must have at least two clothing items per child.");

  inputFile.close();

  // allocate memory for arrays holding constants
  char ** childIDs; // array of strings to hold child IDs
  if ((childIDs = new char * [numChild]) == NULL)
    fatal("memory not allocated");
  for (int i = 0; i < numChild; i++)
    if ((childIDs[i] = new char[STRING_LENGTH]) == NULL)
      fatal("memory not allocated");

  char ** clothesIDs; // array of strings to hold clothing IDs
  if ((clothesIDs = new char * [numClothes]) == NULL)
    fatal("memory not allocated");
  for (int i = 0; i < numClothes; i++)
    if ((clothesIDs[i] = new char[STRING_LENGTH]) == NULL)
      fatal("memory not allocated");

  char * childSize; // array to hold sizes of children
  if ((childSize = new char[numChild]) == NULL) // use S, M, L, X, A for small, medium, large, extra large, one-size-fits-all
    fatal("memory not allocated");

  int * price; // array to hold prices of clothes
  if ((price = new int[numClothes]) == NULL)
    fatal("memory not allocated");

  char * clothesSize; // array to hold sizes of clothes
  if ((clothesSize = new char[numClothes]) == NULL)
    fatal("memory not allocated");

  char * season; // array to hold season types of clothes
  if ((season = new char[numClothes]) == NULL)
    fatal("memory not allocated");

  int ** assignment;
  assignment = getTwoDMatrixDefaultvalues(numChild, numClothes);

  // reopen input file and read in information
  inputFile.open(inputFileName);

  if (!inputFile.is_open())
    fatal("Unable to open input file.");

  inputFile >> tempStrng; // read in 'Clothes' and ignore

  for (int i = 0; i < numClothes; i++) {
    inputFile >> clothesIDs[i]; // clothes IDs in first column
    inputFile >> tempStrng;
    clothesSize[i] = tempStrng[0]; // clothes size  in second column (only keep first character)
    inputFile >> tempStrng;
    season[i] = tempStrng[0]; // clothing season type in third column (only keep first character)
    inputFile >> price[i]; // clothes price in fourth column

    if (inputFile.eof())
      fatal("Less data in input file than expected.");
  }

  inputFile >> tempStrng; // read in 'Children' and ignore

  for (int i = 0; i < numChild; i++) {
    inputFile >> childIDs[i]; // children's IDs in first column
    inputFile >> tempStrng;
    childSize[i] = tempStrng[0]; // child's size  in second column (only keep first character)
  }

  inputFile.close();

  if (VERBOSE) {
    cout << "\nChild IDs and sizes are:" << endl;
    for (int i = 0; i < numChild; i++)
      cout << childIDs[i] << "\t" << childSize[i] << endl;
    cout << endl;

    cout << "Clothes IDs, sizes, seasons, and prices are:" << endl;
    for (int i = 0; i < numClothes; i++)
      cout << clothesIDs[i] << "\t" << clothesSize[i] << "\t" << season[i] << "\t" << price[i] << endl;
    cout << "\n";
  }

  float obj; // hold the D value (objective function value)

  /***********************************************************************************************
  ************************************************************************************************

  Note: Added my code here

  The logic is simple. The implementation first prepares a matrix with all prices mapped into cells
  where rows are children and columns are clothes. Only eligible (as per sizes and seasons) clothes are mapped. For an example,
  here is how the price matrix looks with all eligible mappings:
      A1  A2  A3 A4
  C1  31  24  0  18
  C2  0   0   21 18

  Here the cloth A4 is eligible can be mapped/distributed to either C1 and C2. Therefore, we explore
  both the possibilities (combinations) and pick the combinations that results us with global optimal
  minimal fair price distribution as per our requirement.

  Algorithm:
  1. Prepare initial eligible price matrix where some clothes are mapped to more than one child.
  2. Then start forming the combinations of clothes being mapped to children such that only one cloth is
  distributed to a student and other eligibility conditions/
    a) This is achieved through recursion. This is similar to exploring all possible paths in a matrix
       except we have our own constraints
    b) Out of all the valid combinations return the combination that resulted in minimal distribution value
       and the path.
    c) Use this returned matrix path to build the assignment matrix which is used in the down-stream code
       to output the result.
  Documented and structured and easily readible code
  ************************************************************************************************
  ***********************************************************************************************/

  obj = -1;

  int ** priceMatrix;
  priceMatrix = getTwoDMatrixDefaultvalues(numChild, numClothes);
  for (int i = 0; i < numChild; i++) {
    for (int j = 0; j < numClothes; j++) {
      if ((childSize[i] == clothesSize[j]) || (clothesSize[j] == 'A')) {
        priceMatrix[i][j] = price[j];
      }
    }
  }
  // Compute N, R and R/N ratio
  int R; //sum of retail prices of all clothing
  for (int i = 0; i < numClothes; i++) {
    R += price[i];
  }

  float rByNRatio;
  rByNRatio = float(R) / float(numChild);

  Solution optimalGlobalMinimumSolution = minFairPriceDifference(priceMatrix, numChild, numClothes, rByNRatio);
  obj = optimalGlobalMinimumSolution.minDvalue;

  for (int i = 0; i < numChild; i++) {
    for (int j = 0; j < numClothes; j++) {
      assignment[i][j] = min(1, optimalGlobalMinimumSolution.priceMatrixUpdated[i][j]);
    }
  }
  /***********************************************************************************************
  ************************************************************************************************
     End of my code.
  ************************************************************************************************
  ***********************************************************************************************/

  // output results   
  int share; // hold sum of clothing assigned to child

  if (!QUIET)
    cout << "\nAssignments are:\n";

  for (int i = 0; i < numChild; i++) {
    outputFile << childIDs[i]; // begin row with child ID number
    share = 0;

    if (!QUIET)
      cout << childIDs[i];

    for (int j = 0; j < numClothes; j++) {
      if (assignment[i][j] == 1) { // clothing item j is assigned to child i
        outputFile << "\t" << clothesIDs[j];

        if (!QUIET)
          cout << "\t" << clothesIDs[j];

        share += price[j];
      }
    }

    outputFile << "\t" << share << endl;
    if (!QUIET)
      cout << "\t" << share << "\n";
  }

  if (!QUIET)
    cout << "D\t" << obj << endl;

  outputFile << "D\t" << obj << endl;

  if (LOG_FILE) {
    for (int i = 0; i < numChild; i++) {
      fprintf(logfile, "%s", childIDs[i]);

      for (int j = 0; j < numClothes; j++)
        if (assignment[i][j] == 1) // clothing item j is assigned to child i
          fprintf(logfile, "\t%s", clothesIDs[j]);
      fprintf(logfile, "\t%d\n", share);
    }

    fprintf(logfile, "D\t%f\n\n", obj);
  }

  // *** delete arrays **************

  t.stop("\nTimer stopped.");
  cout << t << " seconds.\n" << endl;

  if (LOG_FILE) {
    double compTime;
    compTime = t.timeVal();
    fprintf(logfile, "\n%f seconds.\n\n", compTime);
  }

  outputFile.close();
  fclose(logfile);

  return 0;
}
