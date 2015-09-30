#include "EicDircStandaloneSteppingAction.hh"
//#include "EicDircStandaloneEventAction.hh"
//#include "EicDircStandaloneTrackingAction.hh"
//#include "EicDircStandaloneTrajectory.hh"
#include "EicDircStandaloneSD.hh"
//#include "EicDircStandaloneUserTrackInformation.hh"
//#include "EicDircStandaloneUserEventInformation.hh"
#include "EicDircStandaloneSteppingMessenger.hh"
//#include "EicDircStandaloneRecorderBase.hh"

#include "G4SteppingManager.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandaloneSteppingAction::EicDircStandaloneSteppingAction()
  : fOneStepPrimaries(false)
{
  fSteppingMessenger = new EicDircStandaloneSteppingMessenger(this);

  fExpectedNextStatus = Undefined;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandaloneSteppingAction::~EicDircStandaloneSteppingAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EicDircStandaloneSteppingAction::UserSteppingAction(const G4Step * theStep){
  G4Track* theTrack = theStep->GetTrack();

  G4StepPoint* thePrePoint = theStep->GetPreStepPoint();
  G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();

  G4StepPoint* thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

  if(!thePostPV){ //out of world
    return;
  }

  /* If optical photon enters photosensor, kill it and record its entry position */
  G4ParticleDefinition* particleType = theTrack->GetDefinition();
  if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()){
    //Optical photon only

    if ( thePostPV->GetName() == "Photosensor" )
      {
	//Triger sensitive detector manually
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	G4String sdName="/EicDircStandaloneDet/photoSD";
	EicDircStandaloneSD* photoSD = (EicDircStandaloneSD*)SDman->FindSensitiveDetector(sdName);
	if(photoSD) photoSD->ProcessHits_constStep(theStep,NULL);

	theTrack->SetTrackStatus(fStopAndKill);
      }
  }

}
