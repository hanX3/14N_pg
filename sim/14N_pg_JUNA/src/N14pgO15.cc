#include "N14pgO15.hh"

#include "G4DynamicParticle.hh"
#include "Randomize.hh"
#include "G4ParticleMomentum.hh"
#include "G4IonTable.hh"
#include "G4IonTable.hh"
#include "globals.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4Gamma.hh"
#include "G4Nucleus.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4NucleiProperties.hh"

#include "G4NuclearLevelData.hh"

#include "Constants.hh"


//
N14pgO15::N14pgO15()
{
  SetMinEnergy(0. *keV);
  SetMaxEnergy(100. *MeV);

  SetLevelsO15();
}

//
N14pgO15::~N14pgO15()
{

}

//
// theParticleChange is inherit from G4HadronicInteraction
G4HadFinalState *N14pgO15::ApplyYourself(const G4HadProjectile &projectile, G4Nucleus &targetNucleus)
{
  // for(int i=0;i<5;i++){
  //   G4cout << "levelsO15 " << levelsO15[i] << G4endl;
  //   G4cout << "levelsBranchRatioO15 " << levelsBranchRatioO15[i] << G4endl;
  //   G4cout << "levelsBranchRatioO15Add " << i << " " << levelsBranchRatioO15Add[i] << G4endl;
  // }

  theParticleChange.Clear();
  theParticleChange.SetStatusChange(stopAndKill);

  const G4int targetA = targetNucleus.GetA_asInt();
  const G4int targetZ = targetNucleus.GetZ_asInt();
  const G4int projectA = projectile.GetDefinition()->GetBaryonNumber();
  const G4int projectZ = projectile.GetDefinition()->GetAtomicNumber();
  // G4cout << "projectA " << projectA << G4endl;
  // G4cout << "projectZ " << projectZ << G4endl;
  // G4cout << "targetA " << targetA << G4endl;
  // G4cout << "targetZ " << targetZ << G4endl;


  if(projectA==0){}
  else if((projectA==1 && projectZ==1 && targetA==14 && targetZ==7)){
    
    G4ParticleDefinition *proParDef = G4IonTable::GetIonTable()->GetIon(projectZ, projectA, 0);
    G4ParticleDefinition *tarParDef = G4IonTable::GetIonTable()->GetIon(targetZ, targetA, 0);

    G4double proPDGMass = proParDef->GetPDGMass();
    G4double tarPDGMass = tarParDef->GetPDGMass();
    // G4cout << "pro mass " << proPDGMass << G4endl;
    // G4cout << "tar mass " << tarPDGMass << G4endl;

    G4LorentzVector proLonVector = projectile.Get4Momentum(); //unit MeV
    // G4cout << "proLonVector x " << proLonVector.x() << G4endl;
    // G4cout << "proLonVector y " << proLonVector.y() << G4endl;
    // G4cout << "proLonVector z " << proLonVector.z() << G4endl;
    // G4cout << "proLonVector t " << proLonVector.t() << G4endl;

    G4double proKLab = proLonVector.t()-proPDGMass;
    // G4cout << proKLab << G4endl; //MeV
    G4double proKCM = proKLab*tarPDGMass/(proPDGMass+tarPDGMass);
    // G4cout << proKCM << G4endl; //MeV

    G4ParticleDefinition *product0 = G4IonTable::GetIonTable()->GetIon(targetZ+1, targetA+1, 0.);
    G4double product0PDGMass = product0->GetPDGMass();

    G4double excEnergy = proPDGMass+tarPDGMass+proKCM-product0PDGMass;
    // G4cout << excEnergy << G4endl; //MeV

    G4LorentzVector product0LonVector = G4LorentzVector(0., 0., 0., product0PDGMass);
    G4DynamicParticle *product0Dynamic = new G4DynamicParticle(product0, product0LonVector);
    theParticleChange.AddSecondary(product0Dynamic);

    G4double ratio = G4UniformRand();
    if(ratio<levelsBranchRatioO15Add[0]){
      AddGammaRay(excEnergy);      
    }else{
      for(int i=1;i<NLEVELS;i++){
        if(ratio>=levelsBranchRatioO15Add[i-1] && ratio<levelsBranchRatioO15Add[i]){
           G4double energyGamma1 = excEnergy-levelsO15[i];
           G4double energyGamma2 = levelsO15[i];
           AddGammaRay(energyGamma1);
           AddGammaRay(energyGamma2);
           break;
        }else continue;
      }
    }
    
    // G4int nSec = theParticleChange.GetNumberOfSecondaries();
    // G4cout << "nSec " << nSec << G4endl;

    // G4double finalE = 0.;
    // for (G4int i = 0; i < nSec; i++) {
    //   G4DynamicParticle *pdyn=theParticleChange.GetSecondary(i)->GetParticle();
    //   finalE += pdyn->GetTotalEnergy();
    //   G4double mass_pdg=pdyn->GetDefinition()->GetPDGMass();
    //   G4double mass_dyn=pdyn->GetMass();
    //   G4cout << "mass_pdg " << mass_pdg << G4endl;
    //   G4cout << "mass_dyn " << mass_dyn << G4endl;
    //   G4cout << "finalE " << finalE << G4endl;
    // }

    // G4cout << "finalE " << finalE << G4endl;

    // G4cout << "projectile total energy " << projectile.GetTotalEnergy() << G4endl;
    // G4cout << "delta_E " << tarPDGMass+projectile.GetTotalEnergy()-finalE << G4endl;
    // G4cout << "delta_E " << tarPDGMass+proLonVector.t()-finalE << G4endl;
 
  }
  return &theParticleChange;
}

//
void N14pgO15::SetLevelsO15()
{
  for(int i=0;i<NLEVELS;i++){
    levelsO15[i] = LevelsO15[i];
    levelsBranchRatioO15[i] = LevelsBranchRatioO15[i];
  }

  for(int i=0;i<NLEVELS;i++){
    levelsBranchRatioO15Add[i] = 0;
    for(int j=0;j<i+1;j++) levelsBranchRatioO15Add[i] += levelsBranchRatioO15[j];
  }
}

//
void N14pgO15::AddGammaRay(G4double energy)
{
  G4ParticleDefinition *productGamma = G4Gamma::GammaDefinition();
  G4double rx = (2*G4UniformRand()-1);
  G4double ry = (2*G4UniformRand()-1);
  G4double rz = (2*G4UniformRand()-1);
  // G4cout << "rx " << rx << G4endl;
  // G4cout << "ry " << ry << G4endl;
  // G4cout << "rz " << rz << G4endl;
  G4double r = sqrt(rx*rx+ry*ry+rz*rz);
  G4LorentzVector productGammaLonVector = G4LorentzVector(energy*rx/r, energy*ry/r, energy*rz/r, energy); //MeV
  G4DynamicParticle *productGammaDynamic = new G4DynamicParticle(productGamma, productGammaLonVector);
  theParticleChange.AddSecondary(productGammaDynamic);
}
