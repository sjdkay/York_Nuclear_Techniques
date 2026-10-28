// This macro checks the number of events present within a tree and prints the branches the tree contains

void TreeCheck(){

  // Check the file exists in this directory
  if(gSystem->AccessPathName("Test.root") == kTRUE){
    cerr << "Error! Test.root does not exist in this directory!" << endl;
    cerr << "Download the file/directory from the Drive again!" << endl;
    exit(1);
  }

  TFile* File = TFile::Open("Test.root");
  // Check the file isn't corrupted
  if (File && File->IsZombie()) { // If the file exists and is a Zombie, complain
    cerr << "Error! Test.root exists but is corrupted!" << endl;
    cerr << "Delete the file and ownload the file/directory from the Drive again!" << endl;
    exit(2);
  }

  // Check the events TTree exists
  TTree *tree = nullptr;
  File->GetObject("events", tree);
  if (!tree) {
    cerr << "Error: TTree '" << "events" << "' not found." << endl;
    cerr << "Delete the file and ownload the file/directory from the Drive again!" << endl;
    File->Close();
    exit(3);
  }
  
  // Checks done, print the number of entries in our tree
  Long64_t nEntries = tree->GetEntries();
  cout << "\n" << "The events tree has: " << nEntries << " entries (i.e events)" << "\n" << endl;

  // Look at the branches in the tree
  TObjArray *branches = tree->GetListOfBranches();
  // If branches found, print the number of them
  if (branches) {
    cout << "There are: " << branches->GetEntries() << " branches in the events tree." << "\n" << endl;
    // Prompt user to respond - Do they want to print all branch names?
    string response;
    cout << "Do you want to print all branch names? (y/n): ";
    cin >> response;
    if (response == "y" || response == "Y" || response == "yes" || response == "Yes") { // If yes, print
      for (Int_t i = 0; i < branches->GetEntries(); ++i) {
	TBranch *branch = static_cast<TBranch*>(branches->At(i));
	cout << "  - " << branch->GetName() << endl;
      }
    }
    else{ // If anything that doesn't look like a yes, skip printing individual branch names
      cout << "Skipped printing of all branch names." << endl;
    }
  }
  
  // Close the file
  File->Close();
  exit(0);
 
}
