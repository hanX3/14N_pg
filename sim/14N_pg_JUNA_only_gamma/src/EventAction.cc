#include "EventAction.hh"
#include "GeHit.hh"
#include "RootIO.hh"
#include "PrimaryGeneratorAction.hh"
#include "Constants.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4DCofThisEvent.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include "TMath.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
EventAction::EventAction(PrimaryGeneratorAction *pri, RootIO *file)
: G4UserEventAction(),
  primary(pri),
  rootIO(file)
{}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::EndOfEventAction(const G4Event* event)
{
  auto sdManager = G4SDManager::GetSDMpointer();
  G4double idd = sdManager->GetCollectionID("geSD/geHitCollection");

  // Get hits collections
  auto hce = event->GetHCofThisEvent();
  auto hcge = static_cast<GeHitsCollection*>(hce->GetHC(idd));

  G4double erg[3] = {0., 0., 0.};

  for(int i=0;i<NofGe;i++){
    erg[i] = (*hcge)[i]->GetEdep();
    erg[i] /= keV;

    erg[i] = TMath::Abs(G4RandGauss::shoot(erg[i], (erg[i]-Energy2)*(Sigma1-Sigma2)/(Energy1-Energy2)+Sigma2));
  }

  if(erg[0]>0 || erg[1]>0 || erg[2]>0){
    rootIO->FillEnergyTree(erg[0], erg[1], erg[2], 0);
  }

  // periodic printing
  G4int eventID = event->GetEventID();
  if ( eventID < 10 || eventID % 100000 == 0) {
    G4cout << ">>> Event: " << eventID  << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
