"""
Created:      1 December 2017
Last Updated: 1 December 2017

Dan Marley
daniel.edison.marley@cernSPAMNOT.ch
Texas A&M University

Justin Pilot
UC Davis

---

Scikit-learn model -> lwtnn converter

Convert simple sklearn MLP Classifer to proper format for lwtnn framework.
  https://github.com/lwtnn/lwtnn
  Based on converters/keras2json.py.

WARNING: Some values are hard-coded due to my ignorance with sklearn interface
NB:
   scale/offset defined from "StandardScalar"
     offset = -mean          (attribute: mean_)
     1 / standard_deviation  (attribute: var_)
"""
import sys
import json
import numpy as np
from math import sqrt
from argparse import ArgumentParser
from sklearn import svm, metrics, preprocessing
from sklearn.externals import joblib


class Sklearn2json(object):
    """Class to convert scikit-learn model to JSON format for lwtnn"""
    def __init__(self):
        """Set attributes of the class"""
        # converting model
        self.model          = None          # model from sklearn
        self.scaler_file    = None          # StandardScaler object from sklearn
        self.output_file    = None          # name of output file to store JSON
        self.variables_file = None          # name of JSON file that contains variables

        # generate variables JSON
        self.makeVariablesJSON = False      # boolean to (not) make new variables JSON
        self.listOfVariables   = None       # name of text file that contains list of variables

        # parameters for converting model
        self.architecutre      = "dense"    # always appears to be this (fully-connected MLPClassifier)
        self.nodeActivation    = "linear"   # always appears to be this
        self.class_labels      = None       # names in map for NN outputs
        self.miscellaneous     = None       # misc. info

        # extra parameters needed
        self.activation_fns    = {'relu':'rectified','softmax':'softmax'} # sklearn->lwtnn naming

        # storing output (JSON)
        self.output = {"defaults":{},
                       "inputs":[],
                       "layers":[],
                       "miscellaneous":{},
                       "outputs":[]}


    def execute(self):
        """Run the converter"""
        print " Running scikit-learn to JSON converter "
        if self.makeVariablesJSON:
            print " > Generating variables JSON file {0}".format(self.variables_file)
            self.generateVariablesJSON()  # generate the variables JSON file from scratch

        print " > Load sklearn model "
        self.loadModel()       # load the sklearn model

        print " > Load variables JSON "
        self.loadVariables()   # load the inputs (variables/scales/offsets/misc./class labels)

        print " > Load layers of neural network into dictionary "
        self.loadLayers()      # load the network layers

        print " > Save model to {0}".format(self.output_file)
        self.saveModel()       # save the model to JSON output

        return


    def loadModel(self):
        """Load the model (saved with joblib!)"""
        self.mlp = joblib.load(self.model)       # load model

        self.activation    = self.mlp.activation      # activation functions (one for all hidden layers)
        self.outActivation = self.mlp.out_activation_ # output activation
        self.weights       = self.mlp.coefs_          # weights vectors
        self.biases        = self.mlp.intercepts_     # bias vectors
        self.nLayers       = self.mlp.n_layers_       # number of layers in NN (input + N hidden + output)
        self.nOutputs      = self.mlp.n_outputs_      # number of output values
        self.sizeOfHLs     = self.mlp.hidden_layer_sizes   # tuple of hidden layer sizes
        self.nHiddenLayers = len(self.sizeOfHLs)      # number of hidden layers

        return


    def loadVariables(self):
        """Inputs (variables, weights + offsets).
           Read the variables JSON file to better understand what is being saved.
        """
        self.variables = json.load( open(self.variables_file) ) # contains variables, class_labels, and misc.

        self.output["inputs"]        = self.variables["inputs"]
        self.output["miscellaneous"] = self.variables["miscellaneous"]

        output_names = self.variables["class_labels"]
        if self.nOutputs!=len(output_names):
            print (" WARNING:  Number of outputs ({0}) "
                  "and number of output names ({1}) do not match!".format(nOutputs,output_names))
            print " WARNING:  Please check the model and list of output names."
            sys.exit(1)

        self.output["outputs"] = output_names

        return


    def loadLayers(self):
        """
        Connecting layer (l) to layer (l+1) & storing in a dictionary (JSON):
           IN  -> Hidden Layer l (HL1)
           HL1 -> HL2
           ...
           HLN -> OUT
        """
        if any( [self.nLayers != len(elem)+1 for elem in [self.weights,self.biases] ] ):
            print (" WARNING:  Number of hidden layers ({0}) "
                  "and length of weights ({1}) do not match!".format(self.nLayers,self.weights+1))
            print " WARNING:  Please check the model."
            sys.exit(1)

        for l in range(self.nLayers-1): 
            # connecting layer (l) to layer (l+1)
            layer = {}
            layer["architecture"] = self.architecutre
            layer["activation"]   = self.nodeActivation
            layer["weights"]      = self.weights[l].T.flatten().tolist()
            layer["bias"]         = self.biases[l].flatten().tolist()

            self.output["layers"].append(layer)

            # activation function at layer (l+1)
            activation_fn = self.activation if l!=self.nLayers-2 else self.outActivation
            activation_fn = self.activation_fns[activation_fn]
            act_fn = {
              "activation":   activation_fn, 
              "architecture": self.architecutre, 
              "bias": [],    # always empty, I think (?)
              "weights": []  # always empty, I think (?)
            }
            self.output["layers"].append(act_fn)

        return


    def saveModel(self):
        """Save data to JSON file"""
        print(json.dumps(self.output, indent=2, sort_keys=True))
#        with open(self.output_file, 'w') as outfile:
#            json.dump(self.output, outfile)

        return


    def generateVariablesJSON(self):
        """From list of variables & StandardScaler, generate variables JSON file"""
        scaler = joblib.load(self.scaler_file)
        vars   = open(self.listOfVariables,"r").readlines()

        variablesJSON = {"inputs": [],
                         "class_labels": self.class_labels,
                         "miscellaneous":self.miscellaneous}

        # generate inputs
        for i,var in enumerate(vars):
            var = var.rstrip('\n')
            input = {"name": var,
                     "scale":-scaler.mean_[i],
                     "offset":1/ sqrt(scaler.var_[i]) }
            variablesJSON["inputs"].append(input)


        with open(self.variables_file,'w') as outfile:
            json.dump(variablesJSON, outfile)

        return



# Convert scikit-learn model to JSON
if __name__ == '__main__':

    ## Parse arguments
    parser = ArgumentParser(description="Scikit-learn Converter")

    parser.add_argument('-m','--model', action='store',
                        default='data/BEST_mlp.pkl',
                        dest='model',
                        help='Name of the model from scikit-lean to convert.')
    parser.add_argument('-v','--variables', action='store',
                        default='data/BEST_mlp_variables.json',
                        dest='variables',
                        help='Name of file that contains variables in model.')
    parser.add_argument('-o','--output', action='store',
                        default='data/BEST_mlp.json',
                        dest='output',
                        help='Name of output file to save the JSON model.')
    parser.add_argument('-s','--scaler', action='store',
                        default='data/BEST_scaler.pkl',
                        dest='scaler',
                        help='Name of the scaler from scikit-learn to scale inputs.')
    parser.add_argument('-mv','--make_variables', action='store_true',
                        dest='make_variables',
                        help='Make the JSON file that contains variable names with scaling and offset values.')
    results = parser.parse_args()



    ## Setup sklearn2json object
    conv = Sklearn2json()
    conv.model          = results.model     # 'BEST_mlp.pkl'
    conv.scaler_file    = results.scaler    # 'BEST_scaler.pkl'
    conv.output_file    = results.output    # 'BEST_mlp.json'
    conv.variables_file = results.variables # 'BEST_mlp_variables.json'

    # generate variables JSON (add options later, if needed)
    conv.makeVariablesJSON = results.make_variables
    if results.make_variables:
        conv.listOfVariables = 'data/BEST_mlp_variables.txt'
        conv.class_labels    = ["dnn_qcd","dnn_w","dnn_z","dnn_higgs","dnn_top"]
        conv.miscellaneous   = {"scikit-learn": "0.18.1"}

    # execute the converter!
    conv.execute()


## THE END
