#include "EicDircStandalonePhotoHit.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

G4Allocator<EicDircStandalonePhotoHit> EicDircStandalonePhotoHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandalonePhotoHit::EicDircStandalonePhotoHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandalonePhotoHit::~EicDircStandalonePhotoHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandalonePhotoHit::EicDircStandalonePhotoHit(const EicDircStandalonePhotoHit &right) : G4VHit()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const EicDircStandalonePhotoHit& EicDircStandalonePhotoHit::operator=(const EicDircStandalonePhotoHit &right){
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int EicDircStandalonePhotoHit::operator==(const EicDircStandalonePhotoHit &right) const{
  return (0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EicDircStandalonePhotoHit::Print()
{
  G4cout << "HIT at " << fHitPos.getX() << " " << fHitPos.getY() << " " << fHitPos.getZ() << G4endl;
}
