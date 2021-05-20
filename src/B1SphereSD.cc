#include "B1SphereSD.hh"

#include "G4SystemOfUnits.hh"
#include "TTree.h"

B1SphereSD::B1SphereSD(TTree * ot, const G4String& name) : G4VSensitiveDetector(name)
{
  maxHits=100;
  nHits=0;
  partIDList = new G4int[maxHits];
  thetaList = new G4double[maxHits];
  phiList = new G4double[maxHits];
  enList = new G4double[maxHits];

  outtree=ot;
  outtree->Branch("nHits",&nHits,"nHits/I");
  outtree->Branch("partID",partIDList,"partID[nHits]/I");
  outtree->Branch("theta",thetaList,"theta[nHits]/D");
  outtree->Branch("phi",phiList,"phi[nHits]/D");
  outtree->Branch("en",enList,"en[nHits]/D");
}

B1SphereSD::~B1SphereSD()
{
  delete partIDList;
  delete thetaList;
  delete phiList;
  delete enList;
}

void B1SphereSD::Initialize(G4HCofThisEvent* hitCollection)
{
  nHits=0;
}

G4bool B1SphereSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
  if (nHits < maxHits)
    {
      G4ThreeVector hitPos = step->GetPreStepPoint()->GetPosition();
      G4double energy = step->GetPreStepPoint()->GetKineticEnergy();

      partIDList[nHits]=step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
      thetaList[nHits]=hitPos.theta()/deg;
      phiList[nHits]=hitPos.phi()/deg;
      enList[nHits]=energy/GeV;
		
      nHits++;
    }

  return true;
}

void B1SphereSD::EndOfEvent(G4HCofThisEvent* hitCollection)
{

}
