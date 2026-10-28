// This macro creates a new output file with a tree inside it. This tree contains 1000 events in a branch, filled randomly from a Gaussian

void TreeFilling() {

  if (gSystem->AccessPathName("Gaussian_Output_Tree.root") == kFALSE){ // Confusingly, this is FALSE if the file DOES exist
    string response;
    cout << "\nWarning! You may already have run this macro!" << endl;
    cout << "File 'Gaussian_Output_Tree.root' already exists. Overwrite? (y/n): ";
    cin >> response;
    if (response != "y" && response != "Y" && response != "yes" && response != "Yes") { // If the response is NOT yes, exit gracefully.
      cout << "Operation cancelled. File was not overwritten." << endl;
      cout << "Exiting now, goodbye :)" << endl;
      exit(2);
    }
  }
  
  TFile *outFile = TFile::Open("Gaussian_Output_Tree.root", "RECREATE");
  if (!outFile || outFile->IsZombie()) {
    cerr << "Error: Could not create output file!" << endl;
    exit(1);
  }

  // Create a new tree in this file
  TTree *tree = new TTree("Gaus_Events", "Tree with Gaussian Random Data");

  // Create buffer variables and assign them to some branches
  Double_t gauss1Val = 0.0;
  Double_t gauss2Val = 0.0;
  tree->Branch("gauss1Val", &gauss1Val, "gauss1Val/D");
  tree->Branch("gauss2Val", &gauss2Val, "gauss2Val/D");

  // Initialise a random number generator and provide it with a seed from the system clock (0)
  TRandom3 rand(0);

  // Fill the tree with 1000 events - We will fill the two branches with different gaussians
  const Int_t nEvents = 1000;
  for (Int_t i = 0; i < nEvents; ++i) {
    // Recall that we provide the mean and SD to the gaussian
    gauss1Val = rand.Gaus(2.0, 0.5);
    gauss2Val = rand.Gaus(-20, 4);
    tree->Fill();
  }
  // Write the tree to our file and close the file
  tree->Write();
  outFile->Close();

  // Clean up the memory pointers
  delete outFile;

  // Print some message to screen to show to the user that we're done
  cout << "Successfully created 'Gaussian_Output_Tree.root' with " 
       << nEvents << " events." << endl;
  cout << "Goodbye :)" <<endl;

  exit(0);
  
}
