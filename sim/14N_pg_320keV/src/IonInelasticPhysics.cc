#include "IonInelasticPhysics.hh"
#include "G4ProtonInelasticProcess.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

#include "N14pgO15.hh"
#include "N14pgO15CrossSection.hh"


IonInelasticPhysics::IonInelasticPhysics(const G4String &name):
  G4VPhysicsConstructor(name)
{
  G4cout << G4endl << "A local inelastic model is activated for all ions" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
IonInelasticPhysics::~IonInelasticPhysics()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IonInelasticPhysics::ConstructProcess()
{
  N14pgO15 *N14pgO15Model = new N14pgO15();
  N14pgO15CrossSection *N14pgO15CrossSecrion = new N14pgO15CrossSection();

  auto particleIterator = GetParticleIterator();
  particleIterator->reset();

  while((*particleIterator)()){
    G4ParticleDefinition *particle = particleIterator->value();
    G4ProcessManager *manager = particle->GetProcessManager();

    G4String particleName = particle->GetParticleName();
    if(particleName == "proton"){
      G4ProtonInelasticProcess *protonInelasticProcess = new G4ProtonInelasticProcess("inelastic");
      protonInelasticProcess->AddDataSet(N14pgO15CrossSecrion);
      protonInelasticProcess->RegisterMe(N14pgO15Model);
      manager->AddDiscreteProcess(protonInelasticProcess);
    }
  }
}
