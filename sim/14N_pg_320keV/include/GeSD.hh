#ifndef GeSD_h
#define GeSD_h 1

#include "G4VSensitiveDetector.hh"
#include "GeHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;  //  save multi SD hitcollection objects

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class GeSD: public G4VSensitiveDetector
{
public:
  GeSD(const G4String& theSDname, const G4String& thehitsCollectionName);
  virtual ~GeSD();

  //  methods from base class
  virtual void  Initialize(G4HCofThisEvent* thehitCollection);
  virtual G4bool ProcessHits(G4Step* thestep, G4TouchableHistory* thehistory);
  virtual void   EndOfEvent(G4HCofThisEvent* thehitCollection);

private:
  GeHitsCollection* hitsCollection;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
