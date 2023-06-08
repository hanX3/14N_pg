#include "N14pgO15CrossSection.hh"


N14pgO15CrossSection::N14pgO15CrossSection()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
N14pgO15CrossSection::~N14pgO15CrossSection()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double N14pgO15CrossSection::GetIsoCrossSection(const G4DynamicParticle *aPar, G4int Z, G4int A, const G4Isotope *, const G4Element *, const G4Material *)
{
  G4double crossSection = 0.;
  const G4int aParA = aPar->GetDefinition()->GetBaryonNumber();
  if(aParA==0);
  else if(aParA==1 && Z==7 && A==14){
    G4double eCM = GetEcmValue(aParA, A, aPar->GetKineticEnergy());
    // G4cout << eCM << G4endl; //MeV    
    G4double sfactor = 0.;
    if(eCM>=0.2 && eCM<=0.4){
      sfactor = 2286./(0.310727-0.375394*(1000.*eCM-259.027)+(1000.*eCM-259.027)*(1000.*eCM-259.027)); //unit keVb
    }
    else{
      sfactor = 0.;
    }
    // G4cout << "sfactor " << sfactor << G4endl;
    G4double eta = 0.1575*1.*7*sqrt((1.*14.)/(1.+14.)/eCM);
    crossSection = sfactor*exp(-2.*3.1415926*eta)/eCM/1000. * barn; // barn 1e-22
    crossSection *= 1e13;

    // G4cout << "crossSection " << crossSection << G4endl;
    // G4cout << "barn " << barn << G4endl;
    // G4cout << "m " << m << G4endl;

  }
  else{
    crossSection = 0.;
  }

  return crossSection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double N14pgO15CrossSection::GetEcmValue(G4double projectA, G4double targetA, G4double elab)
{
  return targetA/(projectA+targetA)*elab;
}
