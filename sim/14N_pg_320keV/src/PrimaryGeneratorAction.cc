#include "PrimaryGeneratorAction.hh"
#include "Constants.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomDirection.hh"
#include "G4IonTable.hh"
#include "G4Geantino.hh"
#include "G4DynamicParticle.hh"

#include "Randomize.hh"
#include "TMatrixD.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
{
  G4int nofParticles = 1;
  fParticleGun  = new G4ParticleGun(nofParticles);

  G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("proton");
  fParticleGun->SetParticleDefinition(particleDefinition);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //test
  /*
  G4ParticleDefinition *test1 = G4IonTable::GetIonTable()->GetIon(6, 12);
  G4cout << "???  12C mass  " << test1->GetPDGMass() << G4endl; 
  G4ParticleDefinition *test2 = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  G4cout << "???  gamma mass  " << test2->GetPDGMass() << G4endl; 
  G4ParticleDefinition *test3 = G4IonTable::GetIonTable()->GetIon(7, 13);
  G4cout << "???  13N mass  " << test3->GetPDGMass() << G4endl; 

  G4ParticleDefinition *test4 = G4ParticleTable::GetParticleTable()->FindParticle("proton");
  G4DynamicParticle *test_dy1 = new G4DynamicParticle(test4, G4ThreeVector(0.,0.,1.), 290.*keV);
  G4cout << "???  test_dy1 momx  " << test_dy1->Get4Momentum().px() << G4endl;
  G4cout << "???  test_dy1 momy  " << test_dy1->Get4Momentum().py() << G4endl;
  G4cout << "???  test_dy1 momz  " << test_dy1->Get4Momentum().pz() << G4endl;
  G4cout << "???  test_dy1 e     " << test_dy1->Get4Momentum().e() << G4endl;
  G4DynamicParticle *test_dy2 = new G4DynamicParticle(test1, G4ThreeVector(0.,0.,0.), 0.*keV);
  G4cout << "???  test_dy2 momx  " << test_dy2->Get4Momentum().px() << G4endl;
  G4cout << "???  test_dy2 momy  " << test_dy2->Get4Momentum().py() << G4endl;
  G4cout << "???  test_dy2 momz  " << test_dy2->Get4Momentum().pz() << G4endl;
  G4cout << "???  test_dy2 e     " << test_dy2->Get4Momentum().e() << G4endl;
  G4cout << "???  barn     " << barn << G4endl;
  */

  //set position

  G4double aa[4][4] = {{std::cos(-BeamAngle/180.*CLHEP::pi),0.,std::sin(-BeamAngle/180.*CLHEP::pi),0.}, {0.,1.,0.,0.}, {-std::sin(-BeamAngle/180.*CLHEP::pi),0.,std::cos(-BeamAngle/180.*CLHEP::pi),0.}, {0.,0.,0.,1.}};
  G4double bb[4][4] = {{1.,0.,0.,2.*BeamTubeLength*std::sin(BeamAngle/180.*CLHEP::pi)}, {0.,1.,0.,0.}, {0.,0.,1.,-2.*BeamTubeLength*std::cos(BeamAngle/180.*CLHEP::pi)}, {0.,0.,0.,1.}};

  TMatrixD mat1(4, 4);
  TMatrixD mat2(4, 4);
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      mat1[i][j] = aa[i][j];
      mat2[i][j] = bb[i][j];
    }
  }
  TMatrixD mat3(4, 4);
  mat3.Mult(mat2,mat1);
  /*
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      G4cout << mat3[i][j] << G4endl;
    }
  }
  */

  G4double r0 = BeamSize*G4UniformRand();
  G4double theta = (2.*CLHEP::pi)*G4UniformRand();
  G4double x0 = r0*std::sin(theta);
  G4double y0 = r0*std::cos(theta);
  G4double z0 = 0.;

  TMatrixD posOri(4, 1);
  posOri[0][0] = x0;
  posOri[1][0] = y0;
  posOri[2][0] = z0;
  posOri[3][0] = 1.;

  TMatrixD posReal(4, 1);
  posReal.Mult(mat3, posOri);
  /*
  for(int i=0;i<4;i++){
    G4cout << posReal[i][0] << G4endl;
  }
  */

  fParticleGun->SetParticlePosition(G4ThreeVector(posReal[0][0], posReal[1][0], posReal[2][0]));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-std::sin(BeamAngle/180.*CLHEP::pi),0,std::cos(BeamAngle/180.*CLHEP::pi)));
  //set energy
  fParticleGun->SetParticleEnergy(ParticleEnergy);

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
