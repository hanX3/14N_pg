#include "GeSD.hh"
#include "Constants.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
GeSD::GeSD(const G4String& theSDname, const G4String& thehitsCollectionName)
: G4VSensitiveDetector(theSDname), hitsCollection(NULL)
{
  // hitcollection's name, have to be defined
  collectionName.insert(thehitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
GeSD::~GeSD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void GeSD::Initialize(G4HCofThisEvent* hce)
{
  hitsCollection = new GeHitsCollection(SensitiveDetectorName, collectionName[0]);
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);
  hce->AddHitsCollection(hcID, hitsCollection);

  for(G4int i=0;i<NofGe;i++){
    hitsCollection->insert(new GeHit());
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool GeSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep == 0){
    return false;
  }

  auto touchable = (aStep->GetPreStepPoint()->GetTouchable());
  G4int geNumber = touchable->GetVolume()->GetCopyNo();

  auto newHit = (*hitsCollection)[geNumber];
  newHit->AddEdep(edep);

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GeSD::EndOfEvent(G4HCofThisEvent*)
{
  //print some information
  if(verboseLevel>1){
    G4int nofHits = hitsCollection->entries();
    G4cout << G4endl << "-------->Hits Collection: in this event they are " << nofHits << " hits in the tracker chambers: " << G4endl;

    for(G4int i=0;i<nofHits;i++){
      (*hitsCollection)[i]->Print();
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
