
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
void area()
{
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

  for(int i=0;i<4;i++){
    for(int j=0;j<3;j++){
      TF1 *tf_back = new TF1("tf_back", background, (peaks[i]-511.*j)*0.92, (peaks[i]-511.*j)*1.08, 2);
      tf_back->SetParameter(0, 10);
      tf_back->SetParameter(1, 1);
      h->Fit("tf_back", "R0Q");
      TF1 *tf = new TF1("tf", fitFunction, (peaks[i]-511.*j)*0.99, (peaks[i]-511.*j)*1.01, 5);
      tf->FixParameter(0, tf_back->GetParameter(0));
      tf->FixParameter(1, tf_back->GetParameter(1));
      int bin = (int)((peaks[i]-511.*j)-p0)/p1;
      cout << "bin " << bin << endl;
      tf->SetParameter(2, 200);
      tf->SetParameter(3, peaks[i]-511.*j);
      tf->SetParameter(4, 3.3);
      h->Fit("tf", "R0Q");
      c1->cd();
      tf_back->SetLineColor(2);
      tf_back->Draw("same");
      tf->SetLineColor(4);
      tf->Draw("same");

      //
      int bin_min = (int)((tf->GetParameter(3)-2.5*tf->GetParameter(4)-p0)/p1+0.5);
      int bin_max = (int)((tf->GetParameter(3)+2.5*tf->GetParameter(4)-p0)/p1+0.5);
      // cout << "bin min " << bin_min << " " << h->GetBinCenter(bin_min) << endl;
      // cout << "bin max " << bin_max << " " << h->GetBinCenter(bin_max) << endl;

      double s = 0.;

      for(int k=bin_min;k<(bin_max+1);k++){
        // cout << h->GetBinContent(k) << endl;
        // cout << tf_back->Eval(h->GetBinCenter(k)) << endl;;
        s += h->GetBinContent(k);
        s -= tf_back->Eval(h->GetBinCenter(k));
      }

      cout << "peak " << tf->GetParameter(3) << "  area " << s << endl;
    }
  }



}
