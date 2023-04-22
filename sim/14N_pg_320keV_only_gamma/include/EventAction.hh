#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"

#include "globals.hh"

class RootIO;
class TFile;
class PrimaryGeneratorAction;

// Event action class

class EventAction: public G4UserEventAction
{
public:
  EventAction(PrimaryGeneratorAction *thePri, RootIO *rootIO);
  virtual ~EventAction();

  virtual void  BeginOfEventAction(const G4Event* );
  virtual void    EndOfEventAction(const G4Event* );

private:
  PrimaryGeneratorAction* primary;
  RootIO* rootIO;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
