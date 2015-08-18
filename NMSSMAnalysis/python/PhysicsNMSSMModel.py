import os

from HiggsAnalysis.CombinedLimit.PhysicsModel import PhysicsModel
#from HiggsAnalysis.HiggsToTauTau.tools.mssm_xsec_tools import mssm_xsec_tools

class NMSSMLikeHiggsModel(PhysicsModel):
    """
    Base class for all further derivatives. At the moment this allows for ggH and WH for production and Haa (a->tautau)
    for decay. Supported run period is 8TeV. The decay channels and run period has to be part of the datacards name.
    The production channel is taken from the samples name following the CMSHCG convention for production channels.
    """
    def getHiggsSignalYieldScale(self, production, decay, energy):
            raise RuntimeError, "Not implemented"
    def getYieldScale(self,bin,process):
        """
        Split in production and decay channels. Call getHiggsSignalYieldScale. Return 1 for backgrounds.
        """
        if not self.DC.isSignal[process]: return 1
        processSource = process
        decaySource   = self.options.fileName+":"+bin # by default, decay comes from the datacard name or bin label
        if "_" in process: (processSource, decaySource) = process.split("_")
        if processSource not in ["ggH", "WH", "Haa"]:
            raise RuntimeError, "Validation Error: signal process %s not among the allowed ones." % processSource
        foundDecay = None
        for D in [ "Haa" ]:
            print D
            if D in decaySource:
                if foundDecay: raise RuntimeError, "Validation Error: decay string %s contains multiple known decay names" % decaySource
                foundDecay = D
        if not foundDecay: print "Oy!" ## RuntimeError, "Validation Error: decay string %s does not contain any known decay name" % decaySource
        foundEnergy = None
        for D in [ "8TeV" ]:
            if D in decaySource:
                if foundEnergy: print "Oy!" ##raise RuntimeError, "Validation Error: decay string %s contains multiple known energies" % decaySource
                foundEnergy = D
        if not foundEnergy:
            foundEnergy = "8TeV" ## To ensure backward compatibility?
            print "Warning: decay string %s does not contain any known energy, assuming %s" % (decaySource, foundEnergy)
        return self.getHiggsSignalYieldScale(processSource, foundDecay, foundEnergy)

class FloatingNMSSMXSHiggs(NMSSMLikeHiggsModel):
    """
    Trivial model to float ggH and WH independently. At the moment only ggH and Wh are supported. Extensions to the other
    production channels channels are given in comments. Also the principle how to deal with manipulations of the POI's and
    other defined roofit variables are shown in comments. 
    """
    def __init__(self):
        NMSSMLikeHiggsModel.__init__(self) # not using 'super(x,self).__init__' since I don't understand it
        #self.tanb   = None
        self.modes    = [ "ggH", "WH" ]
        self.mARange  = [] #DECIDE_WITH_GROUP
        self.ggHRange = ['0.','10.'] #DECIDE_WITH_GROUP
        self.WHRange = ['0.','10.'] #DECIDE_WITH_GROUP
        
    def setPhysicsOptions(self,physOptions):
        """
        Options are: modes. Examples for options like mARange and tanb are given in comments. 
        """
        for po in physOptions:
            #if po.startswith("tanb="): self.tanb = po.replace("tanb=", "")
            if po.startswith("modes="): self.modes = po.replace("modes=","").split(",")
            if po.startswith("mARange="):
                self.mARange = po.replace("mARange=","").split(":")
                if len(self.mARange) != 2:
                    raise RuntimeError, "Definition of mA range requires two extrema, separated by ':'"
                elif float(self.mARange[0]) >= float(self.mARange[1]):
                    raise RuntimeError, "Extrema for mA range defined with inverterd order. Second element must be larger than first element"
            if po.startswith("ggHRange="):
                self.ggHRange = po.replace("ggHRange=","").split(":")
                print "This ggH range is: " + self.ggHRange[0] + "," + self.ggHRange[1]
                if len(self.ggHRange) != 2:
                    raise RuntimeError, "ggH signal strength range requires minimal and maximal value"
                elif float(self.ggHRange[0]) >= float(self.ggHRange[1]):
                    raise RuntimeError, "minimal and maximal range swapped. Second value must be larger first one"
            if po.startswith("WHRange="):
                self.WHRange = po.replace("WHRange=","").split(":")
                print "This WH range is: " + self.WHRange[0] + "," + self.WHRange[1]
                if len(self.WHRange) != 2:
                    raise RuntimeError, "WH signal strength range requires minimal and maximal value"
                elif float(self.WHRange[0]) >= float(self.WHRange[1]):
                    raise RuntimeError, "minimal and maximal range swapped. Second value must be larger first one"
        print "At the end of everything the ggH range is: " + self.ggHRange[0] + "," + self.ggHRange[1]
        print "At the end of everything the WH range is: " + self.WHRange[0] + "," + self.WHRange[1]


    def doParametersOfInterest(self):
        """
        Create POI and other parameters, and define the POI set. E.g. Evaluate cross section for given values of mA and tanb
        """
        ## Define signal strengths on ggH and WH as POI, NOTE: the range of the POIs is defined here

        ### TEST ME ### self.modelBuilder.doVar("r_ggH[%s,%s,%s]" % (str((float(self.ggHRange[0])+float(self.ggHRange[1]))/2.), self.ggHRange[0], self.ggHRange[1]));
        ### TEST ME ### self.modelBuilder.doVar("r_WH[%s,%s,%s]" % (str((float(self.WHRange[0])+float(self.WHRange[1]))/2.), self.WHRange[0], self.WHRange[1]));

        #self.modelBuilder.doVar("r_ggH[%s,%s,%s]" % (str((float(self.ggHRange[0])+float(self.ggHRange[1]))/2.), self.ggHRange[0], self.ggHRange[1]));
        #self.modelBuilder.doVar("r_WH[%s,%s,%s]" % (str((float(self.WHRange[0])+float(self.WHRange[1]))/2.), self.WHRange[0], self.WHRange[1]));
        #self.modelBuilder.doVar("r_ggH[1,0.,20.]");
        #self.modelBuilder.doVar("r_WH[1,0.,20.]");
        #self.modelBuilder.doVar("br_ggH[1.,1.,1.]");
        self.modelBuilder.doVar("br_Haa[1.,0.,1.]");
        ### TEST ME ### poi = ",".join(["r_"+m for m in self.modes])
        ###poi = "xs_ggH,br_Haa"
        for m in self.modes:
            poi = ",".join(["r_"+m for m in self.modes])
#            poi = ",".join(["xs_"+m for m in self.modes])
        print poi
#        poi += ",br_Haa"

        self.modelBuilder.doVar("r_ggH[%s,%s,%s]" % (str((float(self.ggHRange[0])+float(self.ggHRange[1]))/2.), self.ggHRange[0], self.ggHRange[1]));
        self.modelBuilder.doVar("r_WH[%s,%s,%s]" % (str((float(self.WHRange[0])+float(self.WHRange[1]))/2.), self.WHRange[0], self.WHRange[1]));
        #self.modelBuilder.factory_('expr::r_ggH(\"@0*@1\", xs_ggH, br_Haa)')
        #self.modelBuilder.factory_('expr::r_WH(\"@0*@1\", xs_WH, br_Haa)')
        
        ## Define Higgs boson mass as another parameter. It will be floating if mARange is set otherwise it will be treated
        ## as fixed. NOTE: this is only left here as an extended example. It's not useful to have mA floating at the moment.
        if self.modelBuilder.out.var("MH"):
            if len(self.mHRange):
                print 'MH will be left floating within', self.mARange[0], 'and', self.mARange[1]
                self.modelBuilder.out.var("MH").setRange(float(self.mARange[0]),float(self.mARange[1]))
                self.modelBuilder.out.var("MH").setConstant(False)
                poi+=',MH'
            else:
                print 'MH will be assumed to be', self.options.mass
                self.modelBuilder.out.var("MH").removeRange()
                self.modelBuilder.out.var("MH").setVal(self.options.mass)
        else:
            if len(self.mARange):
                print 'MH will be left floating within', self.mARange[0], 'and', self.mARange[1]
                self.modelBuilder.doVar("MH[%s,%s]" % (self.mARange[0],self.mARange[1]))
                poi+=',MH'
            else:
                print 'MH (not there before) will be assumed to be', self.options.mass
                self.modelBuilder.doVar("MH[%g]" % self.options.mass)
        ## define set of POIs
        
        self.modelBuilder.doSet("POI",poi)
        
    def getHiggsSignalYieldScale(self,production,decay, energy):

### TESTME ###         if production == "ggH" or production == "WH":
### TESTME ###             ## This is an example how to multiply the yields r_ggH and r_WH with the roofit variables ggH_xsec and WH_xsec
### TESTME ###             ## that have been defined above, with the help of a roofit expression.
### TESTME ###             #
### TESTME ###             #self.modelBuilder.factory_('expr::%s_yield("@0*@1", r_%s, %s_xsec)' % (production, production, production))
### TESTME ###             #
### TESTME ###             ## This is the trivial model that we follow now. We just pass on the values themselves. Yes this is just a
### TESTME ###             ## trivial renaming, but we leave it in as an example. Instead also r_ggH and r_WH could be passed on directly
### TESTME ###             ## in the return function instead of the newly defined variables ggH_yields or WH_yield.
### TESTME ###             self.modelBuilder.factory_('expr::%s_yield("@0", r_%s)' % (production, production))
### TESTME ###             return "%s_yield" % production
        
        print "PRODUCTION in getHiggsSignalYieldScale is " + production
        if production in ["ggH", "WH"]:
            #self.modelBuilder.factory_('expr::r_%s(\"@0*@1\", xs_ggH, br_Haa)' %(production))
            print "r_%s" %production
            return "r_%s" %production
        else:
            return 1
        #if production == "WH":
            #self.modelBuilder.factory_('expr::r_%s(\"@0*@1\", xs_WH, br_Haa)' %(production))
            #print "r_%s" %production
            #return "r_%s" %production

        raise RuntimeError, "Unknown production mode '%s'" % production


## this is the entry point for text2workspace.py

floatingNMSSMXSHiggs = FloatingNMSSMXSHiggs()
