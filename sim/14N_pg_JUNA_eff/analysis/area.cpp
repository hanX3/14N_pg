
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


void area()
{
  vector<TString> v_filename;
  
  ifstream fi;
  fi.open(TString::Format("filename.txt").Data());
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

  ofstream fo;
  fo.open(TString::Format("area_energy.txt"));

  vector<TString>::iterator it;
  for(it=v_filename.begin();it!=v_filename.end();++it){
    cout << "analysis " << *it << endl;

    // cout << "size " << it->Length() << endl;
    int a = it->Last('_');
    int b = it->Last('.');
    // cout << "a " << a << endl;
    // cout << "b " << b << endl;

    TString sub = (*it)(a+1, b-a-1);
    // cout << "n " << sub << endl;

    int p = it->Last('a');
    int q = it->Last('_');
    // cout << p << endl;
    // cout << q << endl;
    TString sub_e = (*it)(p+2, q-p-5);
    int energy = sub_e.Atoi();
    //cout << "energy " << energy << endl;

    // if(energy!=1500) continue;
    TFile *f = TFile::Open((*it).Data());
    if(!f){
      cout << "can not open " << *it << endl;
      return;
    }

    TH1D *h = new TH1D("h", "", 20000, 0, 20000);
    TTree *tr = (TTree*)f->Get("tree");
    auto c = new TCanvas();
    tr->Draw("energy0>>h", "energy0>10");
    
    // cout << "fit range " << energy*0.998 << " to " << energy*1.002 << endl;

    TF1 *tf = new TF1("tf", fitFunction, energy*0.998, energy*1.002, 5);
    tf->FixParameter(0, 0);
    tf->FixParameter(1, 0);
    int bin = (int)(energy);

    tf->SetParameter(2, h->GetBinContent(bin));
    tf->SetParameter(3, energy);
    tf->SetParameter(4, 3.3);
    h->Fit("tf", "R0Q");
    c->cd();
    tf->SetLineColor(4);
    tf->Draw("same");

    int bin_min = (int)(tf->GetParameter(3)-2.5*TMath::Abs(tf->GetParameter(4))+0.5);
    int bin_max = (int)(tf->GetParameter(3)+2.5*TMath::Abs(tf->GetParameter(4))+0.5);
    // cout << "bin_min " << bin_min << endl;
    // cout << "bin_max " << bin_max << endl;

    double s = 0.;

    for(int k=bin_min;k<(bin_max+1);k++){
      // cout << h->GetBinContent(k) << endl;
      s += h->GetBinContent(k);
    }

    cout << "peak " << tf->GetParameter(3) << "  area " << s << endl;

    if(sub.Contains("k")){
      int k = sub.Last('k');
      // cout << sub(0, k) << endl;
      fo << energy << " " << s << "  " << h->Integral(10, 20000) << "  " << sub(0, k) << "000" << endl; 
    }else{
      fo << energy << " " << s << "  " << h->Integral(10, 20000) << "  " << sub << endl;
    }
    
    // delete f;
    // delete tr;
    // delete h;
    // delete c;
  }
  fo << endl;
  fo.close();

  return;
}
