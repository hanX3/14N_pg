#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetectorMessenger::DetectorMessenger(DetectorConstruction *det)
: G4UImessenger(),
  detectorConstruction(det)
{
  directory = new G4UIdirectory("/juna/");
  directory->SetGuidance("UI commands specific to this example.");

  detDirectory = new G4UIdirectory("/juna/det/");
  detDirectory->SetGuidance("Detector construction control");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetectorMessenger::~DetectorMessenger()
{
  delete directory;
  delete detDirectory;
}