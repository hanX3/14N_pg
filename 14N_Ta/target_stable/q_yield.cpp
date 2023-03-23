
void q_yield()
{
  ifstream file_in;
  file_in.open("q_yield.txt");

  ofstream file_out;
  file_out.open("data.txt");

  TGraph *gr1 = new TGraph();
  TGraph *gr2 = new TGraph();
  
  int i = 0;
  Double_t q, yield;
  Double_t q_pre, yield_pre, yield_mean;
  q_pre = 0;
  yield_pre = 0;

  while(1){
    file_in >> q >> yield;
    if(!file_in.good()) break;

    yield_mean = yield/(q-q_pre)*1000000;
    gr1->SetPoint(i, q/1000000., yield_mean);

    file_out << q/1000000. << " " << yield_mean << " ";

    yield_mean = (yield+yield_pre)/q*1000000;
    gr2->SetPoint(i, q/1000000., yield_mean);
    file_out << q/1000000. << " " << yield_mean << endl;

    i++;

    q_pre = q;
    yield_pre += yield;

  }

  file_in.close();
  file_out.close();

  TCanvas *c1 = new TCanvas("c1", "", 0, 0, 480 , 360);
  TCanvas *c2 = new TCanvas("c2", "", 0, 0, 480 , 360);
  
  c1->cd();
  gr1->Draw("AP*");

  c2->cd();
  gr2->Draw("AP*");
}