
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

  auto c1 = new TCanvas("c1", "", 0, 0, 500, 400);
  c1->cd();
  h->SetLineColor(1);
  h->Draw();

  s = 0.;
  TF1 *tf_back = new TF1("tf_back", background, peaks*0.92, peaks*1.08, 2);
  tf_back->SetParameter(0, 10);
  tf_back->SetParameter(1, 1);
  h->Fit("tf_back", "R0Q");
  TF1 *tf = new TF1("tf", fitFunction, peaks*0.998, peaks*1.002, 5);
  tf->FixParameter(0, tf_back->GetParameter(0));
  tf->FixParameter(1, tf_back->GetParameter(1));
  int bin = (int)(peaks-p0)/p1;
  // cout << "bin " << bin << endl;
  tf->SetParameter(2, h->GetBinContent(bin));
  tf->SetParameter(3, peaks);
  tf->SetParameter(4, 3.3);
  h->Fit("tf", "R");
  c1->cd();
  tf_back->SetLineColor(2);
  tf_back->Draw("same");
  tf->SetLineColor(4);
  tf->Draw("same");

  //
  int bin_min = (int)((tf->GetParameter(3)-2.5*tf->GetParameter(4)-p0)/p1+0.5);
  int bin_max = (int)((tf->GetParameter(3)+2.5*tf->GetParameter(4)-p0)/p1+0.5);
  cout << "bin min " << bin_min << " " << h->GetBinCenter(bin_min) << " " << h->GetBinContent(bin_min) << endl;
  cout << "bin max " << bin_max << " " << h->GetBinCenter(bin_max) << " " << h->GetBinContent(bin_max) << endl;

  for(int k=bin_min;k<(bin_max+1);k++){
    // cout << h->GetBinContent(k) << endl;
    // cout << tf_back->Eval(h->GetBinCenter(k)) << endl;;
    s += h->GetBinContent(k);
    s -= tf_back->Eval(h->GetBinCenter(k));
  }

  cout << "peak " << peaks << "  area " << s << endl;
  
}

//
void area3_single(TH1D *h, Double_t peaks, Double_t &s)
{
  double p0 = -0.746728;
  double p1 = 0.511636;

  auto c1 = new TCanvas("c1", "", 0, 0, 500, 400);
  c1->cd();
  h->SetLineColor(1);
  h->Draw();

  s = 0.;
  for(int j=0;j<3;j++){
    TF1 *tf_back = new TF1("tf_back", background, (peaks-511.*j)*0.92, (peaks-511.*j)*1.08, 2);
    tf_back->SetParameter(0, 10);
    tf_back->SetParameter(1, 1);
    h->Fit("tf_back", "R");
    TF1 *tf = new TF1("tf", fitFunction, (peaks-511.*j)*0.998, (peaks-511.*j)*1.002, 5);
    tf->FixParameter(0, tf_back->GetParameter(0));
    tf->FixParameter(1, tf_back->GetParameter(1));
    int bin = (int)((peaks-511.*j)-p0)/p1;
    // cout << "bin " << bin << endl;
    tf->SetParameter(2, h->GetBinContent(bin));
    tf->SetParameter(3, peaks-511.*j);
    tf->SetParameter(4, 3.3);
    h->Fit("tf", "R0Q");
    c1->cd();
    tf_back->SetLineColor(2);
    tf_back->Draw("same");
    tf->SetLineColor(4);
    tf->Draw("same");

    int bin_min = (int)((tf->GetParameter(3)-2.5*tf->GetParameter(4)-p0)/p1+0.5);
    int bin_max = (int)((tf->GetParameter(3)+2.5*tf->GetParameter(4)-p0)/p1+0.5);
    cout << "bin min " << bin_min << " " << h->GetBinCenter(bin_min) << " " << h->GetBinContent(bin_min) << endl;
    cout << "bin max " << bin_max << " " << h->GetBinCenter(bin_max) << " " << h->GetBinContent(bin_max) << endl;

    for(int k=bin_min;k<(bin_max+1);k++){
      // cout << h->GetBinContent(k) << endl;
      // cout << tf_back->Eval(h->GetBinCenter(k)) << endl;;
      s += h->GetBinContent(k);
      s -= tf_back->Eval(h->GetBinCenter(k));
    }
  }
    
  cout << "peak " << peaks << "  area " << s << endl;
}

//
void area()
{
  gROOT->SetBatch(1);

  double p0 = -0.746728;
  double p1 = 0.511636;

  TFile *fi = TFile::Open("../cali/rootfile/target1.root"); 
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
  fo.open("area.txt");

  double s;
  for(int i=0;i<4;i++){
    area_single(h, peaks[i], s);
    fo << peaks[i] << " " << s << endl;
    // cout << "peak " << peaks[i] << "  area " << s << endl;
  }

  fo.close();
}

//
void area3()
{
  gROOT->SetBatch(1);

  double p0 = -0.746728;
  double p1 = 0.511636;

  TFile *fi = TFile::Open("../cali/rootfile/target1.root"); 
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

  double s;
  ofstream fo;
  fo.open("area3.txt");

  for(int i=0;i<4;i++){
    area3_single(h, peaks[i], s);
    cout << "peak " << peaks[i] << "  area " << s << endl;
    fo << peaks[i] << " " << s << endl;
  }
  fo.close();
}