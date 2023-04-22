#include "Constants.hh"

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "GeSD.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Torus.hh"
#include "G4Tubs.hh"
#include "G4CutTubs.hh"
#include "G4Hype.hh"
#include "G4Trd.hh"
#include "G4Orb.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SDManager.hh"
#include "G4UserLimits.hh"

// public methods
DetectorConstruction::DetectorConstruction()
: matAir(NULL),
  matVaccum(NULL),
  matCu(NULL),
  matAl(NULL),
  matC(NULL),
  matN(NULL),
  matGe(NULL),
  matTa(NULL),
  matTa2N3(NULL),
  matTiN(NULL),
  stepLimit(NULL)
{
  messenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetectorConstruction::~DetectorConstruction()
{
  delete stepLimit;
  delete messenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  DefineMaterials();

  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::DefineMaterials()
{
  G4double z, a;
  G4double density;
  G4int ncomponents, natoms;

  G4NistManager* nist = G4NistManager::Instance();
  matAir = nist->FindOrBuildMaterial("G4_AIR");
  matVaccum = nist->FindOrBuildMaterial("G4_Galactic");
  matCu = nist->FindOrBuildMaterial("G4_Cu");
  matAl = nist->FindOrBuildMaterial("G4_Al");
  matC = nist->FindOrBuildMaterial("G4_C");
  matN = nist->FindOrBuildMaterial("G4_N");
  matGe = nist->FindOrBuildMaterial("G4_Ge");
  matTa = nist->FindOrBuildMaterial("G4_Ta");

  G4Element *N  = new G4Element("Nitrogen", "N", z=7., a=14.01*g/mole);
  G4Element *Ti  = new G4Element("Titanium", "Ti", z=22., a=47.87*g/mole);
  G4Element *Ta  = new G4Element("TanTalum", "Ta", z=73., a=180.95*g/mole);

  matTa2N3 = new G4Material("Ta2N3", density=11.3*g/cm3, ncomponents=2);
  matTa2N3->AddElement(Ta, natoms=2);
  matTa2N3->AddElement(N, natoms=3);

  matTiN = new G4Material("TiN", density=5.43*g/cm3, ncomponents=2);
  matTiN->AddElement(Ti, natoms=1);
  matTiN->AddElement(N, natoms=1);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  G4cout << "Define Materials sucefully" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* DetectorConstruction::GetGeLog(G4String geName)
{
  G4cout<<" --->: GetGe, begin" << G4endl;

  G4LogicalVolume* fGeLog = NULL;
  G4Tubs *solidGe = new G4Tubs("GeTubs", 0, GeR, GeHeight, 0, CLHEP::twopi);
  G4Tubs *solidLN2Hole = new G4Tubs("LN2HoleTubs", 0, LN2HoleR, LN2HoleDeep, 0, CLHEP::twopi);
  G4SubtractionSolid *subGe = new G4SubtractionSolid("GeTubs-LN2HoleTubs", solidGe, solidLN2Hole, G4Transform3D(G4RotationMatrix(), G4ThreeVector(0,0,GeHeight-LN2HoleDeep)));
  fGeLog = new G4LogicalVolume(subGe, matGe, geName);

  //  color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.3));
  pVisAtt->SetForceSolid(true);
  fGeLog->SetVisAttributes(pVisAtt);

  return fGeLog;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* DetectorConstruction::GetFace1Log(G4String face1Name)
{
  G4cout<<" --->: GetFace1, begin" << G4endl;

  G4LogicalVolume* fFace1Log = NULL;
  G4Tubs *solidFace1 = new G4Tubs("Face1Tubs", 0, Face1R, Face1Thickness, 0, CLHEP::twopi);
  fFace1Log = new G4LogicalVolume(solidFace1, matAl, face1Name);

  //  color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.3));
  pVisAtt->SetForceSolid(true);
  fFace1Log->SetVisAttributes(pVisAtt);

  return fFace1Log;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* DetectorConstruction::GetFace2Log(G4String face2Name)
{
  G4cout<<" --->: GetFace2, begin" << G4endl;

  G4LogicalVolume* fFace2Log = NULL;
  G4Tubs *solidFace2 = new G4Tubs("Face2Tubs", 0, Face2R, Face2Thickness, 0, CLHEP::twopi);
  fFace2Log = new G4LogicalVolume(solidFace2, matC, face2Name);

  //  color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 0.3, 0.0, 0.3));
  pVisAtt->SetForceSolid(true);
  fFace2Log->SetVisAttributes(pVisAtt);

  return fFace2Log;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* DetectorConstruction::GetSurround1Log(G4String surround1Name)
{
  G4cout<<" --->: GetSurround1, begin" << G4endl;

  G4LogicalVolume* fSurround1Log = NULL;
  G4Tubs *solidSurround1 = new G4Tubs("Surround1Tubs", Surround1R1, Surround1R2, Surround1Length, 0, CLHEP::twopi);
  fSurround1Log = new G4LogicalVolume(solidSurround1, matCu, surround1Name);

  //  color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 0.3, 0.0, 0.3));
  pVisAtt->SetForceSolid(true);
  fSurround1Log->SetVisAttributes(pVisAtt);

  return fSurround1Log;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* DetectorConstruction::GetSurround2Log(G4String surround2Name)
{
  G4cout<<" --->: GetSurround2, begin" << G4endl;

  G4LogicalVolume* fSurround2Log = NULL;
  G4Tubs *solidSurround2 = new G4Tubs("Surround2Tubs", Surround2R1, Surround2R2, Surround2Length, 0, CLHEP::twopi);
  fSurround2Log = new G4LogicalVolume(solidSurround2, matAl, surround2Name);

  //  color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.3));
  pVisAtt->SetForceSolid(true);
  fSurround2Log->SetVisAttributes(pVisAtt);

  return fSurround2Log;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* DetectorConstruction::GetTargetLog(G4String targetName)
{
  G4cout<<" --->: GetTarget, begin" << G4endl;

  G4LogicalVolume *fTargetLog = NULL;
  G4Tubs *solidTarget = new G4Tubs("TargetTubs", 0, TargetR, TargetThickness, 0, CLHEP::twopi);
  fTargetLog = new G4LogicalVolume(solidTarget, matTa2N3, targetName);

  //  color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.3));
  pVisAtt->SetForceSolid(true);
  fTargetLog->SetVisAttributes(pVisAtt);

  return fTargetLog;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* DetectorConstruction::GetTargetBackLog(G4String targetBackName)
{
  G4cout<<" --->: GetTargetBack, begin" << G4endl;

  G4LogicalVolume *fTargetBackLog = NULL;
  G4Tubs *solidTargetBack = new G4Tubs("TargetBackTubs", 0, TargetBackR, TargetBackThickness, 0, CLHEP::twopi);
  fTargetBackLog = new G4LogicalVolume(solidTargetBack, matTa, targetBackName);

  //  color
  G4VisAttributes *pVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.3));
  pVisAtt->SetForceSolid(true);
  fTargetBackLog->SetVisAttributes(pVisAtt);

  return fTargetBackLog;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* DetectorConstruction::GetBeamTubeLog(G4String beamTubeName)
{
  G4cout<<" --->: Get Beam Tube, begin" << G4endl;

  G4LogicalVolume* fBeamTubeLog = NULL;
  G4CutTubs *solidBeamTube = new G4CutTubs("BeamTube", 0., BeamTubeR, BeamTubeLength, 0, CLHEP::twopi, G4ThreeVector(0,0,0), G4ThreeVector(std::cos((90.-BeamAngle)/180.*CLHEP::pi),0,std::sin((90.-BeamAngle)/180.*CLHEP::pi)));
  fBeamTubeLog = new G4LogicalVolume(solidBeamTube, matVaccum, beamTubeName);

  //  color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(0., 0., 1.0, 0.3));
  pVisAtt->SetForceSolid(true);
  fBeamTubeLog->SetVisAttributes(pVisAtt);

  return fBeamTubeLog;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* DetectorConstruction::GetFlangeLog(G4String flangeName)
{
  G4cout<<" --->: GetFlange, begin" << G4endl;

  G4LogicalVolume* fFlangeLog = NULL;
  G4Tubs *solidTubs1 = new G4Tubs("Tubs1", 0, FlangeR, FlangeThickness, 0, CLHEP::twopi);
  G4Tubs *solidTubs2 = new G4Tubs("Tubs2", 0, FlangeRCut, FlangeThicknessCut, 0, CLHEP::twopi);
  G4SubtractionSolid *subFlange = new G4SubtractionSolid("Tubs1-Tubs2", solidTubs1, solidTubs2, G4Transform3D(G4RotationMatrix(), G4ThreeVector(0,0,FlangeThickness-FlangeThicknessCut)));
  fFlangeLog = new G4LogicalVolume(subFlange, matCu, flangeName);

  //  color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.6));
  pVisAtt->SetForceSolid(true);
  fFlangeLog->SetVisAttributes(pVisAtt);

  return fFlangeLog;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* DetectorConstruction::GetCoolingSupportLog(G4String coolingSupportName)
{
  G4cout<<" --->: Get Cooling Support, begin" << G4endl;

  G4LogicalVolume* fCoolingSupportLog = NULL;
  G4Tubs *solidTubs1 = new G4Tubs("Tubs1", 0, CoolingSupportR, CoolingSupportThickness, 0, CLHEP::twopi);
  G4Tubs *solidTubs2 = new G4Tubs("Tubs2", 0, CoolingSupportRCut, CoolingSupportThicknessCut, 0, CLHEP::twopi);
  G4SubtractionSolid *subCoolingSupport = new G4SubtractionSolid("Tubs1-Tubs2", solidTubs1, solidTubs2, G4Transform3D(G4RotationMatrix(), G4ThreeVector(0,0,CoolingSupportThickness-CoolingSupportThicknessCut)));
  fCoolingSupportLog = new G4LogicalVolume(subCoolingSupport, matAl, coolingSupportName);

  //  color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.6));
  pVisAtt->SetForceSolid(true);
  fCoolingSupportLog->SetVisAttributes(pVisAtt);

  return fCoolingSupportLog;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* DetectorConstruction::GetTestLog(G4String testName)
{
  G4cout<<" --->: Get Test, begin" << G4endl;

  G4LogicalVolume* fTestLog = NULL;
  G4CutTubs *solidTest = new G4CutTubs("test", 12.0*mm, 20.0*mm, 50.0*mm, 0, CLHEP::twopi, G4ThreeVector(0,0,0), G4ThreeVector(std::cos((90.-BeamAngle)/180.*CLHEP::pi),0,std::sin((90.-BeamAngle)/180.*CLHEP::pi)));
  fTestLog = new G4LogicalVolume(solidTest, matVaccum, testName);

  //color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 0.5, 0.0, 0.3));
  pVisAtt->SetForceSolid(true);
  fTestLog->SetVisAttributes(pVisAtt);

  return fTestLog;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  G4cout<<" --->: Construct, begin" << G4endl;

  G4bool checkOverlaps = true;

  //define world
  G4Box* solidWorld = new G4Box("World", 0.5 * worldSizeX, 0.5 * worldSizeY, 0.5 * worldSizeZ);
  // G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, matVaccum, "World");
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, matAir, "World");
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);

  // //target
  // G4LogicalVolume* fTargetLog = GetTargetLog("Target");
  // G4ThreeVector positionTarget = G4ThreeVector(0, 0, 0);
  // new G4PVPlacement(0, positionTarget, fTargetLog, "Target", logicWorld, false, 0, checkOverlaps);

  // //targetBack
  // G4LogicalVolume* fTargetBackLog = GetTargetBackLog("TargetBack");
  // G4ThreeVector positionTargetBack = G4ThreeVector(0, 0, TargetBackPosDis);
  // new G4PVPlacement(0, positionTargetBack, fTargetBackLog, "TargetBack", logicWorld, false, 0, checkOverlaps);

  // //beam tube
  // G4LogicalVolume* fBeamTubeLog = GetBeamTubeLog("BeamTube");
  // G4ThreeVector positionBeamTube = G4ThreeVector(BeamTubeLength*std::sin(BeamAngle/180.*CLHEP::pi), 0, -BeamTubeLength*std::cos(BeamAngle/180.*CLHEP::pi)-TargetThickness);
  // G4RotationMatrix *rotBeamTube = new G4RotationMatrix();
  // rotBeamTube->rotateY(BeamAngle*deg);
  // G4RotationMatrix invrotBeamTube = rotBeamTube->invert();
  // G4Transform3D transformBeamTube = G4Transform3D(invrotBeamTube, positionBeamTube);
  // new G4PVPlacement(transformBeamTube, fBeamTubeLog, "BeamTube", logicWorld, false, 0, checkOverlaps);

  // //flange
  // G4LogicalVolume* fFlangeLog = GetFlangeLog("Flange");
  // G4ThreeVector positionFlange = G4ThreeVector(0, 0, FlangePosDis);
  // new G4PVPlacement(0, positionFlange, fFlangeLog, "Flange", logicWorld, false, 0, checkOverlaps);

  // //cooling support
  // G4LogicalVolume* fCoolingSupportLog = GetCoolingSupportLog("CoolingSupport");
  // G4ThreeVector positionCoolingSupport = G4ThreeVector(0, 0, CoolingSupportPosDis);
  // new G4PVPlacement(0, positionCoolingSupport, fCoolingSupportLog, "CoolingSupport", logicWorld, false, 0, checkOverlaps);

  //Ge
  G4LogicalVolume* fGeLog = GetGeLog("Ge");
  for(int i=0;i<NofGe;i++){
    G4ThreeVector positionGe = G4ThreeVector(GePosDis*std::sin(GeThetaAngle[i]/180.*CLHEP::pi), 0, GePosDis*std::cos(GeThetaAngle[i]/180.*CLHEP::pi));
    G4RotationMatrix *rot = new G4RotationMatrix();
    rot->rotateY(-GeThetaAngle[i]*deg);
    G4RotationMatrix invrot = rot->invert();
    G4Transform3D transform = G4Transform3D(invrot, positionGe);
    new G4PVPlacement(transform, fGeLog, "Ge", logicWorld, false, i, checkOverlaps);

    delete rot;
  }

  //face1
  G4LogicalVolume* fFace1Log = GetFace1Log("Face1");
  for(int i=0;i<NofGe;i++){
    G4ThreeVector positionFace1 = G4ThreeVector(Face1Dis*std::sin(GeThetaAngle[i]/180.*CLHEP::pi), 0, Face1Dis*std::cos(GeThetaAngle[i]/180.*CLHEP::pi));
    G4RotationMatrix *rot = new G4RotationMatrix();
    rot->rotateY(-GeThetaAngle[i]*deg);
    G4RotationMatrix invrot = rot->invert();
    G4Transform3D transform = G4Transform3D(invrot, positionFace1);
    new G4PVPlacement(transform, fFace1Log, "face1", logicWorld, false, i, checkOverlaps);

    delete rot;
  }

  //face2
  G4LogicalVolume* fFace2Log = GetFace2Log("Face2");
  for(int i=0;i<NofGe;i++){
    G4ThreeVector positionFace2 = G4ThreeVector(Face2Dis*std::sin(GeThetaAngle[i]/180.*CLHEP::pi), 0, Face2Dis*std::cos(GeThetaAngle[i]/180.*CLHEP::pi));
    G4RotationMatrix *rot = new G4RotationMatrix();
    rot->rotateY(-GeThetaAngle[i]*deg);
    G4RotationMatrix invrot = rot->invert();
    G4Transform3D transform = G4Transform3D(invrot, positionFace2);
    new G4PVPlacement(transform, fFace2Log, "face2", logicWorld, false, i, checkOverlaps);

    delete rot;
  }

  //surround1
  G4LogicalVolume* fSurround1Log = GetSurround1Log("Surround1");
  for(int i=0;i<NofGe;i++){
    G4ThreeVector positionSurround1 = G4ThreeVector(Surround1Dis*std::sin(GeThetaAngle[i]/180.*CLHEP::pi), 0, Surround1Dis*std::cos(GeThetaAngle[i]/180.*CLHEP::pi));
    G4RotationMatrix *rot = new G4RotationMatrix();
    rot->rotateY(-GeThetaAngle[i]*deg);
    G4RotationMatrix invrot = rot->invert();
    G4Transform3D transform = G4Transform3D(invrot, positionSurround1);
    new G4PVPlacement(transform, fSurround1Log, "surround1", logicWorld, false, i, checkOverlaps);

    delete rot;
  }

  //surround2
  G4LogicalVolume* fSurround2Log = GetSurround2Log("Surround2");
  for(int i=0;i<NofGe;i++){
    G4ThreeVector positionSurround2 = G4ThreeVector(Surround2Dis*std::sin(GeThetaAngle[i]/180.*CLHEP::pi), 0, Surround2Dis*std::cos(GeThetaAngle[i]/180.*CLHEP::pi));
    G4RotationMatrix *rot = new G4RotationMatrix();
    rot->rotateY(-GeThetaAngle[i]*deg);
    G4RotationMatrix invrot = rot->invert();
    G4Transform3D transform = G4Transform3D(invrot, positionSurround2);
    new G4PVPlacement(transform, fSurround2Log, "surround2", logicWorld, false, i, checkOverlaps);

    delete rot;
  }

  //step limit
  stepLimit = new G4UserLimits(MaxStepLimit);
  // fTargetLog->SetUserLimits(stepLimit);

  //Sensitive detectors
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4String SDname;

  GeSD *ge = new GeSD("geSD", "geHitCollection");
  SDman->AddNewDetector(ge);
  fGeLog->SetSensitiveDetector(ge);

  return physWorld;
}
