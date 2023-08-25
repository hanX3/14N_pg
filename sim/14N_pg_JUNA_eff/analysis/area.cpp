
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
void area_single(TString filename, double &s, double &ss)
{
  cout << "analysis " << filename << endl;

  int a = filename.Last('_');
  int b = filename.Last('.');
  // cout << "a " << a << endl;
  // cout << "b " << b << endl;

  TString sub = filename(a+1, b-a-1);
  // cout << "n " << sub << endl;

  int p = filename.Last('a');
  int q = filename.Last('_');
  // cout << p << endl;
  // cout << q << endl;
  TString sub_e = filename(p+2, q-p-5);
  int energy = sub_e.Atoi();
  cout << "energy " << energy << endl;

  TFile *f = TFile::Open(filename.Data());
  if(!f){
    cout << "can not open " << filename << endl;
    return;
  }

  TH1D *h = (TH1D*)f->Get(TString::Format("h_sim_%dkeV", energy).Data());
  auto c = new TCanvas();
  ss = h->Integral(10, 16382);
    
  // cout << "fit range " << energy*0.998 << " to " << energy*1.002 << endl;

  TF1 *tf = new TF1("tf", fitFunction, energy*0.998, energy*1.002, 5);
  tf->FixParameter(0, 0);
  tf->FixParameter(1, 0);
  int bin = (int)(energy);

  tf->SetParameter(2, h->GetBinContent(bin));
  tf->SetParameter(3, energy);
  tf->SetParameter(4, 3.3);
  h->Fit("tf", "R");
  c->cd();
  tf->SetLineColor(2);
  tf->Draw("same");

  int bin_min = (int)(tf->GetParameter(3)-2.5*TMath::Abs(tf->GetParameter(4))+0.5);
  int bin_max = (int)(tf->GetParameter(3)+2.5*TMath::Abs(tf->GetParameter(4))+0.5);
  // cout << "bin_min " << bin_min << endl;
  // cout << "bin_max " << bin_max << endl;

  for(int k=bin_min;k<(bin_max+1);k++){
    // cout << h->GetBinContent(k) << endl;
    s += h->GetBinContent(k);
  }

  cout << "peak " << tf->GetParameter(3) << "  area " << s << endl;

  if(sub.Contains("k")){
    int k = sub.Last('k');
    // cout << sub(0, k) << endl;
    cout << energy << " " << s << "  " << ss << "  " << sub(0, k) << "000" << endl; 
  }else{
    cout << energy << " " << s << "  " << ss << "  " << sub << endl;
  }
    
  // delete f;
  // delete tr;
  // delete h;
  // delete c;
}

//
void area3_single(TString filename, double &s, double &ss)
{
  cout << "analysis " << filename << endl;

  int a = filename.Last('_');
  int b = filename.Last('.');
  // cout << "a " << a << endl;
  // cout << "b " << b << endl;

  TString sub = filename(a+1, b-a-1);
  // cout << "n " << sub << endl;

  int p = filename.Last('a');
  int q = filename.Last('_');
  // cout << p << endl;
  // cout << q << endl;
  TString sub_e = filename(p+2, q-p-5);
  int energy = sub_e.Atoi();
  //cout << "energy " << energy << endl;

  TFile *f = TFile::Open(filename.Data());
  if(!f){
    cout << "can not open " << filename << endl;
    return;
  }

  TH1D *h = (TH1D*)f->Get(TString::Format("h_sim_%dkeV", energy).Data());
  auto c = new TCanvas();
  ss = h->Integral(10, 16382);
  
  for(int i=0;i<3;i++){
    cout << "fit range " << energy*0.998 << " to " << energy*1.002 << endl;
    TF1 *tf = new TF1("tf", fitFunction, energy*0.998, energy*1.002, 5);
    
    int bin = (int)(energy);
    tf->FixParameter(0, h->GetBinContent(bin+511./2));
    tf->FixParameter(1, 0);
    tf->SetParameter(2, h->GetBinContent(bin));
    tf->SetParameter(3, energy);
    tf->SetParameter(4, 3.3);
    h->Fit("tf", "R");
    c->cd();
    tf->SetLineColor(2);
    tf->Draw("same");

    int bin_min = (int)(tf->GetParameter(3)-2.5*TMath::Abs(tf->GetParameter(4))+0.5);
    int bin_max = (int)(tf->GetParameter(3)+2.5*TMath::Abs(tf->GetParameter(4))+0.5);
    // cout << "bin_min " << bin_min << endl;
    // cout << "bin_max " << bin_max << endl;

    for(int k=bin_min;k<(bin_max+1);k++){
      // cout << h->GetBinContent(k) << endl;
      s += h->GetBinContent(k);
      s -= tf->GetParameter(0);
    }

    cout << "peak " << tf->GetParameter(3) << "  area " << s << endl;

    if(sub.Contains("k")){
      int k = sub.Last('k');
      // cout << sub(0, k) << endl;
      cout << energy << " " << s << "  " << ss << "  " << sub(0, k) << "000" << endl; 
    }else{
      cout << energy << " " << s << "  " << ss << "  " << sub << endl;
    }
    
    // delete f;
    // delete tr;
    // delete h;
    // delete c;

    energy -= 511;
  }
  
}

//
void area(int dis)
{
  gROOT->SetBatch(1);
  vector<TString> v_filename;
  
  TString filename;
  for(int energy=1000;energy<=12500;energy+=500){
    filename = TString::Format("./dis_%dmm/hist/mc_dis_%dmm_gamma_%dkeV_10000k.root", dis, dis, energy);

    // cout << filename << endl;
    v_filename.push_back(filename);
  }

  ofstream fo;
  fo.open(TString::Format("./dis_%dmm/area_energy.txt", dis));

  double s = 0.;
  double ss = 0.;
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

    if(energy<2000) continue;

    s = 0.;
    ss = 0.;
    area_single(*it, s, ss);
    cout << "s " << s << endl;
    cout << "ss " << ss << endl;

    if(sub.Contains("k")){
      int k = sub.Last('k');
      // cout << sub(0, k) << endl;
      fo << energy << " " << s << "  " << ss << "  " << sub(0, k) << "000" << endl; 
    }else{
      fo << energy << " " << s << "  " << ss << "  " << sub << endl;
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

//
void area3(int dis)
{
  gROOT->SetBatch(1);

  vector<TString> v_filename;
  
  TString filename;
  for(int energy=1000;energy<=12500;energy+=500){
    filename = TString::Format("./dis_%dmm/hist/mc_dis_%dmm_gamma_%dkeV_10000k.root", dis, dis, energy);

    // cout << filename << endl;
    v_filename.push_back(filename);
  }

  ofstream fo;
  fo.open(TString::Format("./dis_%dmm/area3_energy.txt", dis));

  double s = 0.;
  double ss = 0.; 
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

    if(energy<2000) continue;

    s = 0.;
    ss = 0.; 
    area3_single(*it, s, ss);

    if(sub.Contains("k")){
      int k = sub.Last('k');
      // cout << sub(0, k) << endl;
      fo << energy << " " << s << "  " << ss << "  " << sub(0, k) << "000" << endl; 
    }else{
      fo << energy << " " << s << "  " << ss << "  " << sub << endl;
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