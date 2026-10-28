// This macro checks the directory you are running your macro in and prints where it is being run
// This *should* be /home/$USER/Work/York_Nuclear_Techniques_Snippets - If it is NOT, it will complain at you!
// You might want a line like this if you need a specific path. This will occur if you are running with RELATIVE pathing to input files for example
// This can be problematic for farm jobs etc.

void CheckDir(){

  TString CurrentDir=gSystem->WorkingDirectory(); // Print the directory you've run this script from
  TString ExpectedDir="/home/$USER/Work/York_Nuclear_Techniques/Snippets/"; // Construct the expected directory path
  gSystem->ExpandPathName(ExpectedDir); // Replace $USER with your username

  // Print the directory you're running from and our expected directory to screen
  cout << "Currently running this macro from - " << CurrentDir << endl;
  cout << "Expect to be running this macro from - " << ExpectedDir << endl;
  cout << "\n" << endl;

  // Compare whether the current and expected directories match - Happy or sad face depending upon result
  if(CurrentDir == ExpectedDir){
    cout << "You are running this script from the expected directory! Yay!" << endl;
    cout << "\n" << endl;
    cout << "   .---------.\n"
	 << "  /           \\\n"
	 << " /  O       O  \\\n"
	 << "|               |\n"
	 << "|   \\_______/   |\n"
	 << " \\             /\n"
	 << "  \\           /\n"
	 << "   '---------'\n";
  }
  else{
    cout << "You're NOT running this script from the expected directory!" << endl;
    cout << "\n" << endl;
    cout << "   .---------.\n"
	 << "  /           \\\n"
	 << " /  O       O  \\\n"
	 << "|               |\n"
	 << "|   /-------\\   |\n"
	 << " \\             /\n"
	 << "  \\           /\n"
	 << "   '---------'\n";
  }
  
  cout << "\n" << endl;

  exit(0);
  
}
