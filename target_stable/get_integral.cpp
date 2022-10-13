
void get_integral()
{
  // gROOT->SetBatch(0);

  int run[12] = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
  int a[12] = {10846, 10840, 10850, 10854, 10845, 10845, 10845, 10840, 10840, 10840, 10840, 10840};
  int b[12] = {10880, 10880, 10880, 10884, 10885, 10885, 10885, 10880, 10880, 10880, 10880, 10880};

  TFile *file_in[12];
  TTree *tr[12];

  for(int i=0;i<12;i++){
    file_in[i] = TFile::Open(TString::Format("../../data/target2/281keV/R%04d_ana.root",run[i]));
    if(file_in[i]->IsZombie()){
      cout << "wrong open the file" << endl;
      return;
    }

    TH1D *h1 = new TH1D("h1", "", 20000, 0, 20000);

    tr[i] = (TTree*)file_in[i]->Get("tr");
    tr[i]->Draw("e_trapz[0]>>h1","e_trapz[0]>0");
    cout << run[i] << " " << h1->Integral(a[i], b[i]) << endl;
  }
}