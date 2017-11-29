Justin Pilot  
17 Nov 2017 (D Marley) 

# BESTAnalysis

To check out:
```
cmsrel CMSSW_8_0_12
cd CMSSW_8_0_12/src
cmsenv
git clone https://github.com/justinrpilot/BESTAnalysis Analysis
scram b 
```

To get started:
```
cd Analysis/BESTProducer/test
cmsRun run_HH.py
```

## Training

`BESTProducer.cc` -- computes the event shape quantities in the boosted frame, 
adds them as EDM products to the event, and produces a flat TTree with the quantities for NN training.  
To run:
```
[BESTProducer/test> cmsRun run_TT.py
```

Several files are available (`run_TT.py`, `run_WW.py`, etc.) 
and can be configured according to the sample of interest with the following options:

```
process.run = cms.EDProducer('BESTProducer',
	pdgIDforMatch = cms.int32(6),  → the particle used for jet matching
	NNtargetX = cms.int32(1),  → not used
	NNtargetY = cms.int32(1),  → not used anymore
	isMC = cms.int32(1),   → if the input is MC (to use data eventually)
	doMatch = cms.int32(0) → if the matching requirement with pdgID is actually applied
)
```

To run on crab, use `crab*.py`, where there are different decay modes and resonance masses.

Once you have the training files, you can train the NN.  You can find some of my most recentfiles in 
`/store/user/pilot/BESTFiles/Aug8/`

Before training, some processing needs to be done, to compute additional variables and add the targets.  
The script is `runTree.C`, which can also be used to evaluate new NNs on existing samples on-the-fly:

```
[BESTProducer/test> root -l
[0] .L runTree.C
[1] runTree(string inFile, string outFile, string histName, float targX, float targY, float targ3, float targ4, float targ5, bool reduce = 1)
```

The options are as follows

File | Description
---- | -----------
inFile   | the inputFile to run over
outFile  | the outputFile name
histName | the weight file used to flatten the pT distribution (see below)
targets  | the values of the desired outputs for each node
reduce   | reduce the total number of events to a desired number for training/testing


I usually use `run_all.C` to run these commands sequentially for all samples.  
Flattening the et: Use the script `flatten.C`

```
root -l
[0] .L flatten.C
[1] flatten(TString infile, TString outWeightFile, float etMin = 500, float etMax = 4000)
```

It will spit out a weight file that you use with `runTree.C` as shown above.  
You can now run the training:

```
[BESTProducer/TMVATraining > root -l TMVARegression.C  
```

*Currently, this takes a long time!*
Some important pieces of this file:

Piece | Description
----- | -----
`factory->AddVariable( "h1_top", "h1_top", "", 'F' );`  | Adding the variables for training -- they must match the branch names in the trees
`factory->AddTarget( "targetX" );`       |   The regression "targets" (output nodes) and desired outputs -- must have all 5 and the names must match the branch names again
`TChain *input = new TChain("jetTree");` |  The input tree and file names (everything is added to one chain)
`factory->SetWeightExpression( "flatten", "Regression" );` |  Apply the weights to flatten et
`TCut mycut = "et > 500 && et < 3000"`   |  A cut to apply in creating testing/training samples
`factory->PrepareTrainingAndTestTree( mycut, "nTrain_Regression=100000:nTest_Regression=100000:SplitMode=Random:NormMode=NumEvents:!V" );` |  Define training/testing sizes


You can reduce the number of training events and input variables to train a small NN quickly to see if things are working.  
The network is defined by an xml file in `TMVATraining/weights/`  
**This xml file needs to be used with `runTree.C` to evaluate the NN performance**

Once you have a NN xml file, you can re-run `runTree.C` to look at the output distributions in a nice way, 
make sure you have the correct xml file in there:

See [here](https://github.com/justinrpilot/BESTAnalysis/blob/master/BESTProducer/test/runTree.C#L139).

You must have the variables defined in the same order as you did in `TMVARegression.C` for the TMVA::Reader class.
And make sure `BookMVA()` has the new file name of the xml file from training.



## Plotting

Some plotting scripts that are useful:

Script | Description
------ | ------
`draw.C`   | compares W/Z/t/H/j samples for individual variables (DoDraw.C for batch plot creation)
`draw2D.C` | makes the cool 2D plot and lego plots for the individual samples



## Standalone

To use the BEST tagger inside of another framework, 
access the class in the `BoostedEventShapeTagger` directory.  
The class requires a minimal setup 
(initialize the TMVA object and generate inputs to the network to obtain output).  
An example configuration file is provided in "BESTAnalysis/BoostedEventShapeTagger/data/config.txt".

Checkout & build (after setting up your CMSSW environment!):
```
git clone https://github.com/demarley/BESTAnalysis.git 
cd BESTAnalysis/BoostedEventShapeTagger
scram b -j8
```

In your class, simply provide the following changes:

- Header file
```
#include "BESTAnalysis/BoostedEventShapeTagger/interface/BoostedEventShapeTagger.h"
// private:
BoostedEventShapeTagger *m_BEST;
```

- Source file
```
// constructor (pass the name of the configuration file)
m_BEST = new BoostedEventShapeTagger( "BESTAnalysis/BoostedEventShapeTagger/data/config.txt" );

// destructor
delete m_BEST;

// event loop
std::vector<float> NNresults = m_BEST->execute(ijet);  // ijet is a pat::Jet
int particleType = m_BEST->getParticleID();            // automatically calculate the particle classification
```

- BuildFile
```BuildFile.xml
<use   name="BESTAnalysis/BoostedEventShapeTagger"/>
```

And re-compile your code using `scram`.  
The outputs, `NNresults` and `particleType` can then be saved to your output file,
or used in some other way.
