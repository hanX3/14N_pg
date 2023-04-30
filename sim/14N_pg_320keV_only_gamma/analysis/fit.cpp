
void fit(int energy, double area)
{
  ifstream fi;
  fi.open(TString::Format("area_%dkeV.txt", energy));
  if(!fi){
    cout << "can not open the file" << endl;
    return;
  }

  double s, n;
  map<double, double> m_s_n; // number_area
  while(1){
    fi >> s >> n;
    if(!fi.good()) break;

    m_s_n.insert(make_pair(s, n));
  }

  TGraph *gr = new TGraph();
  int i = 0;
  for(auto it=m_s_n.begin();it!=m_s_n.end();++it){
    // cout << it->first << " " << it->second << endl;
    gr->SetPoint(i, it->first, it->second);
    i++;
  }

  auto c = new TCanvas();
  c->cd();
  gr->Draw("AP*");

  gr->Fit("pol1");
  TF1 *tf_pol1 = ((TF1*)(gROOT->GetListOfFunctions()->FindObject("pol1")));
  // cout << "pol1 p0 " << tf_pol1->GetParameter(0) << endl;
  // cout << "pol1 p1 " << tf_pol1->GetParameter(1) << endl;

  double nn = tf_pol1->Eval(area);
  cout << "nn " << nn << endl;

}
