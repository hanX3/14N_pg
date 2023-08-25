
#define BINS 16384

void tr2hist(TString str, Int_t energy, Double_t sigma)
{
  TFile *fi = TFile::Open(str.Data());
  if(fi->IsZombie()){
    cout << "can not open the file." << endl;
    return;
  }

  TString sigma_str = std::to_string(sigma);
  sigma_str.ReplaceAll(".", "-");
  cout << sigma_str << endl;

  TFile *fo = new TFile(TString::Format("./mc_%dkeV_sigma%s.root", energy, sigma_str.Data()).Data(), "recreate");

  TTree *tr2 = (TTree*)fi->Get("tree");
  double energy0;
  tr2->SetBranchAddress("energy0", &energy0);

  TH1D *h1 = new TH1D(TString::Format("h_sim_%dkeV", energy).Data(), "", BINS, 0, BINS);

  Long64_t nentries = tr2->GetEntries();
  for(Long64_t i=0;i<nentries;i++){
    tr2->GetEntry(i);

    energy0 = gRandom->Gaus(energy0, sigma);
    if(energy0<10.) continue;

    h1->Fill(energy0);
  }


  fo->cd();
  h1->Write();

  fo->Close();
}
