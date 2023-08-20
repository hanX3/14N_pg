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

  const PrimaryGeneratorAction *generatorAction = static_cast<const PrimaryGeneratorAction*>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String particleName;
  G4double particleEnergy;

  const G4ParticleDefinition *particle = generatorAction->GetParticleGun()->GetParticleDefinition();
  particleName = particle->GetParticleName();

  const G4ParticleGun *particleGun = generatorAction->GetParticleGun();
  particleEnergy = particleGun->GetParticleEnergy();
  particleEnergy /= keV;

  // G4cout << "particleName " << particleName << G4endl;
  // G4cout << "particleEnergy " << particleEnergy << G4endl;

  //
  G4long beamOnNum = run->GetNumberOfEventToBeProcessed();
  G4cout << "beamOnNum " << beamOnNum << G4endl;

  //  creat RootIO file
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  // rootIO->OpenEnergyFile(beamOnNum);
  rootIO->OpenEnergyFile(particleName, particleEnergy, beamOnNum);

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
