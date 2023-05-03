
#define p0 -14.9678
#define p1 0.626573 

void raw2root_target2_285keV()
{
  TFile *fi = TFile::Open("../../../data/14N_Ta/target2/285keV/target2_285keV.root");
  if(fi->IsZombie()){
    cout << "wrong open the file" << endl;
    return;
  }

  TTree *tr = (TTree*)fi->Get("tr");

  double a = p0;
  double b = p0+16384*p1;
  cout << a << " " << b << endl;

  TH1D *h_cali = new TH1D("h_cali", "", 16384, a, b);
  TString leaf1 = TString::Format("%f+%lf*e_trapz[0]>>h_cali",p0,p1);
  TString leaf2 = TString::Format("hit_num_trapz==1 && e_trapz[0]>0");
  cout << leaf1 << endl;
  cout << leaf2 << endl;

  tr->Draw(leaf1.Data(), leaf2.Data());

  TFile *fo = new TFile("rootfile/target2_285keV_cali.root", "recreate");
  fo->cd();
  h_cali->Write();

  fi->Close();
  fo->Close();
}
