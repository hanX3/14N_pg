#include "RunAction.hh"
#include "RootIO.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"
#include "G4Timer.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "unistd.h"
#include <fstream>
#include <string>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RunAction::RunAction(RootIO *theRootIO, PrimaryGeneratorAction *thePriGen)
: G4UserRunAction(),
  rootIO(theRootIO),
  priGen(thePriGen)
{  
  // set printing event number per each 100000 events
  G4RunManager::GetRunManager()->SetPrintProgress(100000);

  timer = new G4Timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RunAction::~RunAction()
{
  delete timer;
  timer = NULL;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RunAction::BeginOfRunAction(const G4Run *run)
{
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  //
  G4ParticleDefinition *particle =  priGen->GetParticleGun()->GetParticleDefinition();
  G4String particleName = particle->GetParticleName();
  G4cout << "particleName " << particleName << G4endl;

  G4double energy = priGen->GetParticleGun()->GetParticleEnergy();
  energy /= keV;
  G4cout << "energy " << energy << G4endl;

  G4long beamOnNum = run->GetNumberOfEventToBeProcessed();
  G4cout << "beamOnNum " << beamOnNum << G4endl;

  //  creat RootIO file
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  rootIO->OpenEnergyFile(beamOnNum);

  int runID = run->GetRunID();
  timer->Start();
  G4cout << "======================   RunID = " << runID << "  ======================" << G4endl;

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

void RunAction::EndOfRunAction(const G4Run* run)
{
  rootIO->CloseEnergyFile();
  // rootIO->CloseHitFile();

  // Print results
  G4cout << "  The run was " << run->GetNumberOfEvent() << " events " << G4endl;

  timer->Stop();
  G4cout << " time:  " << *timer << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
