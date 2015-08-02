#ifndef EicDircStandaloneStackingAction_H
#define EicDircStandaloneStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/** @TODO Review this class completely
 */
class EicDircStandaloneStackingAction : public G4UserStackingAction
{
public:
  EicDircStandaloneStackingAction();
  ~EicDircStandaloneStackingAction();

public:
  G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  void NewStage();
  void PrepareNewEvent();

private:
  G4int gammaCounter;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

