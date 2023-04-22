#ifndef RootIO_H
#define RootIO_H 1

#include <globals.hh>

#include <fstream>
#include <map>

class TFile;
class TH1D;
class TTree;

G4String GetFileName(G4int beamErg, const G4String &);

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RootIO
{
public:
  RootIO(G4int saveFlag);
  ~RootIO();

  void OpenEnergyFile();
  void CloseEnergyFile();
  void FillEnergyTree(G4double e0, G4double e1, G4double e2, G4double t);

  void OpenHitFile();
  void CloseHitFile();
  void FillHitTree(G4int id1, G4double e, G4int id2, G4String name, G4double ax, G4double ay, G4double az, G4double zx, G4double zy, G4double zz, G4double l);

  void OpenStepFile();
  void CloseStepFile();
  void FillStepTree(G4int id1, G4double e, G4int id2, G4String name1, G4String name2, G4double ax, G4double ay, G4double az, G4double te1, G4double ke1, G4double zx, G4double zy, G4double zz, G4double te2, G4double ke2, G4double l, G4String name3);

private:
  G4int save;

private:
  G4double energy0;
  G4double energy1;
  G4double energy2;
  G4double theta;

  TFile *energyFile;
  TTree *energyTree;

private:
  G4int eventIDInHit;
  G4double edepInHit;
  G4int trackIDInHit;
  char particleNameInHit[128];
  G4double prexInHit;
  G4double preyInHit;
  G4double prezInHit;
  G4double postxInHit;
  G4double postyInHit;
  G4double postzInHit;
  G4double stepLengthInHit;

  TFile *hitFile;
  TTree *hitTree;

private:
  G4int eventIDInStep;
  G4double edepInStep;
  G4int trackIDInStep;
  char particleNameInStep[128];
  char detectorNameInStep[128];
  G4double prexInStep;
  G4double preyInStep;
  G4double prezInStep;
  G4double preTotalEnergyInStep;
  G4double preKineEnergyInStep;
  G4double postxInStep;
  G4double postyInStep;
  G4double postzInStep;
  G4double postTotalEnergyInStep;
  G4double postKineEnergyInStep;
  G4double stepLengthInStep;
  char processNameInStep[128];

  TFile *stepFile;
  TTree *stepTree;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
