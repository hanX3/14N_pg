
void draw()
{
  gStyle->SetOptStat(0);
  //
  TFile *fi1 = TFile::Open("rootfile/background_1_cali.root");

  TH1D *h1 = (TH1D*)fi1->Get("h_cali");

  auto c1 = new TCanvas("c1", "", 0, 0, 1200, 500);
  c1->SetLogy();

  h1->GetXaxis()->SetRangeUser(0, 8000);
  h1->GetXaxis()->SetTitle("Energy [keV]");
  h1->GetYaxis()->SetTitle("Counts");

  h1->Draw();
}