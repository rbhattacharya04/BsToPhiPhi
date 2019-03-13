#!/bin/bash
for i in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1;
do
  sed -e "s/INDEX/$i/g" Signal_pu200_tight_baseline.job.tmpl > Signal_pu200_tight_baseline_dz_$i.job
  sed -e "s/INDEX/$i/g" bkg_pu200_tight_baseline.job.tmpl > bkg_pu200_tight_baseline_dz_$i.job
done
~      
