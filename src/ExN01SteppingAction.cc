/**
* @file   SteppingAction.cc
*
* @date   17 Dec 2009
* @author adotti
*
* @brief  Implements user class SteppingAction.
*/
#include <vector>

#include "ExN01CreateTree.hh"
#include "B4Analysis.hh"
#include "LinkDef.h"
#include "ExN01SteppingAction.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"

double casualen (double min, double max)			//random numbers generator
    {
    return (min + (max - min)*rand()/(1.*RAND_MAX));
    }

using namespace std ;

SteppingAction::SteppingAction()
	{
	}

SteppingAction::~SteppingAction()
	{
	}	

void SteppingAction::UserSteppingAction( const G4Step * theStep ) 
	{
	//get the two points of a step
	G4StepPoint* point1 = theStep->GetPreStepPoint();
	G4StepPoint* point2 = theStep->GetPostStepPoint();
    
    	//get the particle involved in the step	
	G4ParticleDefinition* particle = theStep->GetTrack()->GetDefinition(); 

	//get the name of the volume in which the particles is at the beginning of the step
	G4TouchableHandle touch1 = point1->GetTouchableHandle();
	G4VPhysicalVolume* pre_volume = touch1->GetVolume();
    	G4String pre_volName = "" ; if ( pre_volume ) pre_volName = pre_volume -> GetName () ;

    	//get the name of the volume in which the particles is at the end of the step
   	G4TouchableHandle touch2 = point2->GetTouchableHandle();
   	G4VPhysicalVolume* post_volume = touch2->GetVolume();
    	G4String post_volName = "" ; if ( post_volume ) post_volName = post_volume -> GetName () ;

	if ( particle -> GetParticleName() == "e+" || particle -> GetParticleName() == "e+")
		{
			if ( pre_volName == "World" && post_volName == "mcp" )
			{
			float R1 = casualen (0.,1.);		//efficiency
			if (R1 > 0.5)
			CreateTree::Instance() -> Q1 -> push_back (casualen (0.,2.));		//charge
			else CreateTree::Instance() -> Q1 -> push_back(0.);
			}
	
		if ( pre_volName == "Abs" )
			{
			CreateTree::Instance() -> EnergyTotalAbs1 += theStep->GetTotalEnergyDeposit();
			}
	
		if ( pre_volName == "World" && post_volName == "mcp2" )
			{
			float R2 = casualen (0.,1.);
			if (R2 > 0.5)
			CreateTree::Instance() -> Q2 -> push_back (casualen (0.,2.));
			else CreateTree::Instance() -> Q2 -> push_back(0.);
			}
	
		if ( pre_volName == "Abs2" )
			{
			CreateTree::Instance() -> EnergyTotalAbs2 += theStep->GetTotalEnergyDeposit();
			}

               		if ( pre_volName == "Calo" )
	               		{
   			        CreateTree::Instance() -> EnergyTotalCalo += theStep->GetTotalEnergyDeposit();       
			        }
		}
	}
