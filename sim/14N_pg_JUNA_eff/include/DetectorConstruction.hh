#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4FieldManager.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4TransportationManager.hh"
#include "G4PropagatorInField.hh"
#include "tls.hh"

// #include "Constants.hh"

class Constants;
class DetectorMessenger;
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;

class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  virtual ~DetectorConstruction();

  virtual G4VPhysicalVolume* Construct();

  G4LogicalVolume* GetFace1Log(G4String face1Name);
  G4LogicalVolume* GetFace2Log(G4String face2Name);
  G4LogicalVolume* GetSurround1Log(G4String surround1Name);
  G4LogicalVolume* GetSurround2Log(G4String surround2Name);
  G4LogicalVolume* GetGeLog(G4String geName);
  G4LogicalVolume* GetTargetLog(G4String targetName);
  G4LogicalVolume* GetTargetBackLog(G4String targetBackName);
  G4LogicalVolume* GetBeamTubeLog(G4String beamTubeName);
  G4LogicalVolume* GetFlangeLog(G4String flangeName);
  G4LogicalVolume* GetCoolingSupportLog(G4String coolingSupportName);

  G4LogicalVolume* GetTestLog(G4String testName);

private:
  void DefineMaterials();
  G4VPhysicalVolume* DefineVolumes();

  G4Material *matAir;
  G4Material *matVaccum;
  G4Material *matCu;
  G4Material *matAl;
  G4Material *matC;
  G4Material *matN;
  G4Material *matGe;
  G4Material *matTa;
  G4Material *matTa2N3;
  G4Material *matTiN;

  G4UserLimits *stepLimit;

  DetectorMessenger *messenger;
};

#endif
