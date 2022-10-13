
// #define FILEPATH "../../data/R0004/"
// #define FILENAME "R0004_000000000_001000000_ana.root"

// #define FILEOUT "../../data/R0004/hist_trapz.txt"

#define FILEPATH "../../data/R0004/"
#define FILENAME "R0004_000000000_000100000_ana.root"

#define FILEOUT "../../data/R0004/hist_fit.txt"

void get_data_hist()
{
  TFile *file_in = TFile::Open(TString::Format("%s%s",FILEPATH,FILENAME).Data());
  if(file_in->IsZombie()){
    cout << "wrong open the file" << endl;
    return;
  }

  TTree *tr = (TTree*)file_in->Get("tr");

  TH1D *h1 = new TH1D("h1", "", 8192, 0, 8192);
  tr->Draw("e_fit[0]>>h1", "");

  ofstream file_out;
  file_out.open(TString::Format("%s",FILEOUT).Data());

  for(int i=0;i<h1->GetNbinsX();i++){
    file_out << i << " " << h1->GetBinContent(i) << endl;
  }

  file_out.close();
}