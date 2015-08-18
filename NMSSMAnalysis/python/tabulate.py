#! /usr/bin/env python
import os
import sys
#from ROOT import *
from optparse import OptionParser, OptionGroup

parser = OptionParser(usage="usage: %prog [options] ARG1 ARG2 ARG3 ...",description="This is a script to retrieve and tabulate the results of runAsym.py, using the log files produced by it.")

optGroup = OptionGroup(parser, "MAIN OPTIONS", "These are the command line options for this script.")
optGroup.add_option("--highMT", dest="highMT", default=True, action="store_true", help="Get limits from the log files in the high MT bin")
optGroup.add_option("--lowMT", dest="lowMT", default=False, action="store_true", help= "Get limits from the log files in the low MT bin")
parser.add_option_group(optGroup)
#optGroup.add_option("--WH", dest="WH", default=True, action="store_true", help="Get limits from the WH log files in the high MT bin")
#optGroup.add_option("--ggH", dest="ggH", default=False, action="store_true", help="Get limits from the ggH log files in the high MT bin")

## check number of arguments; in case print usage
(options, args) = parser.parse_args()
print args
print options
if len(args) < 0 :
    parser.print_usage()
    exit(1)

def getLimit(filename, limstring):
    try:
        readfile = open(filename, 'r')
    except:
        print "Not a valid filename."
        sys.exit()
        
    for line in readfile:
        if line.startswith(limstring):
            startpos = line.find(':')
            theRest = line[startpos+1:]
            theRestStripped = ''.join(theRest.split())
            rlimit = theRestStripped.split('<')
            print rlimit
            try:
                value = float(rlimit[len(rlimit) - 1])
                return value
            except:
                print "Not a valid limit."
                


workingdir = ""
MTbin = ""
channel = ""

if options.highMT :
    workingdir = "/afs/cern.ch/user/f/friccita/CMSSW_6_1_2/src/HiggsAnalysis/NMSSMAnalysis/LIMITS/highMT/"
    MTbin = "highMT"
if options.lowMT :
    workingdir = "/afs/cern.ch/user/f/friccita/CMSSW_6_1_2/src/HiggsAnalysis/NMSSMAnalysis/LIMITS/lowMT/"
    MTbin = "lowMT"
#if options.WH :
#    channel = "WH"
#if options.ggH :
#    channel = "ggH"

print "Getting results for the %s bin" %(MTbin)

os.chdir(workingdir)
outfilename = workingdir + "tableOfLimits_%s_4sig_20GeV_allsignals_unblinded.txt" %(MTbin)
massList = ['5', '7', '9', '11', '13', '15']
outfile = open(outfilename,'w')
outfile.write("mass\t-2sig\t-1sig\tmed\t+1sig\t+2sig\tobserved\n")

sub_obs = "Observed Limit:"
sub_minTwoSig = "Expected  2.5%:"
sub_minOneSig = "Expected 16.0%:"
sub_median = "Expected 50.0%:"
sub_plusOneSig = "Expected 84.0%:"
sub_plusTwoSig = "Expected 97.5%:"



for aMass in massList :
    print "aMass = %s" %(aMass)
    limDict = dict()
    logfile = workingdir + "logfile_%s_%s_4sig_20GeV_allsignals_unblinded.txt" %(MTbin, aMass)
    print logfile
    
    limDict[-2] = getLimit(logfile,sub_minTwoSig)
    limDict[-1] = getLimit(logfile,sub_minOneSig)
    limDict[0] = getLimit(logfile,sub_median)
    limDict[1] = getLimit(logfile,sub_plusOneSig)
    limDict[2] = getLimit(logfile,sub_plusTwoSig)
    limDict[3] = getLimit(logfile,sub_obs)
    
    print limDict
    outfile.write("%s\t%f\t%f\t%f\t%f\t%f\t%f\n" %(aMass, limDict[-2], limDict[-1], limDict[0], limDict[1], limDict[2], limDict[3]))
