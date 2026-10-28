// This macro opens up a file, copies a branch from a tree in this file and moves it to a new file

void TreeCopying(TString InputFile = ""){

  // Check if we were provided with a blank argument - If it is blank, prompt for some input
  while(InputFile.Strip(TString::kBoth).IsNull()){ // While loop ensures we provide  valid input
    cout << "Enter a filename to process: ";
    string tmp;
    getline(cin, tmp); // Asign input to tmp string
    InputFile = tmp.c_str();
  }

  // Check our input exists - exit if it doesn't
  if(gSystem->AccessPathName(InputFile) == kTRUE){
    cout << "Input file - " << InputFile << " not found." << endl;
    cout << "Check pathing and edit input argument as needed" << endl;
    exit(1);
  }
  // Check our input file has the .root suffix - exit if it doesn't
  if (InputFile.EndsWith(".root", TString::kIgnoreCase) == kFALSE) {
    cerr << "Error! Provided input file is not a .root file!" << endl;
    cerr << "Exiting, please provide a .root file!" << endl;
    exit(1);
  }

  // Open our full, unpruned file
  TFile *full_file = TFile::Open(InputFile);
  TTree* full_tree;
  // Get the events tree
  full_file->GetObject("events", full_tree);
  // Deactivate all branches
  full_tree->SetBranchStatus("*", 0);
  // Activate only the branches we want to keep, add more as needed via the line below
  // full_tree->SetBranchStatus("",1) 
  full_tree->SetBranchStatus("MCParticles.*",1);
  // Add more branches as you like
  
  // Construct our output file name based upon the input
  TString OutputFile=InputFile.Remove(InputFile.Length() - 5); // We know our input ends with .root, so strip it
  OutputFile+= "_Trimmed.root"; // Append the pieces we want back to the string
  
  // Check if the output file already exists - prompt for user confirmation if it does, make it if not
  if (gSystem->AccessPathName(OutputFile) == kFALSE){ // Confusingly, this is FALSE if the file DOES exist
    string response;
    cout << "\nWarning! You may already have processed this file!" << endl;
    cout << "File '" << OutputFile << "' already exists. Overwrite? (y/n): ";
    cin >> response;
    if (response != "y" && response != "Y" && response != "yes" && response != "Yes") { // If the response is NOT yes, exit gracefully.
      cout << "Operation cancelled. File was not overwritten." << endl;
      cout << "Exiting now, goodbye :)" << endl;
      full_file->Close(); // Close input file
      delete full_file;
      exit(2);
    }
  }
  
  // Set and open output file for the branches we've specified to copy
  TFile *ofile = TFile::Open(OutputFile,"RECREATE");
  // Clone the tree
  TTree* pruned_tree = full_tree->CloneTree(0);
  // Copy the branches
  pruned_tree->CopyEntries(full_tree);

  // Write the new tree to file
  ofile->Write();
  ofile->Close(); // Close output file
  full_file->Close(); // Close input file

  // Delete the pointers and prevent memory leaks
  delete ofile;
  delete full_file;

  cout << "Specified branches from input file copied to new file - " << OutputFile << endl;
  cout << "Goodbye :)" << endl;
  
  exit(0);
  
}
