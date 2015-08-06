class EicDircStandaloneSteppingVerbose;

#ifndef EicDircStandaloneSteppingVerbose_h
#define EicDircStandaloneSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/** @TODO Review this class completely
 */
class EicDircStandaloneSteppingVerbose : public G4SteppingVerbose
{
public:

  EicDircStandaloneSteppingVerbose();
  ~EicDircStandaloneSteppingVerbose();

  void StepInfo();
  void TrackingStarted();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
