#include "RootIO.hh"

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RootIO::RootIO(G4int saveFlag)
: save(saveFlag),
  energyFile(NULL),
  energyTree(NULL),
  hitFile(NULL),
  hitTree(NULL)
{
  energy0 = 0.;
  energy1 = 0.;
  energy2 = 0.;
  theta = 0.;

  edepInHit = 0.;
  trackIDInHit = 0;
  memset(particleNameInHit, 0, 128);
  prexInHit = 0.;
  preyInHit = 0.;
  prezInHit = 0.;
  postxInHit = 0.;
  postyInHit = 0.;
  postzInHit = 0.;
  stepLengthInHit = 0.;

  eventIDInStep = 0;
  edepInStep = 0.;
  trackIDInStep = 0;
  memset(particleNameInStep, 0, 128);
  memset(detectorNameInStep, 0, 128);
  prexInStep = 0.;
  preyInStep = 0.;
  prezInStep = 0.;
  postxInStep = 0.;
  postyInStep = 0.;
  postzInStep = 0.;
  stepLengthInStep = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RootIO::~RootIO()
{
  if(energyFile){
    delete energyFile;
    energyFile = NULL;
  }

  if(hitFile){
    delete hitFile;
    hitFile = NULL;
  }

  if(stepFile){
    delete stepFile;
    stepFile = NULL;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RootIO::OpenEnergyFile(G4long n)
{
  if(save){
    time_t t;
    struct tm* tt;
    t = time(0);
    tt = localtime(&t);
    char nfdate[1024];
    sprintf(nfdate, "%d%02d%02d_%02dh%02dm%02ds", tt->tm_year+1900, tt->tm_mon+1, tt->tm_mday, tt->tm_hour, tt->tm_min, tt->tm_sec);
    std::stringstream ss;
    ss.str("");

    //energy file
    if(n<1000) ss << "../data/" << nfdate << "_" << n << ".root";
    else ss << "../data/" << nfdate << "_" << n/1000 << "k.root";
    
    G4cout << "energy file " << ss.str() << G4endl;
    energyFile = new TFile(ss.str().c_str(), "RECREATE");
    if(!energyFile){
      G4cout << " RootIO::book :" << " problem creating the ROOT TFile!!!" << G4endl;
      return ;
    }
    energyTree = new TTree("tree", "energy simulation data");
    energyTree->Branch("energy0", &energy0, "energy0/D");
    energyTree->Branch("energy1", &energy1, "energy1/D");
    energyTree->Branch("energy2", &energy2, "energy2/D");
    energyTree->Branch("theta", &theta, "theta/D");
    if(!energyTree){
      G4cout << "\n can't create tree" << G4endl;
    }
    G4cout << "\n----> Tree file is opened in " << ss.str() << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RootIO::OpenEnergyFile(G4String pn, G4double e, G4long n)
{
  if(save){
    time_t t;
    struct tm* tt;
    t = time(0);
    tt = localtime(&t);
    char nfdate[1024];
    sprintf(nfdate, "%d%02d%02d_%02dh%02dm%02ds", tt->tm_year+1900, tt->tm_mon+1, tt->tm_mday, tt->tm_hour, tt->tm_min, tt->tm_sec);
    std::stringstream ss;
    ss.str("");

    //energy file
    if(n<1000) ss << "../data/" << nfdate << "_" << pn << "_" << e << "keV_" << n << ".root";
    else ss << "../data/" << nfdate << "_" << pn << "_" << e << "keV_" << n/1000 << "k.root";
    
    G4cout << "energy file " << ss.str() << G4endl;
    energyFile = new TFile(ss.str().c_str(), "RECREATE");
    if(!energyFile){
      G4cout << " RootIO::book :" << " problem creating the ROOT TFile!!!" << G4endl;
      return ;
    }
    energyTree = new TTree("tree", "energy simulation data");
    energyTree->Branch("energy0", &energy0, "energy0/D");
    energyTree->Branch("energy1", &energy1, "energy1/D");
    energyTree->Branch("energy2", &energy2, "energy2/D");
    energyTree->Branch("theta", &theta, "theta/D");
    if(!energyTree){
      G4cout << "\n can't create tree" << G4endl;
    }
    G4cout << "\n----> Tree file is opened in " << ss.str() << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RootIO::OpenHitFile()
{
  if(save){
    time_t t;
    struct tm* tt;
    t=time(0);
    tt=localtime(&t);
    char nfdate[1024];
    sprintf(nfdate, "%d%02d%02d_%02dh%02dm%02ds", tt->tm_year+1900, tt->tm_mon, tt->tm_mday, tt->tm_hour, tt->tm_min, tt->tm_sec);
    std::stringstream ss;
    ss.str("");
    //hit file
    ss.str("");
    ss << "../data/hit_" << nfdate << ".root";
    G4cout << "hit file " << ss.str() << G4endl;
    hitFile = new TFile(ss.str().c_str(), "RECREATE");
    if(!hitFile){
      G4cout << " RootIO::book :" << " problem creating the ROOT TFile!!!" << G4endl;
      return ;
    }
    hitTree = new TTree("tree", "hit simulation data");
    hitTree->Branch("eventID", &eventIDInHit, "eventID/I");
    hitTree->Branch("edep", &edepInHit, "edep/D");
    hitTree->Branch("trackID", &trackIDInHit, "trackID/I");
    hitTree->Branch("particleName", particleNameInHit, "particleName/C");
    hitTree->Branch("prex", &prexInHit, "prex/D");
    hitTree->Branch("prey", &preyInHit, "prey/D");
    hitTree->Branch("prez", &prezInHit, "prez/D");
    hitTree->Branch("postx", &postxInHit, "postx/D");
    hitTree->Branch("posty", &postyInHit, "posty/D");
    hitTree->Branch("postz", &postzInHit, "postz/D");
    hitTree->Branch("stepLength", &stepLengthInHit, "stepLength/D");
    if(!hitTree){
      G4cout << "\n can't create tree" << G4endl;
    }
    G4cout << "\n----> Tree file is opened in " << ss.str() << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RootIO::OpenStepFile()
{
  if(save){
    time_t t;
    struct tm* tt;
    t=time(0);
    tt=localtime(&t);
    char nfdate[1024];
    sprintf(nfdate, "%d%02d%02d_%02dh%02dm%02ds", tt->tm_year+1900, tt->tm_mon, tt->tm_mday, tt->tm_hour, tt->tm_min, tt->tm_sec);
    std::stringstream ss;
    ss.str("");
    //step file
    ss.str("");
    ss << "../data/step_" << nfdate << ".root";
    G4cout << "step file " << ss.str() << G4endl;
    stepFile = new TFile(ss.str().c_str(), "RECREATE");
    if(!stepFile){
      G4cout << " RootIO::book :" << " problem creating the ROOT TFile!!!" << G4endl;
      return ;
    }
    stepTree = new TTree("tree", "step simulation data");
    stepTree->Branch("eventID", &eventIDInStep, "eventID/I");
    stepTree->Branch("edep", &edepInStep, "edep/D");
    stepTree->Branch("trackID", &trackIDInStep, "trackID/I");
    stepTree->Branch("particleName", particleNameInStep, "particleName/C");
    stepTree->Branch("detectorName", detectorNameInStep, "detectorName/C");
    stepTree->Branch("prex", &prexInStep, "prex/D");
    stepTree->Branch("prey", &preyInStep, "prey/D");
    stepTree->Branch("prez", &prezInStep, "prez/D");
    stepTree->Branch("preTotalEnergy", &preTotalEnergyInStep, "preTotalEnergy/D");
    stepTree->Branch("preKineEnergy", &preKineEnergyInStep, "preKineEnergy/D");
    stepTree->Branch("postx", &postxInStep, "postx/D");
    stepTree->Branch("posty", &postyInStep, "posty/D");
    stepTree->Branch("postz", &postzInStep, "postz/D");
    stepTree->Branch("postTotalEnergy", &postTotalEnergyInStep, "postTotalEnergy/D");
    stepTree->Branch("postKineEnergy", &postKineEnergyInStep, "postKineEnergy/D");
    stepTree->Branch("stepLength", &stepLengthInStep, "stepLength/D");
    stepTree->Branch("processName", processNameInStep, "processName/C");
    if(!stepTree){
      G4cout << "\n can't create tree" << G4endl;
    }
    G4cout << "\n----> Tree file is opened in " << ss.str() << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RootIO::FillEnergyTree(G4double e0, G4double e1, G4double e2, G4double t)
{
  energy0 = e0;
  energy1 = e1;
  energy2 = e2;
  theta = t;

  if(energyTree){
    energyTree->Fill();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RootIO::FillHitTree(G4int id1, G4double e, G4int id2, G4String name, G4double ax, G4double ay, G4double az, G4double zx, G4double zy, G4double zz, G4double l)
{
  eventIDInHit = id1;
  edepInHit = e;
  trackIDInHit = id2;
  strcpy(particleNameInHit, name.c_str());
  prexInHit = ax;
  preyInHit = ay;
  prezInHit = az;
  postxInHit = zx;
  postyInHit = zy;
  postzInHit = zz;
  stepLengthInHit = l;

  if(hitTree){
    hitTree->Fill();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RootIO::FillStepTree(G4int id1, G4double e, G4int id2, G4String name1, G4String name2, G4double ax, G4double ay, G4double az, G4double te1, G4double ke1, G4double zx, G4double zy, G4double zz, G4double te2, G4double ke2, G4double l, G4String name3)
{
  eventIDInStep = id1;
  edepInStep = e;
  trackIDInStep = id2;
  strcpy(particleNameInStep, name1.c_str());
  strcpy(detectorNameInStep, name2.c_str());
  prexInStep = ax;
  preyInStep = ay;
  prezInStep = az;
  preTotalEnergyInStep = te1;
  preKineEnergyInStep = ke1;
  postxInStep = zx;
  postyInStep = zy;
  postzInStep = zz;
  postTotalEnergyInStep = te2;
  postKineEnergyInStep = ke2;
  stepLengthInStep = l;
  strcpy(processNameInStep, name3.c_str());

  if(stepTree){
    stepTree->Fill();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RootIO::CloseEnergyFile()
{
  if(!energyFile){
    return;
  }
  energyFile->cd();
  energyTree->Write();
  energyFile->Close();
  G4cout << "\n----> RootIO is saved. \n" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RootIO::CloseHitFile()
{
  if(!hitFile){
    return;
  }
  hitFile->cd();
  hitTree->Write();
  hitFile->Close();
  G4cout << "\n----> RootIO is saved. \n" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RootIO::CloseStepFile()
{
  if(!stepFile){
    return;
  }
  stepFile->cd();
  stepTree->Write();
  stepFile->Close();
  G4cout << "\n----> RootIO is saved. \n" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
