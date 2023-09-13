
int yield_counts_single(int ep)
{
  double p0 = -0.746728;
  double p1 = 0.511636;
  Double_t bins = 16384;

  Double_t sigma = 2.6;
  Double_t k = 5.;

  Double_t e_min = 6172.-k/2.*sigma;
  Double_t e_max = 6172.+k/2.*sigma;
  // cout << "e_min " << e_min << endl;
  // cout << "e_max " << e_max << endl;

  gStyle->SetOptStat(0);


  TFile *fi1 = TFile::Open(TString::Format("../cali/rootfile/target1_%dkeV_cali.root", ep).Data());
  
  if(fi1->IsZombie()){
    cout << "wrong open the file " << ep << endl;
    return -1;
  }

  TH1D *h1 = (TH1D*)fi1->Get("h_cali");

  // auto c1 = new TCanvas("c1", "c1", 0, 0, 800, 500);
  // c1->cd();
  // h1->Draw();

  int bin_min = (int)((e_min-p0)/p1+0.5);
  int bin_max = (int)((e_max-p0)/p1+0.5);
  // cout << "bin_min " << bin_min << endl;
  // cout << "bin_max " << bin_max << endl;

  int sum = h1->Integral(bin_min, bin_max);
  // cout << "sum " << sum << endl;

  delete h1;

  return sum;
}

//
int yield_counts_single_special(int ep)
{
  double p0 = -0.746728;
  double p1 = 0.511636;
  Double_t bins = 16384;

  Double_t sigma = 2.6;
  Double_t k = 5.;

  Double_t e_min = 6172.-k/2.*sigma;
  Double_t e_max = 6172.+k/2.*sigma;
  // cout << "e_min " << e_min << endl;
  // cout << "e_max " << e_max << endl;

  gStyle->SetOptStat(0);


  TFile *fi1 = TFile::Open(TString::Format("../cali/rootfile/target1_%dkeV_cali_2.root", ep).Data());
  
  if(fi1->IsZombie()){
    cout << "wrong open the file " << ep << endl;
    return -1;
  }

  TH1D *h1 = (TH1D*)fi1->Get("h_cali");

  // auto c1 = new TCanvas("c1", "c1", 0, 0, 800, 500);
  // c1->cd();
  // h1->Draw();

  int bin_min = (int)((e_min-p0)/p1+0.5);
  int bin_max = (int)((e_max-p0)/p1+0.5);
  // cout << "bin_min " << bin_min << endl;
  // cout << "bin_max " << bin_max << endl;

  int sum = h1->Integral(bin_min, bin_max);
  // cout << "sum " << sum << endl;

  delete h1;
  fi1->Close();

  return sum;
}

//
void yield_counts()
{
  ofstream fo1, fo2;
  fo1.open("target1_e_yield.txt");
  fo1.open("target1_e_yield_special.txt");

  Double_t e, q;

  ifstream fi1;
  fi1.open("target1_e_p.txt");
  if(!fi1){
    cout << "can not open the file" << endl;
    return ;
  }

  string line;
  getline(fi1, line);
  cout << " >> " << line << endl;

  map<double, double> m_e_q;
  map<double, double> m_e_yield;

  while(1){
    fi1 >> e >> q;

    if(!fi1.good()) break;

    cout << " >> " << e << " " << q << endl;
    m_e_q.insert(make_pair(e, q));
  }
  fi1.close();

  Double_t yield, yield_unit;
  for(auto it=m_e_q.begin();it!=m_e_q.end();++it){
    cout << it->first << " " << it->second << endl;

    yield = yield_counts_single((int)it->first);
    yield_unit = yield/(it->second);

    m_e_yield.insert(make_pair(it->first, yield_unit));
  }

  auto c1 = new TCanvas("c1", "c1", 0, 0, 800, 500);
  c1->cd();

  auto mg1 = new TMultiGraph();

  TGraph *gr1 = new TGraph();
  int i = 0;
  for(auto it=m_e_yield.begin();it!=m_e_yield.end();++it){
    gr1->SetPoint(i, it->first, it->second);
    i++;

    fo1 << it->first << "  " << it->second << endl;
  }

  gr1->SetMarkerStyle(28);
  gr1->SetMarkerColor(4);
  mg1->Add(gr1);

  //special
  ifstream fi2;
  fi2.open("target1_e_p_special.txt");
  if(!fi2){
    cout << "can not open the file" << endl;
    return ;
  }

  getline(fi2, line);
  cout << " >> " << line << endl;

  map<double, double> m_e_q_special;
  map<double, double> m_e_yield_special;

  while(1){
    fi2 >> e >> q;

    if(!fi2.good()) break;

    cout << " >> " << e << " " << q << endl;
    m_e_q_special.insert(make_pair(e, q));
  }
  fi2.close();

  for(auto it=m_e_q_special.begin();it!=m_e_q_special.end();++it){
    cout << it->first << " " << it->second << endl;

    yield = yield_counts_single_special((int)it->first);
    yield_unit = yield/(it->second);

    m_e_yield_special.insert(make_pair(it->first, yield_unit));
  }

  TGraph *gr2 = new TGraph();
  int j = 0;
  for(auto it=m_e_yield_special.begin();it!=m_e_yield_special.end();++it){
    gr2->SetPoint(j, it->first, it->second);
    j++;

    fo2 << it->first << "  " << it->second << endl;
  }
  gr2->SetMarkerColor(2);
  gr2->SetMarkerStyle(30);

  mg1->Add(gr2);

  mg1->GetXaxis()->SetTitle("Proton Energy [keV]");
  mg1->GetYaxis()->SetTitle("Reaction Yield [Counts/C]");

  mg1->Draw("ap");

  fo1.close();
  fo2.close();
}