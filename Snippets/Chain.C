// This macro reads a list of files and adds them to a TChain.
// Before adding the files, it checks that each exists, can be opened and is not a zombie

void Chain(TString FileList = ""){

  // Check if we were provided with a blank argument - If it is blank, prompt for some input
  while(FileList.Strip(TString::kBoth).IsNull()){ // While loop ensures we provide  valid input
    cout << "Enter a filename to process: ";
    string tmp;
    getline(cin, tmp); // Asign input to tmp string
    FileList = tmp.c_str();
  }

  TChain *AnalysisChain = new TChain("events"); // Create a chain where we will be combining the "events" tree
  
  ifstream fstream (FileList); // Open our file list
  string line;
  int FileCount = 0;  

  while(getline(fstream, line)){ // Go through the file, line by line
    TString tmpFile{line}; // Assign the line in the file to a string - this is the root file we will try to open
    if(gSystem->AccessPathName(tmpFile) == kTRUE){ // If file not found, skip to next line
      cout << "Input file - " << tmpFile << " not found." << endl;
      cout << "Check pathing and edit input argument as needed" << endl;
      continue;
    }
    else{
      auto RootFile = TFile::Open(tmpFile);
      if (RootFile && !RootFile->IsZombie()) { // File exists and is NOT Zombie
	AnalysisChain->Add(tmpFile);
        FileCount++;   
      }
    }
  }
  
  if(FileCount == 0){
    cerr << "Error! No files in list actually added to chain successfully! Check they exist!" << endl;
    cerr << "Download Test1.root, Test2.root and Test3.root from the drive and add them to this directory!" << endl;
    exit(1);
  }
  cout << FileList << " file processed - " << FileCount << " files added to chain" << endl;

  TTreeReader tree_reader(AnalysisChain); // Make a tree_reader for our chain
  // Add readers as needed

  int EventCounter = 0; // An integer to count the number of events - We could use this for loop control - e.g. only analyse up to 1000 events
  while(tree_reader.Next()) { // Loop over all events in our chain
    EventCounter++;
    // Do something to your chain :)
  }

  cout << "Processed chain - " << EventCounter << " events total." << endl;

  exit(0);
}
