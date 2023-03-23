
// #define FILEPATH "../../data/R0004/"
// #define FILENAME "R0004_000000000_001000000_ana.root"
// #define FILEOUT "../../data/R0004/hist_trapz.txt"

// #define FILEPATH "../../data/R0004/"
// #define FILENAME "R0004_ana.root"
// #define FILEOUT "./R0004_hist_trapz_cali.txt"

// #define FILEPATH "../../data/target1/"
// #define FILENAME "target1_ana.root"
// #define FILEOUT "./target1_hist_trapz_cali.txt"

#define FILEPATH "../../data/target2/281keV/"
#define FILENAME "target2_281keV.root"
#define FILEOUT "./target2_281keV_hist_trapz_cali.txt"


#define p0 0.023171
#define p1 0.624471

void get_data_hist_cali()
{
  TFile *file_in = TFile::Open(TString::Format("%s%s",FILEPATH,FILENAME).Data());
  if(file_in->IsZombie()){
    cout << "wrong open the file" << endl;
    return;
  }

  TTree *tr = (TTree*)file_in->Get("tr");

  int a = (int)p0;
  int b = (int)(p0+20000*p1+1);
  cout << a << " " << b << endl;
  int c = b-a;

  TH1D *h1 = new TH1D("h1", "", c, a, b);
  TString leaf1 = TString::Format("%f+%lf*e_trapz[0]>>h1",p0,p1);
  TString leaf2 = TString::Format("hit_num_trapz==1 && e_trapz[0]>0");
  cout << leaf1 << endl;
  cout << leaf2 << endl;

  tr->Draw(leaf1.Data(), leaf2.Data());

  ofstream file_out;
  file_out.open(TString::Format("%s",FILEOUT).Data());

  for(int i=0;i<h1->GetNbinsX();i++){
    file_out << i << " " << h1->GetBinContent(i) << endl;
  }

  file_out.close();
}