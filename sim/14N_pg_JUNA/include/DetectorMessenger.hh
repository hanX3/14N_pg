#ifndef B2aDetectorMessenger_h
#define B2aDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

class DetectorMessenger: public G4UImessenger
{
public:
  DetectorMessenger(DetectorConstruction*);
  virtual ~DetectorMessenger();

private:
  DetectorConstruction *detectorConstruction;

  G4UIdirectory *directory;
  G4UIdirectory *detDirectory;
};

#endif
