#!/bin/bash
for i in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1;
do
  sed -e "s/INDEX/$i/g" submit_job_Signal.sh.tmpl > submit_job_Signal_dz_$i.sh
  sed -e "s/INDEX/$i/g" submit_job_bkg.sh.tmpl > submit_job_bkg_dz_$i.sh
done
~      
