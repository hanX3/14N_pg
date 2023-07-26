
#define BINS 16384

void get_br(TString str, Double_t rebin)
{
  double p0 = -0.746728;
  double p1 = 0.511636;

  double fit_range1 = 4000;
  double fit_range2 = 8000;

  gROOT->SetBatch(0);
  gStyle->SetOptStat(0);

  int gamma[7] = {7556, 6859, 6792, 6172, 6126, 5240, 5181};
  double p_paper[7] = {0.015, 0.0014, 0.23, 0.583, 0.1, 0.0022, 0.169}; // set 6126keV as 0.1 percent

  TFile *fi_exp = TFile::Open("../cali/rootfile/target1.root");
  TH1D *h_exp = (TH1D*)fi_exp->Get("h_cali");
  h_exp->Rebin(rebin);

  //
  TFile *fi_mc = TFile::Open(TString::Format("mc_%s.root", str.Data()));
  if(fi_mc->IsZombie()){
    cout << "can not open " << TString::Format("mc_%s.root", str.Data()) << endl;
    return;
  }

  // FractionFitter
  TObjArray *mc = new TObjArray(7);  // MC histograms are put in this array

  TH1D *h_sim[7];
  for(int i=0;i<7;i++){
    h_sim[i]= (TH1D*)fi_mc->Get(TString::Format("h_sim_%dkeV", gamma[i]).Data());
    h_sim[i]->Rebin(rebin);
    mc->Add(h_sim[i]);
  }

  TFractionFitter *fit = new TFractionFitter(h_exp, mc); // initialise
  for(int i=0;i<7;i++){
    fit->Constrain(i, 0., 1.);  // constrain fraction 1 to be between 0 and 1
  }
  fit->Constrain(0, 0.014, 0.016);
  fit->Constrain(1, 0.001, 0.002);
  fit->Constrain(2, 0.20, 0.26);
  fit->Constrain(3, 0.55, 0.61);

  // exclude
  // for(int i=(int)((6000-p0)/p1/rebin+1);i<(int)((6200-p0)/p1/rebin+1);i++){
  //   cout << "i = " << i << endl;
  //   fit->ExcludeBin(i);
  // }

  // include
  // for(int i=0;i<6;i++){
  //   for(int j=(int)((gamma[i]-100.-p0)/p1/rebin+1);j<(int)((gamma[i]+100.-p0)/p1/rebin+1);j++){
  //     fit->IncludeBin(j);
  //   }
  // }

  int fit_range_bin1 = (int)((fit_range1-p0)/p1/rebin+1);
  int fit_range_bin2 = (int)((fit_range2-p0)/p1/rebin+1);
  cout << "fit_range_bin1 " << fit_range_bin1 << endl;
  cout << "fit_range_bin2 " << fit_range_bin2 << endl;
  fit->SetRangeX(fit_range_bin1, fit_range_bin2); // use particular bins in the fit
  Int_t status = fit->Fit();  // perform the fit
  cout << "fit status: " << status << endl;

  // Display
  gStyle->SetOptStat(0);
  TCanvas *c = new TCanvas("c", "FractionFitter example", 1600, 800);
  c->SetLogy();
  c->cd();
  TLatex lat;
  lat.SetTextSize(.035);
  Char_t texte[600];
  double p[7], p_error[7];
  if(status == 0){  // check on fit status
    TH1D *result = (TH1D*)fit->GetPlot();
    for(int i=0;i<7;i++){
      fit->GetResult(i, p[i], p_error[i]);
      printf("%d keV: paper %.3f, estim. %.3f +/- %.3f\n", gamma[i], p_paper[i], p[i], p_error[i]);
    }

    h_exp->SetLineColor(2);
    h_exp->GetXaxis()->SetRangeUser(fit_range1, fit_range2);
    h_exp->Draw();
    result->Draw("same");
    for(int i=0;i<7;i++){
      sprintf(texte, "%d keV: paper %.2f, estimated %.2f +/- %.2f\n", gamma[i], p_paper[i], p[i], p_error[i]);
      lat.DrawTextNDC(0.65, 0.05*(i+4), texte);
    }
  }

  TCanvas *c2 = new TCanvas("c2", "", 1600, 800);
  c2->SetLogy();
  c2->cd();
  h_exp->Draw();

  double sum_sim = h_exp->Integral(fit_range_bin1, fit_range_bin2);
  cout << "sum_sim " << sum_sim << endl;

  TH1D *h_sim_scale[7];
  TH1F *mc_add = new TH1F("mc_add", "", BINS, p0, p0+p1*BINS);

  for(int i=0;i<7;i++){
    h_sim_scale[i] = (TH1D*)h_sim[i]->Clone(TString::Format("h_sim_sacle_%dkeV", gamma[i]).Data());
    h_sim_scale[i]->Scale((double)sum_sim/(double)(h_sim_scale[i]->Integral(fit_range_bin1, fit_range_bin2))*p_paper[i]);
    h_sim_scale[i]->SetLineColor(i+1);

    h_sim_scale[i]->DrawClone("same hist");

    mc_add->Add(h_sim_scale[i]);
  }

  mc_add->SetLineColor(1);
  mc_add->Draw("same hist");
}

void get_counts()
{
  gStyle->SetOptStat(1111111);

  double p0 = -0.746728;
  double p1 = 0.511636;

  TFile *fi = TFile::Open("../../sim/14N_pg_JUNA_only_gamma/data/20230509_14h51m56s_gamma_7556keV_10000k.root");
  TTree *tr;
  tr = (TTree*)fi->Get("tree");

  TH1D *h = new TH1D("h", "", 16384, p0, p0+p1*BINS);
  h->GetXaxis()->SetRangeUser(4000, 8000);

  TCanvas *c = new TCanvas("c", "", 0, 0, 1400, 500);
  c->cd();
  c->SetLogy();
  tr->Draw("energy0>>h", "energy0>10", "");

  // h->Draw();
}


void get_mc_hist(TString str)
{
  gROOT->SetBatch(1);

  double p0 = -0.746728;
  double p1 = 0.511636;
  int gamma[7] = {7556, 6859, 6792, 6172, 6126, 5240, 5181};

  ifstream fi;
  fi.open(TString::Format("filename_%s.dat", str.Data()));

  if(!fi){
    cout << "can not open " << TString::Format("filename_%s.dat", str.Data()) << endl;
    return ;
  }

  TFile *fi_out = new TFile(TString::Format("mc_%s.root",str.Data()), "recreate");
  TFile *fi_sim[7];
  TTree *tr_sim[7];
  TH1D *h_sim[7];
  int i = 0;

  TString fi_name;
  while(1){
    fi >> fi_name;
    if(!fi.good()) break;

    cout << "fi_name " << fi_name << endl;
    fi_sim[i] = TFile::Open(fi_name.Data());
    if(fi_sim[i]->IsZombie()){
      cout << "can not open " << fi_name << endl;
      return;
    }

    tr_sim[i] = (TTree*)fi_sim[i]->Get("tree");
    h_sim[i] = new TH1D(TString::Format("h_sim_%dkeV", gamma[i]).Data(), "", 16384, p0, p0+p1*BINS);
    tr_sim[i]->Draw(TString::Format("energy0>>h_sim_%dkeV", gamma[i]).Data(), "energy0>10", "Q");

    fi_out->cd();
    h_sim[i]->Write();

    i++;
  }

  fi_out->Close();
}