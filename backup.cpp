// --------------------------------------------------------------------
//
// clothing.cpp
//
// Base file for input and output for clothing distribution problem.
//
// CS5130 Advanced Algorithms
//
// Sharlee Climer, Sept. 2022
//
// ---------------------------------------------------------------------

#include "clothing.h"
using namespace std;
#include <vector>


// return vector for assignment
// apply recursion




struct optimalsolution
{
  int minDvalue;
  int **pricematrixupdated;
};



//optimalsolution minfairpricehelper(int **pricematrix, int numchild, int numclothes, ix, jx, finaloptimalD)
//{

  //if (ix < 0) || (ix > numchild -1) || (jx < 0) || (pricematrix[i][j] == 0)
  //{
    // break recursion
    //optimalsolution retval;
    //retval.minDvalue = -1;
    //return retval
  //}
  //else if (jx <= numclothes -1) {
    // explore to the right
    //for (int idx = 0; idx < numchild; idx ++)
    //{

      //return getminimumfairprice(minfairpricehelper(pricematrix, numchild, numclothes, ix + idx, jx + 1, finaloptimalD),
        //minfairpricehelper(pricematrix, numchild, numclothes, ix - idx - 1, jx + 1, finaloptimalD)
        //)
    //}
  //} else {
    // full path explored
    //int currentD = 0;
    //for (int i; i < numchild; i++)
    //{
      //for (int j; j < numclothes; j++)
      //{
        //currentD += pricematrix[i][j]
      //}
    //}

    //if currentD <

  //}

//}

optimalsolution getminimumfairprice(optimalsolution solutiona, optimalsolution solutionb)
{
  if (solutiona.minDvalue < solutionb.minDvalue)
  {
    return solutiona;
  }
  else{
    return solutionb;
  }
}


optimalsolution minfairpricedifference(int **pricematrix, int numchild, int numclothes)
{
  for (int childix=0; childix<numchild; childix++)
  {
    
    // Initialize a path structure
    int **path; 
    if ((path = new int*[numchild]) == NULL)
      fatal("memory not allocated");
    
    for (int i = 0; i < numchild; i++) 
      if ((path[i] = new int[numclothes]) == NULL)
        fatal("memory not allocated");


    // Initialize seen paths
    std::string seenpathstrings[400];  
    //for (int i=0; i<numchild; i ++)
    { 
        string str_i = to_string(i);
        //string str_j = to_string(j);
        //string str_join = str_i + str_j;
        seenpathstrings[i] = (str_i);
    }
    for (int i=0; i<2; i ++){
        cout << "Vector: \n\n" <<  seenpathstrings[i] << endl;
    }
    for (int i=0; i<numchild; i ++)
    {
      cout << "Inside1" << "\n";

      for (int j; j<numclothes; j++)
      {
        cout << "Inside" << "\n";
        path[i][j] = 2;
      }
    }
    cout << "TEST\n\n";

    for (int i=0; i<numchild; i ++){
      for (int j; j<numclothes; j++)
      {
        cout << "path" <<  path[i][j] << endl;
      }
    }
    //minfairpricehelper(pricematrix, numchild, numclothes, childix, 0, finaloptimalDvalue)

  }


  //std::vector<int> fairpricediffvalues; 
  // Search space - Explore paths
  //for (int ix = 0; ix < numchild; ix ++)
  //{
    //return minfairpricediffhelper
    //fairpricediffvalues.push_back(ix);
  //}
  //cout << "done";
  //for (int ix = 0; ix < numchild; ix ++)
  //{
    //return minfairpricediffhelper
    //cout << "value: " <<fairpricediffvalues[ix] << endl;;
  //}

  optimalsolution retval;
  retval.minDvalue = 10;
  if ((retval.pricematrixupdated = new int*[numchild]) == NULL)
      fatal("memory not allocated");
    for (int i = 0; i < numchild; i++) 
      if ((retval.pricematrixupdated[i] = new int[numclothes]) == NULL)
        fatal("memory not allocated");  

  for (int i = 0; i < numchild; i++)
  {
    for (int j = 0; j < numclothes; j++)
    {
      //cout << clothesSize[j] << endl;
      retval.pricematrixupdated[i][j] = pricematrix[i][j];
    }
  }

  return retval;
}

int main(int argc, char ** argv) 
{
  if (argc != 3)
    fatal("Usage:\n\n   clothing inputFile outputFile\n\n");

  timer t;
  t.start("Timer started.");

  cout << "\nCommand line arguments: \n\t";
  for (int i = 0; i < argc; i++)
    cout << argv[i] << " ";
  cout << "\n" << endl;
  
  char *inputFileName = argv[1];
  char *outputFileName = argv[2];

  FILE *logfile; // log file that records screen output

  char logfileName[2*STRING_LENGTH]; // hold name of logfile
  char base[STRING_LENGTH]; // base for logfile name
  const char logSuffix[] = "_clothing.log"; // suffix for logfile name

  // determine name for logfile
  for (int i = 0; i < STRING_LENGTH; i++) {
    base[i] = outputFileName[i]; // copy output file name
    if (base[i] == '\0') {
      if(i < 5)
        fatal("Expected output file name to have at least 5 characters");
  
      base[i-4] = '\0'; // set end of string to not include 4 char suffix 
      break;
      }
  } 
  sprintf(logfileName, "%s%s", base, logSuffix); // string together file name

  if(LOG_FILE) 
    cout << "Screen output will be recorded in '" << logfileName <<"'.\n\n";

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
  
  if(LOG_FILE) 
    fprintf(logfile, "\nInput will be read from '%s' and results will be written to '%s'.\n", inputFileName, outputFileName); 

  int numchild = 0;
  int numclothes = 0;
  
  // count number of children and clothing items
  // read in data
  char tempStrng [STRING_LENGTH]; // string for temporary storage
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
    numclothes++;
  }
  
  inputFile >> tempStrng; // read in first child ID
    
  while (!inputFile.eof()) {  
    for (int i = 0; i < 2; i++) // read in 2 strings on each line
      inputFile >> tempStrng;
    numchild++;
  }
  
  if(!QUIET)
    cout << "Read in data for " << numchild << " children and " << numclothes << " clothing items." <<  endl;
  
    if(LOG_FILE) {
    fprintf(logfile, "Read in data for %d children and %d clothing items.\n\n", numchild, numclothes);
  } 

  // check validity of values
  if (numchild < 2)
    fatal("Must have at least 2 children.");
    
  if (numclothes < 2 * numchild)
    fatal ("Must have at least two clothing items per child.");
  
  inputFile.close();
  
  // allocate memory for arrays holding constants
  char **childIDs; // array of strings to hold child IDs
  if ((childIDs = new char*[numchild]) == NULL)
    fatal("memory not allocated");
  for (int i = 0; i < numchild; i++) 
    if ((childIDs[i] = new char[STRING_LENGTH]) == NULL)
      fatal("memory not allocated");
 
  char **clothesIDs; // array of strings to hold clothing IDs
  if ((clothesIDs = new char*[numclothes]) == NULL)
    fatal("memory not allocated");
  for (int i = 0; i < numclothes; i++) 
    if ((clothesIDs[i] = new char[STRING_LENGTH]) == NULL)
      fatal("memory not allocated");
   
  char *childSize; // array to hold sizes of children
  if ((childSize = new char[numchild]) == NULL)  // use S, M, L, X, A for small, medium, large, extra large, one-size-fits-all
      fatal("memory not allocated");  
      
  int *price; // array to hold prices of clothes
  if ((price = new int[numclothes]) == NULL)
      fatal("memory not allocated"); 

  char *clothesSize; // array to hold sizes of clothes
  if ((clothesSize = new char[numclothes]) == NULL)  
      fatal("memory not allocated"); 

  char *season; // array to hold season types of clothes
  if ((season = new char[numclothes]) == NULL)  
      fatal("memory not allocated");       
  
  // allocate memory for arrays holding assignment variables 
  int **assignment; // assignment[i][j] = 1 if child i gets clothing j, 0 otherwise
  if ((assignment = new int*[numchild]) == NULL)
    fatal("memory not allocated");
  for (int i = 0; i < numchild; i++) 
    if ((assignment[i] = new int[numclothes]) == NULL)
      fatal("memory not allocated");
  
  // reopen input file and read in information
  inputFile.open(inputFileName);

  if (!inputFile.is_open())
    fatal("Unable to open input file.");

  inputFile >> tempStrng; // read in 'Clothes' and ignore
  
  for (int i = 0; i < numclothes; i++) {
    inputFile >> clothesIDs[i];  // clothes IDs in first column
    inputFile >> tempStrng;
    clothesSize[i] = tempStrng[0]; // clothes size  in second column (only keep first character)
    inputFile >> tempStrng;
    season[i] = tempStrng[0]; // clothing season type in third column (only keep first character)
    inputFile >> price[i]; // clothes price in fourth column
    
    if (inputFile.eof())
      fatal ("Less data in input file than expected.");
  }  
  
  inputFile >> tempStrng; // read in 'Children' and ignore
  
  for (int i = 0; i < numchild; i++) {
    inputFile >> childIDs[i];  // children's IDs in first column
    inputFile >> tempStrng;
    childSize[i] = tempStrng[0]; // child's size  in second column (only keep first character)
  }
  
  inputFile.close();
  
  if (VERBOSE) {
    cout << "\nChild IDs and sizes are:" << endl;
    for (int i = 0; i < numchild; i++)
      cout << childIDs[i] << "\t" << childSize[i] << endl;
    cout << endl;
    
    cout << "Clothes IDs, sizes, seasons, and prices are:" << endl;
    for (int i = 0; i < numclothes; i++)
      cout << clothesIDs[i] << "\t" << clothesSize[i] << "\t" << season[i] << "\t" << price[i] << endl;
    cout << "\n";
  }

  float obj; // hold the D value (objective function value)
  
  
  
/***********************************************************************************************
************************************************************************************************

   Delete the following code and add your code here.
   
************************************************************************************************
***********************************************************************************************/  

  obj = -1;

  // Prepare a price matrix and compute the distribution value for all the eligible paths
  // Elgiibility Check1: Each child should be allocated a cloth
  // Check 2: Each cloth can be allocated to only one child

  int **pricematrix;
  cout << "allocating pricematrix as per eligibility" << endl;
  if ((pricematrix = new int*[numchild]) == NULL)
    fatal("memory not allocated");
  for (int i = 0; i < numchild; i++) 
    if ((pricematrix[i] = new int[numclothes]) == NULL)
      fatal("memory not allocated");

  for (int i = 0; i < numchild; i ++)
  {
    for (int j = 0; j < numclothes; j++)
    {
      if ((childSize[i] == clothesSize[j]) || (clothesSize[j] == 'A'))
      {
        pricematrix[i][j] = price[j];
      }
      cout << pricematrix[i][j]<<"\t";
    }
    cout << "\n";
  }

  // this functions gives me optimal minimum D and optimal minimum path(distribution)

  optimalsolution foo_bar = minfairpricedifference(pricematrix, numchild, numclothes);
  cout << "foo_bar\n" << foo_bar.minDvalue;
  obj = foo_bar.minDvalue;
  //assignment = foo_bar.pricematrixupdated;

  for (int i = 0; i < numchild; i++)
  {
    for (int j = 0; j < numclothes; j++)
    {
      //cout << clothesSize[j] << endl;
      assignment[i][j] = foo_bar.pricematrixupdated[i][j];
    }
  }

  //for (int i = 0; i < numchild; i++)
  //{
    //for (int j = 0; j < numclothes; j++)
    //{
      //cout << clothesSize[j] << endl;

      //if ((childSize[i] == clothesSize[j]) || (clothesSize[j] == 'A'))
      //{
        //assignment[i][j] = 1;
      //}
    //}
  //}

  cout << "final assignment matrix" << endl;
  for (int i = 0; i < numchild; i++)
  {
    for (int j = 0; j < numclothes; j++)
    {
      //if (j == 0)
      //{
        //cout << childIDs[i] << "\tCell: (" << i << ","<< j << ")-" << assignment[i][j] <<"\t";
      //}
      //else
      //{
        //cout << "  \tCell: (" << i << ","<< j << ")-" << assignment[i][j] <<"\t";
      //}
      cout << assignment[i][j] <<"\t";
    }
    cout << "\n";

  }

/***********************************************************************************************
************************************************************************************************

   End of code to be deleted.
   
************************************************************************************************
***********************************************************************************************/  


  
  
  // output results   
  int share; // hold sum of clothing assigned to child
  
  if (!QUIET)
    cout << "\nAssignments are:\n";
    
  for (int i = 0; i < numchild; i++) { 
    outputFile << childIDs[i]; // begin row with child ID number
    share = 0; 
    
    if (!QUIET)
      cout << childIDs[i];
    
    for (int j = 0; j < numclothes; j++) {
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
  
  if(LOG_FILE) {  
    for (int i = 0; i < numchild; i++) { 
      fprintf(logfile, "%s", childIDs[i]);
    
      for (int j = 0; j < numclothes; j++) 
        if (assignment[i][j] == 1)  // clothing item j is assigned to child i
          fprintf(logfile, "\t%s", clothesIDs[j]);
      fprintf(logfile, "\t%d\n", share);
    }  
    
    fprintf(logfile, "D\t%f\n\n", obj); 
  }


// *** delete arrays **************

  t.stop("\nTimer stopped.");
  cout << t << " seconds.\n" << endl;
  
  if(LOG_FILE) {
    double compTime;
    compTime = t.timeVal();
    fprintf(logfile, "\n%f seconds.\n\n", compTime);
  }
  
  outputFile.close();
  fclose(logfile);

  return 0;
}
