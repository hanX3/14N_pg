#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DetectorConstruction;
class EventAction;
class RootIO;
class G4LogicalVolume;

class SteppingAction: public G4UserSteppingAction
{
public:
  SteppingAction(DetectorConstruction *detectorConstruction, RootIO *rootFile);
  virtual ~SteppingAction();

  virtual void UserSteppingAction(const G4Step*);

private:
  const DetectorConstruction *detConstruction;
  RootIO *rootIO;

private:
  G4int eventID;
  G4double edep;
  G4int trackID;
  G4String particleName;
  G4String detectorName;
  G4double prex;
  G4double prey;
  G4double prez;
  G4double preTotalEnergy;
  G4double preKineEnergy;
  G4double postx;
  G4double posty;
  G4double postz;
  G4double postTotalEnergy;
  G4double postKineEnergy;
  G4double stepLength;
  G4String processName;
};

#endif
