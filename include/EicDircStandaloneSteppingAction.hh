#ifndef EicDircStandaloneSteppingAction_H
#define EicDircStandaloneSteppingACtion_H 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"

#include "G4OpBoundaryProcess.hh"

class EicDircStandaloneTrackingAction;
class EicDircStandaloneSteppingMessenger;

class EicDircStandaloneSteppingAction : public G4UserSteppingAction
{
public:

  EicDircStandaloneSteppingAction();
  virtual ~EicDircStandaloneSteppingAction();
  virtual void UserSteppingAction(const G4Step*);

  void SetOneStepPrimaries(G4bool b){fOneStepPrimaries=b;}
  G4bool GetOneStepPrimaries(){return fOneStepPrimaries;}

private:

  G4bool fOneStepPrimaries;
  EicDircStandaloneSteppingMessenger* fSteppingMessenger;

  G4OpBoundaryProcessStatus fExpectedNextStatus;
};

#endif
