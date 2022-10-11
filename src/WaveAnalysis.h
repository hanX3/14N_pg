#ifndef WAVEANALYSIS_H_
#define WAVEANALYSIS_H_

#include "set.h"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TF1.h"
#include "TGraph.h"
#include "TBenchmark.h"
#include "TMultiGraph.h"

#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

struct TRAPZ_PAR{
  Double_t decay_length;   // decay time of input trace (in points)
  UInt_t   rise_length;    // rise time of trapezoid (in points)
  UInt_t   falt_top;       // flat top of trapezoid (in points)
  UInt_t   pre_trigger;    // number of points used for baseline recovery
  UInt_t   peak_delay;     // peak delay after the trigger point
  UInt_t   peak_mean;      // peak mean for energy extraction
};

struct CAEN_RCCR2_PAR{
  UInt_t   pre_trigger;    // number of points used for baseline recovery
  
  UInt_t   smooth_length;  // smooth factor (in points)
  UInt_t   rise_length;    // rise time (in points)

  Int_t    threshold;      // threshold for hit finding
};

struct XIA_FAST_FILTER_PAR{
  UInt_t   pre_trigger;    // number of points used for baseline recovery
  
  UInt_t   fast_length;    // fast length (in points)
  UInt_t   fast_gap;       // fast gap (in points)
  UInt_t   delay_length;   // delay length (in points)
  Double_t scale_factor;   // scaling factor (option: 0.25, 0.125, 0.0625, 0.03125)

  Int_t    threshold;      // threshold for hit finding
};

struct TRAPZ_RESULT{
  Double_t energy[PILEUPMAX];    // mean value of trapezoidal flat-top points
  Double_t time_tag[PILEUPMAX];  // trigger time tag for each hit
  UShort_t trigger_num;         // number of triggers
};

#ifdef OPENFITWAVE
struct FIT_RESULT{
  Double_t energy[PILEUPMAX];
  Double_t t0[PILEUPMAX];
  Double_t time_rise;
  Double_t time_decay;
  UShort_t trigger_num;
};
#endif

//
Double_t RCCR2XX(Double_t *v, UInt_t i, UInt_t window, UInt_t risetime);
Double_t RCCR2YY(Double_t *v, UInt_t i, UInt_t window);
Double_t Fun1(Double_t *x, Double_t *par);

//
class WaveAnalysis
{
public:
  WaveAnalysis() = default;
  WaveAnalysis(const std::string &filename_in, const std::string &filename_out, int a, int b);
  ~WaveAnalysis();

public:
  void Process();
  bool ProcessEntry(Long64_t n);
#ifdef DEBUGDRAWOPTION
  void DrawEntry(Long64_t n);
  void DrawMultiRCCR2();
#endif

private:
  bool GetWave(Long64_t n);
  void CFD(Long64_t n);
  void RCCR2(Long64_t n);
  void Trapezoid(Long64_t n);

#ifdef OPENFITWAVE
  // Fit
  void FitWave(Long64_t n);
#endif

private:
  Int_t entry_start;
  Int_t entry_stop;

private:
  Double_t b_std_sqrt;
  
  TRAPZ_PAR trapz_par;
  CAEN_RCCR2_PAR caen_rccr2_par;
  XIA_FAST_FILTER_PAR xia_fast_filter_par;
  TRAPZ_RESULT trapz_result;

  UShort_t ltra;
  UShort_t data[MAXLENGTH];
  Double_t data_pol[MAXLENGTH];
  Double_t data_bl[MAXLENGTH];
  Double_t data_rccr2[MAXLENGTH];
  Double_t data_trapz[MAXLENGTH];
  Double_t baseline;

#ifdef OPENFITWAVE
  // Fit
  TGraph *gr;
  Double_t fit_par[6];
  FIT_RESULT fit_result;
  Double_t data_fit[MAXLENGTH];
#endif

private:
  TBenchmark *benchmark;

  TFile *file_in;
  TTree *tr_in;
  Long64_t total_entry;

  TFile *file_out;
  TTree *tr_out;

#ifdef DEBUGDRAWOPTION
  TCanvas *cav1;
#endif
};

#endif
