#include "PhysicsList.hh"

#include "G4UnitsTable.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

#include "G4HadronicProcess.hh"
#include "G4ProtonInelasticProcess.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4NuclideTable.hh"
#include "G4NuclearLevelData.hh"
#include "G4ProcessManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PhysicsList::PhysicsList()
: G4VModularPhysicsList(),
  electro_magnetic(nullptr),
  decay(nullptr),
  radioactive_decay(nullptr)
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

  //
  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1*CLHEP::picosecond);
  G4NuclideTable::GetInstance()->SetLevelTolerance(1.0*CLHEP::eV);
  //
  G4DeexPrecoParameters* deex = G4NuclearLevelData::GetInstance()->GetParameters();
  deex->SetCorrelatedGamma(false);
  deex->SetStoreAllLevels(true);
  deex->SetIsomerProduction(true);
  deex->SetMaxLifeTime(G4NuclideTable::GetInstance()->GetThresholdOfHalfLife()/std::log(2.));


  // step limit
  stepLimit = new G4StepLimiterPhysics(verb);
  // RegisterPhysics(stepLimit);
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
  // stepLimit->ConstructProcess();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}
