#!/bin/bash

#MT bins
MTBin=( "_highMT" "_lowMT" )
nMTBins=${#MTBin[@]}
iEndMTBin=`expr $nMTBins - 1`

#pseudoscalar masses
a1Mass=( "_a5" "_a7" "_a9" "_a11" "_a13" "_a15" )
nMasses=${#a1Mass[@]}
iEndMass=`expr $nMasses - 1`

iBeg=0

#loop over a1 mass
for iMass in `seq $iBeg $iEndMass`
do
  echo "a1 mass: ${a1Mass[${iMass}]}"
  massNumber=""
  if [ "${a1Mass[${iMass}]}" = "_a5" ]
    then
      massNumber="5/"
  elif [ "${a1Mass[${iMass}]}" = "_a7" ]
    then
      massNumber="7/"
  elif [ "${a1Mass[${iMass}]}" = "_a9" ]
    then
      massNumber="9/"
  elif [ "${a1Mass[${iMass}]}" = "_a11" ]
    then
      massNumber="11/"
  elif [ "${a1Mass[${iMass}]}" = "_a13" ]
    then
      massNumber="13/"
  elif [ "${a1Mass[${iMass}]}" = "_a15" ]
    then
      massNumber="15/"
  fi

  #loop over MT bin                                                                                                                                           
  for iMTBin in `seq $iBeg $iEndMTBin`
  do
    myBin=""
    if [ "${MTBin[${iMTBin}]}" = "_lowMT" ]
        then
        echo "MT <= 50 GeV"
        myBin="lowMT/"
    elif [ "${MTBin[${iMTBin}]}" = "_highMT" ]
        then
        echo "MT > 50 GeV"
        myBin="highMT/"
    fi
    
    filePrefix1="/afs/cern.ch/user/f/friccita/CMSSW_6_1_2/src/HiggsAnalysis/NMSSMAnalysis/LIMITS/"
    filePrefix2="comb"
    fileSuffix="_Haa_8TeV-125.txt"
    fileName=${filePrefix1}${myBin}${massNumber}${filePrefix2}${a1Mass[${iMass}]}${MTBin[${iMTBin}]}${fileSuffix}
    sed -i 's/muTrig/CMS_eff_m_HLT/g' ${fileName}
    sed -i 's/muIso/CMS_eff_m_iso/g' ${fileName}
    sed -i 's/muID/CMS_eff_m_id/g' ${fileName}
    sed -i 's/softMuID/CMS_eff_m_id_soft/g' ${fileName}
    sed -i 's/tauID/CMS_eff_t_id/g' ${fileName}
    sed -i 's/tauCharge/CMS_eff_t_charge/g' ${fileName}
    sed -i 's/METuncert/CMS_scale_met/g' ${fileName}
    sed -i 's/elecID_HLT/CMS_Haa_eff_e_id_filter/g' ${fileName}
    sed -i 's/softMuID_HLT/CMS_Haa_eff_mu_id_soft_filter/g' ${fileName}
    sed -i 's/tauID_HLT/CMS_Haa_eff_t_id_filter/g' ${fileName}
    sed -i 's/estim_sys/CMS_Haa_estim_sys/g' ${fileName}
    sed -i 's/bkg_sys/CMS_Haa_bkg_sys/g' ${fileName}
    sed -i 's/bkg_BDstat/CMS_Haa_bkg_BDstat/g' ${fileName}
    sed -i 's/CMS_eff_m_id_soft_HLT/CMS_eff_m_id_soft_filter/g' ${fileName}
    sed -i 's/CMS_eff_t_id_soft_HLT/CMS_eff_t_id_soft_filter/g' ${fileName}

  done
done

exit 0
