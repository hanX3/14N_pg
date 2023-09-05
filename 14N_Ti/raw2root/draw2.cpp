
void draw2()
{
  gStyle->SetOptStat(0);

  TFile *fi1 = new TFile("./rootfile/target1_280keV.root");
  TH1D *h1 = (TH1D*)fi1->Get("h");

  TFile *fi2 = new TFile("./rootfile/target1_285keV.root");
  TH1D *h2 = (TH1D*)fi2->Get("h");


  h1->GetXaxis()->SetTitle("Channel");
  h1->GetYaxis()->SetTitle("Counts");
  h1->SetLineColor(2);
  h2->SetLineColor(4);

  auto cc1 = new TCanvas("cc1", "", 0, 0, 800, 400);
  cc1->cd();
  cc1->SetLogy();

  h1->Draw();
  h2->Draw("same");
}