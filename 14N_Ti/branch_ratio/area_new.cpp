
//
Double_t background(Double_t *x, Double_t *par)
{
  return par[0] + par[1]*x[0];
}

// par[0] area
// par[1] mean
// par[2] sigma
Double_t gausPeak(Double_t *x, Double_t *par)
{
  return par[0]*TMath::Gaus(x[0], par[1], par[2]);
}

// Sum of background and peak function
Double_t fitFunction(Double_t *x, Double_t *par)
{
  return background(x, par) + gausPeak(x, &par[2]);
}


//
void area_single(TH1D *h, Double_t peaks, Double_t &s)
{
  double p0 = -0.746728;
  double p1 = 0.511636;

  double k = 5.;

  auto c1 = new TCanvas(TString::Format("c_%d", (int)peaks), TString::Format("c_%d", (int)peaks), 0, 0, 500, 400);
  c1->cd();
  c1->SetLogy();
  h->SetLineColor(1);

  TH1D *hh = (TH1D*)h->Clone(TString::Format("h_%d", (int)peaks));
  hh->GetXaxis()->SetRangeUser(peaks-100., peaks+100.);
  hh->Draw();

  s = 0.;
  TF1 *tf_back = new TF1("tf_back", background, peaks*0.92, peaks*1.08, 2);
  tf_back->SetParameter(0, 10);
  tf_back->SetParameter(1, 1);
  hh->Fit("tf_back", "R0Q");
  TF1 *tf = new TF1("tf", fitFunction, peaks*0.998, peaks*1.002, 5);
  tf->FixParameter(0, tf_back->GetParameter(0));
  tf->FixParameter(1, tf_back->GetParameter(1));
  int bin = (int)(peaks-p0)/p1;
  // cout << "bin " << bin << endl;
  tf->SetParameter(2, h->GetBinContent(bin));
  tf->SetParameter(3, peaks);
  tf->SetParameter(4, 3.3);
  hh->Fit("tf", "R");
  c1->cd();
  tf_back->SetLineColor(2);
  tf_back->Draw("same");
  tf->SetLineColor(4);
  tf->Draw("same");

  //
  int bin_min = (int)((tf->GetParameter(3)-k/2.*tf->GetParameter(4)-p0)/p1+0.5);
  int bin_max = (int)((tf->GetParameter(3)+k/2.*tf->GetParameter(4)-p0)/p1+0.5);
  cout << "bin min " << bin_min << " " << h->GetBinCenter(bin_min) << " " << h->GetBinContent(bin_min) << endl;
  cout << "bin max " << bin_max << " " << h->GetBinCenter(bin_max) << " " << h->GetBinContent(bin_max) << endl;

  for(int j=bin_min;j<(bin_max+1);j++){
    // cout << h->GetBinContent(j) << endl;
    // cout << tf_back->Eval(h->GetBinCenter(j)) << endl;;
    s += h->GetBinContent(j);
    s -= tf_back->Eval(hh->GetBinCenter(j));
  }

  cout << "peak " << peaks << "  area " << s << endl;
  
}


//
void area_new()
{
  // gROOT->SetBatch(1);

  double p0 = -0.746728;
  double p1 = 0.511636;

  TFile *fi = TFile::Open("../cali/rootfile/target1_280keV_cali.root"); 
  if(fi->IsZombie()){
    cout << "can not open the file" << endl;
    return;
  }

  TH1D *h = (TH1D*)fi->Get("h_cali");
  auto c1 = new TCanvas("c1", "", 0, 0, 500, 400);
  c1->cd();
  h->SetLineColor(1);
  h->Draw();

  Double_t peaks[4] = {5181., 6172., 6792., 7556.};

  ofstream fo;
  fo.open("area_new.txt");

  double s;
  for(int i=0;i<4;i++){
    area_single(h, peaks[i], s);
    fo << peaks[i] << " " << s << endl;
    // cout << "peak " << peaks[i] << "  area " << s << endl;
  }

  fo.close();
}

