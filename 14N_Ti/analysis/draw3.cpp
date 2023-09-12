
void R_energy()
{
  gStyle->SetOptStat(0);

  TFile *fi1 = TFile::Open("../cali/rootfile/target1_279keV_cali.root");
  TFile *fi2 = TFile::Open("../cali/rootfile/target1_290keV_cali.root");
  TFile *fi3 = TFile::Open("../cali/rootfile/target1_298keV_cali.root");
  
  if(fi1->IsZombie() || fi2->IsZombie() || fi3->IsZombie()){
    cout << "wrong open the file" << endl;
    return;
  }

  TH1D *h281 = (TH1D*)fi1->Get("h_cali");
  TH1D *h283 = (TH1D*)fi2->Get("h_cali");
  TH1D *h285 = (TH1D*)fi3->Get("h_cali");

  auto c1 = new TCanvas();
  c1->cd();
  h281->SetLineColor(2);
  h283->SetLineColor(3);
  h285->SetLineColor(4);

  h281->Draw();
  h283->Draw("same");
  h285->Draw("same");

  TLegend *legend = new TLegend(0.68,0.6,0.86,0.88);
  legend->AddEntry(h281, "target2 281keV");
  legend->AddEntry(h283, "target2 283keV");
  legend->AddEntry(h285, "target2 285keV");
  legend->Draw();
}
