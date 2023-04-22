#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;
class G4Timer;
class RootIO;
class PrimaryGeneratorAction;

class RunAction: public G4UserRunAction
{
public:
  RunAction(RootIO* therootIO, PrimaryGeneratorAction* thefPriGen);
  virtual ~RunAction();

  virtual void BeginOfRunAction(const G4Run* run);
  virtual void   EndOfRunAction(const G4Run* run);

private:
  G4Timer* fTimer;
  RootIO* fRootIO;
  PrimaryGeneratorAction* fPriGen;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
