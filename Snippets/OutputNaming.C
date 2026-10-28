// This macro takes in an input file name and creates an output file based upon the input
// It also checks that the output does not already exist and prompts the user to confirm before overwriting
// We also name this based upon the current date

void OutputNaming(TString InputFile = ""){

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
  
  // Construct our output file name based upon the input and today's date in DD_MM_YYYY format
  // Get the current date in DD_MM_YYYY format for use in the filename
  TDatime now;
  TString dateStr = Form("%02d_%02d_%04d", now.GetDay(), now.GetMonth(), now.GetYear());
  TString OutputFile=InputFile.Remove(InputFile.Length() - 5); // We know our input ends with .root, so strip it
  OutputFile+= "_Analysed_" + dateStr + ".root"; // Append the pieces we want back to the string
  
  // Check if the output file already exists - prompt for user confirmation if it does, make it if not
  if (gSystem->AccessPathName(OutputFile) == kFALSE){ // Confusingly, this is FALSE if the file DOES exist
    string response;
    cout << "\nWarning! You may already have processed this file!" << endl;
    cout << "File '" << OutputFile << "' already exists. Overwrite? (y/n): ";
    cin >> response;
    if (response != "y" && response != "Y" && response != "yes" && response != "Yes") { // If the response is NOT yes, exit gracefully.
      cout << "Operation cancelled. File was not overwritten." << endl;
      cout << "Exiting now, goodbye :)" << endl;
      exit(2);
    }
  }
  TFile *outFile = TFile::Open(OutputFile, "RECREATE"); // The RECREATE option here creates a new file OR overwrites and existing one
  if (!outFile || outFile->IsZombie()) { // Check our file opened correctly
        cerr << "Error: Failed to create output file '" << OutputFile << "'" << endl;
        exit(3);
  }

  outFile->Write(); // Write anything we've made to our output file
  outFile->Close(); // Close our output file
  cout << "Successfully created/re-wrote the ouput file:" << OutputFile << endl;
  exit(0);
  
}
