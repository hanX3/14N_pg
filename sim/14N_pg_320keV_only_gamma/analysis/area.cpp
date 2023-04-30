
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


void area(int energy)
{
  vector<TString> v_filename;
  
  ifstream fi;
  fi.open(TString::Format("filename_%dkeV.txt", energy).Data());
  if(!fi){
    cout << "can not open the file" << endl;
    return;
  }


  TString filename;
  while(1){
    fi >> filename;
    if(!fi.good()) break;

    // cout << filename << endl;
    v_filename.push_back(filename);
  }

  vector<TString>::iterator it;
  for(it=v_filename.begin();it!=v_filename.end();++it){
    cout << "analysis " << *it << endl;

    TFile *f = TFile::Open((*it).Data());
    if(!f){
      cout << "can not open " << *it << endl;
      return;
    }

    TH1D *h = new TH1D("h", "", 8192, 0, 8192);
    TTree *tr = (TTree*)f->Get("tree");
    auto c = new TCanvas();
    tr->Draw("energy0>>h", "energy0>10");
    
    for(int i=0;i<3;i++){
      TF1 *tf_back = new TF1("tf_back", background, (energy-511.*i)*0.92, (energy-511.*i)*1.08, 2);
      tf_back->SetParameter(0, 10);
      tf_back->SetParameter(1, 1);
      h->Fit("tf_back", "R0Q");

      if(i==0){
        tf_back->SetParameter(0, 0);
        tf_back->SetParameter(1, 0);
      }

      TF1 *tf = new TF1("tf", fitFunction, (energy-511.*i)*0.998, (energy-511.*i)*1.002, 5);
      tf->FixParameter(0, tf_back->GetParameter(0));
      tf->FixParameter(1, tf_back->GetParameter(1));
      int bin = (int)(energy-511.*i);

      tf->SetParameter(2, h->GetBinContent(bin));
      tf->SetParameter(3, energy-511.*i);
      tf->SetParameter(4, 3.3);
      h->Fit("tf", "R0Q");
      c->cd();
      tf_back->SetLineColor(2);
      tf_back->Draw("same");
      tf->SetLineColor(4);
      tf->Draw("same");

      int bin_min = (int)(tf->GetParameter(3)-2.5*tf->GetParameter(4)+0.5);
      int bin_max = (int)(tf->GetParameter(3)+2.5*tf->GetParameter(4)+0.5);
      // cout << "bin_min " << bin_min << endl;
      // cout << "bin_max " << bin_max << endl;

      double s = 0.;

      for(int k=bin_min;k<(bin_max+1);k++){
        // cout << h->GetBinContent(k) << endl;
        // cout << tf_back->Eval(h->GetBinCenter(k)) << endl;;
        s += h->GetBinContent(k);
        s -= tf_back->Eval(h->GetBinCenter(k));
      }

      cout << "peak " << tf->GetParameter(3) << "  area " << s << endl;
    }

    // delete f;
    // delete tr;
    // delete h;
    // delete c;
  }

  return;
}
