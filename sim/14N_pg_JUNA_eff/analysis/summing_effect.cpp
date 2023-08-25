
void summing_effect()
{
  TString y1y2_filename;

  vector<double> v_dis;
  vector<double> v_eff_small;
  vector<double> v_eff_large;

  double energy, eff_small, eff_large;

  for(int dis=20;dis<=300;dis+=20){
    v_dis.push_back(dis);

    y1y2_filename = TString::Format("./dis_%dmm/y1y2.txt", dis);
    ifstream fi;
    fi.open(y1y2_filename.Data());
    if(!fi){
      cout << "can not open " << y1y2_filename << endl;
      return;
    }

    fi >> energy >> eff_small >> eff_large;
    // cout << energy << " " << eff_small << " " << eff_large << endl;

    v_eff_small.push_back(eff_small);
    v_eff_large.push_back(eff_large);
  }

  TGraph *gr = new TGraph();
  for(int i=0;i<v_dis.size();i++){
    gr->SetPoint(i+1, v_dis[i], 100.*(v_eff_large[i]-v_eff_small[i])/v_eff_large[i]);
  }

  auto c1 = new TCanvas("c1", "", 0, 0, 800, 500);
  c1->cd();
  gr->GetXaxis()->SetTitle("Distance [mm]");
  gr->GetYaxis()->SetTitle("Proportion of summing effect [%]");
  gr->Draw("AP*");
}