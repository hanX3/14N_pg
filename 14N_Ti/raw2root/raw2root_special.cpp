
void raw2root_special(TString target, TString energy)
{
  cout << "ana " << target << " " << energy << "keV" << endl;

  ifstream fi;
  fi.open(TString::Format("../../../data/14N_Ti/%s/14N_%skeV_2.txt", target.Data(), energy.Data()).Data());
  if(!fi){
    cout << "can not open file" << endl;
    return ;
  }

  char line[256];
  TString line_new;
  Double_t real_time, live_time;

  TTree *tr = new TTree("tr", "time info");
  tr->Branch("real_time", &real_time, "real_time/D");
  tr->Branch("live_time", &live_time, "live_time/D");

  //
  while(1){
    fi.getline(line, 255);
    // cout << line << endl;

    line_new = TString::Format("%s", line);

    if(line_new.Contains("Channel, Counts")){
      break;
    }

    //
    if(line_new.Contains("Real Time")){
      int a = line_new.Last(',');
      int b = line_new.Length();

      TString real_time_str = line_new(a+1, b);
      real_time = real_time_str.Atof();
    }

    if(line_new.Contains("Live Time")){
      int a = line_new.Last(',');
      int b = line_new.Length();

      TString live_time_str = line_new(a+1, b);
      live_time = live_time_str.Atof();
    }
  }

  cout << "real_time " << real_time << endl;
  cout << "live_time " << live_time << endl;
  tr->Fill();

  //
  TH1D *h = new TH1D("h", "", 16384, 0, 16384);
  Int_t i, c;
  while(1){
    fi.getline(line, 255);
    // cout << line << endl;

    if(!fi.good()){
      break;
    }

    line_new = TString::Format("%s", line);

    int a = line_new.Last(',');
    int b = line_new.Length();
    TString i_str = line_new(0, a);
    i = i_str.Atoi();
    TString c_str = line_new(a+1, b);
    c = c_str.Atoi();

    // cout << i << "  " << c << endl;
    
    h->SetBinContent(i+1, c);
  }

  TFile *file_out = new TFile(TString::Format("%s_%skeV_2.root", target.Data(), energy.Data()).Data(), "recreate");
  file_out->cd();
  h->Write();
  tr->Write();

  delete h;
  file_out->Close();
  fi.close();
}