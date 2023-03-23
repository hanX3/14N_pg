#include "WaveAnalysis.h"

//
WaveAnalysis::WaveAnalysis(const std::string &filename_in, const std::string &filename_out, int a, int b)
{
  benchmark = new TBenchmark;

  entry_start = a;
  entry_stop = b;

  file_in = TFile::Open(filename_in.c_str());
  if(file_in->IsZombie()){
    std::cout << "can not open " << filename_in << std::endl;
  }
  tr_in = (TTree*)file_in->Get("tree");
  tr_in->SetBranchAddress("size", &ltra);
  tr_in->SetBranchAddress("data", data);
  total_entry = tr_in->GetEntries();

  memset(&caen_rccr2_par, 0, sizeof(CAEN_RCCR2_PAR));
  memset(&trapz_par, 0, sizeof(TRAPZ_PAR));

  memset(data, 0, MAXLENGTH*sizeof(UShort_t));
  memset(data_bl, 0, MAXLENGTH*sizeof(Double_t));
  memset(data_rccr2, 0, MAXLENGTH*sizeof(Double_t));
  memset(data_trapz, 0, MAXLENGTH*sizeof(Double_t));
#ifdef OPENFITWAVE
  memset(data_fit, 0, MAXLENGTH*sizeof(Double_t));
#endif

  caen_rccr2_par.pre_trigger = RCCR2PARPRETRIGGER;
  caen_rccr2_par.smooth_length = RCCR2PARSMOOTHLENGTH;
  caen_rccr2_par.rise_length = RCCR2PARRISELENGTH;

  trapz_par.decay_length = TRAPPARDECAYLENGTH;
  trapz_par.rise_length = TRAPPARRISELENGTH;
  trapz_par.falt_top = TRAPPARFLATTOP;
  trapz_par.pre_trigger = TRAPPARPRITRIGGER;
  trapz_par.peak_delay = TRAPPARPEAKDELAY;
  trapz_par.peak_mean = TRAPPARPEAKMEAN;

#ifdef OPENFITWAVE
  // Fit
  gr = new TGraph();
#endif

  file_out = new TFile(filename_out.c_str(), "recreate");
  tr_out = new TTree("tr", "wave analysis info");
  tr_out->Branch("b_std_sqrt", &b_std_sqrt, "b_std_sqrt/D");

  TString leaf1 = TString::Format("e_trapz[%d]/D:t0_trapz[%d]/D:hit_num_trapz/s", PILEUPMAX, PILEUPMAX);
  tr_out->Branch("trapz_result", &trapz_result, leaf1.Data());

#ifdef OPENFITWAVE
  TString leaf2 = TString::Format("e_fit[%d]/D:t0_fit[%d]/D:tr_fit/D:td_fit/D:hit_num_fit/s", PILEUPMAX, PILEUPMAX);
  tr_out->Branch("fit_result", &fit_result, leaf2.Data());
#endif

#ifdef DEBUGDRAWOPTION
  cav1 = new TCanvas("cav1", "", 0, 0, 480, 360);
#endif
}

//
WaveAnalysis::~WaveAnalysis()
{

}

//
bool WaveAnalysis::GetWave(Long64_t n)
{
  ltra = 0;
  memset(data, 0, sizeof(UShort_t)*MAXLENGTH);
  tr_in->GetEntry(n);
  for(UInt_t i=0;i<ltra;i++){
    data_pol[i] = data[i]*POLARITY;
  }

  caen_rccr2_par.threshold = RCCR2PARTHRESHOLD;
  memset(&trapz_result, 0, sizeof(TRAPZ_RESULT));

  return true;
}

//
void WaveAnalysis::Process()
{
  benchmark->Start("analysis");

  for(Long64_t i=entry_start;i<entry_stop;i++){
    if(i==total_entry) break;
    if(i%10000==0){
    std::cout << i << "/" << total_entry << std::endl;
  }

#ifdef OPENFITWAVE
    FitWave(i);
#else
    ProcessEntry(i);
#endif

    tr_out->Fill();
  }

  file_out->cd();
  tr_out->Write();
  file_out->Close();

  file_in->Close();

  benchmark->Show("analysis");
}

//
bool WaveAnalysis::ProcessEntry(Long64_t n)
{
  GetWave(n);

  // Baseline check
  Double_t b = 0.;
  for(int i=0;i<PRETRIGGER;i++){
    b += data_pol[i];
  }
  b /= (Double_t)PRETRIGGER;
  Double_t b_std = 0.;
  for(int i=0;i<PRETRIGGER;i++){
    b_std += (data_pol[i]-b)*(data_pol[i]-b);
  }
  b_std_sqrt = sqrt(b_std)/PRETRIGGER;

  // Energy
  RCCR2(n);
  caen_rccr2_par.threshold = RCCR2PARTHRESHOLD;
  Bool_t trigger_armed = 0;
  UInt_t ii, jj = 0;
  UShort_t hit_num;
  Double_t ee1 = 0., ee2 =0.;
  while(1){
    ii = 0;
    hit_num = 0;
    trigger_armed = 0;
    for(UShort_t i=10;i<(ltra-10);i++){
      if(trigger_armed==0 && data_rccr2[i]>=caen_rccr2_par.threshold){
        trigger_armed = 1;
        ii = i-1;
        ee1 = (data_pol[ii-3]+data_pol[ii-2]+data_pol[ii-1])/3.;
      }
      if(trigger_armed==1 && data_rccr2[i]>=0 && data_rccr2[i+1]<0){
        trigger_armed = 0;
        ee2 = (data_pol[i+1]+data_pol[i+2]+data_pol[i+3])/3.;
        if(i-ii>=5 && ee2-ee1>=caen_rccr2_par.threshold){
          if(hit_num<PILEUPMAX){
            trapz_result.time_tag[hit_num] = (Double_t)i + (Double_t)data_rccr2[i]/((Double_t)data_rccr2[i]-(Double_t)data_rccr2[i+1]);
            hit_num++;
          } 
        }
      }
    }

    if(hit_num==0)
      caen_rccr2_par.threshold = caen_rccr2_par.threshold-1;
    else if(hit_num>PILEUPMAX){
      caen_rccr2_par.threshold = caen_rccr2_par.threshold+1;
    }
    else if(hit_num>0 && hit_num<=PILEUPMAX) break;

    jj++;
    if(jj>0xffff || caen_rccr2_par.threshold<=0x0000 || caen_rccr2_par.threshold>=0xffff){
      hit_num = 0;
      break;
    }
  }

  if(trapz_par.peak_delay==0){
    trapz_par.peak_delay = trapz_par.rise_length + trapz_par.falt_top/2;
  }
  if(trapz_par.peak_mean==0){
    trapz_par.peak_mean = trapz_par.falt_top/4;
  }

  Double_t pre_trigger_set = 4.*caen_rccr2_par.smooth_length+caen_rccr2_par.rise_length;
  trapz_par.pre_trigger = (trapz_result.time_tag[0]>pre_trigger_set)?(trapz_result.time_tag[0]-pre_trigger_set):pre_trigger_set;

#ifdef DEBUGWAVEANALYSIS
  std::cout << "hit_num " << hit_num << std::endl;
  std::cout << "peak_delay " << trapz_par.peak_delay << std::endl;
  std::cout << "peak_mean " << trapz_par.peak_mean << std::endl;
  std::cout << "pre_trigger " << trapz_par.pre_trigger << std::endl;
#endif

  Double_t e_sum = 0;
  UInt_t e_start = 0;
  if(hit_num>0){
    Trapezoid(n);
  }
  trapz_result.trigger_num = hit_num;
  for(UInt_t i=0;i<hit_num;i++){
    e_sum = 0;
    e_start = (UInt_t)(trapz_result.time_tag[i]) + trapz_par.peak_delay;
    if(e_start>=ltra) break;
    if((e_start+trapz_par.peak_mean)<ltra){
      for(UInt_t j=e_start;j<(e_start+trapz_par.peak_mean);j++){
        e_sum += data_trapz[j];
      }
      trapz_result.energy[i] = (e_sum>0 ? e_sum/trapz_par.peak_mean*16.0 : 0);
    }
    else{
      for(UInt_t j=e_start;j<ltra;j++){
        e_sum += data_trapz[j];
      }
      trapz_result.energy[i] = (e_sum>0 ? e_sum/trapz_par.peak_mean*16.0 : 0);
    }
  }

#ifdef DEBUGWAVEANALYSIS
  std::cout << "n " << n << std::endl;
  std::cout << "hit_num " << hit_num << std::endl;
  std::cout << "time_tag " << trapz_result.time_tag[0] << std::endl;
  std::cout << "time_tag " << trapz_result.time_tag[1] << std::endl;
  std::cout << "energy " << trapz_result.energy[0] << std::endl;
  std::cout << "energy " << trapz_result.energy[1] << std::endl;
#endif

  return true;
}

//
void WaveAnalysis::RCCR2(Long64_t n)
{
  memset(data_bl, 0, ltra*sizeof(Double_t));
  memset(data_rccr2, 0, ltra*sizeof(Double_t));

  baseline = 0.;
  for(UInt_t i=0;i<caen_rccr2_par.pre_trigger;i++){
    baseline += data_pol[i];
  }
  baseline /= (Double_t)caen_rccr2_par.pre_trigger;

  for(UShort_t i=0;i<ltra;i++){
    data_bl[i] = data_pol[i]-baseline; 
  }

  for(UShort_t i=(2*caen_rccr2_par.rise_length+caen_rccr2_par.smooth_length);i<ltra;i++){
    data_rccr2[i] = RCCR2XX(data_bl, i, caen_rccr2_par.smooth_length, caen_rccr2_par.rise_length) - RCCR2XX(data_bl, i-caen_rccr2_par.rise_length, caen_rccr2_par.smooth_length, caen_rccr2_par.rise_length);
  }
}

//
void WaveAnalysis::Trapezoid(Long64_t n)
{
  Double_t *d = (Double_t*)malloc(ltra*sizeof(Double_t));
  Double_t *q = (Double_t*)malloc(ltra*sizeof(Double_t));
  Double_t *ss = (Double_t*)malloc(ltra*sizeof(Double_t));
  
  memset(data_trapz, 0, ltra*sizeof(Double_t));

  Double_t M = trapz_par.decay_length;
  UInt_t k = trapz_par.rise_length;
  UInt_t m = trapz_par.falt_top;
  UInt_t l = k+m;

  for(UShort_t i=0;i<ltra;i++){
    if(i==0){
      d[i]=data_bl[i];
      q[i]=d[i];
      ss[i]=q[i]+M*d[i];
    }
    else if(i>0 && i<k){
      d[i]=data_bl[i];
      q[i]=q[i-1]+d[i];
      ss[i]=ss[i-1]+q[i]+M*d[i];
    }
    else if(i>=k && i<l){
      d[i]=data_bl[i]-data_bl[i-k];
      q[i]=q[i-1]+d[i];
      ss[i]=ss[i-1]+q[i]+M*d[i];
    }
    else if(i>=l && i<l+k){
      d[i]=data_bl[i]-data_bl[i-k]-data_bl[i-l];
      q[i]=q[i-1]+d[i];
      ss[i]=ss[i-1]+q[i]+M*d[i];
    }
    else if(i>=l+k){
      d[i]=data_bl[i]-data_bl[i-k]-data_bl[i-l]+data_bl[i-k-l];
      q[i]=q[i-1]+d[i];
      ss[i]=ss[i-1]+q[i]+M*d[i];
    }
    data_trapz[i] = ss[i]/M/(Double_t)k;
  }

  Double_t bl = 0.;
  for(UInt_t i=0;i<trapz_par.pre_trigger;i++){
    bl += data_trapz[i];
  }
  bl /= (Double_t)trapz_par.pre_trigger;
  for(UInt_t i=0;i<ltra;i++){
    data_trapz[i] -= bl;
  }

  free(d);
  free(q);
  free(ss);
}

#ifdef OPENFITWAVE
//
void WaveAnalysis::FitWave(Long64_t n)
{
  ProcessEntry(n);

  for(int i=0;i<ltra;i++){
    gr->SetPoint(i, (Double_t)i, (Double_t)data_bl[i]);
  }

  Double_t par_kb[2];
  TF1 *tf_bl = new TF1("tf_bl", "pol1", 0, trapz_par.pre_trigger);
  tf_bl->SetParameter(0, 0);
  tf_bl->SetParameter(1, -0.01);
  gr->Fit(tf_bl, "RQ0MC");
  tf_bl->GetParameters(&par_kb[0]);

  // std::cout << "bl b = " << par_kb[0] << std::endl;
  // std::cout << "bl k = " << par_kb[1] << std::endl;

  // std::cout << "trigger_num = " << trapz_result.trigger_num << std::endl;
  if(trapz_result.trigger_num != 1) return;

  int t_max = trapz_par.pre_trigger+6.*caen_rccr2_par.smooth_length+caen_rccr2_par.rise_length;
  // std::cout << "t_max = " << t_max << std::endl;
  // std::cout << "max = " << TMath::Max(data_bl[t_max], 10.) << std::endl;

  TF1 *tf_wave = new TF1("tf_wave", Fun1, 0, ltra, 6);
  tf_wave->SetParameter(0, par_kb[0]);
  tf_wave->SetParameter(1, par_kb[1]);
  // tf_wave->FixParameter(0, 0);
  // tf_wave->FixParameter(1, 0);
  tf_wave->SetParameter(2, TMath::Max(data_bl[(int)(t_max)], 10.));
  tf_wave->SetParameter(3, trapz_par.pre_trigger);
  tf_wave->SetParLimits(3, 0, ltra);
  tf_wave->SetParameter(4, FITTAUP);
  tf_wave->SetParameter(5, FITTAUR);
  tf_wave->SetParLimits(5, 2., 10.*FITTAUR);

#ifdef DEBUGDRAWOPTION
  TCanvas *cav2 = new TCanvas("cav2", "", 0, 0, 480, 360);
  cav2->cd();
  gr->Draw();
  gr->Fit("tf_wave", "R");
#else
  gr->Fit("tf_wave", "RQ0M");
#endif

  fit_result.energy[0] = tf_wave->GetParameter(2)*16.0;
  fit_result.t0[0] = tf_wave->GetParameter(3);
  fit_result.time_rise = tf_wave->GetParameter(5);
  fit_result.time_decay = tf_wave->GetParameter(4);
  fit_result.trigger_num = 1;

  for(int i=0;i<ltra;i++){
    data_fit[i] = tf_wave->Eval((Double_t)i);
  }
}
#endif

#ifdef DEBUGDRAWOPTION
//
void WaveAnalysis::DrawEntry(Long64_t n)
{
  GetWave(n);
  RCCR2(n);
  Trapezoid(n);

  FitWave(n);

  TGraph *g1 = new TGraph(ltra);
  for(int i=0;i<ltra;i++){
    g1->SetPoint(i, (Double_t)i, (Double_t)data_bl[i]);
  }

  cav1->cd();
  g1->Draw();

  //
  TGraph *g2 = new TGraph(ltra);
  for(int i=0;i<ltra;i++){
    g2->SetPoint(i, (Double_t)i, (Double_t)data_rccr2[i]);
  }

  cav1->cd();
  g2->SetLineColor(2);
  g2->Draw("same");

  //
  TGraph *g3 = new TGraph(ltra);
  for(int i=0;i<ltra;i++){
    g3->SetPoint(i, (Double_t)i, (Double_t)data_trapz[i]);
  }

  cav1->cd();
  g3->SetLineColor(4);
  g3->Draw("same");

#ifdef GETDATA
  //rccr2
  std::ofstream file_out_rccr2;
  file_out_rccr2.open(TString::Format("../origin_data/wave_id%06d_rccr2.txt",(int)n).Data());
  for(int i=0;i<ltra;i++){
    file_out_rccr2 << i << "  " << (Double_t)data_rccr2[i] << std::endl;
  }
  file_out_rccr2.close();

  //trapz
  std::ofstream file_out_trapz;
  file_out_trapz.open(TString::Format("../origin_data/wave_id%06d_trapz.txt",(int)n).Data());
  for(int i=0;i<ltra;i++){
    file_out_trapz << i << "  " << (Double_t)data_trapz[i] << std::endl;
  }
  file_out_trapz.close();

  //fit
  std::ofstream file_out_fit;
  file_out_fit.open(TString::Format("../origin_data/wave_id%06d_fit.txt",(int)n).Data());
  for(int i=0;i<ltra;i++){
    file_out_fit << i << "  " << (Double_t)data_fit[i] << std::endl;
  }
  file_out_fit.close();
#endif
}
#endif

#ifdef DEBUGDRAWOPTION
//
void WaveAnalysis::DrawMultiRCCR2()
{
  TMultiGraph *mg = new TMultiGraph();
  TGraph *g[1000];
  for(Long64_t i=0;i<1000;i++){
    GetWave(i);
    RCCR2(i);
    g[i] = new TGraph(ltra);
    for(int j=0;j<ltra;j++){
      g[i]->SetPoint(j, (Double_t)j, (Double_t)data_rccr2[j]);
    }
    mg->Add(g[i]);
  }

  cav1->cd();
  mg->Draw("ap");
}
#endif

//
Double_t RCCR2XX(Double_t *v, UInt_t i, UInt_t window, UInt_t risetime)
{
  Double_t x = 0.;
  x = RCCR2YY(v, i, window) - RCCR2YY(v, i-risetime, window);

  return x;
}

//
Double_t RCCR2YY(Double_t *v, UInt_t i, UInt_t window)
{
  Double_t y = 0.;
  for(UInt_t j=window;j>0;j--){
    y += v[i-j];
  }
  y = y/(Double_t)window*2.;

  return y;
}

//
Double_t Fun1(Double_t *x, Double_t *par){
  Double_t fun;
  if(x[0]<=par[3]){
    fun = par[0] + par[1]*x[0];
  }else{
    fun = par[0] + par[1]*x[0] + par[2]*(TMath::Exp(-(x[0]-par[3])/par[4]) - TMath::Exp(-(x[0]-par[3])/par[5]));
  }

  return fun;
}