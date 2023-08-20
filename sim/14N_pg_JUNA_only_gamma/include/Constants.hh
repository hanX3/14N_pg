#ifndef Constants_h
#define Constants_h 1

#include "globals.hh"
#include "G4SystemOfUnits.hh"


constexpr G4double worldSizeX = 2. *m;
constexpr G4double worldSizeY = 2. *m;
constexpr G4double worldSizeZ = 2. *m;

//beam tube
constexpr G4double BeamTubeR = 10. * mm;
constexpr G4double BeamTubeLength = 50. * mm;

//target
constexpr G4double TargetR = 20. *mm;
constexpr G4double TargetThickness = 4. *mm;

//target back
constexpr G4double TargetBackR = 20. *mm;
constexpr G4double TargetBackThickness = 1. *mm;
constexpr G4double TargetBackPosDis = TargetThickness + TargetBackThickness;

//flange
constexpr G4double FlangeR = 82.5 *mm;
constexpr G4double FlangeRCut = 36. *mm;
constexpr G4double FlangeThickness = 6.5 *mm;
constexpr G4double FlangeThicknessCut = 5.25 *mm;
constexpr G4double FlangePosDis = FlangeThickness + TargetThickness + 2*TargetBackThickness;

//cooling support
constexpr G4double CoolingSupportR = 36. *mm;
constexpr G4double CoolingSupportRCut = 20. *mm;
constexpr G4double CoolingSupportThickness = 4.25 *mm;
constexpr G4double CoolingSupportThicknessCut = 3.25 *mm;
constexpr G4double CoolingSupportPosDis = TargetThickness + 2.*TargetBackThickness + 2.*(FlangeThickness-FlangeThicknessCut) + CoolingSupportThickness;

//Ge
constexpr G4double TargetGeDis = 60. * mm;
constexpr G4double GeR  = 46.7 * mm;
constexpr G4double GeHeight  = 54.5 * mm;
constexpr G4double GePosDis = GeHeight + TargetGeDis + TargetThickness + 2.*TargetBackThickness;
constexpr G4int NofGe = 1;
constexpr G4double GeThetaAngle[NofGe] = {0.};
constexpr G4double LN2HoleR = 5.55 * mm;
constexpr G4double LN2HoleDeep = 47.95 * mm;

//face1
constexpr G4double Face1R = 49.7 *mm;
constexpr G4double Face1Thickness = 0.015 *mm;

//face2
constexpr G4double Face2R = 55. *mm;
constexpr G4double Face2Thickness = 0.38 *mm;

//distance
constexpr G4double Face1Face2Dis = 5. *mm;
constexpr G4double Face1Dis = GePosDis - GeHeight - Face1Thickness;
constexpr G4double Face2Dis = GePosDis - GeHeight - 2.*Face1Thickness - Face1Face2Dis - Face2Thickness;

//surround1
constexpr G4double Surround1Thickness = 0.8 *mm;
constexpr G4double Surround1R1 = Face1R;
constexpr G4double Surround1R2 = Surround1R1 + Surround1Thickness;
constexpr G4double Surround1Length = 60. *mm;
constexpr G4double Surround1Dis = GePosDis - GeHeight + Surround1Length - 2.*Face1Thickness;

//surround2
constexpr G4double Surround2Thickness = 1.5 *mm;
constexpr G4double Surround2R1 = Face2R;
constexpr G4double Surround2R2 = Surround2R1 + Surround2Thickness;
constexpr G4double Surround2Length = 75. *mm;
constexpr G4double Surround2Dis = GePosDis - GeHeight + Surround2Length - 2.*Face1Thickness - Face1Face2Dis - 2.*Face2Thickness;

//beam
constexpr G4double BeamAngle = 0.;
constexpr G4double BeamSize = 5 *mm;//r
constexpr G4double ParticleEnergy = 7556. *keV;

//step limit
constexpr G4double MaxStepLimit = 10 *um;

#endif
