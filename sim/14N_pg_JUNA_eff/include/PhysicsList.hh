#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"

/// Modular physics list
///
/// It includes the folowing physics builders
/// - G4DecayPhysics
/// - G4RadioactiveDecayPhysics
/// - G4EmStandardPhysics

class PhysicsList: public G4VModularPhysicsList
{
public:
  PhysicsList();
  virtual ~PhysicsList();

public:
  virtual void ConstructProcess();
  virtual void SetCuts();

private:
  G4VPhysicsConstructor *electro_magnetic;
  G4VPhysicsConstructor *decay;
  G4VPhysicsConstructor *radioactive_decay;
  G4VPhysicsConstructor *stepLimit;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

