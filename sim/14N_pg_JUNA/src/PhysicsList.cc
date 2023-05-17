#include "PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

#include "G4HadronicProcess.hh"
#include "G4ProtonInelasticProcess.hh"

#include "G4StepLimiterPhysics.hh"

#include "IonInelasticPhysics.hh"

#include "G4ProcessManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PhysicsList::PhysicsList()
: G4VModularPhysicsList(),
  electro_magnetic(nullptr),
  decay(nullptr),
  radioactive_decay(nullptr),
  IonInelastic(nullptr)
{
  G4int verb = 0;
  SetVerboseLevel(verb);

  // EM physics
  electro_magnetic = new G4EmStandardPhysics(verb);
  RegisterPhysics(electro_magnetic);
  // Default
  decay = new G4DecayPhysics(verb);
  RegisterPhysics(decay);
  // Radioactive decay
  radioactive_decay = new G4RadioactiveDecayPhysics(verb);
  RegisterPhysics(radioactive_decay);

  // step limit
  stepLimit = new G4StepLimiterPhysics(verb);
  RegisterPhysics(stepLimit);

  // Ion inelastic
  IonInelastic = new IonInelasticPhysics(verb);
  RegisterPhysics(IonInelastic);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PhysicsList::~PhysicsList()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PhysicsList::ConstructProcess()
{
  AddTransportation();

  electro_magnetic->ConstructProcess();
  decay->ConstructProcess();
  radioactive_decay->ConstructProcess();
  stepLimit->ConstructProcess();
  
  IonInelastic->ConstructProcess();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}
