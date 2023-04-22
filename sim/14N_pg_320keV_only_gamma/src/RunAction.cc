#include "RunAction.hh"
#include "RootIO.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"
#include "G4Timer.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleGun.hh"
#include "unistd.h"
#include <fstream>
#include <string>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RunAction::RunAction(RootIO* therootIO, PrimaryGeneratorAction* thefPriGen)
: G4UserRunAction(),
  fRootIO(therootIO),
  fPriGen(thefPriGen)
{  
  // set printing event number per each 100000 events
  G4RunManager::GetRunManager()->SetPrintProgress(100000);

  fTimer = new G4Timer;
  G4cout << "kkkk" << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RunAction::~RunAction()
{
  delete fTimer;
  fTimer = NULL;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RunAction::BeginOfRunAction(const G4Run* frun)
{
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  //  creat RootIO file
  G4cout << "---" << G4endl;
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  fRootIO->OpenEnergyFile();
  // fRootIO->OpenHitFile();
  // fRootIO->OpenStepFile();

  int fRunID = frun->GetRunID();
  fTimer->Start();
  G4cout << "======================   RunID = " << fRunID << "  ======================" << G4endl;

  G4cout << "1 energy " << G4endl;
  G4cout << "2 track id " << G4endl;
  G4cout << "3 particle name " << G4endl;
  G4cout << "4 pre postion " << G4endl;
  G4cout << "5 post postion " << G4endl;
  G4cout << "6 detector name " << G4endl;
  G4cout << "7 step length " << G4endl;
  G4cout << "8 delat postion " << G4endl;
  G4cout << "9 delat time " << G4endl;
  G4cout << "10 delat energy " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* frun)
{
  fRootIO->CloseEnergyFile();
  //fRootIO->CloseHitFile();
  //fRootIO->CloseStepFile();

  // Print results
  G4cout << "  The run was " << frun->GetNumberOfEvent() << " events " << G4endl;

  fTimer->Stop();
  G4cout << " time:  " << *fTimer << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
