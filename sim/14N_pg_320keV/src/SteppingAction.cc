#include "SteppingAction.hh"
#include "RootIO.hh"

#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
SteppingAction::SteppingAction(DetectorConstruction* detectorConstruction, RootIO *rootFile)
  :G4UserSteppingAction(),
   detConstruction(detectorConstruction),
   rootIO(rootFile)
{
  eventID = 0;
  edep = 0.;
  trackID = 0;
  prex = 0.;
  prey = 0.;
  prez = 0.;
  preTotalEnergy = 0.;
  preKineEnergy = 0.;
  postx = 0.;
  posty = 0.;
  postz = 0.;
  postTotalEnergy = 0.;
  postKineEnergy = 0.;
  stepLength = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void SteppingAction::UserSteppingAction(const G4Step* step)
{
  eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  edep = step->GetTotalEnergyDeposit();
  trackID = step->GetTrack()->GetTrackID();
  particleName = step->GetTrack()->GetDefinition()->GetParticleName();
  detectorName = step->GetTrack()->GetVolume()->GetName();
  prex = step->GetPreStepPoint()->GetPosition().x();
  prey = step->GetPreStepPoint()->GetPosition().y();
  prez = step->GetPreStepPoint()->GetPosition().z();
  preTotalEnergy = step->GetPreStepPoint()->GetTotalEnergy();
  preKineEnergy = step->GetPreStepPoint()->GetKineticEnergy();
  postx = step->GetPostStepPoint()->GetPosition().x();
  posty = step->GetPostStepPoint()->GetPosition().y();
  postz = step->GetPostStepPoint()->GetPosition().z();
  postTotalEnergy = step->GetPreStepPoint()->GetTotalEnergy();
  postKineEnergy = step->GetPreStepPoint()->GetKineticEnergy();
  stepLength = step->GetStepLength();
  processName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

  if(strcmp(particleName.c_str(), "gamma")==0 && step->GetTrack()->GetParentID()==1 && strcmp(detectorName, "Target")==0){
    rootIO->FillStepTree(eventID, edep, trackID, particleName, detectorName, prex, prey, prez, preTotalEnergy, preKineEnergy, postx, posty, postz, postTotalEnergy, postKineEnergy, stepLength, processName);
  }
}

