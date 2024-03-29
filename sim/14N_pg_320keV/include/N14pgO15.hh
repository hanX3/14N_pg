#ifndef N14pO15_H
#define N14pO15_H

#include "G4HadronicInteraction.hh"

//
class N14pgO15: public G4HadronicInteraction
{
public:
  N14pgO15();
  virtual ~N14pgO15();

public:
  virtual G4HadFinalState *ApplyYourself(const G4HadProjectile &projectile, G4Nucleus &targetNucleus);

private:
  void SetLevelsO15();
  void AddGammaRay(G4double energy);

  G4double levelsO15[5];
  G4double levelsBranchRatioO15[5];
  G4double levelsBranchRatioO15Add[5];
};

#endif // N14pgO15_H
