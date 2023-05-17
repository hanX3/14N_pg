
void fit()
{
  ifstream fi;
  fi.open(TString::Format("area_energy.txt"));
  if(!fi){
    cout << "can not open the file" << endl;
    return;
  }

  double e, s, st, n;
  double eff, eff_t;
  map<double, double> m_e_eff; // energy peak effective
  map<double, double> m_e_eff_t; // energy peak_eff/total_eff
  while(1){
    fi >> e >> s >> st >> n;
    if(!fi.good()) break;

    eff = s/n;
    eff_t = st/n;
    m_e_eff.insert(make_pair(e, eff));
    m_e_eff_t.insert(make_pair(e, eff/eff_t));
  }
  fi.close();

  // eff
  TGraph *gr1 = new TGraph();
  TGraph *gr2 = new TGraph();
  int i = 0;
  for(auto it=m_e_eff.begin();it!=m_e_eff.end();++it){
    // cout << it->first << " " << it->second << endl;
    gr1->SetPoint(i, it->first, it->second);
    gr2->SetPoint(i, TMath::Log(it->first), TMath::Log(it->second));
    i++;
  }

  // eff_t
  TGraph *gr3 = new TGraph();
  TGraph *gr4 = new TGraph();
  i = 0;
  for(auto it=m_e_eff_t.begin();it!=m_e_eff_t.end();++it){
    // cout << it->first << " " << it->second << endl;
    gr3->SetPoint(i, it->first, it->second);
    gr4->SetPoint(i, TMath::Log(it->first), TMath::Log(it->second));
    i++;
  }

  auto cc1 = new TCanvas();
  cc1->cd();
  gr1->Draw("AP*");

  auto cc2 = new TCanvas();
  cc2->cd();
  gr2->Draw("AP*");
  TF1 *tf1_pol2 = new TF1("tf1_pol2", "pol2");
  gr2->Fit("tf1_pol2");
  double tf1_p0 = tf1_pol2->GetParameter(0);
  double tf1_p1 = tf1_pol2->GetParameter(1);
  double tf1_p2 = tf1_pol2->GetParameter(2);

  // eff_t
  auto cc3 = new TCanvas();
  cc3->cd();
  gr3->Draw("AP*");

  auto cc4 = new TCanvas();
  cc4->cd();
  gr4->Draw("AP*");
  TF1 *tf2_pol2 = new TF1("tf2_pol2", "pol2");
  gr4->Fit("tf2_pol2");
  double tf2_p0 = tf2_pol2->GetParameter(0);
  double tf2_p1 = tf2_pol2->GetParameter(1);
  double tf2_p2 = tf2_pol2->GetParameter(2);

  cout << "pol2 p0 " << tf1_p0 << endl;
  cout << "pol2 p1 " << tf1_p1 << endl;
  cout << "pol2 p2 " << tf1_p2 << endl;
  cout << "pol2 p0 " << tf2_p0 << endl;
  cout << "pol2 p1 " << tf2_p1 << endl;
  cout << "pol2 p2 " << tf2_p2 << endl;

  //
  // eff = TMath::Exp(tf1_pol2->Eval(TMath::Log(7556.)));
  // cout << "eff 7556 keV" << eff << endl;

  double ee[6] = {7556, 6859, 6792, 6172, 5240, 5181};
  // double bb[6] = {1.5, 0.14, 23.0, 58.3, 0.22, 16.9}; //2016Daigle
  double bb[6] = {1.46524, 0., 23.2531, 58.5047, 0., 16.8328};

  double y1[6];
  double y2[6];

  memset(y1, 0, sizeof(double)*6);
  memset(y2, 0, sizeof(double)*6);

  for(int i=0;i<6;i++){
    y1[i] = bb[i]*TMath::Exp(tf1_pol2->Eval(TMath::Log(ee[i])));
    y2[i] = y1[i];
  }

  for(int i=1;i<6;i++){
    y2[0] += bb[i]*TMath::Exp(tf1_pol2->Eval(TMath::Log(ee[i])))*TMath::Exp(tf1_pol2->Eval(TMath::Log(ee[0]-ee[i])));
    
    cout << TMath::Exp(tf1_pol2->Eval(TMath::Log(ee[0]-ee[i]))) << endl;
    cout << TMath::Exp(tf2_pol2->Eval(TMath::Log(ee[0]-ee[i]))) << endl;

    y2[i] *= (1-TMath::Exp(tf1_pol2->Eval(TMath::Log(ee[0]-ee[i])))/TMath::Exp(tf2_pol2->Eval(TMath::Log(ee[0]-ee[i]))));
  }

  ofstream fo1;
  fo1.open("y1y2.txt");

  for(int i=0;i<6;i++){
    cout << "area " << ee[i] << " " << y1[i] << " after summing " << y2[i] << endl;
    fo1 << ee[i] << " " << y1[i] << " " << y2[i] << endl; 
  }
  fo1.close();

  ofstream fo2;
  fo2.open("eff.txt");
  for(int i=0;i<6;i++){
    fo2 << ee[i] << " " << TMath::Exp(tf1_pol2->Eval(TMath::Log(ee[i]))) << endl;
  }
  fo2.close();
}
