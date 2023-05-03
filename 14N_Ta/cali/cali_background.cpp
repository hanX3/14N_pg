
#define FILENAME "background_cali.txt"

void cali_background()
{
  ifstream file_in;
  file_in.open(TString::Format("%s",FILENAME));

  TGraph *gr = new TGraph();
  
  Double_t energy, channel;
  int i = 0;

  char head[1024];
  file_in.getline(head, 1024);

  while(1){
    file_in >> energy >> channel;
    if(!file_in.good()) break;

    gr->SetPoint(i, channel, energy);
    cout << channel << " " << energy << endl;
    i++;
  }
  file_in.close();

  gr->Draw("AP*");
  gr->Fit("pol1");

  TF1 *tf = (TF1*)gr->GetFunction("pol1");
  Double_t par_ab[2];
  tf->GetParameters(&par_ab[0]);

  cout << "par0 = " << par_ab[0] << endl;
  cout << "par1 = " << par_ab[1] << endl;
}
