#ifndef BBbarAnalysis_hh
#define BBbarAnalysis_hh

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

//#include <EVENT/LCObject.h>
#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/Vertex.h>
#include <UTIL/LCRelationNavigator.h>
#include <UTIL/PIDHandler.h>
#include <IMPL/ReconstructedParticleImpl.h>
#include <IMPL/LCCollectionVec.h>

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"
#include "marlin/Processor.h"
#include "lcio.h"
#include <string>
#include <TFile.h>
#include <TTree.h>
#include "QQbarTools.hh"
#include "QQbarMCOperator.hh"

using namespace lcio ;
using namespace marlin ;


namespace QQbarProcessor 
{

  class BBbarAnalysis 
  {
	  
  public:
	  
    BBbarAnalysis ();
    virtual ~BBbarAnalysis () {};
	  
    //METHODS
	  
    void Init(std::string _hfilename) ;
    std::vector< MCParticle * > AnalyseGeneratorBBbar(QQbarMCOperator & opera);
    void AnalyseGeneratorBBbar_PS(QQbarMCOperator & opera);
    void AnalyseBBbar(LCEvent * evt,
		      bool _boolDBDanalysis,
		      bool _kaoncheat,
		      std::string _colRelName,
		      std::string _colName ,
		      std::string _initialJetsColName,
		      std::string _JetsColName ,
		      std::string _JetsRelColName ,
		      std::string _MCColName,
		      std::string _KaonTaggerName
		      ) ;

    void ClearVariables();
    void End();
    
		    
  private:

    void MatchB(std::vector<RecoJet*> * bjets, std::vector< MCParticle * > & mcbs, LCCollection * mcvtxcol);

    TFile * _hfile;
    TTree * _hTree;
    StatsData_BBbar _stats;

  } ;
		
} /* TTbarAnalisys */

#endif



