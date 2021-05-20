#ifndef B1SphereSD_h
#define B1SphereSD_h 1

#include "G4VSensitiveDetector.hh"

// Sensitive Detector Class for sphere

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class TTree;

class B1SphereSD : public G4VSensitiveDetector
{
public:
  B1SphereSD(TTree * ot, const G4String& name);
  virtual ~B1SphereSD();
  
  // methods from base class
  virtual void   Initialize(G4HCofThisEvent* hitCollection);
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
  virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

private:  
  TTree * outtree;
  G4int maxHits; // Maximum number of hits per event
  G4int nHits; // Number of hits in this event
  G4int *partIDList; // List of particle IDs for each hit
  G4double * thetaList; // List of theta angles for each hit
  G4double * phiList; // List of phi angles for each hit
  G4double * enList; // List of particle energy for each hit
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
