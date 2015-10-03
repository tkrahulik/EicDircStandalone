#include "EicDircStandaloneSD.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4Track.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4OpticalPhoton.hh"

EicDircStandaloneSD::EicDircStandaloneSD(G4String DetName, G4String HitColName="EicDircStandalonePhotoHitCollection" )
  :G4VSensitiveDetector(DetName),HCID(-1)
{
  G4String HCname;
  collectionName.insert(HitColName);
}

EicDircStandaloneSD::~EicDircStandaloneSD(){

}

void EicDircStandaloneSD::Initialize(G4HCofThisEvent*)
{

  PhotoHitCollection = new EicDircStandalonePhotoHitsCollection
    (SensitiveDetectorName,collectionName[0]);

}


G4bool EicDircStandaloneSD::ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist)
{
  return false;
}

G4bool EicDircStandaloneSD::ProcessHits_constStep(const G4Step*aStep,G4TouchableHistory*ROhist)
{
  //need to know if this is an optical photon
  if(aStep->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition())
    return false;

  //G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());

  G4Track* theTrack = aStep->GetTrack();

  G4StepPoint* thePostPoint = aStep->GetPostStepPoint();

  EicDircStandalonePhotoHit* hit=NULL;

  G4ThreeVector hitpos = thePostPoint->GetPosition();

  G4double wavelength = 1240.0 / theTrack->GetTotalEnergy()*eV; // in nm

  if(hit==NULL){//this pad wasnt previously hit in this event
    hit = new EicDircStandalonePhotoHit(); //so create new hit
    hit->SetHitPos(hitpos.getX(), hitpos.getY(), hitpos.getZ());
    hit->SetWavelength( wavelength );
    PhotoHitCollection->insert(hit);
  }

  return true;
}


void  EicDircStandaloneSD::EndOfEvent(G4HCofThisEvent*HCE){

  if( HCID < 0 ){
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }

  HCE->AddHitsCollection( HCID, PhotoHitCollection );

}

void  EicDircStandaloneSD::clear(){}

void   EicDircStandaloneSD::DrawAll(){ }

void   EicDircStandaloneSD::PrintAll(){ }




