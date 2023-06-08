#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "RootIO.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ActionInitialization::ActionInitialization(G4int thesaveFlag)
: G4VUserActionInitialization(),
  saveFlag(thesaveFlag)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ActionInitialization::BuildForMaster() const
{
  PrimaryGeneratorAction* priGen = new PrimaryGeneratorAction();
  RootIO* rootIO = new RootIO(saveFlag);

  SetUserAction(new RunAction(rootIO, priGen));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
  PrimaryGeneratorAction* priGen = new PrimaryGeneratorAction();
  RootIO* rootIO = new RootIO(saveFlag);
  DetectorConstruction *detconstruct = new DetectorConstruction();

  SetUserAction(priGen);
  SetUserAction(new RunAction(rootIO, priGen));
  SetUserAction(new EventAction(priGen, rootIO));
  //SetUserAction(new SteppingAction(detconstruct, rootIO));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
