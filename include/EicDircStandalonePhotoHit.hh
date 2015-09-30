#ifndef EicDircStandalonePhotoHit_h
#define EicDircStandalonePhotoHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VPhysicalVolume.hh"

class G4VTouchable;

class EicDircStandalonePhotoHit : public G4VHit
{
public:

  EicDircStandalonePhotoHit();
  virtual ~EicDircStandalonePhotoHit();
  EicDircStandalonePhotoHit(const EicDircStandalonePhotoHit &right);

  const EicDircStandalonePhotoHit& operator=(const EicDircStandalonePhotoHit &right);
  G4int operator==(const EicDircStandalonePhotoHit &right) const;

  inline void *operator new(size_t);
  inline void operator delete(void *aHit);

  virtual void Print();

  inline void SetHitPos(G4double x,G4double y,G4double z)
  {
    fHitPos=G4ThreeVector(x,y,z);
  }

  inline G4ThreeVector GetHitPos(){return fHitPos;}

private:

  G4ThreeVector fHitPos;

};

typedef G4THitsCollection<EicDircStandalonePhotoHit> EicDircStandalonePhotoHitsCollection;

extern G4Allocator<EicDircStandalonePhotoHit> EicDircStandalonePhotoHitAllocator;

inline void* EicDircStandalonePhotoHit::operator new(size_t){
  void *aHit;
  aHit = (void *) EicDircStandalonePhotoHitAllocator.MallocSingle();
  return aHit;
}

inline void EicDircStandalonePhotoHit::operator delete(void *aHit){
  EicDircStandalonePhotoHitAllocator.FreeSingle((EicDircStandalonePhotoHit*) aHit);
}

#endif
