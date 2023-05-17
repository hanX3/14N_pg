#ifndef IonInelasticPhysics_h
#define IonInelasticPhysics_h 1

#include "G4VPhysicsConstructor.hh"

#include "globals.hh"

class IonInelasticPhysics: public G4VPhysicsConstructor
{
public:
  IonInelasticPhysics(const G4String &name = "ion_inelastic");
  virtual ~IonInelasticPhysics();

protected:
  void ConstructParticle() {};
  void ConstructProcess();
};

#endif
