// This short macro snippet shows how to check if a filename provided as an input is valid or not.
#include <TSystem.h>

void FileCheck(TString InputFile = ""){

  // Check if we were provided with a blank argument - If it is blank, prompt for some input
  while(InputFile.Strip(TString::kBoth).IsNull()){ // While loop ensures we provide  valid input
    cout << "Enter a filename to process: ";
    string tmp;
    getline(cin, tmp); // Asign input to tmp string
    InputFile = tmp.c_str();
  }

  // Check if file exists - If it doesn't, exit gracefully
  if(gSystem->AccessPathName(InputFile) == kTRUE){
    cout << "Input file - " << InputFile << " not found." << endl;
    cout << "Check pathing and edit input argument as needed" << endl;
    exit(1);
  }
  else{ // File exists, try to open it!
    TFile *tmpfile = TFile::Open(InputFile);
    if (tmpfile && !tmpfile->IsZombie()) { // File exists and is NOT Zombie
      // Add further checks here
      cout << "Add any checks of the file you want here." << endl;
      cout << "See commented code in file for an example!" << endl;
      // The lines below define a temporary tree and try to assign it to "events" in our input file
      // We then check that the events tree atually contains this tree
      // The assignment will fail if it doesn't exist - You could change "events" to a tree of your choosing
      // TTree *tmptree = (TTree*)tmpfile->Get("events");
      // Ensure the file also contains a valid tree
      //if (!tmptree) {
      //cout << "Tree 'events' not found in file: " << InputFile << endl;
      //exit(2);
      //}
      // Close the file and remove the pointer
      tmpfile->Close();  // Close the file
      delete tmpfile;    // Delete the file pointer
    }
    // If the file IS a zombie, complain and exit
    else {
      cout << "Failed to open file: " << InputFile <<endl;
      exit(3);
      if (tmpfile) {
	tmpfile->Close();  // Close the file if it was partially opened
	delete tmpfile;    // Delete the file pointer
      }
    }
  }

  exit(0);
}
