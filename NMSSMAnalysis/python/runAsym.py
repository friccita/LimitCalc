#! /usr/bin/env python
import os
import sys
#from ROOT import *
from optparse import OptionParser, OptionGroup

parser = OptionParser(usage="usage: %prog [options] ARG1 ARG2 ARG3 ...",description="This is a script to run Asymptotic limit calculations for the datacards in the various MT bins for the NMSSM analysis; log files for the results are produced.")

optGroup = OptionGroup(parser, "MAIN OPTIONS", "These are the command line options for this script.")
optGroup.add_option("--highMT", dest="highMT", default=True, action="store_true", help="Run Asymptotic over datacards in the high MT bin")
optGroup.add_option("--lowMT", dest="lowMT", default=False, action="store_true", help="Run Asymptotic over datacards in the low MT bin")
#optGroup.add_option("--ggH", dest="ggH", default=True, action="store_true", help="Calculate limit for ggH channel while profiling other channel(s)")
#optGroup.add_option("--WH", dest="WH", default=False, action="store_true", help="Calculate limit for WH channel while profiling other channel(s)")
parser.add_option_group(optGroup)

## check number of arguments; in case print usage
(options, args) = parser.parse_args()
print args
print options
if len(args) < 0 :
    parser.print_usage()
    exit(1)

workingdir = ""
MTbin = ""
channelName = ""

if options.highMT :
    workingdir = "/afs/cern.ch/user/f/friccita/CMSSW_6_1_2/src/HiggsAnalysis/NMSSMAnalysis/LIMITS/highMT/"
    MTbin = "highMT"
if options.lowMT :
    workingdir = "/afs/cern.ch/user/f/friccita/CMSSW_6_1_2/src/HiggsAnalysis/NMSSMAnalysis/LIMITS/lowMT/"
    MTbin = "lowMT"
#if options.ggH :
#    channelName = "ggH"
#if options.WH :
#    channelName = "WH"

print "Limits for the %s bin and %s channel will be calculated for this directory: %s" %(MTbin, channelName, workingdir)

os.chdir(workingdir)
for aMass in ['5', '7', '9', '11', '13', '15'] :
    print aMass
#    inWH = workingdir + aMass + "/WH_Haa_8TeV-126.txt"
#    inggH = workingdir + aMass + "/ggH_Haa_8TeV-126.txt"
    inputfile = workingdir + aMass + "/comb_a%s_%s_Haa_8TeV-125.root" %(aMass, MTbin)
    logfile = workingdir + "logfile_%s_%s_4sig_20GeV_allsignals_unblinded.txt" %(MTbin, aMass)
    print "input file = %s" %(inputfile)
    print "output log file = %s" %(logfile)
    
    #print "combineCards.py %s %s > %s" %(inWH, inggH, inputfile)
    #os.system("combineCards.py %s %s > %s" %(inWH, inggH, inputfile))
    # --rMax 40
    #combine -M Asymptotic --redefineSignalPOIs r_ggH comb_Haa_8TeV-126.root -t -1  --setPhysicsModelParameters r_ggH=0,r_WH=0

#old commands for calculating limits on ggH and WH only
#    print "combine -M Asymptotic --redefineSignalPOIs r_%s %s -t -1 --run=blind --setPhysicsModelParameters r_ggH=0,r_WH=0 -n _%s_a%s >& %s &" %(channelName, inputfile, channelName, aMass, logfile)
#    os.system("combine -M Asymptotic --redefineSignalPOIs r_%s %s -t -1 --run=blind --setPhysicsModelParameters r_ggH=0,r_WH=0 -n _%s_a%s >& %s &" %(channelName, inputfile, channelName, aMass, logfile))

    #commands for 4-signal datacards
#    if options.highMT :
#        print "combine -M Asymptotic --redefineSignalPOIs r_ggHWH %s -t -1 --run=blind --freezeNuisances r_VBF,r_ZH -n _%s_a%s >& %s &" %(inputfile, MTbin, aMass, logfile)
#        os.system("combine -M Asymptotic --redefineSignalPOIs r_ggHWH %s -t -1 --run=blind --freezeNuisances r_VBF,r_ZH -n _%s_a%s >& %s &" %(inputfile, MTbin, aMass, logfile))
#    if options.lowMT :
#        print "combine -M Asymptotic --redefineSignalPOIs r_ggHVBF %s -t -1 --run=blind --freezeNuisances r_WH,r_ZH -n _%s_a%s >& %s &" %(inputfile, MTbin, aMass, logfile)
#        os.system("combine -M Asymptotic --redefineSignalPOIs r_ggHVBF %s -t -1 --run=blind --freezeNuisances r_WH,r_ZH -n _%s_a%s >& %s &" %(inputfile, MTbin, aMass, logfile))


#BLINDED
    #if options.highMT :
        #print "combine -M Asymptotic --redefineSignalPOIs r_all %s -t -1 --run=blind -n _%s_a%s >& %s &" %(inputfile, MTbin, aMass, logfile)
        #os.system("combine -M Asymptotic --redefineSignalPOIs r_all %s -t -1 --run=blind -n _%s_a%s >& %s &" %(inputfile, MTbin, aMass, logfile))
    #if options.lowMT :
        #print "combine -M Asymptotic --redefineSignalPOIs r_all %s -t -1 --run=blind -n _%s_a%s >& %s &" %(inputfile, MTbin, aMass, logfile)
        #os.system("combine -M Asymptotic --redefineSignalPOIs r_all %s -t -1 --run=blind -n _%s_a%s >& %s &" %(inputfile, MTbin, aMass, logfile))

#UNBLINDED
    if options.highMT :
        print "combine -M Asymptotic --redefineSignalPOIs r_all %s --run=both -n _%s_a%s >& %s &" %(inputfile, MTbin, aMass, logfile)
        os.system("combine -M Asymptotic --redefineSignalPOIs r_all %s --run=both -n _%s_a%s >& %s &" %(inputfile, MTbin, aMass, logfile))
    if options.lowMT :
        print "combine -M Asymptotic --redefineSignalPOIs r_all %s --run=both -n _%s_a%s >& %s &" %(inputfile, MTbin, aMass, logfile)
        os.system("combine -M Asymptotic --redefineSignalPOIs r_all %s --run=both -n _%s_a%s >& %s &" %(inputfile, MTbin, aMass, logfile))
