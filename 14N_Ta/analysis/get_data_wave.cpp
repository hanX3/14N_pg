#define MAXLENGTH 32768

void get_data_wave(Int_t n)
{
  TFile *file_in = TFile::Open("../../data/R0001.root");
  if(file_in->IsZombie()){
    cout << "wrong open the file" << endl;
    return;
  }

  TTree *tr = (TTree*)file_in->Get("tree");

  UShort_t ltra;
  UShort_t data[MAXLENGTH];
  UShort_t dt[MAXLENGTH];

  tr->SetBranchAddress("size", &ltra);
  tr->SetBranchAddress("data", data);
  tr->SetBranchAddress("dt", dt);

  tr->GetEntry(n);

  ofstream file_out;
  file_out.open(TString::Format("./wave_id%06d.txt",n).Data());

  for(int i=0;i<ltra;i++){
    file_out << i << "  " << data[i] - data[0] << endl;
  }

  file_out.close();
}
