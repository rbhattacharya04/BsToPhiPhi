#!/bin/bash
for i in 2.1 2.2 2.3 2.4 2.5 2.6 2.7 2.8 2.9 3;
do
  sed -e "s/INDEX/$i/g" submit_job_Signal.sh.tmpl > submit_job_Signal_Pt_$i.sh
  sed -e "s/INDEX/$i/g" submit_job_bkg.sh.tmpl > submit_job_bkg_Pt_$i.sh
done
~      
