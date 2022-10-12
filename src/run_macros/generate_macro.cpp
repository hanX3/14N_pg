#define CORE 6

#define FILEPATH "../../../data/"
#define RUNNO 7

//
void generate_macro()
{
  TFile *file_in = TFile::Open(TString::Format("%sR%04d.root",FILEPATH,RUNNO).Data());
  if(file_in->IsZombie()){
    cout << "wrong open the file" << endl;
    return;
  }

  TTree *tr = (TTree*)file_in->Get("tree");
  Long64_t n = tr->GetEntries();
  cout << n << endl;

  Long64_t step = n/6+1;
  cout << step << endl;

  ofstream file_out;
  file_out.open(TString::Format("R%04d.sh",RUNNO).Data());

  file_out << "#!/usr/bin/bash" << endl << endl;
  file_out << "rm " << FILEPATH << TString::Format("R%04d",RUNNO).Data() << "/*.root" << endl << endl;
  file_out << "cd ../\n\n"; 

  Long64_t n1, n2;
  for(int i=0;i<CORE;i++){
    n1 = i*step;
    n2 = (i+1)*step;

    file_out << "./ana_batch " << RUNNO << " " << n1 << " " << n2 << " &\n";
  }

  file_out.close();
}