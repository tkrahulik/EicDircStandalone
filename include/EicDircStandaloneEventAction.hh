#ifndef EicDircStandaloneEventAction_h
#define EicDircStandaloneEventAction_h 1

#include "G4UserEventAction.hh"

#include "EicDircStandalonePhotoHit.hh"

class G4Event;

/// Event action

class EicDircStandaloneEventAction : public G4UserEventAction
{
public:
  EicDircStandaloneEventAction();
  ~EicDircStandaloneEventAction();

public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);

private:
  EicDircStandalonePhotoHitsCollection* GetPhotoHitsCollection(const G4String& hcName, const G4Event* event);

};

#endif


